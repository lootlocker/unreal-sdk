// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LootLockerLeaderboardArchiveRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

void ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(const FLootLockerPlayerData& PlayerData, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerLeaderboardArchiveResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListLeaderboardArchive, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(const FLootLockerPlayerData& PlayerData, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest)
{

    TMultiMap<FString,FString> QueryParams;

	if (!Key.IsEmpty()) {
		QueryParams.Add("key", Key);
	}
	if(Count > 0){
    	QueryParams.Add("count", FString::FromInt(Count));
	}
	if (!After.IsEmpty())
	{
		QueryParams.Add("after", After);
	}
	LLAPI<FLootLockerLeaderboardArchiveDetailsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetLeaderboardArchive, { }, QueryParams, PlayerData, OnCompletedRequest);
}
