// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerAssetsRequestHandler.h"
#include "LootLockerHttpClient.h"
#include "LootLockerResponse.h"
#include "LootLockerCharacterRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerCharacter {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
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
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterLoadout {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString mounted_at;
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
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerCreateCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString character_type_id;
};

USTRUCT(BlueprintType)
struct FLootLockerListCharacterResponseItem {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString id;
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
	FString name;
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterLoadoutResponseBP, FLootLockerCharacterLoadoutResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponseBP, FLootLockerListCharacterTypesResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPLootLockerListPlayerCharactersResponseBP, FLootLockerListPlayerCharactersResponse, Var);

DECLARE_DELEGATE_OneParam(FCharacterLoadoutResponse, FLootLockerCharacterLoadoutResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterDefaultResponse, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponse, FLootLockerListCharacterTypesResponse);
DECLARE_DELEGATE_OneParam(FPLootLockerListPlayerCharactersResponse, FLootLockerListPlayerCharactersResponse);


UCLASS()
class LOOTLOCKERSDK_API ULootLockerCharacterRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerCharacterRequestHandler();
	static void GetCharacterLoadout(const FLootLockerPlayerData& PlayerData, const FPCharacterLoadoutResponseBP& OnCompleteRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void UpdateCharacter(const FLootLockerPlayerData& PlayerData, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void CreateCharacter(const FLootLockerPlayerData& PlayerData, bool IsDefault, FString CharacterName, FString CharacterId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void ListPlayerCharacters(const FLootLockerPlayerData& PlayerData, const FPLootLockerListPlayerCharactersResponseBP& OnCompleteRequestBP = FPLootLockerListPlayerCharactersResponseBP(), const FPLootLockerListPlayerCharactersResponse & = FPLootLockerListPlayerCharactersResponse());
	static void ListCharacterTypes(const FLootLockerPlayerData& PlayerData, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP = FPLootLockerListCharacterTypesResponseBP(), const FPLootLockerListCharacterTypesResponse& OnCompletedRequest = FPLootLockerListCharacterTypesResponse());
	static void EquipAssetToDefaultCharacter(const FLootLockerPlayerData& PlayerData, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToDefaultCharacter(const FLootLockerPlayerData& PlayerData, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void GetCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& PlayerData, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& PlayerData, FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void GetEquipableContextsToDefaultCharacter(const FLootLockerPlayerData& PlayerData, const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static void GetEquipableContextsByCharacterId(const FLootLockerPlayerData& PlayerData, int OtherCharacterId, const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate&
		                                              OnCompletedRequest = FContextDelegate());
public:
	static ULootLockerHttpClient* HttpClient;
};


