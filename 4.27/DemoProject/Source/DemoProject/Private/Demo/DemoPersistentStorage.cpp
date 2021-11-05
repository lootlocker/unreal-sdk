// Copyright (c) 2021 LootLocker

#include "Demo/DemoPersistentStorage.h"


void ADemoPersistentStorage::DemoGetEntirePersistentStorage()
{
   ULootLockerSDKManager::GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnGetEntirePersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoGetItemFromPersistentStorage()
{
   ULootLockerSDKManager::GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnGetItemFromPersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoAddItemsToPersistentStorage()
{
   ULootLockerSDKManager::AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnAddItemsToPersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoDeleteItemFromPersistentStorage()
{
   ULootLockerSDKManager::DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnDeleteItemFromPersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoGetPlayerPersistentStorage()
{
   ULootLockerSDKManager::GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnGetPlayerPersistentStorageCompleted));
}

void ADemoPersistentStorage::OnGetEntirePersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetEntirePersistentStorage Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetEntirePersistentStorage Failed"));
    }
}

void ADemoPersistentStorage::OnGetItemFromPersistentStorageCompleted(FLootLockerPersistentStorageItemResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetItemFromPersistentStorage Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetItemFromPersistentStorage Failed"));
    }
}

void ADemoPersistentStorage::OnAddItemsToPersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnAddItemsToPersistentStorage Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnAddItemsToPersistentStorage Failed"));
    }
}

void ADemoPersistentStorage::OnDeleteItemFromPersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteItemFromPersistentStorage Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteItemFromPersistentStorage Failed"));
    }
}

void ADemoPersistentStorage::OnGetPlayerPersistentStorageCompleted(FLootLockerPersistentStorageItemsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetPlayerPersistentStorage Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetPlayerPersistentStorage Failed"));
    }
}
