// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoMessages.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoMessages : public AActor
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Messages")
    void DemoGetMessages();
    
    void OnGetMessagesCompleted(FMessagesResponse Response);
    
public:
    ADemoMessages();
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
