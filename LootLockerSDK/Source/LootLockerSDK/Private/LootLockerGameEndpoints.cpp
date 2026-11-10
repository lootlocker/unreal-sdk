// Copyright (c) 2021 LootLocker

#include "LootLockerGameEndpoints.h"

#ifdef LOOTLOCKER_USE_LOCAL_DEVENV
FString ULootLockerGameEndpoints::BaseUrl = "http://localhost:8080/";
#else
FString ULootLockerGameEndpoints::BaseUrl = "https://{domainKey}api.lootlocker.com/";
#endif
FString ULootLockerGameEndpoints::GameUrlSuffix = "game/";

//Auth
FLootLockerEndPoints ULootLockerGameEndpoints::StartSessionEndpoint = InitEndpoint("v2/session", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartNintendoSwitchSessionEndpoint = InitEndpoint("session/nintendo-switch", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartXboxSessionEndpoint = InitEndpoint("session/xbox-one", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartAppleSessionEndpoint = InitEndpoint("session/apple", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshAppleSessionEndpoint = InitEndpoint("session/apple", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartGoogleSessionEndpoint = InitEndpoint("session/google", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshGoogleSessionEndpoint = InitEndpoint("session/google", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartGooglePlayGamesSessionEndpoint = InitEndpoint("session/google-play-games/v1/login", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshGooglePlayGamesSessionEndpoint = InitEndpoint("session/google-play-games/v1/login", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartEpicSessionEndpoint = InitEndpoint("session/epic", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshEpicSessionEndpoint = InitEndpoint("session/epic", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::VerifyPlayerIdEndPoint = InitEndpoint("v1/player/verify", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::EndSessionEndpoint = InitEndpoint("v1/session", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GuestloginEndpoint = InitEndpoint("v2/session/guest", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartAppleGameCenterSessionEndpoint = InitEndpoint("session/apple/game-center", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshAppleGameCenterSessionEndpoint = InitEndpoint("session/apple/game-center", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::MetaSessionEndpoint = InitEndpoint("session/meta", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SteamSessionEndpoint = InitEndpoint("session/steam", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartDiscordSessionEndpoint = InitEndpoint("session/discord", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshDiscordSessionEndpoint = InitEndpoint("session/discord", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::PlaystationNetworkV3SessionEndpoint = InitEndpoint("session/psn-v3/v1/login", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerBanStatusEndpoint = InitEndpoint("session/ban-status", ELootLockerHTTPMethod::LL_POST);

// Connected Accounts
FLootLockerEndPoints ULootLockerGameEndpoints::ListConnectedAccountsEndpoint = InitEndpoint("v1/connected-accounts", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DisconnectAccountEndpoint = InitEndpoint("player/providers/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint = InitEndpoint("v1/connected-accounts/{0}", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::AttachRemoteSessionToAccountEndpoint = InitEndpoint("v1/connected-accounts/attach", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint = InitEndpoint("v1/connected-accounts/transfer-providers", ELootLockerHTTPMethod::LL_PUT);

// Friends Endpoints
FLootLockerEndPoints ULootLockerGameEndpoints::ListFriendsEndpoint = InitEndpoint("player/friends", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFriendEndpoint = InitEndpoint("player/friends/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint = InitEndpoint("player/friends/incoming", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint = InitEndpoint("player/friends/outgoing", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SendFriendRequestEndpoint = InitEndpoint("player/friends/{0}", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFriendEndpoint = InitEndpoint("player/friends/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::CancelOutgoingFriendRequestEndpoint = InitEndpoint("player/friends/outgoing/{0}/cancel", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::AcceptIncomingFriendRequestEndpoint = InitEndpoint("player/friends/incoming/{0}/accept", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeclineIncomingFriendRequestEndpoint = InitEndpoint("player/friends/incoming/{0}/decline", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ListBlockedPlayersEndpoint = InitEndpoint("player/friends/blocked", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::BlockPlayerEndpoint = InitEndpoint("player/friends/{0}/block", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UnblockPlayerEndpoint = InitEndpoint("player/friends/{0}/unblock", ELootLockerHTTPMethod::LL_POST);

// Followers Endpoints
FLootLockerEndPoints ULootLockerGameEndpoints::ListFollowersEndpoint = InitEndpoint("player/{0}/followers", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListFollowingEndpoint = InitEndpoint("player/{0}/following", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::FollowPlayerEndpoint = InitEndpoint("player/{0}/followers/follow", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UnfollowPlayerEndpoint = InitEndpoint("player/{0}/followers/unfollow", ELootLockerHTTPMethod::LL_DELETE);

// Remote Sessions
FLootLockerEndPoints ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint = InitEndpoint("session/remote/lease", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::LeaseRemoteSessionForLinkingEndpoint = InitEndpoint("session/remote/link/lease", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::StartRemoteSessionEndpoint = InitEndpoint("session/remote", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefreshRemoteSessionEndpoint = InitEndpoint("session/remote", ELootLockerHTTPMethod::LL_POST);

// White Label
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelAuthEndpoint = InitEndpoint("v2/session/white-label", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelSignupEndpoint = InitEndpoint("white-label-login/sign-up", ELootLockerHTTPMethod::LL_POST, ELootLockerApiType::LL_WHITELABEL);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelSignupFieldsEndpoint = InitEndpoint("white-label-login/sign-up/fields", ELootLockerHTTPMethod::LL_GET, ELootLockerApiType::LL_WHITELABEL);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelLoginEndpoint = InitEndpoint("white-label-login/login", ELootLockerHTTPMethod::LL_POST, ELootLockerApiType::LL_WHITELABEL);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelVerifySessionEndpoint = InitEndpoint("white-label-login/verify-session", ELootLockerHTTPMethod::LL_POST, ELootLockerApiType::LL_WHITELABEL);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelRequestPasswordResetEndpoint = InitEndpoint("white-label-login/request-reset-password", ELootLockerHTTPMethod::LL_POST, ELootLockerApiType::LL_WHITELABEL);
FLootLockerEndPoints ULootLockerGameEndpoints::WhiteLabelRequestVerificationEndpoint = InitEndpoint("white-label-login/request-verification", ELootLockerHTTPMethod::LL_POST, ELootLockerApiType::LL_WHITELABEL);

//Files
FLootLockerEndPoints ULootLockerGameEndpoints::FileUploadEndpoint = InitEndpoint("player/files", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::FileUpdateEndpoint = InitEndpoint("player/files/{0}", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::ListFilesEndpoint = InitEndpoint("player/files", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleFileEndpoint = InitEndpoint("player/files/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFileEndpoint = InitEndpoint("player/files/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::ListOtherPlayersFilesEndpoint = InitEndpoint("player/{0}/files", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListFileRevisionsEndpoint = InitEndpoint("player/files/{0}/revisions", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFileRevisionEndpoint = InitEndpoint("player/files/{0}/revisions/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::PromoteFileRevisionEndpoint = InitEndpoint("player/files/{0}/revisions/{1}/current", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFileByKeyEndpoint = InitEndpoint("player/files/key/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListFileRevisionsByKeyEndpoint = InitEndpoint("player/files/key/{0}/revisions", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFileRevisionByKeyEndpoint = InitEndpoint("player/files/key/{0}/revisions/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::PromoteFileRevisionByKeyEndpoint = InitEndpoint("player/files/key/{0}/revisions/{1}/current", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFileByKeyEndpoint = InitEndpoint("player/files/key/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateFileDownloadLinkEndpoint = InitEndpoint("player/files/{0}/download-link/v1", ELootLockerHTTPMethod::LL_POST);

//Player
FLootLockerEndPoints ULootLockerGameEndpoints::GetInfoFromSession = InitEndpoint("player/hazy-hammock/v1/info", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlayerInfo = InitEndpoint("player/hazy-hammock/v1/info", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerInventoryEndPoint = InitEndpoint("v1/player/inventory/list", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlayerSimpleInventoryEndPoint = InitEndpoint("player/inventories/v1", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrencyBalance = InitEndpoint("v1/player/balance", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint = InitEndpoint("v1/player/notification/assets", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::InitiateDLCMigration = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetDLCsMigrated = InitEndpoint("v1/player/dlcs", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SetProfilePrivate = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::SetProfilePublic = InitEndpoint("v1/player/profile/public", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SetPlayerName = InitEndpoint("player/name", ELootLockerHTTPMethod::LL_PATCH);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerName = InitEndpoint("player/name", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs = InitEndpoint("player/lookup/name", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::LookupMultiplePlayer1stPlatformID = InitEndpoint("player/lookup/ids", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DeletePlayer = InitEndpoint("player", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetUniversalAssetsEndpoint = InitEndpoint("v1/player/inventory/universal", ELootLockerHTTPMethod::LL_GET);

// Items & Item Templates
FLootLockerEndPoints ULootLockerGameEndpoints::ListItemTemplatesEndpoint = InitEndpoint("player/inventory/v1", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlayerInventoryItemsEndpoint = InitEndpoint("player/inventory/v1/my", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetPlayerInventoryItemEndpoint = InitEndpoint("player/inventory/v1/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DeletePlayerInventoryItemEndpoint = InitEndpoint("player/inventory/v1/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::ConsumePlayerInventoryItemEndpoint = InitEndpoint("player/inventory/v1/{0}/consume", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SplitPlayerInventoryItemStackEndpoint = InitEndpoint("player/inventory/v1/{0}/split", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::MergePlayerInventoryItemStacksEndpoint = InitEndpoint("player/inventory/v1/merge", ELootLockerHTTPMethod::LL_POST);

//Heroes
FLootLockerEndPoints ULootLockerGameEndpoints::GetGameHeroes = InitEndpoint("v1/heroes", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlayerHeroes = InitEndpoint("v1/player/heroes", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListOtherPlayersHeroesBySteamID64 = InitEndpoint("v1/heroes/list/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateHero = InitEndpoint("v1/player/heroes", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetHero = InitEndpoint("v1/player/heroes/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersDefaultHeroBySteamID64 = InitEndpoint("v1/player/heroes/default/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateHero = InitEndpoint("v1/player/heroes/{0}", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteHero = InitEndpoint("v1/player/heroes/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetHeroInventory = InitEndpoint("v1/player/heroes/{0}/inventory", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetHeroLoadout = InitEndpoint("v1/player/heroes/{0}/loadout", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersHeroLoadout = InitEndpoint("v1/heroes/{0}/loadout", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddAssetToHeroLoadout = InitEndpoint("v1/player/heroes/{0}/loadout", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RemoveAssetToHeroLoadout = InitEndpoint("v1/player/heroes/{0}/loadout/{1}", ELootLockerHTTPMethod::LL_DELETE);

//Player Progressions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllPlayerProgressions = InitEndpoint("player/progressions", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllOtherPlayersProgressions = InitEndpoint("player/progressions/player/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSinglePlayerProgression = InitEndpoint("player/progressions/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleOtherPlayersProgression = InitEndpoint("player/progressions/{0}/player/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddPointsToPlayerProgression = InitEndpoint("player/progressions/{0}/points/add", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SubtractPointsFromPlayerProgression = InitEndpoint("player/progressions/{0}/points/subtract", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ResetPlayerProgression = InitEndpoint("player/progressions/{0}/reset", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeletePlayerProgression = InitEndpoint("player/progressions/{0}", ELootLockerHTTPMethod::LL_DELETE);

//Character
FLootLockerEndPoints ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint = InitEndpoint("v1/player/character/loadout", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateCharacterEndpoint = InitEndpoint("v1/player/character/{0}", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateCharacterEndpoint = InitEndpoint("v1/player/character", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteCharacterEndpoint = InitEndpoint("v1/player/character/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlayerCharactersEndpoint = InitEndpoint("v1/player/character/list", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint = InitEndpoint("v1/player/character/types", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint = InitEndpoint("v1/player/equip/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint = InitEndpoint("v1/player/character/{0}/equip/{1}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint = InitEndpoint("v1/player/loadout/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint = InitEndpoint("v1/player/character/contexts", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint = InitEndpoint("v1/player/character/{0}/contexts", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersCharacterLoadouts = InitEndpoint("v1/player/character/loadout/{0}?platform={1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersCharacterLoadoutsByUid = InitEndpoint("v1/player/character/loadout/puid/{0}", ELootLockerHTTPMethod::LL_GET);


//Character Progressions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllCharacterProgressions = InitEndpoint("player/characters/{0}/progressions", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddPointsToCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}/points/add", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SubtractPointsFromCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}/points/subtract", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ResetCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}/reset", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteCharacterProgression = InitEndpoint("player/characters/{0}/progressions/{1}", ELootLockerHTTPMethod::LL_DELETE);

//Persistent Storage
FLootLockerEndPoints ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint = InitEndpoint("v1/player/storage", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs = InitEndpoint("v1/player/{0}/storage", ELootLockerHTTPMethod::LL_GET);

//Assets
FLootLockerEndPoints ULootLockerGameEndpoints::GetContextsEndpoint = InitEndpoint("v1/contexts", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetsEndpoint = InitEndpoint("v1/assets/list", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetsByIdsEndpoint = InitEndpoint("v1/assets/by/id", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetBonesEndpoint = InitEndpoint("v1/asset/bones", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint = InitEndpoint("v1/asset/favourites", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint = InitEndpoint("v1/asset/{0}/favourite", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GrantAssetToPlayerInventory = InitEndpoint("player/inventory/grant", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ListAssetsEndpoint = InitEndpoint("assets/artful-alpaca/v1", ELootLockerHTTPMethod::LL_POST);

//Asset Instances
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint = InitEndpoint("v1/asset/instance/{0}/storage/{1}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::InspectLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/inspect", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::OpenLootBoxEndpoint = InitEndpoint("v1/asset/instance/{0}/open", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAssetInstanceFromPlayerInventory = InitEndpoint("player/inventory/{0}", ELootLockerHTTPMethod::LL_POST);

FLootLockerEndPoints ULootLockerGameEndpoints::GetAllInstanceProgressions = InitEndpoint("player/assets/instances/{0}/progressions", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddPointsToInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}/points/add", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::SubtractPointsFromInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}/points/subtract", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::ResetInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}/reset", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteInstanceProgression = InitEndpoint("player/assets/instances/{0}/progressions/{1}", ELootLockerHTTPMethod::LL_DELETE);

//User Generated Content
FLootLockerEndPoints ULootLockerGameEndpoints::CreateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::LL_DELETE);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint = InitEndpoint("v1/player/assets/candidates", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint = InitEndpoint("v1/player/assets/candidates/{0}/file/{1}", ELootLockerHTTPMethod::LL_DELETE);

//Maps
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllMapsEndpoint = InitEndpoint("v1/maps", ELootLockerHTTPMethod::LL_GET);

//Purchases
FLootLockerEndPoints ULootLockerGameEndpoints::ActivateRentalAssetEndpoint = InitEndpoint("v1/asset/instance/{0}/activate", ELootLockerHTTPMethod::LL_POST);

FLootLockerEndPoints ULootLockerGameEndpoints::PurchaseCatalogItem = InitEndpoint("purchase", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RedeemAppleAppStorePurchase = InitEndpoint("store/apple/redeem", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase = InitEndpoint("store/google/redeem", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RedeemEpicStorePurchase = InitEndpoint("store/epic/redeem", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RedeemPlayStationStorePurchase = InitEndpoint("store/playstation/redeem", ELootLockerHTTPMethod::LL_POST);

FLootLockerEndPoints ULootLockerGameEndpoints::XboxServiceTicket = InitEndpoint("store/xbox/ticket", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RedeemXboxStorePurchase = InitEndpoint("store/xbox/redeem", ELootLockerHTTPMethod::LL_POST);

FLootLockerEndPoints ULootLockerGameEndpoints::BeginSteamPurchaseRedemption = InitEndpoint("store/steam/redeem/begin", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::QuerySteamPurchaseRedemptionStatus = InitEndpoint("store/steam/redeem/query", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::FinalizeSteamPurchaseRedemption = InitEndpoint("store/steam/redeem/finalise", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::RefundByEntitlementIds = InitEndpoint("refund/v1", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateStripeCheckoutSession = InitEndpoint("store/stripe/checkout", ELootLockerHTTPMethod::LL_POST);

FLootLockerEndPoints ULootLockerGameEndpoints::InitiateAsyncPurchase = InitEndpoint("purchase/inspired-ibex/v1", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::PollAsyncPurchaseStatus = InitEndpoint("purchase/inspired-ibex/v1/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::RetryAsyncPurchase = InitEndpoint("purchase/inspired-ibex/v1/{0}/retry", ELootLockerHTTPMethod::LL_POST);

//Trigger Events
FLootLockerEndPoints ULootLockerGameEndpoints::TriggerEventEndpoint = InitEndpoint("v1/player/trigger", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetTriggeredEventsEndpoint = InitEndpoint("v1/player/triggers", ELootLockerHTTPMethod::LL_GET);

//Triggers
FLootLockerEndPoints ULootLockerGameEndpoints::InvokeTriggers = InitEndpoint("triggers/cozy-crusader/v1", ELootLockerHTTPMethod::LL_POST);

//Notifications
FLootLockerEndPoints ULootLockerGameEndpoints::ListNotifications = InitEndpoint("notifications/v1", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ReadNotifications = InitEndpoint("notifications/v1/read", ELootLockerHTTPMethod::LL_PUT);
FLootLockerEndPoints ULootLockerGameEndpoints::ReadAllNotifications = InitEndpoint("notifications/v1/read/all", ELootLockerHTTPMethod::LL_PUT);

// Broadcasts
FLootLockerEndPoints ULootLockerGameEndpoints::ListBroadcasts = InitEndpoint("broadcasts/v1", ELootLockerHTTPMethod::LL_GET);

//Messages
FLootLockerEndPoints ULootLockerGameEndpoints::GetMessagesEndpoint = InitEndpoint("v1/messages", ELootLockerHTTPMethod::LL_GET);

//Leaderboards
FLootLockerEndPoints ULootLockerGameEndpoints::ListLeaderboards = InitEndpoint("leaderboards", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetMemberRank = InitEndpoint("leaderboards/{0}/member/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetByListOfMembers = InitEndpoint("leaderboards/{0}/members", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetScoreList = InitEndpoint("leaderboards/{0}/list?count={1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetScoreListAfter = InitEndpoint("leaderboards/{0}/list?count={1}&after={2}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SubmitScore = InitEndpoint("leaderboards/{0}/submit", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::QueryScore = InitEndpoint("leaderboards/{0}/query", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::IncrementScore = InitEndpoint("leaderboards/{0}/increment", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllMemberRanks = InitEndpoint("leaderboards/member/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListLeaderboardArchive = InitEndpoint("leaderboards/{0}/archive/list", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetLeaderboardArchive = InitEndpoint("leaderboards/archive/read", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetLeaderboardDetails = InitEndpoint("leaderboards/{0}/info", ELootLockerHTTPMethod::LL_GET);

//Progressions
FLootLockerEndPoints ULootLockerGameEndpoints::GetAllProgressions = InitEndpoint("progressions", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetSingleProgression = InitEndpoint("progressions/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetProgressionTiers = InitEndpoint("progressions/{0}/tiers", ELootLockerHTTPMethod::LL_GET);

//DropTables
FLootLockerEndPoints ULootLockerGameEndpoints::ComputeAndLockDropTable = InitEndpoint("v1/player/droptables/{0}/compute", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::PickDropsFromDropTable = InitEndpoint("v1/player/droptables/{0}/pick", ELootLockerHTTPMethod::LL_POST);

// Currencies
FLootLockerEndPoints ULootLockerGameEndpoints::ListCurrencies = InitEndpoint("currencies", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrencyDetails = InitEndpoint("currency/code/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetCurrencyDenominationsByCode = InitEndpoint("currency/code/{0}/denominations", ELootLockerHTTPMethod::LL_GET);

// Platform Keys
FLootLockerEndPoints ULootLockerGameEndpoints::ListPlatformKeys = InitEndpoint("platform-keys/v1", ELootLockerHTTPMethod::LL_GET);

// Balances
FLootLockerEndPoints ULootLockerGameEndpoints::ListBalancesInWallet = InitEndpoint("balances/wallet/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetWalletByWalletId = InitEndpoint("wallet/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetWalletByHolderId = InitEndpoint("wallet/holder/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::CreditBalanceToWallet = InitEndpoint("balances/credit", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::DebitBalanceToWallet = InitEndpoint("balances/debit", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::CreateWallet = InitEndpoint("wallet", ELootLockerHTTPMethod::LL_POST);

// Catalogs
FLootLockerEndPoints ULootLockerGameEndpoints::ListCatalogs = InitEndpoint("catalogs", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::DeprecatedListCatalogItemsByKey = InitEndpoint("catalog/key/{0}/prices", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListCatalogItemsByKey = InitEndpoint("catalogs/inspired-ibex/v1/catalog/key/{0}/list", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::ListCatalogItemsById = InitEndpoint("catalogs/inspired-ibex/v1/catalog/items", ELootLockerHTTPMethod::LL_POST);

// Entitlements
FLootLockerEndPoints ULootLockerGameEndpoints::ListEntitlements = InitEndpoint("entitlements", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetEntitlement = InitEndpoint("entitlements/{0}", ELootLockerHTTPMethod::LL_GET);

//Miscellaneous
FLootLockerEndPoints ULootLockerGameEndpoints::GetServerTimeEndpoint = InitEndpoint("ping", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetGameInfoEndpoint = InitEndpoint("info/v1", ELootLockerHTTPMethod::LL_POST);

// Crashes
FLootLockerEndPoints ULootLockerGameEndpoints::Crashes = InitEndpoint("v1/crash", ELootLockerHTTPMethod::LL_UPLOAD);

//Feedback
FLootLockerEndPoints ULootLockerGameEndpoints::ListFeedbackCategories = InitEndpoint("feedback/category/entity/{0}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::SendFeedback = InitEndpoint("feedback", ELootLockerHTTPMethod::LL_POST);

// Error Reporting
FLootLockerEndPoints ULootLockerGameEndpoints::ReportSDKError = InitEndpoint("error-report", ELootLockerHTTPMethod::LL_POST);

// Metadata
FLootLockerEndPoints ULootLockerGameEndpoints::ListMetadata = InitEndpoint("metadata/source/{0}/id/{1}", ELootLockerHTTPMethod::LL_GET);
FLootLockerEndPoints ULootLockerGameEndpoints::GetMultisourceMetadata = InitEndpoint("metadata/multisource", ELootLockerHTTPMethod::LL_POST);
FLootLockerEndPoints ULootLockerGameEndpoints::MetadataActions = InitEndpoint("metadata", ELootLockerHTTPMethod::LL_POST);

// Presence (WebSocket)
FLootLockerEndPoints ULootLockerGameEndpoints::PresenceWebSocketEndpoint = InitEndpoint("presence/v1", ELootLockerHTTPMethod::LL_GET, ELootLockerApiType::LL_WEBSOCKET);


FLootLockerEndPoints ULootLockerGameEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method, ELootLockerApiType ApiType /*= ELootLockerApiType::LL_GAME*/)
{
	FLootLockerEndPoints Result;
	FString UrlBase = BaseUrl;
	switch (ApiType)
	{
		case ELootLockerApiType::LL_WHITELABEL:
			break;
		case ELootLockerApiType::LL_WEBSOCKET:
			// Convert HTTP(S) to WS(S) for WebSocket endpoints
			if (UrlBase.StartsWith(TEXT("https://")))
			{
				UrlBase = UrlBase.Replace(TEXT("https://"), TEXT("wss://"));
			}
			else if (UrlBase.StartsWith(TEXT("http://")))
			{
				UrlBase = UrlBase.Replace(TEXT("http://"), TEXT("ws://"));
			}
			UrlBase += GameUrlSuffix;
			break;
		case ELootLockerApiType::LL_GAME:
		default:
			UrlBase += GameUrlSuffix;
	}
	Result.endpoint = UrlBase + Endpoint;
	Result.requestMethod = Method;

	return Result;
}
