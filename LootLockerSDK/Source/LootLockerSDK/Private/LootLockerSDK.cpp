// Copyright (c) 2021 LootLocker

#include "LootLockerSDK.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerConfig.h"
#endif

#define LOCTEXT_NAMESPACE "FLootLockerSDKModule"
void FLootLockerSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "LootLocker",
			LOCTEXT("LootLockerSDKSettingsName", "LootLockerSDK"),
			LOCTEXT("LootLockerSDKSettingsDescription", "Configure LootLockerSDK."),
			GetMutableDefault<ULootLockerConfig>()
		);
	}
#endif
}

void FLootLockerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
