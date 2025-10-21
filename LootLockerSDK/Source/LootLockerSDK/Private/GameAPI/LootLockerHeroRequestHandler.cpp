#include "GameAPI/LootLockerHeroRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerHeroRequestHandler::GetGameHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerGameHeroListDelegate& OnComplete)
{
	return LLAPI<FLootLockerGameHeroListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetGameHeroes, { }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::ListPlayerHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerHeroListDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListPlayerHeroes, { }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerHeroListDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersHeroesBySteamID64, { SteamID64 }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::CreateHero(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(Request, ULootLockerGameEndpoints::CreateHero, { }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::CreateHeroWithVariation(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(Request, ULootLockerGameEndpoints::CreateHero, { }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::GetHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHero, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersDefaultHeroBySteamID64, { SteamID64 }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::UpdateHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(Request, ULootLockerGameEndpoints::UpdateHero, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::DeleteHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLLHeroDefaultResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteHero, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::GetHeroInventory(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FInventoryResponse& OnComplete)
{
	return LLAPI<FLootLockerInventoryResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroInventory, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::GetHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(FLootLockerHeroAssetInstance{ AssetInstanceID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(FLootLockerHeroGlobalAsset{ AssetID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(FLootLockerHeroGlobalAssetVariation{ AssetID, AssetVariationID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	return LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::RemoveAssetToHeroLoadout,  { HeroID, AssetInstanceID }, EmptyQueryParams, PlayerData, OnComplete);
}

