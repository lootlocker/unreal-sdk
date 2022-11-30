// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerAuthenticationRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerSignupRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	FString password;
};

USTRUCT(BlueprintType)
struct FLootLockerWhiteLabelLoginRequest
{
	GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
    FString email;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
    FString password;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login")
	bool remember = false;
};

USTRUCT(BlueprintType)
struct FLootLockerLoginResponse : public FLootLockerResponse
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
struct FLootLockerErrorData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Error")
	FString message;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Error")
	FString error;
};

USTRUCT(BlueprintType)
struct FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode = false;
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
struct FLootLockerWhiteLabelAuthRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString token;
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
struct FLootLockerXboxSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString xbox_user_token;
};

USTRUCT(BlueprintType)
struct FLootLockerAppleSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString apple_authorization_code;
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshAppleSessionRequest : public FLootLockerBaseAuthRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString refresh_token;
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
struct FLootLockerAuthenticationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 player_id = 0;
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
struct FLootLockerAuthenticationDefaultResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthResponseBP, FLootLockerAuthenticationResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAppleSessionResponseBP, FLootLockerAppleSessionResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthDefaultResponseBP, FLootLockerAuthenticationDefaultResponse, AuthVar);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLoginResponseDelegateBP, FLootLockerLoginResponse, AuthVar);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerVerifySessionResponseBP, FLootLockerWhiteLabelVerifySessionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FLootLockerAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerAppleSessionResponseDelegate, FLootLockerAppleSessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultAuthenticationResponse, FLootLockerAuthenticationDefaultResponse);
DECLARE_DELEGATE_OneParam(FLootLockerLoginResponseDelegate, FLootLockerLoginResponse);
DECLARE_DELEGATE_OneParam(FLootLockerWhiteLabelVerifySessionDelegate, FLootLockerWhiteLabelVerifySessionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultDelegate, FLootLockerResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API ULootLockerAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerAuthenticationRequestHandler();

public:
	static void WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP = FLootLockerLoginResponseDelegateBP(), const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static void WhiteLabelLogin(const FString& Email, const FString& Password, const bool Remember, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP = FLootLockerLoginResponseDelegateBP(), const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static void GuestLogin(const FString& playerIdentifier, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void WhiteLabelStartSession(const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void WhiteLabelVerifySession(const FLootLockerVerifySessionResponseBP& OnCompletedRequestBP = FLootLockerVerifySessionResponseBP(), const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest = FLootLockerWhiteLabelVerifySessionDelegate());
	static void WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static void WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompletedRequest = FLootLockerDefaultDelegate());
	static void StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnCompletedRequestBP = FAppleSessionResponseBP(), const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleSessionResponseDelegate());
	static void RefreshAppleSession(const FString& RefreshToken, const FAppleSessionResponseBP& OnCompletedRequestBP = FAppleSessionResponseBP(), const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest = FLootLockerAppleSessionResponseDelegate());
	static void VerifyPlayer(const FString& PlatformToken, const FString& Platform, const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static void EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static ULootLockerHttpClient* HttpClient;
};
