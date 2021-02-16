// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssetsRequestHandler.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "LootLockerConfig.h"
#include "CharacterRequestHandler.generated.h"


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
struct FCharacterAsset 
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
};
USTRUCT(BlueprintType)
struct FCharacterRental {
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
struct FCharacterLoadout {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString mounted_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FCharacterAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FCharacterRental rental;
};
USTRUCT(BlueprintType)
struct FCharacterLoadoutArray {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerCharacter character;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FCharacterLoadout> loadout;
};
USTRUCT(BlueprintType)
struct FCharacterLoadoutResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FCharacterLoadoutArray> loadouts;
};

USTRUCT(BlueprintType)
struct FUpdateCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FListCharacterRequest {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		FString character_type_id;
};

USTRUCT(BlueprintType)
struct FEquipAssetToCharacterWithInstanceRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
};
USTRUCT(BlueprintType)
struct FEquipUniversalAssetToCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 asset_variation_id;
};

USTRUCT(BlueprintType)
struct FLootLockerListCharacterTypesResponse : public FLootLockerResponse {
	GENERATED_BODY()
	TArray<FLootLockerCharacterTypes> character_types;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterTypes
{
	GENERATED_BODY()
	int32 id;
	bool is_default;
	FString name;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterLoadoutResponseBP, FCharacterLoadoutResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponseBP, FLootLockerListCharacterTypesResponse, Var);

DECLARE_DELEGATE_OneParam(FLootLockerCharacterLoadoutResponse, FCharacterLoadoutResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterDefaultResponse, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponse, FLootLockerListCharacterTypesResponse);


UCLASS()
class LOOTLOCKERSDK_API UCharacterRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	UCharacterRequestHandler();
	static void GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompleteRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void UpdateCharacter(bool IsDefault,const FString& Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP = FPLootLockerListCharacterTypesResponseBP(), const FPLootLockerListCharacterTypesResponse& OnCompletedRequest = FPLootLockerListCharacterTypesResponse());
	static void EquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(),  const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerGetRequests& GetRequests,const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static void GetEquipableContextsByCharacterId(const FLootLockerGetRequests& GetRequests, const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
public:
	static UHttpClient* HttpClient;
};


