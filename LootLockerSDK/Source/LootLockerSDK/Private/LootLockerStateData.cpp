// Copyright (c) 2021 LootLocker


#include "LootLockerStateData.h"

#include "LootLockerPlayerData.h"
#include "LootLockerSDK.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "Kismet/GameplayStatics.h"
#include "LootLockerSDK/Public/LootLockerPersistedState.h"

#if ENGINE_MAJOR_VERSION < 5
const FString ULootLockerStateData::BaseSaveSlot = "LootLocker";
const FString ULootLockerStateData::MetaDataSaveSlot = BaseSaveSlot+"_META";
const FString ULootLockerStateData::PlayerDataSaveSlot = BaseSaveSlot + "_pd_";;
#endif

FLootLockerStateMetaData ULootLockerStateData::ActiveMetaData = FLootLockerStateMetaData();
bool ULootLockerStateData::isMetadataLoaded = false;
TMap<FString, FLootLockerPlayerData> ULootLockerStateData::ActivePlayerData = TMap<FString, FLootLockerPlayerData>();
FLootLockerPlayerData ULootLockerStateData::EmptyPlayerData = FLootLockerPlayerData();

ULootLockerStateData::ULootLockerStateData()
{
	ActiveMetaData = LoadMetaState();
}

FString ULootLockerStateData::GenerateNewGuestIdentifier() 
{
	if (!isMetadataLoaded)
	{
		LoadMetaState();
	}
	if (ActiveMetaData.SavedPlayerStateUlids.IsEmpty() && FGenericPlatformMisc::GetDeviceId != nullptr)
	{
		// For backwards compatibility, base the first guest user on the device id
		return FGenericPlatformMisc::GetDeviceId();
	}
	return ""; // Let backend generate an identifier
}

bool ULootLockerStateData::TransferPlayerCacheToMultiUserSystem()
{
	if (!UGameplayStatics::DoesSaveGameExist(BaseSaveSlot, SaveIndex))
	{
		return false;
	}
	auto GetPlatformRepresentationFromPlatformString = [](const FString& PlatformString) -> const FLootLockerPlatformRepresentation&
		{
			TArray<FLootLockerPlatformRepresentation> platformRepresentations =
				ULootLockerPlatforms::GetAllPlatformRepresentations();
			for (FLootLockerPlatformRepresentation& PlatformRepresentation : platformRepresentations)
			{
				if (PlatformRepresentation.PlatformString.Equals(PlatformString, ESearchCase::IgnoreCase))
				{
					return ULootLockerPlatforms::GetPlatformRepresentationForPlatform(PlatformRepresentation.Platform);
				}
			}
			return ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::None);
		};

	if (ULootLockerPersistedState* PreMultiUserLoadedState = Cast<ULootLockerPersistedState>(UGameplayStatics::LoadGameFromSlot(BaseSaveSlot, SaveIndex)))
	{
		FLootLockerPlayerData DataToTransfer{
			PreMultiUserLoadedState->Token,
			PreMultiUserLoadedState->RefreshToken,
			PreMultiUserLoadedState->PlayerIdentifier,
			"pre-multi-user-fake-ulid",
			"",
			"",
			PreMultiUserLoadedState->WhiteLabelEmail,
			PreMultiUserLoadedState->WhiteLabelToken,
			GetPlatformRepresentationFromPlatformString(PreMultiUserLoadedState->LastActivePlatform),
			""
		};
		SavePlayerData(DataToTransfer);
		ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(DataToTransfer, FLootLockerGetCurrentPlayerInfoResponseBP(), FLootLockerGetCurrentPlayerInfoResponseDelegate::CreateLambda([TempUlidCopy = DataToTransfer.PlayerUlid](const FLootLockerGetCurrentPlayerInfoResponse& Response)
			{
				FLootLockerPlayerData* transferredPlayerData = LoadPlayerData(TempUlidCopy);
				if (transferredPlayerData != nullptr && Response.success)
				{
					transferredPlayerData->PlayerUlid = Response.Info.Id;
					transferredPlayerData->PlayerPublicUid = Response.Info.Public_uid;
					transferredPlayerData->PlayerName = Response.Info.Name;
					SavePlayerData(*transferredPlayerData);
					SetPlayerUlidToInactive(transferredPlayerData->PlayerUlid);
				}
				ClearSavedStateForPlayer(TempUlidCopy);
				}));

		UGameplayStatics::DeleteGameInSlot(BaseSaveSlot, 0);
		return true;
	}
	return false;
}

FLootLockerStateMetaData ULootLockerStateData::LoadMetaState()
{
	if (isMetadataLoaded)
	{
		return ActiveMetaData;
	}
	if (ULootLockerStateMetaDataSaveGame* LoadedMetaState = Cast<ULootLockerStateMetaDataSaveGame>(UGameplayStatics::LoadGameFromSlot(MetaDataSaveSlot, SaveIndex)))
	{
		ActiveMetaData.SavedPlayerStateUlids = LoadedMetaState->SavedPlayerStateUlids;
		ActiveMetaData.DefaultPlayer = LoadedMetaState->DefaultPlayer;
		if (ActiveMetaData.DefaultPlayer.IsEmpty() && ActiveMetaData.SavedPlayerStateUlids.Num() == 1)
		{
			ActiveMetaData.DefaultPlayer = ActiveMetaData.SavedPlayerStateUlids[0];
		}
		ActiveMetaData.MultiuserInitialLoadCompleted = LoadedMetaState->MultiuserInitialLoadCompleted;
		isMetadataLoaded = true;

		if (!ActiveMetaData.MultiuserInitialLoadCompleted && UGameplayStatics::DoesSaveGameExist(BaseSaveSlot, SaveIndex))
		{
			TransferPlayerCacheToMultiUserSystem();
			ActiveMetaData.MultiuserInitialLoadCompleted = true;
		}

		return ActiveMetaData;
	}

	FLootLockerStateMetaData NewMetaState = FLootLockerStateMetaData{ TArray<FString>(), "", true };
	SetMetaState(NewMetaState);
	bool preMultiUserStateFound = TransferPlayerCacheToMultiUserSystem();
	if (!preMultiUserStateFound)
	{
		//No state stored, return
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("No persisted LootLocker state found, this is fine if this is the first run on a device or state has been cleared"));
	}
	return ActiveMetaData;
}

void ULootLockerStateData::SetMetaState(FLootLockerStateMetaData& updatedMetaData)
{
	ULootLockerStateMetaDataSaveGame* newSave = NewObject<ULootLockerStateMetaDataSaveGame>();
	newSave->DefaultPlayer = updatedMetaData.DefaultPlayer;
	newSave->SavedPlayerStateUlids = updatedMetaData.SavedPlayerStateUlids;
	newSave->MultiuserInitialLoadCompleted = updatedMetaData.MultiuserInitialLoadCompleted;
	if (UGameplayStatics::SaveGameToSlot(newSave, MetaDataSaveSlot, SaveIndex))
	{
		ActiveMetaData.DefaultPlayer = updatedMetaData.DefaultPlayer;
		ActiveMetaData.SavedPlayerStateUlids = updatedMetaData.SavedPlayerStateUlids;
		ActiveMetaData.MultiuserInitialLoadCompleted = updatedMetaData.MultiuserInitialLoadCompleted;
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

	if (FLootLockerPlayerData* ActivePlayer = ActivePlayerData.Find(TargetPlayerUlid))
	{
		if (!TargetPlayerUlid.Equals(ActivePlayer->PlayerUlid))
		{
			// Active player is invalid, reset
			ActivePlayerData.Remove(TargetPlayerUlid);
		}
		else
		{
			return ActivePlayer;
		}
				
	}

	FString TargetSaveSlot = PlayerDataSaveSlot + "_" + TargetPlayerUlid;
	if (ULootLockerPlayerDataSaveGame* LoadedState = Cast<ULootLockerPlayerDataSaveGame>(UGameplayStatics::LoadGameFromSlot(TargetSaveSlot, SaveIndex)))
	{
		if (DefaultPlayerUlid.IsEmpty())
		{
			SetDefaultPlayerUlid(TargetPlayerUlid);
		}
		ActivePlayerData.Add(LoadedState->PlayerUlid, FLootLockerPlayerData::Create(LoadedState->Token, LoadedState->RefreshToken, LoadedState->PlayerIdentifier, LoadedState->PlayerUlid, LoadedState->PlayerPublicUid, LoadedState->PlayerName, LoadedState->WhiteLabelEmail, LoadedState->WhiteLabelToken, LoadedState->CurrentPlatform, LoadedState->LastSignIn, LoadedState->PlayerCreatedAt));
		UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("Loaded LootLocker state from disk for player with ulid %s"), *TargetPlayerUlid);
		return ActivePlayerData.Find(LoadedState->PlayerUlid);
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

	FString TargetSaveSlot = PlayerDataSaveSlot + "_" + PlayerData.PlayerUlid;
	if (!UGameplayStatics::SaveGameToSlot(ULootLockerPlayerDataSaveGame::Create(PlayerData), TargetSaveSlot, SaveIndex)) {
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("Failed to save LootLocker state to disk for player with ulid %s"), *PlayerData.PlayerUlid);
		return;
	}
	UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("Saved LootLocker player state to disk for player with ulid %s"), *PlayerData.PlayerUlid);

	FLootLockerStateMetaData metaState = LoadMetaState();
	if (metaState.DefaultPlayer.IsEmpty() || ActivePlayerData.Num() == 0)
	{
		metaState.DefaultPlayer = PlayerData.PlayerUlid;
		SetDefaultPlayerUlid(PlayerData.PlayerUlid);
	}
	if (!metaState.SavedPlayerStateUlids.Contains(PlayerData.PlayerUlid))
	{
		metaState.SavedPlayerStateUlids.Add(PlayerData.PlayerUlid);
		SetMetaState(metaState);
	}
	ActivePlayerData.Add(PlayerData.PlayerUlid, PlayerData);
}

FString ULootLockerStateData::GetDefaultPlayerUlid()
{
	return LoadMetaState().DefaultPlayer;
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

	if (ActivePlayerData.Contains(PlayerUlid))
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
	return ActiveMetaData.SavedPlayerStateUlids.Contains(PlayerUlid);
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

	FString TargetSaveSlot = PlayerDataSaveSlot + "_" + PlayerUlid;
	UGameplayStatics::DeleteGameInSlot(TargetSaveSlot, SaveIndex);

	FLootLockerStateMetaData metaState = LoadMetaState();
	metaState.SavedPlayerStateUlids.Remove(PlayerUlid);
	if (PlayerUlid.Equals(GetDefaultPlayerUlid()))
	{
		metaState.DefaultPlayer = "";
	}

	SetMetaState(metaState);
	ActivePlayerData.Remove(PlayerUlid);
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
	ActivePlayerData.Empty();
}

TArray<FString> ULootLockerStateData::GetActivePlayerUlids()
{
	TArray<FString> OutUlids;
	ActivePlayerData.GetKeys(OutUlids);
	return OutUlids;
}

TArray<FString> ULootLockerStateData::GetCachedPlayerUlids()
{
	return ActiveMetaData.SavedPlayerStateUlids;
}

void ULootLockerStateData::SetPlayerUlidToInactive(const FString& PlayerUlid)
{
	if (PlayerUlid.IsEmpty())
	{
		//Nothing more to load, return
		return;
	}

	ActivePlayerData.Remove(PlayerUlid);
}
