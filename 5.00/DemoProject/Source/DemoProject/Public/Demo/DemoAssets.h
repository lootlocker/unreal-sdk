// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoAssets.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoAssets : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int StartFromIndex;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int ItemsCount;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ELootLockerAssetFilter AssetFilter;
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
    
    void OnGetContextsCompleted(FLootLockerGetContextResponse Response);
    void OnGetAssetsCompleted(FLootLockerGetAssetsResponse Response);
    void OnGetAssetsByIdsCompleted(FLootLockerGetAssetsResponse Response);
    void OnGetAssetBonesCompleted(FLootLockerGetAssetBonesResponse Response);
    void OnGetFavouriteAssetIndicesCompleted(FLootLockerGetFavouriteAssetIndicesResponse Response);
    void OnAddAssetToFavouritesCompleted(FLootLockerGetFavouriteAssetIndicesResponse Response);
    void OnRemoveAssetFromFavouritesCompleted(FLootLockerGetFavouriteAssetIndicesResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
