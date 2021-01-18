// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoMaps.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoMaps : public AActor
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Maps")
    void GetMaps();
    
    void OnGetMapsCompleted(FGetMapsResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
