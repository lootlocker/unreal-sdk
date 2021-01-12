// Copyright (c) 2020 LootLocker

#include "Demo/DemoAssetInstances.h"

void ADemoAssetInstances::DemoGetAllKeyValuePairsForAssetInstance()
{
    ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnGetAllKeyValuePairsForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoGetAllKeyValuePairsToAnInstanceForAssetInstance()
{
    ULootLockerSDKManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoGetAKeyValuePairByIdForAssetInstance()
{
    ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnGetAKeyValuePairByIdForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoCreateAKeyValuePairForAssetInstance()
{
    ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnCreateAKeyValuePairForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoUpdateOneOrMoreKeyValuePairForAssetInstance()
{
    ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoUpdateAKeyValuePairByIdForAssetInstance()
{
    ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnUpdateAKeyValuePairByIdForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoDeleteAKeyValuePairByIdForAssetInstance()
{
    ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnDeleteAKeyValuePairByIdForAssetInstanceCompleted));
}

void ADemoAssetInstances::DemoInspectLootBox()
{
    ULootLockerSDKManager::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnInspectLootBoxCompleted));
}

void ADemoAssetInstances::DemoOpenLootBox()
{
    ULootLockerSDKManager::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegate::CreateUObject(this, &ADemoAssetInstances::OnOpenLootBoxCompleted));
}

void ADemoAssetInstances::OnGetAllKeyValuePairsForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("GetAllKeyValuePairsForAssetInstance Success"));
    }
    else 
    {
        UE_LOG(LogTemp, Verbose, TEXT("GetAllKeyValuePairsForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("GetAllKeyValuePairsToAnInstanceForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("GetAllKeyValuePairsToAnInstanceForAssetInstance Failed"));
    }
    
}

void ADemoAssetInstances::OnGetAKeyValuePairByIdForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("GetAKeyValuePairByIdForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("GetAKeyValuePairByIdForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnCreateAKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("CreateAKeyValuePairForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("CreateAKeyValuePairForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("UpdateOneOrMoreKeyValuePairForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("UpdateOneOrMoreKeyValuePairForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnUpdateAKeyValuePairByIdForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("UpdateAKeyValuePairByIdForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("UpdateAKeyValuePairByIdForAssetInstance Failed"));
    }
}

void ADemoAssetInstances::OnDeleteAKeyValuePairByIdForAssetInstanceCompleted(FAssetInstanceStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("DeleteAKeyValuePairByIdForAssetInstance Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("DeleteAKeyValuePairByIdForAssetInstance Failed"));
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
