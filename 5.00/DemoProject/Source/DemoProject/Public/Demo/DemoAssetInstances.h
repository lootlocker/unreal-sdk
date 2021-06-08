// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoAssetInstances.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoAssetInstances : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetInstanceId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int StorageItemId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerAssetInstanceStorageItem Item;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerAssetInstanceStorageItem> Items;
    
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
    
    void OnGetAllKeyValuePairsForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnGetAKeyValuePairByIdForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnCreateAKeyValuePairForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnUpdateAKeyValuePairByIdForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnDeleteAKeyValuePairByIdForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response);
    void OnInspectLootBoxCompleted(FLootLockerLootBoxContentResponse Response);
    void OnOpenLootBoxCompleted(FLootLockerOpenLootBoxResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
