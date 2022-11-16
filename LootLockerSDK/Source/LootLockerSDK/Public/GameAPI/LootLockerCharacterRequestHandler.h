// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerAssetsRequestHandler.h"
#include "JsonObjectConverter.h"
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
	bool is_default = false;
};
USTRUCT(BlueprintType)
struct FLootLockerCharacterAsset
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
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
	FLootLockerCharacterAsset asset;
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
struct FLootLockerListCharacterRequest {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString character_type_id;
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
struct FLootLockerCharacterTypes : public FLootLockerHasKeyValueStorage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerListCharacterTypesResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<struct FLootLockerCharacterTypes> character_types;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterLoadoutResponseBP, FLootLockerCharacterLoadoutResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponseBP, FLootLockerListCharacterTypesResponse, Var);

DECLARE_DELEGATE_OneParam(FCharacterLoadoutResponse, FLootLockerCharacterLoadoutResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterDefaultResponse, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponse, FLootLockerListCharacterTypesResponse);


UCLASS()
class LOOTLOCKERSDK_API ULootLockerCharacterRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerCharacterRequestHandler();
	static void GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompleteRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void UpdateCharacter(int CharacterId,bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void CreateCharacter(bool IsDefault,  FString CharacterName, FString CharacterId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP = FPLootLockerListCharacterTypesResponseBP(), const FPLootLockerListCharacterTypesResponse& OnCompletedRequest = FPLootLockerListCharacterTypesResponse());
	static void EquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(int CharacterId,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP =
		                                        FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest =
		                                        FLootLockerCharacterDefaultResponse());
	static void GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static void GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate&
		                                              OnCompletedRequest = FContextDelegate());
public:
	static ULootLockerHttpClient* HttpClient;
};


