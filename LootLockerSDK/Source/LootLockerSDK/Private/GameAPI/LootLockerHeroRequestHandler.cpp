#include "GameAPI/LootLockerHeroRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerHeroRequestHandler::HttpClient = nullptr;

ULootLockerHeroRequestHandler::ULootLockerHeroRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerHeroRequestHandler::GetGameHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerGameHeroListBP& OnCompleteBP, const FLootLockerGameHeroListDelegate& OnComplete)
{
	LLAPI<FLootLockerGameHeroListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetGameHeroes, { }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::ListPlayerHeroes(const FLootLockerPlayerData& PlayerData, const FLootLockerHeroListBP& OnCompleteBP, const FLootLockerHeroListDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListPlayerHeroes, { }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP, const FLootLockerHeroListDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersHeroesBySteamID64, { SteamID64 }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::CreateHero(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::CreateHero, { }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::CreateHeroWithVariation(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::CreateHero, { }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHero, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(const FLootLockerPlayerData& PlayerData, const int64 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersDefaultHeroBySteamID64, { SteamID64 }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::UpdateHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP, const FLootLockerPlayerHeroDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::UpdateHero, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::DeleteHero(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP, const FLLHeroDefaultResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteHero, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHeroInventory(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBp, const FInventoryResponse& OnComplete)
{
	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroInventory, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBp, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, FLootLockerHeroAssetInstance{ AssetInstanceID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, FLootLockerHeroGlobalAsset{ AssetID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, FLootLockerHeroGlobalAssetVariation{ AssetID, AssetVariationID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(const FLootLockerPlayerData& PlayerData, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP &OnCompleteBP, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::RemoveAssetToHeroLoadout,  { HeroID, AssetInstanceID }, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}

