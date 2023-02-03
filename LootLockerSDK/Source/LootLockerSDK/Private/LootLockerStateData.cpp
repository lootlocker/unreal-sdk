// Copyright (c) 2021 LootLocker


#include "LootLockerStateData.h"

#include "LootLockerConfig.h"
#include "LootLockerPersistedState.h"
#include "Kismet/GameplayStatics.h"
#include "Launch/Resources/Version.h"

FString ULootLockerStateData::Token = "";
FString ULootLockerStateData::SteamToken = "";
FString ULootLockerStateData::PlayerIdentifier = FGenericPlatformMisc::GetDeviceId();
FString ULootLockerStateData::WhiteLabelEmail = "";
FString ULootLockerStateData::WhiteLabelToken = "";
bool ULootLockerStateData::StateLoaded = false;

#if ENGINE_MAJOR_VERSION < 5
const FString ULootLockerStateData::SaveSlot = "LootLocker";
#endif

void ULootLockerStateData::LoadStateFromDiskIfNeeded() 
{
	if(StateLoaded)
	{
		return;
	}

	if (ULootLockerPersistedState* LoadedState = Cast<ULootLockerPersistedState>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveIndex)))
	{
		Token = LoadedState->Token;
		PlayerIdentifier = LoadedState->PlayerIdentifier.IsEmpty() ? FPlatformMisc::GetDeviceId() : LoadedState->PlayerIdentifier;
		SteamToken = LoadedState->SteamToken;
		WhiteLabelEmail = LoadedState->WhiteLabelEmail;
		WhiteLabelToken = LoadedState->WhiteLabelToken;

		UE_LOG(LogLootLockerGameSDK, Log, TEXT("Loaded LootLocker state from disk for player with identifier %s"), *PlayerIdentifier);
		StateLoaded = true;
		return;
	}
	UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to load LootLocker state from disk"));
}

void ULootLockerStateData::SaveStateToDisk() 
{
	if (ULootLockerPersistedState* SavedState = Cast<ULootLockerPersistedState>(UGameplayStatics::CreateSaveGameObject(ULootLockerPersistedState::StaticClass())))
	{
		SavedState->Token = Token;
		SavedState->PlayerIdentifier = PlayerIdentifier;
		SavedState->SteamToken = SteamToken;
		SavedState->WhiteLabelEmail = WhiteLabelEmail;
		SavedState->WhiteLabelToken = WhiteLabelToken;

		if (UGameplayStatics::SaveGameToSlot(SavedState, SaveSlot, SaveIndex)) {
			UE_LOG(LogLootLockerGameSDK, Log, TEXT("Saved LootLocker state to disk for player with identifier %s"), *PlayerIdentifier);
			return;
		}
	}
    UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to save LootLocker state to disk"));
}

FString ULootLockerStateData::GetToken()
{
	LoadStateFromDiskIfNeeded();
	return Token;
}

FString ULootLockerStateData::GetSteamToken() 
{
	LoadStateFromDiskIfNeeded();
	return SteamToken;
}

FString ULootLockerStateData::GetPlayerIdentifier() 
{
	LoadStateFromDiskIfNeeded();
	return PlayerIdentifier;
}

FString ULootLockerStateData::GetWhiteLabelEmail() 
{
	LoadStateFromDiskIfNeeded();
	return WhiteLabelEmail;
}

FString ULootLockerStateData::GetWhiteLabelToken() 
{
	LoadStateFromDiskIfNeeded();
	return WhiteLabelToken;
}

void ULootLockerStateData::SetToken(FString InToken) {
	LoadStateFromDiskIfNeeded();
	if(InToken.Equals(Token)) {
		return;
	}
	Token = InToken;
	SaveStateToDisk();
}
void ULootLockerStateData::SetSteamToken(FString InSteamToken) {
	LoadStateFromDiskIfNeeded();
	if (InSteamToken.Equals(SteamToken)) {
		return;
	}
	SteamToken = InSteamToken;
	SaveStateToDisk();
}
void ULootLockerStateData::SetPlayerIdentifier(FString InPlayerIdentifier) {
	LoadStateFromDiskIfNeeded();
	if (InPlayerIdentifier.Equals(PlayerIdentifier)) {
		return;
	}
	PlayerIdentifier = InPlayerIdentifier;
	SaveStateToDisk();
}
void ULootLockerStateData::SetWhiteLabelEmail(FString InWhiteLabelEmail) {
	LoadStateFromDiskIfNeeded();
	if (InWhiteLabelEmail.Equals(WhiteLabelEmail)) {
		return;
	}
	WhiteLabelEmail = InWhiteLabelEmail;
	SaveStateToDisk();
}
void ULootLockerStateData::SetWhiteLabelToken(FString InWhiteLabelToken) {
	LoadStateFromDiskIfNeeded();
	if (InWhiteLabelToken.Equals(WhiteLabelToken)) {
		return;
	}
	WhiteLabelToken = InWhiteLabelToken;
	SaveStateToDisk();
}

void ULootLockerStateData::ClearState()
{
	LoadStateFromDiskIfNeeded();
	Token = "";
	SteamToken = "";
	PlayerIdentifier = "";
	WhiteLabelEmail = "";
	WhiteLabelToken = "";
	SaveStateToDisk();
	StateLoaded = false;
}
