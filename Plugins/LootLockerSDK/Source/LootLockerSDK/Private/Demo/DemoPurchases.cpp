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

void ADemoPurchases::DemoVerifyPurchaseIos()
{
   ULootLockerSDKManager::VerifyPurchaseIos(IosPurchaseData, FPurchaseResponseDelegate::CreateUObject(this, &ADemoPurchases::OnVerifyPurchaseIosCompleted));
}

void ADemoPurchases::DemoPollPurchaseStatus()
{
   ULootLockerSDKManager::PollPurchaseStatus(PurchaseId, FPurchaseStatusResponseDelegate::CreateUObject(this, &ADemoPurchases::OnPollPurchaseStatusCompleted));
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

void ADemoPurchases::OnVerifyPurchaseIosCompleted(FPurchaseResponse Response)
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

void ADemoPurchases::OnPollPurchaseStatusCompleted(FPurchaseStatusResponse Response)
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
