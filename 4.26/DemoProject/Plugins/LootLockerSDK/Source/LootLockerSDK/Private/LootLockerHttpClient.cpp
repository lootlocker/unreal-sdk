// Copyright (c) 2021 LootLocker


#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerSDK.h"
#include "LootLockerPersitentDataHolder.h"
#include "Misc/FileHelper.h"

ULootLockerHttpClient::ULootLockerHttpClient()
{

}

void ULootLockerHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, bool useHeader, bool useAdmin)
{
	FHttpModule* HttpModule = &FHttpModule::Get();
#if ENGINE_MINOR_VERSION < 26
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif
	Request->SetURL(endPoint);

	ULootLockerPersitentDataHolder::CachedLastEndpointUsed = endPoint;
	ULootLockerPersitentDataHolder::CachedLastRequestTypeUsed = requestType;
	ULootLockerPersitentDataHolder::CachedLastDataSentToServer = data;
	savedOnCompleteRequest = onCompleteRequest;

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	if (useHeader)
	{
        if (!useAdmin) {
            Request->SetHeader(TEXT("x-session-token"), ULootLockerPersitentDataHolder::Token);
        } else {
            Request->SetHeader(TEXT("x-auth-token"), ULootLockerPersitentDataHolder::AdminToken);
        }
	}
    
	Request->SetVerb(requestType);
    Request->SetContentAsString(data);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerResponse response;

			if (!ResponseIsValid(Response, bWasSuccessful))
			{
				response.success = false;
				response.FullTextFromServer = Response->GetContentAsString();
				response.ServerCallHasError = true;
				response.ServerCallStatusCode = Response->GetResponseCode();
				response.ServerError = Response->GetContentAsString();
				onCompleteRequest.ExecuteIfBound(response);
				return;
			}

			UE_LOG(LogTemp, Warning, TEXT("Response code: %d; Response content:\n%s"), Response->GetResponseCode(), *ResponseString);
			response.success = true;
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallHasError = false;
			response.ServerCallStatusCode = Response->GetResponseCode();
			response.ServerError = Response->GetContentAsString();
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();
}

void ULootLockerHttpClient::TokenRefresh(const FResponseCallback onCompleteRequest)
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MINOR_VERSION < 26
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif

    
	
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::StartSessionEndpoint;
	FString Endpoint = endpoint.endpoint;

	UE_LOG(LogTemp, Warning, TEXT("refresh Full url is: %s"), *Endpoint);

	Request->SetURL(Endpoint);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	Request->SetVerb(requestMethod);
	FLootLockerAuthenticationRequest authRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_key = config->LootLockerGameKey;
	authRequest.game_version = config->GameVersion;

	authRequest.player_identifier = ULootLockerPersitentDataHolder::CachedPlayerIdentifier;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));

	authRequest.platform = platform;

	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	Request->SetContentAsString(AuthContentString);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest,  this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerResponse response;

			if (!ResponseIsValid(Response, bWasSuccessful))
			{
				response.success = false;
				response.FullTextFromServer = Response->GetContentAsString();
				response.ServerCallHasError = true;
				response.ServerCallStatusCode = Response->GetResponseCode();
				response.ServerError = Response->GetContentAsString();
				onCompleteRequest.ExecuteIfBound(response);
				return;
			}
			FLootLockerAuthenticationResponse ResponseStruct;
			FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAuthenticationResponse>(ResponseString, &ResponseStruct, 0, 0);
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallHasError = false;
			response.ServerCallStatusCode = Response->GetResponseCode();
			response.ServerError = Response->GetContentAsString();
			response.success = true;
			ULootLockerPersitentDataHolder::Token = ResponseStruct.session_token;
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();

}

void ULootLockerHttpClient::VerifyRefresh(const FResponseCallback onCompleteRequest)
{
	FHttpModule* HttpModule = &FHttpModule::Get();

#if ENGINE_MINOR_VERSION < 26
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif

    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::VerifyPlayerIdEndPoint;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FString Endpoint = endpoint.endpoint;
	Request->SetURL(Endpoint);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	Request->SetVerb(requestMethod);
	FLootLockerVerificationRequest authRequest;
	authRequest.key = config->LootLockerGameKey;

	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));

	authRequest.platform = platform;

	authRequest.token = ULootLockerPersitentDataHolder::CachedSteamToken;

	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	Request->SetContentAsString(AuthContentString);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			const FString ResponseString = Response->GetContentAsString();
			FLootLockerResponse response;

			if (!ResponseIsValid(Response, bWasSuccessful))
			{
				response.success = false;
				response.FullTextFromServer = Response->GetContentAsString();
				response.ServerCallHasError = true;
				response.ServerCallStatusCode = Response->GetResponseCode();
				response.ServerError = Response->GetContentAsString();
				onCompleteRequest.ExecuteIfBound(response);
				return;
			}
			FLootLockerAuthenticationResponse ResponseStruct;
			FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAuthenticationResponse>(ResponseString, &ResponseStruct, 0, 0);
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallHasError = false;
			response.ServerCallStatusCode = Response->GetResponseCode();
			response.ServerError = Response->GetContentAsString();
			response.success = true;
			ULootLockerPersitentDataHolder::Token = ResponseStruct.session_token;
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();

}

bool ULootLockerHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode()))
	{
		return true;
	}
	else
	{
		const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
		if (!config->AllowTokenRefresh)
		{
			return false;
		}
		if (InResponse->GetResponseCode() == 401)
		{
			UE_LOG(LogTemp, Warning, TEXT("Call failed, trying to get a new token"));
	
			if (config->Platform != ELootLockerPlatformType::Steam)
			{
				refreshCompleteRequest = FResponseCallback::CreateLambda([this](FLootLockerResponse response)
					{
						if (response.success)
						{
							SendApi(ULootLockerPersitentDataHolder::CachedLastEndpointUsed, ULootLockerPersitentDataHolder::CachedLastRequestTypeUsed, ULootLockerPersitentDataHolder::CachedLastDataSentToServer, savedOnCompleteRequest, true);
						}
						else {
							UE_LOG(LogTemp, Warning, TEXT("Token refresh failed"));
							FLootLockerResponse resultResponse;
							resultResponse.success = false;
							resultResponse.FullTextFromServer = TEXT("Token has expired and refresh failed");
							resultResponse.ServerCallHasError = true;
							resultResponse.ServerCallStatusCode = 401;
							resultResponse.ServerError = TEXT("Token has expired and refresh failed");
							savedOnCompleteRequest.ExecuteIfBound(resultResponse);
						}
					});

				TokenRefresh(refreshCompleteRequest);
			}
			else
			{
				verifyRefreshCompleteRequest = FResponseCallback::CreateLambda([this](FLootLockerResponse VerifyResponse)
					{
						if (VerifyResponse.success)
						{
							//On succesfful token refresh
							refreshCompleteRequest = FResponseCallback::CreateLambda([this](FLootLockerResponse RefreshResponse)
								{
									if (RefreshResponse.success)
									{
										SendApi(ULootLockerPersitentDataHolder::CachedLastEndpointUsed, ULootLockerPersitentDataHolder::CachedLastRequestTypeUsed, ULootLockerPersitentDataHolder::CachedLastDataSentToServer, savedOnCompleteRequest, true);
									}
									else {
										FLootLockerResponse resultResponse;
										resultResponse.success = false;
										resultResponse.FullTextFromServer = TEXT("Token has expired and refresh failed");
										resultResponse.ServerCallHasError = true;
										resultResponse.ServerCallStatusCode = 401;
										resultResponse.ServerError = TEXT("Token has expired and refresh failed");
										savedOnCompleteRequest.ExecuteIfBound(resultResponse);
									}
								});

							TokenRefresh(refreshCompleteRequest);
						}
						else {
							FLootLockerResponse resultResponse;
							resultResponse.success = false;
							resultResponse.FullTextFromServer = TEXT("Token has expired and refresh failed");
							resultResponse.ServerCallHasError = true;
							resultResponse.ServerCallStatusCode = 401;
							resultResponse.ServerError = TEXT("Token has expired and refresh failed");
							savedOnCompleteRequest.ExecuteIfBound(resultResponse);
						}
					});

				VerifyRefresh(verifyRefreshCompleteRequest);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Token failed with non token error"));
			return false;
		}
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), InResponse->GetResponseCode());
		UE_LOG(LogTemp, Warning, TEXT("Http Response content:\n%s"), *InResponse->GetContentAsString());
		return false;
	}
}

void ULootLockerHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FResponseCallback& onCompleteRequest, bool useHeader, bool useAdmin)
{
    FHttpModule* HttpModule = &FHttpModule::Get();
#if ENGINE_MINOR_VERSION < 26
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
#else
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule->CreateRequest();
#endif

    Request->SetURL(endPoint);

    ULootLockerPersitentDataHolder::CachedLastEndpointUsed = endPoint;
    ULootLockerPersitentDataHolder::CachedLastRequestTypeUsed = requestType;
    savedOnCompleteRequest = onCompleteRequest;
    
    FString Boundary = "lootlockerboundary";

    Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=" + Boundary));

    if (useHeader)
    {
        if (!useAdmin) {
            Request->SetHeader(TEXT("x-session-token"), ULootLockerPersitentDataHolder::Token);
        } else {
            Request->SetHeader(TEXT("x-auth-token"), ULootLockerPersitentDataHolder::AdminToken);
        }
    }
    
    Request->SetVerb(requestType);
    
    TArray<uint8> UpFileRawData;
    if (!FFileHelper::LoadFileToArray(UpFileRawData, *FilePath)) {
        UE_LOG(LogTemp, Error, TEXT("FILE NOT READ!"));
        return;
    }
    
    TArray<uint8> Data;
    
    const FString BeginBoundary = TEXT("\r\n--" + Boundary + "\r\n");
    const FString EndBoundary = TEXT("\r\n--" + Boundary + "--\r\n");
    
    for (auto KeyValuePair : AdditionalFields) {
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
    
    int32 LastSlashPos;
    FilePath.FindLastChar('/', LastSlashPos);
    FString FileName = FilePath.RightChop(LastSlashPos + 1);
    
    FileHeader.Append(FileName + "\"\r\n\r\n");
    
    Data.Append((uint8*)TCHAR_TO_ANSI(*FileHeader), FileHeader.Len());
    Data.Append(UpFileRawData);
    Data.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());
    
    Request->SetContent(Data);

    Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            const FString ResponseString = Response->GetContentAsString();
            FLootLockerResponse response;
        
            response.FullTextFromServer = Response->GetContentAsString();
            response.ServerCallStatusCode = Response->GetResponseCode();
            response.ServerError = Response->GetContentAsString();
        
            UE_LOG(LogTemp, Warning, TEXT("Response code: %d; Response content:\n%s"), Response->GetResponseCode(), *ResponseString);
            bool success = ResponseIsValid(Response, bWasSuccessful);
        
            response.success = success;
            response.ServerCallHasError = !success;
        
            onCompleteRequest.ExecuteIfBound(response);
        });
    Request->ProcessRequest();
}
