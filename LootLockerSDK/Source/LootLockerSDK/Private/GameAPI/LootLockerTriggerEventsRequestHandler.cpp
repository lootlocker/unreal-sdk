// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerTriggerEventsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerTriggerEventsRequestHandler::HttpClient = nullptr;

ULootLockerTriggerEventsRequestHandler::ULootLockerTriggerEventsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerTriggerEventsRequestHandler::TriggerEvent(const FLootLockerPlayerData& PlayerData, const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnCompletedRequestBP, const FTriggerEventResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerTriggerEventResponse>::CallAPI(HttpClient, Event, ULootLockerGameEndpoints::TriggerEventEndpoint, {  },EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerTriggerEventsRequestHandler::GetTriggeredEvents(const FLootLockerPlayerData& PlayerData, const FTriggersResponseDelegateBP& OnCompletedRequestBP, const FTriggersResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerTriggersResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetTriggeredEventsEndpoint, {  },EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}
