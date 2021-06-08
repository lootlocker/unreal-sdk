// Copyright (c) 2021 LootLocker

#include "Demo/DemoMessages.h"


void ADemoMessages::DemoGetMessages()
{
   ULootLockerSDKManager::GetMessages(FMessagesResponseDelegate::CreateUObject(this, &ADemoMessages::OnGetMessagesCompleted));
}

void ADemoMessages::OnGetMessagesCompleted(FLootLockerMessagesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetMessages Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetMessages Failed"));
    }
}
