// Copyright (c) 2021 LootLocker

#include "LootLockerGameEndpoints.h"

FString ULootLockerGameEndpoints::GameBaseUrl = "https://api.lootlocker.io/game/";

//Auth
FLootLockerEndPoints ULootLockerGameEndpoints::StartSessionEndpoint = InitEndpoint("v2/session", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::VerifyPlayerIdEndPoint = InitEndpoint("v1/player/verify", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::EndSessionEndpoint = InitEndpoint("v1/session", ELootLockerHTTPMethod::DEL);

//Player
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerInfoEndPoint = InitEndpoint("v1/player/info", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerInventoryEndPoint = InitEndpoint("v1/player/inventory/list", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SubmitXpEndpoint = InitEndpoint("v1/player/xp", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrencyBalance = InitEndpoint("v1/player/balance", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayerInfoEndpoint = InitEndpoint("v1/player/score", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint = InitEndpoint("v1/player/notification/assets", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CheckPlayerAssetDeactivatonEndpoint = InitEndpoint("v1/player/notification/deactivations", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::InitiateDLCMigration = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetDLCsMigrated = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SetProfilePrivate = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::DEL);
FLootLockerEndPoints ULootLockerGameEndpoints::SetProfilePublic = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SetPlayerName = InitEndpoint("player/name", ELootLockerHTTPMethod::PATCH);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerName = InitEndpoint("player/name", ELootLockerHTTPMethod::GET);

//Character
FLootLockerEndPoints ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint = InitEndpoint("v1/player/character/loadout", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateCharacterEndpoint = InitEndpoint("v1/player/character/{0}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateCharacterEndpoint = InitEndpoint("v1/player/character", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint = InitEndpoint("v1/player/character/types", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip/{0}", ELootLockerHTTPMethod::DEL);
FLootLockerEndPoints ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip/{1}", ELootLockerHTTPMethod::DEL);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint = InitEndpoint("v1/player/character/contexts", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint = InitEndpoint("v1/player/character/{0}/contexts", ELootLockerHTTPMethod::GET);

//Persistent Storage
FLootLockerEndPoints ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::DEL);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs = InitEndpoint("v1/player/{0}/storage", ELootLockerHTTPMethod::GET);

//Assets
FLootLockerEndPoints ULootLockerGameEndpoints::GetContextsEndpoint = InitEndpoint("v1/contexts", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetsEndpoint = InitEndpoint("v1/assets/list", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetsByIdsEndpoint = InitEndpoint("v1/assets/by/id", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetBonesEndpoint = InitEndpoint("v1/asset/bones", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint = InitEndpoint("v1/asset/favourites", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::DEL);

//Asset Instances
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::DEL);
FLootLockerEndPoints ULootLockerGameEndpoints::InspectLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/inspect", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::OpenLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/open", ELootLockerHTTPMethod::PUT);

//User Generated Content
FLootLockerEndPoints ULootLockerGameEndpoints::CreateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::DEL);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file/{1}", ELootLockerHTTPMethod::DEL);

//Missions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllMissionsEndpoint = InitEndpoint("v1/missions", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetMissionEndpoint = InitEndpoint("v1/missions/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::StartMissionEndpoint = InitEndpoint("v1/mission/{0}/start", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::FinishMissionEndpoint = InitEndpoint("v1/mission/{0}/end", ELootLockerHTTPMethod::POST);

//Maps
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllMapsEndpoint = InitEndpoint("v1/maps", ELootLockerHTTPMethod::GET);

//Purchases
FLootLockerEndPoints ULootLockerGameEndpoints::PurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::IOSPurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::AndroidPurchaseEndpoint = InitEndpoint("v1/purchase", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::PollingOrderStatusEndpoint = InitEndpoint("v1/purchase/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ActivateRentalAssetEndpoint = InitEndpoint("v1/asset/instance/{0}/activate", ELootLockerHTTPMethod::POST);

//Trigger Events
FLootLockerEndPoints ULootLockerGameEndpoints::TriggerEventEndpoint = InitEndpoint("v1/player/trigger", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetTriggeredEventsEndpoint = InitEndpoint("v1/player/triggers", ELootLockerHTTPMethod::GET);

//Collectables
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllCollectablesEndpoint = InitEndpoint("v1/collectable", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CollectItemEndpoint = InitEndpoint("v1/collectable", ELootLockerHTTPMethod::POST);

//Messages
FLootLockerEndPoints ULootLockerGameEndpoints::GetMessagesEndpoint = InitEndpoint("v1/messages", ELootLockerHTTPMethod::GET);

//Leaderboards
FLootLockerEndPoints ULootLockerGameEndpoints::GetMemberRank = InitEndpoint("leaderboards/{0}/member/{1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetByListOfMembers = InitEndpoint("leaderboards/{0}/members", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetScoreList = InitEndpoint("leaderboards/{0}/list?count={1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerHTTPMethod::POST);

//DropTables
FLootLockerEndPoints ULootLockerGameEndpoints::ComputeAndLockDropTable = InitEndpoint("v1/player/droptables/{0}/compute", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::PickDropsFromDropTable = InitEndpoint("v1/player/droptables/{0}/pick", ELootLockerHTTPMethod::POST);

FLootLockerEndPoints ULootLockerGameEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method)
{
	FLootLockerEndPoints Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
