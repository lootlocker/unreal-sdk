// Copyright (c) 2021 LootLocker


#include "LootLockerSDKManager.h"

#include "LootLockerStateData.h"
#include "GameAPI/LootLockerFriendsRequestHandler.h"

// Player State
TArray<FString> ULootLockerSDKManager::GetActivePlayerUlids()
{
    return ULootLockerStateData::GetActivePlayerUlids();
}

void ULootLockerSDKManager::SetPlayerUlidToInactive(const FString& PlayerUlid)
{
    return ULootLockerStateData::SetPlayerUlidToInactive(PlayerUlid);
}

void ULootLockerSDKManager::SetAllPlayersToInactive()
{
    ULootLockerStateData::SetAllPlayersToInactive();
}

void ULootLockerSDKManager::SetAllPlayersToInactiveExceptForPlayer(const FString& PlayerUlid)
{
    ULootLockerStateData::SetAllPlayersToInactiveExceptForPlayer(PlayerUlid);
}

TArray<FString> ULootLockerSDKManager::GetCachedPlayerUlids()
{
    return ULootLockerStateData::GetActivePlayerUlids();
}

FString ULootLockerSDKManager::GetDefaultPlayerUlid()
{
    return ULootLockerStateData::GetDefaultPlayerUlid();
}

bool ULootLockerSDKManager::SetDefaultPlayer(const FString& PlayerUlid)
{
    return ULootLockerStateData::SetDefaultPlayerUlid(PlayerUlid);
}

FLootLockerPlayerData ULootLockerSDKManager::GetSavedStateOrDefaultOrEmptyForPlayer(const FString& PlayerUlid)
{
    return ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(PlayerUlid);
}

void ULootLockerSDKManager::ClearCacheForPlayer(const FString& PlayerUlid)
{
    ULootLockerStateData::ClearSavedStateForPlayer(PlayerUlid);
}

void ULootLockerSDKManager::ClearAllPlayerCaches()
{
    ULootLockerStateData::ClearAllSavedStates();
}

void ULootLockerSDKManager::ClearAllPlayerCachesExceptForPlayer(const FString& PlayerUlid)
{
    ULootLockerStateData::ClearAllSavedStatesExceptForPlayer(PlayerUlid);
}

//Authentication
void ULootLockerSDKManager::StartSessionManual(const FLootLockerPlayerData& ForPlayer)
{
    ULootLockerStateData::SavePlayerData(ForPlayer);
}

FString ULootLockerSDKManager::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(Email, Password, OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest, const bool Remember /* = false */)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(Email, Password, Remember, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(PsnOnlineId, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, const FLootLockerSessionResponse& OnCompletedRequest, int PsnIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::VerifyPlayerAndStartPlaystationNetworkSession(AuthCode, AccountID, PsnIssuerId, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, const FLootLockerSessionResponse& OnCompletedRequest, int EnvIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::VerifyPlayerAndStartPlaystationNetworkV3Session(AuthCode, EnvIssuerId, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartAndroidSession(const FString& DeviceId, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartAndroidSession(DeviceId, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartAmazonLunaSession(const FString& AmazonLunaGuid,const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(AmazonLunaGuid, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FLootLockerSessionResponse& OnCompletedRequest, const FString& SteamAppId /* = "" */, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartSteamSession(SteamSessionTicket, SteamAppId, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(NSAIdToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartXboxSession(XboxUserToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartGoogleSession(const FString& IdToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Platform, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::RefreshGoogleSession(const FString& RefreshToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(RefreshToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartGooglePlayGamesSession(const FString& AuthCode, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartGooglePlayGamesSession(AuthCode, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::RefreshGooglePlayGamesSession(const FString& RefreshToken, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshGooglePlayGamesSession(RefreshToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartAppleSession(const FString& AuthorizationCode, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartAppleSession(AuthorizationCode, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::RefreshAppleSession(const FString& RefreshToken, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshAppleSession(RefreshToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseDelegate& OnStartedAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, Optionals, OnStartedAppleGameCenterSessionCompleted);
}

FString ULootLockerSDKManager::RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseDelegate& OnRefreshAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(RefreshToken, Optionals, OnRefreshAppleGameCenterSessionCompleted);
}

FString ULootLockerSDKManager::StartEpicSession(const FString& IdToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartEpicSession(IdToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::RefreshEpicSession(const FString& RefreshToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshEpicSession(RefreshToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartMetaSession(UserId, Nonce, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshMetaSession(RefreshToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelStartSession(const FLootLockerSessionResponse &OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& OnCompletedRequest, const bool Remember, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(Email, Password, Remember, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelVerifySession(const FLootLockerWhiteLabelVerifySessionDelegate &OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelRequestUserVerification(const int &UserId, const FLootLockerDefaultDelegate &OnCompletedRequest)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(UserId, OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(Email, OnCompletedRequest);
}

FString ULootLockerSDKManager::WhiteLabelRequestPasswordReset(const FString &Email, const FLootLockerDefaultDelegate &OnCompletedRequest)
{
    return ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(Email, OnCompletedRequest);
}

FString ULootLockerSDKManager::GuestLogin(const FLootLockerSessionResponse &OnCompletedRequest, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::GuestLogin(PlayerIdentifier, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartDiscordSession(const FString& AccessToken, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::StartDiscordSession(AccessToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::RefreshDiscordSession(const FString& RefreshToken, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    return ULootLockerAuthenticationRequestHandler::RefreshDiscordSession(RefreshToken, Optionals, OnCompletedRequest);
}

FString ULootLockerSDKManager::VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultDelegate& OnCompleteRequest, const FString& Platform, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAuthenticationRequestHandler::VerifyPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlatformToken, Platform, -1, OnCompleteRequest);
}

FString ULootLockerSDKManager::EndSession(const FLootLockerDefaultDelegate& OnCompleteRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAuthenticationRequestHandler::EndSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompleteRequest);
}

//==================================================
// Connected Accounts
//==================================================
FString ULootLockerSDKManager::ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

FString ULootLockerSDKManager::DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AccountToDisconnect, OnComplete);
}

FString ULootLockerSDKManager::ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IdToken, OnComplete);
}

FString ULootLockerSDKManager::ConnectGoogleAccount(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IdToken, Platform, OnComplete);
}

FString ULootLockerSDKManager::ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AuthorizationCode, OnComplete);
}

FString ULootLockerSDKManager::ConnectTwitchAccount(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectTwitchAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AuthorizationCode, OnComplete);
}

FString ULootLockerSDKManager::ConnectEpicAccount(const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectEpicAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Token, OnComplete);
}

FString ULootLockerSDKManager::ConnectPlaystationAccount(const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectPlaystationAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Environment, Code, OnComplete);
}

FString ULootLockerSDKManager::ConnectDiscordAccount(const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectDiscordAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Token, OnComplete);
}

FString ULootLockerSDKManager::ConnectRemoteSessionAccount(const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Code, Nonce, OnComplete);
}

FString ULootLockerSDKManager::TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid,	const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    const auto& fromPlayer = GetSavedStateOrDefaultOrEmptyForPlayer(FromPlayerWithUlid);
    const auto& toPlayer = GetSavedStateOrDefaultOrEmptyForPlayer(ToPlayerWithUlid);
    return ULootLockerConnectedAccountsRequestHandler::TransferIdentityProvidersBetweenAccounts(fromPlayer, toPlayer, ProvidersToTransfer, OnComplete);
}

//==================================================
// Remote Sessions
//==================================================
FString ULootLockerSDKManager::StartRemoteSession(
    const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
    const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
    const FLootLockerStartRemoteSessionResponseDelegate& OnComplete,
    float PollingIntervalSeconds,
    float TimeOutAfterMinutes)
{
    return ULootLockerRemoteSessionRequestHandler::StartRemoteSession(
        ELootLockerRemoteSessionLeaseIntent::login,
        RemoteSessionLeaseInformation,
        RemoteSessionLeaseStatusUpdate,
        OnComplete,
        PollingIntervalSeconds,
        TimeOutAfterMinutes,
        "");
}

FString ULootLockerSDKManager::StartRemoteSessionForLinking(
    const FString& ForPlayerWithUlid,
    const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
    const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
    const FLootLockerStartRemoteSessionResponseDelegate& OnComplete,
    float PollingIntervalSeconds,
    float TimeOutAfterMinutes)
{
    return ULootLockerRemoteSessionRequestHandler::StartRemoteSession(
        ELootLockerRemoteSessionLeaseIntent::link,
        RemoteSessionLeaseInformation,
        RemoteSessionLeaseStatusUpdate,
        OnComplete,
        PollingIntervalSeconds,
        TimeOutAfterMinutes,
        ForPlayerWithUlid);
}

void ULootLockerSDKManager::CancelRemoteSessionProcess(const FString& ProcessID)
{
    ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(ProcessID);
}

FString ULootLockerSDKManager::RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest)
{
    return ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(RefreshToken, OnCompletedRequest);
}

//Player
FString ULootLockerSDKManager::GetCurrentPlayerInfo(const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::ListPlayerInfo(TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::ListPlayerInfo(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetInventory(const FInventoryResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::GetInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetFullInventory(const FInventoryResponse& OnCompletedRequest, int32 StartIndex, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::GetFullInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest, StartIndex);
}

FString ULootLockerSDKManager::CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetCurrencyBalance(const FPBalanceResponse& onCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::GetCurrencyBalance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), onCompletedRequest);
}

FString ULootLockerSDKManager::InitiateDLCMigration(const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::InitiateDLCMigration(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::SetPlayerName(FString Name, const FPNameResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::SetPlayerName(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Name, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetPlayerName(const FPNameResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::GetPlayerName(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest& Request, const FPMultiplePlayerNames& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

FString ULootLockerSDKManager::LookupMultiplePlayersDataUsingIDs(const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNames& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

FString ULootLockerSDKManager::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeletePlayer(const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::DeletePlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

//Files
FString ULootLockerSDKManager::UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULLPlayerFilesRequestHandler::UploadFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnComplete);
}

FString ULootLockerSDKManager::UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULLPlayerFilesRequestHandler::UpdateFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileId, Request, OnComplete);
}

FString ULootLockerSDKManager::ListFiles(const FLootLockerFileListDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULLPlayerFilesRequestHandler::ListFiles(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

FString ULootLockerSDKManager::ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerID, OnComplete);
}

FString ULootLockerSDKManager::GetSingleFile(const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULLPlayerFilesRequestHandler::GetSingleFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileID, OnComplete);
}

FString ULootLockerSDKManager::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULLPlayerFilesRequestHandler::DeletePlayerFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileID, OnComplete);
}

FString ULootLockerSDKManager::GetDLCsMigration(const FPDlcResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::GetDLCsMigration(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::SetProfilePrivate(const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::SetProfilePrivate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::SetProfilePublic(const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPlayerRequestHandler::SetProfilePublic(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

// Player Progressions
FString ULootLockerSDKManager::GetPlayerProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetPlayerProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetPlayerProgressions(const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetPlayerProgressions(Count, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetPlayerProgressions(const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetPlayerProgressions(-1, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Amount, OnComplete);
}

FString ULootLockerSDKManager::SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Amount, OnComplete);
}

FString ULootLockerSDKManager::ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::ResetPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::DeletePlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetOtherPlayersProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerUlid, Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetOtherPlayersProgressions(PlayerUlid, Count, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetOtherPlayersProgressions(PlayerUlid, -1, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetOtherPlayersProgression(const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetOtherPlayersProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerUlid, ProgressionKey, OnComplete);
}

// Heroes
FString ULootLockerSDKManager::GetGameHeroes(const FLootLockerGameHeroListDelegate& OnCompleteRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::GetGameHeroes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompleteRequest);
}

FString ULootLockerSDKManager::ListPlayerHeroes(const FLootLockerHeroListDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::ListPlayerHeroes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamID64, OnCompletedRequest);
}

FString ULootLockerSDKManager::CreateHero(const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::CreateHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

FString ULootLockerSDKManager::CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::CreateHeroWithVariation(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetHero(const int32 HeroID, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::GetHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamID64, OnCompletedRequest);
}

FString ULootLockerSDKManager::UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::UpdateHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, Request, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::DeleteHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetHeroInventory(const int32 HeroID, const FInventoryResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::GetHeroInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::GetHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, OnCompletedRequest);
}

FString ULootLockerSDKManager::AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetInstanceID, OnCompletedRequest);
}

FString ULootLockerSDKManager::AddGlobalAssetToHeroLoadout(const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetID, OnCompletedRequest);
}

FString ULootLockerSDKManager::AddGlobalAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetID, AssetVariationID, OnCompletedRequest);
}

FString ULootLockerSDKManager::RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetInstanceID, OnCompletedRequest);
}


//Character
FString ULootLockerSDKManager::GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetCharacterLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::UpdateCharacter(int CharacterId, bool IsDefault, FString& Name, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::UpdateCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, IsDefault, Name, OnCompletedRequest);
}

FString ULootLockerSDKManager::CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterTypeId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::CreateCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IsDefault, CharacterName, CharacterTypeId, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteCharacter(int CharacterId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::DeleteCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, OnCompletedRequest);
}

FString ULootLockerSDKManager::ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::ListCharacterTypes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), InstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, AssetId, AssetVariationId, OnCompletedRequest);
}

FString ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, InstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), InstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, InstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerId, OtherPlayerPlatform, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherCharacterId, OnCompletedRequest);
}

FString ULootLockerSDKManager::ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::ListPlayerCharacters(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetOtherPlayersCharacterLoadouts(const FString& OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */, const FString& OtherPlayerPlatform /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetOtherPlayersCharacterLoadouts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerId, OtherPlayerPlatform, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetOtherPlayersCharacterLoadoutsByUid(const FString& OtherPlayerUid, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCharacterRequestHandler::GetOtherPlayersCharacterLoadoutsByUid(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerUid, OnCompletedRequest);
}

// Character Progressions
FString ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetCharacterProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetCharacterProgressions(CharacterId, Count, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetCharacterProgressions(CharacterId, -1, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, Amount, OnComplete);
}

FString ULootLockerSDKManager::SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, Amount, OnComplete);
}

FString ULootLockerSDKManager::ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::ResetCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, OnComplete);
}

//Asset Instance Progressions


FString ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32& Count, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Count, "", OnComplete);
}

FString ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, 0, "", OnComplete);
}

FString ULootLockerSDKManager::GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, Amount, OnComplete);
}

FString ULootLockerSDKManager::SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, Amount, OnComplete);
}

FString ULootLockerSDKManager::ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::ResetInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, OnComplete);
}

//Persistent Storage
FString ULootLockerSDKManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, OnCompletedRequest);
}

FString ULootLockerSDKManager::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Items, OnCompletedRequest);
}

FString ULootLockerSDKManager::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Item, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerId, OnCompletedRequest);
}

//Assets
FString ULootLockerSDKManager::GetContexts(const FContextDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GetContexts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GetAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GetUniversalAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), After, ItemsCount, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GetAssetsByIds(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetIds, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GetAssetBones(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::AddAssetToFavourites(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetId, OnCompletedRequest);
}

FString ULootLockerSDKManager::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetId, OnCompletedRequest);
}

FString ULootLockerSDKManager::GrantAssetToPlayerInventory(const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetID, AssetVariationID, AssetRentalOptionID, OnCompletedRequest);
}

FString ULootLockerSDKManager::ListAssetsWithDefaultParameters(const FListSimpleAssetsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /*= ""*/)
{
    return ListAssets(FLootLockerListSimpleAssetsRequest(), OnCompletedRequest, 0, 0, ELootLockerOrderAssetListBy::None, ELootLockerOrderAssetListDirection::None, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::ListAssets(const FLootLockerListSimpleAssetsRequest& Request, const FListSimpleAssetsResponseDelegate& OnCompletedRequest, int PerPage /*=0*/, int Page /*=0*/, ELootLockerOrderAssetListBy OrderBy /*=ELootLockerOrderAssetListBy::None*/, ELootLockerOrderAssetListDirection OrderDirection /*=ELootLockerOrderAssetListDirection::None*/, const FString& ForPlayerWithUlid /*= ""*/)
{
    return ULootLockerAssetsRequestHandler::ListAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, PerPage, Page, OrderBy, OrderDirection, OnCompletedRequest);
}

//Asset Instances
FString ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, OnCompletedRequest);
}

FString ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Item, OnCompletedRequest);
}

FString ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Items, OnCompletedRequest);
}

FString ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, Item, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, OnCompletedRequest);
}

FString ULootLockerSDKManager::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::InspectLootBox(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::OpenLootBox(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteAssetInstanceFromPlayerInventory(int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceID, OnCompletedRequest);
}

//User Generated Content
FString ULootLockerSDKManager::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateData, OnCompletedRequest);
}

FString ULootLockerSDKManager::CreateAssetCandidateAndMarkComplete(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateData, OnCompletedRequest);
}

FString ULootLockerSDKManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, AssetCandidateData, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, OnCompletedRequest);
}

FString ULootLockerSDKManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FilePath, FilePurpose, OnCompletedRequest);
}

FString ULootLockerSDKManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FileId, OnCompletedRequest);
}

// Progressions
FString ULootLockerSDKManager::GetProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetProgressions(const int32& Count, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetProgressions(Count, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetProgressions(const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetProgressions(-1, "", OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, OnComplete);
}

FString ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const int32& After, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerProgressionsRequestHandler::GetProgressionTiers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetProgressionTiers(ProgressionKey, Count, 0, OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetProgressionTiers(ProgressionKey, -1, 0, OnComplete, ForPlayerWithUlid);
}

//Missions
FString ULootLockerSDKManager::GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMissionsRequestHandler::GetAllMissions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMissionsRequestHandler::GetMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, OnCompletedRequest);
}

FString ULootLockerSDKManager::StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMissionsRequestHandler::StartMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, OnCompletedRequest);
}

FString ULootLockerSDKManager::FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMissionsRequestHandler::FinishMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, MissionData, OnCompletedRequest);
}

//Maps
FString ULootLockerSDKManager::GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMapsRequestHandler::GetMaps(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

//Purchasing

FString ULootLockerSDKManager::ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::ActivateRentalAsset(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

FString ULootLockerSDKManager::LootLockerPurchaseSingleCatalogItem(const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return LootLockerPurchaseCatalogItems(WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::LootLockerPurchaseCatalogItems(const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletId, ItemsToPurchase, OnCompletedRequest);
}

FString ULootLockerSDKManager::RedeemAppleAppStorePurchaseForPlayer(const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, Sandboxed, OnCompletedRequest);
}

FString ULootLockerSDKManager::RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, TransactionId, Sandboxed, OnCompletedRequest);
}

FString ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProductId, PurchaseToken, OnCompletedRequest);
}

FString ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, ProductId, PurchaseToken, OnCompletedRequest);
}


FString ULootLockerSDKManager::RedeemEpicStorePurchase(const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid)
{
    return ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchase(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AccountId, BearerToken, EntitlementIds, SandboxId, OnCompletedRequest);
}

FString ULootLockerSDKManager::RedeemEpicStorePurchaseForCharacter(const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid)
{
    return ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchaseForCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, AccountId, BearerToken, EntitlementIds, SandboxId, OnCompletedRequest);
}

#ifdef LOOTLOCKER_BETA_PLAYSTATION_IAP
// FString ULootLockerSDKManager::RedeemPlayStationStorePurchase(const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FString& ForPlayerWithUlid)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, OnCompletedRequest);
// }

// FString ULootLockerSDKManager::RedeemPlayStationStorePurchaseForCharacter(const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FString& ForPlayerWithUlid)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, OnCompletedRequest);
// }
#endif

FString ULootLockerSDKManager::BeginSteamPurchaseRedemption(const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

FString ULootLockerSDKManager::BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, SteamId, Currency, Language, CatalogItemId, OnCompletedRequest);
}

FString ULootLockerSDKManager::QuerySteamPurchaseRedemptionStatus(const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementId, OnCompletedRequest);
}

FString ULootLockerSDKManager::FinalizeSteamPurchaseRedemption(const FString& EntitlementId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementId, OnCompletedRequest);
}

//Triggers
FString ULootLockerSDKManager::InvokeTriggersByKey(const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerTriggersRequestHandler::InvokeTriggersByKey(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), KeysToInvoke, OnComplete);
}

//Notifications
FString ULootLockerSDKManager::ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

FString ULootLockerSDKManager::ListNotifications(bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerNotificationsRequestHandler::ListNotifications(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, OnComplete);
}

FString ULootLockerSDKManager::ListNotificationsWithPriority(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerNotificationsRequestHandler::ListNotifications(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WithPriority, ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, OnComplete);
}

FString ULootLockerSDKManager::MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

FString ULootLockerSDKManager::MarkNotificationsAsRead(const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    TArray<FString> UnreadNotificationIds;
    for (const FLootLockerNotification& Notification : Notifications)
    {
        if (!Notification.Read)
        {
            UnreadNotificationIds.Add(Notification.Id);
        }
    }
    return MarkNotificationsAsReadByIds(UnreadNotificationIds, OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::MarkNotificationsAsReadByIds(const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), NotificationIDs, OnComplete);
}

//Broadcasts
FString ULootLockerSDKManager::ListTopBroadcasts(const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ListBroadcasts({}, -1, -1, OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::ListTopBroadcastsLocalized(const TArray<FString>& Languages, const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ListBroadcasts(Languages, -1, -1, OnComplete, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::ListBroadcasts(const TArray<FString>& Languages, int32 PerPage, int32 Page, const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerBroadcastRequestHandler::ListBroadcasts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Languages, PerPage, Page, OnComplete);
}

//Collectables
FString ULootLockerSDKManager::GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCollectablesRequestHandler::GetAllCollectables(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCollectablesRequestHandler::CollectItem(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Item, OnCompletedRequest);
}

//Messages
FString ULootLockerSDKManager::GetMessages(const FMessagesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMessagesRequestHandler::GetMessages(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

// Leaderboards
FString ULootLockerSDKManager::ListLeaderboards(int Count, int After, const FLootLockerListLeaderboardsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerLeaderboardRequestHandler::ListLeaderboards(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboard_key = LeaderboardKey;
    MemberRequest.member_id = MemberId;

    return ULootLockerLeaderboardRequestHandler::GetMemberRank(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MemberRequest, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    return ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetByListMembersRequest, LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboard_key = LeaderboardKey;
    return ULootLockerLeaderboardRequestHandler::GetScoreList(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetScoreListRequest, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return GetScoreList(LeaderboardKey, Count, -1, OnCompletedRequest, ForPlayerWithUlid);
}

FString ULootLockerSDKManager::SubmitScore(FString MemberId, const FString LeaderboardKey, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    return ULootLockerLeaderboardRequestHandler::SubmitScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SubmitScoreRequest, LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerSDKManager::QueryScore(const FString LeaderboardKey, const int Score, const FLootLockerSubmitScoreResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerQueryScoreRequest QueryScoreRequest;
    QueryScoreRequest.score = Score;
    return ULootLockerLeaderboardRequestHandler::QueryScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), QueryScoreRequest, LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerSDKManager::IncrementScore(FString MemberId, const FString LeaderboardKey, const int Amount, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerIncrementScoreRequest IncrementScoreRequest;
    IncrementScoreRequest.member_id = MemberId;
    IncrementScoreRequest.amount = Amount;
    return ULootLockerLeaderboardRequestHandler::IncrementScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IncrementScoreRequest, LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetAllMemberRanksRequest GetAllMemberRanksRequest;
    GetAllMemberRanksRequest.after = After;
    GetAllMemberRanksRequest.count = Count;
    GetAllMemberRanksRequest.member_id = MemberId;
    return ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetAllMemberRanksRequest, OnCompletedRequest);
}

FString ULootLockerSDKManager::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), LeaderboardKey, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, Count, After, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetLeaderboardDetails(const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), LeaderboardKey, OnCompletedRequest);
}

// Droptables
FString ULootLockerSDKManager::ComputeAndLockDropTable(const int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TableId, OnCompletedRequest);
}

FString ULootLockerSDKManager::PickDropsFromDropTable(const TArray<int> Picks, const  int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerPickDropsFromDropTableRequest Request;
    Request.picks = Picks;
    return ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, TableId, OnCompletedRequest);
}

// Currencies

FString ULootLockerSDKManager::ListCurrencies(const FLootLockerListCurrenciesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCurrencyRequestHandler::ListCurrencies(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetCurrencyDetails(const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCurrencyRequestHandler::GetCurrencyDetails(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CurrencyCode, OnCompletedRequest);
}

FString ULootLockerSDKManager::GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CurrencyCode, OnCompletedRequest);
}

// Balances

FString ULootLockerSDKManager::ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerBalanceRequestHandler::ListBalancesInWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, OnComplete);
}

FString ULootLockerSDKManager::GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerBalanceRequestHandler::GetWalletByWalletID(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, OnComplete);
}

FString ULootLockerSDKManager::GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerBalanceRequestHandler::GetWalletByHolderID(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HolderULID, HolderType, OnComplete);
}

FString ULootLockerSDKManager::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerBalanceRequestHandler::CreditBalanceToWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, CurrencyID, Amount, OnComplete);
}

FString ULootLockerSDKManager::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerBalanceRequestHandler::DebitBalanceToWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, CurrencyID, Amount, OnComplete);
}

// Catalogs

FString ULootLockerSDKManager::ListCatalogs(const FLootLockerListCatalogsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCatalogRequestHandler::ListCatalogs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnComplete);
}

FString ULootLockerSDKManager::ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerCatalogRequestHandler::ListCatalogItems(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CatalogKey, Count, After, OnComplete);
}

// Entitlements
FString ULootLockerSDKManager::ListEntitlements(const int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerEntitlementRequestHandler::ListEntitlements(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, OnComplete);
}

FString ULootLockerSDKManager::GetEntitlement(const FString& EntitlementID, FLootLockerSingleEntitlementResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerEntitlementRequestHandler::GetEntitlement(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementID, OnComplete);
}

// Feedback
FString ULootLockerSDKManager::ListPlayerFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Player, OnComplete);

}

FString ULootLockerSDKManager::ListGameFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Game, OnComplete);

}

FString ULootLockerSDKManager::ListUGCFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Ugc, OnComplete);

}

FString ULootLockerSDKManager::SendPlayerFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Ulid, Description, CategoryID, ELootLockerFeedbackType::Player, OnComplete);

}

FString ULootLockerSDKManager::SendGameFeedback(const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), "", Description, CategoryID, ELootLockerFeedbackType::Game, OnComplete);

}

FString ULootLockerSDKManager::SendUGCFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Ulid, Description, CategoryID, ELootLockerFeedbackType::Ugc, OnComplete);

}

// Metadata

FString ULootLockerSDKManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, -1, -1, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

FString ULootLockerSDKManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, OnComplete);
}

FString ULootLockerSDKManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, -1, -1, FString(), Tags, IgnoreFiles, OnComplete);
}

FString ULootLockerSDKManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, OnComplete);
}

FString ULootLockerSDKManager::GetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const FLootLockerGetMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::GetMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Key, IgnoreFiles, OnComplete);
}

FString ULootLockerSDKManager::GetMultisourceMetadata(const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const FLootLockerGetMultisourceMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::GetMultisourceMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SourcesAndKeysToGet, IgnoreFiles, OnComplete);
}

FString ULootLockerSDKManager::SetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMetadataRequestHandler::SetMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, MetadataToActionsToPerform, OnComplete);
}

// Followers
FString ULootLockerSDKManager::ListFollowers(const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowers(const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowersPaginated(const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowersPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Cursor, Count, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowersPaginated(const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowersPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, Cursor, Count, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowing(const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowing(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowing(const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowing(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowingPaginated(const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowingPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Cursor, Count, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFollowingPaginated(const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::ListFollowingPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, Cursor, Count, OnResponseCompleted);
}

FString ULootLockerSDKManager::FollowPlayer(const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::FollowPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, OnResponseCompleted);
}

FString ULootLockerSDKManager::UnfollowPlayer(const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFollowersRequestHandler::UnfollowPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, OnResponseCompleted);
}

// Friends

FString ULootLockerSDKManager::ListFriends(const FLootLockerListFriendsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListFriends(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnResponseCompleted);
}

FString ULootLockerSDKManager::ListFriendsPaginated(int32 Page, int32 PerPage, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListFriendsPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListIncomingFriendRequests(const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListIncomingFriendRequests(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnResponseCompleted);
}

FString ULootLockerSDKManager::ListIncomingFriendRequestsPaginated(int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListIncomingFriendRequestsPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListOutgoingFriendRequests(const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListOutgoingFriendRequests(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnResponseCompleted);
}

FString ULootLockerSDKManager::ListOutgoingFriendRequestsPaginated(int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListOutgoingFriendRequestsPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, OnResponseCompleted);
}

FString ULootLockerSDKManager::SendFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::SendFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

FString ULootLockerSDKManager::DeleteFriend(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::DeleteFriend(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

FString ULootLockerSDKManager::CancelOutgoingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::CancelOutgoingFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

FString ULootLockerSDKManager::AcceptIncomingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::AcceptIncomingFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

FString ULootLockerSDKManager::DeclineIncomingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::DeclineIncomingFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

FString ULootLockerSDKManager::ListBlockedPlayers(const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListBlockedPlayers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnResponseCompleted);
}

FString ULootLockerSDKManager::ListBlockedPlayersPaginated(int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::ListBlockedPlayersPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, OnResponseCompleted);
}

FString ULootLockerSDKManager::GetFriend(const FString& FriendUlid, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::GetFriend(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FriendUlid, OnResponseCompleted);
}

FString ULootLockerSDKManager::BlockPlayer(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::BlockPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

FString ULootLockerSDKManager::UnblockPlayer(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerFriendsRequestHandler::UnblockPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, OnResponseCompleted);
}

// Miscellaneous
FString ULootLockerSDKManager::GetServerTime(const FTimeResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerMiscellaneousRequestHandler::GetServerTime(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetLastActivePlatform(const FString& ForPlayerWithUlid /* = "" */){
    return ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid));
}

FString ULootLockerSDKManager::GetGameInfo(const FGameInfoResponseDelegate& OnComplete)
{
    return ULootLockerMiscellaneousRequestHandler::GetGameInfo(OnComplete);
}
