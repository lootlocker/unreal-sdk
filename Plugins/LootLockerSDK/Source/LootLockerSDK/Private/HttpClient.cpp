// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpClient.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "AuthenticationRequestHandler.h"
#include "LootLockerSDK.h"
#include "LootLockerPersitentDataHolder.h"

UHttpClient::UHttpClient()
{

}

void UHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const bool& useHeader, bool useAdmin)
{
	FHttpModule* HttpModule = &FHttpModule::Get();
    ULootLockerConfig* config = FLootLockerSDKModule::Get().GetSettings();
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();

	UE_LOG(LogTemp, Warning, TEXT("Full url is: %s"), *endPoint);
	UE_LOG(LogTemp, Warning, TEXT("Data is: %s"), *data);
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

void UHttpClient::TokenRefresh(const FResponseCallback onCompleteRequest)
{
	FHttpModule* HttpModule = &FHttpModule::Get();

	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();

    FEndPoints endpoint = LootLockerGameEndpoints::StartSessionEndpoint;
	FString Endpoint = endpoint.endpoint;

	UE_LOG(LogTemp, Warning, TEXT("refresh Full url is: %s"), *Endpoint);

	Request->SetURL(Endpoint);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	Request->SetVerb(requestMethod);
	FAuthenticationRequest authRequest;
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_key = config->LootLockerGameKey;
	authRequest.game_version = config->GameVersion;

	authRequest.player_identifier = ULootLockerPersitentDataHolder::CachedPlayerIdentifier;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));

	authRequest.platform = platform;

	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	Request->SetContentAsString(AuthContentString);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, config, this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
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
			FAuthenticationResponse ResponseStruct;
			FJsonObjectConverter::JsonObjectStringToUStruct<FAuthenticationResponse>(ResponseString, &ResponseStruct, 0, 0);
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallHasError = false;
			response.ServerCallStatusCode = Response->GetResponseCode();
			response.ServerError = Response->GetContentAsString();
			response.success = true;
			ULootLockerPersitentDataHolder::Token = ResponseStruct.session_token;
			config->SaveConfig();
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();

}

void UHttpClient::VerifyRefresh(const FResponseCallback onCompleteRequest)
{
	FHttpModule* HttpModule = &FHttpModule::Get();

	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();

    FEndPoints endpoint = LootLockerGameEndpoints::VerifyPlayerIdEndPoint;
	FString Endpoint = endpoint.endpoint;
	Request->SetURL(Endpoint);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	Request->SetVerb(requestMethod);
	FVerificationRequest authRequest;
	authRequest.key = config->LootLockerGameKey;

	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));

	authRequest.platform = platform;

	authRequest.token = ULootLockerPersitentDataHolder::CachedSteamToken;

	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	Request->SetContentAsString(AuthContentString);

	Request->OnProcessRequestComplete().BindLambda([onCompleteRequest, config, this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
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
			FAuthenticationResponse ResponseStruct;
			FJsonObjectConverter::JsonObjectStringToUStruct<FAuthenticationResponse>(ResponseString, &ResponseStruct, 0, 0);
			response.FullTextFromServer = Response->GetContentAsString();
			response.ServerCallHasError = false;
			response.ServerCallStatusCode = Response->GetResponseCode();
			response.ServerError = Response->GetContentAsString();
			response.success = true;
			ULootLockerPersitentDataHolder::Token = ResponseStruct.session_token;
			config->SaveConfig();
			onCompleteRequest.ExecuteIfBound(response);
		});
	Request->ProcessRequest();

}

bool UHttpClient::ResponseIsValid(const FHttpResponsePtr& InResponse, const bool& bWasSuccessful)
{
	if (!bWasSuccessful || !InResponse.IsValid())
		return false;

	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode()))
	{
		return true;
	}
	else
	{
		ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

		if (!config->AllowTokenRefresh)
		{
			return false;
		}
		if (InResponse->GetResponseCode() == 401)
		{
			UE_LOG(LogTemp, Warning, TEXT("Call failed, trying to get a new token"));
	
			if (config->Platform != ELootLockerPlatformType::Steam)
			{
				refreshCompleteRequest = FResponseCallback::CreateLambda([this, config](FLootLockerResponse response)
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
				verifyRefreshCompleteRequest = FResponseCallback::CreateLambda([this, config](FLootLockerResponse response)
					{
						if (response.success)
						{
							//On succesfful token refresh
							refreshCompleteRequest = FResponseCallback::CreateLambda([this, config](FLootLockerResponse response)
								{
									if (response.success)
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

void UHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FResponseCallback& onCompleteRequest, bool useHeader, bool useAdmin)
{
    FHttpModule* HttpModule = &FHttpModule::Get();
    TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();

    UE_LOG(LogTemp, Warning, TEXT("Full url is: %s"), *endPoint);
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
