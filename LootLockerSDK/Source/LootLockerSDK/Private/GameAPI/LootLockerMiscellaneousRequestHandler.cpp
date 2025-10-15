// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

void ULootLockerMiscellaneousRequestHandler::GetServerTime(const FLootLockerPlayerData& PlayerData, const FTimeResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerTimeResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetServerTimeEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(const FLootLockerPlayerData& PlayerData)
{
	return PlayerData.CurrentPlatform.GetFriendlyPlatformString();
}

void ULootLockerMiscellaneousRequestHandler::GetGameInfo(const FGameInfoResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGameInfoRequest Request { config->LootLockerGameKey };
    LLAPI<FLootLockerGameInfoResponse>::CallAPI(
        Request,
        ULootLockerGameEndpoints::GetGameInfoEndpoint,
        {},
        EmptyQueryParams,
        FLootLockerPlayerData(),
        OnCompletedRequest
    );
}