// Copyright (c) 2021 LootLocker

#pragma once

#include "GameAPI/MissionsRequestHandler.h"
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
