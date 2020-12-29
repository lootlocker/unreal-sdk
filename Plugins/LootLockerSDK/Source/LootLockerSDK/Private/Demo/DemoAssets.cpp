// Copyright (c) 2020 LootLocker

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

void ADemoAssets::OnGetContextsCompleted(FGetContextResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetContextsCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssets::OnGetAssetsCompleted(FGetAssetsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetsCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssets::OnGetAssetsByIdsCompleted(FGetAssetsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetsByIdsCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssets::OnGetAssetBonesCompleted(FGetAssetBonesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetBonesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssets::OnGetFavouriteAssetIndicesCompleted(FGetFavouriteAssetIndicesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetFavouriteAssetIndicesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssets::OnAddAssetToFavouritesCompleted(FGetFavouriteAssetIndicesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnAddAssetToFavouritesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssets::OnRemoveAssetFromFavouritesCompleted(FGetFavouriteAssetIndicesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnRemoveAssetFromFavouritesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
