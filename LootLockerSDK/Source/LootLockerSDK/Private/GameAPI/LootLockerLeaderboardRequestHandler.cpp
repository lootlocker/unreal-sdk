// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

FString ULootLockerLeaderboardRequestHandler::ListLeaderboards(const FLootLockerPlayerData& PlayerData, int Count, int After, const FLootLockerListLeaderboardsResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
	if (After > 0) { QueryParams.Add("after", FString::FromInt(After)); }
	return LLAPI<FLootLockerListLeaderboardsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListLeaderboards, {}, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::GetMemberRank(const FLootLockerPlayerData& PlayerData, const FLootLockerGetMemberRankRequest& MemberRequest, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerGetMemberRankResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMemberRank, { MemberRequest.leaderboard_key, MemberRequest.member_id }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::GetByListOfMembers(const FLootLockerPlayerData& PlayerData, const FLootLockerGetByListMembersRequest& GetScoreByListRequests, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerGetByListOfMembersResponse>::CallAPI(GetScoreByListRequests, ULootLockerGameEndpoints::GetByListOfMembers, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::GetScoreList(const FLootLockerPlayerData& PlayerData, const FLootLockerGetScoreListRequest& GetScoreListRequests, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
	int32 after = GetScoreListRequests.after < 0 ? 0 : GetScoreListRequests.after;
	return LLAPI<FLootLockerGetScoreListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetScoreList, { GetScoreListRequests.leaderboard_key, GetScoreListRequests.count, after }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::SubmitScore(const FLootLockerPlayerData& PlayerData, const FLootLockerSubmitScoreRequest& SubmitScoreRequests, FString LeaderboardKey, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerSubmitScoreResponse>::CallAPI(SubmitScoreRequests, ULootLockerGameEndpoints::SubmitScore, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::QueryScore(const FLootLockerPlayerData& PlayerData, const FLootLockerQueryScoreRequest& QueryScoreRequests, FString LeaderboardKey, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerSubmitScoreResponse>::CallAPI(QueryScoreRequests, ULootLockerGameEndpoints::QueryScore, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::IncrementScore(const FLootLockerPlayerData& PlayerData, const FLootLockerIncrementScoreRequest& IncrementScoreRequest, FString LeaderboardKey, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerSubmitScoreResponse>::CallAPI(IncrementScoreRequest, ULootLockerGameEndpoints::IncrementScore, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(const FLootLockerPlayerData& PlayerData, const FLootLockerGetAllMemberRanksRequest& GetAllMemberRanksRequests, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("count", FString::FromInt(GetAllMemberRanksRequests.count));
	if (GetAllMemberRanksRequests.after >= 0)
	{
		QueryParams.Add("after", FString::FromInt(GetAllMemberRanksRequests.after));
	}
	return LLAPI<FLootLockerGetAllMemberRanksResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMemberRanks, { GetAllMemberRanksRequests.member_id }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(const FLootLockerPlayerData& PlayerData, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerLeaderboardDetailsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetLeaderboardDetails, { LeaderboardKey }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
