// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerCharacterRequestHandler::GetCharacterLoadout(const FLootLockerPlayerData& PlayerData, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UpdateCharacter(const FLootLockerPlayerData& PlayerData, int CharacterId, bool IsDefault, FString Name, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	// set post data
	FLootLockerUpdateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = Name;

	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(characterRequest, ULootLockerGameEndpoints::UpdateCharacterEndpoint, { CharacterId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::CreateCharacter(const FLootLockerPlayerData& PlayerData, bool IsDefault, FString CharacterName, FString CharacterId, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FLootLockerCreateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = CharacterName;
	characterRequest.character_type_id = CharacterId;

	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(characterRequest, ULootLockerGameEndpoints::CreateCharacterEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::DeleteCharacter(const FLootLockerPlayerData& PlayerData, int CharacterId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteCharacterEndpoint, { CharacterId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::ListCharacterTypes(const FLootLockerPlayerData& PlayerData, const FPLootLockerListCharacterTypesResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerListCharacterTypesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(const FLootLockerPlayerData& PlayerData, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipAssetToCharacterWithInstanceRequest equipAssetToDefaultCharacterRequest;
	equipAssetToDefaultCharacterRequest.instance_id = InstanceId;
	LLAPI<FLootLockerResponse>::CallAPI(equipAssetToDefaultCharacterRequest, ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipAssetToCharacterWithInstanceRequest equipAssetToCharacterRequest;
	equipAssetToCharacterRequest.instance_id = InstanceId;
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(equipAssetToCharacterRequest, ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint, { CharacterId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint, { CharacterId, AssetId, AssetVariationId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(const FLootLockerPlayerData& PlayerData, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint, { InstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(const FLootLockerPlayerData& PlayerData, int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint, { CharacterId, InstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& PlayerData, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& PlayerData, FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	const FString Platform = !OtherPlayerPlatform.IsEmpty() ? OtherPlayerPlatform : PlayerData.CurrentPlatform.PlatformString;
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("platform", Platform);
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint, { OtherPlayerId }, QueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(const FLootLockerPlayerData& PlayerData, const FContextDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetContextResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(const FLootLockerPlayerData& PlayerData, int OtherCharacterId, const FContextDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetContextResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint, { OtherCharacterId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::ListPlayerCharacters(const FLootLockerPlayerData& PlayerData, const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest) {
	LLAPI<FLootLockerListPlayerCharactersResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListPlayerCharactersEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetOtherPlayersCharacterLoadouts(const FLootLockerPlayerData& PlayerData, const FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FCharacterLoadoutResponse& OnCompletedRequest) {
	const FString Platform = !OtherPlayerPlatform.IsEmpty() ? OtherPlayerPlatform : PlayerData.CurrentPlatform.PlatformString;
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersCharacterLoadouts, { OtherPlayerId, Platform }, { }, PlayerData, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetOtherPlayersCharacterLoadoutsByUid(const FLootLockerPlayerData& PlayerData, const FString& OtherPlayerUid, const FCharacterLoadoutResponse& OnCompletedRequest) {
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersCharacterLoadoutsByUid, { OtherPlayerUid }, { }, PlayerData, OnCompletedRequest);
}