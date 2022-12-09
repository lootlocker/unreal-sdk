// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCollectablesRequestHandler::HttpClient = nullptr;

ULootLockerCollectablesRequestHandler::ULootLockerCollectablesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCollectablesRequestHandler::GetAllCollectables(const FCollectablesResponseDelegateBP& OnCompletedRequestBP, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCollectablesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetAllCollectablesEndpoint, {}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCollectablesRequestHandler::CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCompletedRequestBP, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCollectablesResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::CollectItemEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}
