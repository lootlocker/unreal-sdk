// Copyright (c) 2020 LootLocker

#include "Demo/DemoAssetInstances.h"

void ADemoAssetInstances::DemoGetKeyValuePairsForAssetInstance()
{
    ULootLockerSDKManager::GetKeyValuePairsForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnGetKeyValuePairsForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoGetKeyValuePairForAssetInstance()
{
    ULootLockerSDKManager::GetKeyValuePairForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnGetKeyValuePairForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoCreateStorageItemForAssetInstance()
{
    ULootLockerSDKManager::CreateStorageItemForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnCreateStorageItemForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoUpdateStorageItemsForAssetInstance()
{
    ULootLockerSDKManager::UpdateStorageItemsForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnUpdateStorageItemsForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoUpdateStorageItemForAssetInstance()
{
    ULootLockerSDKManager::UpdateStorageItemForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnUpdateStorageItemForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoDeleteStorageItemForAssetInstance()
{
    ULootLockerSDKManager::DeleteStorageItemForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnDeleteStorageItemForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoInspectLootBox()
{
    ULootLockerSDKManager::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnInspectLootBoxCompleted));
}

void ADemoAssetInstances::DemoOpenLootBox()
{
    ULootLockerSDKManager::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnOpenLootBoxCompleted));
}

void ADemoAssetInstances::OnGetKeyValuePairsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetKeyValuePairsForAssetInstanceCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnGetKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetKeyValuePairForAssetInstanceCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnCreateStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnCreateStorageItemForAssetInstanceCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnUpdateStorageItemsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnUpdateStorageItemsForAssetInstanceCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnUpdateStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnUpdateStorageItemForAssetInstanceCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnDeleteStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnDeleteStorageItemForAssetInstanceCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnInspectLootBoxCompleted(FLootBoxContentResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnInspectLootBoxCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAssetInstances::OnOpenLootBoxCompleted(FOpenLootBoxResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnOpenLootBoxCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
