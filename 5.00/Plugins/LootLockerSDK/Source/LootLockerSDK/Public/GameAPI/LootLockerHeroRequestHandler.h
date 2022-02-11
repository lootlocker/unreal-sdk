// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerAssetsRequestHandler.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerConfig.h"
#include "LootLockerHeroRequestHandler.generated.h"

// Types

USTRUCT(BlueprintType)
struct FLootLockerGameHero
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int hero_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int character_type_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString character_type_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool player_has_hero;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerHero
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int hero_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_default;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString hero_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString character_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString class_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroRental {
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
struct FLootLockerHeroInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString mounted_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerHeroRental rental;
};

// Requests

USTRUCT(BlueprintType)
struct FLootLockerCreateHeroRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int hero_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

// Responses

USTRUCT(BlueprintType)
struct FLootLockerGameHeroesResponse : public FLootLockerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerGameHero> game_heroes;
};
USTRUCT(BlueprintType)
struct FLootLockerHeroResponse : public FLootLockerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerHero hero;
};
USTRUCT(BlueprintType)
struct FLootLockerHeroesResponse : public FLootLockerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerHero> heroes;
};
USTRUCT(BlueprintType)
struct FLootLockerHeroLoadoutResponse : public FLootLockerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerHeroInventory> loadout;
};
USTRUCT(BlueprintType)
struct FLootLockerHeroInventoryResponse : public FLootLockerResponse {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerHeroInventory> inventory;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FPGameHeroesResponseBP, FLootLockerGameHeroesResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPHeroResponseBP, FLootLockerHeroResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPHeroesResponseBP, FLootLockerHeroesResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPHeroLoadoutResponseBP, FLootLockerHeroLoadoutResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPHeroDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPHeroInventoryResponseBP, FLootLockerHeroInventoryResponse, Var);

DECLARE_DELEGATE_OneParam(FGameHeroesResponse, FLootLockerGameHeroesResponse);
DECLARE_DELEGATE_OneParam(FHeroResponse, FLootLockerHeroResponse);
DECLARE_DELEGATE_OneParam(FHeroesResponse, FLootLockerHeroesResponse);
DECLARE_DELEGATE_OneParam(FHeroLoadoutResponse, FLootLockerHeroLoadoutResponse);
DECLARE_DELEGATE_OneParam(FHeroDefaultResponse, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FHeroInventoryResponse, FLootLockerHeroInventoryResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerHeroRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerHeroRequestHandler();

	static void GetGameHeroes(const FPGameHeroesResponseBP& OnCompletedRequestBP = FPGameHeroesResponseBP(), const FGameHeroesResponse& OnCompletedRequest = FGameHeroesResponse());
	static void ListPlayerHeroes(const FPHeroesResponseBP& OnCompletedRequestBP = FPHeroesResponseBP(), const FHeroesResponse& OnCompletedRequest = FHeroesResponse());
	static void CreateHero(FString HeroName, int HeroId, const FPHeroResponseBP& OnCompletedRequestBP = FPHeroResponseBP(), const FHeroResponse& OnCompletedRequest = FHeroResponse());
	static void GetHero(int HeroId, const FPHeroResponseBP& OnCompletedRequestBP = FPHeroResponseBP(), const FHeroResponse& OnCompletedRequest = FHeroResponse());
	static void GetHeroLoadout(int HeroId, const FPHeroLoadoutResponseBP& OnCompletedRequestBP = FPHeroLoadoutResponseBP(), const FHeroLoadoutResponse& OnCompletedRequest = FHeroLoadoutResponse());

public:
	static ULootLockerHttpClient* HttpClient;
};


