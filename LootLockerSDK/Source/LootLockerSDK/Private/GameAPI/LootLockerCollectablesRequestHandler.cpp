// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

constexpr FLootLockerEmptyRequest EmptyRequest;

FString ULootLockerCollectablesRequestHandler::GetAllCollectables(const FLootLockerPlayerData& PlayerData, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerCollectablesResponse>::CallAPI(EmptyRequest, ULootLockerGameEndpoints::GetAllCollectablesEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerCollectablesRequestHandler::CollectItem(const FLootLockerPlayerData& PlayerData, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerCollectablesResponse>::CallAPI(Item, ULootLockerGameEndpoints::CollectItemEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}
