// Copyright (c) 2021 LootLocker

#include "LootLockerGameEndpoints.h"

FString LootLockerGameEndpoints::GameBaseUrl = "https://api.lootlocker.io/game/";

//Auth
FEndPoints LootLockerGameEndpoints::StartSessionEndpoint = InitEndpoint("v2/session", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::VerifyPlayerIdEndPoint = InitEndpoint("v1/player/verify", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::EndSessionEndpoint = InitEndpoint("v1/session", ELootLockerHTTPMethod::DELETE);

//Player
FEndPoints LootLockerGameEndpoints::GetPlayerInfoEndPoint = InitEndpoint("v1/player/info", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetPlayerInventoryEndPoint = InitEndpoint("v1/player/inventory/list", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::SubmitXpEndpoint = InitEndpoint("v1/player/xp", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::GetCurrencyBalance = InitEndpoint("v1/player/balance", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetOtherPlayerInfoEndpoint = InitEndpoint("v1/player/score", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint = InitEndpoint("v1/player/notification/assets", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::CheckPlayerAssetDeactivatonEndpoint = InitEndpoint("v1/player/notification/deactivations", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::InitiateDLCMigration = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::GetDLCsMigrated = InitEndpoint("vv1/player/dlcs", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::SetProfilePrivate = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerGameEndpoints::SetProfilePublic = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::POST);

//Character
FEndPoints LootLockerGameEndpoints::GetCharacterLoadoutEndpoint = InitEndpoint("v1/player/character/loadout", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::UpdateCharacterEndpoint = InitEndpoint("v1/player/character/{0}", ELootLockerHTTPMethod::PUT);
FEndPoints LootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip/{0}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip/{1}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout/{0}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint = InitEndpoint("v1/player/character/contexts", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint = InitEndpoint("v1/player/character/{0}/contexts", ELootLockerHTTPMethod::GET);

//Persistent Storage
FEndPoints LootLockerGameEndpoints::GetEntirePersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs = InitEndpoint("v1/player/{0}/storage", ELootLockerHTTPMethod::GET);

//Assets
FEndPoints LootLockerGameEndpoints::GetContextsEndpoint = InitEndpoint("v1/contexts", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetAssetsEndpoint = InitEndpoint("v1/assets/list", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetAssetsByIdsEndpoint = InitEndpoint("v1/assets/by/id", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetAssetBonesEndpoint = InitEndpoint("v1/asset/bones", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint = InitEndpoint("v1/asset/favourites", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::AddAssetToFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::DELETE);

//Asset Instances
FEndPoints LootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::PUT);
FEndPoints LootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::PUT);
FEndPoints LootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerGameEndpoints::InspectLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/inspect", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::OpenLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/open", ELootLockerHTTPMethod::PUT);

//User Generated Content
FEndPoints LootLockerGameEndpoints::CreateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::UpdateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::PUT);
FEndPoints LootLockerGameEndpoints::DeleteAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerGameEndpoints::GetAllAssetCandidatesEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::AddFileToAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file/{1}", ELootLockerHTTPMethod::DELETE);

//Missions
FEndPoints LootLockerGameEndpoints::GetAllMissionsEndpoint = InitEndpoint("v1/missions", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::GetMissionEndpoint = InitEndpoint("v1/missions/{0}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::StartMissionEndpoint = InitEndpoint("v1/mission/{0}/start", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::FinishMissionEndpoint = InitEndpoint("v1/mission/{0}/end", ELootLockerHTTPMethod::POST);

//Maps
FEndPoints LootLockerGameEndpoints::GetAllMapsEndpoint = InitEndpoint("v1/maps", ELootLockerHTTPMethod::GET);

//Purchases
FEndPoints LootLockerGameEndpoints::PurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::IOSPurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::AndroidPurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::PollingOrderStatusEndpoint = InitEndpoint("v1/purchase/{0}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::ActivateRentalAssetEndpoint = InitEndpoint("v1/asset/instance/{0}/activate", ELootLockerHTTPMethod::POST);

//Trigger Events
FEndPoints LootLockerGameEndpoints::TriggerEventEndpoint = InitEndpoint("v1/player/trigger", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerGameEndpoints::GetTriggeredEventsEndpoint = InitEndpoint("v1/player/triggers", ELootLockerHTTPMethod::GET);

//Collectables
FEndPoints LootLockerGameEndpoints::GetAllCollectablesEndpoint = InitEndpoint("v1/collectable", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerGameEndpoints::CollectItemEndpoint = InitEndpoint("v1/collectable", ELootLockerHTTPMethod::POST);

//Messages
FEndPoints LootLockerGameEndpoints::GetMessagesEndpoint = InitEndpoint("v1/messages", ELootLockerHTTPMethod::GET);

FEndPoints LootLockerGameEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method)
{
	FEndPoints Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
