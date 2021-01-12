// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoMissions.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ADemoMissions : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int MissionId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FFinishMissionData MissionData;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoGetAllMissions();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoGetMission();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoStartMission();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Missions")
    void DemoFinishMission();
    
    void OnGetAllMissionsCompleted(FMissionsResponse Response);
    void OnGetMissionCompleted(FMissionResponse Response);
    void OnStartMissionCompleted(FStartMissionResponse Response);
    void OnFinishMissionCompleted(FFinishMissionResponse Response);
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
