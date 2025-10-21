// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerSessionOptionals.h"
#include "LootLockerAuthenticationRequestHandler.generated.h"

/*
 * Google OAuth2 Client platform
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerGoogleClientPlatform : uint8
{
	Web = 0			UMETA(DisplayName = "Web"),
	Android = 1		UMETA(DisplayName = "Android"),
	Ios = 2			UMETA(DisplayName = "iOS"),
	Desktop = 3		UMETA(DisplayName = "Desktop")
};

USTRUCT()
struct FLootLockerAuthResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	/**
	 * The session token that can now be used to use further LootLocker functionality. We store and use this for you.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString session_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerLoginRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	FString email = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	FString password = "";
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelLoginRequest : public FLootLockerLoginRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	bool remember = false;
};

// Used for WhiteLabel Login
USTRUCT(BlueprintType)
struct FLootLockerLoginResponse : public FLootLockerAuthResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	int32 id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString player_name = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	int32 game_id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString email = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString created_at = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString last_seen = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString updated_at = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString deleted_at = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString validated_at = "";
};

USTRUCT(BlueprintType)
struct FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_key = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version = "";
};

USTRUCT(BlueprintType)
struct FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_api_key = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAuthenticationRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString platform = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString player_identifier = "";
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelAuthRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelVerifySessionRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelResetPasswordRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email = "";
};

USTRUCT(BlueprintType)
struct FLootLockerNintendoSwitchSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString nsa_id_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerStartMetaSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString user_id = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString nonce = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshMetaSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerXboxSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString xbox_user_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAppleGameCenterSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString bundle_id = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString player_id = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString public_key_url = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString signature = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString salt = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString timestamp = "";

};

USTRUCT(BlueprintType)
struct FLootLockerRefreshAppleGameCenterSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};


USTRUCT(BlueprintType)
struct FLootLockerAppleSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString apple_authorization_code = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshAppleSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString id_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionRequestWithPlatform : public FLootLockerGoogleSessionRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	ELootLockerGoogleClientPlatform platform = ELootLockerGoogleClientPlatform::Android;
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshGoogleSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGooglePlayGamesSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString auth_code = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshGooglePlayGamesSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerEpicSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString id_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshEpicSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerVerificationRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPlaystationNetworkVerificationRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Platform = "psn";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Token;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Psn_issuer_id = 256; // Default to production
};

USTRUCT(BlueprintType)
struct FLootLockerPlaystationNetworkV3SessionRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Game_api_key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Game_version;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Auth_code;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Env_iss_id = 256; // Default to production
};

USTRUCT(BlueprintType)
struct FLootLockerSteamSessionRequest: public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString steam_ticket = "";
};

USTRUCT(BlueprintType)
struct FLootLockerDiscordSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString access_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshDiscordSessionRequest : public FLootLockerBaseAuthRequest_Old
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerSteamSessionWithAppIdRequest : public FLootLockerSteamSessionRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString steam_app_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerVerificationWithSteamAppIdRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString token = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Active_steam_app_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerUserIdRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int user_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerEmailRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Email = "";
};

USTRUCT(BlueprintType)
struct FLootLockerLevelThresholds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 current = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool current_is_prestige = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 next = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool next_is_prestige = false;
};

USTRUCT(BlueprintType)
struct FLootLockerAuthenticationResponse : public FLootLockerAuthResponse
{
	GENERATED_BODY()
	/**
	 * The player's name if it has been set by using SetPlayerName().
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_name = "";
	/**
	 * The player id
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 player_id = 0;
	/**
	 * The public UID for this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString public_uid = "";
	/**
	 * The player ULID for this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_ulid = "";
	/**
	 * The date that this player was created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_created_at = "";
	/**
	 * Whether this player has been seen before (true) or is new (false)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool seen_before = false;
	/**
	 * Whether this player has new information to check in grants
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_grant_notifications = false;
	/**
	 * Whether this player has new information to check in deactivations
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_deactivation_notifications = false;
	/**
	 * The current xp of this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	/**
	 * The current level of this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	/**
	 * The level_thresholds that the level and xp data relates to
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerLevelThresholds level_thresholds;
	/**
	 * The current balance in this account
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance = 0;
	/**
	 * The player identifier of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_identifier = "";
	/**
	 The id of the wallet for this account
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString wallet_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAppleSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAppleGameCenterSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGooglePlayGamesSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerEpicSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelVerifySessionResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 game_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 user_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString email = "";
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelLoginAndSessionResponse : public FLootLockerAuthResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FLootLockerLoginResponse LoginResponse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FLootLockerAuthenticationResponse StartSessionResponse;

	FLootLockerWhiteLabelLoginAndSessionResponse() = default;

	FLootLockerWhiteLabelLoginAndSessionResponse(const FLootLockerLoginResponse& LoginResponse)
	{
		this->success = LoginResponse.success;
		this->StatusCode = LoginResponse.StatusCode;
		this->session_token = LoginResponse.session_token;
		this->FullTextFromServer = LoginResponse.FullTextFromServer;
		this->LoginResponse = LoginResponse;
		this->ErrorData = ErrorData;
		this->Context = LoginResponse.Context;
	}

	FLootLockerWhiteLabelLoginAndSessionResponse(const FLootLockerLoginResponse& LoginResponse, const FLootLockerAuthenticationResponse& SessionResponse)
	{
		this->success = SessionResponse.success;
		this->StatusCode = SessionResponse.StatusCode;
		this->session_token = SessionResponse.session_token;
		this->FullTextFromServer = SessionResponse.FullTextFromServer;
		this->LoginResponse = LoginResponse;
		this->StartSessionResponse = SessionResponse;
		this->ErrorData = ErrorData;
		this->Context = SessionResponse.Context;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerMetaSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString refresh_token = "";
};

USTRUCT(BlueprintType)
struct FLootLockerDiscordSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token = "";
};

DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FLootLockerAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerAppleSessionResponseDelegate, FLootLockerAppleSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGoogleSessionResponseDelegate, FLootLockerGoogleSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGooglePlayGamesSessionResponseDelegate, FLootLockerGooglePlayGamesSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerEpicSessionResponseDelegate, FLootLockerEpicSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerLoginResponseDelegate, FLootLockerLoginResponse);
DECLARE_DELEGATE_OneParam(FLootLockerWhiteLabelVerifySessionDelegate, FLootLockerWhiteLabelVerifySessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerWhiteLabelLoginAndSessionResponseDelegate, FLootLockerWhiteLabelLoginAndSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerAppleGameCenterSessionResponseDelegate, FLootLockerAppleGameCenterSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerMetaSessionResponseDelegate, FLootLockerMetaSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDiscordSessionResponseDelegate, FLootLockerDiscordSessionResponse);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API ULootLockerAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerAuthenticationRequestHandler() {};

	static FString WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static FString WhiteLabelLogin(const FString& Email, const FString& Password, const bool Remember, const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static FString GuestLogin(const FString& playerIdentifier, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static FString WhiteLabelStartSession(const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static FString WhiteLabelVerifySession(const FLootLockerPlayerData& ForPlayer, const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest = FLootLockerWhiteLabelVerifySessionDelegate());
	static FString WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static FString WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static FString WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static FString StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, int PsnIssuerId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, int EnvIssuerId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString StartAndroidSession(const FString& DeviceId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString StartGoogleSession(const FString& IdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest = FLootLockerGoogleSessionResponseDelegate());
	static FString StartGoogleSession(const FString& IdToken, const ELootLockerGoogleClientPlatform Platform, const FLootLockerSessionOptionals& Optionals, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest = FLootLockerGoogleSessionResponseDelegate());
	static FString RefreshGoogleSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest = FLootLockerGoogleSessionResponseDelegate());
	static FString StartGooglePlayGamesSession(const FString& IdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest = FLootLockerGooglePlayGamesSessionResponseDelegate());
	static FString RefreshGooglePlayGamesSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest = FLootLockerGooglePlayGamesSessionResponseDelegate());
	static FString StartEpicSession(const FString& IdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest = FLootLockerEpicSessionResponseDelegate());
	static FString RefreshEpicSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest = FLootLockerEpicSessionResponseDelegate());
	static FString StartAmazonLunaSession(const FString& AmazonLunaGuid, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString StartSteamSession(const FString& SteamId64, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString StartSteamSession(const FString& SteamSessionTicket, const FString& SteamAppId, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static FString StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static FString StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static FString StartAppleSession(const FString& AuthorizationCode, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleSessionResponseDelegate());
	static FString RefreshAppleSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleSessionResponseDelegate());
	static FString VerifyPlayer(const FLootLockerPlayerData& ForPlayer, const FString& PlatformToken, const FString& Platform, const int SteamAppId = -1, const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static FString EndSession(const FLootLockerPlayerData& ForPlayer, const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static FString WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, bool bRemember, const FLootLockerSessionOptionals& Optionals, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& LootLockerWhiteLabelLoginAndSessionResponseDelegate = FLootLockerWhiteLabelLoginAndSessionResponseDelegate());
	static FString StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleGameCenterSessionResponseDelegate()); 
	static FString RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleGameCenterSessionResponseDelegate());
	static FString StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerSessionOptionals& Optionals, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest = FLootLockerMetaSessionResponseDelegate());
	static FString RefreshMetaSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest = FLootLockerMetaSessionResponseDelegate());
	static FString StartDiscordSession(const FString& AccessToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest = FLootLockerDiscordSessionResponseDelegate());
	static FString RefreshDiscordSession(const FString& RefreshToken, const FLootLockerSessionOptionals& Optionals, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest = FLootLockerDiscordSessionResponseDelegate());
	
private:
	template<typename RequestType>
	static FString AuthRequestToJsonStringWithOptionals(const RequestType& AuthRequest, const FLootLockerSessionOptionals& Optionals);

	static FString _TempWhiteLabelEmailHolder;
	static FString _TempWhiteLabelTokenHolder;
	static TMap<FString, FString> DomainKeyHeaders();
};
