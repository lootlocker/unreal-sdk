// Copyright (c) 2021 LootLocker

#include "LootLockerGameEndpoints.h"

FString ULootLockerGameEndpoints::GameBaseUrl = "https://{domainKey}api.lootlocker.io/game/";

//Auth
FLootLockerEndPoints ULootLockerGameEndpoints::StartSessionEndpoint = InitEndpoint("v2/session", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint = InitEndpoint("session/nintendo-switch", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartXboxSessionEndpoint = InitEndpoint("session/xbox-one", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartAppleSessionEndpoint = InitEndpoint("session/apple", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshAppleSessionEndpoint = InitEndpoint("session/apple", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartGoogleSessionEndpoint = InitEndpoint("session/google", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshGoogleSessionEndpoint = InitEndpoint("session/google", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartEpicSessionEndpoint = InitEndpoint("session/epic", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshEpicSessionEndpoint = InitEndpoint("session/epic", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::VerifyPlayerIdEndPoint = InitEndpoint("v1/player/verify", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::EndSessionEndpoint = InitEndpoint("v1/session", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GuestloginEndpoint = InitEndpoint("v2/session/guest", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartAppleGameCenterSessionEndpoint = InitEndpoint("session/apple/game-center", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshAppleGameCenterSessionEndpoint = InitEndpoint("session/apple/game-center", ELootLockerHTTPMethod::POST);


// White Label
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelSignupEndpoint = InitEndpoint("white-label-login/sign-up", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelLoginEndpoint = InitEndpoint("white-label-login/login", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelAuthEndpoint = InitEndpoint("v2/session/white-label", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint = InitEndpoint("white-label-login/verify-session", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint = InitEndpoint("white-label-login/request-reset-password", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint = InitEndpoint("white-label-login/request-verification", ELootLockerHTTPMethod::POST);

// Account Linking
FLootLockerEndPoints ULootLockerGameEndpoints::StartAccountLinkingProcess = InitEndpoint("upa/link/start", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CheckAccountLinkingProcessStatus = InitEndpoint("upa/link/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CancelAccountLinkingProcess = InitEndpoint("upa/link/{0}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::UnlinkProviderFromAccount = InitEndpoint("player/providers/{0}", ELootLockerHTTPMethod::DELETE);

//Files
FLootLockerEndPoints ULootLockerGameEndpoints::FileUploadEndpoint = InitEndpoint("player/files", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::FileUpdateEndpoint = InitEndpoint("player/files/{0}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::ListFilesEndpoint = InitEndpoint("player/files", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleFileEndpoint = InitEndpoint("player/files/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFileEndpoint = InitEndpoint("player/files/{0}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::ListOtherPlayersFilesEndpoint = InitEndpoint("player/{0}/files", ELootLockerHTTPMethod::GET);

//Player
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerInfoEndPoint = InitEndpoint("v1/player/info", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerInventoryEndPoint = InitEndpoint("v1/player/inventory/list", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SubmitXpEndpoint = InitEndpoint("v1/player/xp", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrencyBalance = InitEndpoint("v1/player/balance", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersXpAndLevelEndpoint = InitEndpoint("v1/player/score/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetMultipleOtherPlayersXPAndLevel = InitEndpoint("v1/player/scores", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint = InitEndpoint("v1/player/notification/assets", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::InitiateDLCMigration = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetDLCsMigrated = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SetProfilePrivate = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::SetProfilePublic = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SetPlayerName = InitEndpoint("player/name", ELootLockerHTTPMethod::PATCH);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerName = InitEndpoint("player/name", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs = InitEndpoint("player/lookup/name", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::LookupMultiplePlayer1stPlatformID = InitEndpoint("player/lookup/ids", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DeletePlayer = InitEndpoint("player", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetUniversalAssetsEndpoint = InitEndpoint("v1/player/inventory/universal", ELootLockerHTTPMethod::GET);

//Heroes
FLootLockerEndPoints ULootLockerGameEndpoints::GetGameHeroes = InitEndpoint("v1/heroes", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlayerHeroes = InitEndpoint("v1/player/heroes", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListOtherPlayersHeroesBySteamID64 = InitEndpoint("v1/heroes/list/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateHero = InitEndpoint("v1/player/heroes", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetHero = InitEndpoint("v1/player/heroes/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersDefaultHeroBySteamID64 = InitEndpoint("v1/player/heroes/default/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateHero = InitEndpoint("v1/player/heroes/{0}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteHero = InitEndpoint("v1/player/heroes/{0}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetHeroInventory = InitEndpoint("v1/player/heroes/{0}/inventory", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetHeroLoadout = InitEndpoint("v1/player/heroes/{0}/loadout", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersHeroLoadout = InitEndpoint("v1/heroes/{0}/loadout", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddAssetToHeroLoadout = InitEndpoint("v1/player/heroes/{0}/loadout", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RemoveAssetToHeroLoadout = InitEndpoint("v1/player/heroes/{0}/loadout/{1}", ELootLockerHTTPMethod::DELETE);

//Player Progressions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllPlayerProgressions = InitEndpoint("player/progressions", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSinglePlayerProgression = InitEndpoint("player/progressions/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddPointsToPlayerProgression = InitEndpoint("player/progressions/{0}/points/add", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SubtractPointsFromPlayerProgression = InitEndpoint("player/progressions/{0}/points/subtract", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ResetPlayerProgression = InitEndpoint("player/progressions/{0}/reset", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeletePlayerProgression = InitEndpoint("player/progressions/{0}", ELootLockerHTTPMethod::DELETE);

//Character
FLootLockerEndPoints ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint = InitEndpoint("v1/player/character/loadout", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateCharacterEndpoint = InitEndpoint("v1/player/character/{0}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateCharacterEndpoint = InitEndpoint("v1/player/character", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint = InitEndpoint("v1/player/character/types", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip/{0}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip/{1}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint = InitEndpoint("v1/player/character/contexts", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint = InitEndpoint("v1/player/character/{0}/contexts", ELootLockerHTTPMethod::GET);

//Character Progressions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllCharacterProgressions = InitEndpoint("player/characters/{0}/progressions", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddPointsToCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}/points/add", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SubtractPointsFromCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}/points/subtract", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ResetCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}/reset", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}", ELootLockerHTTPMethod::DELETE);

//Persistent Storage
FLootLockerEndPoints ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs = InitEndpoint("v1/player/{0}/storage", ELootLockerHTTPMethod::GET);

//Assets
FLootLockerEndPoints ULootLockerGameEndpoints::GetContextsEndpoint = InitEndpoint("v1/contexts", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetsEndpoint = InitEndpoint("v1/assets/list", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetsByIdsEndpoint = InitEndpoint("v1/assets/by/id", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetBonesEndpoint = InitEndpoint("v1/asset/bones", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint = InitEndpoint("v1/asset/favourites", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::DELETE);

//Asset Instances
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::InspectLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/inspect", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::OpenLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/open", ELootLockerHTTPMethod::PUT);

FLootLockerEndPoints ULootLockerGameEndpoints::GetAllInstanceProgressions = InitEndpoint("player/assets/instances/{0}/progressions", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddPointsToInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}/points/add", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SubtractPointsFromInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}/points/subtract", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ResetInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}/reset", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}", ELootLockerHTTPMethod::DELETE);

//User Generated Content
FLootLockerEndPoints ULootLockerGameEndpoints::CreateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file/{1}", ELootLockerHTTPMethod::DELETE);

//Missions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllMissionsEndpoint = InitEndpoint("v1/missions", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetMissionEndpoint = InitEndpoint("v1/mission/{0}", ELootLockerHTTPMethod::GET);
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
FLootLockerEndPoints ULootLockerGameEndpoints::GetOrderDetailsEndpoint = InitEndpoint("v1/purchase/{0}/details", ELootLockerHTTPMethod::GET);

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
FLootLockerEndPoints ULootLockerGameEndpoints::GetScoreListAfter = InitEndpoint("leaderboards/{0}/list?count={1}&after={2}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllMemberRanks = InitEndpoint("leaderboards/member/{0}", ELootLockerHTTPMethod::GET);

//Progressions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllProgressions = InitEndpoint("progressions", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleProgression = InitEndpoint("progressions/{0}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetProgressionTiers = InitEndpoint("progressions/{0}/tiers", ELootLockerHTTPMethod::GET);

//DropTables
FLootLockerEndPoints ULootLockerGameEndpoints::ComputeAndLockDropTable = InitEndpoint("v1/player/droptables/{0}/compute", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerGameEndpoints::PickDropsFromDropTable = InitEndpoint("v1/player/droptables/{0}/pick", ELootLockerHTTPMethod::POST);


//Miscellaneous
FLootLockerEndPoints ULootLockerGameEndpoints::GetServerTimeEndpoint = InitEndpoint("ping", ELootLockerHTTPMethod::GET);

// Crashes
FLootLockerEndPoints ULootLockerGameEndpoints::Crashes = InitEndpoint("v1/crash", ELootLockerHTTPMethod::UPLOAD);

FLootLockerEndPoints ULootLockerGameEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method)
{
	FLootLockerEndPoints Result;
	Result.endpoint = GameBaseUrl + Endpoint;
	Result.requestMethod = Method;

	// Todo: Do this cleanly lol
	if (Endpoint.Contains("white-label-login"))
	{
		// White-label has its own endpoint but I'm too lazy to refactor this whole thing to support it so yolo
		Result.endpoint = Result.endpoint.Replace(TEXT(".io/game/"), TEXT(".io/"));
	}
	return Result;
}
