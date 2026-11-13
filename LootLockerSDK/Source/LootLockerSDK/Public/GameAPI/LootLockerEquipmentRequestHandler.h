// Copyright LootLocker AB

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerEquipmentRequestHandler.generated.h"

//==================================================
// Request Definitions
//==================================================

/**
 * Request to equip an inventory stack into an equipment slot on an entity.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentEquipRequest
{
    GENERATED_BODY()

    /** The entity the loadout hangs off. Only "player" is resolvable today. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entity_type = "player";

    /** The ULID of the entity. For the "player" entity type this is the player ULID. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString source_id = "";

    /** The ULID of the equipment slot to equip into. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString slot_id = "";

    /** The ULID of the inventory stack to equip. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString inventory_id = "";

    /** Optional: The amount to equip. Left at 0 the whole stack is used, capped by the slot's max_items. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 count = 0;

    /** Optional: Whether a stack already occupying the slot should be auto-unequipped. Pass false to conflict instead. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool replace = true;
};

//==================================================
// Data Definitions
//==================================================

/**
 * A summary of the item template an equipped stack was created from.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentItemTemplate
{
    GENERATED_BODY()

    /** The ULID of the item template. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";

    /** The name of the item template. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";

    /** Whether an inventory row of this template may be deleted. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool deletable = false;
};

/**
 * An equipment slot definition belonging to an equipment group.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentSlot
{
    GENERATED_BODY()

    /** The ULID of the slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";

    /** The stable machine key of the slot, unique within its group. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString slot_key = "";

    /** The display name of the slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";

    /** The maximum number of items the slot holds. Equipping more than this splits the stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 max_items = 0;

    /** The tags an item template must share at least one of for the slot to accept it. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> tags;
};

/**
 * A stack currently attached to an equipment slot.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentStack
{
    GENERATED_BODY()

    /** The equipment entry ULID. Use this to unequip the stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entry_id = "";

    /** The ULID of the inventory row holding the equipped items. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString inventory_id = "";

    /** The number of items currently in the slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 count = 0;

    /** A summary of the item template this stack was created from. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerEquipmentItemTemplate item_template;

    /**
     * False when the item template's tags and the slot's tags no longer intersect. The stack
     * stays attached and is flagged rather than silently removed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool valid = true;

    /** True when the attached count exceeds the slot's max_items, for example after max_items was lowered. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool over_limit = false;

    /** When the stack was attached to the slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString mounted_at = "";
};

/**
 * An equipment slot together with the stack attached to it, if any.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentSlotAndStack
{
    GENERATED_BODY()

    /** The slot definition. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerEquipmentSlot slot;

    /** The attached stack. Null when the slot is empty; check HasStack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerEquipmentStack stack;

    /** Whether a stack is attached to this slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool HasStack = false;
};

/**
 * An equipment group as reported by a loadout read. A group is bound to one entity type and owns its slots.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentGroup
{
    GENERATED_BODY()

    /** The ULID of the group. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";

    /** The stable machine key of the group. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString group_key = "";

    /** The display name of the group. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";

    /** The entity type this group serves. Only "player" is resolvable today. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entity_type = "";

    /** The group's slots with the stack attached to each. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEquipmentSlotAndStack> slots;
};

/**
 * An unequipped inventory stack that a slot would accept.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentCandidate
{
    GENERATED_BODY()

    /** The ULID of the inventory stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString inventory_id = "";

    /** A summary of the item template this stack was created from. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerEquipmentItemTemplate item_template;

    /** The item type of the stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString item_type = "";

    /** The number of items in the inventory stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 count = 0;

    /** The amount an equip would attach right now, which is count capped at the slot's max_items. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 equippable = 0;
};

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing a player's loadout: the groups for the entity's type, each with its slots and attached stacks.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentLoadoutResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The equipment groups serving the entity's type, paged over groups. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEquipmentGroup> groups;

    /** Pagination information for the groups. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination pagination;
};

/**
 * Response containing the inventory stacks that a slot would accept for the calling player.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentSlotCandidatesResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The slot the candidates were listed for. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerEquipmentSlot slot;

    /** The caller's unequipped stacks whose item template shares a tag with the slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerEquipmentCandidate> candidates;

    /** Pagination information for the candidates. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination pagination;
};

/**
 * Response describing what an equip did.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerEquipmentEquipResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The equipment entry ULID, used to unequip the stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entry_id = "";

    /** The ULID of the slot the stack was equipped into. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString slot_id = "";

    /** The ULID of the attached inventory row, which is a fresh split row when the stack was split. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString inventory_id = "";

    /** The amount now attached to the slot. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 equipped = 0;

    /** The amount left on the source inventory stack. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 remainder = 0;

    /** The entry that was auto-unequipped to make room, if any. Empty when no stack was replaced. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString replaced_entry_id = "";
};

/// @addtogroup Equipment
/// @{
/** C++ response callback delegate; receives an @ref FLootLockerEquipmentLoadoutResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerEquipmentLoadoutResponseDelegate, FLootLockerEquipmentLoadoutResponse);

/** C++ response callback delegate; receives an @ref FLootLockerEquipmentSlotCandidatesResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerEquipmentSlotCandidatesResponseDelegate, FLootLockerEquipmentSlotCandidatesResponse);

/** C++ response callback delegate; receives an @ref FLootLockerEquipmentEquipResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerEquipmentEquipResponseDelegate, FLootLockerEquipmentEquipResponse);
/// @}

UCLASS()
class LOOTLOCKERSDK_API ULLEquipmentRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULLEquipmentRequestHandler() {};

    static FString GetLoadout(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerEquipmentLoadoutResponseDelegate& OnCompletedRequest);
    static FString GetEntityLoadout(const FLootLockerPlayerData& PlayerData, const FString& EntityType, const FString& SourceId, int32 Page, int32 PerPage, const FLootLockerEquipmentLoadoutResponseDelegate& OnCompletedRequest);
    static FString GetOtherPlayerLoadout(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicUid, int32 Page, int32 PerPage, const FLootLockerEquipmentLoadoutResponseDelegate& OnCompletedRequest);
    static FString ListSlotCandidates(const FLootLockerPlayerData& PlayerData, const FString& SlotId, int32 Page, int32 PerPage, const FLootLockerEquipmentSlotCandidatesResponseDelegate& OnCompletedRequest);
    static FString EquipStack(const FLootLockerPlayerData& PlayerData, const FLootLockerEquipmentEquipRequest& Request, const FLootLockerEquipmentEquipResponseDelegate& OnCompletedRequest);
    static FString UnequipStack(const FLootLockerPlayerData& PlayerData, const FString& EntryId, const FLootLockerDefaultDelegate& OnCompletedRequest);
};
