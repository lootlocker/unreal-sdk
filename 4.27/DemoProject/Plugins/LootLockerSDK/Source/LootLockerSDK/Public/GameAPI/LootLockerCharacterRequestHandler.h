// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerAssetsRequestHandler.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerConfig.h"
#include "LootLockerCharacterRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerCharacter {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default;
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
	bool is_rental;
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
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
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
struct FLootLockerCharacterLoadoutResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerCharacterLoadoutArray> loadouts;
};

USTRUCT(BlueprintType)
struct FLootLockerUpdateCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerListCharacterRequest {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString character_type_id;
};

USTRUCT(BlueprintType)
struct FLootLockerEquipAssetToCharacterWithInstanceRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
};
USTRUCT(BlueprintType)
struct FLootLockerEquipUniversalAssetToCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_variation_id;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterTypes
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default;
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
	static void EquipAssetToCharacterById(FString CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(),  const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerGetRequests& GetRequests,const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FCharacterLoadoutResponse& OnCompletedRequest = FCharacterLoadoutResponse());
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static void GetEquipableContextsByCharacterId(const FLootLockerGetRequests& GetRequests, const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
public:
	static ULootLockerHttpClient* HttpClient;
};


