// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"

#include "LootLockerConfig.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAuthenticationRequestHandler::HttpClient = nullptr;
FString ULootLockerAuthenticationRequestHandler::_TempWhiteLabelEmailHolder = "";
FString ULootLockerAuthenticationRequestHandler::_TempWhiteLabelTokenHolder = "";

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

	_TempWhiteLabelEmailHolder = Email;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
		{
			if (!Response.success)
			{
				_TempWhiteLabelEmailHolder = "";
			}
		}), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& PlayerIdentifier, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	const FLootLockerPlayerData& PlayerData = ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer();
	AuthRequest.player_identifier = !(PlayerIdentifier.IsEmpty()) ? PlayerIdentifier : !PlayerData.PlayerIdentifier.IsEmpty() ?  PlayerData.PlayerIdentifier : ULootLockerStateData::GenerateNewGuestIdentifier();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	_TempWhiteLabelEmailHolder = Email;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, LoginRequest, ULootLockerGameEndpoints::WhiteLabelLoginEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
		{
			if (Response.success) {
				_TempWhiteLabelTokenHolder = Response.session_token;
			}
			else
			{
				_TempWhiteLabelEmailHolder = "";
			}
		}), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	FLootLockerWhiteLabelAuthRequest AuthRequest;
	AuthRequest.game_key = Config->LootLockerGameKey;
	AuthRequest.game_version = Config->GameVersion;

	AuthRequest.email = _TempWhiteLabelEmailHolder;
	AuthRequest.token = _TempWhiteLabelTokenHolder;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, _TempWhiteLabelEmailHolder, _TempWhiteLabelTokenHolder, ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::WhiteLabel), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
				_TempWhiteLabelEmailHolder = "";
				_TempWhiteLabelTokenHolder = "";
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

void ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(const FLootLockerPlayerData& ForPlayer, const FLootLockerVerifySessionResponseBP& OnCompletedRequestBP, const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelVerifySessionRequest VerifyRequest;
	if (!_TempWhiteLabelEmailHolder.IsEmpty() && !_TempWhiteLabelTokenHolder.IsEmpty())
	{
		VerifyRequest.email = _TempWhiteLabelEmailHolder;
		VerifyRequest.token = _TempWhiteLabelTokenHolder;
	}
	else
	{
		const FLootLockerPlayerData& PlayerData = ForPlayer.WhiteLabelEmail.IsEmpty() ? ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayer.PlayerUlid) : ForPlayer;
		VerifyRequest.email = PlayerData.WhiteLabelEmail;
		VerifyRequest.token = PlayerData.WhiteLabelToken;
	}

	LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::CallAPI(HttpClient, VerifyRequest, ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerUserIdRequest UserIdRequest;
	UserIdRequest.user_id = UserId;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, UserIdRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerEmailRequest EmailRequest;
	EmailRequest.Email = Email;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, EmailRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelResetPasswordRequest ResetPasswordRequest;
	ResetPasswordRequest.email = Email;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, ResetPasswordRequest, ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = PsnOnlineId;

	AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork).PlatformString;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Android).PlatformString;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Android), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerGoogleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartGoogleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Google), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerGoogleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartGoogleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Google), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerGoogleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshGoogleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Google), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartGooglePlayGamesSession(const FString& AuthCode, const FGooglePlayGamesSessionResponseBP& OnCompletedRequestBP, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGooglePlayGamesSessionRequest AuthRequest;
	AuthRequest.game_api_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.auth_code = AuthCode;

	LLAPI<FLootLockerGooglePlayGamesSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartGooglePlayGamesSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGooglePlayGamesSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerGooglePlayGamesSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::GooglePlayGames), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshGooglePlayGamesSession(const FString& RefreshToken, const FGooglePlayGamesSessionResponseBP& OnCompletedRequestBP, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshGooglePlayGamesSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	LLAPI<FLootLockerGooglePlayGamesSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshGooglePlayGamesSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerGooglePlayGamesSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerGooglePlayGamesSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::GooglePlayGames), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerEpicSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartEpicSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerEpicSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerEpicSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Epic), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshEpicSession(const FString& RefreshToken, const FEpicSessionResponseBP& OnCompletedRequestBP, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	const auto InspectionLambda = LLAPI<FLootLockerEpicSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerEpicSessionResponse& Response)
		{
			if (Response.success)
			{
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Epic), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		});
	FLootLockerRefreshEpicSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	LLAPI<FLootLockerEpicSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshEpicSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, InspectionLambda);
}

void ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = AmazonLunaGuid;

	AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AmazonLuna).PlatformString;
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AmazonLuna), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartSteamSession(const FString& SteamSessionTicket, const FString& SteamAppId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	auto responseHandler = LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Steam), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		});
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	if (SteamAppId.IsEmpty()) {
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, FLootLockerSteamSessionRequest{ config->LootLockerGameKey, config->GameVersion, SteamSessionTicket }, ULootLockerGameEndpoints::SteamSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, responseHandler);
	}
	else {
		FLootLockerSteamSessionWithAppIdRequest request;
		request.steam_app_id = SteamAppId;
		request.game_api_key = config->LootLockerGameKey;
		request.game_version = config->GameVersion;
		request.steam_ticket = SteamSessionTicket;
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::SteamSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, responseHandler);
	}
}

void ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerNintendoSwitchSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.nsa_id_token = NSAIdToken;

	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::NintendoSwitch), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartXboxSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Xbox), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerAppleGameCenterSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartAppleGameCenterSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleGameCenterSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAppleGameCenterSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleGameCenter), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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
	LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartAppleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleSignIn), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerAppleGameCenterSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshAppleGameCenterSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleGameCenterSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAppleGameCenterSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, "", "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleGameCenter), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshAppleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleSignIn), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerMetaSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::MetaSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerMetaSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerMetaSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Meta), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
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

	LLAPI<FLootLockerMetaSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::MetaSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerMetaSessionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerMetaSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Meta), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));

}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FLootLockerPlayerData& ForPlayer, const FString& PlatformToken, const FString& Platform, const int SteamAppId /* = -1 */, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	const FString RequestPlatform = Platform.IsEmpty() ? ForPlayer.CurrentPlatform.PlatformString : Platform;
	if(SteamAppId == -1)
	{
		LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerVerificationRequest{ Config->LootLockerGameKey, RequestPlatform }, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest);
	} else
	{
		LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerVerificationWithSteamAppIdRequest{ Config->LootLockerGameKey, RequestPlatform, PlatformToken, SteamAppId }, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequestBP, OnCompletedRequest);
	}
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FLootLockerPlayerData& ForPlayer, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	TMap<FString, FString> CustomHeaders;
	if (ELootLockerPlatform::WhiteLabel == ForPlayer.CurrentPlatform.Platform)
	{
		CustomHeaders.Add(TEXT("logout"), TEXT("true"));
	}
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { }, EmptyQueryParams, ForPlayer, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerResponse& Response)
		{
			if (Response.success) {
				ULootLockerStateData::ClearSavedStateForPlayer(Response.Context.PlayerUlid);
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
