// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LootLockerDropTablesRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerDropTablesRequestHandler::HttpClient = nullptr;

ULootLockerDropTablesRequestHandler::ULootLockerDropTablesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerComputeAndLockDropTableResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ComputeAndLockDropTable, { TableId},EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(const FLootLockerPickDropsFromDropTableRequest& request, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerPickDropsFromDropTableResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::PickDropsFromDropTable, { TableId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
