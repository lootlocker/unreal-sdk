// Copyright (c) 2021 LootLocker


#include "LootLockerStateData.h"

#include "LootLockerPersistedState.h"
#include "LootLockerSDK.h"
#include "Kismet/GameplayStatics.h"

FString ULootLockerStateData::Token = "";
FString ULootLockerStateData::SteamToken = "";
FString ULootLockerStateData::RefreshToken = "";
FString ULootLockerStateData::PlayerIdentifier = FGenericPlatformMisc::GetDeviceId != nullptr ? FGenericPlatformMisc::GetDeviceId() : FGuid::NewGuid().ToString();
FString ULootLockerStateData::WhiteLabelEmail = "";
FString ULootLockerStateData::WhiteLabelToken = "";
FString ULootLockerStateData::LastActivePlatform = "";
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
		RefreshToken = LoadedState->RefreshToken;
		WhiteLabelEmail = LoadedState->WhiteLabelEmail;
		WhiteLabelToken = LoadedState->WhiteLabelToken;
		LastActivePlatform = LoadedState->LastActivePlatform;

		UE_LOG(LogLootLockerGameSDK, Log, TEXT("Loaded LootLocker state from disk"));
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
		SavedState->RefreshToken = RefreshToken;
		SavedState->WhiteLabelEmail = WhiteLabelEmail;
		SavedState->WhiteLabelToken = WhiteLabelToken;
		SavedState->LastActivePlatform = LastActivePlatform;

		if (UGameplayStatics::SaveGameToSlot(SavedState, SaveSlot, SaveIndex)) {
			UE_LOG(LogLootLockerGameSDK, Log, TEXT("Saved LootLocker state to disk"));
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

FString ULootLockerStateData::GetRefreshToken()
{
	LoadStateFromDiskIfNeeded();
	return RefreshToken;
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

FString ULootLockerStateData::GetLastActivePlatform()
{
	LoadStateFromDiskIfNeeded();
	return LastActivePlatform;
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
void ULootLockerStateData::SetRefreshToken(FString InRefreshToken) {
	LoadStateFromDiskIfNeeded();
	if (InRefreshToken.Equals(RefreshToken)) {
		return;
	}
	RefreshToken = InRefreshToken;
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

void ULootLockerStateData::SetLastActivePlatform(FString InLastActivePlatform) {
	LoadStateFromDiskIfNeeded();
	if (InLastActivePlatform.Equals(LastActivePlatform)) {
		return;
	}
	LastActivePlatform = InLastActivePlatform;
	SaveStateToDisk();
}

void ULootLockerStateData::ClearState()
{
	LoadStateFromDiskIfNeeded();
	Token = "";
	SteamToken = "";
	RefreshToken = "";
	PlayerIdentifier = "";
	WhiteLabelEmail = "";
	WhiteLabelToken = "";
	SaveStateToDisk();
	StateLoaded = false;
}
