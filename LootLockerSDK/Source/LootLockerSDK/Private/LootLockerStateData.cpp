// Copyright (c) 2021 LootLocker


#include "LootLockerStateData.h"

#include "LootLockerPersistedState.h"
#include "LootLockerConfig.h"
#include "Kismet/GameplayStatics.h"

FString ULootLockerStateData::Token = "";
FString ULootLockerStateData::DomainKey = "";
FString ULootLockerStateData::SteamToken = "";
FString ULootLockerStateData::PlayerIdentifier = FGenericPlatformMisc::GetDeviceId();
FString ULootLockerStateData::AdminToken = "";
FString ULootLockerStateData::WhiteLabelEmail = "";
FString ULootLockerStateData::WhiteLabelToken = "";
bool ULootLockerStateData::StateLoaded = false;

void ULootLockerStateData::LoadStateFromDiskIfNeeded() 
{
	if(StateLoaded)
	{
		return;
	}

	if (ULootLockerPersistedState* LoadedState = Cast<ULootLockerPersistedState>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveIndex)))
	{
		Token = LoadedState->Token;
		AdminToken = LoadedState->AdminToken;
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
		SavedState->AdminToken = AdminToken;
		SavedState->PlayerIdentifier = PlayerIdentifier;
		SavedState->SteamToken = SteamToken;
		SavedState->WhiteLabelEmail = WhiteLabelEmail;
		SavedState->WhiteLabelToken = WhiteLabelToken;

		if (UGameplayStatics::SaveGameToSlot(SavedState, SaveSlot, SaveIndex)) {
			UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Saved LootLocker state to disk for player with identifier %s"), *PlayerIdentifier);
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

FString ULootLockerStateData::GetDomainKey() 
{
	LoadStateFromDiskIfNeeded();
	return DomainKey;
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

FString ULootLockerStateData::GetAdminToken() 
{
	LoadStateFromDiskIfNeeded();
	return AdminToken;
}

void ULootLockerStateData::SetToken(FString InToken) {
	LoadStateFromDiskIfNeeded();
	if(InToken.Equals(Token)) {
		return;
	}
	Token = InToken;
	SaveStateToDisk();
}
void ULootLockerStateData::SetDomainKey(FString InDomainKey) {
	LoadStateFromDiskIfNeeded();
	if (InDomainKey.Equals(DomainKey)) {
		return;
	}
	DomainKey = InDomainKey;
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
void ULootLockerStateData::SetAdminToken(FString InAdminToken) {
	LoadStateFromDiskIfNeeded();
	if (InAdminToken.Equals(AdminToken)) {
		return;
	}
	AdminToken = InAdminToken;
	SaveStateToDisk();
}

void ULootLockerStateData::ClearState()
{
	LoadStateFromDiskIfNeeded();
	Token = "";
	DomainKey = "";
	SteamToken = "";
	PlayerIdentifier = "";
	WhiteLabelEmail = "";
	WhiteLabelToken = "";
	AdminToken = "";
	SaveStateToDisk();
	StateLoaded = false;
}
