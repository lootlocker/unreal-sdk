// Copyright (c) 2025 LootLocker
#include "LootLockerLogger.h"
#include "LootLockerConfig.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"

// Define the log category for LootLocker SDK
DEFINE_LOG_CATEGORY_STATIC(LogLootLockerGameSDK, Log, All);

ELootLockerLogLevel FLootLockerLogger::GetEffectiveLogLevel()
{
    // Prefer runtime override if set
    return ULootLockerConfig::GetRuntimeLogLevel();
}

// Note: SetRuntimeLogLevel is not recursive; it delegates to config static method.
void FLootLockerLogger::SetRuntimeLogLevel(ELootLockerLogLevel NewLevel)
{
    ULootLockerConfig::SetRuntimeLogLevel(NewLevel);
}

static bool ShouldLogAtLevel(ELootLockerLogLevel MessageLevel)
{
    if (!ULootLockerConfig::ShouldLog())
    {
        return false;
    }
    ELootLockerLogLevel MinLevel = FLootLockerLogger::GetEffectiveLogLevel();
    // Lower enum value = higher severity (e.g., Error < Warning < Log)
    return MessageLevel <= MinLevel;
}

void FLootLockerLogger::Log(const FString& Message, ELootLockerLogLevel Verbosity)
{
    if (!ShouldLogAtLevel(Verbosity)) return;
    // Log the message using Unreal's logging system
    LogInternal(Verbosity, *Message);
}

void FLootLockerLogger::Logf(ELootLockerLogLevel Verbosity, const TCHAR* Format, ...)
{
    if (!ShouldLogAtLevel(Verbosity)) return;
    constexpr int32 BufferSize = 4096;
    TCHAR Buffer[BufferSize];
    va_list ArgPtr;
    va_start(ArgPtr, Format);
    FCString::GetVarArgs(Buffer, BufferSize, Format, ArgPtr);
    va_end(ArgPtr);
    LogInternal(Verbosity, Buffer);
}

void FLootLockerLogger::LogInfo(const FString& Message)
{
    Log(Message, ELootLockerLogLevel::Log);
}

void FLootLockerLogger::LogWarning(const FString& Message)
{
    Log(Message, ELootLockerLogLevel::Warning);
}

void FLootLockerLogger::LogError(const FString& Message)
{
    Log(Message, ELootLockerLogLevel::Error);
}

void FLootLockerLogger::LogVerbose(const FString& Message)
{
    Log(Message, ELootLockerLogLevel::Verbose);
}

void FLootLockerLogger::LogVeryVerbose(const FString& Message)
{
    Log(Message, ELootLockerLogLevel::VeryVerbose);
}

FCriticalSection FLootLockerLogger::FileLogCriticalSection;

void FLootLockerLogger::EnableFileLogging(const FString& FileName)
{
    // Delegate to config static method
    ULootLockerConfig::EnableFileLogging(FileName);
}

void FLootLockerLogger::DisableFileLogging()
{
    // Delegate to config static method
    ULootLockerConfig::DisableFileLogging();
}

bool FLootLockerLogger::IsFileLoggingEnabled()
{
    // Delegate to config static method
    return ULootLockerConfig::IsFileLoggingEnabled();
}

FString FLootLockerLogger::GetLogFilePath()
{
    // Delegate to config static method
    return ULootLockerConfig::GetLogFilePath();
}

void FLootLockerLogger::WriteToFile(const FString& Message)
{
    if (!IsFileLoggingEnabled()) return;
    FScopeLock Lock(&FileLogCriticalSection);
    // Add ISO 8601 timestamp
    FString Timestamp = FDateTime::UtcNow().ToIso8601();
    FString OutLine = FString::Printf(TEXT("[%s] %s%s"), *Timestamp, *Message, LINE_TERMINATOR);
    FString LogFilePath = GetLogFilePath();
    FFileHelper::SaveStringToFile(OutLine, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

FLootLockerOnLogMessage FLootLockerLogger::OnLogMessage;
FLootLockerOnHttpLogEntry FLootLockerLogger::OnHttpLogEntry;

void FLootLockerLogger::LogHttpRequest(const FLootLockerHttpLogEntry& Entry)
{
    // Compose a log line for file/console (for legacy log output)
    FString LogLine = FString::Printf(TEXT("%s request to %s %s in %.6fs\n   HTTP Status code : %d"),
        *Entry.Method,
        *Entry.Path,
        Entry.bSuccess ? TEXT("succeeded") : TEXT("failed"),
        Entry.Duration,
        Entry.StatusCode);
    if (!Entry.RequestData.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Request Data: %s"), *Entry.RequestData);
    if (!Entry.ResponseData.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Response Data: %s"), *Entry.ResponseData);
    if (!Entry.RequestHeaders.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Request Headers: %s"), *Entry.RequestHeaders);
    if (!Entry.ErrorMessage.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Error Message: %s"), *Entry.ErrorMessage);
    if (!Entry.ErrorCode.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Error Code: %s"), *Entry.ErrorCode);
    if (!Entry.ErrorDocUrl.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Further Information: %s"), *Entry.ErrorDocUrl);
    if (!Entry.ErrorRequestId.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Request ID: %s"), *Entry.ErrorRequestId);
    if (!Entry.ErrorTraceId.IsEmpty())
        LogLine += FString::Printf(TEXT("\n   Trace ID: %s"), *Entry.ErrorTraceId);
    LogLine += TEXT("\n###");
    // Log to file/console at appropriate level
    Log( LogLine, Entry.bSuccess ? ELootLockerLogLevel::Log : ELootLockerLogLevel::Error );
    // Broadcast to UI
    OnHttpLogEntry.Broadcast(Entry);
}

void FLootLockerLogger::LogInternal(ELootLockerLogLevel Verbosity, const TCHAR* m)
{
    if (Verbosity == ELootLockerLogLevel::NoLogging)
    {
        return; // No logging requested
    }
    // Write to file if enabled
    if (IsFileLoggingEnabled())
    {
        // Only print the value, not the enum type name
        const UEnum* EnumPtr = StaticEnum<ELootLockerLogLevel>();
        FString VerbosityString = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Verbosity) : TEXT("Unknown");
        VerbosityString.RemoveFromStart(TEXT("ELootLockerLogLevel::"));
        WriteToFile(FString::Printf(TEXT("[%s] %s"), *VerbosityString, m));
    }
    // Broadcast to UI
    OnLogMessage.Broadcast(FString(m), Verbosity);
    switch(Verbosity)
    {
        case ELootLockerLogLevel::NoLogging: return;
        case ELootLockerLogLevel::Fatal: __LogInternalF(m); return;
        case ELootLockerLogLevel::Error: __LogInternalE(m); return;
        case ELootLockerLogLevel::Warning: __LogInternalW(m); return;
        case ELootLockerLogLevel::Display: __LogInternalD(m); return;
        case ELootLockerLogLevel::Log: __LogInternalL(m); return;
        case ELootLockerLogLevel::Verbose: __LogInternalV(m); return;
        case ELootLockerLogLevel::VeryVerbose: __LogInternalVV(m); return;
        default: __LogInternalW(m); return; // Fallback to Warning if unknown level
    }
}

void FLootLockerLogger::__LogInternalF(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, Fatal, TEXT("%s"), m); }

void FLootLockerLogger::__LogInternalE(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, Error, TEXT("%s"), m); }

void FLootLockerLogger::__LogInternalW(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, Warning, TEXT("%s"), m); }

void FLootLockerLogger::__LogInternalD(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, Display, TEXT("%s"), m); }

void FLootLockerLogger::__LogInternalL(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, Log, TEXT("%s"), m); }

void FLootLockerLogger::__LogInternalV(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("%s"), m); }

void FLootLockerLogger::__LogInternalVV(const TCHAR* m) { UE_LOG(LogLootLockerGameSDK, VeryVerbose, TEXT("%s"), m); }
