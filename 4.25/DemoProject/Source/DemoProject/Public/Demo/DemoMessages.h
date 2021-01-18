// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoMessages.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoMessages : public AActor
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Messages")
    void DemoGetMessages();
    
    void OnGetMessagesCompleted(FMessagesResponse Response);
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
