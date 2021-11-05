// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoPersistentStorage.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoPersistentStorage : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerPersistentStorageItem> Items;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString PlayerId;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Persistent Storage")
    void DemoGetEntirePersistentStorage();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Persistent Storage")
    void DemoGetItemFromPersistentStorage();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Persistent Storage")
    void DemoAddItemsToPersistentStorage();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Persistent Storage")
    void DemoDeleteItemFromPersistentStorage();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Persistent Storage")
    void DemoGetPlayerPersistentStorage();
    
    void OnGetEntirePersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response);
    void OnGetItemFromPersistentStorageCompleted(FLootLockerPersistentStorageItemResponse Response);
    void OnAddItemsToPersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response);
    void OnDeleteItemFromPersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response);
    void OnGetPlayerPersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
