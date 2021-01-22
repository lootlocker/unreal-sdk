// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoPlayers.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoPlayers : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerGetRequests getRequests;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetPlayerInfo();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetInventory();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoSubmitXp();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoGetOtherPlayerInfo();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoCheckPlayerAssetNotification();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoCheckPlayerAssetDeactivationNotification();
    
    void OnGetPlayerInfoCompleted(FPlayerInfoResponse Response);
    void OnGetInventoryCompleted(FInventoryResponse Response);
    void OnSubmitXpCompleted(FSubmitXpResponse Response);
    void OnGetOtherPlayerInfoCompleted(FPlayerInfoResponse Response);
    void OnCheckPlayerAssetNotificationCompleted(FPlayerAssetNotificationResponse Response);
    void OnCheckPlayerAssetDeactivationNotificationCompleted(FPlayerAssetNotificationResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
