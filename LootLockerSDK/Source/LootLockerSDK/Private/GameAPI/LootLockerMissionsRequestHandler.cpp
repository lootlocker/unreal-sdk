// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerMissionsRequestHandler::HttpClient = nullptr;

ULootLockerMissionsRequestHandler::ULootLockerMissionsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMissionsRequestHandler::GetAllMissions(const FLootLockerPlayerData& PlayerData, const FMissionsResponseDelegateBP& OnCompletedRequestBP, const FMissionsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerMissionsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMissionsEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerMissionsRequestHandler::GetMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FMissionResponseDelegateBP& OnCompletedRequestBP, const FMissionResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerMissionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerMissionsRequestHandler::StartMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FStartMissionResponseDelegateBP& OnCompletedRequestBP, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerStartMissionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::StartMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerMissionsRequestHandler::FinishMission(const FLootLockerPlayerData& PlayerData, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnCompletedRequestBP, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerFinishMissionResponse>::CallAPI(HttpClient, MissionData, ULootLockerGameEndpoints::FinishMissionEndpoint, { MissionId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}
