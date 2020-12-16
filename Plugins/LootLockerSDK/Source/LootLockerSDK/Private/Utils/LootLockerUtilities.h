// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MissionsRequestHandler.h"
#include "AdminAPI/AdminMissionsRequestHandler.h"
#include "AdminAPI/AdminTriggersRequestHandler.h"

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter);

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson);

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints);

    FString SerializeMission(const FAMission& Mission);

    FString SerializeTrigger(const FATriggerPayload& Trigger);
}
