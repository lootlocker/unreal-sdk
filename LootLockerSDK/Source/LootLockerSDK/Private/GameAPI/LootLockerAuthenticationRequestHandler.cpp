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

void ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate& OnCompletedRequest)
{
	FLootLockerLoginRequest SignupRequest;
	SignupRequest.email = Email;
	SignupRequest.password = Password;

	_TempWhiteLabelEmailHolder = Email;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
		{
			if (!Response.success)
			{
				_TempWhiteLabelEmailHolder = "";
			}
		}), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	const FLootLockerPlayerData& PlayerData = ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer();
	AuthRequest.player_identifier = !(PlayerIdentifier.IsEmpty()) ? PlayerIdentifier : !PlayerData.PlayerIdentifier.IsEmpty() ?  PlayerData.PlayerIdentifier : ULootLockerStateData::GenerateNewGuestIdentifier();
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::GuestloginEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(const FString& Email, const FString& Password, const bool Remember, const FLootLockerLoginResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	FLootLockerWhiteLabelLoginRequest LoginRequest;
	LoginRequest.email = Email;
	LoginRequest.password = Password;
	LoginRequest.remember = Remember;

	_TempWhiteLabelEmailHolder = Email;

	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, LoginRequest, ULootLockerGameEndpoints::WhiteLabelLoginEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
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

void ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	FLootLockerWhiteLabelAuthRequest AuthRequest;
	AuthRequest.game_key = Config->LootLockerGameKey;
	AuthRequest.game_version = Config->GameVersion;

	AuthRequest.email = _TempWhiteLabelEmailHolder;
	AuthRequest.token = _TempWhiteLabelTokenHolder;
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, _TempWhiteLabelEmailHolder, _TempWhiteLabelTokenHolder, ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::WhiteLabel), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
				_TempWhiteLabelEmailHolder = "";
				_TempWhiteLabelTokenHolder = "";
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, bool bRemember, const FLootLockerSessionOptionals& Optionals, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& LootLockerWhiteLabelLoginAndSessionResponseDelegate)
{
	WhiteLabelLogin(Email, Password, bRemember, FLootLockerLoginResponseDelegate::CreateLambda([Optionals, LootLockerWhiteLabelLoginAndSessionResponseDelegate](FLootLockerLoginResponse LoginResponse)
		{
			if (!LoginResponse.success)
			{
				const FLootLockerWhiteLabelLoginAndSessionResponse FullResponse = FLootLockerWhiteLabelLoginAndSessionResponse(LoginResponse);
				LootLockerWhiteLabelLoginAndSessionResponseDelegate.ExecuteIfBound(FullResponse);
				return;
			}

			WhiteLabelStartSession(Optionals, FLootLockerSessionResponse::CreateLambda([LootLockerWhiteLabelLoginAndSessionResponseDelegate, LoginResponse](const FLootLockerAuthenticationResponse& StartSessionResponse)
				{
					const FLootLockerWhiteLabelLoginAndSessionResponse FullResponse = FLootLockerWhiteLabelLoginAndSessionResponse(LoginResponse, StartSessionResponse);
					LootLockerWhiteLabelLoginAndSessionResponseDelegate.ExecuteIfBound(FullResponse);
				}));
		}));
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(const FLootLockerPlayerData& ForPlayer, const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest)
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

	LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::CallAPI(HttpClient, VerifyRequest, ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerUserIdRequest UserIdRequest;
	UserIdRequest.user_id = UserId;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, UserIdRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerEmailRequest EmailRequest;
	EmailRequest.Email = Email;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, EmailRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelResetPasswordRequest ResetPasswordRequest;
	ResetPasswordRequest.email = Email;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, ResetPasswordRequest, ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = PsnOnlineId;

	AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork).PlatformString;
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, int PsnIssuerId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerPlaystationNetworkVerificationRequest VerificationRequest;
	VerificationRequest.Key = config->LootLockerGameKey;
	VerificationRequest.Token = AuthCode;
	VerificationRequest.Psn_issuer_id = PsnIssuerId;
	VerificationRequest.Platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork).PlatformString;

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, VerificationRequest, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, FLootLockerPlayerData(), FLootLockerDefaultDelegate(), LLAPI<FLootLockerResponse>::FResponseInspectorCallback::CreateLambda([AccountID, Optionals, Delegate](FLootLockerResponse& Response)
		{
			if (!Response.success)
			{
				FLootLockerAuthenticationResponse TranslatedError = LootLockerResponseFactory::ErrorFromError<FLootLockerAuthenticationResponse>(Response);
				Delegate.ExecuteIfBound(TranslatedError);
				return;
			}
		const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
		FLootLockerAuthenticationRequest AuthRequest;
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.player_identifier = AccountID;
		AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork).PlatformString;
		FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
		LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), Delegate, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
	}));

}

void ULootLockerAuthenticationRequestHandler::VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, int EnvIssuerId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerPlaystationNetworkV3SessionRequest AuthRequest {
		config->LootLockerGameKey,
		config->GameVersion,
		AuthCode,
		EnvIssuerId
	};
	
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::PlaystationNetworkV3SessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), Delegate, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::PlayStationNetwork), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartAndroidSession(const FString& DeviceId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = DeviceId;

	AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Android).PlatformString;
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Android), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartGoogleSession(const FString& IdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGoogleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.id_token = IdToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerGoogleSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartGoogleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Google), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartGoogleSession(const FString& IdToken, const ELootLockerGoogleClientPlatform Platform, const FLootLockerSessionOptionals& Optionals, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGoogleSessionRequestWithPlatform AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.id_token = IdToken;
	AuthRequest.platform = Platform;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerGoogleSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartGoogleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Google), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshGoogleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerGoogleSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::RefreshGoogleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerGoogleSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerGoogleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Google), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartGooglePlayGamesSession(const FString& AuthCode, const FLootLockerSessionOptionals& Optionals, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGooglePlayGamesSessionRequest AuthRequest;
	AuthRequest.game_api_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.auth_code = AuthCode;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerGooglePlayGamesSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartGooglePlayGamesSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerGooglePlayGamesSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerGooglePlayGamesSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::GooglePlayGames), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshGooglePlayGamesSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshGooglePlayGamesSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerGooglePlayGamesSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::RefreshGooglePlayGamesSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerGooglePlayGamesSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerGooglePlayGamesSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::GooglePlayGames), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartEpicSession(const FString& IdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerEpicSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.id_token = IdToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerEpicSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartEpicSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerEpicSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerEpicSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Epic), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshEpicSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	const auto InspectionLambda = LLAPI<FLootLockerEpicSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerEpicSessionResponse& Response)
		{
			if (Response.success)
			{
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Epic), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		});
	FLootLockerRefreshEpicSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerEpicSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::RefreshEpicSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, InspectionLambda);
}

void ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = AmazonLunaGuid;

	AuthRequest.platform = ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AmazonLuna).PlatformString;
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AmazonLuna), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartSteamSession(const FString& SteamSessionTicket, const FString& SteamAppId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	auto responseHandler = LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Steam), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		});
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	if (SteamAppId.IsEmpty()) {
		FLootLockerSteamSessionRequest request;
		request.game_api_key = config->LootLockerGameKey;
		request.game_version = config->GameVersion;
		request.steam_ticket = SteamSessionTicket;
		FString Json = AuthRequestToJsonStringWithOptionals(request, Optionals);
		LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::SteamSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, responseHandler);
	}
	else {
		FLootLockerSteamSessionWithAppIdRequest request;
		request.steam_app_id = SteamAppId;
		request.game_api_key = config->LootLockerGameKey;
		request.game_version = config->GameVersion;
		request.steam_ticket = SteamSessionTicket;
		FString Json = AuthRequestToJsonStringWithOptionals(request, Optionals);
		LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::SteamSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, responseHandler);
	}
}

void ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerNintendoSwitchSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.nsa_id_token = NSAIdToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::NintendoSwitch), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerXboxSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.xbox_user_token = XboxUserToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartXboxSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Xbox), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest)
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

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAppleGameCenterSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartAppleGameCenterSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAppleGameCenterSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAppleGameCenterSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleGameCenter), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));


}

void ULootLockerAuthenticationRequestHandler::StartAppleSession(const FString& AuthorizationCode, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerAppleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.apple_authorization_code = AuthorizationCode;
	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAppleSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartAppleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleSignIn), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();


	FLootLockerRefreshAppleGameCenterSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAppleGameCenterSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::RefreshAppleGameCenterSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAppleGameCenterSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAppleGameCenterSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, "", "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleGameCenter), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));

}

void ULootLockerAuthenticationRequestHandler::RefreshAppleSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshAppleSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerAppleSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::RefreshAppleSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::AppleSignIn), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerSessionOptionals& Optionals, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();

	FLootLockerStartMetaSessionRequest AuthRequest;
	AuthRequest.user_id = UserId;
	AuthRequest.nonce = Nonce;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerMetaSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::MetaSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerMetaSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerMetaSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Meta), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));

}

void ULootLockerAuthenticationRequestHandler::RefreshMetaSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();

	FLootLockerRefreshMetaSessionRequest AuthRequest;
	AuthRequest.refresh_token = RefreshToken;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerMetaSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::MetaSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerMetaSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerMetaSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Meta), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));

}

void ULootLockerAuthenticationRequestHandler::StartDiscordSession(const FString& AccessToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerDiscordSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.access_token = AccessToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerDiscordSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::StartDiscordSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerDiscordSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerDiscordSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Discord), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::RefreshDiscordSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshDiscordSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	FString Json = AuthRequestToJsonStringWithOptionals(AuthRequest, Optionals);
	LLAPI<FLootLockerDiscordSessionResponse>::CallAPIUsingRawJSON(HttpClient, Json, ULootLockerGameEndpoints::RefreshDiscordSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest, LLAPI<FLootLockerDiscordSessionResponse>::FResponseInspectorCallback::CreateLambda([Optionals](FLootLockerDiscordSessionResponse& Response)
		{
			if (Response.success)
			{
				Response.Context.PlayerUlid = Response.player_ulid;
				auto NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Discord), FDateTime::Now().ToString(), Response.player_created_at, Optionals);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FLootLockerPlayerData& ForPlayer, const FString& PlatformToken, const FString& Platform, const int SteamAppId /* = -1 */, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	const FString RequestPlatform = Platform.IsEmpty() ? ForPlayer.CurrentPlatform.PlatformString : Platform;
	if(SteamAppId == -1)
	{
		LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerVerificationRequest{ Config->LootLockerGameKey, RequestPlatform }, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest);
	} 
	else
	{
		LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerVerificationWithSteamAppIdRequest{ Config->LootLockerGameKey, RequestPlatform, PlatformToken, SteamAppId }, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompletedRequest);
	}
}

void ULootLockerAuthenticationRequestHandler::EndSession(const FLootLockerPlayerData& ForPlayer, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	TMap<FString, FString> CustomHeaders;
	if (ELootLockerPlatform::WhiteLabel == ForPlayer.CurrentPlatform.Platform)
	{
		CustomHeaders.Add(TEXT("logout"), TEXT("true"));
	}
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { }, EmptyQueryParams, ForPlayer, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerResponse& Response)
		{
			if (Response.success) {
				ULootLockerStateData::ClearSavedStateForPlayer(Response.Context.PlayerUlid);
			}
		}), CustomHeaders);
}

template<typename RequestType>
FString ULootLockerAuthenticationRequestHandler::AuthRequestToJsonStringWithOptionals(const RequestType& AuthRequest, const FLootLockerSessionOptionals& Optionals)
{
	TSharedRef<FJsonObject> JsonObject = LootLockerUtilities::UStructToJsonObject(AuthRequest);
	FString ParsedJsonString = LootLockerUtilities::FStringFromJsonObject(JsonObject);
	if(ParsedJsonString.IsEmpty() || LootLockerUtilities::IsEmptyJsonString(ParsedJsonString))
	{
		return ParsedJsonString;
	}

	// Add optional parameters if they are set
	if (Optionals.IsSet())
	{
		TSharedRef<FJsonObject> OptionalsObject = LootLockerUtilities::UStructToJsonObject(Optionals);
		ParsedJsonString = LootLockerUtilities::FStringFromJsonObject(OptionalsObject);
		if(!ParsedJsonString.IsEmpty() && !LootLockerUtilities::IsEmptyJsonString(ParsedJsonString))
		{
			JsonObject->SetObjectField(TEXT("optionals"), OptionalsObject);
		}
	}
	else 
	{
		JsonObject->SetField(TEXT("optionals"), MakeShared<FJsonValueNull>());
	}
	
	return LootLockerUtilities::FStringFromJsonObject(JsonObject);
}

TMap<FString, FString> ULootLockerAuthenticationRequestHandler::DomainKeyHeaders()
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	TMap<FString, FString> CustomHeaders = TMap<FString, FString>();
	CustomHeaders.Add(TEXT("domain-key"), Config->DomainKey);
	CustomHeaders.Add(TEXT("is-development"), Config->LootLockerGameKey.StartsWith("dev_") ? TEXT("true") : TEXT("false"));
	return CustomHeaders;
}
