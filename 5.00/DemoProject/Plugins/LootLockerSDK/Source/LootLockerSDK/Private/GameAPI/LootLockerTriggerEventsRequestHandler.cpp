// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerTriggerEventsRequestHandler.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerTriggerEventsRequestHandler::HttpClient = nullptr;

ULootLockerTriggerEventsRequestHandler::ULootLockerTriggerEventsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerTriggerEventsRequestHandler::TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnCompletedRequestBP, const FTriggerEventResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerTriggerEventResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerTriggerEventResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("TriggerEvent failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerTriggerEvent::StaticStruct(), &Event, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::TriggerEventEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerTriggerEventsRequestHandler::GetTriggeredEvents(const FTriggersResponseDelegateBP& OnCompletedRequestBP, const FTriggersResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerTriggersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerTriggersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetTriggeredEvents failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetTriggeredEventsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}
