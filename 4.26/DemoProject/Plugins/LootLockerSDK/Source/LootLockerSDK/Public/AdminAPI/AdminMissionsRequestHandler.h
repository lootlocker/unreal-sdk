// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "GameAPI/MissionsRequestHandler.h"
#include "AdminMissionsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAMissionFilter {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString value;
};

USTRUCT(BlueprintType)
struct FAMission {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int game_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int map_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString poster_path = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int rounds = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString round_length = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int completion_bonus = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString difficulty_name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float difficulty_multiplier = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int time_score_multiplier = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMissionGoal> goals;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMissionCheckpoint> checkpoints;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAMissionFilter> filters;
};

USTRUCT(BlueprintType)
struct FAMissionResponse : public FLootLockerResponse {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAMission mission;
};

USTRUCT(BlueprintType)
struct FAMissionsResponse : public FLootLockerResponse {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAMission> missions;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAMissionResponseDelegate, FAMissionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAMissionsResponseDelegate, FAMissionsResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminMissionsRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Missions", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CreateMission(const FAMission& MissionData, const FAMissionResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Missions", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateMission(int MissionId, const FAMission& MissionData, const FAMissionResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Missions", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetAllMissions(int GameId, const FAMissionsResponseDelegate& OnComplete);
    
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
