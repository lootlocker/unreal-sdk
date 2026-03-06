// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
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
    FString Catalog_listing_id = "";
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
    FString Wallet_id = "";
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
    FString Transaction_id = "";
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
    FString Product_id = "";
    /**
     * The token from the purchase successfully made towards the Google Play Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Purchase_token = "";
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
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRedeemEpicStorePurchaseForPlayerRequest
{
    GENERATED_BODY()
    /**
     * The epic account id of the account that this purchase was made for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Account_id = "";
    /**
     * This is the token from epic used to allow the LootLocker backend to verify ownership of the specified entitlements. This is sometimes referred to as the Server Auth Ticket or Auth Token depending on your Epic integration.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Bearer_token = "";
    /**
     * The ids of the purchased entitlements that you wish to redeem
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Entitlement_ids;
    /**
     * The Sandbox Id configured for the game making the purchase (this is the sandbox id from your epic online service configuration)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Sandbox_id = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRedeemEpicStorePurchaseForCharacterRequest : public FLootLockerRedeemEpicStorePurchaseForPlayerRequest
{
    GENERATED_BODY()
    /**
     * The ulid of the character to redeem this purchase for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Character_id = "";
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
    FString Steam_id = "";
    /**
     * The currency to use for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency = "";
    /**
     * The language to use for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Language = "";
    /**
     * The LootLocker Catalog Item Id for the item you wish to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_item_id = "";
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
    FString Entitlement_id = "";
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
    FString Entitlement_id = "";
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
    FString Entitlement_id = "";
};

/**
 * Possible actions for a player inventory event during a refund
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerRefundInventoryEventAction : uint8
{
    removed = 0,
    skipped = 1,
};

/**
 * Possible kinds of non-reversible rewards in a refund warning
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerRefundNonReversibleRewardKind : uint8
{
    progression_points = 0,
    progression_reset = 1,
};

/**
 * Possible warning types in a refund response
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerRefundWarningDetailType : uint8
{
    non_reversible_rewards = 0,
    insufficient_funds = 1,
    already_refunded = 2,
    refund_failed = 3,
};

USTRUCT(BlueprintType)
struct FLootLockerRefundByEntitlementIdsRequest
{
    GENERATED_BODY()
    /** The IDs of the entitlements to refund */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> entitlement_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerRefundPlayerInventoryEvent
{
    GENERATED_BODY()
    /** The legacy numeric asset ID */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int64 asset_id = 0;
    /** Display name of the asset */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    /** "removed" if the asset was taken back from inventory, "skipped" if it could not be removed */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRefundInventoryEventAction action = ELootLockerRefundInventoryEventAction::removed;
};

USTRUCT(BlueprintType)
struct FLootLockerRefundCurrencyEntry
{
    GENERATED_BODY()
    /** The ULID of the currency */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString currency_id;
    /** Short code identifying the currency (e.g. "gold", "gems") */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString currency_code;
    /** The amount credited or debited, represented as a string to support arbitrary precision */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString amount;
};

USTRUCT(BlueprintType)
struct FLootLockerRefundNonReversibleReward
{
    GENERATED_BODY()
    /** "progression_points": points were added to a progression. "progression_reset": a progression was reset. Additional values may be added in future. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRefundNonReversibleRewardKind kind = ELootLockerRefundNonReversibleRewardKind::progression_points;
    /** The ULID of the progression that was affected */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id;
    /** Display name of the progression */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    /** The number of points granted that cannot be reversed. Only present for kind "progression_points". */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString amount;
};

USTRUCT(BlueprintType)
struct FLootLockerRefundWarningDetail
{
    GENERATED_BODY()
    /**
     * The warning category:
     * non_reversible_rewards: rewards granted that cannot be automatically clawed back.
     * insufficient_funds: the player does not have enough currency balance to cover the clawback.
     * already_refunded: the entitlement was already refunded before this request.
     * refund_failed: the entitlement could not be refunded due to an unexpected error.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRefundWarningDetailType type = ELootLockerRefundWarningDetailType::refund_failed;
    /** Human-readable explanation of the warning */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString message;
    /** The specific rewards that could not be reversed. Only present when type is "non_reversible_rewards". */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRefundNonReversibleReward> rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerRefundWarning
{
    GENERATED_BODY()
    /** The entitlement this warning applies to */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entitlement_id;
    /** One or more warning conditions for this entitlement */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRefundWarningDetail> details;
};

USTRUCT(BlueprintType)
struct FLootLockerRefundByEntitlementIdsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /** Assets that were added or removed from the player's inventory as part of the refund */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRefundPlayerInventoryEvent> player_inventory_events;
    /** Currency amounts credited back to the player's wallet (the purchase price being returned) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRefundCurrencyEntry> currency_refunded;
    /** Currency amounts debited from the player's wallet (currency rewards from the entitlement being reclaimed) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRefundCurrencyEntry> currency_clawback;
    /**
     * Warnings encountered during refund processing, grouped by entitlement.
     * A non-empty warnings array does not mean the refund failed — it means some aspects could not be fully reversed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRefundWarning> warnings;
};

DECLARE_DELEGATE_OneParam(FActivateRentalAssetResponseDelegate, FLootLockerActivateRentalAssetResponse);
DECLARE_DELEGATE_OneParam(FLootLockerBeginSteamPurchaseRedemptionDelegate, FLootLockerBeginSteamPurchaseRedemptionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerQuerySteamPurchaseRedemptionStatusDelegate, FLootLockerQuerySteamPurchaseRedemptionStatusResponse);
DECLARE_DELEGATE_OneParam(FLootLockerRefundByEntitlementIdsDelegate, FLootLockerRefundByEntitlementIdsResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPurchasesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerPurchasesRequestHandler() {};


    static FString ActivateRentalAsset(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest);

    static FString PurchaseCatalogItems(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const TArray<FLootLockerCatalogItemAndQuantityPair>& ItemsToPurchase, const FLootLockerDefaultDelegate& OnCompleted);

    static FString RedeemAppleAppStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const bool Sandboxed = false, const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static FString RedeemAppleAppStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& TransactionId, const bool Sandboxed = false, const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static FString RedeemGooglePlayStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompleted);

    static FString RedeemGooglePlayStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompleted);

    static FString RedeemEpicStorePurchase(const FLootLockerPlayerData& PlayerData, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompleted);

    static FString RedeemEpicStorePurchaseForCharacter(const FLootLockerPlayerData& PlayerData, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompleted);

    static FString RedeemPlayStationStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel = "", const FString& ServiceName = "", const int Environment = -1, const int UseCount = -1, const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static FString RedeemPlayStationStorePurchaseForCharacter(const FLootLockerPlayerData& PlayerData, const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel = "", const FString& ServiceName = "", const int Environment = -1, const int UseCount = -1, const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

    static FString BeginSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted);

    static FString BeginSteamPurchaseRedemptionForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted);

    static FString QuerySteamPurchaseRedemptionStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompleted);

    static FString FinalizeSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerDefaultDelegate& OnCompleted);

    static FString RefundByEntitlementIds(const FLootLockerPlayerData& PlayerData, const TArray<FString>& EntitlementIds, const FLootLockerRefundByEntitlementIdsDelegate& OnCompleted);
};
