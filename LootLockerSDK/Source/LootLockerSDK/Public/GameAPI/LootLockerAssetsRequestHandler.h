// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "LootLockerAssetsRequestHandler.generated.h"

//TODO: propably wrong, remove later
// USTRUCT(BlueprintType)
// struct FLootLockerDefaultLoadouts
// {
//     GENERATED_BODY()
//     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
//     bool skier = false;
//     UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
//     bool snowboarder = false;
// };

USTRUCT(BlueprintType)
struct FLootLockerPsn
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entitlement_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 service_label = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerApple
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString product_id;
};

USTRUCT(BlueprintType)
struct FLootLockerGoogle
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString product_id;
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
    FString url;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FLootLockerFilter
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerRarity
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString short_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString color;
};

USTRUCT(BlueprintType)
struct FLootLockerLinks
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString thumbnail;
};

USTRUCT(BlueprintType)
struct FLootLockerRentalOption
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 duration = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 price = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLinks links;
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
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString primary_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString secondary_color;
  // TODO: properties not implemented
  //
    // "properties": [
    //     {
    //         "material_path": "CharacterAttachments\/hands\/lo2\/lo2-gloves-13-sven\/lo2-gloves-13-sven.mtl",
    //         "binding_path": "CharacterAttachments\/hands\/shared-meshes\/gloves-a\/gloves-a.skin",
    //         "bone_id": 12,
    //         "bone_overrides": {
    //
    //         }
    //     }
    
  //  TArray<FProperty> properties;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLinks links;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidate
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int created_by_player_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_by_player_uid;
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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")  //TODO:missing in Unity SDK
    FString uuid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool active = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool purchasable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 price = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString display_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker") //TODO:missing in Unity SDK
    int32 context_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString unlocks_context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool detachable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString updated;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString marked_new;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 default_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLinks links;
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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker") //TODO:missing in Unity SDK
    FString shop_thumbnail;
    // UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker") //TODO:replaced by map
    // FLootLockerDefaultLoadouts default_loadouts;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker") //TODO:missing in Unity SDK
    TMap<FString, bool> default_loadouts;
    FLootLockerExternalIdentifiers external_identifiers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString drop_table_max_picks; //TODO:missing in Unity SDK    
    
    //TODO: below seems to be unnecessary
//     // TODO: this does not look correct 
// //    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
// //    TArray<FString> package_contents; //TODO: check output
};

USTRUCT(BlueprintType)
struct FLootLockerContext {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString uuid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString friendly_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool detachable = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool user_facing = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 dependent_asset_id = 0;
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
	FString acquisition_source;

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
    FString rotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString boneName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString flags;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString mass;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString binding;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetBone {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetBoneParameters> parameters;
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FContextDelegateBP, FLootLockerGetContextResponse, ContextsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetsResponseDelegateBP, FLootLockerGetAssetsResponse, AssetsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetBonesResponseDelegateBP, FLootLockerGetAssetBonesResponse, AssetBonesResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetFavouriteAssetIndicesResponseDelegateBP, FLootLockerGetFavouriteAssetIndicesResponse, FavouriteAssetIndicesResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FUniversalAssetResponseDelegateBP, FLootLockerUniversalAssetsResponse, UniversalAssetsResponse);

DECLARE_DELEGATE_OneParam(FContextDelegate, FLootLockerGetContextResponse);
DECLARE_DELEGATE_OneParam(FAssetsResponseDelegate, FLootLockerGetAssetsResponse);
DECLARE_DELEGATE_OneParam(FAssetBonesResponseDelegate, FLootLockerGetAssetBonesResponse);
DECLARE_DELEGATE_OneParam(FGetFavouriteAssetIndicesResponseDelegate, FLootLockerGetFavouriteAssetIndicesResponse);
DECLARE_DELEGATE_OneParam(FUniversalAssetResponseDelegate, FLootLockerUniversalAssetsResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSDK_API ULootLockerAssetsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void GetContexts(const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());

    static void GetAssets(int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FAssetsResponseDelegateBP& OnCompletedRequestBP = FAssetsResponseDelegateBP(), const FAssetsResponseDelegate& OnCompletedRequest = FAssetsResponseDelegate());

    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnCompletedRequestBP = FAssetsResponseDelegateBP(), const FAssetsResponseDelegate& OnCompletedRequest = FAssetsResponseDelegate());

    static void GetAssetBones(const FAssetBonesResponseDelegateBP& OnCompletedRequestBP = FAssetBonesResponseDelegateBP(), const FAssetBonesResponseDelegate& OnCompletedRequest = FAssetBonesResponseDelegate());

    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP = FGetFavouriteAssetIndicesResponseDelegateBP(), const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());

    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP = FGetFavouriteAssetIndicesResponseDelegateBP(), const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());

    static void RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP = FGetFavouriteAssetIndicesResponseDelegateBP(), const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());

	static void GetUniversalAssets(int After, int Count, const FUniversalAssetResponseDelegateBP &OnCompletedRequestBP = FUniversalAssetResponseDelegateBP(), const FUniversalAssetResponseDelegate &OnCompletedRequest = FUniversalAssetResponseDelegate());

public:
    ULootLockerAssetsRequestHandler();

    static ULootLockerHttpClient* HttpClient;
	// static TMap<ELootLockerAssetFilter, FString>* AssetFilterMap;
};
