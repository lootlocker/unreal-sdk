// Copyright (c) 2020 LootLocker

#include "Demo/DemoMessages.h"


void ADemoMessages::DemoGetMessages()
{
   ULootLockerSDKManager::GetMessages(FMessagesResponseDelegate::CreateUObject(this, &ADemoMessages::OnGetMessagesCompleted));
}

void ADemoMessages::OnGetMessagesCompleted(FMessagesResponse Response)
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
