// Copyright (c) 2021 LootLocker

#pragma once

/// @addtogroup Init
/// @{

#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION >= 5
#include <regex>
#endif
#include "CoreMinimal.h"
#include "Logging/LogVerbosity.h"
#include "LootLockerLogLevel.h"
#include "LootLockerFileConfig.h"

#include "LootLockerConfig.generated.h"

/**
 * Delegate type for configuration update events
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLootLockerConfigurationUpdateDelegate, const FString&, SettingName);

/**
 * Controls how the SDK handles multiple player sessions when a new authentication succeeds.
 * Determines which player is considered the "default" for API calls that do not specify a player ULID.
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerMultiUserSessionMode : uint8
{
	/**
	 * [Not yet configured] The SDK will automatically set the correct mode the first time the project is
	 * loaded with this version of the SDK: new installs (no API key) get SingleSession, existing projects
	 * get Hotseat for backwards compatibility. This value should never be set manually.
	 */
	NotSet          UMETA(Hidden),

	/**
	 * Multiple active sessions are allowed simultaneously.
	 * The first player to authenticate in a game session becomes the default.
	 * Subsequent authentications are additive — they join the active pool but do not change the default.
	 * All player data is retained in persistent cache between sessions.
	 *
	 * Best for: local multiplayer, couch co-op, or any game where multiple players share a device at the same time.
	 */
	Hotseat         UMETA(DisplayName = "Hotseat"),

	/**
	 * Only one player session exists at any given time.
	 * Each new authentication completely wipes all previous session data before saving the new player as the sole active default.
	 * There is always exactly one player in the system; no historical data is kept.
	 *
	 * Best for: standard single-player games where only one account should ever exist on the device.
	 */
	SingleSession   UMETA(DisplayName = "Single Session"),

	/**
	 * Only one player is active at a time, but historical player sessions are retained in a cold cache.
	 * Each new authentication makes that player the sole active and default while all previously active
	 * players are deactivated — but their session data remains on-device.
	 * You can switch back to a previously-authenticated player without re-authenticating.
	 *
	 * Best for: games with an account selection screen, or games where players switch between accounts.
	 */
	ProfileSwitching UMETA(DisplayName = "Profile Switching"),
};

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

	/**
	 * Returns true when a pre-configured file config is active and governing settings.
	 * When true, the Project Settings panel is locked to prevent drift from the file config.
	 */
	static bool IsFileConfigActive();

	/**
	 * Parses a pre-config file's raw content (plain JSON or encrypted) into an FLootLockerFileConfig.
	 * Returns an empty TOptional when content is invalid or api_key is missing/empty.
	 * Exposed publicly so unit tests can call it without needing a real plugin on disk.
	 */
	static TOptional<FLootLockerFileConfig> ParseFileConfigContent(const FString& Content);

	/** Display name used in all editor UI. Publishers change this to rebrand the SDK. */
	inline static const FString PackageName = TEXT("LootLocker");

	/** Name of the Unreal plugin (matches the .uplugin filename). Does not change when PackageName is rebranded. */
	inline static const FString PluginName = TEXT("LootLockerSDK");

	/**
	 * Optional identifier appended to the pre-config file name, e.g. setting this to "acme" causes
	 * the SDK to look for "LootLockerPreConfig-acme.bytes" instead of "LootLockerPreConfig.bytes".
	 */
	inline static const FString ConfigFileIdentifier = TEXT("");

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		ApplyFileConfigIfPresent();
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
		MigrateSettingsIfNeeded();
		LoadFileConfig();
		ApplyFileConfigIfPresent();
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
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker", Meta = (EditCondition = "bIsFileConfigLocked", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "INFO:"), Transient)
	FString FileConfigActiveNotice = "Settings are governed by the pre-configured file config shipped with the plugin and cannot be changed from the editor.";
	/// API Key used to talk to LootLocker. The API key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker", Meta = (DisplayName = "LootLocker API Key", EditCondition = "!bIsFileConfigLocked"))
	FString LootLockerGameKey = "";
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker", Meta = (EditCondition = "!bIsFileConfigLocked"))
    FString GameVersion = "";
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker", Meta = (EditCondition = "!IsValidGameVersion", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString InvalidGameVersionWarning = "Game version needs to follow a numeric Semantic Versioning pattern: X.Y.Z.B with the sections denoting MAJOR.MINOR.PATCH.BUILD and the last two being optional. Read more at https://docs.lootlocker.com/the-basics/core-concepts/glossary#game-version";
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool AllowTokenRefresh = true;
	/// Domain Key used to talk to LootLocker. The Domain key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker", Meta = (EditCondition = "!bIsFileConfigLocked"))
	FString DomainKey = "";
	/// When true, HTTP requests are routed through the legacy ULootLockerHttpClient stack instead of the new
	/// FLootLockerHTTPExecutionQueue. Use this as a temporary escape hatch if you encounter issues with the
	/// new queue. This setting has no effect when the project is compiled with LOOTLOCKER_FORCE_LEGACY_HTTP_STACK=1
	/// (which always uses the legacy stack regardless of this value). This option will be removed once the
	/// execution queue is declared stable.
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker", Meta = (DisplayName = "Use Legacy HTTP Stack", EditCondition = "!bIsFileConfigLocked"))
	bool bUseLegacyHTTPStack = false;
	/// Allow LootLocker to log non error logs outside the editor. This is false by default to avoid log spamming and unintentional logging of data (as LootLocker logs requests and responses vs LootLocker).
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (EditCondition = "!bIsFileConfigLocked"))
	bool LogOutsideOfEditor = false;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (DisplayName = "LootLocker Log Level", EditCondition = "!bIsFileConfigLocked"))
    ELootLockerLogLevel LootLockerLogLevel = ELootLockerLogLevel::Warning;

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

    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (DisplayName = "Enable File Logging", EditCondition = "!bIsFileConfigLocked"))
    bool bEnableFileLogging = false;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Logging", Meta = (DisplayName = "Name of LootLocker Log File", EditCondition = "bEnableFileLogging && !bIsFileConfigLocked", EditConditionHides))
    FString LogFileName = TEXT("LootLockerLog");
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker|Logging", Meta = (EditCondition = "bEnableFileLogging", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "Actual Log File (on current device)"), Transient)
	FString LongLogFilePath = "";

	// ========================================================================
	// PRESENCE CONFIGURATION
	// ========================================================================
	
	/** Enable or disable the entire Presence system globally */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Enable Presence System", EditCondition = "!bIsFileConfigLocked"))
	bool bEnablePresence = false;

	/** Whether to automatically connect presence when sessions are established */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Auto-Connect on Session Start", EditCondition = "bEnablePresence && !bIsFileConfigLocked", EditConditionHides))
	bool bEnablePresenceAutoConnect = true;

	/** Whether to automatically disconnect presence when the application loses focus or goes to background */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Auto-Disconnect on Focus Loss", EditCondition = "bEnablePresence && !bIsFileConfigLocked", EditConditionHides))
	bool bEnablePresenceAutoDisconnectOnFocusChange = true;

	/** Enable presence features in the editor (for testing purposes) */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Presence", Meta = (DisplayName = "Enable In Editor", EditCondition = "bEnablePresence && !bIsFileConfigLocked", EditConditionHides))
	bool bEnablePresenceInEditor = true;

	// ========================================================================
	// MULTI USER CONFIGURATION
	// ========================================================================

	/**
	 * Controls how the SDK handles multiple player sessions when a new authentication succeeds.
	 *
	 * Hotseat: Multiple active sessions allowed. The first authenticated player is default; subsequent
	 * authentications are additive. Best for local multiplayer / couch co-op.
	 *
	 * Single Session: Only one player session exists at a time. New authentications wipe all previous
	 * session data. Best for standard single-player games.
	 *
	 * Profile Switching: Only one player active at a time, but historical players kept in cold cache.
	 * Each new authentication deactivates all others and becomes the sole active default. Best for
	 * games with account selection screens.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker|Multi User", Meta = (DisplayName = "Multi User Session Mode", EditCondition = "!bIsFileConfigLocked"))
	ELootLockerMultiUserSessionMode MultiUserSessionMode = ELootLockerMultiUserSessionMode::NotSet;
private:
	FString LogFilePath = "";
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool IsValidGameVersion = true;
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool bIsFileConfigLocked = false;
	inline static bool bFileConfigChecked = false;
	inline static TOptional<FLootLockerFileConfig> FileConfig;
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool IsOutdatedSDK /** Value in ifdef */
#ifdef LOOTLOCKER_SHOW_OUTDATED_SDK_MESSAGE
		= true
#else
		= false
#endif
	;
#if ENGINE_MAJOR_VERSION >= 5
	inline static const std::regex SemverPattern = std::regex("^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:\\.(0|[1-9]\\d*))?(?:\\.(0|[1-9]\\d*))?$" );
#endif

	/** Performs a one-time migration of settings that were introduced after initial project setup.
	 *  Specifically handles MultiUserSessionMode: if not present in DefaultGame.ini (pre-migration install),
	 *  sets Hotseat for existing projects (backwards compatible) or SingleSession for new installs,
	 *  then persists the result so subsequent loads skip this check. */
	void MigrateSettingsIfNeeded();

	static void LoadFileConfig();
	void ApplyFileConfigIfPresent();
};

/// @}
