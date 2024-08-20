// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerLeaderboardRequestHandler.generated.h"

UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerLeaderboardRewardEntityKind : uint8
{
    Asset = 0,
    Currency = 1,
    Progression_Points = 2,
    Progression_Reset = 3,
    Group = 4,
};

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
struct FLootLockerAssetRewardDetails
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString thumbnail;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString variation_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString rental_option_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int legacy_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString id;

};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardAssetReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerAssetRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString asset_rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString reward_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString asset_ulid;
};

USTRUCT(BlueprintType)
struct FLootLockerCurrencyRewardDetails
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString code;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString amount;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString id;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardCurrencyReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString amount;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerCurrencyRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString reward_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString currency_id;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionResetRewardDetails
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString id;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardProgressionResetReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString progression_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerProgressionResetRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString reward_id;

};

USTRUCT(BlueprintType)
struct FLootLockerProgressionPointRewardDetails
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int amount = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString id;
};


USTRUCT(BlueprintType)
struct FLootLockerLeaderboardProgressionPointsReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerProgressionPointRewardDetails details;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int amount = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString progression_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString reward_id;

};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardRewardArgs
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int max = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int min = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString direction;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardDetailPredicates
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerLeaderboardRewardArgs args;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardSchedule 
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString cron_expression;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString next_run;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString last_run;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FString> schedule;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardGroupRewardAssociation 
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerLeaderboardRewardEntityKind kind = ELootLockerLeaderboardRewardEntityKind::Asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardCurrencyReward currency;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardProgressionResetReward progression_reset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardProgressionPointsReward progression_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardAssetReward asset;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardGroupRewardMetadata
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardGroupReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLeaderboardGroupRewardMetadata> metadata;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLeaderboardGroupRewardAssociation> associations;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString reward_id;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerLeaderboardRewardEntityKind reward_kind = ELootLockerLeaderboardRewardEntityKind::Asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLeaderboardDetailPredicates> predicates;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardCurrencyReward currency;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardProgressionResetReward progression_reset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardProgressionPointsReward progression_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardAssetReward asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardGroupReward group;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString reward_id;

};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardDetailsResponse : public FLootLockerResponse 
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString direction_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int game_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool enable_game_api_writes = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overwrite_score_on_submit = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool has_metadata = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLeaderboardSchedule schedule;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLeaderboardReward> rewards;

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
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaderboardDetailsResponseBP, FLootLockerLeaderboardDetailsResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerGetMemberRankResponseDelegate, FLootLockerGetMemberRankResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetByListOfMembersResponseDelegate, FLootLockerGetByListOfMembersResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetScoreListResponseDelegate, FLootLockerGetScoreListResponse);
DECLARE_DELEGATE_OneParam(FLootLockerSubmitScoreResponseDelegate, FLootLockerSubmitScoreResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetAllMemberRanksResponseDelegate, FLootLockerGetAllMemberRanksResponse)
DECLARE_DELEGATE_OneParam(FLootLockerLeaderboardDetailsResponseDelegate, FLootLockerLeaderboardDetailsResponse)

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
    static void GetLeaderboardDetails(const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP = FLootLockerLeaderboardDetailsResponseBP(), const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest = FLootLockerLeaderboardDetailsResponseDelegate());
public:
    ULootLockerLeaderboardRequestHandler();
    static ULootLockerHttpClient* HttpClient;
};
