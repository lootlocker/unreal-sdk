// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
#include "GameFramework/SaveGame.h"
#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerStateData.generated.h"

UCLASS()
class ULootLockerStateMetaDataSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	TArray<FString> SavedPlayerStateUlids;
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString DefaultPlayer;
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	bool MultiuserInitialLoadCompleted; //TODO: Deprecated (or rather temporary) - Remove after 20250901
};

USTRUCT(BlueprintType)
struct FLootLockerStateMetaData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	TArray<FString> SavedPlayerStateUlids;
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString DefaultPlayer;
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	bool MultiuserInitialLoadCompleted; //TODO: Deprecated (or rather temporary) - Remove after 20250901
};

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPlayerDataSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString Token = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString RefreshToken = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString PlayerIdentifier = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString PlayerUlid = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString PlayerPublicUid = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString PlayerName = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString WhiteLabelEmail = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString WhiteLabelToken = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FLootLockerPlatformRepresentation CurrentPlatform;
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString LastSignIn = "";

	static ULootLockerPlayerDataSaveGame* Create(const FLootLockerPlayerData& PlayerData)
	{
		return Create(PlayerData.Token, PlayerData.RefreshToken, PlayerData.PlayerIdentifier, PlayerData.PlayerUlid, PlayerData.PlayerPublicUid, PlayerData.PlayerName, PlayerData.WhiteLabelEmail, PlayerData.WhiteLabelToken, PlayerData.CurrentPlatform, PlayerData.LastSignIn);
	}

	static ULootLockerPlayerDataSaveGame* Create(const FString& token = "", const FString& refreshToken = "", const FString& playerIdentifier = "", const FString& playerUlid = "", const FString& playerPublicUid = "", const FString& playerName = "", const FString& whiteLabelEmail = "", const FString& whiteLabelToken = "", const FLootLockerPlatformRepresentation& currentPlatform = FLootLockerPlatformRepresentation(), const FString& lastSignIn = "")
	{
		ULootLockerPlayerDataSaveGame* newObj = NewObject<ULootLockerPlayerDataSaveGame>();
		newObj->Token = token;
		newObj->RefreshToken = refreshToken;
		newObj->PlayerIdentifier = playerIdentifier;
		newObj->PlayerUlid = playerUlid;
		newObj->PlayerPublicUid = playerPublicUid;
		newObj->PlayerName = playerName;
		newObj->WhiteLabelEmail = whiteLabelEmail;
		newObj->WhiteLabelToken = whiteLabelToken;
		newObj->CurrentPlatform = currentPlatform;
		newObj->LastSignIn = lastSignIn;
		return newObj;
	}
};

UCLASS()
class LOOTLOCKERSDK_API ULootLockerStateData : public UObject
{
	GENERATED_BODY()
private:
	static FLootLockerPlayerData EmptyPlayerData;
	static FLootLockerStateMetaData ActiveMetaData;
	static bool isMetadataLoaded;
	static TMap<FString, FLootLockerPlayerData> ActivePlayerData;

#if ENGINE_MAJOR_VERSION < 5
	static const FString BaseSaveSlot;
	inline static const FString MetaDataSaveSlot;
	inline static const FString PlayerDataSaveSlot;
    static constexpr int SaveIndex = 0;
#else
    inline static const FString BaseSaveSlot = "LootLocker";
	inline static const FString MetaDataSaveSlot = BaseSaveSlot+"_md";
	inline static const FString PlayerDataSaveSlot = BaseSaveSlot+"_pd";
    inline static constexpr int SaveIndex = 0;
#endif

	//TODO: Deprecated (or rather temporary) - Remove after 20250901
	static bool TransferPlayerCacheToMultiUserSystem();
	static FLootLockerStateMetaData LoadMetaState();
	static FLootLockerPlayerData* LoadPlayerData(const FString& PlayerUlid);
	static void SetMetaState(FLootLockerStateMetaData& updatedMetaData);
public:
	ULootLockerStateData();

	static FString GetNewUniqueIdentifier();
	static bool SaveStateExistsForPlayer(const FString& PlayerUlid = "");
	static const FLootLockerPlayerData& GetSavedStateOrDefaultOrEmptyForPlayer(const FString& PlayerUlid = "");
	static FString GetDefaultPlayerUlid();
	static bool SetDefaultPlayerUlid(const FString& PlayerUlid);
	static void SavePlayerData(const FLootLockerPlayerData& PlayerData);
	static bool ClearSavedStateForPlayer(const FString& PlayerUlid);
	static void ClearAllSavedStates();
	static TArray<FString> GetActivePlayerUlids();
	static TArray<FString> GetCachedPlayerUlids();
	static void SetPlayerUlidToInactive(const FString& PlayerUlid);
};
