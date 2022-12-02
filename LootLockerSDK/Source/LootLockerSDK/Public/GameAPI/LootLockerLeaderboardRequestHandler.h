// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerLeaderboardRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerPlayer
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id = 0;
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
    int rank = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPlayer player;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerMember
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rank = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPlayer player;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboard
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int leaderboard_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString leaderboard_key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerGetMemberRankResponse rank;
};

USTRUCT(BlueprintType)
struct FLootLockerPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int next_cursor = 0;
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
    TArray<FLootLockerMember> items;
};

USTRUCT(BlueprintType)
struct FLootLockerGetAllMemberRanksResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPagination pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLeaderboard> leaderboards;
};

USTRUCT(BlueprintType)
struct FLootLockerSubmitScoreResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rank = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerSubmitScoreRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString metadata;
};

USTRUCT(BlueprintType)
struct FLootLockerGetMemberRankRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString leaderboard_key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerGetScoreListRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString leaderboard_key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int count = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int after = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerGetAllMemberRanksRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString member_id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int count = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int after = 0;
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetAllMemberRanksResponseBP, FLootLockerGetAllMemberRanksResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerGetMemberRankResponseDelegate, FLootLockerGetMemberRankResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetByListOfMembersResponseDelegate, FLootLockerGetByListOfMembersResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetScoreListResponseDelegate, FLootLockerGetScoreListResponse);
DECLARE_DELEGATE_OneParam(FLootLockerSubmitScoreResponseDelegate, FLootLockerSubmitScoreResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetAllMemberRanksResponseDelegate, FLootLockerGetAllMemberRanksResponse)

UCLASS()
class LOOTLOCKERSDK_API ULootLockerLeaderboardRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void GetMemberRank(const FLootLockerGetMemberRankRequest& MemberRequest, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP = FLootLockerGetMemberRankResponseBP(), const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest = FLootLockerGetMemberRankResponseDelegate());
    static void GetByListOfMembers(const FLootLockerGetByListMembersRequest& GetScoreByListRequests, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP = FLootLockerGetByListOfMembersResponseBP(), const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest = FLootLockerGetByListOfMembersResponseDelegate());
    static void GetScoreList(const FLootLockerGetScoreListRequest& GetScoreListRequests, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP = FLootLockerGetScoreListResponseBP(), const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest = FLootLockerGetScoreListResponseDelegate());
    static void SubmitScore(const FLootLockerSubmitScoreRequest& SubmitScoreRequests, FString LeaderboardKey, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP = FLootLockerSubmitScoreResponseBP(), const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest = FLootLockerSubmitScoreResponseDelegate());
    static void GetAllMemberRanks(const FLootLockerGetAllMemberRanksRequest& GetAllMemberRanksRequests, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP = FLootLockerGetAllMemberRanksResponseBP(), const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest = FLootLockerGetAllMemberRanksResponseDelegate());

public:
    ULootLockerLeaderboardRequestHandler();
    static ULootLockerHttpClient* HttpClient;
};
