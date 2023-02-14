#include "GameAPI/LootLockerHeroRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerHeroRequestHandler::HttpClient = nullptr;

ULootLockerHeroRequestHandler::ULootLockerHeroRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerHeroRequestHandler::GetGameHeroes(const FLootLockerGameHeroListBP &OnCompleteBP, const FLootLockerGameHeroListDelegate &OnComplete)
{
	LLAPI<FLootLockerGameHeroListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetGameHeroes, { },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::ListPlayerHeroes(const FLootLockerHeroListBP &OnCompleteBP, const FLootLockerHeroListDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListPlayerHeroes, { },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListBP &OnCompleteBP, const FLootLockerHeroListDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersHeroesBySteamID64, { SteamID64 },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::CreateHero(const FLootLockerCreateHeroRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP, const FLootLockerPlayerHeroDelegate &OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::CreateHero, { },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP, const FLootLockerPlayerHeroDelegate &OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::CreateHero, { },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHero(const int32 HeroID, const FLootLockerPlayerHeroBP &OnCompleteBP, const FLootLockerPlayerHeroDelegate &OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHero,  { HeroID },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroBP &OnCompleteBP, const FLootLockerPlayerHeroDelegate &OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersDefaultHeroBySteamID64,  { SteamID64 },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP, const FLootLockerPlayerHeroDelegate &OnComplete)
{
	LLAPI<FLootLockerPlayerHeroResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::UpdateHero, { HeroID },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseBP &OnCompleteBP, const FLLHeroDefaultResponseDelegate &OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteHero, { HeroID },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHeroInventory(const int32 HeroID, const FPInventoryResponseBP &OnCompleteBp, const FInventoryResponse &OnComplete)
{
	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroInventory, { HeroID },EmptyQueryParams, OnCompleteBp, OnComplete);
}

void ULootLockerHeroRequestHandler::GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP &OnCompleteBP, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetHeroLoadout,  { HeroID },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP &OnCompleteBP, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersHeroLoadout,  { HeroID },EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP &OnCompleteBP, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, FLootLockerHeroAssetInstance{ AssetInstanceID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::AddAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP, const FHeroLoadoutReseponseDelegate& OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, FLootLockerHeroAsset{ AssetID, AssetVariationID }, ULootLockerGameEndpoints::AddAssetToHeroLoadout, { HeroID }, EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP &OnCompleteBP, const FHeroLoadoutReseponseDelegate &OnComplete)
{
	LLAPI<FLootLockerHeroLoadoutResponse>::CallAPI(HttpClient, FLootLockerHeroAssetInstance{ AssetInstanceID }, ULootLockerGameEndpoints::RemoveAssetToHeroLoadout,  { HeroID }, EmptyQueryParams, OnCompleteBP, OnComplete);
}

