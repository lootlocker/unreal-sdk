// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "LootLockerLogger.h"

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

#if defined(LOOTLOCKER_COMMANDLINE_SETTINGS)
void ULootLockerConfig::CheckForSettingOverrides()
{
    const TCHAR* CommandLine = FCommandLine::Get();
    if (!CommandLine)
    {
        return;
    }

    FString Value;
    bool bAnyOverrideApplied = false;

    // Check for -lootlockerkey or -apikey
    if (FParse::Value(CommandLine, TEXT("-lootlockerkey="), Value) || FParse::Value(CommandLine, TEXT("-apikey="), Value))
    {
        LootLockerGameKey = Value;
        FLootLockerLogger::LogVerbose(TEXT("Command line override: LootLockerGameKey"));
        bAnyOverrideApplied = true;
    }

    // Check for -lootlockerdomainkey or -domainkey
    if (FParse::Value(CommandLine, TEXT("-lootlockerdomainkey="), Value) || FParse::Value(CommandLine, TEXT("-domainkey="), Value))
    {
        DomainKey = Value;
        FLootLockerLogger::LogVerbose(TEXT("Command line override: DomainKey"));
        bAnyOverrideApplied = true;
    }

    // Check for -lootlockerversion or -gameversion
    if (FParse::Value(CommandLine, TEXT("-lootlockerversion="), Value) || FParse::Value(CommandLine, TEXT("-gameversion="), Value))
    {
        GameVersion = Value;
        IsValidGameVersion = IsSemverString(GameVersion);
        FLootLockerLogger::LogVerbose(FString::Printf(TEXT("Command line override: GameVersion = %s"), *Value));
        bAnyOverrideApplied = true;
    }

    // Check for -lootlockerlogging or -loglevel
    if (FParse::Value(CommandLine, TEXT("-lootlockerlogging="), Value) || FParse::Value(CommandLine, TEXT("-loglevel="), Value))
    {
        if (Value.Equals(TEXT("NoLogging"), ESearchCase::IgnoreCase))
        {
            LootLockerLogLevel = ELootLockerLogLevel::NoLogging;
        }
        else if (Value.Equals(TEXT("Error"), ESearchCase::IgnoreCase) || Value.Equals(TEXT("Errors"), ESearchCase::IgnoreCase))
        {
            LootLockerLogLevel = ELootLockerLogLevel::Error;
        }
        else if (Value.Equals(TEXT("Warning"), ESearchCase::IgnoreCase) || Value.Equals(TEXT("Warnings"), ESearchCase::IgnoreCase))
        {
            LootLockerLogLevel = ELootLockerLogLevel::Warning;
        }
        else if (Value.Equals(TEXT("Verbose"), ESearchCase::IgnoreCase) || Value.Equals(TEXT("All"), ESearchCase::IgnoreCase))
        {
            LootLockerLogLevel = ELootLockerLogLevel::Verbose;
        }
        FLootLockerLogger::LogVerbose(FString::Printf(TEXT("Command line override: LootLockerLogLevel = %s"), *Value));
        bAnyOverrideApplied = true;
    }

    // Check for -lootlockerlogfile or -logfile
    if (FParse::Value(CommandLine, TEXT("-lootlockerlogfile="), Value) || FParse::Value(CommandLine, TEXT("-logfile="), Value))
    {
        if (!Value.IsEmpty())
        {
            LogFileName = Value;
            bEnableFileLogging = true;
            EnableFileLogging(LogFileName);
            FLootLockerLogger::LogVerbose(FString::Printf(TEXT("Command line override: LogFileName = %s"), *Value));
            bAnyOverrideApplied = true;
        }
    }

    // Check for -lootlockerallowrefresh or -allowtokenrefresh
    if (FParse::Param(CommandLine, TEXT("lootlockerallowrefresh")) || FParse::Param(CommandLine, TEXT("allowtokenrefresh")))
    {
        AllowTokenRefresh = true;
        FLootLockerLogger::LogVerbose(TEXT("Command line override: AllowTokenRefresh = true"));
        bAnyOverrideApplied = true;
    }
    else if (FParse::Param(CommandLine, TEXT("lootlockerdisablerefresh")) || FParse::Param(CommandLine, TEXT("disabletokenrefresh")))
    {
        AllowTokenRefresh = false;
        FLootLockerLogger::LogVerbose(TEXT("Command line override: AllowTokenRefresh = false"));
        bAnyOverrideApplied = true;
    }

    // Check for -lootlockerlogoutside or -logoutside
    if (FParse::Param(CommandLine, TEXT("lootlockerlogoutside")) || FParse::Param(CommandLine, TEXT("logoutside")))
    {
        LogOutsideOfEditor = true;
        FLootLockerLogger::LogVerbose(TEXT("Command line override: LogOutsideOfEditor = true"));
        bAnyOverrideApplied = true;
    }
    else if (FParse::Param(CommandLine, TEXT("lootlockernologoutside")) || FParse::Param(CommandLine, TEXT("nologoutside")))
    {
        LogOutsideOfEditor = false;
        FLootLockerLogger::LogVerbose(TEXT("Command line override: LogOutsideOfEditor = false"));
        bAnyOverrideApplied = true;
    }

    if (bAnyOverrideApplied)
    {
        FLootLockerLogger::LogVerbose(TEXT("LootLocker configuration overridden via command line arguments"));
    }
}
#endif
