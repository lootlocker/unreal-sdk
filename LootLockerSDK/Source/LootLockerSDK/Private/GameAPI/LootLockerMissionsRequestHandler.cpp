// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

void ULootLockerMissionsRequestHandler::GetAllMissions(const FLootLockerPlayerData& PlayerData, const FMissionsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerMissionsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMissionsEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerMissionsRequestHandler::GetMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FMissionResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerMissionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerMissionsRequestHandler::StartMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerStartMissionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::StartMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerMissionsRequestHandler::FinishMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerFinishMissionResponse>::CallAPI(MissionData, ULootLockerGameEndpoints::FinishMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
