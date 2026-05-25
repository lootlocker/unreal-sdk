// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerBanRequestHandler.h"
#include "LootLockerConfig.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerBanRequestHandler::GetPlayerBanStatus(const FString& PlayerUlid, const FLootLockerBanStatusDelegate& OnCompletedRequest)
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    FLootLockerBanStatusRequest Request;
    Request.game_api_key = Config->LootLockerGameKey;
    Request.player_id = PlayerUlid;
    return LLAPI<FLootLockerBanStatusResponse>::CallAPI(Request, ULootLockerGameEndpoints::GetPlayerBanStatusEndpoint, {}, {}, FLootLockerPlayerData(), OnCompletedRequest);
}
