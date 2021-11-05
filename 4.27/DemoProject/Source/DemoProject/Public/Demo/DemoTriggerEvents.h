// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoTriggerEvents.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoTriggerEvents : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerTriggerEvent Event;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Trigger Events")
    void DemoTriggerEvent();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Trigger Events")
    void DemoGetTriggeredEvents();
    
    void OnTriggerEventCompleted(FLootLockerTriggerEventResponse Response);
    void OnGetTriggeredEventsCompleted(FLootLockerTriggersResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
