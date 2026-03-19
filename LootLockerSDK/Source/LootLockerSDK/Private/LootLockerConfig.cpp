// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"

namespace {
    // Used for runtime log level override
    static bool bRuntimeLogLevelOverrideSet = false;
    static ELootLockerLogLevel RuntimeLogLevelOverride = ELootLockerLogLevel::NoLogging;
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
    if (LogDir.IsEmpty())
    {
        LogDir = FPaths::EngineSavedDir() / TEXT("Logs");
    }
    FString DateAppendix = FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d"));
    Config->LogFilePath = FPaths::Combine(LogDir, FileName + TEXT("_") + DateAppendix + TEXT(".log"));
    Config->LongLogFilePath = FPaths::ConvertRelativePathToFull(Config->LogFilePath);
#if ENGINE_MAJOR_VERSION >= 5
    Config->TryUpdateDefaultConfigFile();
#else
    Config->UpdateDefaultConfigFile();
#endif
}

void ULootLockerConfig::DisableFileLogging()
{
    ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
    Config->bEnableFileLogging = false;
    Config->LogFilePath = TEXT("");
    Config->LongLogFilePath = "";
#if ENGINE_MAJOR_VERSION >= 5
    Config->TryUpdateDefaultConfigFile();
#else
    Config->UpdateDefaultConfigFile();
#endif
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

// ========================================================================
// PRESENCE CONFIGURATION IMPLEMENTATIONS
// ========================================================================

bool ULootLockerConfig::IsPresenceEnabled()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->bEnablePresence;
}

bool ULootLockerConfig::IsPresenceAutoConnectEnabled()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->bEnablePresence && Config->bEnablePresenceAutoConnect;
}

bool ULootLockerConfig::IsPresenceAutoDisconnectOnFocusChangeEnabled()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->bEnablePresence && Config->bEnablePresenceAutoDisconnectOnFocusChange;
}

bool ULootLockerConfig::IsPresenceEnabledInEditor()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->bEnablePresence && Config->bEnablePresenceInEditor;
}
