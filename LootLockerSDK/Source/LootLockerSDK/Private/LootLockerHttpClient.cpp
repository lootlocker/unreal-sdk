// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerSDK.h"
#include "LootLockerPersistentDataHolder.h"
#include "Misc/FileHelper.h"
#include "LootLockerConfig.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"

unsigned long requestNumber = 0;

ULootLockerHttpClient::ULootLockerHttpClient()
{

}

void ULootLockerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, bool useHeader, bool useAdmin, bool useDomainKey, bool useDevHeaders) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();

    auto localRequestNumber = ++requestNumber;
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
            UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Request #%d, Setting session token to: %s"), localRequestNumber, *ULootLockerPersistentDataHolder::Token);
            Request->SetHeader(TEXT("x-session-token"), ULootLockerPersistentDataHolder::Token);
        } else {
            UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Request #%d, Setting admin token to: %s"), localRequestNumber, *ULootLockerPersistentDataHolder::AdminToken);
            Request->SetHeader(TEXT("x-auth-token"), ULootLockerPersistentDataHolder::AdminToken);
        }
	}

	// Needed by the White Label Login
	if (useDomainKey)
	{
        UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Request #%d, Setting domain key to: %s"), localRequestNumber, *ULootLockerPersistentDataHolder::DomainKey);
		Request->SetHeader(TEXT("domain-key"), ULootLockerPersistentDataHolder::DomainKey);
	}

	// This is normally sent via the body, but with the white label login it goes in the header!
	if (useDevHeaders)
	{
        UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Request #%d, Setting development mode to: %s"), localRequestNumber, GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
		Request->SetHeader(TEXT("is-development"),GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	}

	Request->SetVerb(requestType);
    Request->SetContentAsString(data);

    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Request #%d, Making request %s to %s"), localRequestNumber, *requestType, *endPoint);
    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Request #%d, Data: %s"), localRequestNumber, *data);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, endPoint, requestType, data, localRequestNumber](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerResponse response;

			if (!ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, data, localRequestNumber))
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

bool ULootLockerHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful, FString RequestMethod, FString Endpoint, FString Data, unsigned long localRequestNumber)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Req #%d, Http Response returned error code: %d"), localRequestNumber, InResponse->GetResponseCode());
    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Req #%d, Http Response content:\n%s"), localRequestNumber, *InResponse->GetContentAsString());
    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Req #%d, Http Request endpoint: %s to %s"), localRequestNumber, *RequestMethod, *Endpoint);
    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Req #%d, Http Request data: %s"), localRequestNumber, *Data);
	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode()))
	{
		return true;
	}
	else
	{
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

            bool success = ResponseIsValid(Response, bWasSuccessful, requestType, endPoint, FString("Data Stream"), 1337);

            response.success = success;
            response.ServerCallHasError = !success;

            onCompleteRequest.ExecuteIfBound(response);
        });
    Request->ProcessRequest();
}
