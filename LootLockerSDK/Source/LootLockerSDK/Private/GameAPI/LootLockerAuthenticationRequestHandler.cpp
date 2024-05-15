// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"

#include "LootLockerConfig.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAuthenticationRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerAuthenticationRequestHandler::ULootLockerAuthenticationRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP, const FLootLockerLoginResponseDelegate& OnCompletedRequest)
{
	FLootLockerLoginRequest SignupRequest;
	SignupRequest.email = Email;
	SignupRequest.password = Password;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
		{
			ULootLockerStateData::SetWhiteLabelEmail(Email);
		}), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& PlayerIdentifier, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = !(PlayerIdentifier.IsEmpty()) ? PlayerIdentifier : ULootLockerStateData::GetPlayerIdentifier();
	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Guest);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(const FString& Email, const FString& Password, const bool Remember, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP, const FLootLockerLoginResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	FLootLockerWhiteLabelLoginRequest LoginRequest;
	LoginRequest.email = Email;
	LoginRequest.password = Password;
	LoginRequest.remember = Remember;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::WhiteLabel);
	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, LoginRequest, ULootLockerGameEndpoints::WhiteLabelLoginEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
		{
			if (Response.success) {
				ULootLockerStateData::SetWhiteLabelEmail(Email);
				ULootLockerStateData::SetWhiteLabelToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	FLootLockerWhiteLabelAuthRequest AuthRequest;
	AuthRequest.game_key = Config->LootLockerGameKey;
	AuthRequest.game_version = Config->GameVersion;
	AuthRequest.email = ULootLockerStateData::GetWhiteLabelEmail();
	AuthRequest.token = ULootLockerStateData::GetWhiteLabelToken();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, bool bRemember, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& LootLockerWhiteLabelLoginAndSessionResponseDelegateBP, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& LootLockerWhiteLabelLoginAndSessionResponseDelegate)
{
	WhiteLabelLogin(Email, Password, bRemember, FLootLockerLoginResponseDelegateBP(), FLootLockerLoginResponseDelegate::CreateLambda([LootLockerWhiteLabelLoginAndSessionResponseDelegateBP, LootLockerWhiteLabelLoginAndSessionResponseDelegate](FLootLockerLoginResponse LoginResponse)
		{
			if (!LoginResponse.success)
			{
				const FLootLockerWhiteLabelLoginAndSessionResponse FullResponse = FLootLockerWhiteLabelLoginAndSessionResponse(LoginResponse);
				LootLockerWhiteLabelLoginAndSessionResponseDelegateBP.ExecuteIfBound(FullResponse);
				LootLockerWhiteLabelLoginAndSessionResponseDelegate.ExecuteIfBound(FullResponse);
				return;
			}

			WhiteLabelStartSession(FAuthResponseBP(), FLootLockerSessionResponse::CreateLambda([LootLockerWhiteLabelLoginAndSessionResponseDelegateBP, LootLockerWhiteLabelLoginAndSessionResponseDelegate, LoginResponse](const FLootLockerAuthenticationResponse& StartSessionResponse)
			{
				const FLootLockerWhiteLabelLoginAndSessionResponse FullResponse = FLootLockerWhiteLabelLoginAndSessionResponse(LoginResponse, StartSessionResponse);
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

	LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::CallAPI(HttpClient, VerifyRequest, ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerUserIdRequest UserIdRequest;
	UserIdRequest.user_id = UserId;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, UserIdRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerEmailRequest EmailRequest;
	EmailRequest.Email = Email;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, EmailRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelResetPasswordRequest ResetPasswordRequest;
	ResetPasswordRequest.email = Email;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, ResetPasswordRequest, ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = PsnOnlineId;


	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::PlayStationNetwork);
	AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = DeviceId;


	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Android);
	AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnCompletedRequestBP, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGoogleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.id_token = IdToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Google);
	LLAPI<FLootLockerGoogleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartGoogleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartGoogleSession(const FString& IdToken, const ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnCompletedRequestBP, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGoogleSessionRequestWithPlatform AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.id_token = IdToken;
	AuthRequest.platform = Platform;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Google);
	LLAPI<FLootLockerGoogleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartGoogleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(const FString& RefreshToken, const FGoogleSessionResponseBP& OnCompletedRequestBP, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshGoogleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Google);
	LLAPI<FLootLockerGoogleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshGoogleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnCompletedRequestBP, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerEpicSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.id_token = IdToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Epic);
	LLAPI<FLootLockerEpicSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartEpicSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerEpicSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerEpicSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshEpicSession(const FString& RefreshToken, const FEpicSessionResponseBP& OnCompletedRequestBP, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	const auto InspectionLambda = LLAPI<FLootLockerEpicSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerEpicSessionResponse& Response)
	{
		if (Response.success)
		{
			ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			ULootLockerStateData::SetToken(Response.session_token);
			ULootLockerStateData::SetRefreshToken(Response.refresh_token);
		}
		else
		{
			ULootLockerCurrentPlatform::Reset();
		}
	});
	FLootLockerRefreshEpicSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken.IsEmpty() ? ULootLockerStateData::GetRefreshToken() : RefreshToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Epic);
	LLAPI<FLootLockerEpicSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshEpicSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, InspectionLambda);
}

void ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = AmazonLunaGuid;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AmazonLuna);
	AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartSteamSession(const FString& SteamId64, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = SteamId64;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Steam);
	AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerNintendoSwitchSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.nsa_id_token = NSAIdToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::NintendoSwitch);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerXboxSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.xbox_user_token = XboxUserToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Xbox);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartXboxSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnCompletedRequestBP, const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();

	FLootLockerAppleGameCenterSessionRequest AuthRequest;

	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.bundle_id = BundleId;
	AuthRequest.player_id = PlayerId;
	AuthRequest.public_key_url = PublicKeyUrl;
	AuthRequest.signature = Signature;
	AuthRequest.salt = Salt;
	AuthRequest.timestamp = Timestamp;


	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AppleGameCenter);
	LLAPI<FLootLockerAppleGameCenterSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartAppleGameCenterSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleGameCenterSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleGameCenterSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
				ULootLockerStateData::SetToken(Response.session_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));


}

void ULootLockerAuthenticationRequestHandler::StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnCompletedRequestBP, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAppleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.apple_authorization_code = AuthorizationCode;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AppleSignIn);
	LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartAppleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}


void ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnCompletedRequestBP, const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();


	FLootLockerRefreshAppleGameCenterSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AppleGameCenter);
	LLAPI<FLootLockerAppleGameCenterSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshAppleGameCenterSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleGameCenterSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleGameCenterSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));

}
void ULootLockerAuthenticationRequestHandler::RefreshAppleSession(const FString& RefreshToken, const FAppleSessionResponseBP& OnCompletedRequestBP, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshAppleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AppleSignIn);
	LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshAppleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnCompletedRequestBP, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();

	FLootLockerStartMetaSessionRequest AuthRequest;
	AuthRequest.user_id = UserId;
	AuthRequest.nonce = Nonce;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Meta);
	LLAPI<FLootLockerMetaSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::MetaSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerMetaSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerMetaSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));

}

void ULootLockerAuthenticationRequestHandler::RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnCompletedRequestBP, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();

	FLootLockerRefreshMetaSessionRequest AuthRequest;
	AuthRequest.refresh_token = RefreshToken;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Meta);
	LLAPI<FLootLockerMetaSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::MetaSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerMetaSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerMetaSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));

}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FString& PlatformToken, const FString& Platform, const int SteamAppId /* = -1 */, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	const FString RequestPlatform = Platform.IsEmpty() ? ULootLockerCurrentPlatform::GetString() : Platform;
	if(SteamAppId == -1)
	{
		LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerVerificationRequest{ Config->LootLockerGameKey, RequestPlatform }, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback::CreateLambda([RequestPlatform, PlatformToken](const FLootLockerResponse& Response)
		{
			if (Response.success)
			{
				if (RequestPlatform.Compare(ULootLockerCurrentPlatform::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Steam).PlatformString))
				{
					ULootLockerStateData::SetSteamToken(PlatformToken);
				}
			}
		}));
	} else
	{
		LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerVerificationWithSteamAppIdRequest{ Config->LootLockerGameKey, RequestPlatform, PlatformToken, SteamAppId }, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback::CreateLambda([RequestPlatform, PlatformToken](const FLootLockerResponse& Response)
		{
			if (Response.success)
			{
				if (RequestPlatform.Compare(ULootLockerCurrentPlatform::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Steam).PlatformString))
				{
					ULootLockerStateData::SetSteamToken(PlatformToken);
				}
			}
		}));
	}
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	TMap<FString, FString> CustomHeaders;
	if (ELootLockerPlatform::WhiteLabel == ULootLockerCurrentPlatform::Get())
	{
		CustomHeaders.Add(TEXT("logout"), TEXT("true"));
	}
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerResponse& Response)
		{
			if (Response.success) {
				ULootLockerStateData::ClearState();
				ULootLockerCurrentPlatform::Reset();
			}
		}), CustomHeaders);
}

TMap<FString, FString> ULootLockerAuthenticationRequestHandler::DomainKeyHeaders()
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("domain-key"), Config->DomainKey);
	CustomHeaders.Add(TEXT("is-development"), Config->LootLockerGameKey.StartsWith("dev_") ? TEXT("true") : TEXT("false"));
	return CustomHeaders;
}
