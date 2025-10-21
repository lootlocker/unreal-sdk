// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerMapsRequestHandler::GetMaps(const FLootLockerPlayerData& PlayerData, const FGetMapsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetMapsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMapsEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}
