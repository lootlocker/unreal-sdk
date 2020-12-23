// Copyright (c) 2020 LootLocker

#include "Demo/DemoCollectables.h"

ADemoCollectables::ADemoCollectables()
{
    LootLockerManager = NewObject<ULootLockerSDKManager>();
}

void ADemoCollectables::DemoGetAllCollectables()
{
    LootLockerManager->GetAllCollectables(FCollectablesResponseDelegate::CreateUObject(this, &ADemoCollectables::OnGetAllCollectablesCompleted));
}

void ADemoCollectables::DemoCollectItem()
{
    LootLockerManager->CollectItem(Item, FCollectablesResponseDelegate::CreateUObject(this, &ADemoCollectables::OnCollectItemCompleted));
}

void ADemoCollectables::OnGetAllCollectablesCompleted(FCollectablesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAllCollectablesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCollectables::OnCollectItemCompleted(FCollectablesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnCollectItemCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
