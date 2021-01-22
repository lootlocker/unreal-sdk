// Copyright (c) 2021 LootLocker

#include "Demo/DemoMissions.h"

void ADemoMissions::DemoGetAllMissions()
{
   ULootLockerSDKManager::GetAllMissions(FMissionsResponseDelegate::CreateUObject(this, &ADemoMissions::OnGetAllMissionsCompleted));
}

void ADemoMissions::DemoGetMission()
{
   ULootLockerSDKManager::GetMission(MissionId, FMissionResponseDelegate::CreateUObject(this, &ADemoMissions::OnGetMissionCompleted));
}

void ADemoMissions::DemoStartMission()
{
   ULootLockerSDKManager::StartMission(MissionId, FStartMissionResponseDelegate::CreateUObject(this, &ADemoMissions::OnStartMissionCompleted));
}

void ADemoMissions::DemoFinishMission()
{
   ULootLockerSDKManager::FinishMission(MissionId, MissionData, FFinishMissionResponseDelegate::CreateUObject(this, &ADemoMissions::OnFinishMissionCompleted));
}

void ADemoMissions::OnGetAllMissionsCompleted(FMissionsResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAllMissions Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAllMissions Failed"));
    }
}

void ADemoMissions::OnGetMissionCompleted(FMissionResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetMission Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetMission Failed"));
    }
}

void ADemoMissions::OnStartMissionCompleted(FStartMissionResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnStartMission Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnStartMission Failed"));
    }
}

void ADemoMissions::OnFinishMissionCompleted(FFinishMissionResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnFinishMission Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnFinishMission Failed"));
    }
}
