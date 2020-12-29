// Copyright (c) 2020 LootLocker

#include "Demo/DemoTriggerEvents.h"


void ADemoTriggerEvents::DemoTriggerEvent()
{
   ULootLockerSDKManager::TriggerEvent(Event, FTriggerEventResponseDelegate::CreateUObject(this, &ADemoTriggerEvents::OnTriggerEventCompleted));
}

void ADemoTriggerEvents::DemoGetTriggeredEvents()
{
   ULootLockerSDKManager::GetTriggeredEvents(FTriggersResponseDelegate::CreateUObject(this, &ADemoTriggerEvents::OnGetTriggeredEventsCompleted));
}

void ADemoTriggerEvents::OnTriggerEventCompleted(FTriggerEventResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnTriggerEventCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoTriggerEvents::OnGetTriggeredEventsCompleted(FTriggersResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetTriggeredEventsCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
