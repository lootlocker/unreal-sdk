// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

#include "LootLockerPlatformManager.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "LootLockerSDKManager.h"

// Player State
TArray<FString> ULootLockerManager::GetActivePlayerUlids()
{
    return ULootLockerStateData::GetActivePlayerUlids();
}

void ULootLockerManager::SetPlayerUlidToInactive(const FString& PlayerUlid)
{
    return ULootLockerStateData::SetPlayerUlidToInactive(PlayerUlid);
}

void ULootLockerManager::SetAllPlayersToInactive()
{
    ULootLockerStateData::SetAllPlayersToInactive();
}

void ULootLockerManager::SetAllPlayersToInactiveExceptForPlayer(const FString& PlayerUlid)
{
    ULootLockerStateData::SetAllPlayersToInactiveExceptForPlayer(PlayerUlid);
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

void ULootLockerManager::ClearAllPlayerCachesExceptForPlayer(const FString& PlayerUlid)
{
    ULootLockerStateData::ClearAllSavedStatesExceptForPlayer(PlayerUlid);
}

// Authentication
void ULootLockerManager::StartSessionManual(const FString& SessionToken, const FString& PlayerUlid,
    FLootLockerPlatformRepresentation CurrentPlatform, const FString& RefreshToken, const FString& PlayerIdentifier, const FString& PlayerPublicUid, const FString& PlayerName,
    const FString& WhiteLabelEmail, const FString& WhiteLabelToken, const FString& LastSignIn, const FString& PlayerCreatedAt, const FLootLockerSessionOptionals& SessionOptionals)
{
    FLootLockerPlayerData Data = FLootLockerPlayerData::Create(SessionToken, RefreshToken, PlayerIdentifier, PlayerUlid, PlayerPublicUid, PlayerName, WhiteLabelEmail, WhiteLabelToken, CurrentPlatform, LastSignIn, PlayerCreatedAt, SessionOptionals);
    ULootLockerStateData::SavePlayerData(Data);
}

void ULootLockerManager::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
#pragma warning(disable : 4996)
    ULootLockerSDKManager::StartPlaystationNetworkSession(PsnOnlineId, FLootLockerSessionResponse::CreateLambda([OnStartedSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
#pragma warning(default : 4996)
}

void ULootLockerManager::VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, const FAuthResponseBP& OnCompletedRequest, int PsnIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkSession(AuthCode, AccountID, FLootLockerSessionResponse::CreateLambda([OnCompletedRequest](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), PsnIssuerId, Optionals);
}

void ULootLockerManager::VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, const FAuthResponseBP& OnCompletedRequest, int EnvIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkV3Session(AuthCode, FLootLockerSessionResponse::CreateLambda([OnCompletedRequest](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), EnvIssuerId, Optionals);
}

void ULootLockerManager::StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartAndroidSession(DeviceId, FLootLockerSessionResponse::CreateLambda([OnStartedSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartAmazonLunaSession(AmazonLunaGuid, FLootLockerSessionResponse::CreateLambda([OnStartedSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FString& SteamAppId, const FAuthResponseBP& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartSteamSessionUsingTicket(SteamSessionTicket, FLootLockerSessionResponse::CreateLambda([OnCompletedRequest](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), SteamAppId, Optionals);
}

void ULootLockerManager::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnStartedNintendoSwitchSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartNintendoSwitchSession(NSAIdToken, FLootLockerSessionResponse::CreateLambda([OnStartedNintendoSwitchSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedNintendoSwitchSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnStartedXboxSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartXboxSession(XboxUserToken, FLootLockerSessionResponse::CreateLambda([OnStartedXboxSessionCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedXboxSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnStartedAppleSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartAppleSession(AuthorizationCode, FLootLockerAppleSessionResponseDelegate::CreateLambda([OnStartedAppleSessionCompleted](const FLootLockerAppleSessionResponse& Response) {
        OnStartedAppleSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshAppleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshAppleSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerAppleSessionResponseDelegate::CreateLambda([OnRefreshAppleSessionCompleted](const FLootLockerAppleSessionResponse& Response) {
        OnRefreshAppleSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, FLootLockerAppleGameCenterSessionResponseDelegate::CreateLambda([OnStartedAppleGameCenterSessionCompleted](const FLootLockerAppleGameCenterSessionResponse& Response) {
        OnStartedAppleGameCenterSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshAppleGameCenterSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshAppleGameCenterSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerAppleGameCenterSessionResponseDelegate::CreateLambda([OnRefreshAppleGameCenterSessionCompleted](const FLootLockerAppleGameCenterSessionResponse& Response) {
        OnRefreshAppleGameCenterSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartGoogleSession(IdToken, FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnStartedGoogleSessionRequestCompleted](const FLootLockerGoogleSessionResponse& Response) {
        OnStartedGoogleSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartGoogleSessionForPlatform(IdToken, Platform, FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnStartedGoogleSessionRequestCompleted](const FLootLockerGoogleSessionResponse& Response) {
        OnStartedGoogleSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshGoogleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshGoogleSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnRefreshGoogleSessionCompleted](const FLootLockerGoogleSessionResponse& Response) {
        OnRefreshGoogleSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartGooglePlayGamesSession(const FString& AuthCode, const FGooglePlayGamesSessionResponseBP& OnStartedGooglePlayGamesSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartGooglePlayGamesSession(AuthCode, FLootLockerGooglePlayGamesSessionResponseDelegate::CreateLambda([OnStartedGooglePlayGamesSessionRequestCompleted](const FLootLockerGooglePlayGamesSessionResponse& Response) {
        OnStartedGooglePlayGamesSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshGooglePlayGamesSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGooglePlayGamesSessionResponseBP& OnRefreshGooglePlayGamesSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshGooglePlayGamesSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerGooglePlayGamesSessionResponseDelegate::CreateLambda([OnRefreshGooglePlayGamesSessionCompleted](const FLootLockerGooglePlayGamesSessionResponse& Response) {
        OnRefreshGooglePlayGamesSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartEpicSession(IdToken, FLootLockerEpicSessionResponseDelegate::CreateLambda([OnStartedEpicSessionRequestCompleted](const FLootLockerEpicSessionResponse& Response) {
        OnStartedEpicSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshEpicSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshEpicSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerEpicSessionResponseDelegate::CreateLambda([OnRefreshEpicSessionCompleted](const FLootLockerEpicSessionResponse& Response) {
        OnRefreshEpicSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartMetaSession(UserId, Nonce, FLootLockerMetaSessionResponseDelegate::CreateLambda([OnMetaSessionRequestCompleted](const FLootLockerMetaSessionResponse& Response) {
        OnMetaSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshMetaSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshMetaSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerMetaSessionResponseDelegate::CreateLambda([OnMetaSessionRequestCompleted](const FLootLockerMetaSessionResponse& Response) {
        OnMetaSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::WhiteLabelStartSession(const FAuthResponseBP& OnStartWhiteLabelSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::WhiteLabelStartSession(FLootLockerSessionResponse::CreateLambda([OnStartWhiteLabelSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartWhiteLabelSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::WhiteLabelLoginAndStartSession(Email, Password, FLootLockerWhiteLabelLoginAndSessionResponseDelegate::CreateLambda([OnWhiteLabelLoginAndStartSessionRequestCompleted](const FLootLockerWhiteLabelLoginAndSessionResponse& Response) {
        OnWhiteLabelLoginAndStartSessionRequestCompleted.ExecuteIfBound(Response);
    }), Remember, Optionals);
}

void ULootLockerManager::WhiteLabelVerifySession(const FString& ForPlayerWithUlid, const FLootLockerVerifySessionResponseBP& OnVerifyWhiteLabelSessionRequestCompleted)
{
    ULootLockerSDKManager::WhiteLabelVerifySession(FLootLockerWhiteLabelVerifySessionDelegate::CreateLambda([OnVerifyWhiteLabelSessionRequestCompleted](const FLootLockerWhiteLabelVerifySessionResponse& Response) {
        OnVerifyWhiteLabelSessionRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    ULootLockerSDKManager::WhiteLabelRequestUserVerification(UserId, FLootLockerDefaultDelegate::CreateLambda([OnRequestWhiteLabelUserVerificationRequestCompleted](const FLootLockerResponse& Response) {
        OnRequestWhiteLabelUserVerificationRequestCompleted.ExecuteIfBound(Response);
    }));
}

void ULootLockerManager::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    ULootLockerSDKManager::WhiteLabelRequestUserVerificationByEmail(Email, FLootLockerDefaultDelegate::CreateLambda([OnRequestWhiteLabelUserVerificationRequestCompleted](const FLootLockerResponse& Response) {
        OnRequestWhiteLabelUserVerificationRequestCompleted.ExecuteIfBound(Response);
    }));
}

void ULootLockerManager::WhiteLabelResetPassword(const FString& Email, const FLootLockerDefaultResponseBP& OnResetWhiteLabelPasswordRequestCompleted)
{
    ULootLockerSDKManager::WhiteLabelRequestPasswordReset(Email, FLootLockerDefaultDelegate::CreateLambda([OnResetWhiteLabelPasswordRequestCompleted](const FLootLockerResponse& Response) {
        OnResetWhiteLabelPasswordRequestCompleted.ExecuteIfBound(Response);
    }));
}

void ULootLockerManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelLoginRequestCompleted, const bool Remember /* = false */)
{
    ULootLockerSDKManager::WhiteLabelLogin(Email, Password, FLootLockerLoginResponseDelegate::CreateLambda([OnWhiteLabelLoginRequestCompleted](const FLootLockerLoginResponse& Response) {
        OnWhiteLabelLoginRequestCompleted.ExecuteIfBound(Response);
    }), Remember);
}

void ULootLockerManager::WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelAccountCreationRequestCompleted)
{
    ULootLockerSDKManager::WhiteLabelCreateAccount(Email, Password, FLootLockerLoginResponseDelegate::CreateLambda([OnWhiteLabelAccountCreationRequestCompleted](const FLootLockerLoginResponse& Response) {
        OnWhiteLabelAccountCreationRequestCompleted.ExecuteIfBound(Response);
    }));
}

void ULootLockerManager::GuestLogin(const FAuthResponseBP& OnCompletedRequestBP, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::GuestLogin(FLootLockerSessionResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), PlayerIdentifier, Optionals);
}

void ULootLockerManager::StartDiscordSession(const FString& AccessToken, const FDiscordSessionResponseBP& OnStartedDiscordSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::StartDiscordSession(AccessToken, FLootLockerDiscordSessionResponseDelegate::CreateLambda([OnStartedDiscordSessionRequestCompleted](const FLootLockerDiscordSessionResponse& Response) {
        OnStartedDiscordSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::RefreshDiscordSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FDiscordSessionResponseBP& OnRefreshDiscordSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    ULootLockerSDKManager::RefreshDiscordSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerDiscordSessionResponseDelegate::CreateLambda([OnRefreshDiscordSessionCompleted](const FLootLockerDiscordSessionResponse& Response) {
        OnRefreshDiscordSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

void ULootLockerManager::VerifyPlayer(const FString& ForPlayerWithUlid, const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform /*= FString()*/)
{
#pragma warning(disable : 4996)
    ULootLockerSDKManager::VerifyPlayer(PlatformToken, FLootLockerDefaultDelegate::CreateLambda([OnVerifyPlayerRequestCompleted](const FLootLockerResponse& Response)
    {
        OnVerifyPlayerRequestCompleted.ExecuteIfBound(Response);
    }), Platform, ForPlayerWithUlid);
#pragma warning(default : 4996)
}

void ULootLockerManager::EndSession(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted)
{
    ULootLockerSDKManager::EndSession(FLootLockerDefaultDelegate::CreateLambda([OnEndSessionRequestCompleted](const FLootLockerResponse& Response)
    {
        OnEndSessionRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

//==================================================
// Connected Accounts
//==================================================
void ULootLockerManager::ListConnectedAccounts(const FString& ForPlayerWithUlid, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ListConnectedAccounts(FLootLockerListConnectedAccountsResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerListConnectedAccountsResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DisconnectAccount(const FString& ForPlayerWithUlid, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::DisconnectAccount(AccountToDisconnect, FLootLockerDefaultDelegate::CreateLambda([OnCompleteBP](const FLootLockerResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectGoogleAccount(const FString& ForPlayerWithUlid, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectGoogleAccount(IdToken, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectGoogleAccountWithPlatform(const FString& ForPlayerWithUlid, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectGoogleAccount(IdToken, Platform, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectAppleAccountByRestSignIn(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectAppleAccountByRestSignIn(AuthorizationCode, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectTwitchAccount(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectTwitchAccount(AuthorizationCode, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectEpicAccount(const FString& ForPlayerWithUlid, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectEpicAccount(Token, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectPlaystationAccount(const FString& ForPlayerWithUlid, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectPlaystationAccount(Environment, Code, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectDiscordAccount(const FString& ForPlayerWithUlid, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectDiscordAccount(Token, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ConnectRemoteSessionAccount(const FString& ForPlayerWithUlid, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::ConnectRemoteSessionAccount(Code, Nonce, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid, const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::TransferIdentityProvidersBetweenAccounts(FromPlayerWithUlid, ToPlayerWithUlid, ProvidersToTransfer, FLootLockerListConnectedAccountsResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerListConnectedAccountsResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }));
}

//==================================================
// Remote Sessions
//==================================================
FString ULootLockerManager::StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegateBP& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
    return ULootLockerSDKManager::StartRemoteSession(
        FLootLockerLeaseRemoteSessionResponseDelegate::CreateLambda([RemoteSessionLeaseInformation](FLootLockerLeaseRemoteSessionResponse Response) {
            RemoteSessionLeaseInformation.ExecuteIfBound(Response);
        }),
        FLootLockerRemoteSessionStatusPollingResponseDelegate::CreateLambda([RemoteSessionLeaseStatusUpdate](FLootLockerRemoteSessionStatusPollingResponse Response) {
            RemoteSessionLeaseStatusUpdate.ExecuteIfBound(Response);
        }),
        FLootLockerStartRemoteSessionResponseDelegate::CreateLambda([OnComplete](FLootLockerStartRemoteSessionResponse Response) {
            OnComplete.ExecuteIfBound(Response);
        }),
        PollingIntervalSeconds,
        TimeOutAfterMinutes);
}

void ULootLockerManager::CancelRemoteSessionProcess(FString ProcessID)
{
    ULootLockerSDKManager::CancelRemoteSessionProcess(ProcessID);
}

void ULootLockerManager::RefreshRemoteSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RefreshRemoteSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, 
        FLootLockerRefreshRemoteSessionResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerRefreshRemoteSessionResponse Response) {
            OnCompletedRequest.ExecuteIfBound(Response);
        }));
}

//==================================================
// Player
//==================================================
void ULootLockerManager::GetCurrentPlayerInfo(const FString& ForPlayerWithUlid, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetCurrentPlayerInfo(FLootLockerGetCurrentPlayerInfoResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerGetCurrentPlayerInfoResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListPlayerInfo(const FString& ForPlayerWithUlid, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::ListPlayerInfo(PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, FLootLockerListPlayerInfoResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerListPlayerInfoResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetInventory(const FString& ForPlayerWithUlid, const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    ULootLockerSDKManager::GetInventory(FInventoryResponse::CreateLambda([OnGetInventoryRequestCompleted](FLootLockerInventoryResponse Response)
    {
        OnGetInventoryRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetFullInventory(const FString ForPlayerWithUlid, int32 StartIndex, const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    ULootLockerSDKManager::GetFullInventory(FInventoryResponse::CreateLambda([OnGetInventoryRequestCompleted](FLootLockerInventoryResponse Response)
    {
        OnGetInventoryRequestCompleted.ExecuteIfBound(Response);
    }), StartIndex, ForPlayerWithUlid);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification(const FString& ForPlayerWithUlid, const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    ULootLockerSDKManager::CheckPlayerAssetActivationNotification(FLootLockerAssetNotificationResponse::CreateLambda([OnCheckPlayerAssetDeactivationNotificationRequestCompleted](FLootLockerPlayerAssetNotificationResponse Response)
    {
        OnCheckPlayerAssetDeactivationNotificationRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetCurrencyBalance(const FString& ForPlayerWithUlid, const FPBalanceResponseBP& OnGetCurrencyBalance)
{
    ULootLockerSDKManager::GetCurrencyBalance(FPBalanceResponse::CreateLambda([OnGetCurrencyBalance](FLootLockerBalanceResponse Response)
    {
        OnGetCurrencyBalance.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


void ULootLockerManager::InitiateDLCMigration(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnInitiateDlcMigration)
{
    ULootLockerSDKManager::InitiateDLCMigration(FResponseCallback::CreateLambda([OnInitiateDlcMigration](FLootLockerResponse Response)
    {
        OnInitiateDlcMigration.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


void ULootLockerManager::GetDLCsMigration(const FString& ForPlayerWithUlid, const FPDlcResponseBP& OnGotDlcMigration)
{
    ULootLockerSDKManager::GetDLCsMigration(FPDlcResponse::CreateLambda([OnGotDlcMigration](FLootLockerDlcResponse Response)
    {
        OnGotDlcMigration.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


void ULootLockerManager::SetProfilePrivate(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPrivate)
{
    ULootLockerSDKManager::SetProfilePrivate(FResponseCallback::CreateLambda([OnProfileSetPrivate](FLootLockerResponse Response)
    {
        OnProfileSetPrivate.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SetProfilePublic(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPublic)
{
    ULootLockerSDKManager::SetProfilePublic(FResponseCallback::CreateLambda([OnProfileSetPublic](FLootLockerResponse Response)
    {
        OnProfileSetPublic.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}
void ULootLockerManager::SetPlayerName(const FString& ForPlayerWithUlid, FString Name, const FPNameResponseBP& OnSetPlayerName)
{
    ULootLockerSDKManager::SetPlayerName(Name, FPNameResponse::CreateLambda([OnSetPlayerName](FLootLockerNameResponse Response)
    {
        OnSetPlayerName.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetPlayerName(const FString& ForPlayerWithUlid, const FPNameResponseBP& OnGetPlayerName)
{
    ULootLockerSDKManager::GetPlayerName(FPNameResponse::CreateLambda([OnGetPlayerName](FLootLockerNameResponse Response)
    {
        OnGetPlayerName.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::LookupMultiplePlayerNamesUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
#pragma warning(disable : 4996)
    ULootLockerSDKManager::LookupMultiplePlayerNamesUsingIDs(Request, FPMultiplePlayerNames::CreateLambda([OnCompletedRequest](FLootLockerMultiplePlayersNamesResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
#pragma warning(default : 4996)
}

void ULootLockerManager::LookupMultiplePlayersDataUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    ULootLockerSDKManager::LookupMultiplePlayersDataUsingIDs(Request, FPMultiplePlayerNames::CreateLambda([OnCompletedRequest](FLootLockerMultiplePlayersNamesResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::LookupMultiplePlayerNames1stPlatformIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest)
{
    ULootLockerSDKManager::LookupMultiplePlayerNames1stPlatformIDs(Request, FPMultiplePlayersPlatformIdsNames::CreateLambda([OnCompletedRequest](FLootLockerMultiplePlayersPlatformIdsResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeletePlayer(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::DeletePlayer(FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


void ULootLockerManager::UploadFile(const FString& ForPlayerWithUlid, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULootLockerSDKManager::UploadFile(Request, FLootLockerUploadFileDelegate::CreateLambda([OnComplete](FLootLockerPlayerFileResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UpdateFile(const FString& ForPlayerWithUlid, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    ULootLockerSDKManager::UpdateFile(FileId, Request, FLootLockerUploadFileDelegate::CreateLambda([OnComplete](FLootLockerPlayerFileResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListFiles(const FString& ForPlayerWithUlid, const FLootLockerFileListBP& OnComplete)
{
    ULootLockerSDKManager::ListFiles(FLootLockerFileListDelegate::CreateLambda([OnComplete](FLootLockerFileListResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListOtherPlayersPublicFiles(const FString& ForPlayerWithUlid, const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP)
{
    ULootLockerSDKManager::ListOtherPlayersPublicFiles(PlayerID, FLootLockerFileListDelegate::CreateLambda([OnCompleteBP](FLootLockerFileListResponse Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetSingleFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerUploadFileBP& OnComplete)
{
    ULootLockerSDKManager::GetSingleFile(FileID, FLootLockerUploadFileDelegate::CreateLambda([OnComplete](FLootLockerPlayerFileResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeletePlayerFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerFileDeletedBP& OnComplete)
{
    ULootLockerSDKManager::DeletePlayerFile(FileID, FLootLockerFileDeletedDelegate::CreateLambda([OnComplete](FLootLockerResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Player Progressions
void ULootLockerManager::GetPlayerProgressions(const FString& ForPlayerWithUlid, const int32 Count /*= -1*/, const FString& After /*= ""*/, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetPlayerProgressions(Count, After, FLootLockerPaginatedPlayerProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetPlayerProgression(ProgressionKey, FLootLockerPlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddPointsToPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::AddPointsToPlayerProgression(ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SubtractPointsFromPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::SubtractPointsFromPlayerProgression(ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ResetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::ResetPlayerProgression(ProgressionKey, FLootLockerPlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeletePlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerSDKManager::DeletePlayerProgression(ProgressionKey, FLootLockerDeleteProgressionDelegate::CreateLambda([OnCompletedRequest](const FLootLockerResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetOtherPlayersProgressions(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetOtherPlayersProgressions(PlayerUlid, Count, After, FLootLockerPaginatedPlayerProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetOtherPlayersProgression(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetOtherPlayersProgression(PlayerUlid, ProgressionKey, FLootLockerPlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Heroes
void ULootLockerManager::GetGameHeroes(const FString& ForPlayerWithUlid, const FLootLockerGameHeroListBP& OnCompleteBP)
{
    ULootLockerSDKManager::GetGameHeroes(FLootLockerGameHeroListDelegate::CreateLambda([OnCompleteBP](const FLootLockerGameHeroListResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListPlayerHeroes(const FString& ForPlayerWithUlid, const FLootLockerHeroListBP& OnCompleteBP)
{
    ULootLockerSDKManager::ListPlayerHeroes(FLootLockerHeroListDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroListResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListOtherPlayersHeroesBySteamID64(const FString& ForPlayerWithUlid, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP)
{
    ULootLockerSDKManager::ListOtherPlayersHeroesBySteamID64(SteamID64, FLootLockerHeroListDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroListResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::CreateHero(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerSDKManager::CreateHero(Request, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::CreateHeroWithVariation(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerSDKManager::CreateHeroWithVariation(Request, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerSDKManager::GetHero(HeroID, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetOtherPlayersDefaultHeroBySteamID64(const FString& ForPlayerWithUlid, const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerSDKManager::GetOtherPlayersDefaultHeroBySteamID64(SteamID64, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UpdateHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    ULootLockerSDKManager::UpdateHero(HeroID, Request, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::DeleteHero(HeroID, FLLHeroDefaultResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetHeroInventory(const FString& ForPlayerWithUlid, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::GetHeroInventory(HeroID, FInventoryResponse::CreateLambda([OnCompleteBP](const FLootLockerInventoryResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::GetHeroLoadout(HeroID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetOtherPlayersHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::GetOtherPlayersHeroLoadout(HeroID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::AddAssetToHeroLoadout(HeroID, AssetInstanceID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddGlobalAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::AddGlobalAssetToHeroLoadout(HeroID, AssetID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddGlobalAssetVariationToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::AddGlobalAssetVariationToHeroLoadout(HeroID, AssetID, AssetVariationID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::RemoveAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    ULootLockerSDKManager::RemoveAssetToHeroLoadout(HeroID, AssetInstanceID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Character

void ULootLockerManager::GetCharacterLoadout(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    ULootLockerSDKManager::GetCharacterLoadout(FCharacterLoadoutResponse::CreateLambda([OnGetCharacterLoadoutRequestCompleted](const FLootLockerCharacterLoadoutResponse& Response) {
        OnGetCharacterLoadoutRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UpdateCharacter(const FString& ForPlayerWithUlid, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::UpdateCharacter(CharacterId, IsDefault, Name, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequest](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::CreateCharacter(const FString& ForPlayerWithUlid, bool IsDefault, FString CharacterName, FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::CreateCharacter(IsDefault, CharacterName, CharacterTypeId, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteCharacter(const FString& ForPlayerWithUlid, int CharacterId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::DeleteCharacter(CharacterId, FLootLockerCharacterDefaultResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListCharacterTypes(const FString& ForPlayerWithUlid, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::ListCharacterTypes(FPLootLockerListCharacterTypesResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerListCharacterTypesResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListPlayerCharacters(const FString& ForPlayerWithUlid, const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::ListPlayerCharacters(FPLootLockerListPlayerCharactersResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerListPlayerCharactersResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::EquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerSDKManager::EquipAssetToDefaultCharacter(InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnEquipAssetToDefaultCharacterRequestCompleted](const FLootLockerResponse& Response) {
        OnEquipAssetToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::EquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerSDKManager::EquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId, FLootLockerCharacterDefaultResponse::CreateLambda([OnEquipAssetToCharacterByIdRequestCompleted](const FLootLockerResponse& Response) {
        OnEquipAssetToCharacterByIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::EquipAssetToCharacterByIdAndInstance(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerSDKManager::EquipAssetToCharacterById(CharacterId, InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnEquipAssetToCharacterByIdRequestCompleted](const FLootLockerResponse& Response) {
        OnEquipAssetToCharacterByIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnUnEquipAssetToDefaultCharacterRequestCompleted](const FLootLockerResponse& Response) {
        OnUnEquipAssetToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UnEquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    ULootLockerSDKManager::UnEquipAssetToCharacterById(CharacterId, InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnUnEquipAssetToCharacterByIdRequestCompleted](const FLootLockerResponse& Response) {
        OnUnEquipAssetToCharacterByIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(FCharacterLoadoutResponse::CreateLambda([OnGetCurrentLoadoutToDefaultCharacterRequestCompleted](const FLootLockerCharacterLoadoutResponse& Response) {
        OnGetCurrentLoadoutToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/)
{
    ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId, FCharacterLoadoutResponse::CreateLambda([OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted](const FLootLockerCharacterLoadoutResponse& Response) {
        OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), OtherPlayerPlatform, ForPlayerWithUlid);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(FContextDelegate::CreateLambda([OnGetEquipableContextsToDefaultCharacterRequestCompleted](const FLootLockerGetContextResponse& Response) {
        OnGetEquipableContextsToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetEquipableContextsByCharacterId(const FString& ForPlayerWithUlid, int OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    ULootLockerSDKManager::GetEquipableContextsByCharacterId(OtherCharacterId, FContextDelegate::CreateLambda([OnGetEquipableContextsByCharacterIdRequestCompleted](const FLootLockerGetContextResponse& Response) {
        OnGetEquipableContextsByCharacterIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetOtherPlayersCharacterLoadouts(const FString& ForPlayerWithUlid, const FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetOtherPlayersCharacterLoadouts(OtherPlayerId, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequest](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid, OtherPlayerPlatform);
}

void ULootLockerManager::GetOtherPlayersCharacterLoadoutsByUid(const FString& ForPlayerWithUlid, const FString& OtherPlayerUid, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetOtherPlayersCharacterLoadoutsByUid(OtherPlayerUid, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequest](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Character Progressions
void ULootLockerManager::GetCharacterProgressions(const FString& ForPlayerWithUlid, const int32& CharacterId, const int32 Count /*=-1*/, const FString& After /*=""*/, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetCharacterProgressions(CharacterId, Count, After, FLootLockerPaginatedCharacterProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedCharacterProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetCharacterProgression(CharacterId, ProgressionKey, FLootLockerCharacterProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddPointsToCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::AddPointsToCharacterProgression(CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SubtractPointsFromCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::SubtractPointsFromCharacterProgression(CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ResetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::ResetCharacterProgression(CharacterId, ProgressionKey, FLootLockerCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerSDKManager::DeleteCharacterProgression(CharacterId, ProgressionKey, FLootLockerDeleteProgressionDelegate::CreateLambda([OnCompletedRequest](const FLootLockerResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Persistent Storage
void ULootLockerManager::GetEntirePersistentStorage(const FString& ForPlayerWithUlid, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    ULootLockerSDKManager::GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegate::CreateLambda([OnPersistentStorageItemsRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnPersistentStorageItemsRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    ULootLockerSDKManager::GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegate::CreateLambda([OnPersistentStorageItemRequestCompleted](FLootLockerPersistentStorageItemResponse Response)
    {
        OnPersistentStorageItemRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddItemsToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    ULootLockerSDKManager::AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegate::CreateLambda([OnPersistentStorageItemsAddRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnPersistentStorageItemsAddRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddItemToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted)
{
    ULootLockerSDKManager::AddItemsToPersistentStorage(Item, FPersistentStorageItemResponseDelegate::CreateLambda([OnPersistentStorageItemAddRequestCompleted](FLootLockerPersistentStorageItemResponse Response)
    {
        OnPersistentStorageItemAddRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted)
{
    ULootLockerSDKManager::DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegate::CreateLambda([OnPersistentStorageItemDeleteRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnPersistentStorageItemDeleteRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetPlayerPersistentStorage(const FString& ForPlayerWithUlid, const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted)
{
    ULootLockerSDKManager::GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegate::CreateLambda([OnGetPlayerPersistentStorageRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnGetPlayerPersistentStorageRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetContexts(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetContextsRequestCompleted)
{
    ULootLockerSDKManager::GetContexts(FContextDelegate::CreateLambda([OnGetContextsRequestCompleted](const FLootLockerGetContextResponse& Response)
    {
        OnGetContextsRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetAssets(const FString& ForPlayerWithUlid, const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    ULootLockerSDKManager::GetAssets(FAssetsResponseDelegate::CreateLambda([OnGetAssetsRequestCompleted](const FLootLockerGetAssetsResponse& Response)
    {
        OnGetAssetsRequestCompleted.ExecuteIfBound(Response);
    }), StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, ForPlayerWithUlid);
}

void ULootLockerManager::ListAssetsWithDefaultParameters(const FString& ForPlayerWithUlid, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest)
{
    ListAssets(ForPlayerWithUlid, FLootLockerListSimpleAssetsRequest(), 0, 0, ELootLockerOrderAssetListBy::None, ELootLockerOrderAssetListDirection::None, OnCompletedRequest);
}

void ULootLockerManager::ListAssets(const FString& ForPlayerWithUlid, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, ELootLockerOrderAssetListBy OrderBy, ELootLockerOrderAssetListDirection OrderDirection, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::ListAssets(Request, FListSimpleAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerListSimpleAssetsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), PerPage, Page, OrderBy, OrderDirection, ForPlayerWithUlid);
}

void ULootLockerManager::GetAssetsByIds(const FString& ForPlayerWithUlid, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted)
{
    ULootLockerSDKManager::GetAssetsByIds(AssetIds, FAssetsResponseDelegate::CreateLambda([OnGetAssetsByIdsRequestCompleted](const FLootLockerGetAssetsResponse& Response)
    {
        OnGetAssetsByIdsRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetAssetBones(const FString& ForPlayerWithUlid, const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted)
{
    ULootLockerSDKManager::GetAssetBones(FAssetBonesResponseDelegate::CreateLambda([OnGetAssetBonesRequestCompleted](const FLootLockerGetAssetBonesResponse& Response)
    {
        OnGetAssetBonesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetFavouriteAssetIndices(const FString& ForPlayerWithUlid, const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted)
{
    ULootLockerSDKManager::GetFavouriteAssetIndices(FGetFavouriteAssetIndicesResponseDelegate::CreateLambda([OnGetFavouriteAssetIndicesRequestCompleted](const FLootLockerGetFavouriteAssetIndicesResponse& Response)
    {
        OnGetFavouriteAssetIndicesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddAssetToFavourites(const FString& ForPlayerWithUlid, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted)
{
    ULootLockerSDKManager::AddAssetToFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegate::CreateLambda([OnAddAssetToFavouritesRequestCompleted](const FLootLockerGetFavouriteAssetIndicesResponse& Response)
    {
        OnAddAssetToFavouritesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::RemoveAssetFromFavourites(const FString& ForPlayerWithUlid, int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted)
{
    ULootLockerSDKManager::RemoveAssetFromFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegate::CreateLambda([OnRemoveAssetFromFavouritesRequestCompleted](const FLootLockerGetFavouriteAssetIndicesResponse& Response)
    {
        OnRemoveAssetFromFavouritesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetUniversalAssets(const FString& ForPlayerWithUlid, int After, int ItemsCount, const FUniversalAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetUniversalAssets(After, ItemsCount, FUniversalAssetResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerUniversalAssetsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GrantAssetWithVariationToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GrantAssetToPlayerInventory(AssetID, AssetVariationID, AssetRentalOptionID, FGrantAssetResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerGrantAssetResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


// Asset Instances
void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnGetAllKeyValuePairsForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnGetAllKeyValuePairsForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemResponseDelegate::CreateLambda([OnGetAKeyValuePairByIdForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemResponse& Response)
        {
            OnGetAKeyValuePairByIdForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::CreateAKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnCreateAKeyValuePairForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnCreateAKeyValuePairForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
{
    ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemResponseDelegate::CreateLambda([OnUpdateAKeyValuePairByIdForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemResponse& Response)
        {
            OnUpdateAKeyValuePairByIdForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted)
{
    ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnDeleteAKeyValuePairByIdForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnDeleteAKeyValuePairByIdForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::InspectLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted)
{
    ULootLockerSDKManager::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegate::CreateLambda([OnInspectLootBoxCompleted](const FLootLockerLootBoxContentResponse& Response)
        {
            OnInspectLootBoxCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::OpenLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted)
{
    ULootLockerSDKManager::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegate::CreateLambda([OnOpenLootBoxCompleted](const FLootLockerOpenLootBoxResponse& Response)
        {
            OnOpenLootBoxCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteAssetInstanceFromPlayerInventory(const FString& ForPlayerWithUlid, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted)
{
    ULootLockerSDKManager::DeleteAssetInstanceFromPlayerInventory(AssetInstanceID, FDeleteAssetInstanceResponseDelegate::CreateLambda([OnCompleted](const FLootLockerDeleteAssetInstanceResponse& Response)
        {
            OnCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

// User Generated Content - Asset Candidates

void ULootLockerManager::CreateAssetCandidate(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerSDKManager::CreateAssetCandidate(AssetCandidateData, FCreateAssetCandidateResponseDelegate::CreateLambda([OnCreateAssetCandidateCompleted](FLootLockerCreateAssetCandidateResponse Response)
        {
            OnCreateAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::CreateAssetCandidateAndMarkComplete(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerSDKManager::CreateAssetCandidateAndMarkComplete(AssetCandidateData, FCreateAssetCandidateResponseDelegate::CreateLambda([OnCreateAssetCandidateCompleted](FLootLockerCreateAssetCandidateResponse Response)
        {
            OnCreateAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::UpdateAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    ULootLockerSDKManager::UpdateAssetCandidate(AssetCandidateId, AssetCandidateData, FAssetCandidateResponseDelegate::CreateLambda([OnUpdateAssetCandidateCompleted](FLootLockerAssetCandidateResponse Response)
        {
            OnUpdateAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted)
{
    ULootLockerSDKManager::DeleteAssetCandidate(AssetCandidateId, FResponseCallback::CreateLambda([OnDeleteAssetCandidateCompleted](FLootLockerResponse Response)
        {
            OnDeleteAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetAllAssetCandidates(const FString& ForPlayerWithUlid, const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted)
{
    ULootLockerSDKManager::GetAllAssetCandidates(FAssetCandidatesResponseDelegate::CreateLambda([OnGetAllAssetCandidatesCompleted](FLootLockerAssetCandidatesResponse Response)
        {
            OnGetAllAssetCandidatesCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted)
{
    ULootLockerSDKManager::GetAssetCandidate(AssetCandidateId, FAssetCandidateResponseDelegate::CreateLambda([OnGetAssetCandidateCompleted](FLootLockerAssetCandidateResponse Response)
        {
            OnGetAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::AddFileToAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegateBP& OnAddFileToAssetCandidateCompleted)
{
    ULootLockerSDKManager::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, FAssetCandidateResponseDelegate::CreateLambda([OnAddFileToAssetCandidateCompleted](FLootLockerAssetCandidateResponse Response)
        {
            OnAddFileToAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteFileFromAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted)
{
    ULootLockerSDKManager::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, FResponseCallback::CreateLambda([OnDeleteFileFromAssetCandidateCompleted](FLootLockerResponse Response)
        {
            OnDeleteFileFromAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

// Progressions
void ULootLockerManager::GetProgressions(const FString& ForPlayerWithUlid, const int32 Count /*= -1*/, const FString& After /*=""*/, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetProgressions(Count, After, FLootLockerPaginatedProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedProgressionsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetProgression(ProgressionKey, FLootLockerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetProgressionTiers(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32 Count /*=-1*/, const int32 After /*=-1*/, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetProgressionTiers(ProgressionKey, Count, After, FLootLockerPaginatedProgressionTiersResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedProgressionTiersResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

//Instance progression

void ULootLockerManager::GetInstanceProgressions(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetInstanceProgressions(AssetInstanceId, Count, After, FLootLockerPaginatedInstanceProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedInstanceProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AddPointsToInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::AddPointsToInstanceProgression(AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SubtractPointsFromInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::SubtractPointsFromInstanceProgression(AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ResetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::ResetInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    ULootLockerSDKManager::DeleteInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerDeleteProgressionDelegate::CreateLambda([OnCompletedRequest](const FLootLockerResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Missions
void ULootLockerManager::GetAllMissions(const FString& ForPlayerWithUlid, const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted)
{
    ULootLockerSDKManager::GetAllMissions(FMissionsResponseDelegate::CreateLambda([OnGetAllMissionsCompleted](FLootLockerMissionsResponse Response)
    {
        OnGetAllMissionsCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetMission(const FString& ForPlayerWithUlid, int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted)
{
    ULootLockerSDKManager::GetMission(MissionId, FMissionResponseDelegate::CreateLambda([OnGetMissionCompleted](FLootLockerMissionResponse Response)
    {
        OnGetMissionCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::StartMission(const FString& ForPlayerWithUlid, int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted)
{
    ULootLockerSDKManager::StartMission(MissionId, FStartMissionResponseDelegate::CreateLambda([OnStartMissionCompleted](FLootLockerStartMissionResponse Response)
    {
        OnStartMissionCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::FinishMission(const FString& ForPlayerWithUlid, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted)
{
    ULootLockerSDKManager::FinishMission(MissionId, MissionData, FFinishMissionResponseDelegate::CreateLambda([OnFinishMissionCompleted](FLootLockerFinishMissionResponse Response)
    {
        OnFinishMissionCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetMaps(const FString& ForPlayerWithUlid, const FGetMapsResponseDelegateBP& OnGetMapsCompleted)
{
    ULootLockerSDKManager::GetMaps(FGetMapsResponseDelegate::CreateLambda([OnGetMapsCompleted](FLootLockerGetMapsResponse Response)
        {
            OnGetMapsCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::ActivateRentalAsset(const FString& ForPlayerWithUlid, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    ULootLockerSDKManager::ActivateRentalAsset(AssetInstanceId, FActivateRentalAssetResponseDelegate::CreateLambda([OnActivateRentalAssetCompleted](FLootLockerActivateRentalAssetResponse Response)
        {
            OnActivateRentalAssetCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::LootLockerPurchaseSingleCatalogItem(const FString& ForPlayerWithUlid, const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    LootLockerPurchaseCatalogItems(ForPlayerWithUlid, WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest);
}

void ULootLockerManager::LootLockerPurchaseCatalogItems(const FString& ForPlayerWithUlid, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::LootLockerPurchaseCatalogItems(WalletId, ItemsToPurchase, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RedeemAppleAppStorePurchaseForPlayer(TransactionId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), Sandboxed, ForPlayerWithUlid);
}

void ULootLockerManager::RedeemAppleAppStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RedeemAppleAppStorePurchaseForClass(ClassId, TransactionId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), Sandboxed, ForPlayerWithUlid);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForPlayer(ProductId, PurchaseToken, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::RedeemGooglePlayStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForClass(ClassId, ProductId, PurchaseToken, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::RedeemEpicStorePurchase(const FString& ForPlayerWithUlid, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RedeemEpicStorePurchase(AccountId, BearerToken, EntitlementIds, SandboxId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::RedeemEpicStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::RedeemEpicStorePurchaseForCharacter(CharacterId, AccountId, BearerToken, EntitlementIds, SandboxId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

#ifdef LOOTLOCKER_BETA_PLAYSTATION_IAP
// void ULootLockerManager::RedeemPlayStationStorePurchase(const FString& ForPlayerWithUlid, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedRequest)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, OnCompletedRequest);
// }

// void ULootLockerManager::RedeemPlayStationStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedRequest)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, OnCompletedRequest);
// }
#endif

void ULootLockerManager::BeginSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::BeginSteamPurchaseRedemption(SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegate::CreateLambda([OnCompletedRequest](FLootLockerBeginSteamPurchaseRedemptionResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::BeginSteamPurchaseRedemptionForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::BeginSteamPurchaseRedemptionForClass(ClassId, SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegate::CreateLambda([OnCompletedRequest](FLootLockerBeginSteamPurchaseRedemptionResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::QuerySteamPurchaseRedemptionStatus(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest)
{
    ULootLockerSDKManager::QuerySteamPurchaseRedemptionStatus(EntitlementId, FLootLockerQuerySteamPurchaseRedemptionStatusDelegate::CreateLambda([OnCompletedRequest](FLootLockerQuerySteamPurchaseRedemptionStatusResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::FinalizeSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::FinalizeSteamPurchaseRedemption(EntitlementId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

//Triggers
void ULootLockerManager::InvokeTriggersByKey(const FString& ForPlayerWithUlid, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnComplete)
{
    ULootLockerSDKManager::InvokeTriggersByKey(KeysToInvoke, FLootLockerInvokeTriggersByKeyResponseDelegate::CreateLambda([OnComplete](FLootLockerInvokeTriggersByKeyResponse Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

//Notifications
void ULootLockerManager::ListNotificationsWithDefaultParameters(const FString& ForPlayerWithUlid, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListNotificationsWithDefaultParameters(FLootLockerListNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerListNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListNotifications(const FString& ForPlayerWithUlid, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListNotifications(ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, FLootLockerListNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerListNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListNotificationsWithPriority(const FString& ForPlayerWithUlid, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListNotificationsWithPriority(WithPriority, ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, FLootLockerListNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerListNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

bool ULootLockerManager::TryGetContentBodyAsString(const FLootLockerNotificationContent& Content, FString& OutValue)
{
    return Content.TryGetContentBodyAsString(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsFloat(const FLootLockerNotificationContent& Content, float& OutValue)
{
    return Content.TryGetContentBodyAsFloat(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsInteger(const FLootLockerNotificationContent& Content, int& OutValue)
{
    return Content.TryGetContentBodyAsInteger(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsBool(const FLootLockerNotificationContent& Content, bool& OutValue)
{
    return Content.TryGetContentBodyAsBool(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsFloatArray(const FLootLockerNotificationContent& Content, TArray<float>& OutValue)
{
    return Content.TryGetContentBodyAsFloatArray(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsIntegerArray(const FLootLockerNotificationContent& Content, TArray<int>& OutValue)
{
    return Content.TryGetContentBodyAsIntegerArray(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsBoolArray(const FLootLockerNotificationContent& Content, TArray<bool>& OutValue)
{
    return Content.TryGetContentBodyAsBoolArray(OutValue);
}

bool ULootLockerManager::TryGetContentBodyAsRewardNotification(const FLootLockerNotificationContent& Content, FLootLockerNotificationContentRewardBody& OutValue)
{
    return Content.TryGetContentBodyAsRewardNotification(OutValue);
}

void ULootLockerManager::MarkAllNotificationsAsRead(const FString& ForPlayerWithUlid, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerSDKManager::MarkAllNotificationsAsRead(FLootLockerReadNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerReadNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::MarkNotificationsAsRead(const FString& ForPlayerWithUlid, const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerSDKManager::MarkNotificationsAsRead(Notifications, FLootLockerReadNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerReadNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::MarkNotificationsAsReadByIds(const FString& ForPlayerWithUlid, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    ULootLockerSDKManager::MarkNotificationsAsReadByIds(NotificationIDs, FLootLockerReadNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerReadNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

bool ULootLockerManager::TryGetNotificationsByIdentifyingValue(const FLootLockerListNotificationsResponse& NotificationsResponse, const FString& IdentifyingValue, TArray<FLootLockerNotification>& Notifications)
{
    return NotificationsResponse.TryGetNotificationsByIdentifyingValue(IdentifyingValue, Notifications);
}

// Broadcasts

void ULootLockerManager::ListBroadcasts(const TArray<FString>& Languages, int32 PerPage, int32 Page, const FString& ForPlayerWithUlid, const FLootLockerListBroadcastsResponseBP& OnComplete)
{
    ULootLockerBroadcastRequestHandler::ListBroadcasts(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), Languages, PerPage, Page, OnComplete);
}

// Collectables

void ULootLockerManager::GetAllCollectables(const FString& ForPlayerWithUlid, const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted)
{
    ULootLockerSDKManager::GetAllCollectables(FCollectablesResponseDelegate::CreateLambda([OnGetAllCollectablesCompleted](const FLootLockerCollectablesResponse& Response)
    {
        OnGetAllCollectablesCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::CollectItem(const FString& ForPlayerWithUlid, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted)
{
    ULootLockerSDKManager::CollectItem(Item, FCollectablesResponseDelegate::CreateLambda([OnCollectItemCompleted](const FLootLockerCollectablesResponse& Response)
    {
        OnCollectItemCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Messages
void ULootLockerManager::GetMessages(const FString& ForPlayerWithUlid, const FMessagesResponseDelegateBP& OnGetMessagesCompleted)
{
    ULootLockerMessagesRequestHandler::GetMessages(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), FMessagesResponseDelegate::CreateLambda([OnGetMessagesCompleted](FLootLockerMessagesResponse Response)
    {
        OnGetMessagesCompleted.ExecuteIfBound(Response);
    }));
}

void ULootLockerManager::ListLeaderboards(const FString& ForPlayerWithUlid, int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::ListLeaderboards(Count, After, FLootLockerListLeaderboardsResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerListLeaderboardsResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetMemberRank(const FString& ForPlayerWithUlid, FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::GetMemberRank(LeaderboardKey, MemberId, FLootLockerGetMemberRankResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetMemberRankResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetAllMemberRanks(const FString& ForPlayerWithUlid, FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::GetAllMemberRanks(MemberId, Count, After, FLootLockerGetAllMemberRanksResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetAllMemberRanksResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetByListOfMembers(const FString& ForPlayerWithUlid, TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::GetByListOfMembers(Members, LeaderboardKey, FLootLockerGetByListOfMembersResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetByListOfMembersResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetScoreList(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::GetScoreList(LeaderboardKey, Count, After, FLootLockerGetScoreListResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetScoreListResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetScoreListInitial(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    GetScoreList(ForPlayerWithUlid, LeaderboardKey, Count, -1, OnCompletedRequestBP);
}


void ULootLockerManager::SubmitScore(const FString& ForPlayerWithUlid, FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::SubmitScore(MemberId, LeaderboardKey, Score, Metadata, FLootLockerSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerSubmitScoreResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::QueryScore(const FString LeaderboardKey, const int Score, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerSDKManager::QueryScore(LeaderboardKey, Score, FLootLockerSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerSubmitScoreResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::IncrementScore(FString MemberId, const FString LeaderboardKey, const int Amount, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FString& ForPlayerWithUlid /* = "" */)
{
    ULootLockerSDKManager::IncrementScore(MemberId, LeaderboardKey, Amount, FLootLockerSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerSubmitScoreResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::ListLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::ListLeaderboardArchive(LeaderboardKey, FLootLockerLeaderboardArchiveResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerLeaderboardArchiveResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::GetLeaderboardArchive(Key, Count, After, FLootLockerLeaderboardArchiveDetailResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerLeaderboardArchiveDetailsResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

void ULootLockerManager::GetLeaderboardDetails(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::GetLeaderboardDetails(LeaderboardKey, FLootLockerLeaderboardDetailsResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerLeaderboardDetailsResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

// Drop Tables

void ULootLockerManager::ComputeAndLockDropTable(const FString& ForPlayerWithUlid, int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::ComputeAndLockDropTable(TableId, FLootLockerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerComputeAndLockDropTableResponse& Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::PickDropsFromDropTable(const FString& ForPlayerWithUlid, TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
{
    ULootLockerSDKManager::PickDropsFromDropTable(Picks, TableId, FFLootLockerPickDropsFromDropTableResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerPickDropsFromDropTableResponse& Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Currencies
void ULootLockerManager::ListCurrencies(const FString& ForPlayerWithUlid, const FLootLockerListCurrenciesResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::ListCurrencies(FLootLockerListCurrenciesResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerListCurrenciesResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetCurrencyDetails(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetCurrencyDetails(CurrencyCode, FLootLockerGetCurrencyDetailsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerGetCurrencyDetailsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetCurrencyDenominationsByCode(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnCompletedRequest)
{
    ULootLockerSDKManager::GetCurrencyDenominationsByCode(CurrencyCode, FLootLockerListDenominationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerListDenominationsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Balances

void ULootLockerManager::ListBalancesInWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListBalancesInWallet(WalletID, FLootLockerListBalancesForWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerListBalancesForWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetWalletByWalletID(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerSDKManager::GetWalletByWalletID(WalletID, FLootLockerGetWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerGetWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetWalletByHolderID(const FString& ForPlayerWithUlid, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnComplete)
{
    ULootLockerSDKManager::GetWalletByHolderID(HolderULID, HolderType, FLootLockerGetWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerGetWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::CreditBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnComplete)
{
    ULootLockerSDKManager::CreditBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerCreditWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerCreditWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DebitBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnComplete)
{
    ULootLockerSDKManager::DebitBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerDebitWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerDebitWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Catalogs

void ULootLockerManager::ListCatalogs(const FString& ForPlayerWithUlid, const FLootLockerListCatalogsResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListCatalogs(FLootLockerListCatalogsResponseDelegate::CreateLambda([OnComplete](const FLootLockerListCatalogsResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListCatalogItems(const FString& ForPlayerWithUlid, const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListCatalogItems(CatalogKey, Count, After, FLootLockerListCatalogPricesResponseDelegate::CreateLambda([OnComplete](const FLootLockerListCatalogPricesResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

TArray<FLootLockerInlinedCatalogEntry> ULootLockerManager::ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog)
{
    return ULootLockerCatalogRequestHandler::ConvertCatalogToInlineItems(Catalog);
}

// Entitlements
void ULootLockerManager::ListEntitlements(const FString& ForPlayerWithUlid, int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListEntitlements(Count, After, FLootLockerListEntitlementsResponseDelegate::CreateLambda([OnComplete](const FLootLockerEntitlementHistoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::GetEntitlement(const FString& ForPlayerWithUlid, const FString& EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnComplete)
{
    FLootLockerSingleEntitlementResponseDelegate Delegate = FLootLockerSingleEntitlementResponseDelegate::CreateLambda([OnComplete](const FLootLockerSingleEntitlementResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    });
    ULootLockerSDKManager::GetEntitlement(EntitlementID, Delegate, ForPlayerWithUlid);
}

// Feedback

void ULootLockerManager::ListPlayerFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListPlayerFeedbackCategories(FLootLockerListFeedbackCategoryResponseDelegate::CreateLambda([OnComplete](const FLootLockerFeedbackCategoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListGameFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListGameFeedbackCategories(FLootLockerListFeedbackCategoryResponseDelegate::CreateLambda([OnComplete](const FLootLockerFeedbackCategoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListUGCFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListUGCFeedbackCategories(FLootLockerListFeedbackCategoryResponseDelegate::CreateLambda([OnComplete](const FLootLockerFeedbackCategoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SendPlayerFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerSDKManager::SendPlayerFeedback(Ulid, Description, CategoryID, FLootLockerSendFeedbackResponseDelegate::CreateLambda([OnComplete](const FLootLockerResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SendGameFeedback(const FString& ForPlayerWithUlid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerSDKManager::SendGameFeedback(Description, CategoryID, FLootLockerSendFeedbackResponseDelegate::CreateLambda([OnComplete](const FLootLockerResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::SendUGCFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    ULootLockerSDKManager::SendUGCFeedback(Ulid, Description, CategoryID, FLootLockerSendFeedbackResponseDelegate::CreateLambda([OnComplete](const FLootLockerResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);

}

// Metadata

void ULootLockerManager::ListMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListMetadata(Source, SourceID, Page, PerPage, FLootLockerListMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerListMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
}

void ULootLockerManager::ListMetadataWithTags(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    ULootLockerSDKManager::ListMetadataWithTags(Source, SourceID, Tags, Page, PerPage, FLootLockerListMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerListMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
}

void ULootLockerManager::GetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnComplete)
{
    ULootLockerSDKManager::GetMetadata(Source, SourceID, Key, FLootLockerGetMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerGetMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
}

void ULootLockerManager::GetMultisourceMetadata(const FString& ForPlayerWithUlid, const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseBP& OnComplete)
{
    ULootLockerSDKManager::GetMultisourceMetadata(SourcesAndKeysToGet, FLootLockerGetMultisourceMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerGetMultisourceMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
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
    FString ValueToParse = "";
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
    ULootLockerSDKManager::SetMetadata(Source, SourceID, MetadataToActionsToPerform, FLootLockerSetMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerSetMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
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
    ULootLockerSDKManager::GetServerTime(FTimeResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerTimeResponse Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetLastActivePlatform(const FString& ForPlayerWithUlid) {
    return ULootLockerSDKManager::GetLastActivePlatform(ForPlayerWithUlid);
}

void ULootLockerManager::GetGameInfo(const FGameInfoResponseDelegateBP& OnCompletedRequestBP) {
    ULootLockerSDKManager::GetGameInfo(FGameInfoResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGameInfoResponse Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

// Followers (Unified with optional pagination parameters)
void ULootLockerManager::ListFollowersForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListFollowersPaginated(PlayerPublicUid, Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListFollowers(PlayerPublicUid, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::ListFollowers(const FString& ForPlayerWithUlid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListFollowersPaginated(Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListFollowers(FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::ListFollowingForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListFollowingPaginated(PlayerPublicUid, Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListFollowing(PlayerPublicUid, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::ListFollowing(const FString& ForPlayerWithUlid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListFollowingPaginated(Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListFollowing(FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::FollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::FollowPlayer(PlayerPublicUid, FLootLockerFollowActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFollowActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UnfollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::UnfollowPlayer(PlayerPublicUid, FLootLockerFollowActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFollowActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Friends
void ULootLockerManager::ListFriends(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListFriendsPaginated(Page, PerPage, FLootLockerListFriendsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFriendsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListFriends(FLootLockerListFriendsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFriendsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::ListIncomingFriendRequests(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListIncomingFriendRequestsPaginated(Page, PerPage, FLootLockerListIncomingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListIncomingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListIncomingFriendRequests(FLootLockerListIncomingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListIncomingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::ListOutgoingFriendRequests(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListOutgoingFriendRequestsPaginated(Page, PerPage, FLootLockerListOutgoingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListOutgoingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListOutgoingFriendRequests(FLootLockerListOutgoingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListOutgoingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::SendFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::SendFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeleteFriend(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::DeleteFriend(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::CancelOutgoingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::CancelOutgoingFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::AcceptIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::AcceptIncomingFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::DeclineIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::DeclineIncomingFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::ListBlockedPlayers(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        ULootLockerSDKManager::ListBlockedPlayersPaginated(Page, PerPage, FLootLockerListBlockedPlayersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListBlockedPlayersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        ULootLockerSDKManager::ListBlockedPlayers(FLootLockerListBlockedPlayersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListBlockedPlayersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

void ULootLockerManager::GetFriend(const FString& ForPlayerWithUlid, const FString& FriendUlid, const FLootLockerGetFriendResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::GetFriend(FriendUlid, FLootLockerGetFriendResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerGetFriendResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::BlockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::BlockPlayer(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

void ULootLockerManager::UnblockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    ULootLockerSDKManager::UnblockPlayer(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}
