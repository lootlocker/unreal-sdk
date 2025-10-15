// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"

#include "LootLockerLeaderboardArchiveRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchivePlayer
{
	GENERATED_BODY()
	// The name of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	// The Public UID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString public_uid = "";
	// The ID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int id = 0;
	// The ULID of the Player.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_ulid = "";
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
	FString metadata = "";
	// The Player's member ID on the Archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString member_id = "";
	// The Player's rank on the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int rank = 0;
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
	FString last_modified = "";
	// The type of content (application/json).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString content_type = "";
	// The Key which is used to identify a json body of an old Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key = "";
	// Length of the archived Leaderboard.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int content_length = 0;
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

DECLARE_DELEGATE_OneParam(FLootLockerLeaderboardArchiveResponseDelegate, FLootLockerLeaderboardArchiveResponse);
DECLARE_DELEGATE_OneParam(FLootLockerLeaderboardArchiveDetailResponseDelegate, FLootLockerLeaderboardArchiveDetailsResponse);


UCLASS()
class LOOTLOCKERSDK_API ULootLockerLeaderboardArchiveRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerLeaderboardArchiveRequestHandler() {};

	static void ListLeaderboardArchive(const FLootLockerPlayerData& PlayerData, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest);
	static void GetLeaderboardArchive(const FLootLockerPlayerData& PlayerData, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest);
};
