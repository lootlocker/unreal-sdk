// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerEntitlementRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/*
 * An enum with the supported stores that can generate entitlements
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerEntitlementHistoryListingStore : uint8
{
    None = 0,
    Apple_app_store = 1,
    Google_play_store = 2,
    Steam_store = 3,
    Playstation_network = 4,
    Nintendo_eshop = 5,
    Lootlocker = 6
};

/*
 * Status of the entitlement
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerEntitlementHistoryListingStatus : uint8
{
    None = 0,
    Active = 1,
    Pending = 2,
    Expired = 3,
    Canceled = 4,
    Refunded = 5
};

/*
 * Status of the entitlement
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerEntitlementHistoryListingType : uint8
{
    Undefined = 0,
    One_time_purchase = 1,
    Leaderboard_reward = 2,
    Subscription = 3
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEntitlementHistoryItem
{
    GENERATED_BODY()
    /*
     * When this item was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";

    /*
     * What kind of reward this item is
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_kind = "";

    /*
     * The unique identifier of this specific item
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";

    /*
     * The id of the reward this item is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_id = "";

    /*
     * The id of the catalog item that this item is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_id = "";

    /*
     * Whether this item is purchasable
     */
    bool Purchasable = false;
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEntitlementHistoryMetadata
{
    GENERATED_BODY()
    /*
     * The key of this pair, describes what the value is
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";

    /*
     * The value of this pair, contains the information of the metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Value = "";
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEntitlementHistoryReward
{
    GENERATED_BODY()
    /*
     * When this reward was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";

    /*
     * The id of this entitlement
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_id = "";

    /*
     * The unique identifier of this reward
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEntitlementListing
{
    GENERATED_BODY()
    /*
     * When this entitlement listing was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";

    /*
     * The unique identifier of this entitlement listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";

    /*
     * List of items in this entitlement (items are related to the catalog)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEntitlementHistoryItem> Items;

    /*
     * List of rewards in this entitlement (these are rewards from systems such as leaderboards, progressions, etc.)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEntitlementHistoryReward> Rewards;

    /*
     * Metadata related to this entitlement listing
     * This array consists of key value pairs and contains various pieces of information about the entitlement, such as information from third party stores etc.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEntitlementHistoryMetadata> Metadata;

    /*
     * The status of this entitlement listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerEntitlementHistoryListingStatus Status = ELootLockerEntitlementHistoryListingStatus::None;

    /*
     * Which store (if any) that this entitlement listing relates to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerEntitlementHistoryListingStore Store = ELootLockerEntitlementHistoryListingStore::None;

    /*
     * Which type this entitlement listing is
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerEntitlementHistoryListingType Type = ELootLockerEntitlementHistoryListingType::Undefined;
};

//==================================================
// Response Definitions
//==================================================
/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEntitlementHistoryResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /*
     * List of entitlement history entries
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEntitlementListing> Listings;

    /*
     * Pagination data to use for subsequent requests
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerKeyBasedPagination Pagination;
};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSingleEntitlementResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /*
    * When this entitlement listing was created
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at;
    /*
     * The status of this entitlement listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerEntitlementHistoryListingStatus Status = ELootLockerEntitlementHistoryListingStatus::None;

    /*
     * Which store (if any) that this entitlement listing relates to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerEntitlementHistoryListingStore Store = ELootLockerEntitlementHistoryListingStore::None;

    /*
     * Which type this entitlement listing is
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerEntitlementHistoryListingType Type = ELootLockerEntitlementHistoryListingType::Undefined;
    /*
    * An array of the items connected to this entitlement
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEntitlementHistoryItem> Items;
    /*
    * Metadata of the entitlement
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEntitlementHistoryMetadata> Metadata;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for listing entitlement history
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListEntitlementsResponseBP, FLootLockerEntitlementHistoryResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSingleEntitlementResponseBP, FLootLockerSingleEntitlementResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/**
 * C++ response delegate for listing entitlement history
 */
DECLARE_DELEGATE_OneParam(FLootLockerListEntitlementsResponseDelegate, FLootLockerEntitlementHistoryResponse);
DECLARE_DELEGATE_OneParam(FLootLockerSingleEntitlementResponseDelegate, FLootLockerSingleEntitlementResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerEntitlementRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerEntitlementRequestHandler();
    static void ListEntitlements(int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnCompleteBP = FLootLockerListEntitlementsResponseBP(), const FLootLockerListEntitlementsResponseDelegate& OnComplete = FLootLockerListEntitlementsResponseDelegate());
    static void GetEntitlement(FString EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnCompleteBP = FLootLockerSingleEntitlementResponseBP(), const FLootLockerSingleEntitlementResponseDelegate& OnComplete = FLootLockerSingleEntitlementResponseDelegate());
private:
    static ULootLockerHttpClient* HttpClient;
};
