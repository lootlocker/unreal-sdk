// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerAuthenticationRequestHandler.generated.h"

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
struct FLootLockerLoginResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker Login Response")
	int32 game_id;
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
struct FLootLockerBaseAuthRequest : public FLootLockerErrorData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString email;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString password;
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
struct FLootLockerLevelThresholds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 current;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool current_is_prestige;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 next;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool next_is_prestige;
};


USTRUCT(BlueprintType)
struct FLootLockerAuthenticationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool seen_before;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_grant_notifications;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_deactivation_notifications;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerLevelThresholds level_thresholds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString session_token;
};



USTRUCT(BlueprintType)
struct FLootLockerAuthenticationDefaultResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthResponseBP, FLootLockerAuthenticationResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthDefaultResponseBP, FLootLockerAuthenticationDefaultResponse, AuthVar);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLoginResponseDelegateBP, FLootLockerLoginResponse, AuthVar);
DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FLootLockerAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultAuthenticationResponse, FLootLockerAuthenticationDefaultResponse);
DECLARE_DELEGATE_OneParam(FLootLockerLoginResponseDelegate, FLootLockerLoginResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API ULootLockerAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerAuthenticationRequestHandler();

public:
	static void Signup(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP = FLootLockerLoginResponseDelegateBP(), const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static void Login(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnCompletedRequestBP = FLootLockerLoginResponseDelegateBP(), const FLootLockerLoginResponseDelegate& OnCompletedRequest = FLootLockerLoginResponseDelegate());
	static void GuestLogin(const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void WhiteLabelStartSession(const FString& Email, const FString& Password, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static void EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static ULootLockerHttpClient* HttpClient;
};
