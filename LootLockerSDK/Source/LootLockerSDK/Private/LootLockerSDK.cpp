// Copyright (c) 2021 LootLocker

#include "LootLockerSDK.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerConfig.h"
#endif

#include "LootLockerPersistentData.h"
#include "LootLockerSaveState.h"
#include "UObject/ConstructorHelpers.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Kismet/GameplayStatics.h"


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
	
	if (ULootLockerSaveState* LoadedState = Cast<ULootLockerSaveState>(UGameplayStatics::LoadGameFromSlot(ULootLockerSaveState::SaveSlot, ULootLockerSaveState::SaveIndex)))
	{
		ULootLockerPersistentData::Token = LoadedState->Token;
		ULootLockerPersistentData::AdminToken = LoadedState->AdminToken;
		ULootLockerPersistentData::PlayerIdentifier = LoadedState->PlayerIdentifier;
		ULootLockerPersistentData::SteamToken = LoadedState->SteamToken;
		ULootLockerPersistentData::WhiteLabelEmail = LoadedState->WhiteLabelEmail;
		ULootLockerPersistentData::WhiteLabelToken = LoadedState->WhiteLabelToken;

		UE_LOG(LogLootLockerGameSDK, Log, TEXT("Loaded state from disk for player with identifier %s"), *ULootLockerPersistentData::PlayerIdentifier);
	}

#endif
}

void FLootLockerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	bool SuccessfullySaved = false;
	if (ULootLockerSaveState* SavedState = Cast<ULootLockerSaveState>(UGameplayStatics::CreateSaveGameObject(ULootLockerSaveState::StaticClass())))
	{
		SavedState->Token = ULootLockerPersistentData::Token;
		SavedState->AdminToken = ULootLockerPersistentData::AdminToken;
		SavedState->PlayerIdentifier = ULootLockerPersistentData::PlayerIdentifier;
		SavedState->SteamToken = ULootLockerPersistentData::SteamToken;
		SavedState->WhiteLabelEmail = ULootLockerPersistentData::WhiteLabelEmail;
		SavedState->WhiteLabelToken = ULootLockerPersistentData::WhiteLabelToken;
		
		SuccessfullySaved = UGameplayStatics::SaveGameToSlot(SavedState, ULootLockerSaveState::SaveSlot, ULootLockerSaveState::SaveIndex);
	}
	if(!SuccessfullySaved)
	{
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to save LootLocker state to disk"));
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
