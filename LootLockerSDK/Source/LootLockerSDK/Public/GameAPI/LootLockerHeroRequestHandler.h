#pragma once
#include "CoreMinimal.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHeroRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerHero
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 hero_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 character_type_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString character_type_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	bool player_has_hero = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerHero
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 hero_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString hero_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString character_name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	bool is_default = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroResponse : public FLootLockerResponse{
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerHero hero;	
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerHeroResponse : public FLootLockerResponse {
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerPlayerHero hero;	
};

USTRUCT(BlueprintType)
struct FLootLockerGameHeroListResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	TArray<FLootLockerHero> game_heroes;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroListResponse : public FLootLockerResponse
{
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	TArray<FLootLockerPlayerHero> heroes;
};

USTRUCT(BlueprintType)
struct FLootLockerCreateHeroRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 hero_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	bool is_default = false;
};

USTRUCT(BlueprintType)
struct FLootLockerCreateHeroWithVariationRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 hero_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 asset_variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	bool is_default = false;
};

USTRUCT(BlueprintType)
struct FLootLockerUpdateHeroRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	bool is_default = false;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroLoadout
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString mounted_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	TArray<FLootLockerAsset> asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FLootLockerRental rental;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroLoadoutResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString mounted_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	TArray<FLootLockerAsset> asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FLootLockerRental rental;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroAssetInstance
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 instance_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroAsset
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 asset_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 asset_variation_id = 0;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerHeroBP, FLootLockerHeroResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerHeroDelegate, FLootLockerHeroResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGameHeroListBP, FLootLockerGameHeroListResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerGameHeroListDelegate, FLootLockerGameHeroListResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerHeroListBP, FLootLockerHeroListResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerHeroListDelegate, FLootLockerHeroListResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerHeroBP, FLootLockerPlayerHeroResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPlayerHeroDelegate, FLootLockerPlayerHeroResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLLHeroDefaultResponseBP, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FLLHeroDefaultResponseDelegate, FLootLockerResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FHeroLoadoutReseponseBP, FLootLockerHeroLoadoutResponse, Response);
DECLARE_DELEGATE_OneParam(FHeroLoadoutReseponseDelegate, FLootLockerHeroLoadoutResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerHeroRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	static void GetGameHeroes(const FLootLockerGameHeroListBP& OnCompleteBP, const FLootLockerGameHeroListDelegate& OnComplete);
	static void ListPlayerHeroes(const FLootLockerHeroListBP& OnCompleteBP, const FLootLockerHeroListDelegate& OnComplete);
	static void ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP, const FLootLockerHeroListDelegate& OnComplete);
	static void CreateHero(const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete);
	static void CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete);
	static void GetHero(const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete);
	static void GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete);
	static void UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete);
	static void DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP, const FLLHeroDefaultResponseDelegate& OnComplete);
	static void GetHeroInventory(const int32 HeroID, const FPInventoryResponseBP& OnCompleteBp, const FInventoryResponse& OnComplete);
	static void GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete);
	static void GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete);
	static void AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete);
	static void AddAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete);
	static void RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete);

	ULootLockerHeroRequestHandler();
	static ULootLockerHttpClient* HttpClient;
};
