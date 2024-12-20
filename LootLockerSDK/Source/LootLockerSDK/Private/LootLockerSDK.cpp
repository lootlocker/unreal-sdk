// Copyright (c) 2021 LootLocker

#include "LootLockerSDK.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#endif
#include "LootLockerConfig.h"

#define LOCTEXT_NAMESPACE "FLootLockerSDKModule"
DEFINE_LOG_CATEGORY(LogLootLockerGameSDK);
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
#ifdef LOOTLOCKER_SHOW_OUTDATED_SDK_MESSAGE
	UE_LOG(LogLootLockerGameSDK, Warning, TEXT("This version of LootLocker is no longer updated through fab because of fab guidelines. Please use GitHub releases to update: https://github.com/lootlocker/unreal-sdk/releases. Add `LootLockerSDK.bShowOutdatedSDKMessage = false;` to your game's Build.cs file to hide this warning."));
#endif
#endif
}

void FLootLockerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
