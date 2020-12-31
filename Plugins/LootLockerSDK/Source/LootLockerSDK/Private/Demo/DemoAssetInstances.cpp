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
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetKeyValuePairsForAssetInstance Success"));
    }
    else 
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetKeyValuePairsForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnGetKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetKeyValuePairForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetKeyValuePairForAssetInstance Failed"));
    }
    
}

void ADemoAssetInstances::OnCreateStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCreateStorageItemForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCreateStorageItemForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnUpdateStorageItemsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnUpdateStorageItemsForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnUpdateStorageItemsForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnUpdateStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnUpdateStorageItemForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnUpdateStorageItemForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnDeleteStorageItemForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteStorageItemForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteStorageItemForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnInspectLootBoxCompleted(FLootBoxContentResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnInspectLootBox Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnInspectLootBox Failed"));
    }
}

void ADemoAssetInstances::OnOpenLootBoxCompleted(FOpenLootBoxResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnOpenLootBox Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnOpenLootBox Failed"));
    }
}
