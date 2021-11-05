// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoPurchases.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoPurchases : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerAssetPurchaseData> PurchaseData;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerAndroidAssetPurchaseData> AndroidPurchaseData;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerVerifyPurchaseIosData> IosPurchaseData;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int PurchaseId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetId;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPurchaseAssets();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPurchaseAssetsAndroid();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPurchaseAssetsIOS();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoPollingOrderStatus();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Purchases")
    void DemoActivateRentalAsset();
    
    void OnPurchaseAssetsCompleted(FLootLockerPurchaseResponse Response);
    void OnPurchaseAssetsAndroidCompleted(FLootLockerPurchaseResponse Response);
    void OnPurchaseAssetsIOSCompleted(FLootLockerPurchaseResponse Response);
    void OnPollingStatusCompleted(FLootLockerPurchaseStatusResponse Response);
    void OnActivateRentalAssetCompleted(FLootLockerActivateRentalAssetResponse Response);
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
