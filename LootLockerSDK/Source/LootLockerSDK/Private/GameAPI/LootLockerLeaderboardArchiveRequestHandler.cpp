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

void ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(FString LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerLeaderboardArchiveResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListLeaderboardArchive, { LeaderboardKey }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
void ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(FString Key, int Count, FString After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest)
{

	FLootLockerLeaderboardArchiveRequest makeRequest;
	makeRequest.key = Key;
	if (Count > 0) { 
		makeRequest.count = Count;
	}
	if (!After.IsEmpty()) {
		makeRequest.after = After;
	}

	LLAPI<FLootLockerLeaderboardArchiveDetailsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetLeaderboardArchive, { makeRequest.key, makeRequest.count, makeRequest.after  }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);


}