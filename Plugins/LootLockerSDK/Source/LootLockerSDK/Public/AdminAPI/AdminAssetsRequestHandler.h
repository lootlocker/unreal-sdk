// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminAssetsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAAssetVariation {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString primary_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString secondary_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString deleted_at;
};

USTRUCT(BlueprintType)
struct FAAssetData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool active;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool tradable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool marketable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString context;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString last_changed;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString thumbnail;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetVariation> variations;
};

USTRUCT(BlueprintType)
struct FAAssetLanguage {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
};

USTRUCT(BlueprintType)
struct FAAssetContext {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
};

USTRUCT(BlueprintType)
struct FAAssetRarity {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString short_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString color;
};

USTRUCT(BlueprintType)
struct FAAssetLink {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString url;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int type_id;
};

USTRUCT(BlueprintType)
struct FAAssetLinkType {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int type;
};

USTRUCT(BlueprintType)
struct FAAssetGameVersion {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString version;
};

USTRUCT(BlueprintType)
struct FAAssetProperty {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString material_path;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString binding_path;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int bone_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int min_game_version_id;
};

USTRUCT(BlueprintType)
struct FADetailedAssetVariation {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool Default;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString primary_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString secondary_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetLink> links;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetProperty> properties;
};

USTRUCT(BlueprintType)
struct FAAssetFilterValue {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString url;
};

USTRUCT(BlueprintType)
struct FAAssetFilter {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAAssetFilterValue value;
};

USTRUCT(BlueprintType)
struct FAAssetBone {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
};

USTRUCT(BlueprintType)
struct FAAssetBoneParameter {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString bone_id;
};

USTRUCT(BlueprintType)
struct FADetailedAssetData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool active;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool purchasable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString last_changed;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float sales_price;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool on_steam;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, FAAssetLanguage> languages;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int context_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool global;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool featured;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> activation_errors;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int min_game_version_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAAssetRarity rarity;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int type_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool popular;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float popularity_score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool unique_instance;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString external_identifiers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetContext> contexts;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString background_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool tradable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool marketable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString market_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString market_hash_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString market_fee;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetLink> links;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, FAAssetLinkType> link_types;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetGameVersion> game_versions;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool is_package;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FADetailedAssetVariation> variations;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, FAAssetFilter> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetBone> bones;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetBoneParameter> boneParameters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool simple_asset;
};

USTRUCT(BlueprintType)
struct FAAssetDeactivationData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString reason;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int replacement_asset_id;
};

USTRUCT(BlueprintType)
struct FAAssetContextData : public FAAssetContext {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString friendly_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool detachable;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool user_facing;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, bool> characters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool dependent_asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool editable;
};

USTRUCT(BlueprintType)
struct FAAssetType {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
};

USTRUCT(BlueprintType)
struct FAAssetsResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetData> assets;
};

USTRUCT(BlueprintType)
struct FADetailedAssetResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FADetailedAssetData asset;
};

USTRUCT(BlueprintType)
struct FAAssetActivationResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool can_activate;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> errors;
};

USTRUCT(BlueprintType)
struct FAAssetDeactivationResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> errors;
};

USTRUCT(BlueprintType)
struct FAAssetContextsResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetContextData> contexts;
};

USTRUCT(BlueprintType)
struct FAAssetTypesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAAssetType> asset_types;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAAssetsResponseDelegate, FAAssetsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FADetailedAssetResponseDelegate, FADetailedAssetResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAAssetActivationResponseDelegate, FAAssetActivationResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAAssetDeactivationResponseDelegate, FAAssetDeactivationResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAAssetContextsResponseDelegate, FAAssetContextsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAAssetTypesResponseDelegate, FAAssetTypesResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminAssetsRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetAssets(int GameId, const FAAssetsResponseDelegate& OnComplete, const FString& SearchQuery = "", int Page = 0);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetAssetsByIds(const TArray<int> AssetIds, int GameId, const FAAssetsResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetDetailedAssetInfo(int GameId, int AssetId, const FADetailedAssetResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CreateAsset(const FADetailedAssetData& AssetData, const FADetailedAssetResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CheckIfAssetCanBeActivated(int AssetId, const FAAssetActivationResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void ActivateAsset(int AssetId, const FAAssetActivationResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void DeactivateAsset(int AssetId, const FAAssetDeactivationData& DeactivationData, const FAAssetDeactivationResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetAssetContexts(int GameId, const FAAssetContextsResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateAssetContexts(int GameId, const TArray<FAAssetContextData>& Contexts, const FAAssetContextsResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Assets", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetAssetTypes(int GameId, const FAAssetTypesResponseDelegate& OnComplete);
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
