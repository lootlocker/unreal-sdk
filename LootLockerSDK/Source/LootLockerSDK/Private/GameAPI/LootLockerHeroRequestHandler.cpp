#include "GameAPI/LootLockerHeroRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerHeroRequestHandler::GetGameHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerGameHeroListDelegate& OnComplete)
{
	LLAPI<FLootLockerGameHeroListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetGameHeroes, { }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::ListPlayerHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerHeroListDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListPlayerHeroes, { }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerHeroListDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersHeroesBySteamID64, { SteamID64 }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::CreateHero(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(Request, ULootLockerGameEndpoints::CreateHero, { }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::CreateHeroWithVariation(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(Request, ULootLockerGameEndpoints::CreateHero, { }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHero, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersDefaultHeroBySteamID64, { SteamID64 }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::UpdateHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(Request, ULootLockerGameEndpoints::UpdateHero, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::DeleteHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLLHeroDefaultResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteHero, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHeroInventory(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FInventoryResponse& OnComplete)
{
	LLAPI<FLootLockerInventoryResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroInventory, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(FLootLockerHeroAssetInstance{ AssetInstanceID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(FLootLockerHeroGlobalAsset{ AssetID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(FLootLockerHeroGlobalAssetVariation{ AssetID, AssetVariationID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::RemoveAssetToHeroLoadout,  { HeroID, AssetInstanceID }, EmptyQueryParams, PlayerData, OnComplete);
}

