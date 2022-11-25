// Copyright (c) 2021 LootLocker

#include "LootLockerSDK.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerConfig.h"
#endif

#include "LootLockerStateData.h"
#include "LootLockerPersistedState.h"
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
	
	if (ULootLockerPersistedState* LoadedState = Cast<ULootLockerPersistedState>(UGameplayStatics::LoadGameFromSlot(ULootLockerPersistedState::SaveSlot, ULootLockerPersistedState::SaveIndex)))
	{
		ULootLockerStateData::Token = LoadedState->Token;
		ULootLockerStateData::AdminToken = LoadedState->AdminToken;
		ULootLockerStateData::PlayerIdentifier = LoadedState->PlayerIdentifier;
		ULootLockerStateData::SteamToken = LoadedState->SteamToken;
		ULootLockerStateData::WhiteLabelEmail = LoadedState->WhiteLabelEmail;
		ULootLockerStateData::WhiteLabelToken = LoadedState->WhiteLabelToken;

		UE_LOG(LogLootLockerGameSDK, Log, TEXT("Loaded state from disk for player with identifier %s"), *ULootLockerStateData::PlayerIdentifier);
	}

#endif
}

void FLootLockerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	bool SuccessfullySaved = false;
	if (ULootLockerPersistedState* SavedState = Cast<ULootLockerPersistedState>(UGameplayStatics::CreateSaveGameObject(ULootLockerPersistedState::StaticClass())))
	{
		SavedState->Token = ULootLockerStateData::Token;
		SavedState->AdminToken = ULootLockerStateData::AdminToken;
		SavedState->PlayerIdentifier = ULootLockerStateData::PlayerIdentifier;
		SavedState->SteamToken = ULootLockerStateData::SteamToken;
		SavedState->WhiteLabelEmail = ULootLockerStateData::WhiteLabelEmail;
		SavedState->WhiteLabelToken = ULootLockerStateData::WhiteLabelToken;
		
		SuccessfullySaved = UGameplayStatics::SaveGameToSlot(SavedState, ULootLockerPersistedState::SaveSlot, ULootLockerPersistedState::SaveIndex);
	}
	if(!SuccessfullySaved)
	{
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to save LootLocker state to disk"));
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
