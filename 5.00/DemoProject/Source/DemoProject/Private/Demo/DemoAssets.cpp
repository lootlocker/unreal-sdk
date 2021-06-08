// Copyright (c) 2021 LootLocker

#include "Demo/DemoAssets.h"

void ADemoAssets::DemoGetContexts()
{
   ULootLockerSDKManager::GetContexts(FContextDelegate::CreateUObject(this, &ADemoAssets::OnGetContextsCompleted));
}

void ADemoAssets::DemoGetAssets()
{
   ULootLockerSDKManager::GetAssets(FAssetsResponseDelegate::CreateUObject(this, &ADemoAssets::OnGetAssetsCompleted), StartFromIndex, ItemsCount, AssetFilter, IncludeUGC);
}

void ADemoAssets::DemoGetAssetsByIds()
{
   ULootLockerSDKManager::GetAssetsByIds(AssetIds, FAssetsResponseDelegate::CreateUObject(this, &ADemoAssets::OnGetAssetsByIdsCompleted));
}

void ADemoAssets::DemoGetAssetBones()
{
   ULootLockerSDKManager::GetAssetBones(FAssetBonesResponseDelegate::CreateUObject(this, &ADemoAssets::OnGetAssetBonesCompleted));
}

void ADemoAssets::DemoGetFavouriteAssetIndices()
{
   ULootLockerSDKManager::GetFavouriteAssetIndices(FGetFavouriteAssetIndicesResponseDelegate::CreateUObject(this, &ADemoAssets::OnGetFavouriteAssetIndicesCompleted));
}

void ADemoAssets::DemoAddAssetToFavourites()
{
   ULootLockerSDKManager::AddAssetToFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegate::CreateUObject(this, &ADemoAssets::OnAddAssetToFavouritesCompleted));
}

void ADemoAssets::DemoRemoveAssetFromFavourites()
{
   ULootLockerSDKManager::RemoveAssetFromFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegate::CreateUObject(this, &ADemoAssets::OnRemoveAssetFromFavouritesCompleted));
}

void ADemoAssets::OnGetContextsCompleted(FLootLockerGetContextResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetContexts Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetContexts Failed"));
    }
}

void ADemoAssets::OnGetAssetsCompleted(FLootLockerGetAssetsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssets Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssets Failed"));
    }
}

void ADemoAssets::OnGetAssetsByIdsCompleted(FLootLockerGetAssetsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetsByIds Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetsByIds Failed"));
    }
}

void ADemoAssets::OnGetAssetBonesCompleted(FLootLockerGetAssetBonesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetBones Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetBones Failed"));
    }
}

void ADemoAssets::OnGetFavouriteAssetIndicesCompleted(FLootLockerGetFavouriteAssetIndicesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetFavouriteAssetIndices Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetFavouriteAssetIndices Failed"));
    }
}

void ADemoAssets::OnAddAssetToFavouritesCompleted(FLootLockerGetFavouriteAssetIndicesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnAddAssetToFavourites Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnAddAssetToFavourites Failed"));
    }
}

void ADemoAssets::OnRemoveAssetFromFavouritesCompleted(FLootLockerGetFavouriteAssetIndicesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnRemoveAssetFromFavourites Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnRemoveAssetFromFavourites Failed"));
    }
}
