// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPersistentDataHolder.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAuthenticationRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerAuthenticationRequestHandler::ULootLockerAuthenticationRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegateBP &OnCompletedRequestBP,
	const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
	FLootLockerLoginRequest SignupRequest;
	SignupRequest.email = Email;
	SignupRequest.password = Password;

	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerPersistentDataHolder::DomainKey = Config->DomainKey;
	
	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest, true, true);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegateBP &OnCompletedRequestBP,
	const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
	FLootLockerLoginRequest LoginRequest;
	LoginRequest.email = Email;
	LoginRequest.password = Password;
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerPersistentDataHolder::DomainKey = Config->DomainKey;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, LoginRequest, ULootLockerGameEndpoints::WhiteLabelLoginEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest, true, true);
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& playerIdentifier, const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	FLootLockerAuthenticationRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = playerIdentifier;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(const FString &Email, const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	FLootLockerWhiteLabelAuthRequest AuthRequest;
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = Config->OnDevelopmentMode;
	AuthRequest.game_key = Config->LootLockerGameKey;
	AuthRequest.game_version = Config->GameVersion;
	AuthRequest.email = Email;
	AuthRequest.token = ULootLockerPersistentDataHolder::Token;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerPersistentDataHolder::CachedPlayerIdentifier = PlayerId;
	FLootLockerAuthenticationRequest AuthRequest;

	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = PlayerId;

	FString Platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	AuthRequest.platform = Platform;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest )
{
	FLootLockerVerificationRequest AuthRequest;
	AuthRequest.token = SteamToken;

	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	AuthRequest.key = Config->LootLockerGameKey;

	FString Platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(Config->Platform));
	AuthRequest.platform = Platform;

	ULootLockerPersistentDataHolder::CachedSteamToken = SteamToken;

	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

