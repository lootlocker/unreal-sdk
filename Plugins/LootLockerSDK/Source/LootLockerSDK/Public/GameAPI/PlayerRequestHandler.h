// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "GameAPI/AuthenticationRequestHandler.h"
#include "GameAPI/AssetsRequestHandler.h"
#include "PlayerRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfoResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 account_balance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLevelThresholds level_thresholds;
};
USTRUCT(BlueprintType)
struct FRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool is_rental;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString is_active;
};
USTRUCT(BlueprintType)
struct FInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRental rental;
};
USTRUCT(BlueprintType)
struct FInventoryResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FInventory> inventory;
};

USTRUCT(BlueprintType)
struct FPlayerLevel {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 xp_threshold;
};
USTRUCT(BlueprintType)
struct FXp {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 previous;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 current;
};
USTRUCT(BlueprintType)
struct FSubmitXpResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FXp xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FPlayerLevel> levels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool check_grant_notifications;
};
USTRUCT(BlueprintType)
struct FSubmitXpRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 points;
};
USTRUCT(BlueprintType)
struct FLootLockerObjects
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString reason;
};
USTRUCT(BlueprintType)
struct FPlayerAssetNotificationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLootLockerObjects> objects;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPInfoResponseBP, FPlayerInfoResponse, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPInventoryResponseBP, FInventoryResponse, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPSubmitResponseBP, FSubmitXpResponse, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPAssetNotificationResponseBP, FPlayerAssetNotificationResponse, Value);


DECLARE_DELEGATE_OneParam(FLootLockerPlayerInformationResponse, FPlayerInfoResponse);

DECLARE_DELEGATE_OneParam(FLootLockerInventoryResponse, FInventoryResponse);

DECLARE_DELEGATE_OneParam(FLootLockerSubmitXpResponse, FSubmitXpResponse);

DECLARE_DELEGATE_OneParam(FLootLockerAssetNotificationResponse, FPlayerAssetNotificationResponse);

UCLASS()
class LOOTLOCKERSDK_API UPlayerRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	UPlayerRequestHandler();
	static void GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP = FPInfoResponseBP(), const FLootLockerPlayerInformationResponse& OnCompletedRequest = FLootLockerPlayerInformationResponse());
	static void GetInventory(const FPInventoryResponseBP& onCompletedRequestBP = FPInventoryResponseBP(), const FLootLockerInventoryResponse& onCompletedRequest = FLootLockerInventoryResponse());
	static void SubmitXp(int points, const FPSubmitResponseBP& onCompletedRequestBP = FPSubmitResponseBP(), const FLootLockerSubmitXpResponse& onCompletedRequest = FLootLockerSubmitXpResponse());
	static void GetOtherPlayerInfo(FLootLockerGetRequests getRequests, const FPInfoResponseBP& onCompletedRequestBP = FPInfoResponseBP(), const FLootLockerPlayerInformationResponse& onCompletedRequest = FLootLockerPlayerInformationResponse());
	static void CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& onCompletedRequestBP = FPAssetNotificationResponseBP(), const FLootLockerAssetNotificationResponse& onCompletedRequest = FLootLockerAssetNotificationResponse());
	static void CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& onCompletedRequestBP= FPAssetNotificationResponseBP(), const FLootLockerAssetNotificationResponse& onCompletedRequest = FLootLockerAssetNotificationResponse());

public:
	static FResponseCallback sessionResponse;
	static UHttpClient* HttpClient;
};
