#include "GameAPI/LootLockerDropTablesRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

void ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(const FLootLockerPlayerData& PlayerData, int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerComputeAndLockDropTableResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ComputeAndLockDropTable, { TableId},EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(const FLootLockerPlayerData& PlayerData, const FLootLockerPickDropsFromDropTableRequest& request, int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerPickDropsFromDropTableResponse>::CallAPI(request, ULootLockerGameEndpoints::PickDropsFromDropTable, { TableId },EmptyQueryParams, PlayerData, OnCompletedRequest);
}
