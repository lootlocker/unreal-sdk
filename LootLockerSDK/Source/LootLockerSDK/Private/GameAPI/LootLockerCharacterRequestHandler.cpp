// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"

ULootLockerHttpClient* ULootLockerCharacterRequestHandler::HttpClient = nullptr;
const LLAPI<FLootLockerCharacterLoadoutResponse>::FResponseInspectorCallback FLootLockerCharacterLoadoutResponse::ManualDeserializer =
            LLAPI<FLootLockerCharacterLoadoutResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerCharacterLoadoutResponse& Response)
            {
                if(Response.success)
                {
                    // Add "default" to is_default field manually if it exists
                    for(int i = 0; i < Response.loadouts.Num(); ++i)
                    {
                        auto& loadout = Response.loadouts[i];
                        
                        const TSharedPtr<FJsonObject> jsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
                        auto jsonLoadouts = jsonObject->GetArrayField(TEXT("loadouts"));
                        auto jsonLoadout = jsonLoadouts[i]->AsObject();
                        loadout.character.is_default = jsonLoadout->GetBoolField(TEXT("default"));
                    }
                }
            });

const LLAPI<FLootLockerListPlayerCharactersResponse>::FResponseInspectorCallback FLootLockerListPlayerCharactersResponse::ManualDeserializer =
            LLAPI<FLootLockerListPlayerCharactersResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerListPlayerCharactersResponse& Response)
            {
                if(Response.success)
                {
                    // Add "default" to is_default field manually if it exists
                    for(int i = 0; i < Response.items.Num(); ++i)
                    {
                        auto& item = Response.items[i];
                        
                        const TSharedPtr<FJsonObject> jsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
                        auto jsonItems = jsonObject->GetArrayField(TEXT("items"));
                        auto jsonItem = jsonItems[i]->AsObject();
                        item.is_default = jsonItem->GetBoolField(TEXT("default"));
                    }
                }
            });

ULootLockerCharacterRequestHandler::ULootLockerCharacterRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCharacterRequestHandler::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, FLootLockerCharacterLoadoutResponse::ManualDeserializer);
}

void ULootLockerCharacterRequestHandler::UpdateCharacter(int CharacterId, bool IsDefault,  FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	// set post data
	FLootLockerUpdateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = Name;
	
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, characterRequest, ULootLockerGameEndpoints::UpdateCharacterEndpoint, { CharacterId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, FLootLockerCharacterLoadoutResponse::ManualDeserializer);
}

void ULootLockerCharacterRequestHandler::CreateCharacter(bool IsDefault,  FString CharacterName,  FString CharacterId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FLootLockerCreateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = CharacterName;
	characterRequest.character_type_id = CharacterId;

	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, characterRequest, ULootLockerGameEndpoints::CreateCharacterEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, FLootLockerCharacterLoadoutResponse::ManualDeserializer);
}

void ULootLockerCharacterRequestHandler::ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP, const FPLootLockerListCharacterTypesResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerListCharacterTypesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(int InstanceId,const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipAssetToCharacterWithInstanceRequest equipAssetToDefaultCharacterRequest;
	equipAssetToDefaultCharacterRequest.instance_id = InstanceId;
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, equipAssetToDefaultCharacterRequest, ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(int CharacterId,int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipAssetToCharacterWithInstanceRequest equipAssetToCharacterRequest;
	equipAssetToCharacterRequest.instance_id = InstanceId;
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, equipAssetToCharacterRequest, ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint, { CharacterId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(int CharacterId,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint, { CharacterId, AssetId, AssetVariationId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint, { InstanceId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(int CharacterId,int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint, { CharacterId, InstanceId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, FLootLockerCharacterLoadoutResponse::ManualDeserializer);
}

void ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP,  const FCharacterLoadoutResponse& OnCompletedRequest)
{
	const FString Platform = !OtherPlayerPlatform.IsEmpty() ? OtherPlayerPlatform : ULootLockerCurrentPlatform::GetString();
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("platform", Platform);
	LLAPI<FLootLockerCharacterLoadoutResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint, { OtherPlayerId },QueryParams, OnCompletedRequestBP, OnCompletedRequest, FLootLockerCharacterLoadoutResponse::ManualDeserializer);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetContextResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetContextResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint, { OtherCharacterId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerCharacterRequestHandler::ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP, const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest) {
	LLAPI<FLootLockerListPlayerCharactersResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListPlayerCharactersEndpoint, {}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, FLootLockerListPlayerCharactersResponse::ManualDeserializer);
}
