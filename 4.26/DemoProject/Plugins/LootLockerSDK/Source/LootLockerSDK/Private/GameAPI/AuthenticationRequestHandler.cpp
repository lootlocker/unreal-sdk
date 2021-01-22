// Copyright (c) 2021 LootLocker

#include "GameAPI/AuthenticationRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPersitentDataHolder.h"

UHttpClient* UAuthenticationRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
UAuthenticationRequestHandler::UAuthenticationRequestHandler()
{
	HttpClient = NewObject<UHttpClient>();
}


void UAuthenticationRequestHandler::StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerPersitentDataHolder::CachedPlayerIdentifier = PlayerId;
	FAuthenticationRequest authRequest;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	authRequest.development_mode = ULootLockerConfig::OnDevelopmentMode;
	authRequest.game_key = ULootLockerConfig::LootLockerGameKey;
	authRequest.game_version = ULootLockerConfig::GameVersion;
	authRequest.player_identifier = PlayerId;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(ULootLockerConfig::Platform));
	authRequest.platform = platform;
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FAuthenticationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, config](FLootLockerResponse response)
		{
			FAuthenticationResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FAuthenticationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ULootLockerPersitentDataHolder::Token = ResponseStruct.session_token;
				config->SaveConfig();
				ResponseStruct.success = true;
			}
			else
			{
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Starting of Session failed"));
			}

			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::StartSessionEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, sessionResponse);
}

void UAuthenticationRequestHandler::VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP , const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest )
{
	FVerificationRequest authRequest;
	authRequest.token = SteamToken;
	authRequest.key = ULootLockerConfig::LootLockerGameKey;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(ULootLockerConfig::Platform));
	authRequest.platform = platform;
	ULootLockerPersitentDataHolder::CachedSteamToken = SteamToken;
	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FVerificationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	FResponseCallback verifyResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FAuthenticationDefaultResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FAuthenticationDefaultResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Verification failed"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::VerifyPlayerIdEndPoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, verifyResponse);
}

void UAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	FString AuthContentString = TEXT("");

	FResponseCallback endSessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FAuthenticationDefaultResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FAuthenticationDefaultResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Session ending failed"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::EndSessionEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, AuthContentString, endSessionResponse);
}

