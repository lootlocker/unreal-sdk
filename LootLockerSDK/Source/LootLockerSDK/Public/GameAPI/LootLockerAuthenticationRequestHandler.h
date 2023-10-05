// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString session_token;	
};

USTRUCT(BlueprintType)
struct FLootLockerLoginRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	FString password;
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelLoginRequest : public FLootLockerLoginRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	bool remember = false;
};

USTRUCT(BlueprintType)
struct FLootLockerLoginResponse : public FLootLockerAuthResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	int32 id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	int32 game_id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString created_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString updated_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString deleted_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	FString validated_at;
};

USTRUCT(BlueprintType)
struct FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
};

USTRUCT(BlueprintType)
struct FLootLockerAuthenticationRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString player_identifier;
};

USTRUCT(BlueprintType)
struct FLootLockerAuthenticationRequestWithDevelopmentMode : public FLootLockerAuthenticationRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerAuthenticationRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelAuthRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString token;
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelAuthRequestWithDevelopmentMode : public FLootLockerWhiteLabelAuthRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerWhiteLabelAuthRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelVerifySessionRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString token;
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelResetPasswordRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email;
};

USTRUCT(BlueprintType)
struct FLootLockerNintendoSwitchSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString nsa_id_token;
};

USTRUCT(BlueprintType)
struct FLootLockerNintendoSwitchSessionRequestWithDevelopmentMode : public FLootLockerNintendoSwitchSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerNintendoSwitchSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerStartMetaSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString nonce;
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshMetaSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token;
};

USTRUCT(BlueprintType)
struct FLootLockerXboxSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString xbox_user_token;
};

USTRUCT(BlueprintType)
struct FLootLockerXboxSessionRequestWithDevelopmentMode : public FLootLockerXboxSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerXboxSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};


USTRUCT(BlueprintType)
struct FLootLockerAppleGameCenterSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString bundle_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString player_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString public_key_url;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString signature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString salt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString timestamp;

};

USTRUCT(BlueprintType)
struct FLootLockerRefreshAppleGameCenterSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString refresh_token;
};


USTRUCT(BlueprintType)
struct FLootLockerAppleSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString apple_authorization_code;
};

USTRUCT(BlueprintType)
struct FLootLockerAppleSessionRequestWithDevelopmentMode : public FLootLockerAppleSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerAppleSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};



USTRUCT(BlueprintType)
struct FLootLockerRefreshAppleSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token;
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshAppleSessionRequestWithDevelopmentMode : public FLootLockerRefreshAppleSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerRefreshAppleSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString id_token;
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionRequestWithDevelopmentMode : public FLootLockerGoogleSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerGoogleSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionRequestWithPlatform : public FLootLockerGoogleSessionRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	ELootLockerGoogleClientPlatform platform = ELootLockerGoogleClientPlatform::Android;
};

USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionRequestWithPlatformAndDevelopmentMode : public FLootLockerGoogleSessionRequestWithPlatform // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool development_mode;

	FLootLockerGoogleSessionRequestWithPlatformAndDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshGoogleSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token;
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshGoogleSessionRequestWithDevelopmentMode : public FLootLockerRefreshGoogleSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerRefreshGoogleSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerEpicSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString id_token;
};

USTRUCT(BlueprintType)
struct FLootLockerEpicSessionRequestWithDevelopmentMode : public FLootLockerEpicSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;

	FLootLockerEpicSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshEpicSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString refresh_token;
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshEpicSessionRequestWithDevelopmentMode : public FLootLockerRefreshEpicSessionRequest // TODO: Deprecated functionality, remove in v2.1
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
		bool development_mode;

	FLootLockerRefreshEpicSessionRequestWithDevelopmentMode(bool developmentMode = false)
	{
		development_mode = developmentMode;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerVerificationRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString token;
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 player_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString public_uid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_ulid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool seen_before = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_grant_notifications = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_deactivation_notifications = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerLevelThresholds level_thresholds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_identifier;
};

USTRUCT(BlueprintType)
struct FLootLockerAppleSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString refresh_token;
};

USTRUCT(BlueprintType)
struct FLootLockerAppleGameCenterSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString refresh_token;
};


USTRUCT(BlueprintType)
struct FLootLockerGoogleSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString refresh_token;
};

USTRUCT(BlueprintType)
struct FLootLockerEpicSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString refresh_token;
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
	FString email;
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

		this->Error = LoginResponse.Error;
		this->ServerCallStatusCode = LoginResponse.ServerCallStatusCode;
	}

	FLootLockerWhiteLabelLoginAndSessionResponse(const FLootLockerLoginResponse& LoginResponse, const FLootLockerAuthenticationResponse& SessionResponse)
	{
		this->success = SessionResponse.success;
		this->StatusCode = SessionResponse.StatusCode;
		this->session_token = SessionResponse.session_token;
		this->FullTextFromServer = SessionResponse.FullTextFromServer;
		this->LoginResponse = LoginResponse;
		this->StartSessionResponse = SessionResponse;

		this->ServerCallStatusCode = SessionResponse.ServerCallStatusCode;
		this->Error = SessionResponse.Error;
	}
};

USTRUCT(BlueprintType)
struct FLootLockerMetaSessionResponse : public FLootLockerAuthenticationResponse
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
		FString refresh_token;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthResponseBP, FLootLockerAuthenticationResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAppleSessionResponseBP, FLootLockerAppleSessionResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGoogleSessionResponseBP, FLootLockerGoogleSessionResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEpicSessionResponseBP, FLootLockerEpicSessionResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLoginResponseDelegateBP, FLootLockerLoginResponse, AuthVar);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerVerifySessionResponseBP, FLootLockerWhiteLabelVerifySessionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP, FLootLockerWhiteLabelLoginAndSessionResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerAppleGameCenterSessionResponseBP, FLootLockerAppleGameCenterSessionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerMetaSessionResponseBP, FLootLockerMetaSessionResponse, Var);
DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FLootLockerAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerAppleSessionResponseDelegate, FLootLockerAppleSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGoogleSessionResponseDelegate, FLootLockerGoogleSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerEpicSessionResponseDelegate, FLootLockerEpicSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerLoginResponseDelegate, FLootLockerLoginResponse);
DECLARE_DELEGATE_OneParam(FLootLockerWhiteLabelVerifySessionDelegate, FLootLockerWhiteLabelVerifySessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerWhiteLabelLoginAndSessionResponseDelegate, FLootLockerWhiteLabelLoginAndSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerAppleGameCenterSessionResponseDelegate, FLootLockerAppleGameCenterSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerMetaSessionResponseDelegate, FLootLockerMetaSessionResponse);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API ULootLockerAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerAuthenticationRequestHandler();

	static void WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP = FLootLockerLoginResponseDelegateBP(), const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static void WhiteLabelLogin(const FString& Email, const FString& Password, const bool Remember, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP = FLootLockerLoginResponseDelegateBP(), const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static void GuestLogin(const FString& playerIdentifier, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void WhiteLabelStartSession(const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void WhiteLabelVerifySession(const FLootLockerVerifySessionResponseBP& OnCompletedRequestBP = FLootLockerVerifySessionResponseBP(), const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest = FLootLockerWhiteLabelVerifySessionDelegate());
	static void WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
    static void WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
    static void WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static void StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& AuthResponseBP = FAuthResponseBP(), const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static void StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& AuthResponseBP = FAuthResponseBP(), const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
	static void StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnCompletedRequestBP = FGoogleSessionResponseBP(), const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest = FLootLockerGoogleSessionResponseDelegate());
	static void StartGoogleSession(const FString& IdToken, const ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnCompletedRequestBP = FGoogleSessionResponseBP(), const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest = FLootLockerGoogleSessionResponseDelegate());
    static void RefreshGoogleSession(const FString& RefreshToken, const FGoogleSessionResponseBP& OnCompletedRequestBP = FGoogleSessionResponseBP(), const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest = FLootLockerGoogleSessionResponseDelegate());
	static void StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnCompletedRequestBP = FEpicSessionResponseBP(), const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest = FLootLockerEpicSessionResponseDelegate());
	static void RefreshEpicSession(const FString& RefreshToken, const FEpicSessionResponseBP& OnCompletedRequestBP = FEpicSessionResponseBP(), const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest = FLootLockerEpicSessionResponseDelegate());
    static void StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& AuthResponseBP = FAuthResponseBP(), const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
    static void StartSteamSession(const FString& SteamId64, const FAuthResponseBP& AuthResponseBP = FAuthResponseBP(), const FLootLockerSessionResponse& Delegate = FLootLockerSessionResponse());
    static void StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnCompletedRequestBP = FAppleSessionResponseBP(), const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleSessionResponseDelegate());
	static void RefreshAppleSession(const FString& RefreshToken, const FAppleSessionResponseBP& OnCompletedRequestBP = FAppleSessionResponseBP(), const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleSessionResponseDelegate());
	static void VerifyPlayer(const FString& PlatformToken, const FString& Platform, const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static void EndSession(const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
    static void WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, bool bRemember, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& LootLockerWhiteLabelLoginAndSessionResponseDelegateBP = FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP(), const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& LootLockerWhiteLabelLoginAndSessionResponseDelegate = FLootLockerWhiteLabelLoginAndSessionResponseDelegate());
	static void StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnCompletedRequestBP = FLootLockerAppleGameCenterSessionResponseBP(), const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleGameCenterSessionResponseDelegate()); 
	static void RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnCompletedRequestBP = FLootLockerAppleGameCenterSessionResponseBP(), const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleGameCenterSessionResponseDelegate());
	static void StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnCompletedRequestBP = FLootLockerMetaSessionResponseBP(), const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest = FLootLockerMetaSessionResponseDelegate());
	static void RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnCompletedRequestBP = FLootLockerMetaSessionResponseBP(), const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest = FLootLockerMetaSessionResponseDelegate());
	static ULootLockerHttpClient* HttpClient;
private:
	static TMap<FString, FString> DomainKeyHeaders();
};
