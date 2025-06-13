// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerLeaderboardRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerLeaderboardRequestHandler::ULootLockerLeaderboardRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerLeaderboardRequestHandler::ListLeaderboards(const FLootLockerPlayerData& PlayerData, int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP, const FLootLockerListLeaderboardsResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
	if (After > 0) { QueryParams.Add("after", FString::FromInt(After)); }
	LLAPI<FLootLockerListLeaderboardsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListLeaderboards, {}, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetMemberRank(const FLootLockerPlayerData& PlayerData, const FLootLockerGetMemberRankRequest& MemberRequest, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetMemberRankResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMemberRank, { MemberRequest.leaderboard_key, MemberRequest.member_id }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetByListOfMembers(const FLootLockerPlayerData& PlayerData, const FLootLockerGetByListMembersRequest& GetScoreByListRequests, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetByListOfMembersResponse>::CallAPI(HttpClient, GetScoreByListRequests, ULootLockerGameEndpoints::GetByListOfMembers, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetScoreList(const FLootLockerPlayerData& PlayerData, const FLootLockerGetScoreListRequest& GetScoreListRequests, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
	int32 after = GetScoreListRequests.after < 0 ? 0 : GetScoreListRequests.after;
	LLAPI<FLootLockerGetScoreListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetScoreList, { GetScoreListRequests.leaderboard_key, GetScoreListRequests.count, after }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::SubmitScore(const FLootLockerPlayerData& PlayerData, const FLootLockerSubmitScoreRequest& SubmitScoreRequests, FString LeaderboardKey, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerSubmitScoreResponse>::CallAPI(HttpClient, SubmitScoreRequests, ULootLockerGameEndpoints::SubmitScore, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(const FLootLockerPlayerData& PlayerData, const FLootLockerGetAllMemberRanksRequest& GetAllMemberRanksRequests, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("count", FString::FromInt(GetAllMemberRanksRequests.count));
	if (GetAllMemberRanksRequests.after >= 0)
	{
		QueryParams.Add("after", FString::FromInt(GetAllMemberRanksRequests.after));
	}
	LLAPI<FLootLockerGetAllMemberRanksResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMemberRanks, { GetAllMemberRanksRequests.member_id }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(const FLootLockerPlayerData& PlayerData, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP, const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerLeaderboardDetailsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetLeaderboardDetails, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}
