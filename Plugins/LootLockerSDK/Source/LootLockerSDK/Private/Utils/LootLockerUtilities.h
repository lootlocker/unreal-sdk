// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MissionsRequestHandler.h"

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter);

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson);
}
