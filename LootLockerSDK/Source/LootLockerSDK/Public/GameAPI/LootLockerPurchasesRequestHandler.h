// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerPurchasesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerActivateRentalAssetResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int time_left = 0;
};

/**
 * 
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogItemAndQuantityPair
{
    GENERATED_BODY()
    /**
     * The unique listing id of the catalog item to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;
    /**
     * The quantity of the specified item to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Quantity = 0;
};

/**
 * 
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPurchaseCatalogItemRequest
{
    GENERATED_BODY()
    /**
     * The id of the wallet to be used for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
    /**
     * A list of items to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogItemAndQuantityPair> Items;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRedeemAppleAppStorePurchaseForPlayerRequest
{
    GENERATED_BODY()
    /**
     * Whether or not to use the app store sandbox for this redemption
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Sandboxed = false;
    /**
     * The id of the transaction successfully made towards the Apple App Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Transaction_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRedeemAppleAppStorePurchaseForClassRequest : public FLootLockerRedeemAppleAppStorePurchaseForPlayerRequest
{
    GENERATED_BODY()
    /**
     * The id of the class to redeem this transaction for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Class_id = 0;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRedeemGooglePlayStorePurchaseForPlayerRequest
{
    GENERATED_BODY()
    /**
     * The id of the product that this redemption refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Product_id;
    /**
     * The token from the purchase successfully made towards the Google Play Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Purchase_token;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRedeemGooglePlayStorePurchaseForClassRequest : public FLootLockerRedeemGooglePlayStorePurchaseForPlayerRequest
{
    GENERATED_BODY()
    /**
     * The id of the class to redeem this purchase for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Class_id = 0;
};

/**
 * Possible statuses a Steam Purchase can have
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerSteamPurchaseRedemptionStatus : uint8
{
    Init = 0,
    Approved = 1,
    Succeeded = 2,
    Failed = 3,
    Refunded = 4,
    PartialRefund = 5,
    ChargedBack = 6,
    RefundedSuspectedFraud = 7,
    RefundedFriendlyFraud = 8,
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBeginSteamPurchaseRedemptionRequest
{
    GENERATED_BODY()
    /**
     * Id of the Steam User that is making the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Steam_id;
    /**
     * The currency to use for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency;
    /**
     * The language to use for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Language;
    /**
     * The LootLocker Catalog Item Id for the item you wish to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_item_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBeginSteamPurchaseRedemptionForClassRequest : public FLootLockerBeginSteamPurchaseRedemptionRequest
{
    GENERATED_BODY()
    /**
     * Id of the class to make the purchase for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Class_id = 0;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBeginSteamPurchaseRedemptionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Was the purchase redemption process started successfully
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool isSuccess = false;
    /**
     * The id of the entitlement this purchase relates to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerQuerySteamPurchaseRedemptionStatusRequest
{
    GENERATED_BODY()
    /**
     * The id of the entitlement to check the status for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerQuerySteamPurchaseRedemptionStatusResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The status of the steam purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerSteamPurchaseRedemptionStatus Status = ELootLockerSteamPurchaseRedemptionStatus::Init;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFinalizeSteamPurchaseRedemptionRequest
{
    GENERATED_BODY()
    /**
     * The id of the entitlement to finalize the purchase for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_id;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FActivateRentalAssetResponseDelegateBP, FLootLockerActivateRentalAssetResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerBeginSteamPurchaseRedemptionDelegateBP, FLootLockerBeginSteamPurchaseRedemptionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP, FLootLockerQuerySteamPurchaseRedemptionStatusResponse, Response);
DECLARE_DELEGATE_OneParam(FActivateRentalAssetResponseDelegate, FLootLockerActivateRentalAssetResponse);
DECLARE_DELEGATE_OneParam(FLootLockerBeginSteamPurchaseRedemptionDelegate, FLootLockerBeginSteamPurchaseRedemptionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerQuerySteamPurchaseRedemptionStatusDelegate, FLootLockerQuerySteamPurchaseRedemptionStatusResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPurchasesRequestHandler : public UObject
{
    GENERATED_BODY()
public:

    static void ActivateRentalAsset(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP = FActivateRentalAssetResponseDelegateBP(), const FActivateRentalAssetResponseDelegate& OnCompletedRequest = FActivateRentalAssetResponseDelegate());

    static void PurchaseCatalogItems(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const TArray<FLootLockerCatalogItemAndQuantityPair>& ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static void RedeemAppleAppStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const bool Sandboxed = false, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static void RedeemAppleAppStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& TransactionId, const bool Sandboxed = false, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static void RedeemGooglePlayStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static void RedeemGooglePlayStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static void BeginSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedBP = FLootLockerBeginSteamPurchaseRedemptionDelegateBP(), const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted = FLootLockerBeginSteamPurchaseRedemptionDelegate());

    static void BeginSteamPurchaseRedemptionForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedBP = FLootLockerBeginSteamPurchaseRedemptionDelegateBP(), const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted = FLootLockerBeginSteamPurchaseRedemptionDelegate());

    static void QuerySteamPurchaseRedemptionStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedBP = FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP(), const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompleted = FLootLockerQuerySteamPurchaseRedemptionStatusDelegate());

    static void FinalizeSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());
public:
    ULootLockerPurchasesRequestHandler();

    static ULootLockerHttpClient* HttpClient;
};
