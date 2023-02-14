// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerMiscellaneousRequestHandler::HttpClient = nullptr;

ULootLockerMiscellaneousRequestHandler::ULootLockerMiscellaneousRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMiscellaneousRequestHandler::GetServerTime(const FTimeResponseDelegateBP& OnCompletedRequestBP, const FTimeResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerTimeResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetServerTimeEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
