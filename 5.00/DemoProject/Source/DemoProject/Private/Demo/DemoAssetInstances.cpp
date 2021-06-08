// Copyright (c) 2021 LootLocker

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

void ADemoAssetInstances::OnGetAllKeyValuePairsForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnGetAKeyValuePairByIdForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnCreateAKeyValuePairForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnUpdateAKeyValuePairByIdForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnDeleteAKeyValuePairByIdForAssetInstanceCompleted(FLootLockerAssetInstanceStorageItemsResponse Response)
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

void ADemoAssetInstances::OnInspectLootBoxCompleted(FLootLockerLootBoxContentResponse Response)
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

void ADemoAssetInstances::OnOpenLootBoxCompleted(FLootLockerOpenLootBoxResponse Response)
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
