// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "LootLockerItemRequestHandler.generated.h"


//==================================================
// Enum Definitions
//==================================================

/// @addtogroup Items
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * Enum for filtering player items on whether they are consumable.
 */
enum class ELootLockerItemConsumableFilter : uint8
{
    All = 0,
    Consumable = 1,
    Not_consumable = 2,
};
/// @}

/// @addtogroup Items
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * The type of an item, determining whether item instances are stackable or individually tracked.
 */
enum class ELootLockerItemType : uint8
{
    /** No filter. Only used when passing an item type to a request. */
    None = 0,
    /** Each granted item is a separate, individually tracked instance. */
    Instanced = 1,
    /** The item is stored as a single entry with a count that can be incremented or decremented. */
    Stackable = 2,
};
/// @}

/// @addtogroup Items
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * The field by which to order a player item list response.
 */
enum class ELootLockerItemSortField : uint8
{
    /** No sorting. The backend defaults to created_at. */
    None = 0,
    /** Order by when the item was created. */
    Created_at = 1,
    /** Order by when the item was last updated. */
    Updated_at = 2,
    /** Order by the source that granted the item. */
    Source = 3,
};
/// @}

/// @addtogroup Items
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * The direction in which to order a player item list response.
 */
enum class ELootLockerItemSortOrder : uint8
{
    /** No explicit order. The backend defaults to descending. */
    None = 0,
    /** Order ascending. */
    Asc = 1,
    /** Order descending. */
    Desc = 2,
};
/// @}

/// @addtogroup Items
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * The kind of reward that was granted as a result of a behaviour.
 */
enum class ELootLockerRewardKind : uint8
{
    /** The reward kind could not be determined. */
    Unknown = 0,
    /** An asset. */
    Asset = 1,
    /** Progression points. */
    Progression_points = 2,
    /** A progression reset. */
    Progression_reset = 3,
    /** A currency. */
    Currency = 4,
    /** A group. */
    Group = 5,
    /** A reward. */
    Reward = 6,
    /** A platform key. */
    Platform_key = 7,
    /** A publisher currency. */
    Publisher_currency = 8,
    /** Publisher progression points. */
    Publisher_progression_points = 9,
    /** Player metadata. */
    Player_metadata = 10,
    /** A file. */
    File = 11,
    /** A Discord role. */
    Discord_role = 12,
    /** An item template. */
    Item_template = 13,
};
/// @}


//==================================================
// Data Type Definitions
//==================================================


/**
 * Represents an item template that can be granted to players.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerItemTemplate
{
    GENERATED_BODY()

    /** The ULID of the item template. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";

    /** The name of the item template. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";

    /** Whether this template is limited (0 for not limited, otherwise the limit). */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Limited = 0;

    /** The type of the item (instanced or stackable). */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerItemType Item_type = ELootLockerItemType::None;

    /** Whether this item can be consumed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Consumable = false;

    /** Whether instances of this item can be deleted by players. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Deletable = false;

    /** When this item template was created. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Created_at = FDateTime(0);

    /** When this item template was last updated. Unset (FDateTime(0)) when the template has never been updated. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Updated_at = FDateTime(0);
};

/**
 * Represents a single item (inventory entry) owned by a player.
 *
 * This represents an item granted from an item template. It is unrelated to the asset-based
 * inventory API (FLootLockerInventory, GetInventory, ListPlayerInventory), which deals with
 * assets and asset instances.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInventoryItem
{
    GENERATED_BODY()

    /** The ULID of this specific inventory item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";

    /** The legacy integer id of the player that owns this item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Player_id = 0;

    /** The ULID of the item template that this item is based on. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_template_id = "";

    /** The type of the item (instanced or stackable). */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerItemType Item_type = ELootLockerItemType::None;

    /** Whether this item can be consumed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Consumable = false;

    /** Whether this item can be deleted by the player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Deletable = false;

    /** How many of this item the stack holds. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Count = 0;

    /** How this item was acquired. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Source = "";

    /** The name of the item template this item is based on. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";

    /** When this item was acquired. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Created_at = FDateTime(0);

    /** When this item was last updated. Unset (FDateTime(0)) when the item has never been updated. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Updated_at = FDateTime(0);

    /** The free-form metadata for this item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMetadataEntry> Metadata;
};

/**
 * Represents an item that was granted as a result of consuming an item.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGrantedItem
{
    GENERATED_BODY()

    /** The ULID of the granted reward. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Source_id = "";

    /** How many of the item were granted. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Count = 0;

    /** The kind of reward that was granted. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRewardKind Type = ELootLockerRewardKind::Unknown;

    /** The name of the granted reward. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";

    /** The code of the granted reward. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
};


//==================================================
// Request Definitions
//==================================================


/**
 * Request to consume one or more of an item.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConsumeInventoryItemRequest
{
    GENERATED_BODY()

    /**
     The number of items to consume. Defaults to 1 when omitted/unset. To consume an entire stack,
     pass the item's current count.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Count = 1;
};

/**
 * Request to split a stackable item into two stacks.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSplitInventoryItemStackRequest
{
    GENERATED_BODY()

    /** How many items to move to the new stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Count = 0;
};

/**
 * Request to merge two item stacks into one.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerMergeInventoryItemStacksRequest
{
    GENERATED_BODY()

    /** The ULID of the item stack to take items from. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Source_inventory_id = "";

    /** The ULID of the item stack that will receive the items. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Target_inventory_id = "";
};


//==================================================
// Response Definitions
//==================================================


/**
 * Response for listing item templates.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListItemTemplatesResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** List of item templates according to the requested pagination. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerItemTemplate> Items;

    /** Pagination information for the item templates returned. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
};

/**
 * Response for listing a player's inventory items.
 *
 * Operates on items and item templates. This is unrelated to the asset-based inventory API
 * (GetInventory, ListPlayerInventory), which deals with assets and asset instances.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListPlayerInventoryItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** List of the player's items according to the requested filters and pagination. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerInventoryItem> Items;

    /** Pagination information for the items returned. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;

    /**
     * Populate convenience structures (parsed metadata) from the raw response.
     */
    void PopulateConvenienceStructures();
};

/**
 * Response for getting a single player inventory item.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGetPlayerInventoryItemResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The ULID of this specific inventory item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";

    /** The legacy integer id of the player that owns this item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Player_id = 0;

    /** The ULID of the item template that this item is based on. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_template_id = "";

    /** The type of the item (instanced or stackable). */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerItemType Item_type = ELootLockerItemType::None;

    /** Whether this item can be consumed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Consumable = false;

    /** Whether this item can be deleted by the player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Deletable = false;

    /** How many of this item the stack holds. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Count = 0;

    /** How this item was acquired. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Source = "";

    /** When this item was acquired. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Created_at = FDateTime(0);

    /** When this item was last updated. Unset (FDateTime(0)) when the item has never been updated. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Updated_at = FDateTime(0);

    /** The item template that this item is based on. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerItemTemplate Template;

    /** The free-form metadata for this item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMetadataEntry> Metadata;

    /**
     * Populate convenience structures (parsed metadata) from the raw response.
     */
    void PopulateConvenienceStructures();
};

/**
 * Response for consuming one or more of an item.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConsumePlayerInventoryItemResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** Whether the item was consumed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Consumed = false;

    /** Any items granted as a result of consuming the item. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerGrantedItem> Granted;
};

/**
 * Response for splitting an item stack.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSplitInventoryItemStackResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The ULID of the newly created item stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/**
 * Response for merging two item stacks. Empty unless the request failed.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerMergeInventoryItemStacksResponse : public FLootLockerResponse
{
    GENERATED_BODY()
};


//==================================================
// Delegate Definitions
//==================================================

/// @addtogroup Items
/// @{
/**
 * C++ response delegate for listing item templates.
 */
DECLARE_DELEGATE_OneParam(FLootLockerListItemTemplatesResponseDelegate, FLootLockerListItemTemplatesResponse);

/**
 * C++ response delegate for listing player items.
 */
DECLARE_DELEGATE_OneParam(FLootLockerListPlayerInventoryItemsResponseDelegate, FLootLockerListPlayerInventoryItemsResponse);

/**
 * C++ response delegate for getting a player item.
 */
DECLARE_DELEGATE_OneParam(FLootLockerGetPlayerInventoryItemResponseDelegate, FLootLockerGetPlayerInventoryItemResponse);

/**
 * C++ response delegate for consuming a player item.
 */
DECLARE_DELEGATE_OneParam(FLootLockerConsumePlayerInventoryItemResponseDelegate, FLootLockerConsumePlayerInventoryItemResponse);

/**
 * C++ response delegate for splitting an item stack.
 */
DECLARE_DELEGATE_OneParam(FLootLockerSplitInventoryItemStackResponseDelegate, FLootLockerSplitInventoryItemStackResponse);

/**
 * C++ response delegate for merging item stacks.
 */
DECLARE_DELEGATE_OneParam(FLootLockerMergeInventoryItemStacksResponseDelegate, FLootLockerMergeInventoryItemStacksResponse);


//==================================================
// API Class Definition
//==================================================

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerItemRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerItemRequestHandler() {};

    static FString ListItemTemplates(const FLootLockerPlayerData& PlayerData, int32 PerPage, int32 Page, const FLootLockerListItemTemplatesResponseDelegate& OnCompletedRequest);

    static FString ListPlayerInventoryItems(const FLootLockerPlayerData& PlayerData, int32 PerPage, int32 Page, const FString& Name, ELootLockerItemType ItemType, ELootLockerItemConsumableFilter ConsumableFilter, ELootLockerItemSortField Sort, ELootLockerItemSortOrder Order, const FLootLockerListPlayerInventoryItemsResponseDelegate& OnCompletedRequest);

    static FString GetPlayerInventoryItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerGetPlayerInventoryItemResponseDelegate& OnCompletedRequest);

    static FString DeletePlayerInventoryItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerDefaultDelegate& OnCompletedRequest);

    static FString ConsumePlayerInventoryItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerConsumeInventoryItemRequest& Request, const FLootLockerConsumePlayerInventoryItemResponseDelegate& OnCompletedRequest);

    static FString SplitPlayerInventoryItemStack(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerSplitInventoryItemStackRequest& Request, const FLootLockerSplitInventoryItemStackResponseDelegate& OnCompletedRequest);

    static FString MergePlayerInventoryItemStacks(const FLootLockerPlayerData& PlayerData, const FLootLockerMergeInventoryItemStacksRequest& Request, const FLootLockerMergeInventoryItemStacksResponseDelegate& OnCompletedRequest);
};