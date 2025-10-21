// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerAssetsRequestHandler.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerCharacterRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerCharacter {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString type = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 ulid = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_rental = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString time_left = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active = "";
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterLoadout {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString mounted_at = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerCharacterRental rental;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterLoadoutArray {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerCharacter character;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerCharacterLoadout> loadout;
};

USTRUCT(BlueprintType)
struct FLootLockerEmptyRequest {
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterLoadoutResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerCharacterLoadoutArray> loadouts;
};

USTRUCT(BlueprintType)
struct FLootLockerUpdateCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerCreateCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString character_type_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerListCharacterResponseItem {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerEquipAssetToCharacterWithInstanceRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerEquipUniversalAssetToCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_variation_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterTypeDefaultLoadout {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterTypes : public FLootLockerHasKeyValueStorage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerCharacterTypeDefaultLoadout> default_loadout;
};

USTRUCT(BlueprintType)
struct FLootLockerListCharacterTypesResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<struct FLootLockerCharacterTypes> character_types;
};

USTRUCT(BlueprintType)
struct FLootLockerListPlayerCharactersResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerListCharacterResponseItem> items;
};

DECLARE_DELEGATE_OneParam(FCharacterLoadoutResponse, FLootLockerCharacterLoadoutResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterDefaultResponse, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponse, FLootLockerListCharacterTypesResponse);
DECLARE_DELEGATE_OneParam(FPLootLockerListPlayerCharactersResponse, FLootLockerListPlayerCharactersResponse);


UCLASS()
class LOOTLOCKERSDK_API ULootLockerCharacterRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerCharacterRequestHandler() {};

	static FString GetCharacterLoadout(const FLootLockerPlayerData& PlayerData, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static FString UpdateCharacter(const FLootLockerPlayerData& PlayerData, int CharacterId, bool IsDefault, FString Name, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static FString CreateCharacter(const FLootLockerPlayerData& PlayerData, bool IsDefault, FString CharacterName, FString CharacterId, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static FString DeleteCharacter(const FLootLockerPlayerData& PlayerData, int CharacterId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static FString ListPlayerCharacters(const FLootLockerPlayerData& PlayerData, const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest = FPLootLockerListPlayerCharactersResponse());
	static FString ListCharacterTypes(const FLootLockerPlayerData& PlayerData, const FPLootLockerListCharacterTypesResponse& OnCompletedRequest = FPLootLockerListCharacterTypesResponse());
	static FString EquipAssetToDefaultCharacter(const FLootLockerPlayerData& PlayerData, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static FString EquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static FString EquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static FString UnEquipAssetToDefaultCharacter(const FLootLockerPlayerData& PlayerData, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static FString UnEquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static FString GetCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& PlayerData, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static FString GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& PlayerData, FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static FString GetEquipableContextsToDefaultCharacter(const FLootLockerPlayerData& PlayerData, const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static FString GetEquipableContextsByCharacterId(const FLootLockerPlayerData& PlayerData, int OtherCharacterId, const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static FString GetOtherPlayersCharacterLoadouts(const FLootLockerPlayerData& PlayerData, const FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static FString GetOtherPlayersCharacterLoadoutsByUid(const FLootLockerPlayerData& PlayerData, const FString& OtherPlayerUid, const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
};


