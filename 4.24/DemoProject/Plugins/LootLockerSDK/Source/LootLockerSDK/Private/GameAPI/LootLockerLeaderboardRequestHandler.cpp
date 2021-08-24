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
	FString ContentString;
	// FJsonObjectConverter::UStructToJsonObjectString(FLootLockerGetMemberRankRequest::StaticStruct(), &MemberRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerGetMemberRankResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetMemberRankResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("GetMemberRank failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetMemberRank;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, { MemberRequest.leaderboardId, MemberRequest.member_id });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerLeaderboardRequestHandler::GetByListOfMembers(const FLootLockerGetByListMembersRequest& GetScoreByListRequests, int LeaderboardId, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerGetByListMembersRequest::StaticStruct(), &GetScoreByListRequests, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerGetByListOfMembersResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetByListOfMembersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("GetByListOfMembers failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetByListOfMembers;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, { LeaderboardId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerLeaderboardRequestHandler::GetScoreList(const FLootLockerGetScoreListRequest& GetScoreListRequests, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	//FJsonObjectConverter::UStructToJsonObjectString(FLootLockerGetScoreListRequest::StaticStruct(), &GetScoreListRequests, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerGetScoreListResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetScoreListResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
				UE_LOG(LogTemp, Error, TEXT("GetScoreList success from lootlocker"));
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("GetScoreList failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetScoreList;
	FString TempEndpoint = Endpoint.endpoint;
	FString newEndpoint = FString::Format(*TempEndpoint, { GetScoreListRequests.leaderboardId,GetScoreListRequests.count });

	if (GetScoreListRequests.after != -1)
	{
		TempEndpoint = Endpoint.endpoint + "&after={2}";
		newEndpoint = FString::Format(*TempEndpoint, { GetScoreListRequests.leaderboardId, GetScoreListRequests.count, GetScoreListRequests.after});
		UE_LOG(LogTemp, Error, TEXT("not minus 1"));
	}

	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerLeaderboardRequestHandler::SubmitScore(const FLootLockerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerSubmitScoreRequest::StaticStruct(), &SubmitScoreRequests, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerSubmitScoreResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerSubmitScoreResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("SubmitScore failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::SubmitScore;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, { LeaderboardId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	UE_LOG(LogTemp, Error, TEXT("%s"), *newEndpoint);
	UE_LOG(LogTemp, Error, TEXT("%s"), *requestMethod);
	UE_LOG(LogTemp, Error, TEXT("%s"), *ContentString);
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
