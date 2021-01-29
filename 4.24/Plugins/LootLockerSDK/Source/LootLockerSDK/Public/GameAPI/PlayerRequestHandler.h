// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "GameAPI/AuthenticationRequestHandler.h"
#include "GameAPI/AssetsRequestHandler.h"
#include "PlayerRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FBalanceResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	float balance;
};

USTRUCT(BlueprintType)
struct FDlcResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> dlcs;
};

USTRUCT(BlueprintType)
struct FPlayerInfoResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLevelThresholds level_thresholds;
};
USTRUCT(BlueprintType)
struct FRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_rental;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active;
};
USTRUCT(BlueprintType)
struct FInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FRental rental;
};
USTRUCT(BlueprintType)
struct FInventoryResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FInventory> inventory;
};

USTRUCT(BlueprintType)
struct FPlayerLevel {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp_threshold;
};
USTRUCT(BlueprintType)
struct FXp {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 previous;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 current;
};
USTRUCT(BlueprintType)
struct FSubmitXpResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FXp xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FPlayerLevel> levels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_grant_notifications;
};
USTRUCT(BlueprintType)
struct FSubmitXpRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 points;
};
USTRUCT(BlueprintType)
struct FLootLockerObjects
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString reason;
};
USTRUCT(BlueprintType)
struct FPlayerAssetNotificationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerObjects> objects;
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FPInfoResponseBP, FPlayerInfoResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPInventoryResponseBP, FInventoryResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPSubmitResponseBP, FSubmitXpResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPAssetNotificationResponseBP, FPlayerAssetNotificationResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPBalanceResponseBP, FBalanceResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDlcResponseBP, FDlcResponse, Value);


DECLARE_DELEGATE_OneParam(FLootLockerPlayerInformationResponse, FPlayerInfoResponse);

DECLARE_DELEGATE_OneParam(FLootLockerInventoryResponse, FInventoryResponse);

DECLARE_DELEGATE_OneParam(FLootLockerSubmitXpResponse, FSubmitXpResponse);

DECLARE_DELEGATE_OneParam(FLootLockerAssetNotificationResponse, FPlayerAssetNotificationResponse);

DECLARE_DELEGATE_OneParam(FPBalanceResponse, FBalanceResponse);

DECLARE_DELEGATE_OneParam(FPDlcResponse, FDlcResponse);

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
	static void GetCurrencyBalance(const FPBalanceResponseBP& onCompletedRequestBP = FPBalanceResponseBP(), const FPBalanceResponse& onCompletedRequest = FPBalanceResponse());
	static void InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP = FPDlcResponseBP(), const FPDlcResponse& OnCompletedRequest = FPDlcResponse());
	static void SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());

public:
	static UHttpClient* HttpClient;
};
