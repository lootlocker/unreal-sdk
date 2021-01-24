// Copyright (c) 2021 LootLocker

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
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAllCollectables Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAllCollectables Failed"));
    }
}

void ADemoCollectables::OnCollectItemCompleted(FCollectablesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCollectItem Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCollectItem Failed"));
    }
}
