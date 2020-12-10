// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "AssetsRequestHandler.h"
#include "MissionsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerMissionGoalAsset
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerAsset assets;
};

USTRUCT(BlueprintType)
struct FLootLockerMissionGoal
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString goal;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMissionGoalAsset> asssets;
};

USTRUCT(BlueprintType)
struct FLootLockerMissionCheckpoint
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int index;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int time;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, FString> parameters;
};

USTRUCT(BlueprintType)
struct FLootLockerMission
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString mission_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int rounds;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString round_length;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString difficulty_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float difficulty_multiplier;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString difficulty_color;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int difficulty_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMissionGoal> goals;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMissionCheckpoint> checkpoints;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool player_access;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString best_goal;
};

USTRUCT(BlueprintType)
struct FCheckpointTime
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int index;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int time;
};

USTRUCT(BlueprintType)
struct FFinishMissionPayload
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString finish_time;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString finish_score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCheckpointTime> checkpoint_times;
};

USTRUCT(BlueprintType)
struct FFinishMissionData
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString signature;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FFinishMissionPayload payload;
};

USTRUCT(BlueprintType)
struct FMissionsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMission> missions;
};

USTRUCT(BlueprintType)
struct FMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerMission mission;
};

USTRUCT(BlueprintType)
struct FStartMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString signature;
};

USTRUCT(BlueprintType)
struct FFinishMissionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool check_grant_notifications;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMissionsResponseDelegateBP, FMissionsResponse, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMissionResponseDelegateBP, FMissionResponse, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartMissionResponseDelegateBP, FStartMissionResponse, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishMissionResponseDelegateBP, FFinishMissionResponse, Response);
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
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
