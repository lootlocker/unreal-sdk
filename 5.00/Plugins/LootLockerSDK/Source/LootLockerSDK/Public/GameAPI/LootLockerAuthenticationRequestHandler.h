// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerAuthenticationRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerAuthenticationRequest
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
	bool development_mode = false;
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
	FString session_token;
};



USTRUCT(BlueprintType)
struct FLootLockerAuthenticationDefaultResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthResponseBP, FLootLockerAuthenticationResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthDefaultResponseBP, FLootLockerAuthenticationDefaultResponse, AuthVar);
DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FLootLockerAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultAuthenticationResponse, FLootLockerAuthenticationDefaultResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API ULootLockerAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerAuthenticationRequestHandler();

public:
	static void StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static void EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static ULootLockerHttpClient* HttpClient;
};
