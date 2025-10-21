#pragma once
#include "CoreMinimal.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
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
	FString character_type_name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString name = "";
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
	FString hero_name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FString character_name = "";
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
	FString name = "";
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
	FString name = "";
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
	FString name = "";
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
	FString mounted_at = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	FLootLockerRental rental;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroLoadoutResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	TArray<FLootLockerHeroLoadout> Loadout;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroAssetInstance
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 instance_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroGlobalAsset
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 asset_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerHeroGlobalAssetVariation : public FLootLockerHeroGlobalAsset
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Heroes")
	int32 asset_variation_id = 0;

	FLootLockerHeroGlobalAssetVariation() {}
	FLootLockerHeroGlobalAssetVariation(int32 AssetID, int32 AssetVariationID) : FLootLockerHeroGlobalAsset{ AssetID }, asset_variation_id(AssetVariationID) {}
};
DECLARE_DELEGATE_OneParam(FLootLockerHeroDelegate, FLootLockerHeroResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGameHeroListDelegate, FLootLockerGameHeroListResponse);
DECLARE_DELEGATE_OneParam(FLootLockerHeroListDelegate, FLootLockerHeroListResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPlayerHeroDelegate, FLootLockerPlayerHeroResponse);
DECLARE_DELEGATE_OneParam(FLLHeroDefaultResponseDelegate, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FHeroLoadoutReseponseDelegate, FLootLockerHeroLoadoutResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerHeroRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerHeroRequestHandler() {};

	static FString GetGameHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerGameHeroListDelegate& OnComplete);
	static FString ListPlayerHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerHeroListDelegate& OnComplete);
	static FString ListOtherPlayersHeroesBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerHeroListDelegate& OnComplete);
	static FString CreateHero(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete);
	static FString CreateHeroWithVariation(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete);
	static FString GetHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerPlayerHeroDelegate& OnComplete);
	static FString GetOtherPlayersDefaultHeroBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerPlayerHeroDelegate& OnComplete);
	static FString UpdateHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete);
	static FString DeleteHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLLHeroDefaultResponseDelegate& OnComplete);
	static FString GetHeroInventory(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FInventoryResponse& OnComplete);
	static FString GetHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnComplete);
	static FString GetOtherPlayersHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnComplete);
	static FString AddAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnComplete);
	static FString AddGlobalAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate& OnComplete);
	static FString AddGlobalAssetVariationToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnComplete);
	static FString RemoveAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnComplete);
};
