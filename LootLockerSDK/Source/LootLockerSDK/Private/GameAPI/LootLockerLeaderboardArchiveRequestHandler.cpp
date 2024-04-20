// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LootLockerLeaderboardArchiveRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"


ULootLockerHttpClient* ULootLockerLeaderboardArchiveRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerLeaderboardArchiveRequestHandler::ULootLockerLeaderboardArchiveRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerLeaderboardArchiveResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListLeaderboardArchive, { LeaderboardKey }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest)
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
	LLAPI<FLootLockerLeaderboardArchiveDetailsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetLeaderboardArchive, { }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}