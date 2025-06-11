// Copyright (c) 2025 LootLocker
#pragma once

#include "CoreMinimal.h"
#include "LootLockerLogLevel.generated.h"

/**
 * Enum for LootLocker log verbosity levels.
 * Compatible with UE4.27+ (no C++17 features).
 */
UENUM(BlueprintType)
enum class ELootLockerLogLevel : uint8
{
    /** No logging will be performed. */
    NoLogging     UMETA(DisplayName = "No Logging"),
    /** Fatal errors that cause the application to crash. */
    Fatal         UMETA(DisplayName = "Fatal"),
    /** Error messages indicating a problem. */
    Error         UMETA(DisplayName = "Error"),
    /** Warning messages indicating a potential issue. */
    Warning       UMETA(DisplayName = "Warning"),
    /** Display messages for important runtime information. */
    Display       UMETA(DisplayName = "Display"),
    /** General log messages. */
    Log           UMETA(DisplayName = "Log"),
    /** Verbose log messages for debugging. */
    Verbose       UMETA(DisplayName = "Verbose"),
    /** Very verbose log messages for deep debugging. */
    VeryVerbose   UMETA(DisplayName = "Very Verbose")
};