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
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString public_uid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString player_ulid;


};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveDetails 
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FLootLockerLeaderboardArchivePlayer player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString metadata;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString member_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		int32 rank;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		int score;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveRequest
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		int count;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString after;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchive
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString last_modified;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString content_type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		int32 content_length;
};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveDetailsResponse : public FLootLockerResponse
{
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		TArray<FLootLockerLeaderboardArchiveDetails> items;

};

USTRUCT(BlueprintType)
struct FLootLockerLeaderboardArchiveResponse : public FLootLockerResponse
{
	GENERATED_BODY()
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
	static void ListLeaderboardArchive(FString LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP = FLootLockerLeaderboardArchiveResponseBP(), const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest = FLootLockerLeaderboardArchiveResponseDelegate());
	static void GetLeaderboardArchive(FString Key, int Count, FString After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP = FLootLockerLeaderboardArchiveDetailReponseBP(), const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest = FLootLockerLeaderboardArchiveDetailResponseDelegate());
public:
	ULootLockerLeaderboardArchiveRequestHandler();
	static ULootLockerHttpClient* HttpClient;
};