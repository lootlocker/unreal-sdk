// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "LootLockerLogger.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "LootLockerSDK.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Utils/LootLockerUtilities.h"

const FString ULootLockerHttpClient::UserAgent = FString::Format(TEXT("X-UnrealEngine-Agent/{0}"), { ENGINE_VERSION_STRING });
const FString ULootLockerHttpClient::UserInstanceIdentifier = FGuid::NewGuid().ToString();
FString ULootLockerHttpClient::SDKVersion = "";
TWeakObjectPtr<ULootLockerHttpClient> ULootLockerHttpClient::SingletonInstance = nullptr;
FCriticalSection ULootLockerHttpClient::SingletonMutex;

ULootLockerHttpClient::ULootLockerHttpClient()
{
}

ULootLockerHttpClient* ULootLockerHttpClient::Get()
{
    if (SingletonInstance.IsValid())
    {
        return SingletonInstance.Get();
    }

    FScopeLock Lock(&SingletonMutex);
    if (!SingletonInstance.IsValid())
    {
        // Create in transient package so it isn't saved; mark as RF_MarkAsRootSet to avoid GC if desired
        ULootLockerHttpClient* NewObj = NewObject<ULootLockerHttpClient>(GetTransientPackage());
        // Optionally prevent GC: NewObj->AddToRoot(); Uncomment if you want it truly persistent.
        SingletonInstance = NewObj;
    }
    return SingletonInstance.Get();
}

ULootLockerHttpClient& ULootLockerHttpClient::GetRef()
{
    ULootLockerHttpClient* Instance = Get();
    checkf(Instance != nullptr, TEXT("ULootLockerHttpClient singleton instance could not be created."));
    return *Instance;
}

void ULootLockerHttpClient::LogFailedRequestInformation(const FLootLockerResponse& Response, const FString& AllHeadersDelimited)
{
    FLootLockerLogger::LogHttpRequest(Response, AllHeadersDelimited);
}

void ULootLockerHttpClient::LogSuccessfulRequestInformation(const FLootLockerResponse& Response, const FString& AllHeadersDelimited)
{
    FLootLockerLogger::LogHttpRequest(Response, AllHeadersDelimited);
}

bool ULootLockerHttpClient::ResponseIsSuccess(const FHttpResponsePtr& InResponse, bool bWasSuccessful)
{
    if (!bWasSuccessful || !InResponse.IsValid())
        return false;

    return EHttpResponseCodes::IsOk(InResponse->GetResponseCode());
}

FString ULootLockerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders) const
{
	FHttpModule* HttpModule = &FHttpModule::Get();
    if(SDKVersion.IsEmpty())
    {
	    const TSharedPtr<IPlugin> Ptr = IPluginManager::Get().FindPlugin("LootLockerSDK");
        if (Ptr.IsValid())
        {
            SDKVersion = Ptr->GetDescriptor().VersionName;
            FLootLockerLogger::LogVerbose(FString::Printf(TEXT("LootLocker version: v%s"), *SDKVersion));
        }
    }
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
	Request->SetURL(endPoint);

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("LL-Instance-Identifier"), UserInstanceIdentifier);
    Request->SetHeader(TEXT("LL-SDK-Version"), SDKVersion);
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

    for (TTuple<FString, FString> CustomHeader : customHeaders)
    {
        Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
    }

	Request->SetVerb(requestType);
    Request->SetContentAsString(data);

    FString playerUlid = PlayerData.PlayerUlid;
    FString requestTime = FDateTime::Now().ToString();
    FString DelimitedHeaders = "";
    TArray<FString> AllHeaders = Request->GetAllHeaders();
    for (auto Header : AllHeaders)
    {
        DelimitedHeaders += TEXT("    ") + Header + TEXT("\n");
    }

    FString requestId = FGuid::NewGuid().ToString();

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, endPoint, requestType, data, playerUlid, requestTime, DelimitedHeaders, requestId](FHttpRequestPtr Req, const FHttpResponsePtr& Response, bool bWasSuccessful)
	{
        if (!Response.IsValid())
        {
            FLootLockerResponse Error = LootLockerResponseFactory::Error<FLootLockerResponse>("HTTP Response was invalid", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP, playerUlid);
            Error.Context.RequestTime = requestTime;
            Error.Context.RequestId = requestId;
            Error.Context.RequestURL = endPoint;
            Error.Context.RequestMethod = requestType;
            Error.Context.RequestParametersJsonString = data;
            LogFailedRequestInformation(Error, DelimitedHeaders);
            onCompleteRequest.ExecuteIfBound(Error);
            return;
        }

		FLootLockerResponse response;
        
        response.success = ResponseIsSuccess(Response, bWasSuccessful);
        response.StatusCode = Response->GetResponseCode();
		response.FullTextFromServer = Response->GetContentAsString();
        response.Context.PlayerUlid = playerUlid;
        response.Context.RequestTime = requestTime;
        response.Context.RequestId = requestId;
        response.Context.RequestURL = endPoint;
        response.Context.RequestMethod = requestType;
        response.Context.RequestParametersJsonString = data;
		if (!response.success)
		{
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorData>(response.FullTextFromServer, &response.ErrorData, 0, 0);
            FString RetryAfterHeader = Response->GetHeader("retry-after");
            if(!RetryAfterHeader.IsEmpty()) {
                response.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
            }
            LogFailedRequestInformation(response, DelimitedHeaders);
		}
        else
        {
            LogSuccessfulRequestInformation(response, DelimitedHeaders);
        }
		onCompleteRequest.ExecuteIfBound(response);
	});
	Request->ProcessRequest();
    return requestId;
}

FString ULootLockerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>& AdditionalFields, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders) const
{
    FHttpModule* HttpModule = &FHttpModule::Get();
    if (SDKVersion.IsEmpty())
    {
        TSharedPtr<IPlugin> Ptr = IPluginManager::Get().FindPlugin("LootLockerSDK");
        if (Ptr.IsValid())
        {
            SDKVersion = Ptr->GetDescriptor().VersionName;
        }
    }
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
	Request->SetURL(endPoint);

    FString Boundary = "lootlockerboundary";

	Request->SetHeader(TEXT("User-Agent"), UserAgent);
	Request->SetHeader(TEXT("LL-Instance-Identifier"), UserInstanceIdentifier);
    Request->SetHeader(TEXT("LL-SDK-Version"), SDKVersion);

    Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

    for (TTuple<FString, FString> CustomHeader : customHeaders)
    {
        Request->SetHeader(CustomHeader.Key, CustomHeader.Value);
    }
    FString DelimitedHeaders = "";
    TArray<FString> AllHeaders = Request->GetAllHeaders();
    for (auto Header : AllHeaders)
    {
        DelimitedHeaders += TEXT("    ") + Header + TEXT("\n");
    }

    Request->SetVerb(requestType);

    FString requestTime = FDateTime::Now().ToString();
    TArray<uint8> UpFileRawData;
    if (!FFileHelper::LoadFileToArray(UpFileRawData, *FilePath)) {
        FLootLockerResponse Error = LootLockerResponseFactory::Error<FLootLockerResponse>("HTTP Response was invalid", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP, PlayerData.PlayerUlid);
        Error.Context.RequestTime = requestTime;
        LogFailedRequestInformation(Error, DelimitedHeaders);
        onCompleteRequest.ExecuteIfBound(Error);
        return "";
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
    if (LastSlashPos == -1) {
        FilePath.FindLastChar('\\', LastSlashPos);
    }
    FString FileName = FilePath.RightChop(LastSlashPos + 1);

    FileHeader.Append(FileName + "\"\r\n\r\n");

    Data.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
    Data.Append(UpFileRawData);
    Data.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

    Request->SetContent(Data);

    FString playerUlid = PlayerData.PlayerUlid;
    FString requestId = FGuid::NewGuid().ToString();

    Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this, requestType, endPoint, playerUlid, requestTime, DelimitedHeaders, requestId](FHttpRequestPtr Req, const FHttpResponsePtr& Response, bool bWasSuccessful)
        {
            if (!Response.IsValid())
            {
                FLootLockerResponse Error = LootLockerResponseFactory::Error<FLootLockerResponse>("HTTP Response was invalid", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP, playerUlid);
                Error.Context.RequestTime = requestTime;
                LogFailedRequestInformation(Error, DelimitedHeaders);
                onCompleteRequest.ExecuteIfBound(Error);
                return;
            }
            FLootLockerResponse response;

            response.success = ResponseIsSuccess(Response, bWasSuccessful);
            response.StatusCode = Response->GetResponseCode();
            response.FullTextFromServer = Response->GetContentAsString();
            response.Context.PlayerUlid = playerUlid;
            response.Context.RequestTime = requestTime;
            response.Context.RequestId = requestId;
            response.Context.RequestURL = endPoint;
            response.Context.RequestMethod = requestType;
            if (!response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorData>(response.FullTextFromServer, &response.ErrorData, 0, 0);
                FString RetryAfterHeader = Response->GetHeader("retry-after");
                if(!RetryAfterHeader.IsEmpty()) {
                    response.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
                }
                LogFailedRequestInformation(response, DelimitedHeaders);
            }
    		else
            {
                LogSuccessfulRequestInformation(response, DelimitedHeaders);
            }
            onCompleteRequest.ExecuteIfBound(response);
        });
    Request->ProcessRequest();
    return requestId;
}
