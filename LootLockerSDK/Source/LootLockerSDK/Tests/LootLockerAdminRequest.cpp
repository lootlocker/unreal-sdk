// Copyright (c) 2021 LootLocker

#include "LootLockerAdminRequest.h"

#if ENGINE_MAJOR_VERSION > 4

#include <future>
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformProcess.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/CommandLine.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

// ─── Statics ──────────────────────────────────────────────────────────────────

FString FLootLockerAdminRequest::AdminToken;
int32   FLootLockerAdminRequest::OrganisationId = 0;
int32   FLootLockerAdminRequest::ActiveGameId   = 0;

// ─── Private helpers ──────────────────────────────────────────────────────────

FString FLootLockerAdminRequest::GetBaseUrl()
{
#ifdef LOOTLOCKER_USE_LOCAL_DEVENV
	return TEXT("http://localhost:8080/");
#else
	return TEXT("https://api.lootlocker.com/");
#endif
}

bool FLootLockerAdminRequest::GetCredentials(FString& OutEmail, FString& OutPassword)
{
	OutEmail    = FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_ADMIN_EMAIL"));
	OutPassword = FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_ADMIN_PASSWORD"));
	if (!OutEmail.IsEmpty() && !OutPassword.IsEmpty())
	{
		return true;
	}

	// Fall back to command-line args (-adminemail=foo@bar.com -adminpassword=secret)
	const TCHAR* CmdLine = FCommandLine::Get();
	FString Email, Password;
	FParse::Value(CmdLine, TEXT("-adminemail="),    Email);
	FParse::Value(CmdLine, TEXT("-adminpassword="), Password);

	if (!Email.IsEmpty())    OutEmail    = Email;
	if (!Password.IsEmpty()) OutPassword = Password;

	return !OutEmail.IsEmpty() && !OutPassword.IsEmpty();
}

// ─── Public API ───────────────────────────────────────────────────────────────

bool FLootLockerAdminRequest::EnsureSignedIn()
{
	if (!AdminToken.IsEmpty())
	{
		return true;
	}

	FString Email, Password;
	if (!GetCredentials(Email, Password))
	{
		UE_LOG(LogTemp, Error,
			TEXT("LootLockerAdmin: No credentials found. "
			     "Set LOOTLOCKER_ADMIN_EMAIL / LOOTLOCKER_ADMIN_PASSWORD env vars, "
			     "or pass -adminemail=<email> -adminpassword=<pass> on the command line."));
		return false;
	}

	return Login(Email, Password);
}

bool FLootLockerAdminRequest::Login(const FString& Email, const FString& Password)
{
	TSharedRef<FJsonObject> RequestJson = MakeShared<FJsonObject>();
	RequestJson->SetStringField(TEXT("email"),    Email);
	RequestJson->SetStringField(TEXT("password"), Password);

	FString JsonBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonBody);
	FJsonSerializer::Serialize(RequestJson, Writer);

	const FLootLockerAdminResponse Response =
		SendOnce(GetBaseUrl() + TEXT("v1/session"), TEXT("POST"), JsonBody);

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerAdmin: Login failed (%d): %s"),
			Response.StatusCode, *Response.Body);
		return false;
	}

	TSharedPtr<FJsonObject> Json;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.Body);
	if (!FJsonSerializer::Deserialize(Reader, Json) || !Json.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerAdmin: Failed to parse login response"));
		return false;
	}

	Json->TryGetStringField(TEXT("auth_token"), AdminToken);

	const TArray<TSharedPtr<FJsonValue>>* Orgs;
	if (Json->TryGetArrayField(TEXT("organisations"), Orgs) && Orgs->Num() > 0)
	{
		TSharedPtr<FJsonObject> FirstOrg = (*Orgs)[0]->AsObject();
		if (FirstOrg.IsValid())
		{
			FirstOrg->TryGetNumberField(TEXT("id"), OrganisationId);
		}
	}

	if (AdminToken.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerAdmin: Login response missing auth_token"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("LootLockerAdmin: Signed in (org %d)"), OrganisationId);
	return true;
}

FLootLockerAdminResponse FLootLockerAdminRequest::SendOnce(
	const FString& FullUrl, const FString& Method, const FString& JsonBody)
{
	// Use a heap-allocated promise so the lambda can capture it by raw pointer.
	// The promise is deleted on this thread after get() returns.
	std::promise<FLootLockerAdminResponse>* PromisePtr =
		new std::promise<FLootLockerAdminResponse>();
	std::future<FLootLockerAdminResponse> Future = PromisePtr->get_future();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
		FHttpModule::Get().CreateRequest();

	Request->SetURL(FullUrl);
	Request->SetVerb(Method);
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accept"),       TEXT("application/json"));

	if (!AdminToken.IsEmpty())
	{
		Request->SetHeader(TEXT("x-auth-token"), AdminToken);
	}

	if (!JsonBody.IsEmpty())
	{
		Request->SetContentAsString(JsonBody);
	}

	Request->OnProcessRequestComplete().BindLambda(
		[PromisePtr](FHttpRequestPtr, FHttpResponsePtr Response, bool bConnected)
		{
			FLootLockerAdminResponse AdminResponse;
			if (bConnected && Response.IsValid())
			{
				AdminResponse.StatusCode = Response->GetResponseCode();
				AdminResponse.Body       = Response->GetContentAsString();
				AdminResponse.bSuccess   =
					AdminResponse.StatusCode >= 200 && AdminResponse.StatusCode < 300;
			}
			else
			{
				AdminResponse.StatusCode = 0;
				AdminResponse.Body       = TEXT("Connection failed");
			}
			PromisePtr->set_value(MoveTemp(AdminResponse));
		});

	if (!Request->ProcessRequest())
	{
		delete PromisePtr;
		FLootLockerAdminResponse Failed;
		Failed.Body = TEXT("ProcessRequest() returned false");
		return Failed;
	}

	FLootLockerAdminResponse Result = Future.get();
	delete PromisePtr;
	return Result;
}

FLootLockerAdminResponse FLootLockerAdminRequest::Send(
	const FString& Endpoint, const FString& Method, const FString& JsonBody)
{
	const FString ProcessedEndpoint =
		Endpoint.Replace(TEXT("#GAMEID#"), *FString::FromInt(ActiveGameId));
	const FString FullUrl = GetBaseUrl() + ProcessedEndpoint;

	for (int32 Attempt = 0; Attempt <= MaxRetries; ++Attempt)
	{
		FLootLockerAdminResponse Response = SendOnce(FullUrl, Method, JsonBody);

		if (Response.StatusCode != 429)
		{
			return Response;
		}

		if (Attempt >= MaxRetries)
		{
			break;
		}

		int32 RetryAfter = 5;
		TSharedPtr<FJsonObject> Json;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.Body);
		if (FJsonSerializer::Deserialize(Reader, Json) && Json.IsValid())
		{
			Json->TryGetNumberField(TEXT("retry_after_seconds"), RetryAfter);
		}

		UE_LOG(LogTemp, Warning,
			TEXT("LootLockerAdmin: Rate limited (429), retrying in %ds (attempt %d/%d)"),
			RetryAfter, Attempt + 1, MaxRetries);

		FPlatformProcess::Sleep(static_cast<float>(RetryAfter));
	}

	FLootLockerAdminResponse Failed;
	Failed.Body = TEXT("Request exceeded maximum retry count");
	return Failed;
}

#endif // ENGINE_MAJOR_VERSION > 4
