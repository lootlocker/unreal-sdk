// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerMapsRequestHandler::HttpClient = nullptr;



ULootLockerMapsRequestHandler::ULootLockerMapsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMapsRequestHandler::GetMaps(const FGetMapsResponseDelegateBP& OnCompletedRequestBP, const FGetMapsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetMapsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SubmitScore, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
