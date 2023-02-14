// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerMessagesRequestHandler::HttpClient = nullptr;

ULootLockerMessagesRequestHandler::ULootLockerMessagesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMessagesRequestHandler::GetMessages(const FMessagesResponseDelegateBP& OnCompletedRequestBP, const FMessagesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerMessagesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMessagesEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
