// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerMissionsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerMissionGoalAsset
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAsset assets;
};

USTRUCT(BlueprintType)
struct FLootLockerMissionGoal
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString goal;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMissionGoalAsset> assets;
};

USTRUCT(BlueprintType)
struct FLootLockerMissionCheckpoint
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int index = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int time = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> parameters;
};

USTRUCT(BlueprintType)
struct FLootLockerMission
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int mission_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int map_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int type = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rounds = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString round_length;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString difficulty_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float difficulty_multiplier = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString difficulty_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int difficulty_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString,FLootLockerMissionGoal> goals;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMissionCheckpoint> checkpoints;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool player_access = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString best_goal;
};

USTRUCT(BlueprintType)
struct FLootLockerCheckpointTime
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int index = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int time = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerFinishMissionPayload
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString finish_time;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString finish_score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCheckpointTime> checkpoint_times;
};

USTRUCT(BlueprintType)
struct FLootLockerFinishMissionData
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString signature;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerFinishMissionPayload payload;
};

USTRUCT(BlueprintType)
struct FLootLockerMissionsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMission> missions;
};

USTRUCT(BlueprintType)
struct FLootLockerMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerMission mission;
};

USTRUCT(BlueprintType)
struct FLootLockerStartMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString signature;
};

USTRUCT(BlueprintType)
struct FLootLockerFinishMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool check_grant_notifications = false;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FMissionsResponseDelegateBP, FLootLockerMissionsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FMissionResponseDelegateBP, FLootLockerMissionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStartMissionResponseDelegateBP, FLootLockerStartMissionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FFinishMissionResponseDelegateBP, FLootLockerFinishMissionResponse, Response);
DECLARE_DELEGATE_OneParam(FMissionsResponseDelegate, FLootLockerMissionsResponse);
DECLARE_DELEGATE_OneParam(FMissionResponseDelegate, FLootLockerMissionResponse);
DECLARE_DELEGATE_OneParam(FStartMissionResponseDelegate, FLootLockerStartMissionResponse);
DECLARE_DELEGATE_OneParam(FFinishMissionResponseDelegate, FLootLockerFinishMissionResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerMissionsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerMissionsRequestHandler();
    
    static void GetAllMissions(const FMissionsResponseDelegateBP& OnCompletedRequestBP = FMissionsResponseDelegateBP(), const FMissionsResponseDelegate& OnCompletedRequest = FMissionsResponseDelegate());
    
    static void GetMission(int MissionId, const FMissionResponseDelegateBP& OnCompletedRequestBP = FMissionResponseDelegateBP(), const FMissionResponseDelegate& OnCompletedRequest = FMissionResponseDelegate());
    
    static void StartMission(int MissionId, const FStartMissionResponseDelegateBP& OnCompletedRequestBP = FStartMissionResponseDelegateBP(), const FStartMissionResponseDelegate& OnCompletedRequest = FStartMissionResponseDelegate());
    
    static void FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnCompletedRequestBP = FFinishMissionResponseDelegateBP(), const FFinishMissionResponseDelegate& OnCompletedRequest = FFinishMissionResponseDelegate());

public:
    static ULootLockerHttpClient* HttpClient;
};
