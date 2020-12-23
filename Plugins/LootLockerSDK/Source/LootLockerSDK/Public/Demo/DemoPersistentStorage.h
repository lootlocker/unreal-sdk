// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoPersistentStorage.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoPersistentStorage : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FPersistentStorageItem> Items;
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
    
    void OnGetEntirePersistentStorageCompleted(FPersistentStorageItemsResponse Response);
    void OnGetItemFromPersistentStorageCompleted(FPersistentStorageItemResponse Response);
    void OnAddItemsToPersistentStorageCompleted(FPersistentStorageItemsResponse Response);
    void OnDeleteItemFromPersistentStorageCompleted(FPersistentStorageItemsResponse Response);
    void OnGetPlayerPersistentStorageCompleted(FPersistentStorageItemsResponse Response);
    
public:
    ADemoPersistentStorage();
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
