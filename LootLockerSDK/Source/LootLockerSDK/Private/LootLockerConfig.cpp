// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"

namespace {
    // Used for runtime log level override
    static bool bRuntimeLogLevelOverrideSet = false;
    static ELootLockerLogLevel RuntimeLogLevelOverride = ELootLockerLogLevel::NoLogging;

#if ENGINE_MAJOR_VERSION < 5
    // UE4.27 compatibility: static regex pattern for semver
    static const std::regex SemverPattern("^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:\\.(0|[1-9]\\d*))?(?:\\.(0|[1-9]\\d*))?$" );
#endif
}

ULootLockerConfig::ULootLockerConfig()
{
    LootLockerLogLevel = ELootLockerLogLevel::Warning;
}

void ULootLockerConfig::SetRuntimeLogLevel(ELootLockerLogLevel NewLevel)
{
    // Set the runtime log level override directly in config
    RuntimeLogLevelOverride = NewLevel;
    bRuntimeLogLevelOverrideSet = true;
}

ELootLockerLogLevel ULootLockerConfig::GetRuntimeLogLevel()
{
    if (bRuntimeLogLevelOverrideSet)
    {
        return RuntimeLogLevelOverride;
    }
    return GetConfiguredLogLevel();
}

void ULootLockerConfig::EnableFileLogging(const FString& FileName)
{
    ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
    Config->bEnableFileLogging = true;
    Config->LogFileName = FileName;
    FString LogDir = FPaths::ProjectLogDir();
    Config->LogFilePath = FPaths::Combine(LogDir, FileName);
    Config->LongLogFilePath = FPaths::ConvertRelativePathToFull(Config->LogFilePath);
    Config->SaveConfig();
}

void ULootLockerConfig::DisableFileLogging()
{
    ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
    Config->bEnableFileLogging = false;
    Config->LogFilePath = TEXT("");
    Config->LongLogFilePath = "";
    Config->SaveConfig();
}

bool ULootLockerConfig::IsFileLoggingEnabled()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->bEnableFileLogging && !Config->LogFileName.IsEmpty();
}

FString ULootLockerConfig::GetLogFilePath()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->LogFilePath;
}
