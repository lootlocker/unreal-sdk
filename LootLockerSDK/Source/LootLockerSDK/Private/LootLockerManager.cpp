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

FString ULootLockerManager::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
#pragma warning(disable : 4996)
    return ULootLockerSDKManager::StartPlaystationNetworkSession(PsnOnlineId, FLootLockerSessionResponse::CreateLambda([OnStartedSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
#pragma warning(default : 4996)
}

FString ULootLockerManager::VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, const FAuthResponseBP& OnCompletedRequest, int PsnIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkSession(AuthCode, AccountID, FLootLockerSessionResponse::CreateLambda([OnCompletedRequest](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), PsnIssuerId, Optionals);
}

FString ULootLockerManager::VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, const FAuthResponseBP& OnCompletedRequest, int EnvIssuerId /*= 256*/, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::VerifyPlayerAndStartPlaystationNetworkV3Session(AuthCode, FLootLockerSessionResponse::CreateLambda([OnCompletedRequest](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), EnvIssuerId, Optionals);
}

FString ULootLockerManager::StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartAndroidSession(DeviceId, FLootLockerSessionResponse::CreateLambda([OnStartedSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartAmazonLunaSession(AmazonLunaGuid, FLootLockerSessionResponse::CreateLambda([OnStartedSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FString& SteamAppId, const FAuthResponseBP& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartSteamSessionUsingTicket(SteamSessionTicket, FLootLockerSessionResponse::CreateLambda([OnCompletedRequest](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), SteamAppId, Optionals);
}

FString ULootLockerManager::StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnStartedNintendoSwitchSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartNintendoSwitchSession(NSAIdToken, FLootLockerSessionResponse::CreateLambda([OnStartedNintendoSwitchSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedNintendoSwitchSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnStartedXboxSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartXboxSession(XboxUserToken, FLootLockerSessionResponse::CreateLambda([OnStartedXboxSessionCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartedXboxSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnStartedAppleSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartAppleSession(AuthorizationCode, FLootLockerAppleSessionResponseDelegate::CreateLambda([OnStartedAppleSessionCompleted](const FLootLockerAppleSessionResponse& Response) {
        OnStartedAppleSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshAppleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshAppleSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerAppleSessionResponseDelegate::CreateLambda([OnRefreshAppleSessionCompleted](const FLootLockerAppleSessionResponse& Response) {
        OnRefreshAppleSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, FLootLockerAppleGameCenterSessionResponseDelegate::CreateLambda([OnStartedAppleGameCenterSessionCompleted](const FLootLockerAppleGameCenterSessionResponse& Response) {
        OnStartedAppleGameCenterSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshAppleGameCenterSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshAppleGameCenterSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerAppleGameCenterSessionResponseDelegate::CreateLambda([OnRefreshAppleGameCenterSessionCompleted](const FLootLockerAppleGameCenterSessionResponse& Response) {
        OnRefreshAppleGameCenterSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartGoogleSession(IdToken, FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnStartedGoogleSessionRequestCompleted](const FLootLockerGoogleSessionResponse& Response) {
        OnStartedGoogleSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartGoogleSessionForPlatform(IdToken, Platform, FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnStartedGoogleSessionRequestCompleted](const FLootLockerGoogleSessionResponse& Response) {
        OnStartedGoogleSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshGoogleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshGoogleSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerGoogleSessionResponseDelegate::CreateLambda([OnRefreshGoogleSessionCompleted](const FLootLockerGoogleSessionResponse& Response) {
        OnRefreshGoogleSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartGooglePlayGamesSession(const FString& AuthCode, const FGooglePlayGamesSessionResponseBP& OnStartedGooglePlayGamesSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartGooglePlayGamesSession(AuthCode, FLootLockerGooglePlayGamesSessionResponseDelegate::CreateLambda([OnStartedGooglePlayGamesSessionRequestCompleted](const FLootLockerGooglePlayGamesSessionResponse& Response) {
        OnStartedGooglePlayGamesSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshGooglePlayGamesSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGooglePlayGamesSessionResponseBP& OnRefreshGooglePlayGamesSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshGooglePlayGamesSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerGooglePlayGamesSessionResponseDelegate::CreateLambda([OnRefreshGooglePlayGamesSessionCompleted](const FLootLockerGooglePlayGamesSessionResponse& Response) {
        OnRefreshGooglePlayGamesSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartEpicSession(IdToken, FLootLockerEpicSessionResponseDelegate::CreateLambda([OnStartedEpicSessionRequestCompleted](const FLootLockerEpicSessionResponse& Response) {
        OnStartedEpicSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshEpicSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshEpicSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerEpicSessionResponseDelegate::CreateLambda([OnRefreshEpicSessionCompleted](const FLootLockerEpicSessionResponse& Response) {
        OnRefreshEpicSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartMetaSession(UserId, Nonce, FLootLockerMetaSessionResponseDelegate::CreateLambda([OnMetaSessionRequestCompleted](const FLootLockerMetaSessionResponse& Response) {
        OnMetaSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshMetaSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshMetaSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerMetaSessionResponseDelegate::CreateLambda([OnMetaSessionRequestCompleted](const FLootLockerMetaSessionResponse& Response) {
        OnMetaSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::WhiteLabelStartSession(const FAuthResponseBP& OnStartWhiteLabelSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::WhiteLabelStartSession(FLootLockerSessionResponse::CreateLambda([OnStartWhiteLabelSessionRequestCompleted](const FLootLockerAuthenticationResponse& Response) {
        OnStartWhiteLabelSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::WhiteLabelLoginAndStartSession(Email, Password, FLootLockerWhiteLabelLoginAndSessionResponseDelegate::CreateLambda([OnWhiteLabelLoginAndStartSessionRequestCompleted](const FLootLockerWhiteLabelLoginAndSessionResponse& Response) {
        OnWhiteLabelLoginAndStartSessionRequestCompleted.ExecuteIfBound(Response);
    }), Remember, Optionals);
}

FString ULootLockerManager::WhiteLabelVerifySession(const FString& ForPlayerWithUlid, const FLootLockerVerifySessionResponseBP& OnVerifyWhiteLabelSessionRequestCompleted)
{
    return ULootLockerSDKManager::WhiteLabelVerifySession(FLootLockerWhiteLabelVerifySessionDelegate::CreateLambda([OnVerifyWhiteLabelSessionRequestCompleted](const FLootLockerWhiteLabelVerifySessionResponse& Response) {
        OnVerifyWhiteLabelSessionRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    return ULootLockerSDKManager::WhiteLabelRequestUserVerification(UserId, FLootLockerDefaultDelegate::CreateLambda([OnRequestWhiteLabelUserVerificationRequestCompleted](const FLootLockerResponse& Response) {
        OnRequestWhiteLabelUserVerificationRequestCompleted.ExecuteIfBound(Response);
    }));
}

FString ULootLockerManager::WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted)
{
    return ULootLockerSDKManager::WhiteLabelRequestUserVerificationByEmail(Email, FLootLockerDefaultDelegate::CreateLambda([OnRequestWhiteLabelUserVerificationRequestCompleted](const FLootLockerResponse& Response) {
        OnRequestWhiteLabelUserVerificationRequestCompleted.ExecuteIfBound(Response);
    }));
}

FString ULootLockerManager::WhiteLabelResetPassword(const FString& Email, const FLootLockerDefaultResponseBP& OnResetWhiteLabelPasswordRequestCompleted)
{
    return ULootLockerSDKManager::WhiteLabelRequestPasswordReset(Email, FLootLockerDefaultDelegate::CreateLambda([OnResetWhiteLabelPasswordRequestCompleted](const FLootLockerResponse& Response) {
        OnResetWhiteLabelPasswordRequestCompleted.ExecuteIfBound(Response);
    }));
}

FString ULootLockerManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelLoginRequestCompleted, const bool Remember /* = false */)
{
    return ULootLockerSDKManager::WhiteLabelLogin(Email, Password, FLootLockerLoginResponseDelegate::CreateLambda([OnWhiteLabelLoginRequestCompleted](const FLootLockerLoginResponse& Response) {
        OnWhiteLabelLoginRequestCompleted.ExecuteIfBound(Response);
    }), Remember);
}

FString ULootLockerManager::WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelAccountCreationRequestCompleted)
{
    return ULootLockerSDKManager::WhiteLabelCreateAccount(Email, Password, FLootLockerLoginResponseDelegate::CreateLambda([OnWhiteLabelAccountCreationRequestCompleted](const FLootLockerLoginResponse& Response) {
        OnWhiteLabelAccountCreationRequestCompleted.ExecuteIfBound(Response);
    }));
}

FString ULootLockerManager::GuestLogin(const FAuthResponseBP& OnCompletedRequestBP, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::GuestLogin(FLootLockerSessionResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerAuthenticationResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), PlayerIdentifier, Optionals);
}

FString ULootLockerManager::StartDiscordSession(const FString& AccessToken, const FDiscordSessionResponseBP& OnStartedDiscordSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::StartDiscordSession(AccessToken, FLootLockerDiscordSessionResponseDelegate::CreateLambda([OnStartedDiscordSessionRequestCompleted](const FLootLockerDiscordSessionResponse& Response) {
        OnStartedDiscordSessionRequestCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::RefreshDiscordSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FDiscordSessionResponseBP& OnRefreshDiscordSessionCompleted, const FLootLockerSessionOptionals& Optionals)
{
    return ULootLockerSDKManager::RefreshDiscordSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, FLootLockerDiscordSessionResponseDelegate::CreateLambda([OnRefreshDiscordSessionCompleted](const FLootLockerDiscordSessionResponse& Response) {
        OnRefreshDiscordSessionCompleted.ExecuteIfBound(Response);
    }), Optionals);
}

FString ULootLockerManager::VerifyPlayer(const FString& ForPlayerWithUlid, const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform /*= FString()*/)
{
#pragma warning(disable : 4996)
    return ULootLockerSDKManager::VerifyPlayer(PlatformToken, FLootLockerDefaultDelegate::CreateLambda([OnVerifyPlayerRequestCompleted](const FLootLockerResponse& Response)
    {
        OnVerifyPlayerRequestCompleted.ExecuteIfBound(Response);
    }), Platform, ForPlayerWithUlid);
#pragma warning(default : 4996)
}

FString ULootLockerManager::EndSession(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted)
{
    return ULootLockerSDKManager::EndSession(FLootLockerDefaultDelegate::CreateLambda([OnEndSessionRequestCompleted](const FLootLockerResponse& Response)
    {
        OnEndSessionRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

//==================================================
// Connected Accounts
//==================================================
FString ULootLockerManager::ListConnectedAccounts(const FString& ForPlayerWithUlid, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ListConnectedAccounts(FLootLockerListConnectedAccountsResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerListConnectedAccountsResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DisconnectAccount(const FString& ForPlayerWithUlid, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::DisconnectAccount(AccountToDisconnect, FLootLockerDefaultDelegate::CreateLambda([OnCompleteBP](const FLootLockerResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectGoogleAccount(const FString& ForPlayerWithUlid, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectGoogleAccount(IdToken, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectGoogleAccountWithPlatform(const FString& ForPlayerWithUlid, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectGoogleAccount(IdToken, Platform, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectAppleAccountByRestSignIn(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectAppleAccountByRestSignIn(AuthorizationCode, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectTwitchAccount(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectTwitchAccount(AuthorizationCode, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectEpicAccount(const FString& ForPlayerWithUlid, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectEpicAccount(Token, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectPlaystationAccount(const FString& ForPlayerWithUlid, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectPlaystationAccount(Environment, Code, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectDiscordAccount(const FString& ForPlayerWithUlid, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectDiscordAccount(Token, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ConnectRemoteSessionAccount(const FString& ForPlayerWithUlid, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ConnectRemoteSessionAccount(Code, Nonce, FLootLockerAccountConnectedResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerAccountConnectedResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid, const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::TransferIdentityProvidersBetweenAccounts(FromPlayerWithUlid, ToPlayerWithUlid, ProvidersToTransfer, FLootLockerListConnectedAccountsResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerListConnectedAccountsResponse& Response)
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

FString ULootLockerManager::RefreshRemoteSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RefreshRemoteSession(RefreshToken.IsEmpty() ? GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken : RefreshToken, 
        FLootLockerRefreshRemoteSessionResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerRefreshRemoteSessionResponse Response) {
            OnCompletedRequest.ExecuteIfBound(Response);
        }));
}

//==================================================
// Player
//==================================================
FString ULootLockerManager::GetCurrentPlayerInfo(const FString& ForPlayerWithUlid, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetCurrentPlayerInfo(FLootLockerGetCurrentPlayerInfoResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerGetCurrentPlayerInfoResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListPlayerInfo(const FString& ForPlayerWithUlid, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ListPlayerInfo(PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, FLootLockerListPlayerInfoResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerListPlayerInfoResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetInventory(const FString& ForPlayerWithUlid, const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    return ULootLockerSDKManager::GetInventory(FInventoryResponse::CreateLambda([OnGetInventoryRequestCompleted](FLootLockerInventoryResponse Response)
    {
        OnGetInventoryRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetFullInventory(const FString ForPlayerWithUlid, int32 StartIndex, const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    return ULootLockerSDKManager::GetFullInventory(FInventoryResponse::CreateLambda([OnGetInventoryRequestCompleted](FLootLockerInventoryResponse Response)
    {
        OnGetInventoryRequestCompleted.ExecuteIfBound(Response);
    }), StartIndex, ForPlayerWithUlid);
}

FString ULootLockerManager::ListPlayerInventory(const FString& ForPlayerWithUlid, const FLootLockerListSimplifiedInventoryRequest& Request, int PerPage, const int& Page, const FLootLockerSimpleInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ListPlayerInventory(Request, PerPage, Page, FLootLockerSimpleInventoryResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerSimpleInventoryResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListCharacterInventory(const FString& ForPlayerWithUlid, int CharacterId, const FLootLockerListSimplifiedInventoryRequest& Request, int PerPage, const int& Page, const FLootLockerSimpleInventoryResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ListCharacterInventory(CharacterId, Request, PerPage, Page, FLootLockerSimpleInventoryResponseDelegate::CreateLambda([OnCompletedRequest](FLootLockerSimpleInventoryResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CheckPlayerAssetActivationNotification(const FString& ForPlayerWithUlid, const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    return ULootLockerSDKManager::CheckPlayerAssetActivationNotification(FLootLockerAssetNotificationResponse::CreateLambda([OnCheckPlayerAssetDeactivationNotificationRequestCompleted](FLootLockerPlayerAssetNotificationResponse Response)
    {
        OnCheckPlayerAssetDeactivationNotificationRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetCurrencyBalance(const FString& ForPlayerWithUlid, const FPBalanceResponseBP& OnGetCurrencyBalance)
{
    return ULootLockerSDKManager::GetCurrencyBalance(FPBalanceResponse::CreateLambda([OnGetCurrencyBalance](FLootLockerBalanceResponse Response)
    {
        OnGetCurrencyBalance.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


FString ULootLockerManager::InitiateDLCMigration(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnInitiateDlcMigration)
{
    return ULootLockerSDKManager::InitiateDLCMigration(FResponseCallback::CreateLambda([OnInitiateDlcMigration](FLootLockerResponse Response)
    {
        OnInitiateDlcMigration.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


FString ULootLockerManager::GetDLCsMigration(const FString& ForPlayerWithUlid, const FPDlcResponseBP& OnGotDlcMigration)
{
    return ULootLockerSDKManager::GetDLCsMigration(FPDlcResponse::CreateLambda([OnGotDlcMigration](FLootLockerDlcResponse Response)
    {
        OnGotDlcMigration.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


FString ULootLockerManager::SetProfilePrivate(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPrivate)
{
    return ULootLockerSDKManager::SetProfilePrivate(FResponseCallback::CreateLambda([OnProfileSetPrivate](FLootLockerResponse Response)
    {
        OnProfileSetPrivate.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SetProfilePublic(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPublic)
{
    return ULootLockerSDKManager::SetProfilePublic(FResponseCallback::CreateLambda([OnProfileSetPublic](FLootLockerResponse Response)
    {
        OnProfileSetPublic.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}
FString ULootLockerManager::SetPlayerName(const FString& ForPlayerWithUlid, FString Name, const FPNameResponseBP& OnSetPlayerName)
{
    return ULootLockerSDKManager::SetPlayerName(Name, FPNameResponse::CreateLambda([OnSetPlayerName](FLootLockerNameResponse Response)
    {
        OnSetPlayerName.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetPlayerName(const FString& ForPlayerWithUlid, const FPNameResponseBP& OnGetPlayerName)
{
    return ULootLockerSDKManager::GetPlayerName(FPNameResponse::CreateLambda([OnGetPlayerName](FLootLockerNameResponse Response)
    {
        OnGetPlayerName.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::LookupMultiplePlayerNamesUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
#pragma warning(disable : 4996)
    return ULootLockerSDKManager::LookupMultiplePlayerNamesUsingIDs(Request, FPMultiplePlayerNames::CreateLambda([OnCompletedRequest](FLootLockerMultiplePlayersNamesResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
#pragma warning(default : 4996)
}

FString ULootLockerManager::LookupMultiplePlayersDataUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::LookupMultiplePlayersDataUsingIDs(Request, FPMultiplePlayerNames::CreateLambda([OnCompletedRequest](FLootLockerMultiplePlayersNamesResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::LookupMultiplePlayerNames1stPlatformIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::LookupMultiplePlayerNames1stPlatformIDs(Request, FPMultiplePlayersPlatformIdsNames::CreateLambda([OnCompletedRequest](FLootLockerMultiplePlayersPlatformIdsResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeletePlayer(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::DeletePlayer(FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


FString ULootLockerManager::UploadFile(const FString& ForPlayerWithUlid, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    return ULootLockerSDKManager::UploadFile(Request, FLootLockerUploadFileDelegate::CreateLambda([OnComplete](FLootLockerPlayerFileResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UpdateFile(const FString& ForPlayerWithUlid, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete)
{
    return ULootLockerSDKManager::UpdateFile(FileId, Request, FLootLockerUploadFileDelegate::CreateLambda([OnComplete](FLootLockerPlayerFileResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListFiles(const FString& ForPlayerWithUlid, const FLootLockerFileListBP& OnComplete)
{
    return ULootLockerSDKManager::ListFiles(FLootLockerFileListDelegate::CreateLambda([OnComplete](FLootLockerFileListResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListOtherPlayersPublicFiles(const FString& ForPlayerWithUlid, const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ListOtherPlayersPublicFiles(PlayerID, FLootLockerFileListDelegate::CreateLambda([OnCompleteBP](FLootLockerFileListResponse Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetSingleFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerUploadFileBP& OnComplete)
{
    return ULootLockerSDKManager::GetSingleFile(FileID, FLootLockerUploadFileDelegate::CreateLambda([OnComplete](FLootLockerPlayerFileResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeletePlayerFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerFileDeletedBP& OnComplete)
{
    return ULootLockerSDKManager::DeletePlayerFile(FileID, FLootLockerFileDeletedDelegate::CreateLambda([OnComplete](FLootLockerResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Player Progressions
FString ULootLockerManager::GetPlayerProgressions(const FString& ForPlayerWithUlid, const int32 Count /*= -1*/, const FString& After /*= ""*/, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetPlayerProgressions(Count, After, FLootLockerPaginatedPlayerProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetPlayerProgression(ProgressionKey, FLootLockerPlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddPointsToPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::AddPointsToPlayerProgression(ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SubtractPointsFromPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::SubtractPointsFromPlayerProgression(ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ResetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ResetPlayerProgression(ProgressionKey, FLootLockerPlayerProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeletePlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::DeletePlayerProgression(ProgressionKey, FLootLockerDeleteProgressionDelegate::CreateLambda([OnCompletedRequest](const FLootLockerResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetOtherPlayersProgressions(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetOtherPlayersProgressions(PlayerUlid, Count, After, FLootLockerPaginatedPlayerProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetOtherPlayersProgression(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetOtherPlayersProgression(PlayerUlid, ProgressionKey, FLootLockerPlayerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPlayerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Heroes
FString ULootLockerManager::GetGameHeroes(const FString& ForPlayerWithUlid, const FLootLockerGameHeroListBP& OnCompleteBP)
{
    return ULootLockerSDKManager::GetGameHeroes(FLootLockerGameHeroListDelegate::CreateLambda([OnCompleteBP](const FLootLockerGameHeroListResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListPlayerHeroes(const FString& ForPlayerWithUlid, const FLootLockerHeroListBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ListPlayerHeroes(FLootLockerHeroListDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroListResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListOtherPlayersHeroesBySteamID64(const FString& ForPlayerWithUlid, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP)
{
    return ULootLockerSDKManager::ListOtherPlayersHeroesBySteamID64(SteamID64, FLootLockerHeroListDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroListResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CreateHero(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    return ULootLockerSDKManager::CreateHero(Request, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CreateHeroWithVariation(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    return ULootLockerSDKManager::CreateHeroWithVariation(Request, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    return ULootLockerSDKManager::GetHero(HeroID, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetOtherPlayersDefaultHeroBySteamID64(const FString& ForPlayerWithUlid, const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    return ULootLockerSDKManager::GetOtherPlayersDefaultHeroBySteamID64(SteamID64, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UpdateHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP)
{
    return ULootLockerSDKManager::UpdateHero(HeroID, Request, FLootLockerPlayerHeroDelegate::CreateLambda([OnCompleteBP](const FLootLockerPlayerHeroResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::DeleteHero(HeroID, FLLHeroDefaultResponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetHeroInventory(const FString& ForPlayerWithUlid, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::GetHeroInventory(HeroID, FInventoryResponse::CreateLambda([OnCompleteBP](const FLootLockerInventoryResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::GetHeroLoadout(HeroID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetOtherPlayersHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::GetOtherPlayersHeroLoadout(HeroID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::AddAssetToHeroLoadout(HeroID, AssetInstanceID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddGlobalAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::AddGlobalAssetToHeroLoadout(HeroID, AssetID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddGlobalAssetVariationToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::AddGlobalAssetVariationToHeroLoadout(HeroID, AssetID, AssetVariationID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::RemoveAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP)
{
    return ULootLockerSDKManager::RemoveAssetToHeroLoadout(HeroID, AssetInstanceID, FHeroLoadoutReseponseDelegate::CreateLambda([OnCompleteBP](const FLootLockerHeroLoadoutResponse& Response)
    {
        OnCompleteBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Character

FString ULootLockerManager::GetCharacterLoadout(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    return ULootLockerSDKManager::GetCharacterLoadout(FCharacterLoadoutResponse::CreateLambda([OnGetCharacterLoadoutRequestCompleted](const FLootLockerCharacterLoadoutResponse& Response) {
        OnGetCharacterLoadoutRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UpdateCharacter(const FString& ForPlayerWithUlid, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::UpdateCharacter(CharacterId, IsDefault, Name, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequest](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CreateCharacter(const FString& ForPlayerWithUlid, bool IsDefault, FString CharacterName, int CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::CreateCharacter(IsDefault, CharacterName, CharacterTypeId, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteCharacter(const FString& ForPlayerWithUlid, int CharacterId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::DeleteCharacter(CharacterId, FLootLockerCharacterDefaultResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListCharacterTypes(const FString& ForPlayerWithUlid, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::ListCharacterTypes(FPLootLockerListCharacterTypesResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerListCharacterTypesResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListPlayerCharacters(const FString& ForPlayerWithUlid, const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::ListPlayerCharacters(FPLootLockerListPlayerCharactersResponse::CreateLambda([OnCompletedRequestBP](const FLootLockerListPlayerCharactersResponse& Response) {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::EquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted)
{
    return ULootLockerSDKManager::EquipAssetToDefaultCharacter(InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnEquipAssetToDefaultCharacterRequestCompleted](const FLootLockerResponse& Response) {
        OnEquipAssetToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::EquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    return ULootLockerSDKManager::EquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId, FLootLockerCharacterDefaultResponse::CreateLambda([OnEquipAssetToCharacterByIdRequestCompleted](const FLootLockerResponse& Response) {
        OnEquipAssetToCharacterByIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::EquipAssetToCharacterByIdAndInstance(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    return ULootLockerSDKManager::EquipAssetToCharacterById(CharacterId, InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnEquipAssetToCharacterByIdRequestCompleted](const FLootLockerResponse& Response) {
        OnEquipAssetToCharacterByIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UnEquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    return ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnUnEquipAssetToDefaultCharacterRequestCompleted](const FLootLockerResponse& Response) {
        OnUnEquipAssetToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UnEquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    return ULootLockerSDKManager::UnEquipAssetToCharacterById(CharacterId, InstanceId, FLootLockerCharacterDefaultResponse::CreateLambda([OnUnEquipAssetToCharacterByIdRequestCompleted](const FLootLockerResponse& Response) {
        OnUnEquipAssetToCharacterByIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    return ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(FCharacterLoadoutResponse::CreateLambda([OnGetCurrentLoadoutToDefaultCharacterRequestCompleted](const FLootLockerCharacterLoadoutResponse& Response) {
        OnGetCurrentLoadoutToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/)
{
    return ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId, FCharacterLoadoutResponse::CreateLambda([OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted](const FLootLockerCharacterLoadoutResponse& Response) {
        OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), OtherPlayerPlatform, ForPlayerWithUlid);
}

FString ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    return ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(FContextDelegate::CreateLambda([OnGetEquipableContextsToDefaultCharacterRequestCompleted](const FLootLockerGetContextResponse& Response) {
        OnGetEquipableContextsToDefaultCharacterRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetEquipableContextsByCharacterId(const FString& ForPlayerWithUlid, int OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    return ULootLockerSDKManager::GetEquipableContextsByCharacterId(OtherCharacterId, FContextDelegate::CreateLambda([OnGetEquipableContextsByCharacterIdRequestCompleted](const FLootLockerGetContextResponse& Response) {
        OnGetEquipableContextsByCharacterIdRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetOtherPlayersCharacterLoadouts(const FString& ForPlayerWithUlid, const FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetOtherPlayersCharacterLoadouts(OtherPlayerId, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequest](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid, OtherPlayerPlatform);
}

FString ULootLockerManager::GetOtherPlayersCharacterLoadoutsByUid(const FString& ForPlayerWithUlid, const FString& OtherPlayerUid, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetOtherPlayersCharacterLoadoutsByUid(OtherPlayerUid, FCharacterLoadoutResponse::CreateLambda([OnCompletedRequest](const FLootLockerCharacterLoadoutResponse& Response) {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Character Progressions
FString ULootLockerManager::GetCharacterProgressions(const FString& ForPlayerWithUlid, const int32& CharacterId, const int32 Count /*=-1*/, const FString& After /*=""*/, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetCharacterProgressions(CharacterId, Count, After, FLootLockerPaginatedCharacterProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedCharacterProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetCharacterProgression(CharacterId, ProgressionKey, FLootLockerCharacterProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddPointsToCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::AddPointsToCharacterProgression(CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SubtractPointsFromCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::SubtractPointsFromCharacterProgression(CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ResetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ResetCharacterProgression(CharacterId, ProgressionKey, FLootLockerCharacterProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerCharacterProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::DeleteCharacterProgression(CharacterId, ProgressionKey, FLootLockerDeleteProgressionDelegate::CreateLambda([OnCompletedRequest](const FLootLockerResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Persistent Storage
FString ULootLockerManager::GetEntirePersistentStorage(const FString& ForPlayerWithUlid, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    return ULootLockerSDKManager::GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegate::CreateLambda([OnPersistentStorageItemsRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnPersistentStorageItemsRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    return ULootLockerSDKManager::GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegate::CreateLambda([OnPersistentStorageItemRequestCompleted](FLootLockerPersistentStorageItemResponse Response)
    {
        OnPersistentStorageItemRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddItemsToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    return ULootLockerSDKManager::AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegate::CreateLambda([OnPersistentStorageItemsAddRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnPersistentStorageItemsAddRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddItemToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted)
{
    return ULootLockerSDKManager::AddItemsToPersistentStorage(Item, FPersistentStorageItemResponseDelegate::CreateLambda([OnPersistentStorageItemAddRequestCompleted](FLootLockerPersistentStorageItemResponse Response)
    {
        OnPersistentStorageItemAddRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted)
{
    return ULootLockerSDKManager::DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegate::CreateLambda([OnPersistentStorageItemDeleteRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnPersistentStorageItemDeleteRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetPlayerPersistentStorage(const FString& ForPlayerWithUlid, const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted)
{
    return ULootLockerSDKManager::GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegate::CreateLambda([OnGetPlayerPersistentStorageRequestCompleted](FLootLockerPersistentStorageItemsResponse Response)
    {
        OnGetPlayerPersistentStorageRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetContexts(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetContextsRequestCompleted)
{
    return ULootLockerSDKManager::GetContexts(FContextDelegate::CreateLambda([OnGetContextsRequestCompleted](const FLootLockerGetContextResponse& Response)
    {
        OnGetContextsRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetAssets(const FString& ForPlayerWithUlid, const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    return ULootLockerSDKManager::GetAssets(FAssetsResponseDelegate::CreateLambda([OnGetAssetsRequestCompleted](const FLootLockerGetAssetsResponse& Response)
    {
        OnGetAssetsRequestCompleted.ExecuteIfBound(Response);
    }), StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, ForPlayerWithUlid);
}

FString ULootLockerManager::ListAssetsWithDefaultParameters(const FString& ForPlayerWithUlid, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest)
{
    return ListAssets(ForPlayerWithUlid, FLootLockerListSimpleAssetsRequest(), 0, 0, ELootLockerOrderAssetListBy::None, ELootLockerOrderAssetListDirection::None, OnCompletedRequest);
}

FString ULootLockerManager::ListAssets(const FString& ForPlayerWithUlid, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, ELootLockerOrderAssetListBy OrderBy, ELootLockerOrderAssetListDirection OrderDirection, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ListAssets(Request, FListSimpleAssetsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerListSimpleAssetsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), PerPage, Page, OrderBy, OrderDirection, ForPlayerWithUlid);
}

FString ULootLockerManager::GetAssetsByIds(const FString& ForPlayerWithUlid, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted)
{
    return ULootLockerSDKManager::GetAssetsByIds(AssetIds, FAssetsResponseDelegate::CreateLambda([OnGetAssetsByIdsRequestCompleted](const FLootLockerGetAssetsResponse& Response)
    {
        OnGetAssetsByIdsRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetAssetBones(const FString& ForPlayerWithUlid, const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted)
{
    return ULootLockerSDKManager::GetAssetBones(FAssetBonesResponseDelegate::CreateLambda([OnGetAssetBonesRequestCompleted](const FLootLockerGetAssetBonesResponse& Response)
    {
        OnGetAssetBonesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetFavouriteAssetIndices(const FString& ForPlayerWithUlid, const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted)
{
    return ULootLockerSDKManager::GetFavouriteAssetIndices(FGetFavouriteAssetIndicesResponseDelegate::CreateLambda([OnGetFavouriteAssetIndicesRequestCompleted](const FLootLockerGetFavouriteAssetIndicesResponse& Response)
    {
        OnGetFavouriteAssetIndicesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddAssetToFavourites(const FString& ForPlayerWithUlid, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted)
{
    return ULootLockerSDKManager::AddAssetToFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegate::CreateLambda([OnAddAssetToFavouritesRequestCompleted](const FLootLockerGetFavouriteAssetIndicesResponse& Response)
    {
        OnAddAssetToFavouritesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::RemoveAssetFromFavourites(const FString& ForPlayerWithUlid, int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted)
{
    return ULootLockerSDKManager::RemoveAssetFromFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegate::CreateLambda([OnRemoveAssetFromFavouritesRequestCompleted](const FLootLockerGetFavouriteAssetIndicesResponse& Response)
    {
        OnRemoveAssetFromFavouritesRequestCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetUniversalAssets(const FString& ForPlayerWithUlid, int After, int ItemsCount, const FUniversalAssetResponseDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetUniversalAssets(After, ItemsCount, FUniversalAssetResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerUniversalAssetsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GrantAssetWithVariationToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GrantAssetToPlayerInventory(AssetID, AssetVariationID, AssetRentalOptionID, FGrantAssetResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerGrantAssetResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}


// Asset Instances
FString ULootLockerManager::GetAllKeyValuePairsForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    return ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnGetAllKeyValuePairsForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnGetAllKeyValuePairsForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
{
    return ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemResponseDelegate::CreateLambda([OnGetAKeyValuePairByIdForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemResponse& Response)
        {
            OnGetAKeyValuePairByIdForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::CreateAKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted)
{
    return ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnCreateAKeyValuePairForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnCreateAKeyValuePairForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
{
    return ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
{
    return ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemResponseDelegate::CreateLambda([OnUpdateAKeyValuePairByIdForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemResponse& Response)
        {
            OnUpdateAKeyValuePairByIdForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted)
{
    return ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegate::CreateLambda([OnDeleteAKeyValuePairByIdForAssetInstanceCompleted](const FLootLockerAssetInstanceStorageItemsResponse& Response)
        {
            OnDeleteAKeyValuePairByIdForAssetInstanceCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::InspectLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted)
{
    return ULootLockerSDKManager::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegate::CreateLambda([OnInspectLootBoxCompleted](const FLootLockerLootBoxContentResponse& Response)
        {
            OnInspectLootBoxCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::OpenLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted)
{
    return ULootLockerSDKManager::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegate::CreateLambda([OnOpenLootBoxCompleted](const FLootLockerOpenLootBoxResponse& Response)
        {
            OnOpenLootBoxCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteAssetInstanceFromPlayerInventory(const FString& ForPlayerWithUlid, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted)
{
    return ULootLockerSDKManager::DeleteAssetInstanceFromPlayerInventory(AssetInstanceID, FDeleteAssetInstanceResponseDelegate::CreateLambda([OnCompleted](const FLootLockerDeleteAssetInstanceResponse& Response)
        {
            OnCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

// User Generated Content - Asset Candidates

FString ULootLockerManager::CreateAssetCandidate(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    return ULootLockerSDKManager::CreateAssetCandidate(AssetCandidateData, FCreateAssetCandidateResponseDelegate::CreateLambda([OnCreateAssetCandidateCompleted](FLootLockerCreateAssetCandidateResponse Response)
        {
            OnCreateAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::CreateAssetCandidateAndMarkComplete(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    return ULootLockerSDKManager::CreateAssetCandidateAndMarkComplete(AssetCandidateData, FCreateAssetCandidateResponseDelegate::CreateLambda([OnCreateAssetCandidateCompleted](FLootLockerCreateAssetCandidateResponse Response)
        {
            OnCreateAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::UpdateAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    return ULootLockerSDKManager::UpdateAssetCandidate(AssetCandidateId, AssetCandidateData, FAssetCandidateResponseDelegate::CreateLambda([OnUpdateAssetCandidateCompleted](FLootLockerAssetCandidateResponse Response)
        {
            OnUpdateAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted)
{
    return ULootLockerSDKManager::DeleteAssetCandidate(AssetCandidateId, FResponseCallback::CreateLambda([OnDeleteAssetCandidateCompleted](FLootLockerResponse Response)
        {
            OnDeleteAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetAllAssetCandidates(const FString& ForPlayerWithUlid, const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted)
{
    return ULootLockerSDKManager::GetAllAssetCandidates(FAssetCandidatesResponseDelegate::CreateLambda([OnGetAllAssetCandidatesCompleted](FLootLockerAssetCandidatesResponse Response)
        {
            OnGetAllAssetCandidatesCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted)
{
    return ULootLockerSDKManager::GetAssetCandidate(AssetCandidateId, FAssetCandidateResponseDelegate::CreateLambda([OnGetAssetCandidateCompleted](FLootLockerAssetCandidateResponse Response)
        {
            OnGetAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddFileToAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegateBP& OnAddFileToAssetCandidateCompleted)
{
    return ULootLockerSDKManager::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, FAssetCandidateResponseDelegate::CreateLambda([OnAddFileToAssetCandidateCompleted](FLootLockerAssetCandidateResponse Response)
        {
            OnAddFileToAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteFileFromAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted)
{
    return ULootLockerSDKManager::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, FResponseCallback::CreateLambda([OnDeleteFileFromAssetCandidateCompleted](FLootLockerResponse Response)
        {
            OnDeleteFileFromAssetCandidateCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

// Progressions
FString ULootLockerManager::GetProgressions(const FString& ForPlayerWithUlid, const int32 Count /*= -1*/, const FString& After /*=""*/, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetProgressions(Count, After, FLootLockerPaginatedProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedProgressionsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetProgression(ProgressionKey, FLootLockerProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetProgressionTiers(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32 Count /*=-1*/, const int32 After /*=-1*/, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetProgressionTiers(ProgressionKey, Count, After, FLootLockerPaginatedProgressionTiersResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedProgressionTiersResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

//Instance progression

FString ULootLockerManager::GetInstanceProgressions(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetInstanceProgressions(AssetInstanceId, Count, After, FLootLockerPaginatedInstanceProgressionsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerPaginatedInstanceProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AddPointsToInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::AddPointsToInstanceProgression(AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SubtractPointsFromInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::SubtractPointsFromInstanceProgression(AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ResetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ResetInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionWithRewardsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerInstanceProgressionWithRewardsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::DeleteInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerDeleteProgressionDelegate::CreateLambda([OnCompletedRequest](const FLootLockerResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Missions
FString ULootLockerManager::GetAllMissions(const FString& ForPlayerWithUlid, const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted)
{
    return ULootLockerSDKManager::GetAllMissions(FMissionsResponseDelegate::CreateLambda([OnGetAllMissionsCompleted](FLootLockerMissionsResponse Response)
    {
        OnGetAllMissionsCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetMission(const FString& ForPlayerWithUlid, int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted)
{
    return ULootLockerSDKManager::GetMission(MissionId, FMissionResponseDelegate::CreateLambda([OnGetMissionCompleted](FLootLockerMissionResponse Response)
    {
        OnGetMissionCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::StartMission(const FString& ForPlayerWithUlid, int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted)
{
    return ULootLockerSDKManager::StartMission(MissionId, FStartMissionResponseDelegate::CreateLambda([OnStartMissionCompleted](FLootLockerStartMissionResponse Response)
    {
        OnStartMissionCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::FinishMission(const FString& ForPlayerWithUlid, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted)
{
    return ULootLockerSDKManager::FinishMission(MissionId, MissionData, FFinishMissionResponseDelegate::CreateLambda([OnFinishMissionCompleted](FLootLockerFinishMissionResponse Response)
    {
        OnFinishMissionCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetMaps(const FString& ForPlayerWithUlid, const FGetMapsResponseDelegateBP& OnGetMapsCompleted)
{
    return ULootLockerSDKManager::GetMaps(FGetMapsResponseDelegate::CreateLambda([OnGetMapsCompleted](FLootLockerGetMapsResponse Response)
        {
            OnGetMapsCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::ActivateRentalAsset(const FString& ForPlayerWithUlid, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    return ULootLockerSDKManager::ActivateRentalAsset(AssetInstanceId, FActivateRentalAssetResponseDelegate::CreateLambda([OnActivateRentalAssetCompleted](FLootLockerActivateRentalAssetResponse Response)
        {
            OnActivateRentalAssetCompleted.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::LootLockerPurchaseSingleCatalogItem(const FString& ForPlayerWithUlid, const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return LootLockerPurchaseCatalogItems(ForPlayerWithUlid, WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest);
}

FString ULootLockerManager::LootLockerPurchaseCatalogItems(const FString& ForPlayerWithUlid, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::LootLockerPurchaseCatalogItems(WalletId, ItemsToPurchase, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::RedeemAppleAppStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RedeemAppleAppStorePurchaseForPlayer(TransactionId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), Sandboxed, ForPlayerWithUlid);
}

FString ULootLockerManager::RedeemAppleAppStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RedeemAppleAppStorePurchaseForClass(ClassId, TransactionId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), Sandboxed, ForPlayerWithUlid);
}

FString ULootLockerManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForPlayer(ProductId, PurchaseToken, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::RedeemGooglePlayStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForClass(ClassId, ProductId, PurchaseToken, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::RedeemEpicStorePurchase(const FString& ForPlayerWithUlid, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RedeemEpicStorePurchase(AccountId, BearerToken, EntitlementIds, SandboxId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::RedeemEpicStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::RedeemEpicStorePurchaseForCharacter(CharacterId, AccountId, BearerToken, EntitlementIds, SandboxId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

#ifdef LOOTLOCKER_BETA_PLAYSTATION_IAP
// FString ULootLockerManager::RedeemPlayStationStorePurchase(const FString& ForPlayerWithUlid, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedRequest)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForPlayer(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, OnCompletedRequest);
// }

// FString ULootLockerManager::RedeemPlayStationStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedRequest)
// {
    // ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForCharacter(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid), CharacterId, TransactionId, AuthCode, EntitlementLabel, ServiceLabel, ServiceName, Environment, UseCount, OnCompletedRequest);
// }
#endif

FString ULootLockerManager::BeginSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::BeginSteamPurchaseRedemption(SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegate::CreateLambda([OnCompletedRequest](FLootLockerBeginSteamPurchaseRedemptionResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::BeginSteamPurchaseRedemptionForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::BeginSteamPurchaseRedemptionForClass(ClassId, SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegate::CreateLambda([OnCompletedRequest](FLootLockerBeginSteamPurchaseRedemptionResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::QuerySteamPurchaseRedemptionStatus(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::QuerySteamPurchaseRedemptionStatus(EntitlementId, FLootLockerQuerySteamPurchaseRedemptionStatusDelegate::CreateLambda([OnCompletedRequest](FLootLockerQuerySteamPurchaseRedemptionStatusResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::FinalizeSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::FinalizeSteamPurchaseRedemption(EntitlementId, FLootLockerDefaultDelegate::CreateLambda([OnCompletedRequest](FLootLockerResponse Response)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

//Triggers
FString ULootLockerManager::InvokeTriggersByKey(const FString& ForPlayerWithUlid, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnComplete)
{
    return ULootLockerSDKManager::InvokeTriggersByKey(KeysToInvoke, FLootLockerInvokeTriggersByKeyResponseDelegate::CreateLambda([OnComplete](FLootLockerInvokeTriggersByKeyResponse Response)
        {
            OnComplete.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

//Notifications
FString ULootLockerManager::ListNotificationsWithDefaultParameters(const FString& ForPlayerWithUlid, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListNotificationsWithDefaultParameters(FLootLockerListNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerListNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListNotifications(const FString& ForPlayerWithUlid, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListNotifications(ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, FLootLockerListNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerListNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListNotificationsWithPriority(const FString& ForPlayerWithUlid, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListNotificationsWithPriority(WithPriority, ShowRead, OfType, WithSource, CustomNotificationsFilter, PerPage, Page, FLootLockerListNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerListNotificationsResponse Response)
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

FString ULootLockerManager::MarkAllNotificationsAsRead(const FString& ForPlayerWithUlid, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::MarkAllNotificationsAsRead(FLootLockerReadNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerReadNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::MarkNotificationsAsRead(const FString& ForPlayerWithUlid, const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::MarkNotificationsAsRead(Notifications, FLootLockerReadNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerReadNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::MarkNotificationsAsReadByIds(const FString& ForPlayerWithUlid, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::MarkNotificationsAsReadByIds(NotificationIDs, FLootLockerReadNotificationsResponseDelegate::CreateLambda([OnComplete](FLootLockerReadNotificationsResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

bool ULootLockerManager::TryGetNotificationsByIdentifyingValue(const FLootLockerListNotificationsResponse& NotificationsResponse, const FString& IdentifyingValue, TArray<FLootLockerNotification>& Notifications)
{
    return NotificationsResponse.TryGetNotificationsByIdentifyingValue(IdentifyingValue, Notifications);
}

// Broadcasts

FString ULootLockerManager::ListBroadcasts(const TArray<FString>& Languages, int32 Limit, const FString& ForPlayerWithUlid, const FLootLockerListBroadcastsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListBroadcasts(Languages, Limit, FLootLockerListBroadcastsResponseDelegate::CreateLambda([OnComplete](const FLootLockerListBroadcastsResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Collectables

FString ULootLockerManager::GetAllCollectables(const FString& ForPlayerWithUlid, const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted)
{
    return ULootLockerSDKManager::GetAllCollectables(FCollectablesResponseDelegate::CreateLambda([OnGetAllCollectablesCompleted](const FLootLockerCollectablesResponse& Response)
    {
        OnGetAllCollectablesCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CollectItem(const FString& ForPlayerWithUlid, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted)
{
    return ULootLockerSDKManager::CollectItem(Item, FCollectablesResponseDelegate::CreateLambda([OnCollectItemCompleted](const FLootLockerCollectablesResponse& Response)
    {
        OnCollectItemCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Messages
FString ULootLockerManager::GetMessages(const FString& ForPlayerWithUlid, const FMessagesResponseDelegateBP& OnGetMessagesCompleted)
{
    return ULootLockerSDKManager::GetMessages(FMessagesResponseDelegate::CreateLambda([OnGetMessagesCompleted](FLootLockerMessagesResponse Response)
    {
        OnGetMessagesCompleted.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListLeaderboards(const FString& ForPlayerWithUlid, int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::ListLeaderboards(Count, After, FLootLockerListLeaderboardsResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerListLeaderboardsResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetMemberRank(const FString& ForPlayerWithUlid, FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetMemberRank(LeaderboardKey, MemberId, FLootLockerGetMemberRankResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetMemberRankResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetAllMemberRanks(const FString& ForPlayerWithUlid, FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetAllMemberRanks(MemberId, Count, After, FLootLockerGetAllMemberRanksResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetAllMemberRanksResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetByListOfMembers(const FString& ForPlayerWithUlid, TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetByListOfMembers(Members, LeaderboardKey, FLootLockerGetByListOfMembersResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetByListOfMembersResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetScoreList(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetScoreList(LeaderboardKey, Count, After, FLootLockerGetScoreListResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGetScoreListResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetScoreListInitial(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    return GetScoreList(ForPlayerWithUlid, LeaderboardKey, Count, -1, OnCompletedRequestBP);
}


FString ULootLockerManager::SubmitScore(const FString& ForPlayerWithUlid, FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::SubmitScore(MemberId, LeaderboardKey, Score, Metadata, FLootLockerSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerSubmitScoreResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::QueryScore(const FString LeaderboardKey, const int Score, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerSDKManager::QueryScore(LeaderboardKey, Score, FLootLockerSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerSubmitScoreResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::IncrementScore(FString MemberId, const FString LeaderboardKey, const int Amount, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP, const FString& ForPlayerWithUlid /* = "" */)
{
    return ULootLockerSDKManager::IncrementScore(MemberId, LeaderboardKey, Amount, FLootLockerSubmitScoreResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerSubmitScoreResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::ListLeaderboardArchive(LeaderboardKey, FLootLockerLeaderboardArchiveResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerLeaderboardArchiveResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetLeaderboardArchive(Key, Count, After, FLootLockerLeaderboardArchiveDetailResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerLeaderboardArchiveDetailsResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetLeaderboardDetails(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetLeaderboardDetails(LeaderboardKey, FLootLockerLeaderboardDetailsResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerLeaderboardDetailsResponse Response)
        {
            OnCompletedRequestBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
}

// Drop Tables

FString ULootLockerManager::ComputeAndLockDropTable(const FString& ForPlayerWithUlid, int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::ComputeAndLockDropTable(TableId, FLootLockerComputeAndLockDropTableResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerComputeAndLockDropTableResponse& Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::PickDropsFromDropTable(const FString& ForPlayerWithUlid, TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::PickDropsFromDropTable(Picks, TableId, FFLootLockerPickDropsFromDropTableResponseDelegate::CreateLambda([OnCompletedRequestBP](const FLootLockerPickDropsFromDropTableResponse& Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Currencies
FString ULootLockerManager::ListCurrencies(const FString& ForPlayerWithUlid, const FLootLockerListCurrenciesResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::ListCurrencies(FLootLockerListCurrenciesResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerListCurrenciesResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetCurrencyDetails(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetCurrencyDetails(CurrencyCode, FLootLockerGetCurrencyDetailsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerGetCurrencyDetailsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetCurrencyDenominationsByCode(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnCompletedRequest)
{
    return ULootLockerSDKManager::GetCurrencyDenominationsByCode(CurrencyCode, FLootLockerListDenominationsResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerListDenominationsResponse& Response)
    {
        OnCompletedRequest.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Balances

FString ULootLockerManager::ListBalancesInWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListBalancesInWallet(WalletID, FLootLockerListBalancesForWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerListBalancesForWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetWalletByWalletID(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerGetWalletResponseBP& OnComplete)
{
    return ULootLockerSDKManager::GetWalletByWalletID(WalletID, FLootLockerGetWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerGetWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetWalletByHolderID(const FString& ForPlayerWithUlid, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnComplete)
{
    return ULootLockerSDKManager::GetWalletByHolderID(HolderULID, HolderType, FLootLockerGetWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerGetWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CreditBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnComplete)
{
    return ULootLockerSDKManager::CreditBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerCreditWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerCreditWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DebitBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnComplete)
{
    return ULootLockerSDKManager::DebitBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerDebitWalletResponseDelegate::CreateLambda([OnComplete](const FLootLockerDebitWalletResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Catalogs

FString ULootLockerManager::ListCatalogs(const FString& ForPlayerWithUlid, const FLootLockerListCatalogsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListCatalogs(FLootLockerListCatalogsResponseDelegate::CreateLambda([OnComplete](const FLootLockerListCatalogsResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListCatalogItems(const FString& ForPlayerWithUlid, const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnComplete)
{
#pragma warning(suppress : 4996)
    return ULootLockerSDKManager::ListCatalogItems(CatalogKey, Count, After, FLootLockerListCatalogPricesResponseDelegate::CreateLambda([OnComplete](const FLootLockerListCatalogPricesResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
#pragma warning(default : 4996)
}

FString ULootLockerManager::ListCatalogItemsV2(const FString& ForPlayerWithUlid, const FString& CatalogKey, int PerPage, int Page, const FLootLockerListCatalogPricesV2ResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListCatalogItems(CatalogKey, PerPage, Page, FLootLockerListCatalogPricesV2ResponseDelegate::CreateLambda([OnComplete](const FLootLockerListCatalogPricesV2Response& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

TArray<FLootLockerInlinedCatalogEntry> ULootLockerManager::ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog)
{
    return ULootLockerCatalogRequestHandler::ConvertCatalogToInlineItems(Catalog);
}

TArray<FLootLockerInlinedCatalogEntry> ULootLockerManager::ConvertCatalogV2ToInlineItems(const FLootLockerListCatalogPricesV2Response& Catalog)
{
    return ULootLockerCatalogRequestHandler::ConvertCatalogV2ToInlineItems(Catalog);
}

// Entitlements
FString ULootLockerManager::ListEntitlements(const FString& ForPlayerWithUlid, int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListEntitlements(Count, After, FLootLockerListEntitlementsResponseDelegate::CreateLambda([OnComplete](const FLootLockerEntitlementHistoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetEntitlement(const FString& ForPlayerWithUlid, const FString& EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnComplete)
{
    FLootLockerSingleEntitlementResponseDelegate Delegate = FLootLockerSingleEntitlementResponseDelegate::CreateLambda([OnComplete](const FLootLockerSingleEntitlementResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    });
    return ULootLockerSDKManager::GetEntitlement(EntitlementID, Delegate, ForPlayerWithUlid);
}

// Feedback

FString ULootLockerManager::ListPlayerFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListPlayerFeedbackCategories(FLootLockerListFeedbackCategoryResponseDelegate::CreateLambda([OnComplete](const FLootLockerFeedbackCategoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListGameFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListGameFeedbackCategories(FLootLockerListFeedbackCategoryResponseDelegate::CreateLambda([OnComplete](const FLootLockerFeedbackCategoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListUGCFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListUGCFeedbackCategories(FLootLockerListFeedbackCategoryResponseDelegate::CreateLambda([OnComplete](const FLootLockerFeedbackCategoryResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SendPlayerFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    return ULootLockerSDKManager::SendPlayerFeedback(Ulid, Description, CategoryID, FLootLockerSendFeedbackResponseDelegate::CreateLambda([OnComplete](const FLootLockerResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SendGameFeedback(const FString& ForPlayerWithUlid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    return ULootLockerSDKManager::SendGameFeedback(Description, CategoryID, FLootLockerSendFeedbackResponseDelegate::CreateLambda([OnComplete](const FLootLockerResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::SendUGCFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete)
{
    return ULootLockerSDKManager::SendUGCFeedback(Ulid, Description, CategoryID, FLootLockerSendFeedbackResponseDelegate::CreateLambda([OnComplete](const FLootLockerResponse& Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);

}

// Metadata

FString ULootLockerManager::ListMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListMetadata(Source, SourceID, Page, PerPage, FLootLockerListMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerListMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
}

FString ULootLockerManager::ListMetadataWithTags(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete)
{
    return ULootLockerSDKManager::ListMetadataWithTags(Source, SourceID, Tags, Page, PerPage, FLootLockerListMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerListMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
}

FString ULootLockerManager::GetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnComplete)
{
    return ULootLockerSDKManager::GetMetadata(Source, SourceID, Key, FLootLockerGetMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerGetMetadataResponse Response)
    {
        OnComplete.ExecuteIfBound(Response);
    }), IgnoreFiles, ForPlayerWithUlid);
}

FString ULootLockerManager::GetMultisourceMetadata(const FString& ForPlayerWithUlid, const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseBP& OnComplete)
{
    return ULootLockerSDKManager::GetMultisourceMetadata(SourcesAndKeysToGet, FLootLockerGetMultisourceMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerGetMultisourceMetadataResponse Response)
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

FString ULootLockerManager::SetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseBP& OnComplete)
{
    return ULootLockerSDKManager::SetMetadata(Source, SourceID, MetadataToActionsToPerform, FLootLockerSetMetadataResponseDelegate::CreateLambda([OnComplete](FLootLockerSetMetadataResponse Response)
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
FString ULootLockerManager::GetServerTime(const FString& ForPlayerWithUlid, const FTimeResponseDelegateBP& OnCompletedRequestBP)
{
    return ULootLockerSDKManager::GetServerTime(FTimeResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerTimeResponse Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::GetLastActivePlatform(const FString& ForPlayerWithUlid) {
    return ULootLockerSDKManager::GetLastActivePlatform(ForPlayerWithUlid);
}

FString ULootLockerManager::GetGameInfo(const FGameInfoResponseDelegateBP& OnCompletedRequestBP) {
    return ULootLockerSDKManager::GetGameInfo(FGameInfoResponseDelegate::CreateLambda([OnCompletedRequestBP](FLootLockerGameInfoResponse Response)
    {
        OnCompletedRequestBP.ExecuteIfBound(Response);
    }));
}

// Followers (Unified with optional pagination parameters)
FString ULootLockerManager::ListFollowersForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListFollowersPaginated(PlayerPublicUid, Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListFollowers(PlayerPublicUid, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::ListFollowers(const FString& ForPlayerWithUlid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListFollowersPaginated(Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListFollowers(FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::ListFollowingForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListFollowingPaginated(PlayerPublicUid, Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListFollowing(PlayerPublicUid, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::ListFollowing(const FString& ForPlayerWithUlid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = !Cursor.IsEmpty() || Count > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListFollowingPaginated(Cursor, Count, FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListFollowing(FLootLockerListFollowersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFollowersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::FollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::FollowPlayer(PlayerPublicUid, FLootLockerFollowActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFollowActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UnfollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::UnfollowPlayer(PlayerPublicUid, FLootLockerFollowActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFollowActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

// Friends
FString ULootLockerManager::ListFriends(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListFriendsPaginated(Page, PerPage, FLootLockerListFriendsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFriendsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListFriends(FLootLockerListFriendsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListFriendsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::ListIncomingFriendRequests(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListIncomingFriendRequestsPaginated(Page, PerPage, FLootLockerListIncomingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListIncomingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListIncomingFriendRequests(FLootLockerListIncomingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListIncomingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::ListOutgoingFriendRequests(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListOutgoingFriendRequestsPaginated(Page, PerPage, FLootLockerListOutgoingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListOutgoingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListOutgoingFriendRequests(FLootLockerListOutgoingFriendRequestsResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListOutgoingFriendRequestsResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::SendFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::SendFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeleteFriend(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::DeleteFriend(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::CancelOutgoingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::CancelOutgoingFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::AcceptIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::AcceptIncomingFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::DeclineIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::DeclineIncomingFriendRequest(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::ListBlockedPlayers(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP)
{
    const bool bUsePagination = Page > 0 || PerPage > 0;
    if (bUsePagination)
    {
        return ULootLockerSDKManager::ListBlockedPlayersPaginated(Page, PerPage, FLootLockerListBlockedPlayersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListBlockedPlayersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
    else
    {
        return ULootLockerSDKManager::ListBlockedPlayers(FLootLockerListBlockedPlayersResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerListBlockedPlayersResponse& Response)
        {
            OnResponseCompletedBP.ExecuteIfBound(Response);
        }), ForPlayerWithUlid);
    }
}

FString ULootLockerManager::GetFriend(const FString& ForPlayerWithUlid, const FString& FriendUlid, const FLootLockerGetFriendResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::GetFriend(FriendUlid, FLootLockerGetFriendResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerGetFriendResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::BlockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::BlockPlayer(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}

FString ULootLockerManager::UnblockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerId, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP)
{
    return ULootLockerSDKManager::UnblockPlayer(PlayerId, FLootLockerFriendActionResponseDelegate::CreateLambda([OnResponseCompletedBP](const FLootLockerFriendActionResponse& Response)
    {
        OnResponseCompletedBP.ExecuteIfBound(Response);
    }), ForPlayerWithUlid);
}
