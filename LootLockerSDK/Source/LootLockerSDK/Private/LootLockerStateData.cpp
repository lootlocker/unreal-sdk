// Copyright (c) 2021 LootLocker


#include "LootLockerStateData.h"

#include "LootLockerPlayerData.h"
#include "LootLockerSDK.h"
#include "Kismet/GameplayStatics.h"

#if ENGINE_MAJOR_VERSION < 5
const FString ULootLockerStateData::BaseSaveSlot = "LootLocker";
#endif

FLootLockerStateMetaData ULootLockerStateData::CachedMetaData = FLootLockerStateMetaData();
bool ULootLockerStateData::isMetadataLoaded = false;
TMap<FString, FLootLockerPlayerData> ULootLockerStateData::CachedPlayerData = TMap<FString, FLootLockerPlayerData>();
FLootLockerPlayerData ULootLockerStateData::EmptyPlayerData = FLootLockerPlayerData();

ULootLockerStateData::ULootLockerStateData()
{
	CachedMetaData = LoadMetaState();
}

FString ULootLockerStateData::GetNewUniqueIdentifier() 
{
	return FGenericPlatformMisc::GetDeviceId != nullptr ? FGenericPlatformMisc::GetDeviceId() : FGuid::NewGuid().ToString();
}

FLootLockerStateMetaData ULootLockerStateData::LoadMetaState()
{
	if (isMetadataLoaded)
	{
		return CachedMetaData;
	}
	if (ULootLockerStateMetaDataSaveGame* LoadedMetaState = Cast<ULootLockerStateMetaDataSaveGame>(UGameplayStatics::LoadGameFromSlot(BaseSaveSlot, SaveIndex)))
	{
		CachedMetaData.SavedPlayerStateUlids = LoadedMetaState->SavedPlayerStateUlids;
		CachedMetaData.DefaultPlayer = LoadedMetaState->DefaultPlayer;
		isMetadataLoaded = true;

		return CachedMetaData;
	}

	//No state stored, return
	UE_LOG(LogLootLockerGameSDK, Warning, TEXT("No persisted LootLocker state found, this is fine if this is the first run on a device or state has been cleared"));

	return FLootLockerStateMetaData();
}

void ULootLockerStateData::SetMetaState(FLootLockerStateMetaData& updatedMetaData)
{
	ULootLockerStateMetaDataSaveGame* newSave = NewObject<ULootLockerStateMetaDataSaveGame>();
	newSave->DefaultPlayer = updatedMetaData.DefaultPlayer;
	newSave->SavedPlayerStateUlids = updatedMetaData.SavedPlayerStateUlids;
	if (UGameplayStatics::SaveGameToSlot(newSave, BaseSaveSlot, SaveIndex))
	{
		CachedMetaData.DefaultPlayer = updatedMetaData.DefaultPlayer;
		CachedMetaData.SavedPlayerStateUlids = updatedMetaData.SavedPlayerStateUlids;
		isMetadataLoaded = true;
		UE_LOG(LogLootLockerGameSDK, VeryVerbose, TEXT("Saved LootLocker meta state to disk"));
		return;
	}
	UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to save LootLocker meta state to disk"));
}

FLootLockerPlayerData* ULootLockerStateData::LoadPlayerData(const FString& PlayerUlid /* = "" */)
{
	FString DefaultPlayerUlid = GetDefaultPlayerUlid();
	FString TargetPlayerUlid = PlayerUlid.IsEmpty() ? DefaultPlayerUlid : PlayerUlid;
	if (TargetPlayerUlid.IsEmpty())
	{
		//Nothing more to load, return
		return nullptr;
	}

	if (FLootLockerPlayerData* CachedPlayer = CachedPlayerData.Find(TargetPlayerUlid))
	{
		if (!TargetPlayerUlid.Equals(CachedPlayer->PlayerUlid))
		{
			// Cache is invalid, reset
			CachedPlayerData.Remove(TargetPlayerUlid);
		}
		else
		{
			return CachedPlayer;
		}
				
	}

	FString TargetSaveSlot = BaseSaveSlot + "_" + TargetPlayerUlid;
	if (ULootLockerPlayerDataSaveGame* LoadedState = Cast<ULootLockerPlayerDataSaveGame>(UGameplayStatics::LoadGameFromSlot(TargetSaveSlot, SaveIndex)))
	{
		if (DefaultPlayerUlid.IsEmpty())
		{
			SetDefaultPlayerUlid(TargetPlayerUlid);
		}
		CachedPlayerData.Add(LoadedState->PlayerUlid, FLootLockerPlayerData::Create(LoadedState->Token, LoadedState->RefreshToken, LoadedState->PlayerIdentifier, LoadedState->PlayerUlid, LoadedState->PlayerPublicUid, LoadedState->PlayerName, LoadedState->WhiteLabelEmail, LoadedState->WhiteLabelToken, LoadedState->CurrentPlatform, LoadedState->LastSignIn));
		UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("Loaded LootLocker state from disk for player with ulid %s"), *TargetPlayerUlid);
		return CachedPlayerData.Find(LoadedState->PlayerUlid);
	}
	UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Found no persisted LootLocker state for player with ulid %s"), *TargetPlayerUlid);
	return nullptr;
}

void ULootLockerStateData::SavePlayerData(const FLootLockerPlayerData& PlayerData)
{
	if (PlayerData.PlayerUlid.IsEmpty())
	{
		//Nothing more to do, return
		return;
	}

	FString TargetSaveSlot = BaseSaveSlot + "_" + PlayerData.PlayerUlid;
	if (!UGameplayStatics::SaveGameToSlot(ULootLockerPlayerDataSaveGame::Create(PlayerData), TargetSaveSlot, SaveIndex)) {
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to save LootLocker state to disk for player with ulid %s"), *PlayerData.PlayerUlid);
		return;
	}
	UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("Saved LootLocker player state to disk for player with ulid %s"), *PlayerData.PlayerUlid);

	FLootLockerStateMetaData metaState = LoadMetaState();
	if (metaState.DefaultPlayer.IsEmpty() || CachedPlayerData.IsEmpty())
	{
		metaState.DefaultPlayer = PlayerData.PlayerUlid;
		SetDefaultPlayerUlid(PlayerData.PlayerUlid);
	}
	if (!metaState.SavedPlayerStateUlids.Contains(PlayerData.PlayerUlid))
	{
		metaState.SavedPlayerStateUlids.Add(PlayerData.PlayerUlid);
		SetMetaState(metaState);
	}
	CachedPlayerData.Add(PlayerData.PlayerUlid, PlayerData);
}

FString ULootLockerStateData::GetDefaultPlayerUlid()
{
	FLootLockerStateMetaData metaState = LoadMetaState();
	if (!metaState.DefaultPlayer.IsEmpty())
	{
		return metaState.DefaultPlayer;
	}
	return "";
}

bool ULootLockerStateData::SetDefaultPlayerUlid(const FString& PlayerUlid)
{
	if (!SaveStateExistsForPlayer(PlayerUlid))
	{
		return false;
	}

	FLootLockerStateMetaData metaState = LoadMetaState();
	if (metaState.DefaultPlayer.Equals(PlayerUlid))
	{
		return false;
	}

	metaState.DefaultPlayer = PlayerUlid;
	metaState.SavedPlayerStateUlids.AddUnique(PlayerUlid);
	SetMetaState(metaState);

	return true;
}

bool ULootLockerStateData::SaveStateExistsForPlayer(const FString& PlayerUlid /* = "" */)
{
	if (PlayerUlid.IsEmpty())
	{
		return false;
	}

	if (CachedPlayerData.Contains(PlayerUlid))
	{
		return true;
	}

	if (!isMetadataLoaded)
	{
		LoadMetaState();
		if (!isMetadataLoaded)
		{
			return false;
		}
	}
	return CachedMetaData.SavedPlayerStateUlids.Contains(PlayerUlid);
}

const FLootLockerPlayerData& ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(const FString& PlayerUlid /* = "" */)
{
	const FLootLockerPlayerData* playerData = LoadPlayerData(PlayerUlid);
	if (playerData != nullptr)
	{
		return *playerData;
	}
	return EmptyPlayerData;
}

bool ULootLockerStateData::ClearSavedStateForPlayer(const FString& PlayerUlid)
{
	if (PlayerUlid.IsEmpty())
	{
		//Nothing more to load, return
		return false;
	}

	FString TargetSaveSlot = BaseSaveSlot + "_" + PlayerUlid;
	UGameplayStatics::DeleteGameInSlot(TargetSaveSlot, SaveIndex);

	FLootLockerStateMetaData metaState = LoadMetaState();
	metaState.SavedPlayerStateUlids.Remove(PlayerUlid);
	if (PlayerUlid.Equals(GetDefaultPlayerUlid()))
	{
		metaState.DefaultPlayer = "";
	}

	SetMetaState(metaState);
	CachedPlayerData.Remove(PlayerUlid);
	return true;
}

void ULootLockerStateData::ClearAllSavedStates()
{
	FLootLockerStateMetaData metaState = LoadMetaState();
	TArray<FString> localLoadedUlidListCopy = metaState.SavedPlayerStateUlids;
	for (const FString& playerUlid : localLoadedUlidListCopy)
	{
		ClearSavedStateForPlayer(playerUlid);
	}
	CachedPlayerData.Empty();
}

TArray<FString> ULootLockerStateData::GetActivePlayerUlids()
{
	TArray<FString> OutUlids;
	CachedPlayerData.GetKeys(OutUlids);
	return OutUlids;
}

TArray<FString> ULootLockerStateData::GetCachedPlayerUlids()
{
	return CachedMetaData.SavedPlayerStateUlids;
}

void ULootLockerStateData::SetPlayerUlidToInactive(const FString& PlayerUlid)
{
	if (PlayerUlid.IsEmpty())
	{
		//Nothing more to load, return
		return;
	}

	CachedPlayerData.Remove(PlayerUlid);
}
