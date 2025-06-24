// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerMiscellaneousRequestHandler::HttpClient = nullptr;

ULootLockerMiscellaneousRequestHandler::ULootLockerMiscellaneousRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMiscellaneousRequestHandler::GetServerTime(const FLootLockerPlayerData& PlayerData, const FTimeResponseDelegateBP& OnCompletedRequestBP, const FTimeResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerTimeResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetServerTimeEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

FString ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(const FLootLockerPlayerData& PlayerData)
{
	return PlayerData.CurrentPlatform.GetFriendlyPlatformString();
}

void ULootLockerMiscellaneousRequestHandler::GetGameInfo(const FGameInfoResponseDelegateBP& OnCompletedRequestBP, const FGameInfoResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGameInfoRequest Request { config->LootLockerGameKey };
    LLAPI<FLootLockerGameInfoResponse>::CallAPI(
        HttpClient,
        Request,
        ULootLockerGameEndpoints::GetGameInfoEndpoint,
        {},
        EmptyQueryParams,
        FLootLockerPlayerData(),
        OnCompletedRequestBP,
        OnCompletedRequest
    );
}