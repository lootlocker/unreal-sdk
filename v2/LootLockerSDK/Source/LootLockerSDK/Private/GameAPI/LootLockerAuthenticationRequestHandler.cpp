// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPersistentDataHolder.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAuthenticationRequestHandler::HttpClient = nullptr;
const FString WHITE_LABEL_PLATFORM = FString(TEXT("white_label_login"));
const FString GUEST_PLATFORM = FString(TEXT("guest"));
// Sets default values for this component's properties
ULootLockerAuthenticationRequestHandler::ULootLockerAuthenticationRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegateBP &OnCompletedRequestBP,
	const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerPersistentDataHolder::DomainKey = Config->DomainKey;
	ULootLockerPersistentDataHolder::CachedWhiteLabelEmail = Email;
	FLootLockerLoginRequest SignupRequest;
	SignupRequest.email = ULootLockerPersistentDataHolder::CachedWhiteLabelEmail;
	SignupRequest.password = Password;
	
	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest, true, true);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(const FString &Email, const FString &Password, const bool Remember, const FLootLockerLoginResponseDelegateBP &OnCompletedRequestBP,
	const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerPersistentDataHolder::DomainKey = Config->DomainKey;
	ULootLockerPersistentDataHolder::CachedWhiteLabelEmail = Email;
	FLootLockerWhiteLabelLoginRequest LoginRequest;
	LoginRequest.email = ULootLockerPersistentDataHolder::CachedWhiteLabelEmail;
	LoginRequest.password = Password;
	LoginRequest.remember = Remember;

	auto CacheWhiteLabelTokenLambda = FLootLockerLoginResponseDelegate::CreateLambda([OnCompletedRequest, OnCompletedRequestBP](FLootLockerLoginResponse Response)
	{
		if (Response.success) {
			ULootLockerPersistentDataHolder::CachedWhiteLabelToken = Response.session_token;
			LootLockerUtilities::CurrentPlatformFString::Override(WHITE_LABEL_PLATFORM);
		}
		OnCompletedRequestBP.ExecuteIfBound(Response);
		OnCompletedRequest.ExecuteIfBound(Response);
	});

	const FLootLockerLoginResponseDelegateBP EmptyPlaceholderResponseDelegateBP;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, LoginRequest, ULootLockerGameEndpoints::WhiteLabelLoginEndpoint, { },EmptyQueryParams, EmptyPlaceholderResponseDelegateBP, CacheWhiteLabelTokenLambda, true, true);
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& playerIdentifier, const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	FLootLockerAuthenticationRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = playerIdentifier;
	LootLockerUtilities::CurrentPlatformFString::Override(GUEST_PLATFORM);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerPersistentDataHolder::DomainKey = Config->DomainKey;
	FLootLockerWhiteLabelAuthRequest AuthRequest;
	AuthRequest.development_mode = Config->OnDevelopmentMode;
	AuthRequest.game_key = Config->LootLockerGameKey;
	AuthRequest.game_version = Config->GameVersion;
	AuthRequest.email = ULootLockerPersistentDataHolder::CachedWhiteLabelEmail;
	AuthRequest.token = ULootLockerPersistentDataHolder::CachedWhiteLabelToken;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(const FLootLockerVerifySessionResponseBP& OnCompletedRequestBP, const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelVerifySessionRequest VerifyRequest;
	VerifyRequest.email = ULootLockerPersistentDataHolder::CachedWhiteLabelEmail;;
	VerifyRequest.token = ULootLockerPersistentDataHolder::CachedWhiteLabelToken;
	LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::CallAPI(HttpClient, VerifyRequest, ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest, true, true);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerUserIdRequest UserIdRequest;
	UserIdRequest.user_id = UserId;
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, UserIdRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest, true, true);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelResetPasswordRequest ResetPasswordRequest;
	ResetPasswordRequest.email = Email;
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, ResetPasswordRequest, ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest, true, true);
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

	LootLockerUtilities::CurrentPlatformFString::Reset();
	FString Platform = LootLockerUtilities::CurrentPlatformFString::Get();
	AuthRequest.platform = Platform;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	FLootLockerNintendoSwitchSessionRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.nsa_id_token = NSAIdToken;

	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	FLootLockerXboxSessionRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.xbox_user_token = XboxUserToken;

	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartXboxSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FString& PlatformToken, const FString& Platform, const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	FLootLockerVerificationRequest AuthRequest;
	AuthRequest.token = PlatformToken;

	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	AuthRequest.key = Config->LootLockerGameKey;

	FString RequestPlatform = Platform.IsEmpty() ? LootLockerUtilities::CurrentPlatformFString::Get() : Platform;
	AuthRequest.platform = RequestPlatform;

	if(RequestPlatform.Compare(ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(ELootLockerPlatformType::Steam))))
	{
		ULootLockerPersistentDataHolder::CachedSteamToken = PlatformToken;
	}

	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	ULootLockerPersistentDataHolder::CachedWhiteLabelEmail = "";
	ULootLockerPersistentDataHolder::CachedWhiteLabelToken = "";
	ULootLockerPersistentDataHolder::Token = "";

	LootLockerUtilities::CurrentPlatformFString::Reset();
	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

