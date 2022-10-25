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



void ULootLockerLeaderboardRequestHandler::GetMemberRank(const FLootLockerGetMemberRankRequest& MemberRequest, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetMemberRankResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetMemberRank, { MemberRequest.leaderboardId, MemberRequest.member_id },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetByListOfMembers(const FLootLockerGetByListMembersRequest& GetScoreByListRequests, int LeaderboardId, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetByListOfMembersResponse>::CallAPI(HttpClient, GetScoreByListRequests, ULootLockerGameEndpoints::GetByListOfMembers, { LeaderboardId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetScoreList(const FLootLockerGetScoreListRequest& GetScoreListRequests, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
	if (GetScoreListRequests.after >= 0)
	{
		LLAPI<FLootLockerGetScoreListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetScoreListAfter, { GetScoreListRequests.leaderboardId, GetScoreListRequests.count, GetScoreListRequests.after },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
	}
	else
	{
		LLAPI<FLootLockerGetScoreListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetScoreList, { GetScoreListRequests.leaderboardId, GetScoreListRequests.count },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
	}
}

void ULootLockerLeaderboardRequestHandler::SubmitScore(const FLootLockerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerSubmitScoreResponse>::CallAPI(HttpClient, SubmitScoreRequests, ULootLockerGameEndpoints::SubmitScore, { LeaderboardId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(const FLootLockerGetAllMemberRanksRequest& GetAllMemberRanksRequests, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
    TMap<FString,FString> QueryParams;
    QueryParams.Add("count", FString::FromInt(GetAllMemberRanksRequests.count));
    if (GetAllMemberRanksRequests.after >= 0)
    {
        QueryParams.Add("after", FString::FromInt(GetAllMemberRanksRequests.after));
    }
	LLAPI<FLootLockerGetAllMemberRanksResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllMemberRanks, {GetAllMemberRanksRequests.memberId}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}