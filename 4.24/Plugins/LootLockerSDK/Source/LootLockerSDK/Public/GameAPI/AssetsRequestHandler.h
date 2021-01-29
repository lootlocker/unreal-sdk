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
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool active;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString display_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString shop_thumbnail;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool detachable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool initially_purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString marked_new;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 default_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FDefaultLoadouts default_loadouts;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool featured;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool context_locked;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString unlocks_context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FRarity rarity;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool popular;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 popularity_score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool unique_instance;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FExternalIdentifiers external_identifiers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FVariation> variations;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FFilter> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FRentalOption> rental_options;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FFile> files;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> data_entities;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLinks links;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FPersistentStorageItem> storage;
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    TArray<FString> package_contents; //TODO: check output
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerAssetCandidate asset_candidate;
};

USTRUCT(BlueprintType)
struct FLootLockerContext {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString friendly_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool detachable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool user_facing;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int dependent_asset_id;
};

USTRUCT(BlueprintType)
struct FGetContextResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerContext> Contexts;
};

USTRUCT(BlueprintType)
struct FGetAssetsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
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
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Rotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString BoneName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Flags;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Mass;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Binding;
};

USTRUCT(BlueprintType)
struct FAssetBone {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAssetBoneParameters> parameters;
};

USTRUCT(BlueprintType)
struct FGetAssetBonesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAssetBone> AssetBones;
};

USTRUCT(BlueprintType)
struct FGetFavouriteAssetIndicesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
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
