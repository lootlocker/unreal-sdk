// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerHttpClient.h"
#include "LootLockerCatalogRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================
/**
 * Possible entity kinds that catalog entries can have
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerCatalogEntryEntityKind : uint8
{
    Asset = 0,
    Currency = 1,
    Progression_Points = 2,
    Progression_Reset = 3,
};

/**
 * 
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
    FString Created_at;
    /**
     *
     * The name of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     *
     * The unique identifying key of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
    /**
     *
     * The id of the catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     *
     * The time when this catalog was deleted, should normally be null
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Deleted_at;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogPagination
{
    GENERATED_BODY()
    /**
     *
     * The total available items in this catalog
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Total;
    /**
     *
     * The cursor that points to the next item in the catalog list. Use this in subsequent requests to get additional items from the catalog.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Cursor;
    /**
     *
     * The cursor that points to the first item in this batch of items.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Previous_cursor;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogEntryPrice
{
    GENERATED_BODY()
    /**
     * The amount (cost) set for this price
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount;
    /**
     * A prettified version of the amount to use for display
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Display_amount;
    /**
     * The short code for the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_code;
    /**
     * The name of the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_name;
    /**
     * The unique id of this price
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Price_id;
    /**
     * The unique id of the currency this price is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogEntry
{
    GENERATED_BODY()
    /**
     * The time when this catalog entry was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at;
    /**
     * The kind of entity that this entry is. This signifies in which lookup structure to find the details of this entry by using the Catalog_listing_id.
     */
    ELootLockerCatalogEntryEntityKind Entity_kind;
    /**
     * The name of this entity
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entity_name;
    /**
     * A list of prices for this catalog entry
     */
    TArray<FLootLockerCatalogEntryPrice> Prices;
    /**
     * The unique id of the entity that this entry refers to.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Entity_id;
    /**
     * A unique listing id for this entry in this catalog, grouping the entity and the prices. This is the key you use to look up details about the entity in the structure signified by the entity_kind.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;
    /**
     * Whether this entry is currently purchasable
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Purchasable;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAssetDetails
{
    GENERATED_BODY()
    /**
     * The name of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     * The id of the specific variation of this asset that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Variation_id;
    /**
     * The id of the specific rental option of this asset that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Rental_option_id;
    /**
     * The legacy id of this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Legacy_id;
    /**
     * The unique identifying id of this asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The thumbnail for this asset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Thumbnail;
    /**
     * The Catalog listing ID for this asset detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;

};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerProgressionPointDetails
{
    GENERATED_BODY()
    /**
     * The unique key of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
    /**
     * The name of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     * The amount of points to be added to the progression in question
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount;
    /**
     * The unique id of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The Catalog listing ID for this progression point detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerProgressionResetDetails
{
    GENERATED_BODY()
    /**
     * The unique key of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
    /**
     * The name of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     * The unique id of the progression that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The Catalog listing ID for this progression reset detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCurrencyDetails
{
    GENERATED_BODY()
    /**
     * The name of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     * The unique code of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code;
    /**
     * The amount of this currency to be awarded
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount;
    /**
     * The unique id of the currency that this refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The Catalog listing ID for this currency detail
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;
};

//==================================================
// Request Definitions
//==================================================

/// N/A

//==================================================
// Response Definitions
//==================================================
/**
 *
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
    FLootLockerCatalogPagination Pagination;
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

    FLootLockerInlinedCatalogEntry(): AssetDetails(), ProgressionPointDetails(), ProgressionResetDetails(), CurrencyDetails() {}

    FLootLockerInlinedCatalogEntry(const FLootLockerCatalogEntry& Entry, const FLootLockerAssetDetails& AssetDetails, const FLootLockerProgressionPointDetails& ProgressionPointDetails, const FLootLockerProgressionResetDetails& ProgressionResetDetails, const FLootLockerCurrencyDetails& CurrencyDetails);
};

/**
 *
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
    TMap<FString /*Catalog_listing_id*/, FLootLockerAssetDetails> Asset_Details;

    /**
     * Lookup map for details about entities of entity type progression_points
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString /*Catalog_listing_id*/, FLootLockerProgressionPointDetails> Progression_Point_Details;

    /**
     * Lookup map for details about entities of entity type progression_reset
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString /*Catalog_listing_id*/, FLootLockerProgressionResetDetails> Progression_Reset_Details;

    /**
     * Lookup map for details about entities of entity type currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString /*Catalog_listing_id*/, FLootLockerCurrencyDetails> Currency_Details;

    /**
     * Pagination data to use for subsequent requests
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCatalogPagination Pagination;

    void AppendCatalogItems(FLootLockerListCatalogPricesResponse AdditionalCatalogPrices);

    FLootLockerListCatalogPricesResponse() : Pagination() {}

    explicit FLootLockerListCatalogPricesResponse(const FInternalLootLockerListCatalogPricesResponse& ArrayResponse);

    /**
     * Get all the entries with details inlined into the entries themselves
     */
    TArray<FLootLockerInlinedCatalogEntry> GetLootLockerInlinedCatalogEntries();
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for listing catalogs
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListCatalogsResponseBP, FLootLockerListCatalogsResponse, Response);
/**
 * Blueprint response delegate for listing items and prices in a catalog
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListCatalogPricesResponseBP, FLootLockerListCatalogPricesResponse, Response);
/**
 * Internal Blueprint response delegate for listing items and prices in a catalog with details as arrays
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FInternalLootLockerListCatalogPricesResponseBP, FInternalLootLockerListCatalogPricesResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing catalogs
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCatalogsResponseDelegate, FLootLockerListCatalogsResponse);
/**
 * C++ response delegate for listing items and prices in a catalog
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCatalogPricesResponseDelegate, FLootLockerListCatalogPricesResponse);
/**
 * Internal C++ response delegate for listing items and prices in a catalog with details as arrays
 */
DECLARE_DELEGATE_OneParam(FInternalLootLockerListCatalogPricesResponseDelegate, FInternalLootLockerListCatalogPricesResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerCatalogRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerCatalogRequestHandler();

    static void ListCatalogs(const FLootLockerListCatalogsResponseBP& OnCompleteBP = FLootLockerListCatalogsResponseBP(), const FLootLockerListCatalogsResponseDelegate& OnComplete = FLootLockerListCatalogsResponseDelegate());
    static void ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnCompleteBP = FLootLockerListCatalogPricesResponseBP(), const FLootLockerListCatalogPricesResponseDelegate& OnComplete = FLootLockerListCatalogPricesResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};
