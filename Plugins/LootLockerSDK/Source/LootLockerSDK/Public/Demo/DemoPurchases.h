// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoPurchases.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoPurchases : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAssetPurchaseData> PurchaseData;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAndroidAssetPurchaseData> AndroidPurchaseData;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FVerifyPurchaseIosData> IosPurchaseData;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int PurchaseId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetId;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPurchaseAssets();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPurchaseAssetsAndroid();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoVerifyPurchaseIos();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPollPurchaseStatus();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoActivateRentalAsset();
    
    void OnPurchaseAssetsCompleted(FPurchaseResponse Response);
    void OnPurchaseAssetsAndroidCompleted(FPurchaseResponse Response);
    void OnVerifyPurchaseIosCompleted(FPurchaseResponse Response);
    void OnPollPurchaseStatusCompleted(FPurchaseStatusResponse Response);
    void OnActivateRentalAssetCompleted(FActivateRentalAssetResponse Response);
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
