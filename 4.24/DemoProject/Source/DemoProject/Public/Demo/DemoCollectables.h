// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoCollectables.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoCollectables : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerCollectItemPayload Item;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Collectables")
    void DemoGetAllCollectables();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Collectables")
    void DemoCollectItem();
    
    void OnGetAllCollectablesCompleted(FLootLockerCollectablesResponse Response);
    void OnCollectItemCompleted(FLootLockerCollectablesResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
