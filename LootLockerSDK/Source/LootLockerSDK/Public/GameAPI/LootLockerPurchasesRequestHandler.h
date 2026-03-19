// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "TimerManager.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LootLockerSDK/Private/Utils/LootLockerUtilities.h"
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

//==================================================
// Async Purchase Types
//==================================================

/**
 * Possible statuses for an async purchase
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerAsyncPurchaseStatus : uint8
{
    Pending = 0,
    Active = 1,
    Failed = 2,
    TimedOut = 3,
    Cancelled = 4,
};

/**
 * Response from initiating an async purchase
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAsyncPurchaseInitiatedResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The id of the entitlement created for this purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_id = "";
};

/**
 * Response from polling the status of an async purchase
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAsyncPurchaseStatusResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The id of the entitlement this status refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_id = "";
    /**
     * The current status of the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerAsyncPurchaseStatus Status = ELootLockerAsyncPurchaseStatus::Pending;
    /**
     * The failure reason. Only populated when status is failed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Error = "";
};

DECLARE_DELEGATE_OneParam(FLootLockerAsyncPurchaseInitiatedDelegate, FLootLockerAsyncPurchaseInitiatedResponse);
DECLARE_DELEGATE_OneParam(FLootLockerAsyncPurchaseStatusDelegate, FLootLockerAsyncPurchaseStatusResponse);

struct FLootLockerAsyncPurchaseProcess
{
    static constexpr int RetryLimit = 5;
    FString EntitlementId = "";
    FString WalletId = "";
    TArray<FLootLockerCatalogItemAndQuantityPair> Items;
    FLootLockerPlayerData PlayerData;
    FDateTime TimeoutTime;
    float PollingIntervalSeconds = 1.0f;
    int Retries = 0;
    bool ShouldCancel = false;
    FTimerHandle AsyncPurchaseProcessTimerHandle;

    FLootLockerAsyncPurchaseProcess() = default;
    FLootLockerAsyncPurchaseProcess(float _PollingIntervalSeconds, float TimeoutAfterMinutes);
};

DECLARE_DELEGATE_OneParam(FActivateRentalAssetResponseDelegate, FLootLockerActivateRentalAssetResponse);
DECLARE_DELEGATE_OneParam(FLootLockerBeginSteamPurchaseRedemptionDelegate, FLootLockerBeginSteamPurchaseRedemptionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerQuerySteamPurchaseRedemptionStatusDelegate, FLootLockerQuerySteamPurchaseRedemptionStatusResponse);
DECLARE_DELEGATE_OneParam(FLootLockerRefundByEntitlementIdsDelegate, FLootLockerRefundByEntitlementIdsResponse);

/**
 * Request to create a Stripe Checkout session for a catalog item
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCreateStripeCheckoutSessionRequest
{
    GENERATED_BODY()
    /**
     * The ULID of the catalog item to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_item_id = "";
};

/**
 * Response from creating a Stripe Checkout session
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCreateStripeCheckoutSessionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The URL of the Stripe-hosted checkout page. Open this in a browser or webview to let the player complete the payment.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString checkout_link = "";
    /**
     * The LootLocker entitlement id tied to this purchase. Use this to track purchase progress via the entitlements endpoint.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entitlement_id = "";
};

DECLARE_DELEGATE_OneParam(FLootLockerCreateStripeCheckoutSessionDelegate, FLootLockerCreateStripeCheckoutSessionResponse);

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

    static FString CreateStripeCheckoutSession(const FLootLockerPlayerData& PlayerData, const FString& CatalogItemId, const FLootLockerCreateStripeCheckoutSessionDelegate& OnCompleted);

    static FString InitiateAsyncPurchase(const FLootLockerPlayerData& PlayerData, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair>& Items, const FLootLockerAsyncPurchaseInitiatedDelegate& OnCompleted);

    static FString GetAsyncPurchaseStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerAsyncPurchaseStatusDelegate& OnCompleted);

    static FString RetryAsyncPurchase(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair>& Items, const FLootLockerAsyncPurchaseInitiatedDelegate& OnCompleted);

    static FString StartAsyncPurchasePolling(const FLootLockerPlayerData& PlayerData, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair>& Items, const FLootLockerAsyncPurchaseStatusDelegate& OnStatusUpdate, const FLootLockerAsyncPurchaseStatusDelegate& OnComplete, float PollingIntervalSeconds = 1.0f, float TimeoutAfterMinutes = 5.0f);

    static void CancelAsyncPurchasePolling(const FString& ProcessID);

    static FString ContinualAsyncPurchasePollAction(const FString& ProcessID, const FLootLockerAsyncPurchaseStatusDelegate& OnStatusUpdate, const FLootLockerAsyncPurchaseStatusDelegate& OnComplete);

    static void KillAsyncPurchaseProcess(const FString& ProcessID);

protected:
    static FString GetAsyncPurchaseStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const LLAPI<FLootLockerAsyncPurchaseStatusResponse>::FResponseInspectorCallback& OnCompleted);
    static void SetAsyncPurchaseTimer(FTimerHandle& TimerHandle, const FTimerDelegate& Delegate, float Time);
    static void ClearAsyncPurchaseTimer(FTimerHandle& TimerHandle);

private:
    static TMap<FString, FLootLockerAsyncPurchaseProcess> AsyncPurchaseProcesses;
};

//==================================================
// Async Blueprint Delegate Definitions
//==================================================

/**
 * Multicast delegate for events triggered from the async purchase polling node
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLootLockerAsyncPurchasePollingMulticastDelegate, FString, ProcessID, FLootLockerAsyncPurchaseStatusResponse, Response);

//==================================================
// Async Blueprint Node Definitions
//==================================================

UCLASS()
class ULootLockerAsyncPollAsyncPurchase : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()
public:
    /**
     * Initiate an async purchase and automatically poll until it reaches a terminal state.
     * While pending, OnPending is triggered each poll. On completion, OnActive or OnFailed is triggered.
     *
     * @param WorldContextObject Non input: Automatic context for async node
     * @param ForPlayerWithUlid Optional: Execute for the player with this ulid. Leave empty for the default player.
     * @param WalletId The id of the wallet to use for the purchase
     * @param Items The catalog items with quantities to purchase
     * @param PollingIntervalSeconds Optional: How often to poll in seconds (minimum 1)
     * @param TimeoutAfterMinutes Optional: How many minutes before the process times out
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "LootLocker Methods | Purchases", WorldContext = "WorldContextObject", AdvancedDisplay = "PollingIntervalSeconds,TimeoutAfterMinutes,ForPlayerWithUlid", PollingIntervalSeconds = 1.0f, TimeoutAfterMinutes = 5.0f, ForPlayerWithUlid = ""))
    static LOOTLOCKERSDK_API ULootLockerAsyncPollAsyncPurchase* AsyncPollAsyncPurchase(UObject* WorldContextObject, FString ForPlayerWithUlid, FString WalletId, TArray<FLootLockerCatalogItemAndQuantityPair> Items, float PollingIntervalSeconds, float TimeoutAfterMinutes);

    /** Triggered on each poll while the purchase is still pending */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncPurchasePollingMulticastDelegate OnPending;
    /** Triggered when the purchase has completed successfully (status = Active) */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncPurchasePollingMulticastDelegate OnActive;
    /** Triggered when the purchase has failed (status = Failed) */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncPurchasePollingMulticastDelegate OnFailed;
    /** Triggered if the process times out */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncPurchasePollingMulticastDelegate OnTimedOut;
    /** Triggered if the process was cancelled using CancelAsyncPurchasePolling */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncPurchasePollingMulticastDelegate OnCancelled;

    LOOTLOCKERSDK_API virtual void Activate() override;

protected:
    FString ForPlayerWithUlid = "";
    FString ProcessID = "";
    FString WalletId = "";
    TArray<FLootLockerCatalogItemAndQuantityPair> Items;
    float PollingIntervalInSeconds = 1.0f;
    float TimeoutAfterMinutes = 5.0f;
};
