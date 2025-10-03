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

void ULootLockerSDKManager::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(Email, Password, FLootLockerLoginResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest, const bool Remember /* = false */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(Email, Password, Remember, FLootLockerLoginResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(PsnOnlineId, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, const FLootLockerSessionResponse& OnCompletedRequest, int PsnIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayerAndStartPlaystationNetworkSession(AuthCode, AccountID, PsnIssuerId, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, const FLootLockerSessionResponse& OnCompletedRequest, int EnvIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayerAndStartPlaystationNetworkV3Session(AuthCode, EnvIssuerId, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAndroidSession(const FString& DeviceId, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartAndroidSession(DeviceId, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAmazonLunaSession(const FString& AmazonLunaGuid,const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(AmazonLunaGuid, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FLootLockerSessionResponse& OnCompletedRequest, const FString& SteamAppId /* = "" */, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartSteamSession(SteamSessionTicket, SteamAppId, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(NSAIdToken, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartXboxSession(XboxUserToken, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartGoogleSession(const FString& IdToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Optionals, FGoogleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Platform, Optionals, FGoogleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshGoogleSession(const FString& RefreshToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(RefreshToken, Optionals, FGoogleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartGooglePlayGamesSession(const FString& AuthCode, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartGooglePlayGamesSession(AuthCode, Optionals, FGooglePlayGamesSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshGooglePlayGamesSession(const FString& RefreshToken, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshGooglePlayGamesSession(RefreshToken, Optionals, FGooglePlayGamesSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAppleSession(const FString& AuthorizationCode, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartAppleSession(AuthorizationCode, Optionals, FAppleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshAppleSession(const FString& RefreshToken, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleSession(RefreshToken, Optionals, FAppleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseDelegate& OnStartedAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, Optionals, FLootLockerAppleGameCenterSessionResponseBP(), OnStartedAppleGameCenterSessionCompleted);
}

void ULootLockerSDKManager::RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseDelegate& OnRefreshAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(RefreshToken, Optionals, FLootLockerAppleGameCenterSessionResponseBP(),OnRefreshAppleGameCenterSessionCompleted);
}

void ULootLockerSDKManager::StartEpicSession(const FString& IdToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartEpicSession(IdToken, Optionals, FEpicSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshEpicSession(const FString& RefreshToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshEpicSession(RefreshToken, Optionals, FEpicSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartMetaSession(UserId, Nonce, Optionals, FLootLockerMetaSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshMetaSession(RefreshToken, Optionals, FLootLockerMetaSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelStartSession(const FLootLockerSessionResponse &OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& OnCompletedRequest, const bool Remember, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(Email, Password, Remember, Optionals, FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelVerifySession(const FLootLockerWhiteLabelVerifySessionDelegate &OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerVerifySessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelRequestUserVerification(const int &UserId, const FLootLockerDefaultDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(UserId, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerificationByEmail(Email, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelRequestPasswordReset(const FString &Email, const FLootLockerDefaultDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(Email, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GuestLogin(const FLootLockerSessionResponse &OnCompletedRequest, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::GuestLogin(PlayerIdentifier, Optionals, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartDiscordSession(const FString& AccessToken, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::StartDiscordSession(AccessToken, Optionals, FDiscordSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshDiscordSession(const FString& RefreshToken, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals /* = FLootLockerSessionOptionals() */)
{
    ULootLockerAuthenticationRequestHandler::RefreshDiscordSession(RefreshToken, Optionals, FDiscordSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultDelegate& OnCompleteRequest, const FString& Platform, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlatformToken, Platform, -1, FLootLockerDefaultResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::EndSession(const FLootLockerDefaultDelegate& OnCompleteRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAuthenticationRequestHandler::EndSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerDefaultResponseBP(), OnCompleteRequest);
}

//==================================================
// Connected Accounts
//==================================================
void ULootLockerSDKManager::ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListConnectedAccountsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AccountToDisconnect, FLootLockerDefaultResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IdToken, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectGoogleAccount(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IdToken, Platform, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AuthorizationCode, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectTwitchAccount(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectTwitchAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AuthorizationCode, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectEpicAccount(const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectEpicAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Token, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectPlaystationAccount(const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectPlaystationAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Environment, Code, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectDiscordAccount(const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectDiscordAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Token, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectRemoteSessionAccount(const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Code, Nonce, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid,	const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    const auto& fromPlayer = GetSavedStateOrDefaultOrEmptyForPlayer(FromPlayerWithUlid);
    const auto& toPlayer = GetSavedStateOrDefaultOrEmptyForPlayer(ToPlayerWithUlid);
    ULootLockerConnectedAccountsRequestHandler::TransferIdentityProvidersBetweenAccounts(fromPlayer, toPlayer, ProvidersToTransfer, FLootLockerListConnectedAccountsResponseBP(), OnComplete);
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
        FLootLockerLeaseRemoteSessionResponseDelegateBP(),
        RemoteSessionLeaseInformation,
        FLootLockerRemoteSessionStatusPollingResponseDelegateBP(),
        RemoteSessionLeaseStatusUpdate,
        FLootLockerStartRemoteSessionResponseDelegateBP(),
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
        FLootLockerLeaseRemoteSessionResponseDelegateBP(),
        RemoteSessionLeaseInformation,
        FLootLockerRemoteSessionStatusPollingResponseDelegateBP(),
        RemoteSessionLeaseStatusUpdate,
        FLootLockerStartRemoteSessionResponseDelegateBP(),
        OnComplete,
        PollingIntervalSeconds,
        TimeOutAfterMinutes,
        ForPlayerWithUlid);
}

void ULootLockerSDKManager::CancelRemoteSessionProcess(const FString& ProcessID)
{
    ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(ProcessID);
}

void ULootLockerSDKManager::RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(RefreshToken, FLootLockerRefreshRemoteSessionResponseDelegateBP(), OnCompletedRequest);
}

//Player
void ULootLockerSDKManager::GetCurrentPlayerInfo(const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerGetCurrentPlayerInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListPlayerInfo(TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::ListPlayerInfo(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, FLootLockerListPlayerInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetInventory(const FInventoryResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::GetInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetFullInventory(const FInventoryResponse& OnCompletedRequest, int32 StartIndex, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::GetFullInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPInventoryResponseBP(), OnCompletedRequest, StartIndex);
}

void ULootLockerSDKManager::CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPAssetNotificationResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyBalance(const FPBalanceResponse& onCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::GetCurrencyBalance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPBalanceResponseBP(), onCompletedRequest);
}

void ULootLockerSDKManager::InitiateDLCMigration(const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::InitiateDLCMigration(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetPlayerName(FString Name, const FPNameResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Name, FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerName(const FPNameResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::GetPlayerName(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest& Request, const FPMultiplePlayerNames& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, FPMultiplePlayerNamesBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayersDataUsingIDs(const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNames& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, FPMultiplePlayerNamesBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, FPMultiplePlayersPlatformIdsBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeletePlayer(const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::DeletePlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

//Files
void ULootLockerSDKManager::UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULLPlayerFilesRequestHandler::UploadFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULLPlayerFilesRequestHandler::UpdateFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileId, Request, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::ListFiles(const FLootLockerFileListDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULLPlayerFilesRequestHandler::ListFiles(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerFileListBP(), OnComplete);
}

void ULootLockerSDKManager::ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerID, FLootLockerFileListBP(), OnComplete);
}

void ULootLockerSDKManager::GetSingleFile(const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULLPlayerFilesRequestHandler::GetSingleFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileID, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULLPlayerFilesRequestHandler::DeletePlayerFile(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FileID, FLootLockerFileDeletedBP(), OnComplete);
}

void ULootLockerSDKManager::GetDLCsMigration(const FPDlcResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::GetDLCsMigration(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPDlcResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetProfilePrivate(const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::SetProfilePrivate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetProfilePublic(const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPlayerRequestHandler::SetProfilePublic(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FResponseCallbackBP(), OnCompletedRequest);
}

// Player Progressions
void ULootLockerSDKManager::GetPlayerProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, FLootLockerPaginatedPlayerProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetPlayerProgressions(const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetPlayerProgressions(Count, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetPlayerProgressions(const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetPlayerProgressions(-1, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, FLootLockerPlayerProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::ResetPlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, FLootLockerPlayerProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::DeletePlayerProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, FLootLockerDeleteProgressionBP(), OnComplete);
}

void ULootLockerSDKManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerUlid, Count, After, FLootLockerPaginatedPlayerProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetOtherPlayersProgressions(PlayerUlid, Count, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetOtherPlayersProgressions(const FString& PlayerUlid, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetOtherPlayersProgressions(PlayerUlid, -1, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetOtherPlayersProgression(const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetOtherPlayersProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerUlid, ProgressionKey, FLootLockerPlayerProgressionResponseBP(), OnComplete);
}

// Heroes
void ULootLockerSDKManager::GetGameHeroes(const FLootLockerGameHeroListDelegate& OnCompleteRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::GetGameHeroes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerGameHeroListBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::ListPlayerHeroes(const FLootLockerHeroListDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::ListPlayerHeroes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerHeroListBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamID64, FLootLockerHeroListBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateHero(const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::CreateHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::CreateHeroWithVariation(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHero(const int32 HeroID, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::GetHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamID64, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::UpdateHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::DeleteHero(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, FLLHeroDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHeroInventory(const int32 HeroID, const FInventoryResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::GetHeroInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, FPInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::GetHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetInstanceID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddGlobalAssetToHeroLoadout(const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddGlobalAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetID, AssetVariationID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HeroID, AssetInstanceID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}


//Character
void ULootLockerSDKManager::GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateCharacter(int CharacterId, bool IsDefault, FString& Name, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, IsDefault, Name, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterTypeId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IsDefault, CharacterName, CharacterTypeId, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteCharacter(int CharacterId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::DeleteCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::ListCharacterTypes(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPLootLockerListCharacterTypesResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, AssetId, AssetVariationId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerId, OtherPlayerPlatform, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherCharacterId, FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::ListPlayerCharacters(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPLootLockerListPlayerCharactersResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCharacterLoadouts(const FString& OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */, const FString& OtherPlayerPlatform /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCharacterLoadouts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerId, OtherPlayerPlatform, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCharacterLoadoutsByUid(const FString& OtherPlayerUid, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCharacterLoadoutsByUid(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OtherPlayerUid, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

// Character Progressions
void ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, Count, After, FLootLockerPaginatedCharacterProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetCharacterProgressions(CharacterId, Count, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetCharacterProgressions(CharacterId, -1, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, FLootLockerCharacterProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::ResetCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, FLootLockerCharacterProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, ProgressionKey, FLootLockerDeleteProgressionBP(), OnComplete);
}

//Asset Instance Progressions


void ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Count, After, FLootLockerPaginatedInstanceProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32& Count, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Count, "", FLootLockerPaginatedInstanceProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, 0, "", FLootLockerPaginatedInstanceProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::ResetInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, ProgressionKey, FLootLockerDeleteProgressionBP(), OnComplete);
}

//Persistent Storage
void ULootLockerSDKManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, FPersistentStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Items, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Item, FPersistentStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerId, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

//Assets
void ULootLockerSDKManager::GetContexts(const FContextDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GetContexts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GetAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, OnCompletedRequest);
}

void ULootLockerSDKManager::GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GetUniversalAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), After, ItemsCount, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GetAssetsByIds(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetIds, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GetAssetBones(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

void ULootLockerSDKManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::AddAssetToFavourites(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetId, OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetId, OnCompletedRequest);
}

void ULootLockerSDKManager::GrantAssetToPlayerInventory(const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetID, AssetVariationID, AssetRentalOptionID, OnCompletedRequest);
}

void ULootLockerSDKManager::ListAssetsWithDefaultParameters(const FListSimpleAssetsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /*= ""*/)
{
    ListAssets(FLootLockerListSimpleAssetsRequest(), OnCompletedRequest, 0, 0, ELootLockerOrderAssetListBy::None, ELootLockerOrderAssetListDirection::None, ForPlayerWithUlid);
}

void ULootLockerSDKManager::ListAssets(const FLootLockerListSimpleAssetsRequest& Request, const FListSimpleAssetsResponseDelegate& OnCompletedRequest, int PerPage /*=0*/, int Page /*=0*/, ELootLockerOrderAssetListBy OrderBy /*=ELootLockerOrderAssetListBy::None*/, ELootLockerOrderAssetListDirection OrderDirection /*=ELootLockerOrderAssetListDirection::None*/, const FString& ForPlayerWithUlid /*= ""*/)
{
    ULootLockerAssetsRequestHandler::ListAssets(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, PerPage, Page, OrderBy, OrderDirection, OnCompletedRequest);
}

//Asset Instances
void ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Item, OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, Items, OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, Item, OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, StorageItemId, OnCompletedRequest);
}

void ULootLockerSDKManager::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::InspectLootBox(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

void ULootLockerSDKManager::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::OpenLootBox(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetInstanceFromPlayerInventory(int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceID, OnCompletedRequest);
}

//User Generated Content
void ULootLockerSDKManager::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateData, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAssetCandidateAndMarkComplete(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateData, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, AssetCandidateData, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FAssetCandidatesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FilePath, FilePurpose, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetCandidateId, FileId, FResponseCallbackBP(), OnCompletedRequest);
}

// Progressions
void ULootLockerSDKManager::GetProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetProgressions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, FLootLockerPaginatedProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetProgressions(const int32& Count, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetProgressions(Count, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetProgressions(const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetProgressions(-1, "", OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetProgression(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, FLootLockerProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const int32& After, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerProgressionsRequestHandler::GetProgressionTiers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProgressionKey, Count, After, FLootLockerPaginatedProgressionTiersResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetProgressionTiers(ProgressionKey, Count, 0, OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    GetProgressionTiers(ProgressionKey, -1, 0, OnComplete, ForPlayerWithUlid);
}

//Missions
void ULootLockerSDKManager::GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMissionsRequestHandler::GetAllMissions(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FMissionsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMissionsRequestHandler::GetMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, FMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMissionsRequestHandler::StartMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, FStartMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMissionsRequestHandler::FinishMission(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MissionId, MissionData, FFinishMissionResponseDelegateBP(), OnCompletedRequest);
}

//Maps
void ULootLockerSDKManager::GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMapsRequestHandler::GetMaps(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FGetMapsResponseDelegateBP(), OnCompletedRequest);
}

//Purchasing

void ULootLockerSDKManager::ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AssetInstanceId, FActivateRentalAssetResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LootLockerPurchaseSingleCatalogItem(const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    LootLockerPurchaseCatalogItems(WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest, ForPlayerWithUlid);
}

void ULootLockerSDKManager::LootLockerPurchaseCatalogItems(const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletId, ItemsToPurchase, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemAppleAppStorePurchaseForPlayer(const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, Sandboxed, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, TransactionId, Sandboxed, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ProductId, PurchaseToken, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, ProductId, PurchaseToken, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}


void ULootLockerSDKManager::RedeemEpicStorePurchase(const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid)
{
    ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchase(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), AccountId, BearerToken, EntitlementIds, SandboxId, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemEpicStorePurchaseForCharacter(const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid)
{
    ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchaseForCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, AccountId, BearerToken, EntitlementIds, SandboxId, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

#ifdef LOOTLOCKER_BETA_PLAYSTATION_IAP
// void ULootLockerSDKManager::RedeemPlayStationStorePurchase(const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FString& ForPlayerWithUlid)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, FLootLockerDefaultResponseBP(), OnCompletedRequest);
// }

// void ULootLockerSDKManager::RedeemPlayStationStorePurchaseForCharacter(const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FString& ForPlayerWithUlid)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, FLootLockerDefaultResponseBP(), OnCompletedRequest);
// }
#endif

void ULootLockerSDKManager::BeginSteamPurchaseRedemption(const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ClassId, SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::QuerySteamPurchaseRedemptionStatus(const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementId, FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::FinalizeSteamPurchaseRedemption(const FString& EntitlementId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementId, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

//Triggers
void ULootLockerSDKManager::InvokeTriggersByKey(const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerTriggersRequestHandler::InvokeTriggersByKey(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), KeysToInvoke, FLootLockerInvokeTriggersByKeyResponseBP(), OnComplete);
}

//Notifications
void ULootLockerSDKManager::ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListNotifications(bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListNotificationsWithPriority(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WithPriority, ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerReadNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::MarkNotificationsAsRead(const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    TArray<FString> UnreadNotificationIds;
    for (const FLootLockerNotification& Notification : Notifications)
    {
        if (!Notification.Read)
        {
            UnreadNotificationIds.Add(Notification.Id);
        }
    }
    MarkNotificationsAsReadByIds(UnreadNotificationIds, OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::MarkNotificationsAsReadByIds(const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), NotificationIDs, FLootLockerReadNotificationsResponseBP(), OnComplete);
}

//Broadcasts
void ULootLockerSDKManager::ListTopBroadcasts(const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ListBroadcasts({}, -1, -1, OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::ListTopBroadcastsLocalized(const TArray<FString>& Languages, const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ListBroadcasts(Languages, -1, -1, OnComplete, ForPlayerWithUlid);
}

void ULootLockerSDKManager::ListBroadcasts(const TArray<FString>& Languages, int32 PerPage, int32 Page, const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerBroadcastRequestHandler::ListBroadcasts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Languages, PerPage, Page, FLootLockerListBroadcastsResponseBP(), OnComplete);
}

//Collectables
void ULootLockerSDKManager::GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCollectablesRequestHandler::GetAllCollectables(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCollectablesRequestHandler::CollectItem(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Item, FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

//Messages
void ULootLockerSDKManager::GetMessages(const FMessagesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMessagesRequestHandler::GetMessages(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FMessagesResponseDelegateBP(), OnCompletedRequest);
}

// Leaderboards
void ULootLockerSDKManager::ListLeaderboards(int Count, int After, const FLootLockerListLeaderboardsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerLeaderboardRequestHandler::ListLeaderboards(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, FLootLockerListLeaderboardsResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboard_key = LeaderboardKey;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), MemberRequest, FLootLockerGetMemberRankResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetByListMembersRequest, LeaderboardKey, FLootLockerGetByListOfMembersResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboard_key = LeaderboardKey;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetScoreListRequest, FLootLockerGetScoreListResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    GetScoreList(LeaderboardKey, Count, -1, OnCompletedRequest, ForPlayerWithUlid);
}

void ULootLockerSDKManager::SubmitScore(FString MemberId, const FString LeaderboardKey, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SubmitScoreRequest, LeaderboardKey, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::QueryScore(const FString LeaderboardKey, const int Score, const FLootLockerSubmitScoreResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerQueryScoreRequest QueryScoreRequest;
    QueryScoreRequest.score = Score;
    ULootLockerLeaderboardRequestHandler::QueryScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), QueryScoreRequest, LeaderboardKey, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::IncrementScore(FString MemberId, const FString LeaderboardKey, const int Amount, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerIncrementScoreRequest IncrementScoreRequest;
    IncrementScoreRequest.member_id = MemberId;
    IncrementScoreRequest.amount = Amount;
    ULootLockerLeaderboardRequestHandler::IncrementScore(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), IncrementScoreRequest, LeaderboardKey, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerGetAllMemberRanksRequest GetAllMemberRanksRequest;
    GetAllMemberRanksRequest.after = After;
    GetAllMemberRanksRequest.count = Count;
    GetAllMemberRanksRequest.member_id = MemberId;
    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), GetAllMemberRanksRequest, FLootLockerGetAllMemberRanksResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), LeaderboardKey, FLootLockerLeaderboardArchiveResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Key, Count, After, FLootLockerLeaderboardArchiveDetailReponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetLeaderboardDetails(const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), LeaderboardKey, FLootLockerLeaderboardDetailsResponseBP(), OnCompletedRequest);
}

// Droptables
void ULootLockerSDKManager::ComputeAndLockDropTable(const int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TableId, FLootLockerComputeAndLockDropTableResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PickDropsFromDropTable(const TArray<int> Picks, const  int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    FLootLockerPickDropsFromDropTableRequest Request;
    Request.picks = Picks;
    ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Request, TableId, FFLootLockerPickDropsFromDropTableResponseBP(), OnCompletedRequest);
}

// Currencies

void ULootLockerSDKManager::ListCurrencies(const FLootLockerListCurrenciesResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCurrencyRequestHandler::ListCurrencies(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListCurrenciesResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyDetails(const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDetails(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CurrencyCode, FLootLockerGetCurrencyDetailsResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CurrencyCode, FLootLockerListDenominationsResponseBP(), OnCompletedRequest);
}

// Balances

void ULootLockerSDKManager::ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerBalanceRequestHandler::ListBalancesInWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, OnComplete);
}

void ULootLockerSDKManager::GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerBalanceRequestHandler::GetWalletByWalletID(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, OnComplete);
}

void ULootLockerSDKManager::GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerBalanceRequestHandler::GetWalletByHolderID(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), HolderULID, HolderType, OnComplete);
}

void ULootLockerSDKManager::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerBalanceRequestHandler::CreditBalanceToWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, CurrencyID, Amount, OnComplete);
}

void ULootLockerSDKManager::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerBalanceRequestHandler::DebitBalanceToWallet(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), WalletID, CurrencyID, Amount, OnComplete);
}

// Catalogs

void ULootLockerSDKManager::ListCatalogs(const FLootLockerListCatalogsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCatalogRequestHandler::ListCatalogs(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListCatalogsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerCatalogRequestHandler::ListCatalogItems(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CatalogKey, Count, After, FLootLockerListCatalogPricesResponseBP(), OnComplete);
}

// Entitlements
void ULootLockerSDKManager::ListEntitlements(const int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerEntitlementRequestHandler::ListEntitlements(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Count, After, FLootLockerListEntitlementsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetEntitlement(const FString& EntitlementID, FLootLockerSingleEntitlementResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerEntitlementRequestHandler::GetEntitlement(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), EntitlementID, FLootLockerSingleEntitlementResponseBP(), OnComplete);
}

// Feedback
void ULootLockerSDKManager::ListPlayerFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Player, FLootLockerListFeedbackCategoryResponseBP(), OnComplete);

}

void ULootLockerSDKManager::ListGameFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Game, FLootLockerListFeedbackCategoryResponseBP(), OnComplete);

}

void ULootLockerSDKManager::ListUGCFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), ELootLockerFeedbackType::Ugc, FLootLockerListFeedbackCategoryResponseBP(), OnComplete);

}

void ULootLockerSDKManager::SendPlayerFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Ulid, Description, CategoryID, ELootLockerFeedbackType::Player, FLootLockerSendFeedbackResponseBP(), OnComplete);

}

void ULootLockerSDKManager::SendGameFeedback(const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), "", Description, CategoryID, ELootLockerFeedbackType::Game, FLootLockerSendFeedbackResponseBP(), OnComplete);

}

void ULootLockerSDKManager::SendUGCFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Ulid, Description, CategoryID, ELootLockerFeedbackType::Ugc, FLootLockerSendFeedbackResponseBP(), OnComplete);

}

// Metadata

void ULootLockerSDKManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, -1, -1, FString(), TArray<FString>(), IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, -1, -1, FString(), Tags, IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::ListMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const FLootLockerGetMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::GetMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, Key, IgnoreFiles, FLootLockerGetMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetMultisourceMetadata(const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const FLootLockerGetMultisourceMetadataResponseDelegate& OnComplete, const bool IgnoreFiles, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::GetMultisourceMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), SourcesAndKeysToGet, IgnoreFiles, FLootLockerGetMultisourceMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseDelegate& OnComplete, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMetadataRequestHandler::SetMetadata(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Source, SourceID, MetadataToActionsToPerform, FLootLockerSetMetadataResponseBP(), OnComplete);
}

// Followers
void ULootLockerSDKManager::ListFollowers(const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowers(const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowersPaginated(const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowersPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Cursor, Count, FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowersPaginated(const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowersPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, Cursor, Count, FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowing(const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowing(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowing(const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowing(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowingPaginated(const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowingPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Cursor, Count, FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFollowingPaginated(const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::ListFollowingPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, Cursor, Count, FLootLockerListFollowersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::FollowPlayer(const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::FollowPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, FLootLockerFollowActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::UnfollowPlayer(const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFollowersRequestHandler::UnfollowPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerPublicId, FLootLockerFollowActionResponseBP(), OnResponseCompleted);
}

// Friends

void ULootLockerSDKManager::ListFriends(const FLootLockerListFriendsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListFriends(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListFriendsResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListFriendsPaginated(int32 Page, int32 PerPage, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListFriendsPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, FLootLockerListFriendsResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListIncomingFriendRequests(const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListIncomingFriendRequests(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListIncomingFriendRequestsResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListIncomingFriendRequestsPaginated(int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListIncomingFriendRequestsPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, FLootLockerListIncomingFriendRequestsResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListOutgoingFriendRequests(const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListOutgoingFriendRequests(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListOutgoingFriendRequestsResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListOutgoingFriendRequestsPaginated(int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListOutgoingFriendRequestsPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, FLootLockerListOutgoingFriendRequestsResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::SendFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::SendFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::DeleteFriend(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::DeleteFriend(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::CancelOutgoingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::CancelOutgoingFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::AcceptIncomingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::AcceptIncomingFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::DeclineIncomingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::DeclineIncomingFriendRequest(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListBlockedPlayers(const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListBlockedPlayers(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FLootLockerListBlockedPlayersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::ListBlockedPlayersPaginated(int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::ListBlockedPlayersPaginated(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Page, PerPage, FLootLockerListBlockedPlayersResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::GetFriend(const FString& FriendUlid, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::GetFriend(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FriendUlid, FLootLockerGetFriendResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::BlockPlayer(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::BlockPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

void ULootLockerSDKManager::UnblockPlayer(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerFriendsRequestHandler::UnblockPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), PlayerULID, FLootLockerFriendActionResponseBP(), OnResponseCompleted);
}

// Miscellaneous
void ULootLockerSDKManager::GetServerTime(const FTimeResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FTimeResponseDelegateBP(), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetLastActivePlatform(const FString& ForPlayerWithUlid /* = "" */){
    return ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid));
}

void ULootLockerSDKManager::GetGameInfo(const FGameInfoResponseDelegate& OnComplete)
{
    ULootLockerMiscellaneousRequestHandler::GetGameInfo(FGameInfoResponseDelegateBP(), OnComplete);
}
