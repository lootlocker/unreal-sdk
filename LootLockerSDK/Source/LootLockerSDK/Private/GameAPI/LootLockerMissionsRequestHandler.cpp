// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

FString ULootLockerMissionsRequestHandler::GetAllMissions(const FLootLockerPlayerData& PlayerData, const FMissionsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerMissionsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMissionsEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerMissionsRequestHandler::GetMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FMissionResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerMissionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerMissionsRequestHandler::StartMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerStartMissionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::StartMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerMissionsRequestHandler::FinishMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerFinishMissionResponse>::CallAPI(MissionData, ULootLockerGameEndpoints::FinishMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
