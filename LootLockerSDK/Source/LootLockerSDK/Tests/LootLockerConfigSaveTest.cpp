// Copyright (c) 2021 LootLocker

// Regression test for issue #1411:
// EnableFileLogging() and DisableFileLogging() must not overwrite settings in
// DefaultGame.ini that belong to other sections/plugins.
//
// Run headless from the command line (no backend connection required):
//   UnrealEditor.exe "YourProject.uproject" -run=automation
//     -ExecCmds="automation RunTests LootLocker.Config.SaveConfigPreservesOtherIniSettings"
//     -unattended -nullrhi -nosound -stdout

#include "LootLockerConfig.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/ConfigCacheIni.h"

#if ENGINE_MAJOR_VERSION > 4

/**
 * Verifies that calling EnableFileLogging / DisableFileLogging does not wipe
 * other sections in DefaultGame.ini (regression for issue #1411).
 *
 * The test is tagged SmokeFilter so it can run without network access and will
 * be included in any local or CI smoke pass.
 */
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FLootLockerConfigSavePreservesOtherIniSettingsTest,
    "LootLocker.Config.SaveConfigPreservesOtherIniSettings",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter
)

bool FLootLockerConfigSavePreservesOtherIniSettingsTest::RunTest(const FString& Parameters)
{
    // -------------------------------------------------------------------------
    // 1. Locate the DefaultGame.ini that ULootLockerConfig writes to.
    // -------------------------------------------------------------------------
    ULootLockerConfig* MutableConfig = GetMutableDefault<ULootLockerConfig>();
    const FString ConfigFilename = MutableConfig->GetDefaultConfigFilename();

    if (!TestFalse("DefaultGame.ini path should not be empty", ConfigFilename.IsEmpty()))
    {
        return false;
    }

    // -------------------------------------------------------------------------
    // 2. Save original file-logging state so we can restore it after the test.
    // -------------------------------------------------------------------------
    const bool bWasEnabled = ULootLockerConfig::IsFileLoggingEnabled();
    const FString OriginalLogFileName = MutableConfig->LogFileName;

    // -------------------------------------------------------------------------
    // 3. Write a "sentinel" entry into a section that LootLocker has nothing to
    //    do with, simulating settings from another plugin stored in the same
    //    DefaultGame.ini.
    // -------------------------------------------------------------------------
    const TCHAR* SentinelSection = TEXT("/Script/IssueRegression1411.SentinelConfig");
    const TCHAR* SentinelKey     = TEXT("SentinelValue_1411");
    const TCHAR* SentinelValue   = TEXT("MUST_BE_PRESERVED_ACROSS_SAVECONFIG");

    GConfig->SetString(SentinelSection, SentinelKey, SentinelValue, ConfigFilename);
    GConfig->Flush(false, ConfigFilename);

    // Confirm the sentinel is on disk before we do any LootLocker operations.
    FString DiskContentsBeforeEnable;
    if (!TestTrue("Config file should be readable from disk",
            FFileHelper::LoadFileToString(DiskContentsBeforeEnable, *ConfigFilename)))
    {
        return false;
    }
    TestTrue("Sentinel value should be present on disk before calling EnableFileLogging",
        DiskContentsBeforeEnable.Contains(SentinelValue));

    // -------------------------------------------------------------------------
    // 4. EnableFileLogging — this triggered the bug before the fix.
    // -------------------------------------------------------------------------
    ULootLockerConfig::EnableFileLogging(TEXT("LootLockerTestLog_1411"));

    // Read the file directly from disk (bypasses GConfig in-memory state).
    FString DiskContentsAfterEnable;
    TestTrue("Config file should still be readable from disk after EnableFileLogging",
        FFileHelper::LoadFileToString(DiskContentsAfterEnable, *ConfigFilename));

    const bool bSentinelSurvivesEnable = DiskContentsAfterEnable.Contains(SentinelValue);
    TestTrue(
        "After EnableFileLogging, settings from unrelated sections must not be erased "
        "from DefaultGame.ini.  A FAIL here indicates issue #1411 is not fixed.",
        bSentinelSurvivesEnable);

    // -------------------------------------------------------------------------
    // 5. DisableFileLogging — same check.
    // -------------------------------------------------------------------------
    ULootLockerConfig::DisableFileLogging();

    FString DiskContentsAfterDisable;
    TestTrue("Config file should still be readable from disk after DisableFileLogging",
        FFileHelper::LoadFileToString(DiskContentsAfterDisable, *ConfigFilename));

    const bool bSentinelSurvivesDisable = DiskContentsAfterDisable.Contains(SentinelValue);
    TestTrue(
        "After DisableFileLogging, settings from unrelated sections must not be erased "
        "from DefaultGame.ini.  A FAIL here indicates issue #1411 is not fixed.",
        bSentinelSurvivesDisable);

    // -------------------------------------------------------------------------
    // 6. Cleanup — remove the sentinel and restore the original logging config.
    // -------------------------------------------------------------------------
    GConfig->RemoveKey(SentinelSection, SentinelKey, ConfigFilename);
    GConfig->Flush(false, ConfigFilename);

    if (bWasEnabled)
    {
        ULootLockerConfig::EnableFileLogging(
            OriginalLogFileName.IsEmpty() ? TEXT("LootLockerLog") : OriginalLogFileName);
    }

    return bSentinelSurvivesEnable && bSentinelSurvivesDisable;
}

#endif // ENGINE_MAJOR_VERSION > 4
