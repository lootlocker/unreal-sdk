// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "LootLockerLogger.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "LootLockerSDK.h"
#include "LootLockerConfig.h"
#include "LootLockerStateData.h"
#include "LootLockerSDKManager.h"
#include "LootLockerPlatformManager.h"
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

FString ULootLockerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders, bool bIsRetryAttempt)
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
    if (!PlayerData.Token.IsEmpty())
    {
        Request->SetHeader(TEXT("x-session-token"), PlayerData.Token);
    }
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

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, endPoint, requestType, data, playerUlid, requestTime, DelimitedHeaders, requestId, PlayerData, customHeaders, bIsRetryAttempt](FHttpRequestPtr Req, const FHttpResponsePtr& Response, bool bWasSuccessful)
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
            
            // Check if we should attempt session refresh
            if (ShouldRefreshSession(response.StatusCode, PlayerData, bIsRetryAttempt))
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Attempting session refresh for %s request to %s (Status: %d)"), 
                    *requestType, *endPoint, response.StatusCode));
                
                // Store original request data for retry
                FLootLockerRetryRequestData RetryData(endPoint, requestType, data, onCompleteRequest, PlayerData, customHeaders);
                
                // Attempt session refresh
                RefreshSessionForPlatform(PlayerData, [RetryData, response, onCompleteRequest](bool bRefreshSuccess) {
                    if (bRefreshSuccess)
                    {
                        RetryOriginalRequest(RetryData);
                    }
                    else
                    {
                        onCompleteRequest.ExecuteIfBound(response);
                    }
                });
                return; // Don't call the original callback yet
            }
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

FString ULootLockerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>& AdditionalFields, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders, bool bIsRetryAttempt)
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

    if (!PlayerData.Token.IsEmpty())
    {
        Request->SetHeader(TEXT("x-session-token"), PlayerData.Token);
    }
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

    Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, requestType, endPoint, playerUlid, requestTime, DelimitedHeaders, requestId, PlayerData, customHeaders, FilePath, AdditionalFields, bIsRetryAttempt](FHttpRequestPtr Req, const FHttpResponsePtr& Response, bool bWasSuccessful)
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
                
                // Check if we should attempt session refresh
                if (ShouldRefreshSession(response.StatusCode, PlayerData, bIsRetryAttempt))
                {
                    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Attempting session refresh for %s file upload to %s (Status: %d)"), 
                        *requestType, *endPoint, response.StatusCode));
                    
                    // Store original request data for retry
                    FLootLockerRetryRequestData RetryData(endPoint, requestType, FilePath, AdditionalFields, onCompleteRequest, PlayerData, customHeaders);
                    
                    // Attempt session refresh
                    RefreshSessionForPlatform(PlayerData, [RetryData, response, onCompleteRequest](bool bRefreshSuccess) {
                        if (bRefreshSuccess)
                        {
                            RetryOriginalRequest(RetryData);
                        }
                        else
                        {
                            onCompleteRequest.ExecuteIfBound(response);
                        }
                    });
                    return; // Don't call the original callback yet
                }
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

bool ULootLockerHttpClient::ShouldRefreshSession(int32 StatusCode, const FLootLockerPlayerData& PlayerData, bool bIsRetryAttempt)
{
    // Don't attempt refresh if this is already a retry attempt
    if (bIsRetryAttempt)
    {
        FLootLockerLogger::LogVerbose(TEXT("Skipping session refresh - this is already a retry attempt"));
        return false;
    }
    
    // Check if we should attempt session refresh
    // Only attempt for 401 (Unauthorized) or 403 (Forbidden) responses
    if (StatusCode != 401 && StatusCode != 403)
    {
        return false;
    }
    
    // Check if token refresh is enabled in config
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    if (!Config || !Config->AllowTokenRefresh)
    {
        return false;
    }
    
    return CanRefreshSession(PlayerData);
}

bool ULootLockerHttpClient::CanRefreshSession(const FLootLockerPlayerData& PlayerData)
{
    // Check if platform supports session refresh
    ELootLockerPlatform Platform = PlayerData.CurrentPlatform.Platform;
    
    // Platforms that support refresh tokens
    TArray<ELootLockerPlatform> RefreshSupportedPlatforms = {
        ELootLockerPlatform::Google,
        ELootLockerPlatform::Epic,
        ELootLockerPlatform::AppleSignIn,
        ELootLockerPlatform::AppleGameCenter,
        ELootLockerPlatform::Meta,
        ELootLockerPlatform::Discord,
        ELootLockerPlatform::GooglePlayGames,
        ELootLockerPlatform::Remote
    };
    
    // Check if platform supports refresh via tokens
    if (RefreshSupportedPlatforms.Contains(Platform) && !PlayerData.RefreshToken.IsEmpty())
    {
        return true;
    }
    
    // Guest and WhiteLabel can be refreshed using stored auth data
    if ((Platform == ELootLockerPlatform::Guest && !PlayerData.PlayerIdentifier.IsEmpty()) || 
        (Platform == ELootLockerPlatform::WhiteLabel && 
         !PlayerData.WhiteLabelEmail.IsEmpty() && 
         !PlayerData.WhiteLabelToken.IsEmpty()))
    {
        return true;
    }
    
    return false;
}

void ULootLockerHttpClient::RefreshSessionForPlatform(const FLootLockerPlayerData& PlayerData, TFunction<void(bool)> OnRefreshCompleted)
{
    ELootLockerPlatform Platform = PlayerData.CurrentPlatform.Platform;
    
    switch (Platform)
    {
        case ELootLockerPlatform::Guest:
        {
            ULootLockerSDKManager::GuestLogin(
                FLootLockerSessionResponse::CreateLambda([OnRefreshCompleted](const FLootLockerAuthenticationResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.PlayerIdentifier,
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::WhiteLabel:
        {
            ULootLockerSDKManager::WhiteLabelStartSessionManual(
                PlayerData.WhiteLabelEmail, 
                PlayerData.WhiteLabelToken,
                FLootLockerSessionResponse::CreateLambda([OnRefreshCompleted](const FLootLockerAuthenticationResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::Google:
        {
            ULootLockerSDKManager::RefreshGoogleSession(
                PlayerData.RefreshToken,
                FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerGoogleSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::GooglePlayGames:
        {
            ULootLockerSDKManager::RefreshGooglePlayGamesSession(
                PlayerData.RefreshToken,
                FLootLockerGooglePlayGamesSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerGooglePlayGamesSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::Epic:
        {
            ULootLockerSDKManager::RefreshEpicSession(
                PlayerData.RefreshToken,
                FLootLockerEpicSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerEpicSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::AppleSignIn:
        {
            ULootLockerSDKManager::RefreshAppleSession(
                PlayerData.RefreshToken,
                FLootLockerAppleSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerAppleSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::AppleGameCenter:
        {
            ULootLockerSDKManager::RefreshAppleGameCenterSession(
                PlayerData.RefreshToken,
                FLootLockerAppleGameCenterSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerAppleGameCenterSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::Meta:
        {
            ULootLockerSDKManager::RefreshMetaSession(
                PlayerData.RefreshToken,
                FLootLockerMetaSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerMetaSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::Discord:
        {
            ULootLockerSDKManager::RefreshDiscordSession(
                PlayerData.RefreshToken,
                FLootLockerDiscordSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerDiscordSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                }),
                PlayerData.SessionOptionals
            );
            break;
        }
        case ELootLockerPlatform::Remote:
        {
            ULootLockerSDKManager::RefreshRemoteSession(
                PlayerData.RefreshToken,
                FLootLockerRefreshRemoteSessionResponseDelegate::CreateLambda([OnRefreshCompleted](const FLootLockerRefreshRemoteSessionResponse& Response) {
                    OnRefreshCompleted(Response.success);
                })
            );
            break;
        }
        default:
        {
            FLootLockerLogger::LogWarning(FString::Printf(TEXT("Token refresh not supported for platform: %s"), 
                *PlayerData.CurrentPlatform.GetFriendlyPlatformString()));
            OnRefreshCompleted(false);
            break;
        }
    }
}

void ULootLockerHttpClient::RetryOriginalRequest(const FLootLockerRetryRequestData& RetryData)
{
    // Get the updated player data after refresh    
    FLootLockerPlayerData UpdatedPlayerData = ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(RetryData.PlayerData.PlayerUlid);
    
    if (RetryData.bIsFileUpload)
    {
        UploadFile(RetryData.EndPoint, RetryData.RequestType, RetryData.FilePath, RetryData.AdditionalFields, 
                  RetryData.OnCompleteRequest, UpdatedPlayerData, RetryData.CustomHeaders, true);
    }
    else
    {
        SendApi(RetryData.EndPoint, RetryData.RequestType, RetryData.Data, 
               RetryData.OnCompleteRequest, UpdatedPlayerData, RetryData.CustomHeaders, true);
    }
}
