// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "HttpClient.h"
#include "GameAPI/PersistentStorageRequestHandler.h"
#include "AssetsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FDefaultLoadouts {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool skier;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool snowboarder;
};
USTRUCT(BlueprintType)
struct FPsn {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entitlement_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 service_label;
};
USTRUCT(BlueprintType)
struct FExternalIdentifiers {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FPsn psn;
};
USTRUCT(BlueprintType)
struct FFile {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> tags;
};
USTRUCT(BlueprintType)
struct FFilter {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
};
USTRUCT(BlueprintType)
struct FRarity {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString short_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString color;
};
USTRUCT(BlueprintType)
struct FLinks {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString thumbnail;
};
USTRUCT(BlueprintType)
struct FRentalOption {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 duration;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLinks links;
};
USTRUCT(BlueprintType)
struct FBoneOverrides 
{
    GENERATED_BODY()
};
//USTRUCT(BlueprintType)
//struct FProperty {
//    GENERATED_BODY()
//    FString material_path;
//    FString binding_path;
//    int bone_id;
//    FBoneOverrides bone_overrides;
//};

USTRUCT(BlueprintType)
struct FVariation {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString primary_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString secondary_color;
  //  TArray<FProperty> properties;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLinks links;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidate
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int created_by_player_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_by_player_uid;
};

USTRUCT(BlueprintType)
struct FLootLockerAsset
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool active;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString display_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString shop_thumbnail;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool detachable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool initially_purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString updated;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString marked_new;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 default_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDefaultLoadouts default_loadouts;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool featured;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool context_locked;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString unlocks_context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FRarity rarity;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool popular;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 popularity_score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool unique_instance;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FExternalIdentifiers external_identifiers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FVariation> variations;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FFilter> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FRentalOption> rental_options;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FFile> files;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> data_entities;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLinks links;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FPersistentStorageItem> storage;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
//    TArray<FString> package_contents; //TODO: check output
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetCandidate asset_candidate;
};

USTRUCT(BlueprintType)
struct FLootLockerContext {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString friendly_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool detachable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool user_facing;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int dependent_asset_id;
};

USTRUCT(BlueprintType)
struct FGetContextResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerContext> Contexts;
};

USTRUCT(BlueprintType)
struct FGetAssetsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAsset> Assets;
};

UENUM(BlueprintType)
enum class EAssetFilter : uint8
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
struct FAssetBoneParameters {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Rotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString BoneName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Flags;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Mass;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Binding;
};

USTRUCT(BlueprintType)
struct FAssetBone {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FAssetBoneParameters> parameters;
};

USTRUCT(BlueprintType)
struct FGetAssetBonesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FAssetBone> AssetBones;
};

USTRUCT(BlueprintType)
struct FGetFavouriteAssetIndicesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<int> Indices;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FContextDelegateBP, FGetContextResponse, ContextsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetsResponseDelegateBP, FGetAssetsResponse, AssetsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetBonesResponseDelegateBP, FGetAssetBonesResponse, AssetBonesResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetFavouriteAssetIndicesResponseDelegateBP, FGetFavouriteAssetIndicesResponse, FavouriteAssetIndicesResponse);
DECLARE_DELEGATE_OneParam(FContextDelegate, FGetContextResponse);
DECLARE_DELEGATE_OneParam(FAssetsResponseDelegate, FGetAssetsResponse);
DECLARE_DELEGATE_OneParam(FAssetBonesResponseDelegate, FGetAssetBonesResponse);
DECLARE_DELEGATE_OneParam(FGetFavouriteAssetIndicesResponseDelegate, FGetFavouriteAssetIndicesResponse);

/**
 *
 */
UCLASS()
class LOOTLOCKERSDK_API UAssetsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void GetContexts(const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
    
    static void GetAssets(int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC, const FAssetsResponseDelegateBP& OnCompletedRequestBP = FAssetsResponseDelegateBP(), const FAssetsResponseDelegate& OnCompletedRequest = FAssetsResponseDelegate());
    
    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnCompletedRequestBP = FAssetsResponseDelegateBP(), const FAssetsResponseDelegate& OnCompletedRequest = FAssetsResponseDelegate());
    
    static void GetAssetBones(const FAssetBonesResponseDelegateBP& OnCompletedRequestBP = FAssetBonesResponseDelegateBP(), const FAssetBonesResponseDelegate& OnCompletedRequest = FAssetBonesResponseDelegate());
    
    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP = FGetFavouriteAssetIndicesResponseDelegateBP(), const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());
    
    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP = FGetFavouriteAssetIndicesResponseDelegateBP(), const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());
    
    static void RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP = FGetFavouriteAssetIndicesResponseDelegateBP(), const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest = FGetFavouriteAssetIndicesResponseDelegate());
    
public:
    UAssetsRequestHandler();

    static UHttpClient* HttpClient;
};
