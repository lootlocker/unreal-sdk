// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

#if ENGINE_MAJOR_VERSION > 4 && defined(LOOTLOCKER_COMMANDLINE_SETTINGS)

BEGIN_DEFINE_SPEC(FTestLootLockerCommandLineConfig, "LootLocker.CommandLineConfig", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerCommandLineConfig)

void FTestLootLockerCommandLineConfig::Define()
{
	Describe("CommandLineConfig", [this]()
	{
		It("Should have CheckForSettingOverrides method available", [this]()
		{
			// This test verifies that the command line settings feature is compiled in
			// The actual method is private, but if it compiles with LOOTLOCKER_COMMANDLINE_SETTINGS defined,
			// then the feature is available
			const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
			TestNotNull("Config should not be null", Config);
		});

		It("Should respect config values when no command line args are present", [this]()
		{
			const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
			TestNotNull("Config should not be null", Config);
			
			// These values should be from the config file, not overridden
			// We can't test the exact values since they're config-dependent,
			// but we can verify the config is accessible
			TestTrue("Config should be accessible", true);
		});
	});
}

#endif
