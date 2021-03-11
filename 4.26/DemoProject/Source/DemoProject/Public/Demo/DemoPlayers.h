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

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void GetCurrencyBalance();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void InitiateDLCMigration();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void GetDLCsMigration();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void SetProfilePrivate();

    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void SetProfilePublic();
    
    void OnGetPlayerInfoCompleted(FLootLockerPlayerInfoResponse Response);
    void OnGetInventoryCompleted(FLootLockerInventoryResponse Response);
    void OnSubmitXpCompleted(FLootLockerSubmitXpResponse Response);
    void OnGetOtherPlayerInfoCompleted(FLootLockerPlayerInfoResponse Response);
    void OnCheckPlayerAssetNotificationCompleted(FLootLockerPlayerAssetNotificationResponse Response);
    void OnCheckPlayerAssetDeactivationNotificationCompleted(FLootLockerPlayerAssetNotificationResponse Response);
    void OnGetCurrencyBalance(FLootLockerBalanceResponse Response);
    void OnInitiateDlcMigration(FLootLockerResponse Response);
    void OnGotDlcMigration(FLootLockerDlcResponse Response);
    void OnProfileSetPrivate(FLootLockerResponse Response);
    void OnProfileSetPublic(FLootLockerResponse Response);

    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
