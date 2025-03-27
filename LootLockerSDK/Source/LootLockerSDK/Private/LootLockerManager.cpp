// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

#include "LootLockerPlatformManager.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"

// Player State
TArray<FString> ULootLockerManager::GetActivePlayerUlids()
{
    return ULootLockerStateData::GetActivePlayerUlids();
}

void ULootLockerManager::SetPlayerUlidToInactive(const FString& PlayerUlid)
{
    return ULootLockerStateData::SetPlayerUlidToInactive(PlayerUlid);
}

TArray<FString> ULootLockerManager::GetCachedPlayerUlids()
{
    return ULootLockerStateData::GetActivePlayerUlids();
}

FString ULootLockerManager::GetDefaultPlayerUlid()
{
    return ULootLockerStateData::GetDefaultPlayerUlid();
}

bool ULootLockerManager::SetDefaultPlayer(const FString& PlayerUlid)
{
    return ULootLockerStateData::SetDefaultPlayerUlid(PlayerUlid);
}

FLootLockerPlayerData ULootLockerManager::GetSavedStateOrDefaultOrEmptyForPlayer(const FString& PlayerUlid)
{
    return ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(PlayerUlid);
}

void ULootLockerManager::ClearCacheForPlayer(const FString& PlayerUlid)
{
    ULootLockerStateData::ClearSavedStateForPlayer(PlayerUlid);
}

void ULootLockerManager::ClearAllPlayerCaches()
{
    ULootLockerStateData::ClearAllSavedStates();
}

// Authentication
void ULootLockerManager::StartSessionManual(const FString& SessionToken, const FString& PlayerUlid,
    FLootLockerPlatformRepresentation CurrentPlatform, const FString& RefreshToken, const FString& PlayerIdentifier, const FString& PlayerPublicUid, const FString& PlayerName,
    const FString& WhiteLabelEmail, const FString& WhiteLabelToken, const FString& LastSignIn)
{
    FLootLockerPlayerData Data = FLootLockerPlayerData::Create(SessionToken, RefreshToken, PlayerIdentifier, PlayerUlid, PlayerPublicUid, PlayerName, WhiteLabelEmail, WhiteLabelToken, CurrentPlatform, LastSignIn);
    ULootLockerStateData::SavePlayerData(Data);
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

void ULootLockerManager::RefreshAppleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, OnRefreshAppleSessionCompleted);
}

void ULootLockerManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, OnStartedAppleGameCenterSessionCompleted);
}

void ULootLockerManager::RefreshAppleGameCenterSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, OnRefreshAppleGameCenterSessionCompleted);
}

void ULootLockerManager::StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, OnStartedGoogleSessionRequestCompleted);
}

void ULootLockerManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Platform, OnStartedGoogleSessionRequestCompleted);
}

void ULootLockerManager::RefreshGoogleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, OnRefreshGoogleSessionCompleted);
}

void ULootLockerManager::StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartEpicSession(IdToken, OnStartedEpicSessionRequestCompleted);
}

void ULootLockerManager::RefreshEpicSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshEpicSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, OnRefreshEpicSessionCompleted);
}

void ULootLockerManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartMetaSession(UserId, Nonce, OnMetaSessionRequestCompleted);
}

void ULootLockerManager::RefreshMetaSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshMetaSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, OnMetaSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelStartSession(const FAuthResponseBP& OnStartWhiteLabelSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(OnStartWhiteLabelSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(Email, Password, Remember, OnWhiteLabelLoginAndStartSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelVerifySession(const FString& ForPlayerWithUlid, const FLootLockerVerifySessionResponseBP& OnVerifyWhiteLabelSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnVerifyWhiteLabelSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(UserId, OnRequestWhiteLabelUserVerificationRequestCompleted);
}

void ULootLockerManager::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(Email, OnRequestWhiteLabelUserVerificationRequestCompleted);
}

void ULootLockerManager::WhiteLabelResetPassword(const FString& Email, const FLootLockerDefaultResponseBP& OnResetWhiteLabelPasswordRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(Email, OnResetWhiteLabelPasswordRequestCompleted);
}

void ULootLockerManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelLoginRequestCompleted, const bool Remember /* = false */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(Email, Password, Remember, OnWhiteLabelLoginRequestCompleted);
}

void ULootLockerManager::WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelAccountCreationRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(Email, Password, OnWhiteLabelAccountCreationRequestCompleted);
}

void ULootLockerManager::GuestLogin(const FAuthResponseBP& OnCompletedRequestBP, const FString& PlayerIdentifier)
{
    ULootLockerAuthenticationRequestHandler::GuestLogin(PlayerIdentifier, OnCompletedRequestBP);
}

void ULootLockerManager::VerifyPlayer(const FString& ForPlayerWithUlid, const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform /*= FString()*/)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlatformToken, Platform, -1, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::EndSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnEndSessionRequestCompleted);
}

//==================================================
// Connected Accounts
//==================================================
void ULootLockerManager::ListConnectedAccounts(const FString& ForPlayerWithUlid, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompleteBP);
}

void ULootLockerManager::DisconnectAccount(const FString& ForPlayerWithUlid, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AccountToDisconnect, OnCompleteBP);
}

void ULootLockerManager::ConnectGoogleAccount(const FString& ForPlayerWithUlid, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IdToken, OnCompleteBP);
}

void ULootLockerManager::ConnectGoogleAccountWithPlatform(const FString& ForPlayerWithUlid, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IdToken, Platform, OnCompleteBP);
}

void ULootLockerManager::ConnectAppleAccountByRestSignIn(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AuthorizationCode, OnCompleteBP);
}

void ULootLockerManager::ConnectRemoteSessionAccount(const FString& ForPlayerWithUlid, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Code, Nonce, OnCompleteBP);
}

//==================================================
// Remote Sessions
//==================================================
FString ULootLockerManager::StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegateBP& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
    return ULootLockerRemoteSessionRequestHandler::StartRemoteSession(ELootLockerRemoteSessionLeaseIntent::login, RemoteSessionLeaseInformation, FLootLockerLeaseRemoteSessionResponseDelegate(), RemoteSessionLeaseStatusUpdate, FLootLockerRemoteSessionStatusPollingResponseDelegate(), OnComplete, FLootLockerStartRemoteSessionResponseDelegate(), PollingIntervalSeconds, TimeOutAfterMinutes);
}

void ULootLockerManager::CancelRemoteSessionProcess(FString ProcessID)
{
    ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(ProcessID);
}

void ULootLockerManager::RefreshRemoteSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, OnCompletedRequest);
}

//==================================================
// Player
//==================================================
void ULootLockerManager::GetCurrentPlayerInfo(const FString& ForPlayerWithUlid, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

void ULootLockerManager::ListPlayerInfo(const FString& ForPlayerWithUlid, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::ListPlayerInfo(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, OnCompletedRequest);
}

void ULootLockerManager::GetInventory(const FString& ForPlayerWithUlid, const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    ULootLockerPlayerRequestHandler::GetInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetInventoryRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification(const FString& ForPlayerWithUlid, const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::GetCurrencyBalance(const FString& ForPlayerWithUlid, const FPBalanceResponseBP& OnGetCurrencyBalance)
{
    ULootLockerPlayerRequestHandler::GetCurrencyBalance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetCurrencyBalance);
}


void ULootLockerManager::InitiateDLCMigration(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnInitiateDlcMigration)
{
    ULootLockerPlayerRequestHandler::InitiateDLCMigration(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnInitiateDlcMigration);
}


void ULootLockerManager::GetDLCsMigration(const FString& ForPlayerWithUlid, const FPDlcResponseBP& OnGotDlcMigration)
{
    ULootLockerPlayerRequestHandler::GetDLCsMigration(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGotDlcMigration);
}


void ULootLockerManager::SetProfilePrivate(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPrivate)
{
    ULootLockerPlayerRequestHandler::SetProfilePrivate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnProfileSetPrivate);
}

void ULootLockerManager::SetProfilePublic(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPublic)
{
    ULootLockerPlayerRequestHandler::SetProfilePublic(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnProfileSetPublic);
}
void ULootLockerManager::SetPlayerName(const FString& ForPlayerWithUlid, FString Name, const FPNameResponseBP& OnSetPlayerName)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Name, OnSetPlayerName);
}

void ULootLockerManager::GetPlayerName(const FString& ForPlayerWithUlid, const FPNameResponseBP& OnGetPlayerName)
{
    ULootLockerPlayerRequestHandler::GetPlayerName(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetPlayerName);
}

void ULootLockerManager::LookupMultiplePlayerNamesUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

void ULootLockerManager::LookupMultiplePlayersDataUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

void ULootLockerManager::LookupMultiplePlayerNames1stPlatformIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

void ULootLockerManager::DeletePlayer(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::DeletePlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}


void ULootLockerManager::UploadFile(const FString& ForPlayerWithUlid, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::UploadFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnComplete);
}

void ULootLockerManager::UpdateFile(const FString& ForPlayerWithUlid, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::UpdateFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileId, Request, OnComplete);
}

void ULootLockerManager::ListFiles(const FString& ForPlayerWithUlid, const FLootLockerFileListBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::ListFiles(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete, FLootLockerFileListDelegate());
}

void ULootLockerManager::ListOtherPlayersPublicFiles(const FString& ForPlayerWithUlid, const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP)
{
    ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerID, OnCompleteBP);
}

void ULootLockerManager::GetSingleFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::GetSingleFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileID, OnComplete);
}

void ULootLockerManager::DeletePlayerFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerFileDeletedBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::DeletePlayerFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileID, OnComplete);
}

// Player Progressions
void ULootLockerManager::GetPlayerProgressions(const FString& ForPlayerWithUlid, const int32 Count /*= -1*/, const FString& After /*= ""*/, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeletePlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeletePlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::GetOtherPlayersProgressions(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerUlid, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetOtherPlayersProgression(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerUlid, ProgressionKey, OnCompletedRequest);
}

// Heroes
void ULootLockerManager::GetGameHeroes(const FString& ForPlayerWithUlid, const FLootLockerGameHeroListBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetGameHeroes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompleteBP, FLootLockerGameHeroListDelegate());
}

void ULootLockerManager::ListPlayerHeroes(const FString& ForPlayerWithUlid, const FLootLockerHeroListBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::ListPlayerHeroes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::ListOtherPlayersHeroesBySteamID64(const FString& ForPlayerWithUlid, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamID64, OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::CreateHero(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::CreateHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::CreateHeroWithVariation(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::CreateHeroWithVariation(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::GetHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::GetOtherPlayersDefaultHeroBySteamID64(const FString& ForPlayerWithUlid, const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamID64, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::UpdateHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::UpdateHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::DeleteHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::DeleteHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompleteBP, FLLHeroDefaultResponseDelegate());
}

void ULootLockerManager::GetHeroInventory(const FString& ForPlayerWithUlid, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetHeroInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompleteBP, FInventoryResponse());
}

void ULootLockerManager::GetHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetOtherPlayersHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetInstanceID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddGlobalAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddGlobalAssetVariationToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetID, AssetVariationID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::RemoveAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetInstanceID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetCharacterLoadout(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::UpdateCharacter(const FString& ForPlayerWithUlid, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, IsDefault, Name, OnCompletedRequest);
}

void ULootLockerManager::CreateCharacter(const FString& ForPlayerWithUlid, bool IsDefault, FString CharacterName, FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IsDefault, CharacterName, CharacterTypeId, OnCompletedRequestBP);
}

void ULootLockerManager::ListCharacterTypes(const FString& ForPlayerWithUlid, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::ListCharacterTypes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequestBP);
}

void ULootLockerManager::ListPlayerCharacters(const FString& ForPlayerWithUlid, const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::ListPlayerCharacters(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequestBP);
}

void ULootLockerManager::EquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, AssetId, AssetVariationId, OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterByIdAndInstance(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, InstanceId, OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, InstanceId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerId, OtherPlayerPlatform, OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId(const FString& ForPlayerWithUlid, int OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherCharacterId, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

// Character Progressions
void ULootLockerManager::GetCharacterProgressions(const FString& ForPlayerWithUlid, const int32& CharacterId, const int32 Count /*=-1*/, const FString& After /*=""*/, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeleteCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, OnCompletedRequest);
}

// Persistent Storage
void ULootLockerManager::GetEntirePersistentStorage(const FString& ForPlayerWithUlid, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerManager::AddItemsToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Items, OnPersistentStorageItemsAddRequestCompleted);
}

void ULootLockerManager::AddItemToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Item, OnPersistentStorageItemAddRequestCompleted);
}

void ULootLockerManager::DeleteItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, OnPersistentStorageItemDeleteRequestCompleted);
}

void ULootLockerManager::GetPlayerPersistentStorage(const FString& ForPlayerWithUlid, const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerId, OnGetPlayerPersistentStorageRequestCompleted);
}

void ULootLockerManager::GetContexts(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetContextsRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetContexts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetContextsRequestCompleted);
}

void ULootLockerManager::GetAssets(const FString& ForPlayerWithUlid, const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    ULootLockerAssetsRequestHandler::GetAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, OnGetAssetsRequestCompleted);
}

void ULootLockerManager::GetAssetsByIds(const FString& ForPlayerWithUlid, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetAssetsByIds(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetIds, OnGetAssetsByIdsRequestCompleted);
}

void ULootLockerManager::GetAssetBones(const FString& ForPlayerWithUlid, const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetAssetBones(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetAssetBonesRequestCompleted);
}

void ULootLockerManager::GetFavouriteAssetIndices(const FString& ForPlayerWithUlid, const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetFavouriteAssetIndicesRequestCompleted);
}

void ULootLockerManager::AddAssetToFavourites(const FString& ForPlayerWithUlid, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::AddAssetToFavourites(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetId, OnAddAssetToFavouritesRequestCompleted);
}

void ULootLockerManager::RemoveAssetFromFavourites(const FString& ForPlayerWithUlid, int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetId, OnRemoveAssetFromFavouritesRequestCompleted);
}

void ULootLockerManager::GetUniversalAssets(const FString& ForPlayerWithUlid, int After, int ItemsCount, const FUniversalAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetUniversalAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), After, ItemsCount, OnCompletedRequest);
}

void ULootLockerManager::GrantAssetWithVariationToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetID, AssetVariationID, AssetRentalOptionID, OnCompletedRequest);
}

void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnGetAllKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, OnGetAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::CreateAKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Item, OnCreateAKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Items, OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, Item, OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::InspectLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted)
{
    ULootLockerAssetInstancesRequestHandler::InspectLootBox(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnInspectLootBoxCompleted);
}

void ULootLockerManager::OpenLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted)
{
    ULootLockerAssetInstancesRequestHandler::OpenLootBox(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnOpenLootBoxCompleted);
}

void ULootLockerManager::DeleteAssetInstanceFromPlayerInventory(const FString& ForPlayerWithUlid, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceID, OnCompleted);
}

void ULootLockerManager::CreateAssetCandidate(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateData, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::CreateAssetCandidateAndMarkComplete(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateData, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::UpdateAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, AssetCandidateData, OnUpdateAssetCandidateCompleted);
}

void ULootLockerManager::DeleteAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, OnDeleteAssetCandidateCompleted);
}

void ULootLockerManager::GetAllAssetCandidates(const FString& ForPlayerWithUlid, const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetAllAssetCandidatesCompleted);
}

void ULootLockerManager::GetAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, OnGetAssetCandidateCompleted);
}

void ULootLockerManager::AddFileToAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted);
}

void ULootLockerManager::DeleteFileFromAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted);
}

// Progressions
void ULootLockerManager::GetProgressions(const FString& ForPlayerWithUlid, const int32 Count /*= -1*/, const FString& After /*=""*/, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::GetProgressionTiers(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32 Count /*=-1*/, const int32 After /*=-1*/, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgressionTiers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Count, After, OnCompletedRequest);
}

//Instance progression

void ULootLockerManager::GetInstanceProgressions(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeleteInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

// Missions
void ULootLockerManager::GetAllMissions(const FString& ForPlayerWithUlid, const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted)
{
    ULootLockerMissionsRequestHandler::GetAllMissions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetAllMissionsCompleted);
}

void ULootLockerManager::GetMission(const FString& ForPlayerWithUlid, int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted)
{
    ULootLockerMissionsRequestHandler::GetMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, OnGetMissionCompleted);
}

void ULootLockerManager::StartMission(const FString& ForPlayerWithUlid, int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted)
{
    ULootLockerMissionsRequestHandler::StartMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, OnStartMissionCompleted);
}

void ULootLockerManager::FinishMission(const FString& ForPlayerWithUlid, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted)
{
    ULootLockerMissionsRequestHandler::FinishMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, MissionData, OnFinishMissionCompleted);
}

void ULootLockerManager::GetMaps(const FString& ForPlayerWithUlid, const FGetMapsResponseDelegateBP& OnGetMapsCompleted)
{
    ULootLockerMapsRequestHandler::GetMaps(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetMapsCompleted);
}

void ULootLockerManager::ActivateRentalAsset(const FString& ForPlayerWithUlid, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnActivateRentalAssetCompleted);
}

void ULootLockerManager::LootLockerPurchaseSingleCatalogItem(const FString& ForPlayerWithUlid, const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    LootLockerPurchaseCatalogItems(ForPlayerWithUlid, WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest);
}

void ULootLockerManager::LootLockerPurchaseCatalogItems(const FString& ForPlayerWithUlid, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletId, ItemsToPurchase, OnCompletedRequest);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, Sandboxed, OnCompletedRequest);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, TransactionId, Sandboxed, OnCompletedRequest);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProductId, PurchaseToken, OnCompletedRequest);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, ProductId, PurchaseToken, OnCompletedRequest);
}

void ULootLockerManager::BeginSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

void ULootLockerManager::BeginSteamPurchaseRedemptionForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

void ULootLockerManager::QuerySteamPurchaseRedemptionStatus(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementId, OnCompletedRequest);
}

void ULootLockerManager::FinalizeSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementId, OnCompletedRequest);
}

//Triggers
void ULootLockerManager::InvokeTriggersByKey(const FString& ForPlayerWithUlid, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnComplete)
{
    ULootLockerTriggersRequestHandler::InvokeTriggersByKey(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), KeysToInvoke, OnComplete);
}

//Notifications
void ULootLockerManager::ListNotificationsWithDefaultParameters(const FString& ForPlayerWithUlid, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

void ULootLockerManager::ListNotifications(const FString& ForPlayerWithUlid, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ShowRead, OfType, WithSource, PerPage, Page, OnComplete);
}

void ULootLockerManager::ListNotificationsWithPriority(const FString& ForPlayerWithUlid, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WithPriority, ShowRead, OfType, WithSource, PerPage, Page, OnComplete);
}

void ULootLockerManager::MarkAllNotificationsAsRead(const FString& ForPlayerWithUlid, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

void ULootLockerManager::MarkNotificationsAsRead(const FString& ForPlayerWithUlid, const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    TArray<FString> UnreadNotificationIds;
    for (const FLootLockerNotification& Notification : Notifications)
    {
        if (!Notification.Read)
        {
            UnreadNotificationIds.Add(Notification.Id);
        }
    }
    MarkNotificationsAsReadByIds(ForPlayerWithUlid, UnreadNotificationIds, OnComplete);
}

void ULootLockerManager::MarkNotificationsAsReadByIds(const FString& ForPlayerWithUlid, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), NotificationIDs, OnComplete);
}

bool ULootLockerManager::TryGetNotificationsByIdentifyingValue(const FLootLockerListNotificationsResponse& NotificationsResponse, const FString& IdentifyingValue, TArray<FLootLockerNotification>& Notifications)
{
    return NotificationsResponse.TryGetNotificationsByIdentifyingValue(IdentifyingValue, Notifications);
}

void ULootLockerManager::GetAllCollectables(const FString& ForPlayerWithUlid, const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted)
{
    ULootLockerCollectablesRequestHandler::GetAllCollectables(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetAllCollectablesCompleted);
}

void ULootLockerManager::CollectItem(const FString& ForPlayerWithUlid, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted)
{
    ULootLockerCollectablesRequestHandler::CollectItem(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Item, OnCollectItemCompleted);
}

void ULootLockerManager::GetMessages(const FString& ForPlayerWithUlid, const FMessagesResponseDelegateBP& OnGetMessagesCompleted)
{
    ULootLockerMessagesRequestHandler::GetMessages(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnGetMessagesCompleted);
}

void ULootLockerManager::ListLeaderboards(const FString& ForPlayerWithUlid, int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardRequestHandler::ListLeaderboards(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnCompletedRequestBP);
}

void ULootLockerManager::GetMemberRank(const FString& ForPlayerWithUlid, FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboard_key = LeaderboardKey;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MemberRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetAllMemberRanks(const FString& ForPlayerWithUlid, FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetAllMemberRanksRequest MemberRanksRequest;
    MemberRanksRequest.after = After;
    MemberRanksRequest.count = Count;

    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MemberRanksRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetByListOfMembers(const FString& ForPlayerWithUlid, TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetByListMembersRequest, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreList(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboard_key = LeaderboardKey;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetScoreListRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreListInitial(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    GetScoreList(ForPlayerWithUlid, LeaderboardKey, Count, -1, OnCompletedRequestBP);
}


void ULootLockerManager::SubmitScore(const FString& ForPlayerWithUlid, FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SubmitScoreRequest, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::ListLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::GetLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, Count, After, OnCompletedRequestBP);
}

void ULootLockerManager::GetLeaderboardDetails(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::ComputeAndLockDropTable(const FString& ForPlayerWithUlid, int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
{
    ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TableId, OnCompletedRequestBP);
}

void ULootLockerManager::PickDropsFromDropTable(const FString& ForPlayerWithUlid, TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
{
    FLootLockerPickDropsFromDropTableRequest request;
    request.picks = Picks;
    ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), request, TableId, OnCompletedRequestBP);
}

// Currencies
void ULootLockerManager::ListCurrencies(const FString& ForPlayerWithUlid, const FLootLockerListCurrenciesResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::ListCurrencies(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

void ULootLockerManager::GetCurrencyDetails(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDetails(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CurrencyCode, OnCompletedRequest);
}

void ULootLockerManager::GetCurrencyDenominationsByCode(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CurrencyCode, OnCompletedRequest);
}

// Balances

void ULootLockerManager::ListBalancesInWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::ListBalancesInWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, OnComplete);
}

void ULootLockerManager::GetWalletByWalletID(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByWalletID(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, OnComplete);
}

void ULootLockerManager::GetWalletByHolderID(const FString& ForPlayerWithUlid, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByHolderID(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HolderULID, HolderType, OnComplete);
}

void ULootLockerManager::CreditBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::CreditBalanceToWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, CurrencyID, Amount, OnComplete);
}

void ULootLockerManager::DebitBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::DebitBalanceToWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, CurrencyID, Amount, OnComplete);
}

// Catalogs

void ULootLockerManager::ListCatalogs(const FString& ForPlayerWithUlid, const FLootLockerListCatalogsResponseBP& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

void ULootLockerManager::ListCatalogItems(const FString& ForPlayerWithUlid, const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogItems(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CatalogKey, Count, After, OnComplete);
}

TArray<FLootLockerInlinedCatalogEntry> ULootLockerManager::ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog)
{
    return ULootLockerCatalogRequestHandler::ConvertCatalogToInlineItems(Catalog);
}

// Entitlements
void ULootLockerManager::ListEntitlements(const FString& ForPlayerWithUlid, int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnComplete)
{
    ULootLockerEntitlementRequestHandler::ListEntitlements(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnComplete);
}

void ULootLockerManager::GetEntitlement(const FString& ForPlayerWithUlid, const FString& EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnComplete)
{
    ULootLockerEntitlementRequestHandler::GetEntitlement(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementID, OnComplete);
}

void ULootLockerManager::ListPlayerFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Player, OnComplete);
}

void ULootLockerManager::ListGameFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Game, OnComplete);
}

void ULootLockerManager::ListUGCFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Ugc, OnComplete);
}

void ULootLockerManager::SendPlayerFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Ulid, Description, CategoryID, ELootLockerFeedbackType::Player, OnComplete);
}

void ULootLockerManager::SendGameFeedback(const FString& ForPlayerWithUlid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), "", Description, CategoryID, ELootLockerFeedbackType::Game, OnComplete);
}

void ULootLockerManager::SendUGCFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Ulid, Description, CategoryID, ELootLockerFeedbackType::Ugc, OnComplete);

}

// Metadata

void ULootLockerManager::ListMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

void ULootLockerManager::ListMetadataWithTags(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, OnComplete);
}

void ULootLockerManager::GetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::GetMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Key, IgnoreFiles, OnComplete);
}

void ULootLockerManager::GetMultisourceMetadata(const FString& ForPlayerWithUlid, const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::GetMultisourceMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SourcesAndKeysToGet, IgnoreFiles, OnComplete);
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
    if (!Entry.TryGetSerializedValue(ValueToParse))
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

void ULootLockerManager::SetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::SetMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, MetadataToActionsToPerform, OnComplete);
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
    return FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeIntegerEntry(Key, Tags, Access, Value) };
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionBool(ELootLockerMetadataActions Action, const FString& Key, const bool Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeBoolEntry(Key, Tags, Access, Value) };
}

void ULootLockerManager::MakeMetadataActionJson(ELootLockerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerSetMetadataAction& ConstructedEntry)
{
    TArray<TSharedPtr<FJsonValue>> JsonArrayValue;
    if (LootLockerUtilities::JsonArrayFromFString(Value, JsonArrayValue))
    {
        ConstructedEntry = FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeJsonArrayEntry(Key, Tags, Access, JsonArrayValue) };
        Succeeded = true;
        return;
    }

    TSharedPtr<FJsonObject> JsonObjectValue = LootLockerUtilities::JsonObjectFromFString(Value);
    if (JsonObjectValue.IsValid())
    {
        ConstructedEntry = FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeJsonObjectEntry(Key, Tags, Access, *JsonObjectValue) };
        Succeeded = true;
        return;
    }
    Succeeded = false;
}

FLootLockerSetMetadataAction ULootLockerManager::MakeMetadataActionBase64(ELootLockerMetadataActions Action, const FString& Key, const FLootLockerMetadataBase64Value& Value, const TArray<FString>& Tags, const TArray<FString>& Access)
{
    return FLootLockerSetMetadataAction{ Action, FLootLockerMetadataEntry::MakeBase64Entry(Key, Tags, Access, Value) };
}

// Miscellaneous
void ULootLockerManager::GetServerTime(const FString& ForPlayerWithUlid, const FTimeResponseDelegateBP& OnCompletedRequestBP)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequestBP);
}

FString ULootLockerManager::GetLastActivePlatform(const FString& ForPlayerWithUlid) {
    return ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid));
}
