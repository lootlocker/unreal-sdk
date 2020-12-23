// Copyright (c) 2020 LootLocker

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool is_default;
};
USTRUCT(BlueprintType)
struct FCharacterAsset 
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLootLockerAsset asset;
};
USTRUCT(BlueprintType)
struct FCharacterRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool is_rental;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString is_active;
};
USTRUCT(BlueprintType)
struct FCharacterLoadout {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString mounted_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCharacterAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCharacterRental rental;
};
USTRUCT(BlueprintType)
struct FCharacterLoadoutArray {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLootLockerCharacter character;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCharacterLoadout> loadout;
};
USTRUCT(BlueprintType)
struct FCharacterLoadoutResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCharacterLoadoutArray> loadouts;
};

USTRUCT(BlueprintType)
struct FUpdateCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString name;
};
USTRUCT(BlueprintType)
struct FEquipAssetToCharacterWithInstanceRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 instance_id;
};
USTRUCT(BlueprintType)
struct FEquipUniversalAssetToCharacterRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 asset_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 asset_variation_id;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPCharacterLoadoutResponseBP, FCharacterLoadoutResponse, Var);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPCharacterDefaultResponseBP, FLootLockerResponse, Var);

DECLARE_DELEGATE_OneParam(FLootLockerCharacterLoadoutResponse, FCharacterLoadoutResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterDefaultResponse, FLootLockerResponse);


UCLASS()
class LOOTLOCKERSDK_API UCharacterRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	UCharacterRequestHandler();
	static void GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompleteRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void UpdateCharacter(bool IsDefault,const FString& Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void EquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void EquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(), const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void UnEquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP = FPCharacterDefaultResponseBP(),  const FLootLockerCharacterDefaultResponse& OnCompletedRequest = FLootLockerCharacterDefaultResponse());
	static void GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerGetRequests& GetRequests,const FPCharacterLoadoutResponseBP& OnCompletedRequestBP = FPCharacterLoadoutResponseBP(), const FLootLockerCharacterLoadoutResponse& OnCompletedRequest = FLootLockerCharacterLoadoutResponse());
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
	static void GetEquipableContextsByCharacterId(const FLootLockerGetRequests& GetRequests, const FContextDelegateBP& OnCompletedRequestBP = FContextDelegateBP(), const FContextDelegate& OnCompletedRequest = FContextDelegate());
public:
	static FResponseCallback sessionResponse;
	static UHttpClient* HttpClient;
};


