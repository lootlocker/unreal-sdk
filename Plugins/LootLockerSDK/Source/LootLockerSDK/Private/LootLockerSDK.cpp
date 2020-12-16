// Copyright Epic Games, Inc. All Rights Reserved.

#include "LootLockerSDK.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerConfig.h"


#define LOCTEXT_NAMESPACE "FLootLockerSDKModule"

void FLootLockerSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR
    
    LootLockerSettings = NewObject<ULootLockerConfig>(GetTransientPackage(), "LootLockerSettings", RF_Standalone);
    LootLockerSettings->AddToRoot();

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "LootLockerSDK",
			LOCTEXT("LootLockerSDKSettingsName", "LootLockerSDK"),
			LOCTEXT("LootLockerSDKSettingsDescription", "Configure LootLockerSDK."),
			LootLockerSettings
		);
	}

#endif
}

void FLootLockerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
      SettingsModule->UnregisterSettings("Project", "Plugins", "LootLockerSDK");
    }

    if (!GExitPurge)
    {
      // If we're in exit purge, this object has already been destroyed
      LootLockerSettings->RemoveFromRoot();
    }
    else
    {
      LootLockerSettings = nullptr;
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
