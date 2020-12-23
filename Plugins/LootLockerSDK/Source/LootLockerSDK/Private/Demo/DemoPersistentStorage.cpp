// Copyright (c) 2020 LootLocker

#include "Demo/DemoPersistentStorage.h"

ADemoPersistentStorage::ADemoPersistentStorage()
{
    LootLockerManager = NewObject<ULootLockerSDKManager>();
}

void ADemoPersistentStorage::DemoGetEntirePersistentStorage()
{
    LootLockerManager->GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnGetEntirePersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoGetItemFromPersistentStorage()
{
    LootLockerManager->GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnGetItemFromPersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoAddItemsToPersistentStorage()
{
    LootLockerManager->AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnAddItemsToPersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoDeleteItemFromPersistentStorage()
{
    LootLockerManager->DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnDeleteItemFromPersistentStorageCompleted));
}

void ADemoPersistentStorage::DemoGetPlayerPersistentStorage()
{
    LootLockerManager->GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegate::CreateUObject(this, &ADemoPersistentStorage::OnGetPlayerPersistentStorageCompleted));
}

void ADemoPersistentStorage::OnGetEntirePersistentStorageCompleted(FPersistentStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetEntirePersistentStorageCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPersistentStorage::OnGetItemFromPersistentStorageCompleted(FPersistentStorageItemResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetItemFromPersistentStorageCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPersistentStorage::OnAddItemsToPersistentStorageCompleted(FPersistentStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnAddItemsToPersistentStorageCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPersistentStorage::OnDeleteItemFromPersistentStorageCompleted(FPersistentStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnDeleteItemFromPersistentStorageCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPersistentStorage::OnGetPlayerPersistentStorageCompleted(FPersistentStorageItemsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetPlayerPersistentStorageCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
