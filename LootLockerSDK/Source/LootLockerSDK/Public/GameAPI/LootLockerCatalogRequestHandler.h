// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerHttpClient.h"
#include "LootLockerCatalogRequestHandler.generated.h"

#if (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 27) || (ENGINE_MAJOR_VERSION >= 5)
template <typename T>
using TOptionalIfSupported=TOptional<T>;
#else
template <typename T>
using TOptionalIfSupported=T;
#endif

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
    FString Created_at;
    /**
     *
     * The name of the catalog
     */
    FString Name;
    /**
     *
     * The unique identifying key of the catalog
     */
    FString Key;
    /**
     *
     * The id of the catalog
     */
    FString Id;
    /**
     *
     * The time when this catalog was deleted, should normally be null
     */
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
    int Total;
    /**
     *
     * The cursor that points to the next item in the catalog list. Use this in subsequent requests to get additional items from the catalog.
     */
    FString Cursor;
    /**
     *
     * The cursor that points to the first item in this batch of items.
     */
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
    int Amount;
	/**
	 * A prettified version of the amount to use for display
     */
    FString Display_amount;
    /**
     * The short code for the currency this price is in
     */
    FString Currency_code;
    /**
     * The name of the currency this price is in
     */
    FString Currency_name;
    /**
     * The unique id of this price
     */
    FString Price_id;
    /**
     * The unique id of the currency this price is in
     */
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
    FString Created_at;
    /**
     * The kind of entity that this entry is. This signifies in which lookup structure to find the details of this entry by using the grouping_key.
     */
   ELootLockerCatalogEntryEntityKind Entity_kind;
    /**
     * The name of this entity
     */
    FString Entity_name;
    /**
     * A list of prices for this catalog entry
     */
	TArray<FLootLockerCatalogEntryPrice> Prices;
	/**
	 * The unique id of the entity that this entry refers to.
     */
    FString Entity_id;
    /**
     * A unique id for this entry in this catalog grouping the entity and the prices. This is the key you use to look up details about the entity in the structure signified by the entity_kind.
     */
    FString Grouping_key;
    /**
     * Whether this entry is currently purchasable
     */
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
    FString Name;
    /**
     * The id of the specific variation of this asset that this refers to
     */
    FString Variation_id;
    /**
     * The id of the specific rental option of this asset that this refers to
     */
    FString Rental_option_id;
    /**
     * The legacy id of this asset
     */
    int Legacy_id;
    /**
     * The unique identifying id of this asset.
     */
    FString Id;
    /**
     * The thumbnail for this asset
     */
    FString Thumbnail;
    /**
     * The grouping key for this asset detail
     */
    FString Grouping_key;

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
    FString Key;
    /**
     * The name of the progression that this refers to
     */
    FString Name;
    /**
     * The amount of points to be added to the progression in question
     */
    int Amount;
	/**
     * The unique id of the progression that this refers to
     */
    FString Id;
    /**
     * The grouping key for this progression point detail
     */
    FString Grouping_key;
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
    FString Key;
    /**
     * The name of the progression that this refers to
     */
    FString Name;
    /**
     * The unique id of the progression that this refers to
     */
    FString Id;
    /**
     * The grouping key for this progression reset detail
     */
    FString Grouping_key;
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
    FString Name;
    /**
     * The unique code of the currency that this refers to
     */
    FString Code;
    /**
     * The amount of this currency to be awarded
     */
    FString Amount;
    /**
     * The unique id of the currency that this refers to
     */
    FString Id;
    /**
     * The grouping key for this currency detail
     */
    FString Grouping_key;
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
    TArray<FLootLockerCatalog> Catalogs;
};

/**
 * This is what the response looks like, but we want to expose the Mapped variant
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FInternalLootLockerListCatalogPricesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
	FLootLockerCatalog Catalog;
    TArray<FLootLockerCatalogEntry> Entries;
    TArray<FLootLockerAssetDetails> Assets_Details;
    TArray<FLootLockerProgressionPointDetails> Progression_Points_Details;
    TArray<FLootLockerProgressionResetDetails> Progression_Resets_Details;
    TArray<FLootLockerCurrencyDetails> Currency_Details;
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
    TOptionalIfSupported<FLootLockerAssetDetails> AssetDetails;
    /**
     * Progression point details inlined for this catalog entry, will be Empty if the entity_kind is not progression_points
     */
    TOptionalIfSupported<FLootLockerProgressionPointDetails> ProgressionPointDetails;
    /**
     * Progression reset details inlined for this catalog entry, will be Empty if the entity_kind is not progression_reset
     */
    TOptionalIfSupported<FLootLockerProgressionResetDetails> ProgressionResetDetails;
    /**
     * Currency details inlined for this catalog entry, will be Empty if the entity_kind is not currency
     */
    TOptionalIfSupported<FLootLockerCurrencyDetails> CurrencyDetails;

    FLootLockerInlinedCatalogEntry() {}

    FLootLockerInlinedCatalogEntry(const FLootLockerCatalogEntry& Entry, const TOptionalIfSupported<FLootLockerAssetDetails>& AssetDetails, const TOptionalIfSupported<FLootLockerProgressionPointDetails>& ProgressionPointDetails, const TOptionalIfSupported<FLootLockerProgressionResetDetails>& ProgressionResetDetails, const TOptionalIfSupported<FLootLockerCurrencyDetails>& CurrencyDetails)
    {
        Created_at = Entry.Created_at;
        Entity_kind = Entry.Entity_kind;
        Entity_name = Entry.Entity_name;
        Entity_id = Entry.Entity_id;
        Prices = Entry.Prices;
        Grouping_key = Entry.Grouping_key;
        Purchasable = Entry.Purchasable;
        this->AssetDetails = AssetDetails;
        this->ProgressionPointDetails = ProgressionPointDetails;
        this->ProgressionResetDetails = ProgressionResetDetails;
        this->CurrencyDetails = CurrencyDetails;
    }
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
    FLootLockerCatalog Catalog;

    /**
     * A list of entries available in this catalog
     */
    TArray<FLootLockerCatalogEntry> Entries;

    /**
	 * Lookup map for details about entities of entity type assets
     */
    TMap<FString /*Grouping_Key*/, FLootLockerAssetDetails> Asset_Details;

    /**
     * Lookup map for details about entities of entity type progression_points
     */
    TMap<FString /*Grouping_Key*/, FLootLockerProgressionPointDetails> Progression_Point_Details;

    /**
     * Lookup map for details about entities of entity type progression_reset
     */
    TMap<FString /*Grouping_Key*/, FLootLockerProgressionResetDetails> Progression_Reset_Details;

    /**
     * Lookup map for details about entities of entity type currency
     */
    TMap<FString /*Grouping_Key*/, FLootLockerCurrencyDetails> Currency_Details;

    /**
     * Pagination data to use for subsequent requests
     */
    FLootLockerCatalogPagination Pagination;

    void AppendCatalogItems(FLootLockerListCatalogPricesResponse AdditionalCatalogPrices)
    {
        if(!AdditionalCatalogPrices.success)
        {
            return;
        }

        Pagination.Total = AdditionalCatalogPrices.Pagination.Total;
        Pagination.Cursor = AdditionalCatalogPrices.Pagination.Cursor;

        for(auto& Entry : AdditionalCatalogPrices.Entries)
        {
            Entries.Add(Entry);
        }

        for(const auto& Detail : AdditionalCatalogPrices.Asset_Details)
        {
            Asset_Details.Add(Detail.Key, Detail.Value);
        }

        for(const auto& Detail : AdditionalCatalogPrices.Progression_Point_Details)
        {
            Progression_Point_Details.Add(Detail.Key, Detail.Value);
        }

        for(const auto& Detail : AdditionalCatalogPrices.Progression_Reset_Details)
        {
            Progression_Reset_Details.Add(Detail.Key, Detail.Value);
        }

        for(const auto& Detail : AdditionalCatalogPrices.Currency_Details)
        {
            Currency_Details.Add(Detail.Key, Detail.Value);
        }
    }

    FLootLockerListCatalogPricesResponse() : Pagination() {}

    explicit FLootLockerListCatalogPricesResponse(const FInternalLootLockerListCatalogPricesResponse& ArrayResponse)
    {
        success = ArrayResponse.success;
        ServerCallStatusCode = ArrayResponse.ServerCallStatusCode;
        FullTextFromServer = ArrayResponse.FullTextFromServer;
        ErrorData = ArrayResponse.ErrorData;
        if (!success)
        {
            return;
        }

        Catalog = ArrayResponse.Catalog;
        Entries = ArrayResponse.Entries;
        Pagination = ArrayResponse.Pagination;

        for (const auto& Detail : ArrayResponse.Assets_Details)
        {
            Asset_Details.Add(Detail.Grouping_key, Detail);
        }

        for (const auto& Detail : ArrayResponse.Progression_Points_Details)
        {
            Progression_Point_Details.Add(Detail.Grouping_key, Detail);
        }

        for (const auto& Detail : ArrayResponse.Progression_Resets_Details)
        {
            Progression_Reset_Details.Add(Detail.Grouping_key, Detail);
        }

        for (const auto& Detail : ArrayResponse.Currency_Details)
        {
            Currency_Details.Add(Detail.Grouping_key, Detail);
        }
    }

    /**
     * Get all the entries with details inlined into the entries themselves
     */
    TArray<FLootLockerInlinedCatalogEntry> GetLootLockerInlinedCatalogEntries()
    {
        TArray<FLootLockerInlinedCatalogEntry> InlinedEntries;
        for (const auto& CatalogEntry : Entries)
        {
            const FString& GroupingKey = CatalogEntry.Grouping_key;
            const auto& EntityKind = CatalogEntry.Entity_kind;
            InlinedEntries.Add(FLootLockerInlinedCatalogEntry(
                CatalogEntry,
#if false && (ENGINE_MAJOR_VERSION >= 4 && ENGINE_MINOR_VERSION >= 27) || (ENGINE_MAJOR_VERSION >= 5)
                ELootLockerCatalogEntryEntityKind::Asset == EntityKind && Asset_Details.Contains(GroupingKey) ? TOptional<FLootLockerAssetDetails>(Asset_Details.FindRef(GroupingKey)) : TOptional<FLootLockerAssetDetails>(),
                ELootLockerCatalogEntryEntityKind::Progression_Points == EntityKind && Progression_Point_Details.Contains(GroupingKey) ? TOptional<FLootLockerProgressionPointDetails>(Progression_Point_Details.FindRef(GroupingKey)) : TOptional<FLootLockerProgressionPointDetails>(),
                ELootLockerCatalogEntryEntityKind::Progression_Reset == EntityKind && Progression_Reset_Details.Contains(GroupingKey) ? TOptional<FLootLockerProgressionResetDetails>(Progression_Reset_Details.FindRef(GroupingKey)) : TOptional<FLootLockerProgressionResetDetails>(),
                ELootLockerCatalogEntryEntityKind::Currency == EntityKind && Currency_Details.Contains(GroupingKey) ? TOptional<FLootLockerCurrencyDetails>(Currency_Details.FindRef(GroupingKey)) : TOptional<FLootLockerCurrencyDetails>()
#else
                ELootLockerCatalogEntryEntityKind::Asset == EntityKind && Asset_Details.Contains(GroupingKey) ? Asset_Details.FindRef(GroupingKey) : FLootLockerAssetDetails(),
                ELootLockerCatalogEntryEntityKind::Progression_Points == EntityKind && Progression_Point_Details.Contains(GroupingKey) ? Progression_Point_Details.FindRef(GroupingKey) : FLootLockerProgressionPointDetails(),
                ELootLockerCatalogEntryEntityKind::Progression_Reset == EntityKind && Progression_Reset_Details.Contains(GroupingKey) ? Progression_Reset_Details.FindRef(GroupingKey) : FLootLockerProgressionResetDetails(),
                ELootLockerCatalogEntryEntityKind::Currency == EntityKind && Currency_Details.Contains(GroupingKey) ? Currency_Details.FindRef(GroupingKey) : FLootLockerCurrencyDetails()
#endif
            ));
        }
        return InlinedEntries;
    }
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
