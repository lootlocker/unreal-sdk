// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerSDK.h"
#include "LootLockerPersistentDataHolder.h"
#include "Misc/FileHelper.h"
#include "LootLockerConfig.h"

ULootLockerHttpClient::ULootLockerHttpClient()
{

}

void ULootLockerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, bool useHeader, bool useAdmin, bool useDomainKey, bool useDevHeaders) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MINOR_VERSION < 26
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif
	Request->SetURL(endPoint);

	ULootLockerPersistentDataHolder::CachedLastEndpointUsed = endPoint;
	ULootLockerPersistentDataHolder::CachedLastRequestTypeUsed = requestType;
	ULootLockerPersistentDataHolder::CachedLastDataSentToServer = data;

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	// Todo: Replace this header madness with an optional TMap of headers.
	if (useHeader)
	{
        if (!useAdmin) {
            Request->SetHeader(TEXT("x-session-token"), ULootLockerPersistentDataHolder::Token);
        } else {
            Request->SetHeader(TEXT("x-auth-token"), ULootLockerPersistentDataHolder::AdminToken);
        }
	}

	// Needed by the White Label Login
	if (useDomainKey)
	{
		Request->SetHeader(TEXT("domain-key"), ULootLockerPersistentDataHolder::DomainKey);
	}

	// This is normally sent via the body, but with the white label login it goes in the header!
	if (useDevHeaders)
	{
		Request->SetHeader(TEXT("is-development"),GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	}

	Request->SetVerb(requestType);
    Request->SetContentAsString(data);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, endPoint, requestType, data](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerResponse response;

			if (!ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, data))
			{
				response.success = false;
				response.FullTextFromServer = Response->GetContentAsString();
				response.ServerCallHasError = true;
				response.ServerCallStatusCode = Response->GetResponseCode();
				response.ServerError = Response->GetContentAsString();
				onCompleteRequest.ExecuteIfBound(response);
				return;
			}

			response.success = true;
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallHasError = false;
			response.ServerCallStatusCode = Response->GetResponseCode();
			response.ServerError = Response->GetContentAsString();
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();
}

bool ULootLockerHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful, FString RequestMethod, FString Endpoint, FString Data)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode()))
	{
		return true;
	}
	else
	{
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Response returned error code: %d"), InResponse->GetResponseCode());
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Response content:\n%s"), *InResponse->GetContentAsString());
        UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Request endpoint: %s to %s"), *RequestMethod, *Endpoint);
        UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Http Request data: %s"), *Data);
		return false;
	}
}

void ULootLockerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FResponseCallback& onCompleteRequest, bool useHeader, bool useAdmin) const
{
    FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MINOR_VERSION < 26
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif
	Request->SetURL(endPoint);

    ULootLockerPersistentDataHolder::CachedLastEndpointUsed = endPoint;
    ULootLockerPersistentDataHolder::CachedLastRequestTypeUsed = requestType;
    ULootLockerPersistentDataHolder::CachedLastDataSentToServer = FString(TEXT("Data Stream"));

    FString Boundary = "lootlockerboundary";

    Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

    if (useHeader)
    {
        if (!useAdmin) {
            Request->SetHeader(TEXT("x-session-token"), ULootLockerPersistentDataHolder::Token);
        } else {
            Request->SetHeader(TEXT("x-auth-token"), ULootLockerPersistentDataHolder::AdminToken);
        }
    }

    Request->SetVerb(requestType);

    TArray<uint8> UpFileRawData;
    if (!FFileHelper::LoadFileToArray(UpFileRawData, *FilePath)) {
        UE_LOG(LogLootLockerGameSDK, Error, TEXT("FILE NOT READ!"));
        return;
    }

    TArray<uint8> Data;

    const FString BeginBoundary = TEXT("\r\n--" + Boundary + "\r\n");
    const FString EndBoundary = TEXT("\r\n--" + Boundary + "--\r\n");

    for (auto& KeyValuePair : AdditionalFields) {
        Data.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

        FString ParameterEntry = "Content-Type: text/plain; charset=\"utf-8\"\r\n";
        ParameterEntry.Append(TEXT("Content-Disposition: form-data; name=\""));
        ParameterEntry.Append(KeyValuePair.Key);
        ParameterEntry.Append(TEXT("\"\r\n\r\n"));
        ParameterEntry.Append(KeyValuePair.Value);

        Data.Append((uint8*)TCHAR_TO_ANSI(*ParameterEntry), ParameterEntry.Len());
    }

    Data.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());

    FString FileHeader = (TEXT("Content-Type: application/octet-stream\r\n"));
    FileHeader.Append(TEXT("Content-disposition: form-data; name=\"file\"; filename=\""));

    int32 LastSlashPos = 0;
    FilePath.FindLastChar('/', LastSlashPos);
    FString FileName = FilePath.RightChop(LastSlashPos + 1);

    FileHeader.Append(FileName + "\"\r\n\r\n");

    Data.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
    Data.Append(UpFileRawData);
    Data.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

    Request->SetContent(Data);

    Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, requestType, endPoint](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            const FString ResponseString = Response->GetContentAsString();
            FLootLockerResponse response;

            response.FullTextFromServer = Response->GetContentAsString();
            response.ServerCallStatusCode = Response->GetResponseCode();
            response.ServerError = Response->GetContentAsString();

            bool success = ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, FString("Data Stream"));

            response.success = success;
            response.ServerCallHasError = !success;

            onCompleteRequest.ExecuteIfBound(response);
        });
    Request->ProcessRequest();
}