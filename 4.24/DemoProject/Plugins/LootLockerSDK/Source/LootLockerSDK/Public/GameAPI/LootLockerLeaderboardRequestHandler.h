// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerLeaderboardRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerPlayer
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString public_uid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerGetMemberRankResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rank;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPlayer player;
};

USTRUCT(BlueprintType)
struct FLootLockerMember
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rank;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPlayer player;
};

USTRUCT(BlueprintType)
struct FLootLockerPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int total;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int next_cursor;

};
USTRUCT(BlueprintType)
struct FLootLockerGetByListOfMembersResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMember> members;
};

USTRUCT(BlueprintType)
struct FLootLockerGetScoreListResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPagination pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMember> members;
};


USTRUCT(BlueprintType)
struct FLootLockerSubmitScoreResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rank;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
};

USTRUCT(BlueprintType)
struct FLootLockerSubmitScoreRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
};

USTRUCT(BlueprintType)
struct FLootLockerGetMemberRankRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int leaderboardId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int member_id;
};

USTRUCT(BlueprintType)
struct FLootLockerGetScoreListRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int leaderboardId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int count;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int after;
};

USTRUCT(BlueprintType)
struct FLootLockerGetByListMembersRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> members;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetMemberRankResponseBP, FLootLockerGetMemberRankResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetByListOfMembersResponseBP, FLootLockerGetByListOfMembersResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetScoreListResponseBP, FLootLockerGetScoreListResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSubmitScoreResponseBP, FLootLockerSubmitScoreResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerGetMemberRankResponseDelegate, FLootLockerGetMemberRankResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetByListOfMembersResponseDelegate, FLootLockerGetByListOfMembersResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetScoreListResponseDelegate, FLootLockerGetScoreListResponse);
DECLARE_DELEGATE_OneParam(FLootLockerSubmitScoreResponseDelegate, FLootLockerSubmitScoreResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerLeaderboardRequestHandler : public UObject
{
	GENERATED_BODY()
public:
    static void GetMemberRank(const FLootLockerGetMemberRankRequest& MemberRequest, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP = FLootLockerGetMemberRankResponseBP(), const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest = FLootLockerGetMemberRankResponseDelegate());
    static void GetByListOfMembers(const FLootLockerGetByListMembersRequest& GetScoreByListRequests, int LeaderboardId, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP = FLootLockerGetByListOfMembersResponseBP(), const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest = FLootLockerGetByListOfMembersResponseDelegate());
    static void GetScoreList(const FLootLockerGetScoreListRequest& GetScoreListRequests, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP = FLootLockerGetScoreListResponseBP(), const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest = FLootLockerGetScoreListResponseDelegate());
    static void SubmitScore(const FLootLockerSubmitScoreRequest& SubmitScoreRequests, int LeaderboardId, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP = FLootLockerSubmitScoreResponseBP(), const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest = FLootLockerSubmitScoreResponseDelegate());


public:
    ULootLockerLeaderboardRequestHandler();
    static ULootLockerHttpClient* HttpClient;

};
