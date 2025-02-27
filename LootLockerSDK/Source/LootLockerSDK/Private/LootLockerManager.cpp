// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

#include "LootLockerPlatformManager.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"

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

void ULootLockerManager::StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FString& SteamAppId, const FAuthResponseBP& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartSteamSession(SteamSessionTicket, SteamAppId, OnCompletedRequest);
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

void ULootLockerManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, OnStartedAppleGameCenterSessionCompleted);
}

void ULootLockerManager::RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(RefreshToken, OnRefreshAppleGameCenterSessionCompleted);
}

void ULootLockerManager::StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, OnStartedGoogleSessionRequestCompleted);
}

void ULootLockerManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Platform, OnStartedGoogleSessionRequestCompleted);
}

void ULootLockerManager::RefreshGoogleSession(const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(RefreshToken, OnRefreshGoogleSessionCompleted);
}

void ULootLockerManager::StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartEpicSession(IdToken, OnStartedEpicSessionRequestCompleted);
}

void ULootLockerManager::RefreshEpicSession(const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshEpicSession(RefreshToken, OnRefreshEpicSessionCompleted);
}

void ULootLockerManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartMetaSession(UserId, Nonce, OnMetaSessionRequestCompleted);
}

void ULootLockerManager::RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshMetaSession(RefreshToken, OnMetaSessionRequestCompleted);
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

void ULootLockerManager::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(Email, OnRequestWhiteLabelUserVerificationRequestCompleted);
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

void ULootLockerManager::VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform /*= FString()*/)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(PlatformToken, Platform, -1, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const  FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::EndSession(OnEndSessionRequestCompleted);
}

//==================================================
// Connected Accounts
//==================================================
void ULootLockerManager::ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(OnCompleteBP);
}

void ULootLockerManager::DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(AccountToDisconnect, OnCompleteBP);
}

void ULootLockerManager::ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(IdToken, OnCompleteBP);
}

void ULootLockerManager::ConnectGoogleAccountWithPlatform(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(IdToken, Platform, OnCompleteBP);
}

void ULootLockerManager::ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(AuthorizationCode, OnCompleteBP);
}

//==================================================
// Remote Sessions
//==================================================
FString ULootLockerManager::StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegateBP& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
    return ULootLockerRemoteSessionRequestHandler::StartRemoteSession(RemoteSessionLeaseInformation, FLootLockerLeaseRemoteSessionResponseDelegate(), RemoteSessionLeaseStatusUpdate, FLootLockerRemoteSessionStatusPollingResponseDelegate(), OnComplete, FLootLockerStartRemoteSessionResponseDelegate(), PollingIntervalSeconds, TimeOutAfterMinutes);
}

void ULootLockerManager::CancelRemoteSessionProcess(FString ProcessID)
{
    ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(ProcessID);
}

void ULootLockerManager::RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(RefreshToken, OnCompletedRequest);
}

//==================================================
// Player
//==================================================
void ULootLockerManager::GetCurrentPlayerInfo(const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(OnCompletedRequest);
}

void ULootLockerManager::ListPlayerInfo(TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::ListPlayerInfo(PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, OnCompletedRequest);
}

void ULootLockerManager::GetInventory(const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    ULootLockerPlayerRequestHandler::GetInventory(OnGetInventoryRequestCompleted);
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

void ULootLockerManager::LookupMultiplePlayersDataUsingIDs(const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(Request, OnCompletedRequest);
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

void ULootLockerManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgressions(PlayerUlid, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetOtherPlayersProgression(const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgression(PlayerUlid, ProgressionKey, OnCompletedRequest);
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

void ULootLockerManager::AddGlobalAssetToHeroLoadout(const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
	ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(HeroID, AssetID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddGlobalAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
	ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(HeroID, AssetID, AssetVariationID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
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

void ULootLockerManager::ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::ListPlayerCharacters(OnCompletedRequestBP);
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

void ULootLockerManager::GrantAssetWithVariationToPlayerInventory(const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(AssetID, AssetVariationID, AssetRentalOptionID, OnCompletedRequest);
}

void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(AssetInstanceId, OnGetAllKeyValuePairsForAssetInstanceCompleted);
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

void ULootLockerManager::DeleteAssetInstanceFromPlayerInventory(int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(AssetInstanceID, OnCompleted);
}

void ULootLockerManager::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(AssetCandidateData, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::CreateAssetCandidateAndMarkComplete(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(AssetCandidateData, OnCreateAssetCandidateCompleted);
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

//Instance progression

void ULootLockerManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(AssetInstanceId, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgression(AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetInstanceProgression(AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(AssetInstanceId, ProgressionKey, OnCompletedRequest);
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

void ULootLockerManager::ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(AssetInstanceId, OnActivateRentalAssetCompleted);
}

void ULootLockerManager::LootLockerPurchaseSingleCatalogItem(const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    LootLockerPurchaseCatalogItems(WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest);
}

void ULootLockerManager::LootLockerPurchaseCatalogItems(const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(WalletId, ItemsToPurchase, OnCompletedRequest);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForPlayer(const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(TransactionId, Sandboxed, OnCompletedRequest);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(ClassId, TransactionId, Sandboxed, OnCompletedRequest);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ProductId, const FString& PurchaseToken,	const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(ProductId, PurchaseToken, OnCompletedRequest);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString& ProductId,	const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(ClassId, ProductId, PurchaseToken, OnCompletedRequest);
}

void ULootLockerManager::BeginSteamPurchaseRedemption(const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

void ULootLockerManager::BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(ClassId, SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

void ULootLockerManager::QuerySteamPurchaseRedemptionStatus(const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(EntitlementId, OnCompletedRequest);
}

void ULootLockerManager::FinalizeSteamPurchaseRedemption(const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(EntitlementId, OnCompletedRequest);
}

//Triggers
void ULootLockerManager::InvokeTriggersByKey(const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnComplete)
{
    ULootLockerTriggersRequestHandler::InvokeTriggersByKey(KeysToInvoke, OnComplete);
}

//Notifications
void ULootLockerManager::ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(OnComplete);
}

void ULootLockerManager::ListNotifications(bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(ShowRead, OfType, WithSource, PerPage, Page, OnComplete);
}

void ULootLockerManager::ListNotificationsWithPriority(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(WithPriority, ShowRead, OfType, WithSource, PerPage, Page, OnComplete);
}

void ULootLockerManager::MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(OnComplete);
}

void ULootLockerManager::MarkNotificationsAsRead(const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    TArray<FString> UnreadNotificationIds;
	for (const FLootLockerNotification& Notification : Notifications)
	{
		if(!Notification.Read)
		{
            UnreadNotificationIds.Add(Notification.Id);
		}
	}
    MarkNotificationsAsReadByIds(UnreadNotificationIds, OnComplete);
}

void ULootLockerManager::MarkNotificationsAsReadByIds(const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(NotificationIDs, OnComplete);
}

bool ULootLockerManager::TryGetNotificationsByIdentifyingValue(const FLootLockerListNotificationsResponse& NotificationsResponse, const FString& IdentifyingValue, TArray<FLootLockerNotification>& Notifications)
{
    return NotificationsResponse.TryGetNotificationsByIdentifyingValue(IdentifyingValue, Notifications);
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

void ULootLockerManager::ListLeaderboards(int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardRequestHandler::ListLeaderboards(Count, After, OnCompletedRequestBP);
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

void ULootLockerManager::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(Key, Count, After, OnCompletedRequestBP);
}

void ULootLockerManager::GetLeaderboardDetails(const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(LeaderboardKey, OnCompletedRequestBP);
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

// Currencies
void ULootLockerManager::ListCurrencies(const FLootLockerListCurrenciesResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::ListCurrencies(OnCompletedRequest);
}

void ULootLockerManager::GetCurrencyDetails(const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDetails(CurrencyCode, OnCompletedRequest);
}

void ULootLockerManager::GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(CurrencyCode, OnCompletedRequest);
}

// Balances

void ULootLockerManager::ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::ListBalancesInWallet(WalletID, OnComplete);
}

void ULootLockerManager::GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByWalletID(WalletID, OnComplete);
}

void ULootLockerManager::GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByHolderID(HolderULID, HolderType, OnComplete);
}

void ULootLockerManager::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::CreditBalanceToWallet(WalletID, CurrencyID, Amount, OnComplete);
}

void ULootLockerManager::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::DebitBalanceToWallet(WalletID, CurrencyID, Amount, OnComplete);
}

// Catalogs

void ULootLockerManager::ListCatalogs(const FLootLockerListCatalogsResponseBP& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogs(OnComplete);
}

void ULootLockerManager::ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogItems(CatalogKey, Count, After, OnComplete);
}

TArray<FLootLockerInlinedCatalogEntry> ULootLockerManager::ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog)
{
    return ULootLockerCatalogRequestHandler::ConvertCatalogToInlineItems(Catalog);
}

// Entitlements
void ULootLockerManager::ListEntitlements(int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnComplete)
{
    ULootLockerEntitlementRequestHandler::ListEntitlements(Count, After, OnComplete);
}

void ULootLockerManager::GetEntitlement(const FString& EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnComplete)
{
    ULootLockerEntitlementRequestHandler::GetEntitlement(EntitlementID, OnComplete);
}

void ULootLockerManager::ListPlayerFeedbackCategories(const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ELootLockerFeedbackType::Player, OnComplete);
}

void ULootLockerManager::ListGameFeedbackCategories(const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ELootLockerFeedbackType::Game, OnComplete);
}

void ULootLockerManager::ListUGCFeedbackCategories(const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ELootLockerFeedbackType::Ugc, OnComplete);
}

void ULootLockerManager::SendPlayerFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(Ulid, Description, CategoryID, ELootLockerFeedbackType::Player, OnComplete);
}

void ULootLockerManager::SendGameFeedback(const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback("", Description, CategoryID, ELootLockerFeedbackType::Game, OnComplete);
}

void ULootLockerManager::SendUGCFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(Ulid, Description, CategoryID, ELootLockerFeedbackType::Ugc, OnComplete);

}

// Metadata

void ULootLockerManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::ListMetadata(Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

void ULootLockerManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::ListMetadata(Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, OnComplete);
}

void ULootLockerManager::GetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::GetMetadata(Source, SourceID, Key, IgnoreFiles, OnComplete);
}

void ULootLockerManager::GetMultisourceMetadata(const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::GetMultisourceMetadata(SourcesAndKeysToGet, IgnoreFiles, OnComplete);
}

void ULootLockerManager::ParseLootLockerMetadataEntry(const FLootLockerMetadataEntry& Entry,
                                                      ELootLockerMetadataParserOutputTypes& MetadataTypeSwitch,
                                                      FString& StringValue, int& IntegerValue,
                                                      float& FloatValue, FString& NumberString, bool& BoolValue,
                                                      FString& JsonStringValue,
                                                      FLootLockerMetadataBase64Value& Base64Value,
                                                      FString& ErrorMessage, FLootLockerMetadataEntry& OutEntry)
{
    MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnError;
    StringValue = "";
    BoolValue = false;
    IntegerValue = 0;
    FloatValue = 0.0f;
    NumberString = "";
    JsonStringValue = "";
    Base64Value = FLootLockerMetadataBase64Value();
    ErrorMessage = "Unknown Error";
    OutEntry = Entry;
    FString ValueToParse;
    if(!Entry.TryGetSerializedValue(ValueToParse))
    {
        ErrorMessage = FString::Format(TEXT("Couldn't get serialized value for type: \"{0}\""), { static_cast<int>(Entry.Type) }); ;
        return;	    
    }
    switch (Entry.Type)
    {
    case ELootLockerMetadataTypes::String:
    {
        if (Entry.TryGetValueAsString(StringValue))
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnString;
            return;
        }
        ErrorMessage = "Value \"" + ValueToParse + "\" could not be parsed";
        return;
    }
    case ELootLockerMetadataTypes::Number:
    {
        if (!FCString::IsNumeric(*ValueToParse))
        {
            ErrorMessage = "Could not parse value \"" + ValueToParse + "\" as Number because it is not numeric";
            return;
        }
        // Parse as float
        if (ValueToParse.Contains(".") && Entry.TryGetValueAsFloat(FloatValue))
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnFloat;
            return;
        }
        // Parse as int
        if (Entry.TryGetValueAsInteger(IntegerValue))
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnInteger;
            return;
        }
        //Treat as non int or float value, likely BigInt or BigDecimal
        MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnNumber;
        NumberString = ValueToParse;
        return;
    }
    case ELootLockerMetadataTypes::Bool:
    {
        if (Entry.TryGetValueAsBool(BoolValue))
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnBool;
            return;
        }
        ErrorMessage = "Value \"" + ValueToParse + "\" could not be parsed as boolean value";
        return;
    }
    case ELootLockerMetadataTypes::Json:
    {
        TSharedPtr<FJsonObject> JsonObject = nullptr;
        if (Entry.TryGetValueAsJsonObject(JsonObject) && JsonObject.IsValid())
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnJson;
            JsonStringValue = ValueToParse;
            return;
        }
        TArray<TSharedPtr<FJsonValue>> OutputJsonArray;
        if (Entry.TryGetValueAsJsonArray(OutputJsonArray))
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnJson;
            JsonStringValue = ValueToParse;
            return;
        }
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because it is not a valid Json String";
        return;
    }
    case ELootLockerMetadataTypes::Base64:
    {
        if (Entry.TryGetValueAsBase64(Base64Value) && !Base64Value.Content_type.IsEmpty())
        {
            MetadataTypeSwitch = ELootLockerMetadataParserOutputTypes::OnBase64;
            return;
        }
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because it is not a valid LootLocker Metadata Base64 Object";
        return;
    }
    default:
    {
        ErrorMessage = "Could not parse value \"" + ValueToParse + "\" because the type \"" + ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataTypes"), static_cast<int32>(Entry.Type)) + "\" was not recognized by the parser";
        return;
    }
    }
}

void ULootLockerManager::SetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::SetMetadata(Source, SourceID, MetadataToActionsToPerform, OnComplete);
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionString(ELootLockerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeStringEntry(Key, Tags, Access, Value) };
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionFloat(ELootLockerMetadataActions Action, const FString& Key, const float& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeFloatEntry(Key, Tags, Access, Value) };
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionInteger(ELootLockerMetadataActions Action, const FString& Key, const int Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{Action, FLootLockerMetadataEntry::MakeIntegerEntry(Key, Tags, Access, Value)};
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionBool(ELootLockerMetadataActions Action, const FString& Key, const bool Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{Action, FLootLockerMetadataEntry::MakeBoolEntry(Key, Tags, Access, Value)};
}

void ULootLockerManager::MakeMetadataActionJson(ELootLockerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerSetMetadataAction& ConstructedEntry)
{
    TArray<TSharedPtr<FJsonValue>> JsonArrayValue;
    if(LootLockerUtilities::JsonArrayFromFString(Value, JsonArrayValue))
    {
        ConstructedEntry = FLootLockerSetMetadataAction{Action, FLootLockerMetadataEntry::MakeJsonArrayEntry(Key, Tags, Access, JsonArrayValue)};
        Succeeded = true;
        return;
    }

    TSharedPtr<FJsonObject> JsonObjectValue = LootLockerUtilities::JsonObjectFromFString(Value);
    if(JsonObjectValue.IsValid())
    {
         ConstructedEntry = FLootLockerSetMetadataAction{Action, FLootLockerMetadataEntry::MakeJsonObjectEntry(Key, Tags, Access, *JsonObjectValue)};
         Succeeded = true;
         return;
    }
    Succeeded = false;
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionBase64(ELootLockerMetadataActions Action, const FString& Key, const FLootLockerMetadataBase64Value& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{Action, FLootLockerMetadataEntry::MakeBase64Entry(Key, Tags, Access, Value)};
}

// Miscellaneous
void ULootLockerManager::GetServerTime(const FTimeResponseDelegateBP& OnCompletedRequestBP)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(OnCompletedRequestBP);
}

FString ULootLockerManager::GetLastActivePlatform() {
    return ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform();
}
