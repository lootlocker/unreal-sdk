// Copyright (c) 2021 LootLocker

#include "LootLockerGameEndpoints.h"

FString ULootLockerGameEndpoints::GameBaseUrl = "https://api.lootlocker.io/game/";

//Auth
FEndPoints ULootLockerGameEndpoints::StartSessionEndpoint = InitEndpoint("v2/session", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::VerifyPlayerIdEndPoint = InitEndpoint("v1/player/verify", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::EndSessionEndpoint = InitEndpoint("v1/session", ELootLockerHTTPMethod::DELETE);

//Player
FEndPoints ULootLockerGameEndpoints::GetPlayerInfoEndPoint = InitEndpoint("v1/player/info", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetPlayerInventoryEndPoint = InitEndpoint("v1/player/inventory/list", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::SubmitXpEndpoint = InitEndpoint("v1/player/xp", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::GetCurrencyBalance = InitEndpoint("v1/player/balance", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetOtherPlayerInfoEndpoint = InitEndpoint("v1/player/score", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint = InitEndpoint("v1/player/notification/assets", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::CheckPlayerAssetDeactivatonEndpoint = InitEndpoint("v1/player/notification/deactivations", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::InitiateDLCMigration = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::GetDLCsMigrated = InitEndpoint("vv1/player/dlcs", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::SetProfilePrivate = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::DELETE);
FEndPoints ULootLockerGameEndpoints::SetProfilePublic = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::POST);

//Character
FEndPoints ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint = InitEndpoint("v1/player/character/loadout", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::UpdateCharacterEndpoint = InitEndpoint("v1/player/character/{0}", ELootLockerHTTPMethod::PUT);
FEndPoints ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip/{0}", ELootLockerHTTPMethod::DELETE);
FEndPoints ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip/{1}", ELootLockerHTTPMethod::DELETE);
FEndPoints ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout/{0}", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint = InitEndpoint("v1/player/character/contexts", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint = InitEndpoint("v1/player/character/{0}/contexts", ELootLockerHTTPMethod::GET);

//Persistent Storage
FEndPoints ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::DELETE);
FEndPoints ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs = InitEndpoint("v1/player/{0}/storage", ELootLockerHTTPMethod::GET);

//Assets
FEndPoints ULootLockerGameEndpoints::GetContextsEndpoint = InitEndpoint("v1/contexts", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetAssetsEndpoint = InitEndpoint("v1/assets/list", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetAssetsByIdsEndpoint = InitEndpoint("v1/assets/by/id", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetAssetBonesEndpoint = InitEndpoint("v1/asset/bones", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint = InitEndpoint("v1/asset/favourites", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::DELETE);

//Asset Instances
FEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::PUT);
FEndPoints ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::PUT);
FEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::DELETE);
FEndPoints ULootLockerGameEndpoints::InspectLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/inspect", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::OpenLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/open", ELootLockerHTTPMethod::PUT);

//User Generated Content
FEndPoints ULootLockerGameEndpoints::CreateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::PUT);
FEndPoints ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::DELETE);
FEndPoints ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file/{1}", ELootLockerHTTPMethod::DELETE);

//Missions
FEndPoints ULootLockerGameEndpoints::GetAllMissionsEndpoint = InitEndpoint("v1/missions", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::GetMissionEndpoint = InitEndpoint("v1/missions/{0}", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::StartMissionEndpoint = InitEndpoint("v1/mission/{0}/start", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::FinishMissionEndpoint = InitEndpoint("v1/mission/{0}/end", ELootLockerHTTPMethod::POST);

//Maps
FEndPoints ULootLockerGameEndpoints::GetAllMapsEndpoint = InitEndpoint("v1/maps", ELootLockerHTTPMethod::GET);

//Purchases
FEndPoints ULootLockerGameEndpoints::PurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::IOSPurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::AndroidPurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::PollingOrderStatusEndpoint = InitEndpoint("v1/purchase/{0}", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::ActivateRentalAssetEndpoint = InitEndpoint("v1/asset/instance/{0}/activate", ELootLockerHTTPMethod::POST);

//Trigger Events
FEndPoints ULootLockerGameEndpoints::TriggerEventEndpoint = InitEndpoint("v1/player/trigger", ELootLockerHTTPMethod::POST);
FEndPoints ULootLockerGameEndpoints::GetTriggeredEventsEndpoint = InitEndpoint("v1/player/triggers", ELootLockerHTTPMethod::GET);

//Collectables
FEndPoints ULootLockerGameEndpoints::GetAllCollectablesEndpoint = InitEndpoint("v1/collectable", ELootLockerHTTPMethod::GET);
FEndPoints ULootLockerGameEndpoints::CollectItemEndpoint = InitEndpoint("v1/collectable", ELootLockerHTTPMethod::POST);

//Messages
FEndPoints ULootLockerGameEndpoints::GetMessagesEndpoint = InitEndpoint("v1/messages", ELootLockerHTTPMethod::GET);

FEndPoints ULootLockerGameEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method)
{
	FEndPoints Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
