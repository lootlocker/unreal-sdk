// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LootLockerDropTablesRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerDropTablesRequestHandler::HttpClient = nullptr;

ULootLockerDropTablesRequestHandler::ULootLockerDropTablesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(const FLootLockerPlayerData& PlayerData, int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerComputeAndLockDropTableResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ComputeAndLockDropTable, { TableId},EmptyQueryParams, PlayerData, FLootLockerComputeAndLockDropTableResponseBP(), OnCompletedRequest);
}

void ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(const FLootLockerPlayerData& PlayerData, const FLootLockerPickDropsFromDropTableRequest& request, int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerPickDropsFromDropTableResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::PickDropsFromDropTable, { TableId },EmptyQueryParams, PlayerData, FFLootLockerPickDropsFromDropTableResponseBP(), OnCompletedRequest);
}
