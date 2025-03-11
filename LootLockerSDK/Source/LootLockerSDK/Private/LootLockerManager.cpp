// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

#include "LootLockerPlatformManager.h"
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

void ULootLockerManager::RefreshAppleSession(const FLootLockerPlayerData& ForPlayer, const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleSession(RefreshToken.IsEmpty() ? ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("").RefreshToken : ForPlayer.RefreshToken : RefreshToken, OnRefreshAppleSessionCompleted);
}

void ULootLockerManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, OnStartedAppleGameCenterSessionCompleted);
}

void ULootLockerManager::RefreshAppleGameCenterSession(const FLootLockerPlayerData& ForPlayer, const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(RefreshToken.IsEmpty() ? ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("").RefreshToken : ForPlayer.RefreshToken : RefreshToken, OnRefreshAppleGameCenterSessionCompleted);
}

void ULootLockerManager::StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, OnStartedGoogleSessionRequestCompleted);
}

void ULootLockerManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Platform, OnStartedGoogleSessionRequestCompleted);
}

void ULootLockerManager::RefreshGoogleSession(const FLootLockerPlayerData& ForPlayer, const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(RefreshToken.IsEmpty() ? ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("").RefreshToken : ForPlayer.RefreshToken : RefreshToken, OnRefreshGoogleSessionCompleted);
}

void ULootLockerManager::StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartEpicSession(IdToken, OnStartedEpicSessionRequestCompleted);
}

void ULootLockerManager::RefreshEpicSession(const FLootLockerPlayerData& ForPlayer, const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshEpicSession(RefreshToken.IsEmpty() ? ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("").RefreshToken : ForPlayer.RefreshToken : RefreshToken, OnRefreshEpicSessionCompleted);
}

void ULootLockerManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartMetaSession(UserId, Nonce, OnMetaSessionRequestCompleted);
}

void ULootLockerManager::RefreshMetaSession(const FLootLockerPlayerData& ForPlayer, const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshMetaSession(RefreshToken.IsEmpty() ? ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("").RefreshToken : ForPlayer.RefreshToken : RefreshToken, OnMetaSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelStartSession(const FAuthResponseBP& OnStartWhiteLabelSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(OnStartWhiteLabelSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(Email, Password, Remember, OnWhiteLabelLoginAndStartSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelVerifySession(const FLootLockerPlayerData& ForPlayer, const FLootLockerVerifySessionResponseBP& OnVerifyWhiteLabelSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnVerifyWhiteLabelSessionRequestCompleted);
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

void ULootLockerManager::VerifyPlayer(const FLootLockerPlayerData& ForPlayer, const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform /*= FString()*/)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, PlatformToken, Platform, -1, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const FLootLockerPlayerData& ForPlayer, const FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::EndSession(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnEndSessionRequestCompleted);
}

//==================================================
// Connected Accounts
//==================================================
void ULootLockerManager::ListConnectedAccounts(const FLootLockerPlayerData& ForPlayer, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompleteBP);
}

void ULootLockerManager::DisconnectAccount(const FLootLockerPlayerData& ForPlayer, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AccountToDisconnect, OnCompleteBP);
}

void ULootLockerManager::ConnectGoogleAccount(const FLootLockerPlayerData& ForPlayer, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, IdToken, OnCompleteBP);
}

void ULootLockerManager::ConnectGoogleAccountWithPlatform(const FLootLockerPlayerData& ForPlayer, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, IdToken, Platform, OnCompleteBP);
}

void ULootLockerManager::ConnectAppleAccountByRestSignIn(const FLootLockerPlayerData& ForPlayer, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AuthorizationCode, OnCompleteBP);
}

//==================================================
// Remote Sessions
//==================================================
FString ULootLockerManager::StartRemoteSession(const FLootLockerPlayerData& ForPlayer, const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegateBP& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
    return ULootLockerRemoteSessionRequestHandler::StartRemoteSession(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, RemoteSessionLeaseInformation, FLootLockerLeaseRemoteSessionResponseDelegate(), RemoteSessionLeaseStatusUpdate, FLootLockerRemoteSessionStatusPollingResponseDelegate(), OnComplete, FLootLockerStartRemoteSessionResponseDelegate(), PollingIntervalSeconds, TimeOutAfterMinutes);
}

void ULootLockerManager::CancelRemoteSessionProcess(const FLootLockerPlayerData& ForPlayer, FString ProcessID)
{
    ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(ProcessID);
}

void ULootLockerManager::RefreshRemoteSession(const FLootLockerPlayerData& ForPlayer, const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(RefreshToken.IsEmpty() ? ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("").RefreshToken : ForPlayer.RefreshToken : RefreshToken, OnCompletedRequest);
}

//==================================================
// Player
//==================================================
void ULootLockerManager::GetCurrentPlayerInfo(const FLootLockerPlayerData& ForPlayer, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompletedRequest);
}

void ULootLockerManager::ListPlayerInfo(const FLootLockerPlayerData& ForPlayer, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::ListPlayerInfo(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, OnCompletedRequest);
}

void ULootLockerManager::GetInventory(const FLootLockerPlayerData& ForPlayer, const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    ULootLockerPlayerRequestHandler::GetInventory(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetInventoryRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification(const FLootLockerPlayerData& ForPlayer, const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::GetCurrencyBalance(const FLootLockerPlayerData& ForPlayer, const FPBalanceResponseBP& OnGetCurrencyBalance)
{
    ULootLockerPlayerRequestHandler::GetCurrencyBalance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetCurrencyBalance);
}


void ULootLockerManager::InitiateDLCMigration(const FLootLockerPlayerData& ForPlayer, const FResponseCallbackBP& OnInitiateDlcMigration)
{
    ULootLockerPlayerRequestHandler::InitiateDLCMigration(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnInitiateDlcMigration);
}


void ULootLockerManager::GetDLCsMigration(const FLootLockerPlayerData& ForPlayer, const FPDlcResponseBP& OnGotDlcMigration)
{
    ULootLockerPlayerRequestHandler::GetDLCsMigration(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGotDlcMigration);
}


void ULootLockerManager::SetProfilePrivate(const FLootLockerPlayerData& ForPlayer, const FResponseCallbackBP& OnProfileSetPrivate)
{
    ULootLockerPlayerRequestHandler::SetProfilePrivate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnProfileSetPrivate);
}

void ULootLockerManager::SetProfilePublic(const FLootLockerPlayerData& ForPlayer, const FResponseCallbackBP& OnProfileSetPublic)
{
    ULootLockerPlayerRequestHandler::SetProfilePublic(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnProfileSetPublic);
}
void ULootLockerManager::SetPlayerName(const FLootLockerPlayerData& ForPlayer, FString Name, const FPNameResponseBP& OnSetPlayerName)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Name, OnSetPlayerName);
}

void ULootLockerManager::GetPlayerName(const FLootLockerPlayerData& ForPlayer, const FPNameResponseBP& OnGetPlayerName)
{
    ULootLockerPlayerRequestHandler::GetPlayerName(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetPlayerName);
}

void ULootLockerManager::LookupMultiplePlayerNamesUsingIDs(const FLootLockerPlayerData& ForPlayer, const FLootLockerMultiplePlayerNamesRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnCompletedRequest);
}

void ULootLockerManager::LookupMultiplePlayersDataUsingIDs(const FLootLockerPlayerData& ForPlayer, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnCompletedRequest);
}

void ULootLockerManager::LookupMultiplePlayersDataUsingIDs(const FLootLockerPlayerData& ForPlayer, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnCompletedRequest);
}

void ULootLockerManager::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerPlayerData& ForPlayer, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnCompletedRequest);
}

void ULootLockerManager::DeletePlayer(const FLootLockerPlayerData& ForPlayer, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::DeletePlayer(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompletedRequest);
}


void ULootLockerManager::UploadFile(const FLootLockerPlayerData& ForPlayer, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::UploadFile(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnComplete);
}

void ULootLockerManager::UpdateFile(const FLootLockerPlayerData& ForPlayer, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::UpdateFile(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, FileId, Request, OnComplete);
}

void ULootLockerManager::ListFiles(const FLootLockerPlayerData& ForPlayer, const FLootLockerFileListBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::ListFiles(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnComplete, FLootLockerFileListDelegate());
}

void ULootLockerManager::ListOtherPlayersPublicFiles(const FLootLockerPlayerData& ForPlayer, const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP)
{
    ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, PlayerID, OnCompleteBP);
}

void ULootLockerManager::GetSingleFile(const FLootLockerPlayerData& ForPlayer, const int32 FileID, const FLootLockerUploadFileBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::GetSingleFile(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, FileID, OnComplete);
}

void ULootLockerManager::DeletePlayerFile(const FLootLockerPlayerData& ForPlayer, const int32 FileID, const FLootLockerFileDeletedBP& OnComplete)
{
    ULLPlayerFilesRequestHandler::DeletePlayerFile(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, FileID, OnComplete);
}

// Player Progressions
void ULootLockerManager::GetPlayerProgressions(const FLootLockerPlayerData& ForPlayer, const int32 Count /*= -1*/, const FString& After /*= ""*/, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgressions(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetPlayerProgression(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToPlayerProgression(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromPlayerProgression(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetPlayerProgression(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetPlayerProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeletePlayerProgression(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeletePlayerProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::GetOtherPlayersProgressions(const FLootLockerPlayerData& ForPlayer, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgressions(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, PlayerUlid, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetOtherPlayersProgression(const FLootLockerPlayerData& ForPlayer, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, PlayerUlid, ProgressionKey, OnCompletedRequest);
}

// Heroes
void ULootLockerManager::GetGameHeroes(const FLootLockerPlayerData& ForPlayer, const FLootLockerGameHeroListBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetGameHeroes(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompleteBP, FLootLockerGameHeroListDelegate());
}

void ULootLockerManager::ListPlayerHeroes(const FLootLockerPlayerData& ForPlayer, const FLootLockerHeroListBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::ListPlayerHeroes(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::ListOtherPlayersHeroesBySteamID64(const FLootLockerPlayerData& ForPlayer, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, SteamID64, OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::CreateHero(const FLootLockerPlayerData& ForPlayer, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::CreateHero(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::CreateHeroWithVariation(const FLootLockerPlayerData& ForPlayer, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::CreateHeroWithVariation(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::GetHero(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetHero(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::GetOtherPlayersDefaultHeroBySteamID64(const FLootLockerPlayerData& ForPlayer, const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, SteamID64, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::UpdateHero(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::UpdateHero(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
}

void ULootLockerManager::DeleteHero(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::DeleteHero(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, OnCompleteBP, FLLHeroDefaultResponseDelegate());
}

void ULootLockerManager::GetHeroInventory(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetHeroInventory(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, OnCompleteBP, FInventoryResponse());
}

void ULootLockerManager::GetHeroLoadout(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetHeroLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetOtherPlayersHeroLoadout(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddAssetToHeroLoadout(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, AssetInstanceID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddGlobalAssetToHeroLoadout(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, AssetID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::AddGlobalAssetVariationToHeroLoadout(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, AssetID, AssetVariationID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::RemoveAssetToHeroLoadout(const FLootLockerPlayerData& ForPlayer, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HeroID, AssetInstanceID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetCharacterLoadout(const FLootLockerPlayerData& ForPlayer, const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::UpdateCharacter(const FLootLockerPlayerData& ForPlayer, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, IsDefault, Name, OnCompletedRequest);
}

void ULootLockerManager::CreateCharacter(const FLootLockerPlayerData& ForPlayer, bool IsDefault, FString CharacterName, FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, IsDefault, CharacterName, CharacterTypeId, OnCompletedRequestBP);
}

void ULootLockerManager::ListCharacterTypes(const FLootLockerPlayerData& ForPlayer, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::ListCharacterTypes(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompletedRequestBP);
}

void ULootLockerManager::ListPlayerCharacters(const FLootLockerPlayerData& ForPlayer, const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP)
{
    ULootLockerCharacterRequestHandler::ListPlayerCharacters(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompletedRequestBP);
}

void ULootLockerManager::EquipAssetToDefaultCharacter(const FLootLockerPlayerData& ForPlayer, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterById(const FLootLockerPlayerData& ForPlayer, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, AssetId, AssetVariationId, OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterByIdAndInstance(const FLootLockerPlayerData& ForPlayer, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, InstanceId, OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(const FLootLockerPlayerData& ForPlayer, int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToCharacterById(const FLootLockerPlayerData& ForPlayer, int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, InstanceId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& ForPlayer, const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerPlayerData& ForPlayer, FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OtherPlayerId, OtherPlayerPlatform, OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FLootLockerPlayerData& ForPlayer, const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId(const FLootLockerPlayerData& ForPlayer, int OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OtherCharacterId, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

// Character Progressions
void ULootLockerManager::GetCharacterProgressions(const FLootLockerPlayerData& ForPlayer, const int32& CharacterId, const int32 Count /*=-1*/, const FString& After /*=""*/, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgressions(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetCharacterProgression(const FLootLockerPlayerData& ForPlayer, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToCharacterProgression(const FLootLockerPlayerData& ForPlayer, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromCharacterProgression(const FLootLockerPlayerData& ForPlayer, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetCharacterProgression(const FLootLockerPlayerData& ForPlayer, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetCharacterProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeleteCharacterProgression(const FLootLockerPlayerData& ForPlayer, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CharacterId, ProgressionKey, OnCompletedRequest);
}

// Persistent Storage
void ULootLockerManager::GetEntirePersistentStorage(const FLootLockerPlayerData& ForPlayer, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FLootLockerPlayerData& ForPlayer, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerManager::AddItemsToPersistentStorage(const FLootLockerPlayerData& ForPlayer, FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Items, OnPersistentStorageItemsAddRequestCompleted);
}

void ULootLockerManager::AddItemToPersistentStorage(const FLootLockerPlayerData& ForPlayer, FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Item, OnPersistentStorageItemAddRequestCompleted);
}

void ULootLockerManager::DeleteItemFromPersistentStorage(const FLootLockerPlayerData& ForPlayer, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Key, OnPersistentStorageItemDeleteRequestCompleted);
}

void ULootLockerManager::GetPlayerPersistentStorage(const FLootLockerPlayerData& ForPlayer, const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, PlayerId, OnGetPlayerPersistentStorageRequestCompleted);
}

void ULootLockerManager::GetContexts(const FLootLockerPlayerData& ForPlayer, const FContextDelegateBP& OnGetContextsRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetContexts(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetContextsRequestCompleted);
}

void ULootLockerManager::GetAssets(const FLootLockerPlayerData& ForPlayer, const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    ULootLockerAssetsRequestHandler::GetAssets(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, OnGetAssetsRequestCompleted);
}

void ULootLockerManager::GetAssetsByIds(const FLootLockerPlayerData& ForPlayer, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetAssetsByIds(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetIds, OnGetAssetsByIdsRequestCompleted);
}

void ULootLockerManager::GetAssetBones(const FLootLockerPlayerData& ForPlayer, const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetAssetBones(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetAssetBonesRequestCompleted);
}

void ULootLockerManager::GetFavouriteAssetIndices(const FLootLockerPlayerData& ForPlayer, const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetFavouriteAssetIndicesRequestCompleted);
}

void ULootLockerManager::AddAssetToFavourites(const FLootLockerPlayerData& ForPlayer, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::AddAssetToFavourites(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetId, OnAddAssetToFavouritesRequestCompleted);
}

void ULootLockerManager::RemoveAssetFromFavourites(const FLootLockerPlayerData& ForPlayer, int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted)
{
    ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetId, OnRemoveAssetFromFavouritesRequestCompleted);
}

void ULootLockerManager::GetUniversalAssets(const FLootLockerPlayerData& ForPlayer, int After, int ItemsCount, const FUniversalAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetUniversalAssets(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, After, ItemsCount, OnCompletedRequest);
}

void ULootLockerManager::GrantAssetWithVariationToPlayerInventory(const FLootLockerPlayerData& ForPlayer, const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetID, AssetVariationID, AssetRentalOptionID, OnCompletedRequest);
}

void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, OnGetAllKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, StorageItemId, OnGetAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::CreateAKeyValuePairForAssetInstance(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, Item, OnCreateAKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, Items, OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, StorageItemId, Item, OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, StorageItemId, OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::InspectLootBox(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted)
{
    ULootLockerAssetInstancesRequestHandler::InspectLootBox(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, OnInspectLootBoxCompleted);
}

void ULootLockerManager::OpenLootBox(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, const  FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted)
{
    ULootLockerAssetInstancesRequestHandler::OpenLootBox(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, OnOpenLootBoxCompleted);
}

void ULootLockerManager::DeleteAssetInstanceFromPlayerInventory(const FLootLockerPlayerData& ForPlayer, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceID, OnCompleted);
}

void ULootLockerManager::CreateAssetCandidate(const FLootLockerPlayerData& ForPlayer, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateData, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::CreateAssetCandidateAndMarkComplete(const FLootLockerPlayerData& ForPlayer, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateData, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::UpdateAssetCandidate(const FLootLockerPlayerData& ForPlayer, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateId, AssetCandidateData, OnUpdateAssetCandidateCompleted);
}

void ULootLockerManager::DeleteAssetCandidate(const FLootLockerPlayerData& ForPlayer, int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateId, OnDeleteAssetCandidateCompleted);
}

void ULootLockerManager::GetAllAssetCandidates(const FLootLockerPlayerData& ForPlayer, const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetAllAssetCandidatesCompleted);
}

void ULootLockerManager::GetAssetCandidate(const FLootLockerPlayerData& ForPlayer, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateId, OnGetAssetCandidateCompleted);
}

void ULootLockerManager::AddFileToAssetCandidate(const FLootLockerPlayerData& ForPlayer, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted);
}

void ULootLockerManager::DeleteFileFromAssetCandidate(const FLootLockerPlayerData& ForPlayer, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted);
}

// Progressions
void ULootLockerManager::GetProgressions(const FLootLockerPlayerData& ForPlayer, const int32 Count /*= -1*/, const FString& After /*=""*/, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgressions(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetProgression(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::GetProgressionTiers(const FLootLockerPlayerData& ForPlayer, const FString& ProgressionKey, const int32 Count /*=-1*/, const int32 After /*=-1*/, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetProgressionTiers(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProgressionKey, Count, After, OnCompletedRequest);
}

//Instance progression

void ULootLockerManager::GetInstanceProgressions(const FLootLockerPlayerData& ForPlayer, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, Count, After, OnCompletedRequest);
}

void ULootLockerManager::GetInstanceProgression(const FLootLockerPlayerData& ForPlayer, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::AddPointsToInstanceProgression(const FLootLockerPlayerData& ForPlayer, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::SubtractPointsFromInstanceProgression(const FLootLockerPlayerData& ForPlayer, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, ProgressionKey, Amount, OnCompletedRequest);
}

void ULootLockerManager::ResetInstanceProgression(const FLootLockerPlayerData& ForPlayer, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::ResetInstanceProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

void ULootLockerManager::DeleteInstanceProgression(const FLootLockerPlayerData& ForPlayer, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, ProgressionKey, OnCompletedRequest);
}

// Missions
void ULootLockerManager::GetAllMissions(const FLootLockerPlayerData& ForPlayer, const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted)
{
    ULootLockerMissionsRequestHandler::GetAllMissions(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetAllMissionsCompleted);
}

void ULootLockerManager::GetMission(const FLootLockerPlayerData& ForPlayer, int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted)
{
    ULootLockerMissionsRequestHandler::GetMission(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, MissionId, OnGetMissionCompleted);
}

void ULootLockerManager::StartMission(const FLootLockerPlayerData& ForPlayer, int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted)
{
    ULootLockerMissionsRequestHandler::StartMission(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, MissionId, OnStartMissionCompleted);
}

void ULootLockerManager::FinishMission(const FLootLockerPlayerData& ForPlayer, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted)
{
    ULootLockerMissionsRequestHandler::FinishMission(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, MissionId, MissionData, OnFinishMissionCompleted);
}

void ULootLockerManager::GetMaps(const FLootLockerPlayerData& ForPlayer, const FGetMapsResponseDelegateBP& OnGetMapsCompleted)
{
    ULootLockerMapsRequestHandler::GetMaps(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetMapsCompleted);
}

void ULootLockerManager::ActivateRentalAsset(const FLootLockerPlayerData& ForPlayer, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, AssetInstanceId, OnActivateRentalAssetCompleted);
}

void ULootLockerManager::LootLockerPurchaseSingleCatalogItem(const FLootLockerPlayerData& ForPlayer, const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    LootLockerPurchaseCatalogItems(ForPlayer, WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest);
}

void ULootLockerManager::LootLockerPurchaseCatalogItems(const FLootLockerPlayerData& ForPlayer, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, WalletId, ItemsToPurchase, OnCompletedRequest);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForPlayer(const FLootLockerPlayerData& ForPlayer, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, TransactionId, Sandboxed, OnCompletedRequest);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForClass(const FLootLockerPlayerData& ForPlayer, const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ClassId, TransactionId, Sandboxed, OnCompletedRequest);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForPlayer(const FLootLockerPlayerData& ForPlayer, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ProductId, PurchaseToken, OnCompletedRequest);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForClass(const FLootLockerPlayerData& ForPlayer, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ClassId, ProductId, PurchaseToken, OnCompletedRequest);
}

void ULootLockerManager::BeginSteamPurchaseRedemption(const FLootLockerPlayerData& ForPlayer, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

void ULootLockerManager::BeginSteamPurchaseRedemptionForClass(const FLootLockerPlayerData& ForPlayer, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ClassId, SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

void ULootLockerManager::QuerySteamPurchaseRedemptionStatus(const FLootLockerPlayerData& ForPlayer, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, EntitlementId, OnCompletedRequest);
}

void ULootLockerManager::FinalizeSteamPurchaseRedemption(const FLootLockerPlayerData& ForPlayer, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, EntitlementId, OnCompletedRequest);
}

//Triggers
void ULootLockerManager::InvokeTriggersByKey(const FLootLockerPlayerData& ForPlayer, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnComplete)
{
    ULootLockerTriggersRequestHandler::InvokeTriggersByKey(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, KeysToInvoke, OnComplete);
}

//Notifications
void ULootLockerManager::ListNotificationsWithDefaultParameters(const FLootLockerPlayerData& ForPlayer, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnComplete);
}

void ULootLockerManager::ListNotifications(const FLootLockerPlayerData& ForPlayer, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ShowRead, OfType, WithSource, PerPage, Page, OnComplete);
}

void ULootLockerManager::ListNotificationsWithPriority(const FLootLockerPlayerData& ForPlayer, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, WithPriority, ShowRead, OfType, WithSource, PerPage, Page, OnComplete);
}

void ULootLockerManager::MarkAllNotificationsAsRead(const FLootLockerPlayerData& ForPlayer, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnComplete);
}

void ULootLockerManager::MarkNotificationsAsRead(const FLootLockerPlayerData& ForPlayer, const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    TArray<FString> UnreadNotificationIds;
    for (const FLootLockerNotification& Notification : Notifications)
    {
        if (!Notification.Read)
        {
            UnreadNotificationIds.Add(Notification.Id);
        }
    }
    MarkNotificationsAsReadByIds(ForPlayer, UnreadNotificationIds, OnComplete);
}

void ULootLockerManager::MarkNotificationsAsReadByIds(const FLootLockerPlayerData& ForPlayer, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, NotificationIDs, OnComplete);
}

bool ULootLockerManager::TryGetNotificationsByIdentifyingValue(const FLootLockerListNotificationsResponse& NotificationsResponse, const FString& IdentifyingValue, TArray<FLootLockerNotification>& Notifications)
{
    return NotificationsResponse.TryGetNotificationsByIdentifyingValue(IdentifyingValue, Notifications);
}

void ULootLockerManager::GetAllCollectables(const FLootLockerPlayerData& ForPlayer, const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted)
{
    ULootLockerCollectablesRequestHandler::GetAllCollectables(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetAllCollectablesCompleted);
}

void ULootLockerManager::CollectItem(const FLootLockerPlayerData& ForPlayer, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted)
{
    ULootLockerCollectablesRequestHandler::CollectItem(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Item, OnCollectItemCompleted);
}

void ULootLockerManager::GetMessages(const FLootLockerPlayerData& ForPlayer, const FMessagesResponseDelegateBP& OnGetMessagesCompleted)
{
    ULootLockerMessagesRequestHandler::GetMessages(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnGetMessagesCompleted);
}

void ULootLockerManager::ListLeaderboards(const FLootLockerPlayerData& ForPlayer, int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardRequestHandler::ListLeaderboards(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Count, After, OnCompletedRequestBP);
}

void ULootLockerManager::GetMemberRank(const FLootLockerPlayerData& ForPlayer, FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboard_key = LeaderboardKey;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, MemberRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetAllMemberRanks(const FLootLockerPlayerData& ForPlayer, FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetAllMemberRanksRequest MemberRanksRequest;
    MemberRanksRequest.after = After;
    MemberRanksRequest.count = Count;

    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, MemberRanksRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetByListOfMembers(const FLootLockerPlayerData& ForPlayer, TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, GetByListMembersRequest, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreList(const FLootLockerPlayerData& ForPlayer, FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboard_key = LeaderboardKey;
    ULootLockerLeaderboardRequestHandler::GetScoreList(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, GetScoreListRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreListInitial(const FLootLockerPlayerData& ForPlayer, FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    GetScoreList(ForPlayer, LeaderboardKey, Count, -1, OnCompletedRequestBP);
}


void ULootLockerManager::SubmitScore(const FLootLockerPlayerData& ForPlayer, FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, SubmitScoreRequest, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::ListLeaderboardArchive(const FLootLockerPlayerData& ForPlayer, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::GetLeaderboardArchive(const FLootLockerPlayerData& ForPlayer, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Key, Count, After, OnCompletedRequestBP);
}

void ULootLockerManager::GetLeaderboardDetails(const FLootLockerPlayerData& ForPlayer, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP)
{
    ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, LeaderboardKey, OnCompletedRequestBP);
}

void ULootLockerManager::ComputeAndLockDropTable(const FLootLockerPlayerData& ForPlayer, int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
{
    ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, TableId, OnCompletedRequestBP);
}

void ULootLockerManager::PickDropsFromDropTable(const FLootLockerPlayerData& ForPlayer, TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
{
    FLootLockerPickDropsFromDropTableRequest request;
    request.picks = Picks;
    ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, request, TableId, OnCompletedRequestBP);
}

// Currencies
void ULootLockerManager::ListCurrencies(const FLootLockerPlayerData& ForPlayer, const FLootLockerListCurrenciesResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::ListCurrencies(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompletedRequest);
}

void ULootLockerManager::GetCurrencyDetails(const FLootLockerPlayerData& ForPlayer, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDetails(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CurrencyCode, OnCompletedRequest);
}

void ULootLockerManager::GetCurrencyDenominationsByCode(const FLootLockerPlayerData& ForPlayer, const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CurrencyCode, OnCompletedRequest);
}

// Balances

void ULootLockerManager::ListBalancesInWallet(const FLootLockerPlayerData& ForPlayer, const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::ListBalancesInWallet(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, WalletID, OnComplete);
}

void ULootLockerManager::GetWalletByWalletID(const FLootLockerPlayerData& ForPlayer, const FString& WalletID, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByWalletID(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, WalletID, OnComplete);
}

void ULootLockerManager::GetWalletByHolderID(const FLootLockerPlayerData& ForPlayer, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByHolderID(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, HolderULID, HolderType, OnComplete);
}

void ULootLockerManager::CreditBalanceToWallet(const FLootLockerPlayerData& ForPlayer, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::CreditBalanceToWallet(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, WalletID, CurrencyID, Amount, OnComplete);
}

void ULootLockerManager::DebitBalanceToWallet(const FLootLockerPlayerData& ForPlayer, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnComplete)
{
    ULootLockerBalanceRequestHandler::DebitBalanceToWallet(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, WalletID, CurrencyID, Amount, OnComplete);
}

// Catalogs

void ULootLockerManager::ListCatalogs(const FLootLockerPlayerData& ForPlayer, const FLootLockerListCatalogsResponseBP& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogs(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnComplete);
}

void ULootLockerManager::ListCatalogItems(const FLootLockerPlayerData& ForPlayer, const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogItems(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, CatalogKey, Count, After, OnComplete);
}

TArray<FLootLockerInlinedCatalogEntry> ULootLockerManager::ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog)
{
    return ULootLockerCatalogRequestHandler::ConvertCatalogToInlineItems(Catalog);
}

// Entitlements
void ULootLockerManager::ListEntitlements(const FLootLockerPlayerData& ForPlayer, int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnComplete)
{
    ULootLockerEntitlementRequestHandler::ListEntitlements(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Count, After, OnComplete);
}

void ULootLockerManager::GetEntitlement(const FLootLockerPlayerData& ForPlayer, const FString& EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnComplete)
{
    ULootLockerEntitlementRequestHandler::GetEntitlement(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, EntitlementID, OnComplete);
}

void ULootLockerManager::ListPlayerFeedbackCategories(const FLootLockerPlayerData& ForPlayer, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ELootLockerFeedbackType::Player, OnComplete);
}

void ULootLockerManager::ListGameFeedbackCategories(const FLootLockerPlayerData& ForPlayer, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ELootLockerFeedbackType::Game, OnComplete);
}

void ULootLockerManager::ListUGCFeedbackCategories(const FLootLockerPlayerData& ForPlayer, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, ELootLockerFeedbackType::Ugc, OnComplete);
}

void ULootLockerManager::SendPlayerFeedback(const FLootLockerPlayerData& ForPlayer, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Ulid, Description, CategoryID, ELootLockerFeedbackType::Player, OnComplete);
}

void ULootLockerManager::SendGameFeedback(const FLootLockerPlayerData& ForPlayer, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, "", Description, CategoryID, ELootLockerFeedbackType::Game, OnComplete);
}

void ULootLockerManager::SendUGCFeedback(const FLootLockerPlayerData& ForPlayer, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Ulid, Description, CategoryID, ELootLockerFeedbackType::Ugc, OnComplete);

}

// Metadata

void ULootLockerManager::ListMetadata(const FLootLockerPlayerData& ForPlayer, const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::ListMetadata(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

void ULootLockerManager::ListMetadataWithTags(const FLootLockerPlayerData& ForPlayer, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::ListMetadata(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, OnComplete);
}

void ULootLockerManager::GetMetadata(const FLootLockerPlayerData& ForPlayer, const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::GetMetadata(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Source, SourceID, Key, IgnoreFiles, OnComplete);
}

void ULootLockerManager::GetMultisourceMetadata(const FLootLockerPlayerData& ForPlayer, const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::GetMultisourceMetadata(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, SourcesAndKeysToGet, IgnoreFiles, OnComplete);
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

void ULootLockerManager::SetMetadata(const FLootLockerPlayerData& ForPlayer, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseBP& OnComplete)
{
    ULootLockerMetadataRequestHandler::SetMetadata(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, Source, SourceID, MetadataToActionsToPerform, OnComplete);
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
void ULootLockerManager::GetServerTime(const FLootLockerPlayerData& ForPlayer, const FTimeResponseDelegateBP& OnCompletedRequestBP)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer, OnCompletedRequestBP);
}

FString ULootLockerManager::GetLastActivePlatform(const FLootLockerPlayerData& ForPlayer) {
    return ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(ForPlayer.PlayerUlid.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer("") : ForPlayer);
}
