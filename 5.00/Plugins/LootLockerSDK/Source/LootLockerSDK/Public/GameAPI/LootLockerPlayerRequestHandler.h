// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerPlayerRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerBalanceResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	float balance = .0f;
};

USTRUCT(BlueprintType)
struct FLootLockerDlcResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> dlcs;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerInfoResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerLevelThresholds level_thresholds;
};
USTRUCT(BlueprintType)
struct FLootLockerRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_rental = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active;
};
USTRUCT(BlueprintType)
struct FLootLockerInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerRental rental;
};
USTRUCT(BlueprintType)
struct FLootLockerInventoryResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerInventory> inventory;
};
USTRUCT(BlueprintType)
struct FLootLockerUniversalAsset {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 universal_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerRental rental;
};
USTRUCT(BlueprintType)
struct FLootLockerUniversalAssetsResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerUniversalAsset> global_assets;
};
USTRUCT(BlueprintType)
struct FLootLockerPlayerLevel {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp_threshold = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerXp {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 previous = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 current = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerSubmitXpResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerXp xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerLevel> levels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_grant_notifications = false;
};
USTRUCT(BlueprintType)
struct FLootLockerSubmitXpRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 points = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerObjects
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString reason;
};
USTRUCT(BlueprintType)
struct FLootLockerPlayerAssetNotificationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerObjects> objects;
};

USTRUCT(BlueprintType)
struct FLootLockerNameResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerNameRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FPInfoResponseBP, FLootLockerPlayerInfoResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPInventoryResponseBP, FLootLockerInventoryResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPUniversalAssetsResponseBP, FLootLockerUniversalAssetsResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPSubmitResponseBP, FLootLockerSubmitXpResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPAssetNotificationResponseBP, FLootLockerPlayerAssetNotificationResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPBalanceResponseBP, FLootLockerBalanceResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDlcResponseBP, FLootLockerDlcResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPNameResponseBP, FLootLockerNameResponse, Value);


DECLARE_DELEGATE_OneParam(FLootLockerPlayerInformationResponse, FLootLockerPlayerInfoResponse);

DECLARE_DELEGATE_OneParam(FInventoryResponse, FLootLockerInventoryResponse);

DECLARE_DELEGATE_OneParam(FUniversalAssetsResponse, FLootLockerUniversalAssetsResponse);

DECLARE_DELEGATE_OneParam(FSubmitXpResponse, FLootLockerSubmitXpResponse);

DECLARE_DELEGATE_OneParam(FLootLockerAssetNotificationResponse, FLootLockerPlayerAssetNotificationResponse);

DECLARE_DELEGATE_OneParam(FPBalanceResponse, FLootLockerBalanceResponse);

DECLARE_DELEGATE_OneParam(FPDlcResponse, FLootLockerDlcResponse);

DECLARE_DELEGATE_OneParam(FPNameResponse, FLootLockerNameResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPlayerRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerPlayerRequestHandler();
	static void GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP = FPInfoResponseBP(), const FLootLockerPlayerInformationResponse& OnCompletedRequest = FLootLockerPlayerInformationResponse());
	static void GetInventory(const FPInventoryResponseBP& onCompletedRequestBP = FPInventoryResponseBP(), const FInventoryResponse& onCompletedRequest = FInventoryResponse());
	static void GetUniversalAssets(const FPUniversalAssetsResponseBP& OnCompletedRequestBP = FPUniversalAssetsResponseBP(), const FUniversalAssetsResponse& OnCompletedRequest = FUniversalAssetsResponse());
	
	static void SubmitXp(int points, const FPSubmitResponseBP& onCompletedRequestBP = FPSubmitResponseBP(), const FSubmitXpResponse& onCompletedRequest = FSubmitXpResponse());
	static void GetOtherPlayerInfo(FLootLockerGetRequests getRequests, const FPInfoResponseBP& onCompletedRequestBP = FPInfoResponseBP(), const FLootLockerPlayerInformationResponse& onCompletedRequest = FLootLockerPlayerInformationResponse());
	static void CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& onCompletedRequestBP = FPAssetNotificationResponseBP(), const FLootLockerAssetNotificationResponse& onCompletedRequest = FLootLockerAssetNotificationResponse());
	static void CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& onCompletedRequestBP= FPAssetNotificationResponseBP(), const FLootLockerAssetNotificationResponse& onCompletedRequest = FLootLockerAssetNotificationResponse());
	static void GetCurrencyBalance(const FPBalanceResponseBP& onCompletedRequestBP = FPBalanceResponseBP(), const FPBalanceResponse& onCompletedRequest = FPBalanceResponse());
	static void InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP = FPDlcResponseBP(), const FPDlcResponse& OnCompletedRequest = FPDlcResponse());
	static void SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void SetPlayerName(FString name, const FPNameResponseBP& OnCompletedRequestBP = FPNameResponseBP(), const FPNameResponse& OnCompletedRequest = FPNameResponse());
	static void GetPlayerName(const FPNameResponseBP& OnCompletedRequestBP = FPNameResponseBP(), const FPNameResponse& OnCompletedRequest = FPNameResponse());

public:
	static ULootLockerHttpClient* HttpClient;
};
