// Copyright (c) 2021 LootLocker

// Unit tests for ULootLockerConfig::ParseFileConfigContent.
//
// These tests run without a real plugin/file on disk and exercise the parsing
// of plain-JSON file config content, including default-value fallback, empty
// api_key rejection, and enum string → value round-trips.
//
// Run headless (no backend required):
//   UnrealEditor.exe "YourProject.uproject" -run=automation
//     -ExecCmds="automation RunTests LootLocker.FileConfig"
//     -unattended -nullrhi -nosound -stdout

#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerConfig.h"
#include "LootLockerFileConfig.h"
#include "Misc/AutomationTest.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(
    FLootLockerFileConfigSpec,
    "LootLocker.FileConfig",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
END_DEFINE_SPEC(FLootLockerFileConfigSpec)

void FLootLockerFileConfigSpec::Define()
{
    // -------------------------------------------------------------------------
    // Empty / invalid input
    // -------------------------------------------------------------------------

    It("Returns empty TOptional for empty content", [this]()
    {
        auto Result = ULootLockerConfig::ParseFileConfigContent(TEXT(""));
        TestFalse("TOptional should not be set", Result.IsSet());
    });

    It("Returns empty TOptional for non-JSON content", [this]()
    {
        auto Result = ULootLockerConfig::ParseFileConfigContent(TEXT("not json at all"));
        TestFalse("TOptional should not be set", Result.IsSet());
    });

    It("Returns empty TOptional when api_key is absent", [this]()
    {
        const FString Json = TEXT(R"({"domain_key":"dk","game_version":"2.0.0.0"})");
        auto Result = ULootLockerConfig::ParseFileConfigContent(Json);
        TestFalse("TOptional should not be set when api_key is absent", Result.IsSet());
    });

    It("Returns empty TOptional when api_key is an empty string", [this]()
    {
        const FString Json = TEXT(R"({"api_key":""})");
        auto Result = ULootLockerConfig::ParseFileConfigContent(Json);
        TestFalse("TOptional should not be set when api_key is empty", Result.IsSet());
    });

    // -------------------------------------------------------------------------
    // Minimal / partial JSON (defaults must be preserved)
    // -------------------------------------------------------------------------

    It("Activates when only api_key is provided and fills defaults", [this]()
    {
        const FString Json = TEXT(R"({"api_key":"test-key"})");
        auto Result = ULootLockerConfig::ParseFileConfigContent(Json);
        if (!TestTrue("TOptional should be set", Result.IsSet())) return;

        const FLootLockerFileConfig& Config = Result.GetValue();
        TestEqual("api_key",                   Config.api_key,              FString(TEXT("test-key")));
        TestEqual("domain_key default",        Config.domain_key,           FString(TEXT("")));
        TestEqual("game_version default",      Config.game_version,         FString(TEXT("1.0.0.0")));
        TestTrue( "allow_token_refresh default",  Config.allow_token_refresh);
        TestFalse("log_outside_of_editor default", Config.log_outside_of_editor);
        TestEqual("log_level default",         Config.log_level,            FString(TEXT("Warning")));
        TestFalse("enable_file_logging default",   Config.enable_file_logging);
        TestFalse("enable_presence default",       Config.enable_presence);
        TestTrue( "enable_presence_auto_connect default",  Config.enable_presence_auto_connect);
        TestTrue( "enable_presence_auto_disconnect_on_focus_change default", Config.enable_presence_auto_disconnect_on_focus_change);
        TestTrue( "enable_presence_in_editor default",     Config.enable_presence_in_editor);
        TestEqual("multi_user_session_mode default", Config.multi_user_session_mode, FString(TEXT("NotSet")));
        TestFalse("use_legacy_http_stack default", Config.use_legacy_http_stack);
    });

    // -------------------------------------------------------------------------
    // Full JSON (all runtime fields)
    // -------------------------------------------------------------------------

    It("Parses all runtime fields correctly", [this]()
    {
        const FString Json = TEXT(R"({
            "api_key": "live-key-123",
            "domain_key": "my-domain",
            "game_version": "3.1.4.1",
            "allow_token_refresh": false,
            "log_outside_of_editor": true,
            "log_level": "Verbose",
            "enable_file_logging": true,
            "enable_presence": true,
            "enable_presence_auto_connect": false,
            "enable_presence_auto_disconnect_on_focus_change": false,
            "enable_presence_in_editor": false,
            "multi_user_session_mode": "SingleSession",
            "use_legacy_http_stack": true
        })");

        auto Result = ULootLockerConfig::ParseFileConfigContent(Json);
        if (!TestTrue("TOptional should be set", Result.IsSet())) return;

        const FLootLockerFileConfig& Config = Result.GetValue();
        TestEqual("api_key",                      Config.api_key,              FString(TEXT("live-key-123")));
        TestEqual("domain_key",                   Config.domain_key,           FString(TEXT("my-domain")));
        TestEqual("game_version",                 Config.game_version,         FString(TEXT("3.1.4.1")));
        TestFalse("allow_token_refresh",          Config.allow_token_refresh);
        TestTrue( "log_outside_of_editor",        Config.log_outside_of_editor);
        TestEqual("log_level",                    Config.log_level,            FString(TEXT("Verbose")));
        TestTrue( "enable_file_logging",          Config.enable_file_logging);
        TestTrue( "enable_presence",              Config.enable_presence);
        TestFalse("enable_presence_auto_connect", Config.enable_presence_auto_connect);
        TestFalse("enable_presence_auto_disconnect_on_focus_change", Config.enable_presence_auto_disconnect_on_focus_change);
        TestFalse("enable_presence_in_editor",    Config.enable_presence_in_editor);
        TestEqual("multi_user_session_mode",      Config.multi_user_session_mode, FString(TEXT("SingleSession")));
        TestTrue( "use_legacy_http_stack",        Config.use_legacy_http_stack);
    });

    // -------------------------------------------------------------------------
    // build_flags section is silently ignored at runtime
    // -------------------------------------------------------------------------

    It("Ignores build_flags section without error", [this]()
    {
        const FString Json = TEXT(R"({
            "api_key": "key",
            "build_flags": {
                "enable_google_subsystem_helper": true,
                "force_legacy_http_stack": true
            }
        })");

        auto Result = ULootLockerConfig::ParseFileConfigContent(Json);
        TestTrue("TOptional should be set even with build_flags present", Result.IsSet());
    });

    // -------------------------------------------------------------------------
    // Enum string round-trips via ApplyFileConfigIfPresent (via StaticEnum reflection)
    // -------------------------------------------------------------------------

    Describe("log_level strings map to ELootLockerLogLevel via reflection", [this]()
    {
        const TArray<TPair<FString, ELootLockerLogLevel>> Cases = {
            { TEXT("Error"),       ELootLockerLogLevel::Error       },
            { TEXT("Warning"),     ELootLockerLogLevel::Warning     },
            { TEXT("Display"),     ELootLockerLogLevel::Display     },
            { TEXT("Verbose"),     ELootLockerLogLevel::Verbose     },
            { TEXT("VeryVerbose"), ELootLockerLogLevel::VeryVerbose },
            { TEXT("NoLogging"),   ELootLockerLogLevel::NoLogging   },
        };

        for (const auto& Pair : Cases)
        {
            const FString LogLevelName = Pair.Key;
            const ELootLockerLogLevel Expected = Pair.Value;

            It(FString::Printf(TEXT("'%s' maps correctly"), *LogLevelName), [this, LogLevelName, Expected]()
            {
                const UEnum* Enum = StaticEnum<ELootLockerLogLevel>();
                if (!TestNotNull("ELootLockerLogLevel UEnum must exist", Enum)) return;

                const int64 Value = Enum->GetValueByNameString(LogLevelName);
                TestNotEqual(FString::Printf(TEXT("'%s' must be a valid enum name"), *LogLevelName),
                    Value, static_cast<int64>(INDEX_NONE));
                TestEqual("Mapped value matches expected",
                    static_cast<ELootLockerLogLevel>(Value), Expected);
            });
        }
    });

    Describe("multi_user_session_mode strings map to ELootLockerMultiUserSessionMode via reflection", [this]()
    {
        const TArray<TPair<FString, ELootLockerMultiUserSessionMode>> Cases = {
            { TEXT("Hotseat"),         ELootLockerMultiUserSessionMode::Hotseat         },
            { TEXT("SingleSession"),   ELootLockerMultiUserSessionMode::SingleSession   },
            { TEXT("ProfileSwitching"),ELootLockerMultiUserSessionMode::ProfileSwitching },
        };

        for (const auto& Pair : Cases)
        {
            const FString ModeName = Pair.Key;
            const ELootLockerMultiUserSessionMode Expected = Pair.Value;

            It(FString::Printf(TEXT("'%s' maps correctly"), *ModeName), [this, ModeName, Expected]()
            {
                const UEnum* Enum = StaticEnum<ELootLockerMultiUserSessionMode>();
                if (!TestNotNull("ELootLockerMultiUserSessionMode UEnum must exist", Enum)) return;

                const int64 Value = Enum->GetValueByNameString(ModeName);
                TestNotEqual(FString::Printf(TEXT("'%s' must be a valid enum name"), *ModeName),
                    Value, static_cast<int64>(INDEX_NONE));
                TestEqual("Mapped value matches expected",
                    static_cast<ELootLockerMultiUserSessionMode>(Value), Expected);
            });
        }
    });
}

#endif // ENGINE_MAJOR_VERSION > 4
