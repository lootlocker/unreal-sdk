// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoMissions.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoMissions : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int MissionId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerFinishMissionData MissionData;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoGetAllMissions();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoGetMission();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoStartMission();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoFinishMission();
    
    void OnGetAllMissionsCompleted(FLootLockerMissionsResponse Response);
    void OnGetMissionCompleted(FLootLockerMissionResponse Response);
    void OnStartMissionCompleted(FLootLockerStartMissionResponse Response);
    void OnFinishMissionCompleted(FLootLockerFinishMissionResponse Response);
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
