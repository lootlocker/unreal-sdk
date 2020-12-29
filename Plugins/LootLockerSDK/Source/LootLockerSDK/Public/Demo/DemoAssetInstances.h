// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoAssetInstances.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoAssetInstances : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetInstanceId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int StorageItemId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAssetInstanceStorageItem Item;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAssetInstanceStorageItem> Items;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoGetKeyValuePairsForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoGetKeyValuePairForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoCreateStorageItemForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoUpdateStorageItemsForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoUpdateStorageItemForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoDeleteStorageItemForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoInspectLootBox();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoOpenLootBox();
    
    void OnGetKeyValuePairsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnGetKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnCreateStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnUpdateStorageItemsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnUpdateStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnDeleteStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnInspectLootBoxCompleted(FLootBoxContentResponse Response);
    void OnOpenLootBoxCompleted(FOpenLootBoxResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
