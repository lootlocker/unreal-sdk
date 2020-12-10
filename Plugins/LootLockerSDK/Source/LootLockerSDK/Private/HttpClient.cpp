// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpClient.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "AuthenticationRequestHandler.h"


UHttpClient::UHttpClient()
{

}

void UHttpClient::SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const bool& useHeader)
{
	FHttpModule* HttpModule = &FHttpModule::Get();
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
	FString Endpoint = FPaths::Combine(config->ApiBaseUrl, endPoint);

	UE_LOG(LogTemp, Warning, TEXT("Full url is: %s"), *Endpoint);
	UE_LOG(LogTemp, Warning, TEXT("Data is: %s"), *data);
	Request->SetURL(Endpoint);

	ULootLockerPersitentDataHolder::CachedLastEndpointUsed = endPoint;
	ULootLockerPersitentDataHolder::CachedLastRequestTypeUsed = requestType;
	ULootLockerPersitentDataHolder::CachedLastDataSentToServer = data;
	savedOnCompleteRequest = onCompleteRequest;
	config->SaveConfig();

	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	if (useHeader)
	{
		Request->SetHeader(TEXT("x-session-token"), ULootLockerPersitentDataHolder::Token);
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

	FString Endpoint = FPaths::Combine(config->ApiBaseUrl, config->StartSessionEndpoint.endpoint);

	UE_LOG(LogTemp, Warning, TEXT("refresh Full url is: %s"), *Endpoint);

	Request->SetURL(Endpoint);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->StartSessionEndpoint.requestMethod));
	Request->SetVerb(requestMethod);
	FAuthenticationRequest authRequest;
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_key = config->LootLockerGameKey;
	authRequest.game_version = config->GameVersion;

	authRequest.player_identifier = config->PlayerIdentifier;
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

	FString Endpoint = FPaths::Combine(config->ApiBaseUrl, config->VerifyPlayerIdEndPoint.endpoint);
	Request->SetURL(Endpoint);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->StartSessionEndpoint.requestMethod));
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

void UHttpClient::UploadFile(const FString& endPoint, const FString& requestType, const FString& Boundary, const TArray<uint8>& data, const FResponseCallback& onCompleteRequest, const bool& useHeader)
{
    FHttpModule* HttpModule = &FHttpModule::Get();
    ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
    TSharedRef<IHttpRequest> Request = HttpModule->CreateRequest();
    FString Endpoint = FPaths::Combine(config->ApiBaseUrl, endPoint);

    UE_LOG(LogTemp, Warning, TEXT("Full url is: %s"), *Endpoint);
    Request->SetURL(Endpoint);

    ULootLockerPersitentDataHolder::CachedLastEndpointUsed = endPoint;
    ULootLockerPersitentDataHolder::CachedLastRequestTypeUsed = requestType;
    savedOnCompleteRequest = onCompleteRequest;
    config->SaveConfig();

    Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary =" + Boundary));

    if (useHeader)
    {
        Request->SetHeader(TEXT("x-session-token"), ULootLockerPersitentDataHolder::Token);
    }
    
    Request->SetVerb(requestType);
    Request->SetContent(data);

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
