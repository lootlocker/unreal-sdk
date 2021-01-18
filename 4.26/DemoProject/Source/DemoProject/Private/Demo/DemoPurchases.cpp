// Copyright (c) 2020 LootLocker

#include "Demo/DemoPurchases.h"

void ADemoPurchases::DemoPurchaseAssets()
{
   ULootLockerSDKManager::PurchaseAssets(PurchaseData, FPurchaseResponseDelegate::CreateUObject(this, &ADemoPurchases::OnPurchaseAssetsCompleted));
}

void ADemoPurchases::DemoPurchaseAssetsAndroid()
{
   ULootLockerSDKManager::PurchaseAssetsAndroid(AndroidPurchaseData, FPurchaseResponseDelegate::CreateUObject(this, &ADemoPurchases::OnPurchaseAssetsAndroidCompleted));
}

void ADemoPurchases::DemoPurchaseAssetsIOS()
{
   ULootLockerSDKManager::PurchaseAssetsIOS(IosPurchaseData, FPurchaseResponseDelegate::CreateUObject(this, &ADemoPurchases::OnPurchaseAssetsIOSCompleted));
}

void ADemoPurchases::DemoPollingOrderStatus()
{
   ULootLockerSDKManager::PollingOrderStatus(PurchaseId, FPurchaseStatusResponseDelegate::CreateUObject(this, &ADemoPurchases::OnPollingStatusCompleted));
}

void ADemoPurchases::DemoActivateRentalAsset()
{
   ULootLockerSDKManager::ActivateRentalAsset(AssetId, FActivateRentalAssetResponseDelegate::CreateUObject(this, &ADemoPurchases::OnActivateRentalAssetCompleted));
}

void ADemoPurchases::OnPurchaseAssetsCompleted(FPurchaseResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnPurchaseAssets Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnPurchaseAssets Failed"));
    }
}

void ADemoPurchases::OnPurchaseAssetsAndroidCompleted(FPurchaseResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnPurchaseAssetsAndroid Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnPurchaseAssetsAndroid Failed"));
    }
}

void ADemoPurchases::OnPurchaseAssetsIOSCompleted(FPurchaseResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPurchaseIos Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPurchaseIos Failed"));
    }
}

void ADemoPurchases::OnPollingStatusCompleted(FPurchaseStatusResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnPollPurchaseStatus Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnPollPurchaseStatus Failed"));
    }
}

void ADemoPurchases::OnActivateRentalAssetCompleted(FActivateRentalAssetResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnActivateRentalAsset Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnActivateRentalAsset Failed"));
    }
}
