// Copyright (c) 2020 LootLocker

#include "Demo/DemoCollectables.h"


void ADemoCollectables::DemoGetAllCollectables()
{
   ULootLockerSDKManager::GetAllCollectables(FCollectablesResponseDelegate::CreateUObject(this, &ADemoCollectables::OnGetAllCollectablesCompleted));
}

void ADemoCollectables::DemoCollectItem()
{
   ULootLockerSDKManager::CollectItem(Item, FCollectablesResponseDelegate::CreateUObject(this, &ADemoCollectables::OnCollectItemCompleted));
}

void ADemoCollectables::OnGetAllCollectablesCompleted(FCollectablesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAllCollectablesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCollectables::OnCollectItemCompleted(FCollectablesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnCollectItemCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
