// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "GameAPI/AssetsRequestHandler.h"
#include "MissionsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerMissionGoalAsset
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int variation_id;
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
    int index;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int time;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> parameters;
};

USTRUCT(BlueprintType)
struct FLootLockerMission
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString mission_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rounds;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString round_length;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString difficulty_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float difficulty_multiplier;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString difficulty_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int difficulty_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMissionGoal> goals;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMissionCheckpoint> checkpoints;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool player_access;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString best_goal;
};

USTRUCT(BlueprintType)
struct FCheckpointTime
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int index;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int time;
};

USTRUCT(BlueprintType)
struct FFinishMissionPayload
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString finish_time;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString finish_score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FCheckpointTime> checkpoint_times;
};

USTRUCT(BlueprintType)
struct FFinishMissionData
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString signature;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FFinishMissionPayload payload;
};

USTRUCT(BlueprintType)
struct FMissionsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMission> missions;
};

USTRUCT(BlueprintType)
struct FMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerMission mission;
};

USTRUCT(BlueprintType)
struct FStartMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString signature;
};

USTRUCT(BlueprintType)
struct FFinishMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool check_grant_notifications;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FMissionsResponseDelegateBP, FMissionsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FMissionResponseDelegateBP, FMissionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStartMissionResponseDelegateBP, FStartMissionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FFinishMissionResponseDelegateBP, FFinishMissionResponse, Response);
DECLARE_DELEGATE_OneParam(FMissionsResponseDelegate, FMissionsResponse);
DECLARE_DELEGATE_OneParam(FMissionResponseDelegate, FMissionResponse);
DECLARE_DELEGATE_OneParam(FStartMissionResponseDelegate, FStartMissionResponse);
DECLARE_DELEGATE_OneParam(FFinishMissionResponseDelegate, FFinishMissionResponse);

UCLASS()
class LOOTLOCKERSDK_API UMissionsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    UMissionsRequestHandler();
    
    static void GetAllMissions(const FMissionsResponseDelegateBP& OnCompletedRequestBP = FMissionsResponseDelegateBP(), const FMissionsResponseDelegate& OnCompletedRequest = FMissionsResponseDelegate());
    
    static void GetMission(int MissionId, const FMissionResponseDelegateBP& OnCompletedRequestBP = FMissionResponseDelegateBP(), const FMissionResponseDelegate& OnCompletedRequest = FMissionResponseDelegate());
    
    static void StartMission(int MissionId, const FStartMissionResponseDelegateBP& OnCompletedRequestBP = FStartMissionResponseDelegateBP(), const FStartMissionResponseDelegate& OnCompletedRequest = FStartMissionResponseDelegate());
    
    static void FinishMission(int MissionId, const FFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnCompletedRequestBP = FFinishMissionResponseDelegateBP(), const FFinishMissionResponseDelegate& OnCompletedRequest = FFinishMissionResponseDelegate());

public:
    static UHttpClient* HttpClient;
};
