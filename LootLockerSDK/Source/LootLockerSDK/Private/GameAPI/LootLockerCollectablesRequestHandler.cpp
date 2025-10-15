// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

constexpr FLootLockerEmptyRequest EmptyRequest;

void ULootLockerCollectablesRequestHandler::GetAllCollectables(const FLootLockerPlayerData& PlayerData, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCollectablesResponse>::CallAPI(EmptyRequest, ULootLockerGameEndpoints::GetAllCollectablesEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCollectablesRequestHandler::CollectItem(const FLootLockerPlayerData& PlayerData, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCollectablesResponse>::CallAPI(Item, ULootLockerGameEndpoints::CollectItemEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}
