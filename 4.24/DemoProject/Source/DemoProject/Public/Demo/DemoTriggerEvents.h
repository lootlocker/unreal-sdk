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
    FTriggerEvent Event;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Trigger Events")
    void DemoTriggerEvent();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Trigger Events")
    void DemoGetTriggeredEvents();
    
    void OnTriggerEventCompleted(FTriggerEventResponse Response);
    void OnGetTriggeredEventsCompleted(FTriggersResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
