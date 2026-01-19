// Copyright (c) 2021 LootLocker

#pragma once

#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION >= 5
#include <regex>
#endif
#include "CoreMinimal.h"
#include "Logging/LogVerbosity.h"
#include "LootLockerLogLevel.h"

#include "LootLockerConfig.generated.h"

/**
 * Delegate type for configuration update events
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLootLockerConfigurationUpdateDelegate, const FString&, SettingName);

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "LootLocker SDK Settings"))
class LOOTLOCKERSDK_API ULootLockerConfig : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION()
	static bool IsSemverString(const FString& str)
	{
#if ENGINE_MAJOR_VERSION >= 5
		return std::regex_match(TCHAR_TO_UTF8(*str), SemverPattern);
#else
		return true;
#endif
	}
	
	FLootLockerConfigurationUpdateDelegate OnConfigurationUpdated;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		if (PropertyChangedEvent.GetPropertyName() == "GameVersion")
		{
			IsValidGameVersion = IsSemverString(GameVersion);
		}
		if (PropertyChangedEvent.GetPropertyName() == "bEnableFileLogging" || PropertyChangedEvent.GetPropertyName() == "LogFileName")
		{
			if (bEnableFileLogging)
			{
				EnableFileLogging(LogFileName.IsEmpty() ? "LootLockerLog" : LogFileName);
			}
			else
			{
				DisableFileLogging();
			}
		}
		OnConfigurationUpdated.Broadcast(PropertyChangedEvent.GetPropertyName().ToString());
		UObject::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif //WITH_EDITOR
	virtual void PostInitProperties() override
	{
		IsValidGameVersion = IsSemverString(GameVersion);
		if(bEnableFileLogging)
		{
			EnableFileLogging(LogFileName.IsEmpty() ? "LootLockerLog" : LogFileName);
		}
		else
		{
			DisableFileLogging();
		}
		UObject::PostInitProperties();
	}

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker", Meta = (EditCondition = "IsOutdatedSDK", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString OutdatedSDKWarning = "This version of LootLocker is no longer updated through fab because of fab guidelines. Please use GitHub releases to update: https://github.com/lootlocker/unreal-sdk/releases";
	// API Key used to talk to LootLocker. The API key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker", Meta = (DisplayName = "LootLocker API Key"))
	FString LootLockerGameKey = "";
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString GameVersion = "";
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker", Meta = (EditCondition = "!IsValidGameVersion", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString InvalidGameVersionWarning = "Game version needs to follow a numeric Semantic Versioning pattern: X.Y.Z.B with the sections denoting MAJOR.MINOR.PATCH.BUILD and the last two being optional. Read more at https://docs.lootlocker.com/the-basics/core-concepts/glossary#game-version";
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool AllowTokenRefresh = true;
	// Domain Key used to talk to LootLocker. The Domain key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString DomainKey = "";
	// Allow LootLocker to log non error logs outside the editor. This is false by default to avoid log spamming and unintentional logging of data (as LootLocker logs requests and responses vs LootLocker).
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging")
	bool LogOutsideOfEditor = false;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (DisplayName = "LootLocker Log Level"))
    ELootLockerLogLevel LootLockerLogLevel;

	UFUNCTION()
	static bool ShouldLog()
	{
#if WITH_EDITOR
		return true;
#else
		return GetDefault<ULootLockerConfig>()->LogOutsideOfEditor;
#endif
	}

    // Returns the configured log level from config or ini
    static ELootLockerLogLevel GetConfiguredLogLevel()
    {
        return GetDefault<ULootLockerConfig>()->LootLockerLogLevel;
    }
    /**
     * Sets the log level at runtime (not persisted).
     * @param NewLevel The new log level to use for this session.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static void SetRuntimeLogLevel(ELootLockerLogLevel NewLevel);
    /**
     * Gets the current runtime log level (runtime override or config).
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static ELootLockerLogLevel GetRuntimeLogLevel();
    /**
     * Enables file logging to the specified file name.
     * @param FileName The log file name (relative to project log dir).
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static void EnableFileLogging(const FString& FileName);
    /**
     * Disables file logging.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static void DisableFileLogging();
    /**
     * Returns true if file logging is enabled and a log file name is set.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static bool IsFileLoggingEnabled();
    /**
     * Returns the current log file path (may be empty if not enabled).
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Logging")
    static FString GetLogFilePath();

	// ========================================================================
	// PRESENCE CONFIGURATION ACCESSORS
	// ========================================================================

    /**
     * Check if presence system is enabled globally.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Presence")
    static bool IsPresenceEnabled();

    /**
     * Check if auto-connect is enabled for presence.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Presence")
    static bool IsPresenceAutoConnectEnabled();

    /**
     * Check if auto-disconnect on focus change is enabled.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Presence")
    static bool IsPresenceAutoDisconnectOnFocusChangeEnabled();

    /**
     * Check if presence is enabled in the editor.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker|Presence")
    static bool IsPresenceEnabledInEditor();

    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (DisplayName = "Enable File Logging"))
    bool bEnableFileLogging = false;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (DisplayName = "Name of LootLocker Log File", EditCondition = "bEnableFileLogging", EditConditionHides))
    FString LogFileName = TEXT("LootLockerLog");
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker|Logging", Meta = (EditCondition = "bEnableFileLogging", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "Actual Log File (on current device)"), Transient)
	FString LongLogFilePath = "";

	// ========================================================================
	// PRESENCE CONFIGURATION
	// ========================================================================
	
	/** Enable or disable the entire Presence system globally */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Enable Presence System"))
	bool bEnablePresence = false;

	/** Whether to automatically connect presence when sessions are established */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Auto-Connect on Session Start", EditCondition = "bEnablePresence", EditConditionHides))
	bool bEnablePresenceAutoConnect = true;

	/** Whether to automatically disconnect presence when the application loses focus or goes to background */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Auto-Disconnect on Focus Loss", EditCondition = "bEnablePresence", EditConditionHides))
	bool bEnablePresenceAutoDisconnectOnFocusChange = true;

	/** Enable presence features in the editor (for testing purposes) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Enable In Editor", EditCondition = "bEnablePresence", EditConditionHides))
	bool bEnablePresenceInEditor = true;
private:
	FString LogFilePath = "";
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool IsValidGameVersion = true;
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool IsOutdatedSDK /* Value in ifdef */
#ifdef LOOTLOCKER_SHOW_OUTDATED_SDK_MESSAGE
		= true
#else
		= false
#endif
	;
#if ENGINE_MAJOR_VERSION >= 5
	inline static const std::regex SemverPattern = std::regex("^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:\\.(0|[1-9]\\d*))?(?:\\.(0|[1-9]\\d*))?$" );
#endif

public:
    ULootLockerConfig();
private:
};
