// Copyright (c) 2020 LootLocker

#include "Demo/DemoMessages.h"

ADemoMessages::ADemoMessages()
{
    LootLockerManager = NewObject<ULootLockerSDKManager>();
}

void ADemoMessages::DemoGetMessages()
{
    LootLockerManager->GetMessages(FMessagesResponseDelegate::CreateUObject(this, &ADemoMessages::OnGetMessagesCompleted));
}

void ADemoMessages::OnGetMessagesCompleted(FMessagesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetMessagesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
