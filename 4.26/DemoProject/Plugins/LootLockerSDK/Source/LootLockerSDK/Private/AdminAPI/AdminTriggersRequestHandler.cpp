// Copyright (c) 2020 LootLocker

#include "AdminAPI/AdminTriggersRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FResponseCallback UAdminTriggersRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminTriggersRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminTriggersRequestHandler::ListTriggers(int GameId, const FATriggersResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FATriggersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FATriggersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("ListTriggers failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::ListTriggersEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("ListTriggers: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminTriggersRequestHandler::CreateTrigger(int GameId, const FATriggerPayload& TriggerData, const FATriggersResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FATriggersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FATriggersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateTrigger failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString = LootLockerUtilities::SerializeTrigger(TriggerData);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateTriggerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CreateTrigger: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminTriggersRequestHandler::UpdateTrigger(int GameId, int TriggerId, const FATriggerPayload& TriggerData, const FATriggersResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FATriggersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FATriggersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateTrigger failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString = LootLockerUtilities::SerializeTrigger(TriggerData);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::UpdateTriggerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, TriggerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateTrigger: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminTriggersRequestHandler::DeleteTrigger(int GameId, int TriggerId, const FATriggersResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FATriggersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FATriggersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeleteTrigger failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::DeleteTriggerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, TriggerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("DeleteTrigger: Admin API calls are only allowed in Editor"));
#endif
}
