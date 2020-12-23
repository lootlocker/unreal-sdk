// Copyright (c) 2020 LootLocker

#include "Demo/DemoMissions.h"

ADemoMissions::ADemoMissions()
{
    LootLockerManager = NewObject<ULootLockerSDKManager>();
}

void ADemoMissions::DemoGetAllMissions()
{
    LootLockerManager->GetAllMissions(FMissionsResponseDelegate::CreateUObject(this, &ADemoMissions::OnGetAllMissionsCompleted));
}

void ADemoMissions::DemoGetMission()
{
    LootLockerManager->GetMission(MissionId, FMissionResponseDelegate::CreateUObject(this, &ADemoMissions::OnGetMissionCompleted));
}

void ADemoMissions::DemoStartMission()
{
    LootLockerManager->StartMission(MissionId, FStartMissionResponseDelegate::CreateUObject(this, &ADemoMissions::OnStartMissionCompleted));
}

void ADemoMissions::DemoFinishMission()
{
    LootLockerManager->FinishMission(MissionId, MissionData, FFinishMissionResponseDelegate::CreateUObject(this, &ADemoMissions::OnFinishMissionCompleted));
}

void ADemoMissions::OnGetAllMissionsCompleted(FMissionsResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAllMissionsCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoMissions::OnGetMissionCompleted(FMissionResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetMissionCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoMissions::OnStartMissionCompleted(FStartMissionResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnStartMissionCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoMissions::OnFinishMissionCompleted(FFinishMissionResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnFinishMissionCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
