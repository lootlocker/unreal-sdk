// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
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

void ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegateBP &OnCompletedRequestBP, const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerStateData::SetDomainKey(Config->DomainKey);
	FLootLockerLoginRequest SignupRequest;
	SignupRequest.email = Email;
	SignupRequest.password = Password;

	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetWhiteLabelToken());
	CustomHeaders.Add(TEXT("is-development"), GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	
	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
    {
        ULootLockerStateData::SetWhiteLabelEmail(Email);
    }), CustomHeaders);
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& PlayerIdentifier, const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	FLootLockerAuthenticationRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = !(PlayerIdentifier.IsEmpty()) ? PlayerIdentifier : ULootLockerStateData::GetPlayerIdentifier();
	LootLockerUtilities::CurrentPlatformFString::Override(GUEST_PLATFORM);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if(Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(const FString& Email, const FString& Password, const bool Remember, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP, const FLootLockerLoginResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerStateData::SetDomainKey(Config->DomainKey);
	FLootLockerWhiteLabelLoginRequest LoginRequest;
	LoginRequest.email = Email;
	LoginRequest.password = Password;
	LoginRequest.remember = Remember;

	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetWhiteLabelToken());
	CustomHeaders.Add(TEXT("is-development"), GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, LoginRequest, ULootLockerGameEndpoints::WhiteLabelLoginEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
    {
        if (Response.success) {
            ULootLockerStateData::SetWhiteLabelEmail(Email);
            ULootLockerStateData::SetWhiteLabelToken(Response.session_token);
            LootLockerUtilities::CurrentPlatformFString::Override(WHITE_LABEL_PLATFORM);
        }
    }), CustomHeaders);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	ULootLockerStateData::SetDomainKey(Config->DomainKey);
	FLootLockerWhiteLabelAuthRequest AuthRequest;
	AuthRequest.development_mode = Config->OnDevelopmentMode;
	AuthRequest.game_key = Config->LootLockerGameKey;
	AuthRequest.game_version = Config->GameVersion;
	AuthRequest.email = ULootLockerStateData::GetWhiteLabelEmail();
	AuthRequest.token = ULootLockerStateData::GetWhiteLabelToken();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if(Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, bool bRemember, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& LootLockerWhiteLabelLoginAndSessionResponseDelegateBP, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& LootLockerWhiteLabelLoginAndSessionResponseDelegate)
{
	WhiteLabelLogin(Email, Password, bRemember, FLootLockerLoginResponseDelegateBP(), FLootLockerLoginResponseDelegate::CreateLambda([LootLockerWhiteLabelLoginAndSessionResponseDelegateBP, LootLockerWhiteLabelLoginAndSessionResponseDelegate](FLootLockerLoginResponse LoginResponse)
	{
		if(!LoginResponse.success)
		{
			const FLootLockerWhiteLabelLoginAndSessionResponse FullResponse = FLootLockerWhiteLabelLoginAndSessionResponse(LoginResponse);
			LootLockerWhiteLabelLoginAndSessionResponseDelegateBP.ExecuteIfBound(FullResponse);
			LootLockerWhiteLabelLoginAndSessionResponseDelegate.ExecuteIfBound(FullResponse);
			return;
		}

    	WhiteLabelStartSession(FAuthResponseBP(), FLootLockerSessionResponse::CreateLambda([LootLockerWhiteLabelLoginAndSessionResponseDelegateBP, LootLockerWhiteLabelLoginAndSessionResponseDelegate, LoginResponse](FLootLockerAuthenticationResponse StartSessionResponse)
		{
			const FLootLockerWhiteLabelLoginAndSessionResponse FullResponse = FLootLockerWhiteLabelLoginAndSessionResponse(LoginResponse);
		    LootLockerWhiteLabelLoginAndSessionResponseDelegateBP.ExecuteIfBound(FullResponse);
		    LootLockerWhiteLabelLoginAndSessionResponseDelegate.ExecuteIfBound(FullResponse);
		}));
	}));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(const FLootLockerVerifySessionResponseBP& OnCompletedRequestBP, const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelVerifySessionRequest VerifyRequest;
	VerifyRequest.email = ULootLockerStateData::GetWhiteLabelEmail();
	VerifyRequest.token = ULootLockerStateData::GetWhiteLabelToken();

	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetWhiteLabelToken());
	CustomHeaders.Add(TEXT("is-development"), GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::CallAPI(HttpClient, VerifyRequest, ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::FResponseInspectorCallback(), CustomHeaders);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerUserIdRequest UserIdRequest;
	UserIdRequest.user_id = UserId;

	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetWhiteLabelToken());
	CustomHeaders.Add(TEXT("is-development"), GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, UserIdRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), CustomHeaders);
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelResetPasswordRequest ResetPasswordRequest;
	ResetPasswordRequest.email = Email;

	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetWhiteLabelToken());
	CustomHeaders.Add(TEXT("is-development"), GetDefault<ULootLockerConfig>()->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, ResetPasswordRequest, ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), CustomHeaders);
}

void ULootLockerAuthenticationRequestHandler::StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	FLootLockerAuthenticationRequest AuthRequest;

	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = PlayerId;

	LootLockerUtilities::CurrentPlatformFString::Reset();
	FString Platform = LootLockerUtilities::CurrentPlatformFString::Get();
	AuthRequest.platform = Platform;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if (Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	FLootLockerNintendoSwitchSessionRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.nsa_id_token = NSAIdToken;

	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if (Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	FLootLockerXboxSessionRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.xbox_user_token = XboxUserToken;

	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartXboxSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if (Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnCompletedRequestBP, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
	FLootLockerAppleSessionRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.apple_authorization_code = AuthorizationCode;

	LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartAppleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleSessionResponse& Response)
    {
        if (Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::RefreshAppleSession(const FString& RefreshToken, const FAppleSessionResponseBP& OnCompletedRequestBP, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
	FLootLockerRefreshAppleSessionRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.development_mode = config->OnDevelopmentMode;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshAppleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleSessionResponse& Response)
    {
        if (Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FString& PlatformToken, const FString& Platform, const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	FLootLockerVerificationRequest AuthRequest;
	AuthRequest.token = PlatformToken;

	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	AuthRequest.key = Config->LootLockerGameKey;

	FString RequestPlatform = Platform.IsEmpty() ? LootLockerUtilities::CurrentPlatformFString::Get() : Platform;
	AuthRequest.platform = RequestPlatform;

	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationDefaultResponse>::FResponseInspectorCallback::CreateLambda([RequestPlatform, PlatformToken](const FLootLockerAuthenticationDefaultResponse& Response)
    {
        if (Response.success)
        {

            if (RequestPlatform.Compare(ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(ELootLockerPlatformType::Steam))))
            {
                ULootLockerStateData::SetSteamToken(PlatformToken);
            }
        }
    }));
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationDefaultResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationDefaultResponse& Response)
    {
        if (Response.success) {
            ULootLockerStateData::ClearState();
            LootLockerUtilities::CurrentPlatformFString::Reset();
        }
    }));
}
