// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoAssets.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoAssets : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int StartFromIndex;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int ItemsCount;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EAssetFilter AssetFilter;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool IncludeUGC;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<int> AssetIds;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetId;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoGetContexts();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoGetAssets();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoGetAssetsByIds();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoGetAssetBones();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoGetFavouriteAssetIndices();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoAddAssetToFavourites();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Assets")
    void DemoRemoveAssetFromFavourites();
    
    void OnGetContextsCompleted(FGetContextResponse Response);
    void OnGetAssetsCompleted(FGetAssetsResponse Response);
    void OnGetAssetsByIdsCompleted(FGetAssetsResponse Response);
    void OnGetAssetBonesCompleted(FGetAssetBonesResponse Response);
    void OnGetFavouriteAssetIndicesCompleted(FGetFavouriteAssetIndicesResponse Response);
    void OnAddAssetToFavouritesCompleted(FGetFavouriteAssetIndicesResponse Response);
    void OnRemoveAssetFromFavouritesCompleted(FGetFavouriteAssetIndicesResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
