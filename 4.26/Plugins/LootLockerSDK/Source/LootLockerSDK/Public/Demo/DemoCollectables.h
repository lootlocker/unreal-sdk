// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoCollectables.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoCollectables : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FCollectItemPayload Item;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Collectables")
    void DemoGetAllCollectables();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Collectables")
    void DemoCollectItem();
    
    void OnGetAllCollectablesCompleted(FCollectablesResponse Response);
    void OnCollectItemCompleted(FCollectablesResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
