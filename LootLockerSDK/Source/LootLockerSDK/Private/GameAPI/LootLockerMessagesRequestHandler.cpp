// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerMessagesRequestHandler::GetMessages(const FLootLockerPlayerData& PlayerData, const FMessagesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerMessagesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMessagesEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}
