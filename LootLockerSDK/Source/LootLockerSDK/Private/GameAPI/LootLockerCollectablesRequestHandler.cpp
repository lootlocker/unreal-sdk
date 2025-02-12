// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCollectablesRequestHandler::HttpClient = nullptr;

constexpr FLootLockerEmptyRequest EmptyRequest;

ULootLockerCollectablesRequestHandler::ULootLockerCollectablesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCollectablesRequestHandler::GetAllCollectables(const FLootLockerPlayerData& PlayerData, const FCollectablesResponseDelegateBP& OnCompletedRequestBP, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCollectablesResponse>::CallAPI(HttpClient, EmptyRequest, ULootLockerGameEndpoints::GetAllCollectablesEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCollectablesRequestHandler::CollectItem(const FLootLockerPlayerData& PlayerData, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCompletedRequestBP, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCollectablesResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::CollectItemEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}
