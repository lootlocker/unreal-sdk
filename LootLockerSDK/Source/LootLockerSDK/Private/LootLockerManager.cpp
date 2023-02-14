// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"

void ULootLockerManager::StartSession(const FString& PlayerIdentifier, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartSession(PlayerIdentifier, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(PsnOnlineId, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAndroidSession(DeviceId, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(AmazonLunaGuid, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::StartSteamSession(const FString& SteamId64, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartSteamSession(SteamId64, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnStartedNintendoSwitchSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(NSAIdToken, OnStartedNintendoSwitchSessionRequestCompleted);
}

void ULootLockerManager::StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnStartedXboxSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartXboxSession(XboxUserToken, OnStartedXboxSessionCompleted);
}

void ULootLockerManager::StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnStartedAppleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAppleSession(AuthorizationCode, OnStartedAppleSessionCompleted);
}

void ULootLockerManager::RefreshAppleSession(const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleSession(RefreshToken, OnRefreshAppleSessionCompleted);
}

void ULootLockerManager::WhiteLabelStartSession(const FAuthResponseBP &OnStartWhiteLabelSessionRequestCompleted)
{
	ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(OnStartWhiteLabelSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(Email, Password, Remember, OnWhiteLabelLoginAndStartSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelVerifySession(const FLootLockerVerifySessionResponseBP &OnVerifyWhiteLabelSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(OnVerifyWhiteLabelSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelRequestUserVerification(const int &UserId, const FLootLockerDefaultResponseBP &OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(UserId, OnRequestWhiteLabelUserVerificationRequestCompleted);
}

void ULootLockerManager::WhiteLabelResetPassword(const FString &Email, const FLootLockerDefaultResponseBP &OnResetWhiteLabelPasswordRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(Email, OnResetWhiteLabelPasswordRequestCompleted);
}


void ULootLockerManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelLoginRequestCompleted, const bool Remember /* = false */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(Email, Password, Remember, OnWhiteLabelLoginRequestCompleted);
}

void ULootLockerManager::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegateBP &OnWhiteLabelAccountCreationRequestCompleted)
{
	ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(Email, Password, OnWhiteLabelAccountCreationRequestCompleted);
}

void ULootLockerManager::GuestLogin(const FAuthResponseBP &OnCompletedRequestBP, const FString& PlayerIdentifier)
{
	ULootLockerAuthenticationRequestHandler::GuestLogin(PlayerIdentifier, OnCompletedRequestBP);
}

void ULootLockerManager::VerifyPlayer(const FString& PlatformToken, const FAuthDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform /*= FString()*/)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(PlatformToken, Platform, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const  FAuthDefaultResponseBP& OnEndSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::EndSession(OnEndSessionRequestCompleted);
}

void ULootLockerManager::GetPlayerInfo(const FPInfoResponseBP& OnGetPlayerInfoRequestComplete)
{
    ULootLockerPlayerRequestHandler::GetPlayerInfo(OnGetPlayerInfoRequestComplete);
}

void ULootLockerManager::GetInventory(const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    ULootLockerPlayerRequestHandler::GetInventory(OnGetInventoryRequestCompleted);
}

void ULootLockerManager::SubmitXP(int Points, const FPSubmitResponseBP& OnSubmitXPRequestCompleted)
{
    ULootLockerPlayerRequestHandler::SubmitXp(Points, OnSubmitXPRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersXpAndLevel(FString OtherPlayerId, const FPOtherPlayersXpAndLevelBP& OnGetOtherPlayersXpAndLevelRequestCompleted, FString OtherPlayerPlatform)
{
    ULootLockerPlayerRequestHandler::GetOtherPlayersXpAndLevel(OtherPlayerId, OtherPlayerPlatform, OnGetOtherPlayersXpAndLevelRequestCompleted);
}

void ULootLockerManager::GetMultiplePlayersXp(FString Platform, TArray<FString> PlayerIDs, const FPMultiplePlayersXPBP& OnGetOtherPlayerInfoRequestCompleted)
{
    FLootLockerMultiplePlayersXpRequest request;
    request.platform = Platform;
    request.player_ids = PlayerIDs;
	ULootLockerPlayerRequestHandler::GetMultiplePlayersXp(request, OnGetOtherPlayerInfoRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::GetCurrencyBalance(const FPBalanceResponseBP& OnGetCurrencyBalance)
{
    ULootLockerPlayerRequestHandler::GetCurrencyBalance(OnGetCurrencyBalance);
}


void ULootLockerManager::InitiateDLCMigration(const FResponseCallbackBP& OnInitiateDlcMigration)
{
    ULootLockerPlayerRequestHandler::InitiateDLCMigration(OnInitiateDlcMigration);
}


void ULootLockerManager::GetDLCsMigration(const FPDlcResponseBP& OnGotDlcMigration)
{
    ULootLockerPlayerRequestHandler::GetDLCsMigration(OnGotDlcMigration);
}


void ULootLockerManager::SetProfilePrivate(const FResponseCallbackBP& OnProfileSetPrivate)
{
    ULootLockerPlayerRequestHandler::SetProfilePrivate(OnProfileSetPrivate);
}

void ULootLockerManager::SetProfilePublic(const FResponseCallbackBP& OnProfileSetPublic)
{
    ULootLockerPlayerRequestHandler::SetProfilePublic(OnProfileSetPublic);
}
void ULootLockerManager::SetPlayerName(FString Name, const FPNameResponseBP& OnSetPlayerName)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(Name, OnSetPlayerName);
}

void ULootLockerManager::GetPlayerName(const FPNameResponseBP& OnGetPlayerName)
{
    ULootLockerPlayerRequestHandler::GetPlayerName(OnGetPlayerName);
}

void ULootLockerManager::LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(Request, OnCompletedRequest);
}

void ULootLockerManager::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(Request, OnCompletedRequest);
}

void ULootLockerManager::DeletePlayer(const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::DeletePlayer(OnCompletedRequest);
}


void ULootLockerManager::UploadFile(const FLootLockerFileUploadRequest &Request, const FLootLockerUploadFileBP &OnComplete)
{
	ULLPlayerFilesRequestHandler::UploadFile(Request, OnComplete);
}

void ULootLockerManager::UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::UpdateFile(FileId, Request, OnComplete);
}

void ULootLockerManager::ListFiles(const FLootLockerFileListBP &OnComplete)
{
	ULLPlayerFilesRequestHandler::ListFiles(OnComplete, FLootLockerFileListDelegate());
}

void ULootLockerManager::ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP)
{
    ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(PlayerID, OnCompleteBP);
}

void ULootLockerManager::GetSingleFile(const int32 FileID, const FLootLockerUploadFileBP &OnComplete)
{
	ULLPlayerFilesRequestHandler::GetSingleFile(FileID, OnComplete);
}

void ULootLockerManager::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP &OnComplete)
{
	ULLPlayerFilesRequestHandler::DeletePlayerFile(FileID, OnComplete);
}

// Player Progressions
void ULootLockerManager::GetPlayerProgressions(const int32 Count /*= -1*/, const FString& After /*= ""*/, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgressions(Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgression(ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetPlayerProgression(ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeletePlayerProgression(ProgressionKey, OnCompletedRequest);
}

// Heroes
void ULootLockerManager::GetGameHeroes(const FLootLockerGameHeroListBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetGameHeroes(OnCompleteBP, FLootLockerGameHeroListDelegate());
}

void ULootLockerManager::ListPlayerHeroes(const FLootLockerHeroListBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::ListPlayerHeroes(OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(SteamID64, OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::CreateHero(const FLootLockerCreateHeroRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::CreateHero(Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::CreateHeroWithVariation(Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::GetHero(const int32 HeroID, const FLootLockerPlayerHeroBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetHero(HeroID, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::GetOtherPlayersDefaultHeroBySteamID64(const int32 SteamID64, const FLootLockerPlayerHeroBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(SteamID64, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::UpdateHero(HeroID, Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::DeleteHero(HeroID, OnCompleteBP, FLLHeroDefaultResponseDelegate());
}

void ULootLockerManager::GetHeroInventory(const int32 HeroID, const FPInventoryResponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetHeroInventory(HeroID, OnCompleteBP, FInventoryResponse());
}

void ULootLockerManager::GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetHeroLoadout(HeroID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(HeroID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(HeroID, AssetInstanceID, OnCompleteBP,  FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::AddAssetVariationToHeroLoadout(HeroID, AssetID, AssetVariationID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(HeroID, AssetInstanceID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::UpdateCharacter(int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(CharacterId,IsDefault, Name, OnCompletedRequest);
}

void ULootLockerManager::CreateCharacter(bool IsDefault,  FString CharacterName,  FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(IsDefault, CharacterName, CharacterTypeId, OnCompletedRequestBP);
}

void ULootLockerManager::ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::ListCharacterTypes(OnCompletedRequestBP);
}

void ULootLockerManager::EquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId, OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterByIdAndInstance(int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(CharacterId, InstanceId, OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToCharacterById(int CharacterId,int InstanceId,const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    // FLootLockerGetRequests GetRequests;
    // GetRequests.args.Add(CharacterId);
    // GetRequests.args.Add(InstanceId);
    ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(CharacterId,InstanceId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter( FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId, OtherPlayerPlatform, OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId( int OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(OtherCharacterId, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

// Character Progressions
void ULootLockerManager::GetCharacterProgressions(const int32& CharacterId, const int32 Count /*=-1*/, const FString& After /*=""*/, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgressions(CharacterId, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgression(CharacterId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(CharacterId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(CharacterId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetCharacterProgression(CharacterId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(CharacterId, ProgressionKey, OnCompletedRequest);
}

// Persistent Storage
void ULootLockerManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerManager::AddItemsToPersistentStorage(FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, OnPersistentStorageItemsAddRequestCompleted);
}

void ULootLockerManager::AddItemToPersistentStorage(FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(Item, OnPersistentStorageItemAddRequestCompleted);
}

void ULootLockerManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, OnPersistentStorageItemDeleteRequestCompleted);
}

void ULootLockerManager::GetPlayerPersistentStorage(const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, OnGetPlayerPersistentStorageRequestCompleted);
}

void ULootLockerManager::GetContexts(const FContextDelegateBP& OnGetContextsRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetContexts(OnGetContextsRequestCompleted);
}

void ULootLockerManager::GetAssets(const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted,int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    ULootLockerAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, OnGetAssetsRequestCompleted);
}

void ULootLockerManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetAssetsByIds(AssetIds, OnGetAssetsByIdsRequestCompleted);
}

void ULootLockerManager::GetAssetBones(const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetAssetBones(OnGetAssetBonesRequestCompleted);
}

void ULootLockerManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(OnGetFavouriteAssetIndicesRequestCompleted);
}

void ULootLockerManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::AddAssetToFavourites(AssetId, OnAddAssetToFavouritesRequestCompleted);
}

void ULootLockerManager::RemoveAssetFromFavourites(int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, OnRemoveAssetFromFavouritesRequestCompleted);
}

void ULootLockerManager::GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegateBP &OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetUniversalAssets(After, ItemsCount, OnCompletedRequest);
}


void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(AssetInstanceId, OnGetAllKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, OnGetAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, OnCreateAKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::InspectLootBox(int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted)
{
    ULootLockerAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, OnInspectLootBoxCompleted);
}

void ULootLockerManager::OpenLootBox(int AssetInstanceId, const  FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted)
{
    ULootLockerAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, OnOpenLootBoxCompleted);
}

void ULootLockerManager::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(AssetCandidateData, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AssetCandidateData, OnUpdateAssetCandidateCompleted);
}

void ULootLockerManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, OnDeleteAssetCandidateCompleted);
}

void ULootLockerManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(OnGetAllAssetCandidatesCompleted);
}

void ULootLockerManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, OnGetAssetCandidateCompleted);
}

void ULootLockerManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted);
}

void ULootLockerManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted);
}

// Progressions
void ULootLockerManager::GetProgressions(const int32 Count /*= -1*/, const FString& After /*=""*/, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgressions(Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgression(ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::GetProgressionTiers(const FString& ProgressionKey, const int32 Count /*=-1*/, const int32 After /*=-1*/, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgressionTiers(ProgressionKey, Count, After, OnCompletedRequest);
}

// Missions
void ULootLockerManager::GetAllMissions(const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted)
{
    ULootLockerMissionsRequestHandler::GetAllMissions(OnGetAllMissionsCompleted);
}

void ULootLockerManager::GetMission(int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted)
{
    ULootLockerMissionsRequestHandler::GetMission(MissionId, OnGetMissionCompleted);
}

void ULootLockerManager::StartMission(int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted)
{
    ULootLockerMissionsRequestHandler::StartMission(MissionId, OnStartMissionCompleted);
}

void ULootLockerManager::FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted)
{
    ULootLockerMissionsRequestHandler::FinishMission(MissionId, MissionData, OnFinishMissionCompleted);
}

void ULootLockerManager::GetMaps(const FGetMapsResponseDelegateBP& OnGetMapsCompleted)
{
    ULootLockerMapsRequestHandler::GetMaps(OnGetMapsCompleted);
}

void ULootLockerManager::PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsCompleted)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssets(PurchaseData, OnPurchaseAssetsCompleted);
}

void ULootLockerManager::PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const  FPurchaseResponseDelegateBP& OnPurchaseAssetsAndroidCompleted)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, OnPurchaseAssetsAndroidCompleted);
}

void ULootLockerManager::PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsIOSCompleted)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssetsIOS(PurchaseData, OnPurchaseAssetsIOSCompleted);
}

void ULootLockerManager::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnPollingStatusCompleted)
{
    ULootLockerPurchasesRequestHandler::PollingOrderStatus(PurchaseId, OnPollingStatusCompleted);
}

void ULootLockerManager::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(AssetId, OnActivateRentalAssetCompleted);
}

void ULootLockerManager::GetOrderDetails(int32 OrderId, const bool NoProducts, const FOrderStatusDetailsBP &OnCompleteBP)
{
	ULootLockerPurchasesRequestHandler::GetOrderDetails(OrderId, NoProducts, OnCompleteBP, FOrderStatusDetailsDelegate());
}

void ULootLockerManager::TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnTriggerEventCompleted)
{
    ULootLockerTriggerEventsRequestHandler::TriggerEvent(Event, OnTriggerEventCompleted);
}

void ULootLockerManager::GetTriggeredEvents(const FTriggersResponseDelegateBP& OnGetTriggeredEventsCompleted)
{
    ULootLockerTriggerEventsRequestHandler::GetTriggeredEvents(OnGetTriggeredEventsCompleted);
}

void ULootLockerManager::GetAllCollectables(const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted)
{
    ULootLockerCollectablesRequestHandler::GetAllCollectables(OnGetAllCollectablesCompleted);
}

void ULootLockerManager::CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted)
{
    ULootLockerCollectablesRequestHandler::CollectItem(Item, OnCollectItemCompleted);
}

void ULootLockerManager::GetMessages(const FMessagesResponseDelegateBP& OnGetMessagesCompleted)
{
    ULootLockerMessagesRequestHandler::GetMessages(OnGetMessagesCompleted);
}

void ULootLockerManager::GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboard_key = LeaderboardKey;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(MemberRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetAllMemberRanksRequest MemberRanksRequest;
    MemberRanksRequest.member_id = MemberId;
    MemberRanksRequest.after = After;
    MemberRanksRequest.count = Count;

    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(MemberRanksRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetByListMembersRequest, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboard_key = LeaderboardKey;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    GetScoreList(LeaderboardKey, Count, -1, OnCompletedRequestBP);
}


void ULootLockerManager::SubmitScore(FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(SubmitScoreRequest, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
{
    ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(TableId, OnCompletedRequestBP);
}

void ULootLockerManager::PickDropsFromDropTable(TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
{
    FLootLockerPickDropsFromDropTableRequest request;
    request.picks = Picks;
    ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(request,TableId, OnCompletedRequestBP);
}

// Miscellaneous
void ULootLockerManager::GetServerTime(const FTimeResponseDelegateBP& OnCompletedRequestBP)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(OnCompletedRequestBP);
}
