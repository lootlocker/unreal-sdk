// Copyright (c) 2020 LootLocker

#include "Demo/DemoMaps.h"

ADemoMaps::ADemoMaps()
{
    LootLockerManager = NewObject<ULootLockerSDKManager>();
}

void ADemoMaps::GetMaps()
{
    LootLockerManager->GetMaps(FGetMapsResponseDelegate::CreateUObject(this, &ADemoMaps::OnGetMapsCompleted));
}

void ADemoMaps::OnGetMapsCompleted(FGetMapsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetMapsCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
