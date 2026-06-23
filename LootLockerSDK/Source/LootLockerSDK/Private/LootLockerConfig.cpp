// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"
#include "Misc/Paths.h"
#include "Misc/DateTime.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Interfaces/IPluginManager.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/AES.h"
#include "Misc/Base64.h"

namespace {
    // Used for runtime log level override
    static bool bRuntimeLogLevelOverrideSet = false;
    static ELootLockerLogLevel RuntimeLogLevelOverride = ELootLockerLogLevel::NoLogging;
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

// ========================================================================
// MULTI USER CONFIGURATION IMPLEMENTATION
// ========================================================================

void ULootLockerConfig::MigrateSettingsIfNeeded()
{
	// Check whether MultiUserSessionMode has ever been written to the INI file.
	// If the key is absent (pre-migration install), choose the correct default:
	//   - Existing project (API key already configured) -> Hotseat, for backwards compatibility.
	//   - New install (no API key yet)                  -> SingleSession, the simpler default.
	// After writing the value the key will be present on all subsequent loads and this block is skipped.
	// Use GetDefaultConfigFilename() so the read target matches the write target used by
	// TryUpdateDefaultConfigFile()/UpdateDefaultConfigFile(), regardless of platform or test harness.
	const FString IniFilePath = GetDefaultConfigFilename();
	FString ExistingValue;
	const bool bWasExplicitlySet = GConfig && GConfig->GetString(
		TEXT("/Script/LootLockerSDK.LootLockerConfig"),
		TEXT("MultiUserSessionMode"),
		ExistingValue,
		IniFilePath
	);

	if (!bWasExplicitlySet)
	{
		MultiUserSessionMode = LootLockerGameKey.IsEmpty()
			? ELootLockerMultiUserSessionMode::SingleSession
			: ELootLockerMultiUserSessionMode::Hotseat;
#if WITH_EDITOR
		// Only persist to disk in Editor contexts — packaged builds may be installed to
		// read-only locations, and the runtime value set above is sufficient there.
#if ENGINE_MAJOR_VERSION >= 5
		TryUpdateDefaultConfigFile();
#else
		UpdateDefaultConfigFile();
#endif
#endif
	}
}

bool ULootLockerConfig::IsPresenceEnabledInEditor()
{
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    return Config->bEnablePresence && Config->bEnablePresenceInEditor;
}

// ========================================================================
// FILE CONFIG IMPLEMENTATION
// ========================================================================

bool ULootLockerConfig::IsFileConfigActive()
{
    if (!bFileConfigChecked)
    {
        ULootLockerConfig::LoadFileConfig();
    }
    return FileConfig.IsSet();
}

// Hardcoded decryption key for pre-config files.
// This is intentionally embedded rather than configurable — the scheme is only meant to
// keep the API key out of casual plain-text searches, not to provide cryptographic security.
inline static const FAES::FAESKey GetFileConfigDecryptionKey()
{
    static const uint8 KeyBytes[32] = {
        0x4C, 0x6F, 0x6F, 0x74, 0x4C, 0x6F, 0x63, 0x6B,
        0x65, 0x72, 0x50, 0x72, 0x65, 0x43, 0x6F, 0x6E,
        0x66, 0x69, 0x67, 0x4B, 0x65, 0x79, 0x32, 0x30,
        0x32, 0x35, 0x41, 0x45, 0x53, 0x32, 0x35, 0x36
    };
    FAES::FAESKey Key;
    FMemory::Memcpy(Key.Key, KeyBytes, 32);
    return Key;
}

TOptional<FLootLockerFileConfig> ULootLockerConfig::ParseFileConfigContent(const FString& Content)
{
    if (Content.IsEmpty())
    {
        return {};
    }

    FString JsonString;

    // Try plain JSON first
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        JsonString = Content;
    }
    else
    {
        // Try AES-256-ECB + PKCS7 + Base64 decryption
        TArray<uint8> EncryptedData;
        if (!FBase64::Decode(Content, EncryptedData))
        {
            return {};
        }

        // FAES operates on whole blocks (AES block size is 16 bytes)
        if (EncryptedData.Num() == 0 || (EncryptedData.Num() % 16) != 0)
        {
            return {};
        }

        const FAES::FAESKey DecryptionKey = GetFileConfigDecryptionKey();
        FAES::DecryptData(EncryptedData.GetData(), EncryptedData.Num(), DecryptionKey);

        // Remove PKCS7 padding
        if (EncryptedData.Num() > 0)
        {
            const uint8 PaddingValue = EncryptedData.Last();
            if (PaddingValue > 0 && PaddingValue <= 16 && PaddingValue <= EncryptedData.Num())
            {
                bool bValidPadding = true;
                for (int32 i = 1; i <= PaddingValue; ++i)
                {
                    if (EncryptedData[EncryptedData.Num() - i] != PaddingValue)
                    {
                        bValidPadding = false;
                        break;
                    }
                }
                if (bValidPadding)
                {
                    EncryptedData.SetNum(EncryptedData.Num() - PaddingValue);
                }
            }
        }

        // Convert decrypted bytes to UTF-8 string (ensure null-terminated for UTF8_TO_TCHAR)
        EncryptedData.Add(0);
        JsonString = UTF8_TO_TCHAR(reinterpret_cast<const char*>(EncryptedData.GetData()));

        // Re-parse the decrypted JSON
        Reader = TJsonReaderFactory<>::Create(JsonString);
        if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
        {
            return {};
        }
    }

    FLootLockerFileConfig Config;
    if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &Config, 0, 0))
    {
        return {};
    }

    // api_key is the gating field — empty or missing means "inactive"
    if (Config.api_key.IsEmpty())
    {
        return {};
    }

    return Config;
}

void ULootLockerConfig::LoadFileConfig()
{
    if (bFileConfigChecked)
    {
        return;
    }

    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(*PluginName);
    if (!Plugin.IsValid())
    {
        bFileConfigChecked = true;
        return;
    }

    // Build filename: PackageName + "PreConfig" + optional "-" + ConfigFileIdentifier + ".bytes"
    FString FileName = PackageName + TEXT("PreConfig");
    if (!ConfigFileIdentifier.IsEmpty())
    {
        FileName += TEXT("-") + ConfigFileIdentifier;
    }
    FileName += TEXT(".bytes");

    const FString FilePath = FPaths::Combine(Plugin->GetBaseDir(), TEXT("Config"), FileName);

    FString Content;
    if (!FFileHelper::LoadFileToString(Content, *FilePath))
    {
        bFileConfigChecked = true;
        return;
    }

    FileConfig = ParseFileConfigContent(Content);
    bFileConfigChecked = true;
}

void ULootLockerConfig::ApplyFileConfigIfPresent()
{
    if (!IsFileConfigActive())
    {
        ULootLockerConfig* Default = GetMutableDefault<ULootLockerConfig>();
        Default->bIsFileConfigLocked = false;
        return;
    }

    const FLootLockerFileConfig& FC = FileConfig.GetValue();
    ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();

    Config->LootLockerGameKey = FC.api_key;
    if (!FC.domain_key.IsEmpty())
    {
        Config->DomainKey = FC.domain_key;
    }
    if (!FC.game_version.IsEmpty())
    {
        Config->GameVersion = FC.game_version;
    }
    Config->IsValidGameVersion = IsSemverString(Config->GameVersion);
    Config->AllowTokenRefresh = FC.allow_token_refresh;
    Config->LogOutsideOfEditor = FC.log_outside_of_editor;

    // Map log_level enum string -> ELootLockerLogLevel via static enum reflection
    if (!FC.log_level.IsEmpty())
    {
        const UEnum* Enum = StaticEnum<ELootLockerLogLevel>();
        const int64 Value = Enum->GetValueByNameString(FC.log_level);
        if (Value != INDEX_NONE)
        {
            Config->LootLockerLogLevel = static_cast<ELootLockerLogLevel>(Value);
        }
    }

    Config->bEnableFileLogging = FC.enable_file_logging;
    Config->bEnablePresence = FC.enable_presence;
    Config->bEnablePresenceAutoConnect = FC.enable_presence_auto_connect;
    Config->bEnablePresenceAutoDisconnectOnFocusChange = FC.enable_presence_auto_disconnect_on_focus_change;
    Config->bEnablePresenceInEditor = FC.enable_presence_in_editor;

    // Map multi_user_session_mode enum string
    if (!FC.multi_user_session_mode.IsEmpty())
    {
        const UEnum* Enum = StaticEnum<ELootLockerMultiUserSessionMode>();
        const int64 Value = Enum->GetValueByNameString(FC.multi_user_session_mode);
        if (Value != INDEX_NONE && Value != static_cast<int64>(ELootLockerMultiUserSessionMode::NotSet))
        {
            Config->MultiUserSessionMode = static_cast<ELootLockerMultiUserSessionMode>(Value);
        }
    }

    Config->bUseLegacyHTTPStack = FC.use_legacy_http_stack;
    Config->bIsFileConfigLocked = true;

    if (Config->bEnableFileLogging)
    {
        EnableFileLogging(Config->LogFileName.IsEmpty() ? TEXT("LootLockerLog") : Config->LogFileName);
    }
    else
    {
        DisableFileLogging();
    }
}

#if ENGINE_MAJOR_VERSION < 5
const FString ULootLockerConfig::PackageName = TEXT("LootLocker");
const FString ULootLockerConfig::PluginName = TEXT("LootLockerSDK");
const FString ULootLockerConfig::ConfigFileIdentifier = TEXT("");
bool ULootLockerConfig::bFileConfigChecked = false;
TOptional<FLootLockerFileConfig> ULootLockerConfig::FileConfig;
#endif
