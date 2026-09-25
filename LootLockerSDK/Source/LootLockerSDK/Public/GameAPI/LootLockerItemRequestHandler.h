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

    /** The legacy integer id of the game this template belongs to. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Game_id = 0;

    /** Whether this template is limited (0 for not limited, otherwise the limit). */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Limited = 0;

    /** The type of the item, either "instanced" or "stackable". */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_type = "";

    /** Whether this item can be consumed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Consumable = false;

    /** Whether instances of this item can be deleted by players. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Deletable = false;

    /** When this item template was created. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";

    /** When this item template was last updated. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";
};

/**
 * Represents a single item (inventory entry) owned by a player.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerItem
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

    /** The type of the item, either "instanced" or "stackable". */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_type = "";

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
    FString Created_at = "";

    /** When this item was last updated. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";

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
    FString Type = "";

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
struct FLootLockerConsumeItemRequest
{
    GENERATED_BODY()

    /** The number of items to consume. Defaults to 1 when omitted/unset. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Count = 1;
};

/**
 * Request to split a stackable item into two stacks.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSplitItemStackRequest
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
struct FLootLockerMergeItemStacksRequest
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
 * Response for listing a player's items.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListPlayerItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** List of the player's items according to the requested filters and pagination. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerItem> Items;

    /** Pagination information for the items returned. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;

    /**
     * Populate convenience structures (parsed metadata) from the raw response.
     */
    void PopulateConvenienceStructures();
};

/**
 * Response for getting a single player item.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGetPlayerItemResponse : public FLootLockerResponse
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

    /** The type of the item, either "instanced" or "stackable". */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_type = "";

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
    FString Created_at = "";

    /** When this item was last updated. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";

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
struct FLootLockerConsumePlayerItemResponse : public FLootLockerResponse
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
struct FLootLockerSplitItemStackResponse : public FLootLockerResponse
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
struct FLootLockerMergeItemStacksResponse : public FLootLockerResponse
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
DECLARE_DELEGATE_OneParam(FLootLockerListPlayerItemsResponseDelegate, FLootLockerListPlayerItemsResponse);

/**
 * C++ response delegate for getting a player item.
 */
DECLARE_DELEGATE_OneParam(FLootLockerGetPlayerItemResponseDelegate, FLootLockerGetPlayerItemResponse);

/**
 * C++ response delegate for consuming a player item.
 */
DECLARE_DELEGATE_OneParam(FLootLockerConsumePlayerItemResponseDelegate, FLootLockerConsumePlayerItemResponse);

/**
 * C++ response delegate for splitting an item stack.
 */
DECLARE_DELEGATE_OneParam(FLootLockerSplitItemStackResponseDelegate, FLootLockerSplitItemStackResponse);

/**
 * C++ response delegate for merging item stacks.
 */
DECLARE_DELEGATE_OneParam(FLootLockerMergeItemStacksResponseDelegate, FLootLockerMergeItemStacksResponse);


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

    static FString ListPlayerItems(const FLootLockerPlayerData& PlayerData, int32 PerPage, int32 Page, const FString& Name, const FString& ItemType, ELootLockerItemConsumableFilter ConsumableFilter, const FString& Sort, const FString& Order, const FLootLockerListPlayerItemsResponseDelegate& OnCompletedRequest);

    static FString GetPlayerItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerGetPlayerItemResponseDelegate& OnCompletedRequest);

    static FString DeletePlayerItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerDefaultDelegate& OnCompletedRequest);

    static FString ConsumePlayerItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerConsumeItemRequest& Request, const FLootLockerConsumePlayerItemResponseDelegate& OnCompletedRequest);

    static FString SplitPlayerItemStack(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerSplitItemStackRequest& Request, const FLootLockerSplitItemStackResponseDelegate& OnCompletedRequest);

    static FString MergePlayerItemStacks(const FLootLockerPlayerData& PlayerData, const FLootLockerMergeItemStacksRequest& Request, const FLootLockerMergeItemStacksResponseDelegate& OnCompletedRequest);
};