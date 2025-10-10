// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerMapsRequestHandler::HttpClient = nullptr;



ULootLockerMapsRequestHandler::ULootLockerMapsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMapsRequestHandler::GetMaps(const FLootLockerPlayerData& PlayerData, const FGetMapsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetMapsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMapsEndpoint, { },EmptyQueryParams, PlayerData, FGetMapsResponseDelegateBP(), OnCompletedRequest);
}
