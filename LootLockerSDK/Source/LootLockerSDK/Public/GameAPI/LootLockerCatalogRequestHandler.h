// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
#include "LootLockerResponse.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "LootLockerCatalogRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================
/// @addtogroup Catalog
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * Possible entity kinds that catalog entries can have
 */
enum class ELootLockerCatalogEntryEntityKind : uint8
{
    Asset = 0,
    Currency = 1,
    Progression_Points = 2,
    Progression_Reset = 3,
    Group = 4,
};
/// @}

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerItemDetailsKey
{
    GENERATED_BODY()
    /**
    * The id of the catalog listing
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";
    /**
    * The id of the item
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_id = "";

public:

    friend uint32 GetTypeHash(const FLootLockerItemDetailsKey& p) {
        return HashCombine(GetTypeHash(p.Catalog_listing_id), GetTypeHash(p.Item_id));
    }

    bool operator==(const FLootLockerItemDetailsKey& Other) const
    {
        return Catalog_listing_id.Equals(Other.Catalog_listing_id) && Item_id.Equals(Other.Item_id);
    }

};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAssetItemDetailsKey
{
    GENERATED_BODY()
    /**
    * The id of the catalog listing
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";
    /**
    * The id of the item
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Item_id = "";
    /**
    * The Asset Variation ID
    * Asset Variations is a deprecated feature, this is added for backward compatibility only
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Asset_variation_id = "";
    /**
    * The Asset Rental option ID
    * Asset Rental Options is a deprecated feature, this is added for backward compatibility only
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Rental_option_id = "";

public:

    friend uint32 GetTypeHash(const FLootLockerAssetItemDetailsKey& p) {
        return HashCombine(HashCombine(GetTypeHash(p.Catalog_listing_id), GetTypeHash(p.Item_id)), HashCombine(GetTypeHash(p.Asset_variation_id), GetTypeHash(p.Rental_option_id)));
    }

    bool operator==(const FLootLockerAssetItemDetailsKey& Other) const
    {
        return Catalog_listing_id.Equals(Other.Catalog_listing_id) && Item_id.Equals(Other.Item_id) && Asset_variation_id.Equals(Other.Asset_variation_id) && Rental_option_id.Equals(Other.Rental_option_id);
    }

    FLootLockerAssetItemDetailsKey() = default;

    FLootLockerAssetItemDetailsKey(const FString& InCatalogListingId, const FString& InItemId, const FString& InAssetVariationId, const FString& InRentalOptionId)
        : Catalog_listing_id(InCatalogListingId)
        , Item_id(InItemId)
        , Asset_variation_id(InAssetVariationId)
        , Rental_option_id(InRentalOptionId)
    {
    }

    FLootLockerAssetItemDetailsKey(const FLootLockerAssetItemDetailsKey& Other) = default;

    FLootLockerAssetItemDetailsKey& operator=(const FLootLockerAssetItemDetailsKey& Other) = default;

    ~FLootLockerAssetItemDetailsKey() = default;

    FLootLockerAssetItemDetailsKey(const FString& InCatalogListingId, const FString& InItemId)
        : Catalog_listing_id(InCatalogListingId)
        , Item_id(InItemId)
        , Asset_variation_id("")
        , Rental_option_id("")
    {
    }

    FLootLockerAssetItemDetailsKey(const FLootLockerItemDetailsKey& Other)
        : Catalog_listing_id(Other.Catalog_listing_id)
        , Item_id(Other.Item_id)
        , Asset_variation_id("")
        , Rental_option_id("")
    {
    }

};

/**
 * Represents a catalog with its name, unique key, identifier, and creation and deletion timestamps.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalog
{
    GENERATED_BODY()
    /**
     *
     * The time when this catalog was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
     *
     * The name of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     *
     * The unique identifying key of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
    /**
     *
     * The id of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     *
     * The time when this catalog was deleted, should normally be null
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Deleted_at = "";
};

/**
 * Represents a price for a catalog entry in a specific currency, including the numeric amount, display-friendly string, and unique price identifier.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogEntryPrice
{
    GENERATED_BODY()
    /**
     * The amount (cost) set for this price
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount = 0;
    /**
     * A prettified version of the amount to use for display
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Display_amount = "";
    /**
     * The short code for the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_code = "";
    /**
     * The name of the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_name = "";
    /**
     * The unique id of this price
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Price_id = "";
    /**
     * The unique id of the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id = "";
};

/**
 * Holds the Apple App Store product identifier for a catalog entry that can be purchased through that store.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogAppleAppStoreListing
{
    GENERATED_BODY()
    /**
     * The id of the product in Apple App Store that can be purchased and then used to redeem this catalog entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Product_id = "";
};

/**
 * Holds the Google Play Store product identifier for a catalog entry that can be purchased through that store.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogGooglePlayStoreListing
{
    GENERATED_BODY()
    /**
     * The id of the product in Apple App Store that can be purchased and then used to redeem this catalog entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Product_id = "";
};

/**
 * Represents a single price point for a Steam Store listing, specifying the currency code and amount.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogSteamStoreListingPrice
{
    GENERATED_BODY()
    /**
     * Currency code of the currency to be used for purchasing this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency = "";
    /**
     * Amount of the base value of the specified currency that this listing costs to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int amount = 0;
};

/**
 * Holds the Steam Store listing for a catalog entry, including a description and the available prices.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogSteamStoreListing
{
    GENERATED_BODY()
    /**
     * Description of this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Description = "";
    /**
     * List of prices for this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogSteamStoreListingPrice> Prices;
};

/**
 * Holds the Stripe payment details for a catalog entry, including the currency and charge amount in the smallest currency unit.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogStripeStoreListing
{
    GENERATED_BODY()
    /**
     * The currency to use for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency = "";
    /**
     * The amount to charge in the smallest unit of the currency (e.g. cents for USD)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount = 0;
};

/**
 * Holds the Epic Games Store audience item identifier associated with a catalog entry listing.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogEpicGamesStoreListing
{
    GENERATED_BODY()
    /**
     * The Epic Games audience item id associated with this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Audience_item_id = "";
};

/**
 * Holds the PlayStation Store entitlement label associated with a catalog entry listing.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogPlaystationStoreListing
{
    GENERATED_BODY()
    /**
     * The Playstation entitlement label associated with this listing
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entitlement_label = "";
};

/**
 * Aggregates the platform-specific store listing information configured for a catalog entry across all supported storefronts.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogEntryListings
{
    GENERATED_BODY()
    /**
     * The listing information (if configured) for Apple App Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogAppleAppStoreListing Apple_app_store;
    /**
     * The listing information (if configured) for Google Play Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogGooglePlayStoreListing Google_play_store;
    /**
     * The listing information (if configured) for Steam Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogSteamStoreListing Steam_store;
    /**
     * The listing information (if configured) for Stripe Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogStripeStoreListing Stripe_store;
    /**
     * The listing information (if configured) for Epic Games Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogEpicGamesStoreListing Epic_games_store;
    /**
     * The listing information (if configured) for Playstation Store
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogPlaystationStoreListing Playstation_store;
};

/**
 * Represents a single purchasable item in a catalog, including its entity type, prices, platform store listings, purchasability flag, and unique catalog listing identifier.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogEntry
{
    GENERATED_BODY()
    /**
     * The time when this catalog entry was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
     * The kind of entity that this entry is. This signifies in which lookup structure to find the details of this entry by using the Catalog_listing_id.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerCatalogEntryEntityKind Entity_kind = ELootLockerCatalogEntryEntityKind::Asset;
    /**
     * All the listings configured for this catalog entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogEntryListings Listings;
    /**
     * The name of this entity
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entity_name = "";
    /**
     * A list of prices for this catalog entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogEntryPrice> Prices;
    /**
     * The unique id of the entity that this entry refers to.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entity_id = "";
    /**
     * A unique listing id for this entry in this catalog, grouping the entity and the prices. This is the key you use to look up details about the entity in the structure signified by the entity_kind.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";
    /**
     * Whether this entry is currently purchasable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Purchasable = false;
    /**
     * Whether this entry is refundable. If false, purchases of this entry cannot be refunded.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Non_refundable = false;

};

/**
 * Holds detail information about an asset catalog entity, including its name, ULID, legacy numeric id, thumbnail, and optional variation or rental option identifiers.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAssetDetails
{
    GENERATED_BODY()
    /**
     * The name of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * The id of the specific variation of this asset that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Variation_id = "";
    /**
     * The id of the specific rental option of this asset that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Rental_option_id = "";
    /**
     * The legacy id of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Legacy_id = 0;
    /**
     * The unique identifying id of this asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The thumbnail for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Thumbnail = "";
    /**
     * The Catalog listing ID for this asset detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";

};

/**
 * Holds details about a progression-points catalog entity, including the target progression key, name, ULID, and the number of points to be awarded.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerProgressionPointDetails
{
    GENERATED_BODY()
    /**
     * The unique key of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
    /**
     * The name of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * The amount of points to be added to the progression in question
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount = 0;
    /**
     * The unique id of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The Catalog listing ID for this progression point detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";
};

/**
 * Holds details about a progression-reset catalog entity, identifying the progression to be reset by key, name, and ULID.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerProgressionResetDetails
{
    GENERATED_BODY()
    /**
     * The unique key of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
    /**
     * The name of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * The unique id of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The Catalog listing ID for this progression reset detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";

};

/**
 * Holds details about a currency catalog entity, including the currency name, short code, amount to be awarded, and ULID.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCurrencyDetails
{
    GENERATED_BODY()
    /**
     * The name of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * The unique code of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
    /**
     * The amount of this currency to be awarded
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
     * The unique id of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The Catalog listing ID for this currency detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";

};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogGroupMetadata
{
    GENERATED_BODY()
    /**
     * The Key of a metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key = "";
    /**
     * The Value of a metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value = "";
};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogGroupAssociation
{
    GENERATED_BODY()
    /**
     * The kind of reward, (asset / currency / group / progression points / progression reset).
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerCatalogEntryEntityKind Kind = ELootLockerCatalogEntryEntityKind::Asset;
    /**
     * The unique id of the group that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The catalog listing id for this group detail.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";

};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGroupDetails
{
    GENERATED_BODY()
    /**
     * The name of the Group.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /** 
     * The description of the Group.
     */ 
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Description = "";
    /**
     * The metadata of the Group.
     * @deprecated This field was never used and will be removed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker", meta = (DeprecatedProperty, DeprecationMessage = "This field was never used and will be removed"))
    TArray<FLootLockerCatalogGroupMetadata> Metadata; // Deprecation date 2026-06-30
    /**
     * The ID of the reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id = "";
    /**
     * Associations for the Group reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogGroupAssociation> Associations;
};

//==================================================
// Request Definitions
//==================================================

/// N/A

//==================================================
// Response Definitions
//==================================================
/**
 * Response containing the list of all catalogs configured for the game.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * A list of the prices for the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalog> Catalogs;
};

/**
 * This is what the response looks like, but we want to expose the Mapped variant
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FInternalLootLockerListCatalogPricesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalog Catalog;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogEntry> Entries;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetDetails> Assets_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionPointDetails> Progression_Points_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionResetDetails> Progression_Resets_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCurrencyDetails> Currency_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerGroupDetails> Group_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerKeyBasedPagination Pagination;
};

/**
 * This is what the response looks like, but we want to expose the Mapped variant
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FInternalLootLockerListCatalogPricesV2Response : public FLootLockerResponse
{
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalog Catalog;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogEntry> Entries;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetDetails> Assets_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionPointDetails> Progression_Points_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionResetDetails> Progression_Resets_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCurrencyDetails> Currency_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerGroupDetails> Group_Details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInlinedGroupDetails : public FLootLockerGroupDetails
{
    GENERATED_BODY()
    /**
     * Asset details inlined for this catalog entry, will be Empty if the entity_kind is not asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetDetails> AssetDetails;
    /**
     * Progression point details inlined for this catalog entry, will be Empty if the entity_kind is not progression_points
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionPointDetails> ProgressionPointDetails;
    /**
     * Progression reset details inlined for this catalog entry, will be Empty if the entity_kind is not progression_reset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionResetDetails> ProgressionResetDetails;
    /**
     * Currency details inlined for this catalog entry, will be Empty if the entity_kind is not currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCurrencyDetails> CurrencyDetails;
};

/**
 * A Convenience type to use when you need inlined catalog items
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInlinedCatalogEntry : public FLootLockerCatalogEntry
{
    GENERATED_BODY()
    /**
     * Asset details inlined for this catalog entry, will be Empty if the entity_kind is not asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetDetails AssetDetails;
    /**
     * This is a list of potentially matching asset details for this catalog entry, in case there are multiple variations / rental options
     * Asset Variations and Rental Options are deprecated features, this is added for backward compatibility only
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetDetails> OptionalAssetDetailVariants;
    /**
     * Progression point details inlined for this catalog entry, will be Empty if the entity_kind is not progression_points
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionPointDetails ProgressionPointDetails;
    /**
     * Progression reset details inlined for this catalog entry, will be Empty if the entity_kind is not progression_reset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionResetDetails ProgressionResetDetails;
    /**
     * Currency details inlined for this catalog entry, will be Empty if the entity_kind is not currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrencyDetails CurrencyDetails;
    /**
    * Group details inlined for this catalog entry, will be Empty if the entity_kind is not group
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerInlinedGroupDetails GroupDetails;

    FLootLockerInlinedCatalogEntry(): AssetDetails(), OptionalAssetDetailVariants(), ProgressionPointDetails(), ProgressionResetDetails(), CurrencyDetails(), GroupDetails() {}

    FLootLockerInlinedCatalogEntry(const FLootLockerCatalogEntry& Entry, const FLootLockerListCatalogPricesResponse& CatalogListing);

    FLootLockerInlinedCatalogEntry(const FLootLockerCatalogEntry& Entry, const FLootLockerListCatalogPricesV2Response& CatalogListing);
};

/**
 * Response containing catalog entries with entity-typed lookup maps for asset, progression, currency, and group details, plus key-based pagination.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogPricesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Details about the catalog that the prices is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalog Catalog;

    /**
     * A list of entries available in this catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogEntry> Entries;

    /**
     * Lookup map for details about entities of entity type assets
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerAssetDetails> Asset_Details;

    /**
     * This is a list of potentially matching asset details for this catalog entry, in case there are multiple variations / rental options
     * Asset Variations and Rental Options are deprecated features, this is added for backward compatibility only
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerAssetItemDetailsKey, FLootLockerAssetDetails> Optional_Asset_Detail_Variants;


    /**
     * Lookup map for details about entities of entity type progression_points
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerProgressionPointDetails> Progression_Point_Details;

    /**
     * Lookup map for details about entities of entity type progression_reset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerProgressionResetDetails> Progression_Reset_Details;

    /**
     * Lookup map for details about entities of entity type currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerCurrencyDetails> Currency_Details;

    /**
    * Lookup map for details about entities of entity type group
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerGroupDetails> Group_Details;
    
    /**
     * Pagination data to use for subsequent requests
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerKeyBasedPagination Pagination;

    void AppendCatalogItems(FLootLockerListCatalogPricesResponse AdditionalCatalogPrices);

    FLootLockerListCatalogPricesResponse() {}

    explicit FLootLockerListCatalogPricesResponse(const FInternalLootLockerListCatalogPricesResponse& ArrayResponse);

    /**
     * Get all the entries with details inlined into the entries themselves
     */
    TArray<FLootLockerInlinedCatalogEntry> GetLootLockerInlinedCatalogEntries() const;
};

/**
 * Response containing catalog entries with entity-typed lookup maps for asset, progression, currency, and group details, plus extended index-based pagination for the v2 catalog endpoint.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogPricesV2Response : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Details about the catalog that the prices is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalog Catalog;

    /**
     * A list of entries available in this catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogEntry> Entries;

    /**
     * Lookup map for details about entities of entity type assets
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerAssetDetails> Asset_Details;

    /**
     * This is a list of potentially matching asset details for this catalog entry, in case there are multiple variations / rental options
     * Asset Variations and Rental Options are deprecated features, this is added for backward compatibility only
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerAssetItemDetailsKey, FLootLockerAssetDetails> Optional_Asset_Detail_Variants;

    /**
     * Lookup map for details about entities of entity type progression_points
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerProgressionPointDetails> Progression_Point_Details;

    /**
     * Lookup map for details about entities of entity type progression_reset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerProgressionResetDetails> Progression_Reset_Details;

    /**
     * Lookup map for details about entities of entity type currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerCurrencyDetails> Currency_Details;

    /**
    * Lookup map for details about entities of entity type group
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FLootLockerItemDetailsKey, FLootLockerGroupDetails> Group_Details;
    
    /**
     * Pagination data to use for subsequent requests
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;

    void AppendCatalogItems(FLootLockerListCatalogPricesV2Response AdditionalCatalogPrices);

    FLootLockerListCatalogPricesV2Response() {}

    explicit FLootLockerListCatalogPricesV2Response(const FInternalLootLockerListCatalogPricesV2Response& ArrayResponse);

    /**
     * Get all the entries with details inlined into the entries themselves
     */
    TArray<FLootLockerInlinedCatalogEntry> GetLootLockerInlinedCatalogEntries() const;
};

/**
 * Metadata include configuration for catalog items lookup.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerMetadataInclude
{
    GENERATED_BODY()
    /**
    * If true, all metadata entries for the item are returned.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool All = false;

    /**
    * Specific metadata key names to filter by. Only used when bAll is false.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Keys;
};

/**
 * Optional includes configuration for catalog items lookup.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogItemsIncludes
{
    GENERATED_BODY()
    /**
    * Metadata include configuration. If not set, metadata is not included.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerMetadataInclude Metadata;
};

/**
 * Request body for looking up catalog items by their catalog_listing_ids.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogItemsByIdRequest
{
    GENERATED_BODY()
    /**
    * Array of catalog_listing_id strings to look up (max 100)
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Ids;

    /**
    * Optional includes configuration to control what additional data is returned
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogItemsIncludes Includes;
};

/**
 * A group association with the entity detail inlined directly.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInlinedGroupAssociation
{
    GENERATED_BODY()
    /**
    * The entity kind of this association (asset, currency, progression_points, progression_reset)
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerCatalogEntryEntityKind Kind = ELootLockerCatalogEntryEntityKind::Asset;

    /**
    * The unique id of the entity
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;

    /**
    * The catalog listing id for this association
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;

    /**
    * Asset details inlined, populated when kind is asset
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetDetails Asset_detail;

    /**
    * Currency details inlined, populated when kind is currency
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrencyDetails Currency_detail;

    /**
    * Progression point details inlined, populated when kind is progression_points
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionPointDetails Progression_point_detail;

    /**
    * Progression reset details inlined, populated when kind is progression_reset
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionResetDetails Progression_reset_detail;
};

/**
 * Group detail used by the ListCatalogItemsById endpoint, where association details are
 * inlined directly into each association entry by the backend.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInlinedGroupDetailsWithAssociations
{
    GENERATED_BODY()
    /**
    * The name of the Group.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;

    /**
    * The description of the Group.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Description;

    /**
    * The ID of the reward.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;

    /**
    * The catalog listing id for this group detail.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;

    /**
    * Associations with entity details inlined directly.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerInlinedGroupAssociation> Associations;
};

/**
 * A catalog entry with entity details inlined directly. Used by the ListCatalogItemsById endpoint.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogItemsByIdEntry : public FLootLockerCatalogEntry
{
    GENERATED_BODY()
    /**
    * Asset details inlined, non-null when entity_kind is asset
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetDetails Asset_detail;

    /**
    * Currency details inlined, non-null when entity_kind is currency
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrencyDetails Currency_detail;

    /**
    * Progression point details inlined, non-null when entity_kind is progression_points
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionPointDetails Progression_point_detail;

    /**
    * Progression reset details inlined, non-null when entity_kind is progression_reset
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionResetDetails Progression_reset_detail;

    /**
    * Group details inlined, non-null when entity_kind is group
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerInlinedGroupDetailsWithAssociations Group_detail;

    /**
    * Metadata entries. Populated when includes.metadata is set.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMetadataEntry> Metadata;
};

/**
 * Describes why a specific catalog_listing_id could not be resolved.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogItemsByIdError
{
    GENERATED_BODY()
    /**
    * The catalog_listing_id that failed
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;

    /**
    * The reason (e.g. "not_found")
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reason;
};

/**
 * Response for the ListCatalogItemsById endpoint.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCatalogItemsByIdResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
    * Array of inlined catalog entries matching the successfully resolved IDs
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerListCatalogItemsByIdEntry> Items;

    /**
    * Errors for IDs that could not be resolved. Omitted when all IDs succeeded.
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerListCatalogItemsByIdError> Errors;
};

//==================================================
// Delegate Definitions
//==================================================

/// @addtogroup Catalog
/// @{
/**
 * C++ response delegate for listing catalogs
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCatalogsResponseDelegate, FLootLockerListCatalogsResponse);
/**
 * C++ response delegate for listing items and prices in a catalog
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCatalogPricesResponseDelegate, FLootLockerListCatalogPricesResponse);
/**
 * C++ response delegate for listing items and prices in a catalog
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCatalogPricesV2ResponseDelegate, FLootLockerListCatalogPricesV2Response);
/**
 * Internal C++ response delegate for listing items and prices in a catalog with details as arrays
 */
DECLARE_DELEGATE_OneParam(FInternalLootLockerListCatalogPricesResponseDelegate, FInternalLootLockerListCatalogPricesResponse);
/**
 * Internal C++ response delegate for listing items and prices in a catalog with details as arrays
 */
DECLARE_DELEGATE_OneParam(FInternalLootLockerListCatalogPricesV2ResponseDelegate, FInternalLootLockerListCatalogPricesV2Response);
/**
 * Delegate for ListCatalogItemsById response
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCatalogItemsByIdResponseDelegate, FLootLockerListCatalogItemsByIdResponse);

//==================================================
// API Class Definition
//==================================================

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerCatalogRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerCatalogRequestHandler() {};

    static FString ListCatalogs(const FLootLockerPlayerData& PlayerData, const FLootLockerListCatalogsResponseDelegate& OnComplete);
    static FString ListCatalogItems(const FLootLockerPlayerData& PlayerData, const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseDelegate& OnComplete);
    static FString ListCatalogItemsV2(const FLootLockerPlayerData& PlayerData, const FString& CatalogKey, int PerPage, int Page, const FLootLockerListCatalogPricesV2ResponseDelegate& OnComplete);
    static FString ListCatalogItemsById(const FLootLockerPlayerData& PlayerData, const TArray<FString>& CatalogListingIds, bool IncludeMetadata, const TArray<FString>& MetadataKeys, const FLootLockerListCatalogItemsByIdResponseDelegate& OnComplete);
    static TArray<FLootLockerInlinedCatalogEntry> ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog)
    {
        return Catalog.GetLootLockerInlinedCatalogEntries();
    }
    static TArray<FLootLockerInlinedCatalogEntry> ConvertCatalogV2ToInlineItems(const FLootLockerListCatalogPricesV2Response& Catalog)
    {
        return Catalog.GetLootLockerInlinedCatalogEntries();
    }
};
