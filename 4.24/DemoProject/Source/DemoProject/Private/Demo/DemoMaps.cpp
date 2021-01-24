// Copyright (c) 2021 LootLocker

#include "Demo/DemoMaps.h"


void ADemoMaps::GetMaps()
{
   ULootLockerSDKManager::GetMaps(FGetMapsResponseDelegate::CreateUObject(this, &ADemoMaps::OnGetMapsCompleted));
}

void ADemoMaps::OnGetMapsCompleted(FGetMapsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetMaps Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetMaps Failed"));
    }
}
