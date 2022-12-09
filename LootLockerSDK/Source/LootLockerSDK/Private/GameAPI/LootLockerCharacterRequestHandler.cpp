// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCharacterRequestHandler::HttpClient = nullptr;

ULootLockerCharacterRequestHandler::ULootLockerCharacterRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCharacterRequestHandler::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UpdateCharacter(int CharacterId, bool IsDefault,  FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	// set post data
	FLootLockerUpdateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = Name;
	
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, characterRequest, ULootLockerGameEndpoints::UpdateCharacterEndpoint, { CharacterId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::CreateCharacter(bool IsDefault,  FString CharacterName,  FString CharacterId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FLootLockerListCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = CharacterName;
	characterRequest.character_type_id = CharacterId;

	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, characterRequest, ULootLockerGameEndpoints::CreateCharacterEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP, const FPLootLockerListCharacterTypesResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerListCharacterTypesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(int InstanceId,const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipAssetToCharacterWithInstanceRequest equipAssetToDefaultCharacterRequest;
	equipAssetToDefaultCharacterRequest.instance_id = InstanceId;
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, equipAssetToDefaultCharacterRequest, ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(int CharacterId,int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipAssetToCharacterWithInstanceRequest equipAssetToCharacterRequest;
	equipAssetToCharacterRequest.instance_id = InstanceId;
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, equipAssetToCharacterRequest, ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint, { CharacterId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(int CharacterId,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint, { CharacterId, AssetId, AssetVariationId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint, { InstanceId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(int CharacterId,int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint, { CharacterId, InstanceId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP,  const FCharacterLoadoutResponse& OnCompletedRequest)
{
	const FString Platform = !OtherPlayerPlatform.IsEmpty() ? OtherPlayerPlatform : LootLockerUtilities::CurrentPlatformFString::Get();
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("platform", Platform);
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint, { OtherPlayerId },QueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetContextResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetContextResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint, { OtherCharacterId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}
