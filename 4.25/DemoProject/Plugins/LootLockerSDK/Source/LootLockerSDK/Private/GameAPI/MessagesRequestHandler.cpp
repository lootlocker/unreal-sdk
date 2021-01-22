// Copyright (c) 2021 LootLocker

#include "GameAPI/MessagesRequestHandler.h"
#include "LootLockerGameEndpoints.h"

UHttpClient* UMessagesRequestHandler::HttpClient = nullptr;

UMessagesRequestHandler::UMessagesRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UMessagesRequestHandler::GetMessages(const FMessagesResponseDelegateBP& OnCompletedRequestBP, const FMessagesResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FMessagesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FMessagesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetMessages failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetMessagesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}
