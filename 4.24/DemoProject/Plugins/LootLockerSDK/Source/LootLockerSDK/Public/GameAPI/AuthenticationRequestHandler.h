// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootLockerConfig.h"
#include "HttpClient.h"
#include "JsonObjectConverter.h"
#include "AuthenticationRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAuthenticationRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString player_identifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;
};

USTRUCT(BlueprintType)
struct FVerificationRequest
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
struct FLevelThresholds
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
struct FAuthenticationResponse : public FLootLockerResponse
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
	FLevelThresholds level_thresholds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString session_token;
};



USTRUCT(BlueprintType)
struct FAuthenticationDefaultResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthResponseBP, FAuthenticationResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthDefaultResponseBP, FAuthenticationDefaultResponse, AuthVar);
DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultAuthenticationResponse, FAuthenticationDefaultResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API UAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	UAuthenticationRequestHandler();

public:
	static void StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static void EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static UHttpClient* HttpClient;
};
