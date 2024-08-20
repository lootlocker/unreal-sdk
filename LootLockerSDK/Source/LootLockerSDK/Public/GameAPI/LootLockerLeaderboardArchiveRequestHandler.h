// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"

#include "LootLockerLeaderboardArchiveRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchivePlayer
{
	GENERATED_BODY()
	// The name of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	// The Public UID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString public_uid;
	// The ID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	// The ULID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_ulid;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveDetails 
{
	GENERATED_BODY()
	// The Player on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerLeaderboardArchivePlayer player;
	// Metadata if any was supplied.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString metadata;
	// The Player's member ID on the Archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString member_id;
	// The Player's rank on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 rank = 0;
	// The Player's Score on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int score = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchive
{
	GENERATED_BODY()
	// The date when the archived Leaderboard was modified.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString last_modified;
	// The type of content (application/json).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString content_type;
	// The Key which is used to identify a json body of an old Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key;
	// Length of the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 content_length = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveDetailsResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	// A list of players and details from the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerLeaderboardArchiveDetails> items;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	// A List of past Leaderboards.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerLeaderboardArchive> archives;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaderboardArchiveResponseBP, FLootLockerLeaderboardArchiveResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaderboardArchiveDetailReponseBP, FLootLockerLeaderboardArchiveDetailsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerLeaderboardArchiveResponseDelegate, FLootLockerLeaderboardArchiveResponse);
DECLARE_DELEGATE_OneParam(FLootLockerLeaderboardArchiveDetailResponseDelegate, FLootLockerLeaderboardArchiveDetailsResponse);


UCLASS()
class LOOTLOCKERSDK_API ULootLockerLeaderboardArchiveRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	static void ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP = FLootLockerLeaderboardArchiveResponseBP(), const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest = FLootLockerLeaderboardArchiveResponseDelegate());
	static void GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP = FLootLockerLeaderboardArchiveDetailReponseBP(), const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest = FLootLockerLeaderboardArchiveDetailResponseDelegate());
public:
	ULootLockerLeaderboardArchiveRequestHandler();
	static ULootLockerHttpClient* HttpClient;
};