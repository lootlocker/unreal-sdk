// Copyright (c) 2025 LootLocker
#pragma once

#include "CoreMinimal.h"
#include "LootLockerLogLevel.generated.h"

UENUM(BlueprintType)
enum class ELootLockerLogLevel : uint8
{
    NoLogging     UMETA(DisplayName = "No Logging"),
    Fatal         UMETA(DisplayName = "Fatal"),
    Error         UMETA(DisplayName = "Error"),
    Warning       UMETA(DisplayName = "Warning"),
    Display       UMETA(DisplayName = "Display"),
    Log           UMETA(DisplayName = "Log"),
    Verbose       UMETA(DisplayName = "Verbose"),
    VeryVerbose   UMETA(DisplayName = "Very Verbose")
};