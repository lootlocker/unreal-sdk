// Fill out your copyright notice in the Description page of Project Settings.

#include "AuthenticationRequestHandler.h"

UHttpClient* UAuthenticationRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
UAuthenticationRequestHandler::UAuthenticationRequestHandler()
{
	HttpClient = NewObject<UHttpClient>();
}


void UAuthenticationRequestHandler::StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	FAuthenticationRequest authRequest;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	config->PlayerIdentifier = PlayerId;
	authRequest.development_mode = config->OnDevelopmentMode;
	authRequest.game_key = config->LootLockerGameKey;
	authRequest.game_version = config->GameVersion;
	authRequest.player_identifier = config->PlayerIdentifier;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	authRequest.platform = platform;
	FString AuthContentString;
	config->SaveConfig();
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->StartSessionEndpoint.requestMethod));
	HttpClient->SendApi(config->StartSessionEndpoint.endpoint, requestMethod, AuthContentString, sessionResponse);
}

void UAuthenticationRequestHandler::VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP , const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest )
{
	FVerificationRequest authRequest;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	authRequest.token = SteamToken;
	authRequest.key = config->LootLockerGameKey;
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	authRequest.platform = platform;
	ULootLockerPersitentDataHolder::CachedSteamToken = SteamToken;
	config->SaveConfig();
	FString AuthContentString;

	FJsonObjectConverter::UStructToJsonObjectString(FVerificationRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);

	FResponseCallback verifyResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, config](FLootLockerResponse response)
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->VerifyPlayerIdEndPoint.requestMethod));
	HttpClient->SendApi(config->VerifyPlayerIdEndPoint.endpoint, requestMethod, AuthContentString, verifyResponse);
}

void UAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	FString AuthContentString = TEXT("");
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	FResponseCallback endSessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, config](FLootLockerResponse response)
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->EndSessionEndpoint.requestMethod));
	HttpClient->SendApi(config->EndSessionEndpoint.endpoint, requestMethod, AuthContentString, endSessionResponse);
}

