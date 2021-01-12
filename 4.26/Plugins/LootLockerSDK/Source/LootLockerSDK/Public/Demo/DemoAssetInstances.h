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
    void DemoGetAllKeyValuePairsForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoGetAllKeyValuePairsToAnInstanceForAssetInstance();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoGetAKeyValuePairByIdForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoCreateAKeyValuePairForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoUpdateOneOrMoreKeyValuePairForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoUpdateAKeyValuePairByIdForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoDeleteAKeyValuePairByIdForAssetInstance();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoInspectLootBox();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Asset Instances")
    void DemoOpenLootBox();
    
    void OnGetAllKeyValuePairsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnGetAKeyValuePairByIdForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnCreateAKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnUpdateAKeyValuePairByIdForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnDeleteAKeyValuePairByIdForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response);
    void OnInspectLootBoxCompleted(FLootBoxContentResponse Response);
    void OnOpenLootBoxCompleted(FOpenLootBoxResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
