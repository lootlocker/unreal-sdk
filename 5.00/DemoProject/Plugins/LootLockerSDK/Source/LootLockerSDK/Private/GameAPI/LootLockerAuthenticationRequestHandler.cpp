// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPersitentDataHolder.h"

ULootLockerHttpClient* ULootLockerAuthenticationRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerAuthenticationRequestHandler::ULootLockerAuthenticationRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}


void ULootLockerAuthenticationRequestHandler::StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerPersitentDataHolder::CachedPlayerIdentifier = PlayerId;
	FLootLockerAuthenticationRequest authRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_key = config->LootLockerGameKey;
	authRequest.game_version = config->GameVersion;
	authRequest.player_identifier = PlayerId;
	if (config->Platform != ELootLockerPlatformType::Guest)
	{
		FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
		authRequest.platform = platform;
	}
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	FResponseCallback const SessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, config](FLootLockerResponse response)
		{
			FLootLockerAuthenticationResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAuthenticationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ULootLockerPersitentDataHolder::Token = ResponseStruct.session_token;
				ResponseStruct.success = true;
			}
			else
			{
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Starting of Session failed"));
			}

			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			(void) OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			(void) OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints & Endpoint = ULootLockerGameEndpoints::StartSessionEndpoint;
	if (config->Platform == ELootLockerPlatformType::Guest)
	{
		Endpoint = ULootLockerGameEndpoints::GuestSessionEndpoint;
	}
	FString const RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, RequestMethod, AuthContentString, SessionResponse);
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP , const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest )
{
	FLootLockerVerificationRequest authRequest;
	authRequest.token = SteamToken;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	authRequest.key = config->LootLockerGameKey;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	authRequest.platform = platform;
	ULootLockerPersitentDataHolder::CachedSteamToken = SteamToken;
	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerVerificationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	FResponseCallback verifyResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerAuthenticationDefaultResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAuthenticationDefaultResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Verification failed"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::VerifyPlayerIdEndPoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, verifyResponse);
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	FString AuthContentString = TEXT("");

	FResponseCallback endSessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerAuthenticationDefaultResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAuthenticationDefaultResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Session ending failed"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::EndSessionEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, endSessionResponse);
}

