#include "GameAPI/LootLockerDropTablesRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

FString ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(const FLootLockerPlayerData& PlayerData, int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerComputeAndLockDropTableResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ComputeAndLockDropTable, { TableId},EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(const FLootLockerPlayerData& PlayerData, const FLootLockerPickDropsFromDropTableRequest& request, int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerPickDropsFromDropTableResponse>::CallAPI(request, ULootLockerGameEndpoints::PickDropsFromDropTable, { TableId },EmptyQueryParams, PlayerData, OnCompletedRequest);
}
