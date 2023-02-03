// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
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

void ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegateBP &OnCompletedRequestBP, const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	FLootLockerLoginRequest SignupRequest;
	SignupRequest.email = Email;
	SignupRequest.password = Password;
	
	LLAPI<FLootLockerLoginResponse>::CallAPI(HttpClient, SignupRequest, ULootLockerGameEndpoints::WhiteLabelSignupEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerLoginResponse>::FResponseInspectorCallback::CreateLambda([Email](const FLootLockerLoginResponse& Response)
    {
        ULootLockerStateData::SetWhiteLabelEmail(Email);
    }), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::GuestLogin(const FString& PlayerIdentifier, const FAuthResponseBP &OnCompletedRequestBP, const FLootLockerSessionResponse &OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	if(config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAuthenticationRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.player_identifier = !(PlayerIdentifier.IsEmpty()) ? PlayerIdentifier : ULootLockerStateData::GetPlayerIdentifier();
		ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Guest);
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			} else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = !(PlayerIdentifier.IsEmpty()) ? PlayerIdentifier : ULootLockerStateData::GetPlayerIdentifier();
	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Guest);
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::GuestloginEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if(Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
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
	if (Config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerWhiteLabelAuthRequestWithDevelopmentMode AuthRequest;
		AuthRequest.development_mode = Config->OnDevelopmentMode;
	    AuthRequest.game_key = Config->LootLockerGameKey;
	    AuthRequest.game_version = Config->GameVersion;
	    AuthRequest.email = ULootLockerStateData::GetWhiteLabelEmail();
	    AuthRequest.token = ULootLockerStateData::GetWhiteLabelToken();
	    LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::WhiteLabelAuthEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
	
	LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::CallAPI(HttpClient, VerifyRequest, ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerWhiteLabelVerifySessionResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerUserIdRequest UserIdRequest;
	UserIdRequest.user_id = UserId;
	
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, UserIdRequest, ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

void ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
	FLootLockerWhiteLabelResetPasswordRequest ResetPasswordRequest;
	ResetPasswordRequest.email = Email;
	
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, ResetPasswordRequest, ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback(), DomainKeyHeaders());
}

//TODO: Deprecated method, remove in v2.1
void ULootLockerAuthenticationRequestHandler::StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAuthenticationRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.player_identifier = PlayerId;

		if (ULootLockerCurrentPlatform::Get() == ELootLockerPlatform::None) {
			ULootLockerCurrentPlatform::Set(config->Platform);
		}
		AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = PlayerId;

	if (ULootLockerCurrentPlatform::Get() == ELootLockerPlatform::None) {
		ULootLockerCurrentPlatform::Set(config->Platform);
	}
	AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
    {
        if (Response.success)
        {
            ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
        }
		else
		{
			ULootLockerCurrentPlatform::Reset();
		}
    }));
}

void ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAuthenticationRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
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
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAuthenticationRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
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
				}
				else
				{
					ULootLockerCurrentPlatform::Reset();
				}
			}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
}

void ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnCompletedRequestBP, const FLootLockerSessionResponse& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAuthenticationRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
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
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAuthenticationRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.player_identifier = SteamId64;

		ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AmazonLuna);
		AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
			{
				if (Response.success)
				{
					ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				}
				else
				{
					ULootLockerCurrentPlatform::Reset();
				}
			}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
	FLootLockerAuthenticationRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.player_identifier = SteamId64;

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AmazonLuna);
	AuthRequest.platform = ULootLockerCurrentPlatform::GetString();
	LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
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
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerNintendoSwitchSessionRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.nsa_id_token = NSAIdToken;

		ULootLockerCurrentPlatform::Set(ELootLockerPlatform::NintendoSwitch);
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerXboxSessionRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.xbox_user_token = XboxUserToken;

		ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Xbox);
		LLAPI<FLootLockerAuthenticationResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartXboxSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerAppleSessionRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.apple_authorization_code = AuthorizationCode;

		ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AppleSignIn);
		LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::StartAppleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
	if (config->IsLegacyAPIKey()) // TODO: <Deprecated functionality, remove in v2.1>
	{
		FLootLockerRefreshAppleSessionRequestWithDevelopmentMode AuthRequest(config->OnDevelopmentMode);
		AuthRequest.game_key = config->LootLockerGameKey;
		AuthRequest.game_version = config->GameVersion;
		AuthRequest.refresh_token = RefreshToken;

		ULootLockerCurrentPlatform::Set(ELootLockerPlatform::AppleSignIn);
		LLAPI<FLootLockerAppleSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshAppleSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAppleSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAppleSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));
		return;
	} // TODO: </Deprecated functionality, remove in v2.1>
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
        }
		else
		{
			ULootLockerCurrentPlatform::Reset();
		}
    }));
}

void ULootLockerAuthenticationRequestHandler::VerifyPlayer(const FString& PlatformToken, const FString& Platform, const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	FLootLockerVerificationRequest AuthRequest;
	AuthRequest.token = PlatformToken;

	const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
	AuthRequest.key = Config->LootLockerGameKey;

	FString RequestPlatform = Platform.IsEmpty() ? ULootLockerCurrentPlatform::GetString().IsEmpty() ? ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int>(Config->Platform)) : ULootLockerCurrentPlatform::GetString() : Platform;
	AuthRequest.platform = RequestPlatform;
	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::VerifyPlayerIdEndPoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationDefaultResponse>::FResponseInspectorCallback::CreateLambda([RequestPlatform, PlatformToken](const FLootLockerAuthenticationDefaultResponse& Response)
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

void ULootLockerAuthenticationRequestHandler::EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest)
{
	TMap<FString, FString> CustomHeaders;
	if(ELootLockerPlatform::WhiteLabel == ULootLockerCurrentPlatform::Get())
	{
		CustomHeaders.Add(TEXT("logout"), TEXT("true"));
	}
	LLAPI<FLootLockerAuthenticationDefaultResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::EndSessionEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerAuthenticationDefaultResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerAuthenticationDefaultResponse& Response)
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
	if ((Config->IsLegacyAPIKey() && Config->OnDevelopmentMode) || Config->LootLockerGameKey.StartsWith("dev_")) {
		CustomHeaders.Add(TEXT("is-development"), Config->OnDevelopmentMode ? TEXT("true") : TEXT("false"));
	}
	return CustomHeaders;
}
