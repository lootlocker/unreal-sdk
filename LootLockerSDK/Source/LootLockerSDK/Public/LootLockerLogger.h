// Copyright (c) 2025 LootLocker
#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerErrorData.h"
#include "LootLockerRequestContext.h"
#include "Delegates/Delegate.h"
#include "LootLockerConfig.h"
#include "LootLockerLogger.generated.h"

class ULootLockerConfig;

// Represents a structured HTTP log entry for logging and UI display
USTRUCT(BlueprintType)
struct FLootLockerHttpLogEntry
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString Method = "";
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString Path = "";
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    int32 StatusCode = -1;
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    float Duration = 0.0f;
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString RequestData = "";
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString ResponseData = "";
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString RequestHeaders = "";
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    bool bSuccess = false;
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FDateTime Timestamp;
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FLootLockerErrorData ErrorData;
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FLootLockerRequestContext RequestContext;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FLootLockerOnLogMessage, const FString&, ELootLockerLogLevel);
DECLARE_MULTICAST_DELEGATE_OneParam(FLootLockerOnHttpLogEntry, const FLootLockerHttpLogEntry&);

/**
 * Centralized logger for the LootLocker SDK. Not exposed to Blueprints.
 * Usage: FLootLockerLogger::Log("Message");
 */
class LOOTLOCKERSDK_API FLootLockerLogger
{
public:
    /**
     * Logs a message at the specified verbosity level.
     * @param Message The message to log.
     * @param Verbosity The log verbosity level (default: Verbose).
     */
    static void Log(const FString& Message, ELootLockerLogLevel Verbosity = ELootLockerLogLevel::Verbose);

    /**
     * Logs a formatted message at the specified verbosity level.
     * @param Verbosity The log verbosity level.
     * @param Format The format string.
     * @param ... Arguments for the format string.
     */
    static void Logf(ELootLockerLogLevel Verbosity, const TCHAR* Format, ...);

    /**
     * Logs an info-level message.
     * @param Message The message to log.
     */
    static void LogInfo(const FString& Message);

    /**
     * Logs a warning-level message.
     * @param Message The message to log.
     */
    static void LogWarning(const FString& Message);

    /**
     * Logs an error-level message.
     * @param Message The message to log.
     */
    static void LogError(const FString& Message);

    /**
     * Logs a verbose-level message.
     * @param Message The message to log.
     */
    static void LogVerbose(const FString& Message);

    /**
     * Logs a very verbose-level message.
     * @param Message The message to log.
     */
    static void LogVeryVerbose(const FString& Message);

    /**
     * Gets the effective log level (runtime override or config).
     */
    static ELootLockerLogLevel GetEffectiveLogLevel();

    /**
     * Sets the log level at runtime (not persisted).
     * @param NewLevel The new log level to use for this session.
     */
    static void SetRuntimeLogLevel(ELootLockerLogLevel NewLevel);

    /**
     * Enables file logging to the specified file path.
     * @param FilePath The log file name (relative to project log dir).
     */
    static void EnableFileLogging(const FString& FilePath);

    /**
     * Disables file logging.
     */
    static void DisableFileLogging();

    /**
     * Returns true if file logging is enabled and a log file name is set.
     */
    static bool IsFileLoggingEnabled();

    /**
     * Returns the current log file path (may be empty if not enabled).
     */
    static FString GetLogFilePath();

    /**
     * Delegate for log messages (for UI, not for general use).
     */
    static FLootLockerOnLogMessage OnLogMessage;

    /**
     * Delegate for HTTP log entries (for UI, not for general use).
     */
    static FLootLockerOnHttpLogEntry OnHttpLogEntry;

    /**
     * Logs a structured HTTP request/response entry.
     * @param Entry The HTTP log entry.
     */
    static void LogHttpRequest(const FLootLockerHttpLogEntry& Entry);

    /**
     * Logs a structured HTTP request/response entry.
     * @param Entry The HTTP log entry.
     */
    static void LogHttpRequest(const FLootLockerResponse& Response, const FString& AllHeadersDelimited = "N/A");
private:
    static void LogInternal(ELootLockerLogLevel Verbosity, const TCHAR* m);
    static void __LogInternalF(const TCHAR* m);
    static void __LogInternalE(const TCHAR* m);
    static void __LogInternalW(const TCHAR* m);
    static void __LogInternalD(const TCHAR* m);
    static void __LogInternalL(const TCHAR* m);
    static void __LogInternalV(const TCHAR* m);
    static void __LogInternalVV(const TCHAR* m);
    static void WriteToFile(const FString& Message);
    static FCriticalSection FileLogCriticalSection;
    FLootLockerLogger() = delete;
};
