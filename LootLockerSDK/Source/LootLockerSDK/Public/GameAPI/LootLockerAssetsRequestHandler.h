// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "LootLockerAssetsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerPsn
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entitlement_id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 service_label = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerApple
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString product_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGoogle
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString product_id = "";
};


USTRUCT(BlueprintType)
struct FLootLockerExternalIdentifiers
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPsn psn;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerApple apple_app_store;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerGoogle google_play;
};

USTRUCT(BlueprintType)
struct FLootLockerFile
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FLootLockerFilter
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRarity
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString short_name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString color = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRentalOption
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 duration = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 price = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sales_price = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> links;
};

USTRUCT(BlueprintType)
struct FLootLockerBoneOverrides
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerVariation
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString primary_color = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString secondary_color = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> links;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidate
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int created_by_player_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_by_player_uid = "";
};

USTRUCT(BlueprintType)
struct FLootLockerHasKeyValueStorage
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPersistentStorageItem> storage;
    FString GetKeyValue(const FString &Key)
    {
        FString Found = TEXT("");
        for(int i=0; i < storage.Num(); i++)
        {
            if (storage[i].key == Key)
            {
                Found = storage[i].value;
                break;
            }
        }
        return Found;
    }
};

// LootLockerStorage property through base class
USTRUCT(BlueprintType)
struct FLootLockerAsset : public FLootLockerHasKeyValueStorage
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString uuid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ulid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool active = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool purchasable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 price = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sales_price = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString display_price = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString context = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 context_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString unlocks_context = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool detachable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString updated = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString marked_new = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 default_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString description = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> links;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerRarity rarity;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool popular = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 popularity_score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool unique_instance = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerRentalOption> rental_options;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFilter> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerVariation> variations;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool featured = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool context_locked = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool initially_purchasable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFile> files;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetCandidate asset_candidate;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> data_entities;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<int> character_classes;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString shop_thumbnail = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, bool> default_loadouts;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExternalIdentifiers external_identifiers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString drop_table_max_picks = "";
};

USTRUCT(BlueprintType)
struct FLootLockerContext {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString uuid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString friendly_name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool detachable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool user_facing = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 dependent_asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 max_equip_count = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerGetContextResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerContext> contexts;
};

USTRUCT(BlueprintType)
struct FLootLockerGetAssetsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAsset> assets;
};

UENUM(BlueprintType)
enum class ELootLockerAssetFilter : uint8
{
    None = 0,
    Purchasable = 1,
    NonPurchasable = 2,
    Rentable = 3,
    NonRentable = 4,
    Popular = 5,
    UnPopular = 6
};

UENUM(BlueprintType)
enum class ELootLockerOrderAssetListBy : uint8
{
    None = 0,
    Id = 1,
    Name = 2,
    Created_at = 3,
    Updated_at = 4
};

UENUM(BlueprintType)
enum class ELootLockerOrderAssetListDirection : uint8
{
    None = 0,
    Asc = 1,
    Desc = 2
};

USTRUCT(BlueprintType)
struct FLootLockerUniversalAssets
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int universal_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int variation_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int rental_option_id = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerRentalOption rental;
};

USTRUCT(BlueprintType)
struct FLootLockerUniversalAssetsResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerUniversalAssets> global_assets;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetBoneParameters {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString rotation = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString position = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString boneName = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString flags = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString mass = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString binding = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAssetBone {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetBoneParameters> parameters;
};

USTRUCT(BlueprintType)
struct FLootLockerGrantAssetRequest {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_rental_option_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerGetAssetBonesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetBone> AssetBones;
};

USTRUCT(BlueprintType)
struct FLootLockerGetFavouriteAssetIndicesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<int32> favourites;
};

USTRUCT(BlueprintType)
struct FLootLockerGrantAssetResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString asset_ulid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString acquisition_source = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString acquisition_date = "";
};

/** Fields to include in the simple asset response */
USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetIncludes
{
    GENERATED_BODY()
    // If set to true, response will include storage key-value pairs.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    bool storage = false;
    // If set to true, response will include files.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    bool files = false;
    // If set to true, response will include asset data entities.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    bool data_entities = false;
    // If set to true, response will include asset metadata.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    bool metadata = false;
};

/** Fields to exclude from the simple asset response */
USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetExcludes
{
    GENERATED_BODY()
    // If set to true, UGC assets authors will not be returned.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    bool authors = false;
};

/** Filters to apply to the asset listing based on key-value pairs */
USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetFilter
{
    GENERATED_BODY()
    // The key for which to look for the filtered values
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString key = "";
    // A list of values to filter by. If the asset has any of these values for the given key, it will be included in the results.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FString> values;
};

/** Filters to apply to simple asset listing */
USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetFilters
{
    GENERATED_BODY()
    // If true only UGC assets are returned
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    bool ugc_only = false;
    // If provided only the requested ids will be returned (max 100, server enforced). Pagination ignored.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<int> asset_ids;
    // Filters to apply to the asset listing based on key-value pairs.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FLootLockerSimpleAssetFilter> asset_filters;
};

/** Request payload for simple asset listing */
USTRUCT(BlueprintType)
struct FLootLockerListSimpleAssetsRequest
{
    GENERATED_BODY()
    // Fields to include in the response.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FLootLockerSimpleAssetIncludes includes;
    // Fields to exclude from the response.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FLootLockerSimpleAssetExcludes excludes;
    // Filters to apply to the asset listing.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FLootLockerSimpleAssetFilters filters;
};

USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetAuthor
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    int player_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString player_ulid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString public_uid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString active_name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetFile
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    int size = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString url = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FLootLockerSimpleAssetDataEntity
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString data = "";
};

/** Simplified asset object */
USTRUCT(BlueprintType)
struct FLootLockerSimpleAsset
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString asset_uuid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString asset_ulid = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString asset_name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    int context_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString context_name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FLootLockerSimpleAssetAuthor author;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FLootLockerPersistentStorageItem> storage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FLootLockerSimpleAssetFile> files;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FLootLockerSimpleAssetDataEntity> data_entities;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FLootLockerMetadataEntry> metadata;
};

/** Response payload for simple asset listing */
USTRUCT(BlueprintType)
struct FLootLockerListSimpleAssetsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    // List of assets returned by the endpoint.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    TArray<FLootLockerSimpleAsset> assets;
    // Pagination data for this request
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FLootLockerExtendedIndexBasedPagination pagination;
};

DECLARE_DELEGATE_OneParam(FContextDelegate, FLootLockerGetContextResponse);
DECLARE_DELEGATE_OneParam(FAssetsResponseDelegate, FLootLockerGetAssetsResponse);
DECLARE_DELEGATE_OneParam(FAssetBonesResponseDelegate, FLootLockerGetAssetBonesResponse);
DECLARE_DELEGATE_OneParam(FGetFavouriteAssetIndicesResponseDelegate, FLootLockerGetFavouriteAssetIndicesResponse);
DECLARE_DELEGATE_OneParam(FUniversalAssetResponseDelegate, FLootLockerUniversalAssetsResponse);
DECLARE_DELEGATE_OneParam(FGrantAssetResponseDelegate, FLootLockerGrantAssetResponse);
DECLARE_DELEGATE_OneParam(FListSimpleAssetsResponseDelegate, FLootLockerListSimpleAssetsResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSDK_API ULootLockerAssetsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    // Add inline constructor definition to fix header syntax
    ULootLockerAssetsRequestHandler() {};

    static void GetContexts(const FLootLockerPlayerData& PlayerData, const FContextDelegate& OnCompletedRequest = FContextDelegate());

    static void GetAssets(const FLootLockerPlayerData& PlayerData, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FAssetsResponseDelegate& OnCompletedRequest = FAssetsResponseDelegate());

    static void GetAssetsByIds(const FLootLockerPlayerData& PlayerData, const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest = FAssetsResponseDelegate());

    static void GetAssetBones(const FLootLockerPlayerData& PlayerData, const FAssetBonesResponseDelegate& OnCompletedRequest = FAssetBonesResponseDelegate());

    static void GetFavouriteAssetIndices(const FLootLockerPlayerData& PlayerData, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());

    static void AddAssetToFavourites(const FLootLockerPlayerData& PlayerData, int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());

    static void RemoveAssetFromFavourites(const FLootLockerPlayerData& PlayerData, int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());

    static void GetUniversalAssets(const FLootLockerPlayerData& PlayerData, int After, int Count, const FUniversalAssetResponseDelegate& OnCompletedRequest = FUniversalAssetResponseDelegate());

    static void GrantAssetToPlayerInventory(const FLootLockerPlayerData& PlayerData, const int assetID, const int assetVariationID, const int assetRentalOptionID, const FGrantAssetResponseDelegate& OnCompletedRequest = FGrantAssetResponseDelegate());

    static void ListAssets(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, ELootLockerOrderAssetListBy OrderBy, ELootLockerOrderAssetListDirection OrderDirection, const FListSimpleAssetsResponseDelegate& OnCompletedRequest = FListSimpleAssetsResponseDelegate());
};
