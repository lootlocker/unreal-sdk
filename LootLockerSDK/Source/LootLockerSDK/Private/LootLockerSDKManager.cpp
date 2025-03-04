// Copyright (c) 2021 LootLocker


#include "LootLockerSDKManager.h"

#include "LootLockerPlatformManager.h"

//Authentication
void ULootLockerSDKManager::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(Email, Password, FLootLockerLoginResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest, const bool Remember /* = false */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(Email, Password, Remember, FLootLockerLoginResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartPlaystationNetworkSession(PsnOnlineId, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAndroidSession(const FString& DeviceId, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartAndroidSession(DeviceId, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAmazonLunaSession(const FString& AmazonLunaGuid,const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartAmazonLunaSession(AmazonLunaGuid, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPlayerAndStartSteamSession(const FString& SteamId64, const FString& PlatformToken, const FLootLockerSessionResponse& OnCompletedRequest, const int SteamAppId /* = -1 */)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(PlatformToken, ULootLockerCurrentPlatform::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Steam).AuthenticationProviderString, SteamAppId, FLootLockerDefaultResponseBP(), FLootLockerDefaultDelegate::CreateLambda([SteamId64, OnCompletedRequest](FLootLockerResponse VerifyPlayerResponse)
        {
            if(!VerifyPlayerResponse.success)
            {
                FLootLockerAuthenticationResponse AuthResponse;
                AuthResponse.success = VerifyPlayerResponse.success;
                AuthResponse.FullTextFromServer = VerifyPlayerResponse.FullTextFromServer;
                AuthResponse.StatusCode = VerifyPlayerResponse.StatusCode;
                AuthResponse.ErrorData = VerifyPlayerResponse.ErrorData;
                OnCompletedRequest.ExecuteIfBound(AuthResponse);
                return;
            }
            StartSteamSession(SteamId64, OnCompletedRequest);
        }));
}

void ULootLockerSDKManager::StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FLootLockerSessionResponse& OnCompletedRequest, const FString& SteamAppId /* = "" */)
{
    ULootLockerAuthenticationRequestHandler::StartSteamSession(SteamSessionTicket, SteamAppId, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartSteamSession(const FString& SteamId64, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartSteamSession(SteamId64, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartNintendoSwitchSession(NSAIdToken, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionResponse& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartXboxSession(XboxUserToken, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartGoogleSession(const FString& IdToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, FGoogleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartGoogleSession(IdToken, Platform, FGoogleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshGoogleSession(const FString& RefreshToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::RefreshGoogleSession(RefreshToken, FGoogleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAppleSession(const FString& AuthorizationCode, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartAppleSession(AuthorizationCode, FAppleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshAppleSession(const FString& RefreshToken, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleSession(RefreshToken, FAppleSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseDelegate& OnStartedAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartAppleGameCenterSession(BundleId, PlayerId, PublicKeyUrl, Signature, Salt, Timestamp, FLootLockerAppleGameCenterSessionResponseBP(), OnStartedAppleGameCenterSessionCompleted);
}

void ULootLockerSDKManager::RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseDelegate& OnRefreshAppleGameCenterSessionCompleted)
{
    ULootLockerAuthenticationRequestHandler::RefreshAppleGameCenterSession(RefreshToken, FLootLockerAppleGameCenterSessionResponseBP(),OnRefreshAppleGameCenterSessionCompleted);
}

void ULootLockerSDKManager::StartEpicSession(const FString& IdToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartEpicSession(IdToken, FEpicSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshEpicSession(const FString& RefreshToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::RefreshEpicSession(RefreshToken, FEpicSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::StartMetaSession(UserId, Nonce, FLootLockerMetaSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseDelegate& OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::RefreshMetaSession(RefreshToken, FLootLockerMetaSessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelStartSession(const FLootLockerSessionResponse &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& OnCompletedRequest, const bool Remember)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLoginAndStartSession(Email, Password, Remember, FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelVerifySession(const FLootLockerWhiteLabelVerifySessionDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(FLootLockerVerifySessionResponseBP(), OnCompletedRequest);
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

void ULootLockerSDKManager::GuestLogin(const FLootLockerSessionResponse &OnCompletedRequest, const FString& PlayerIdentifier)
{
    ULootLockerAuthenticationRequestHandler::GuestLogin(PlayerIdentifier, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultDelegate& OnCompleteRequest, const FString& Platform)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(PlatformToken, Platform, -1, FLootLockerDefaultResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::EndSession(const FLootLockerDefaultDelegate& OnCompleteRequest)
{
    ULootLockerAuthenticationRequestHandler::EndSession(FLootLockerDefaultResponseBP(), OnCompleteRequest);
}

//==================================================
// Connected Accounts
//==================================================
void ULootLockerSDKManager::ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(FLootLockerListConnectedAccountsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete)
{
    ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(AccountToDisconnect, FLootLockerDefaultResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(IdToken, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectGoogleAccount(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(IdToken, Platform, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(AuthorizationCode, FLootLockerAccountConnectedResponseBP(), OnComplete);
}

//==================================================
// Remote Sessions
//==================================================
FString ULootLockerSDKManager::StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegate& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
    return ULootLockerRemoteSessionRequestHandler::StartRemoteSession(FLootLockerLeaseRemoteSessionResponseDelegateBP(), RemoteSessionLeaseInformation, FLootLockerRemoteSessionStatusPollingResponseDelegateBP(), RemoteSessionLeaseStatusUpdate, FLootLockerStartRemoteSessionResponseDelegateBP(), OnComplete, PollingIntervalSeconds, TimeOutAfterMinutes);
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
void ULootLockerSDKManager::GetCurrentPlayerInfo(const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(FLootLockerGetCurrentPlayerInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListPlayerInfo(TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::ListPlayerInfo(PlayerIdsToLookUp, PlayerLegacyIdsToLookUp, PlayerPublicUidsToLookUp, FLootLockerListPlayerInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetPlayerInfo(FPInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetInventory(const FInventoryResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetInventory(FPInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetFullInventory(const FInventoryResponse &OnCompletedRequest, int32 StartIndex)
{
    ULootLockerPlayerRequestHandler::GetFullInventory(FPInventoryResponseBP(), OnCompletedRequest, StartIndex);
}

void ULootLockerSDKManager::SubmitXP(int Points, const FSubmitXpResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::SubmitXp(Points, FPSubmitResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersXpAndLevel(FString OtherPlayerId, const FOtherPlayersXpAndLevelResponse& OnCompletedRequest, FString OtherPlayerPlatform)
{
    ULootLockerPlayerRequestHandler::GetOtherPlayersXpAndLevel(OtherPlayerId, OtherPlayerPlatform, FPOtherPlayersXpAndLevelBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMultiplePlayersXp(FLootLockerMultiplePlayersXpRequest &Request, const FPMultiplePlayersXP &OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetMultiplePlayersXp(Request, FPMultiplePlayersXPBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(FPAssetNotificationResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyBalance(const FPBalanceResponse& onCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetCurrencyBalance(FPBalanceResponseBP(), onCompletedRequest);
}

void ULootLockerSDKManager::InitiateDLCMigration(const FResponseCallback& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::InitiateDLCMigration(FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetPlayerName(FString Name, const FPNameResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(Name, FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerName(const FPNameResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetPlayerName(FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(Request, FPMultiplePlayerNamesBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayersDataUsingIDs(const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(Request, FPMultiplePlayerNamesBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(Request, FPMultiplePlayersPlatformIdsBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeletePlayer(const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::DeletePlayer(FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

//Files
void ULootLockerSDKManager::UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
    ULLPlayerFilesRequestHandler::UploadFile(Request, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
    ULLPlayerFilesRequestHandler::UpdateFile(FileId, Request, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::ListFiles(const FLootLockerFileListDelegate &OnComplete)
{
    ULLPlayerFilesRequestHandler::ListFiles(FLootLockerFileListBP(), OnComplete);
}

void ULootLockerSDKManager::ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete)
{
    ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(PlayerID, FLootLockerFileListBP(), OnComplete);
}

void ULootLockerSDKManager::GetSingleFile(const int32 FileID, const FLootLockerUploadFileDelegate &OnComplete)
{
    ULLPlayerFilesRequestHandler::GetSingleFile(FileID, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedDelegate &OnComplete)
{
    ULLPlayerFilesRequestHandler::DeletePlayerFile(FileID, FLootLockerFileDeletedBP(), OnComplete);
}

void ULootLockerSDKManager::GetDLCsMigration(const FPDlcResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetDLCsMigration(FPDlcResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetProfilePrivate(const FResponseCallback& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::SetProfilePrivate(FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetProfilePublic(const FResponseCallback& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::SetProfilePublic(FResponseCallbackBP(), OnCompletedRequest);
}

// Player Progressions
void ULootLockerSDKManager::GetPlayerProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgressions(Count, After, FLootLockerPaginatedPlayerProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetPlayerProgressions(const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete)
{
    GetPlayerProgressions(Count, "", OnComplete);
}

void ULootLockerSDKManager::GetPlayerProgressions(const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete)
{
    GetPlayerProgressions(-1, "", OnComplete);
}

void ULootLockerSDKManager::GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetPlayerProgression(ProgressionKey, FLootLockerPlayerProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(ProgressionKey, Amount, FLootLockerPlayerProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::ResetPlayerProgression(ProgressionKey, FLootLockerPlayerProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::DeletePlayerProgression(ProgressionKey, FLootLockerDeleteProgressionBP(), OnComplete);
}

// Heroes
void ULootLockerSDKManager::GetGameHeroes(const FLootLockerGameHeroListDelegate& OnCompleteRequest)
{
    ULootLockerHeroRequestHandler::GetGameHeroes(FLootLockerGameHeroListBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::ListPlayerHeroes(const FLootLockerHeroListDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::ListPlayerHeroes(FLootLockerHeroListBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(SteamID64, FLootLockerHeroListBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateHero(const FLootLockerCreateHeroRequest &Request, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::CreateHero(Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest &Request, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::CreateHeroWithVariation(Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHero(const int32 HeroID, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::GetHero(HeroID, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersDefaultHeroBySteamID64(SteamID64, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest &Request, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::UpdateHero(HeroID, Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::DeleteHero(HeroID, FLLHeroDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHeroInventory(const int32 HeroID, const FInventoryResponse &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::GetHeroInventory(HeroID, FPInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::GetHeroLoadout(HeroID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::GetOtherPlayersHeroLoadout(HeroID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::AddAssetToHeroLoadout(HeroID, AssetInstanceID, FHeroLoadoutReseponseBP(),  OnCompletedRequest);
}

void ULootLockerSDKManager::AddGlobalAssetToHeroLoadout(const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetToHeroLoadout(HeroID, AssetID, FHeroLoadoutReseponseBP(),  OnCompletedRequest);
}

void ULootLockerSDKManager::AddGlobalAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::AddGlobalAssetVariationToHeroLoadout(HeroID, AssetID, AssetVariationID, FHeroLoadoutReseponseBP(),  OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate &OnCompletedRequest)
{
    ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(HeroID, AssetInstanceID, FHeroLoadoutReseponseBP(), OnCompletedRequest);
}


//Character
void ULootLockerSDKManager::GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateCharacter(int CharacterId, bool IsDefault, FString& Name, const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(CharacterId, IsDefault, Name, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterTypeId, const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(IsDefault, CharacterName, CharacterTypeId, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::ListCharacterTypes(FPLootLockerListCharacterTypesResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(CharacterId,InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(CharacterId, InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& OtherPlayerPlatform /*= FString(TEXT(""))*/)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId, OtherPlayerPlatform, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(OtherCharacterId, FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::ListPlayerCharacters(FPLootLockerListPlayerCharactersResponseBP(), OnCompletedRequest);
}

// Character Progressions
void ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgressions(CharacterId, Count, After, FLootLockerPaginatedCharacterProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete)
{
    GetCharacterProgressions(CharacterId, Count, "", OnComplete);
}

void ULootLockerSDKManager::GetCharacterProgressions(const int32& CharacterId, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete)
{
    GetCharacterProgressions(CharacterId, -1, "", OnComplete);
}

void ULootLockerSDKManager::GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetCharacterProgression(CharacterId, ProgressionKey, FLootLockerCharacterProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(CharacterId, ProgressionKey, Amount, FLootLockerCharacterProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::ResetCharacterProgression(CharacterId, ProgressionKey, FLootLockerCharacterProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(CharacterId, ProgressionKey, FLootLockerDeleteProgressionBP(), OnComplete);
}

//Asset Instance Progressions


void ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(AssetInstanceId, Count, After, FLootLockerPaginatedInstanceProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const int32& Count, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(AssetInstanceId, Count, "", FLootLockerPaginatedInstanceProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetInstanceProgressions(const int32 AssetInstanceId, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgressions(AssetInstanceId, 0, "", FLootLockerPaginatedInstanceProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(AssetInstanceId, ProgressionKey, Amount, FLootLockerInstanceProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::ResetInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerInstanceProgressionWithRewardsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(AssetInstanceId, ProgressionKey, FLootLockerDeleteProgressionBP(), OnComplete);
}

//Persistent Storage
void ULootLockerSDKManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(Item, FPersistentStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

//Assets
void ULootLockerSDKManager::GetContexts(const FContextDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetContexts(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    ULootLockerAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, FAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegate &OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetUniversalAssets(After, ItemsCount, FUniversalAssetResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetAssetsByIds(AssetIds, FAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetAssetBones(FAssetBonesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::AddAssetToFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GrantAssetToPlayerInventory(const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(AssetID, AssetVariationID, AssetRentalOptionID, FGrantAssetResponseDelegateBP(), OnCompletedRequest);
}

//Asset Instance

void ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetInstanceFromPlayerInventory(int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(AssetInstanceID, FDeleteAssetInstanceResponseDelegateBP(), OnCompletedRequest);
}

//User Generated Content
void ULootLockerSDKManager::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(AssetCandidateData, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAssetCandidateAndMarkComplete(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(AssetCandidateData, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AssetCandidateData, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(FAssetCandidatesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, FResponseCallbackBP(), OnCompletedRequest);
}

// Progressions
void ULootLockerSDKManager::GetProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetProgressions(Count, After, FLootLockerPaginatedProgressionsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetProgressions(const int32& Count, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete)
{
    GetProgressions(Count, "", OnComplete);
}

void ULootLockerSDKManager::GetProgressions(const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete)
{
    GetProgressions(-1, "", OnComplete);
}

void ULootLockerSDKManager::GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetProgression(ProgressionKey, FLootLockerProgressionResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const int32& After, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete)
{
    ULootLockerProgressionsRequestHandler::GetProgressionTiers(ProgressionKey, Count, After, FLootLockerPaginatedProgressionTiersResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete)
{
    GetProgressionTiers(ProgressionKey, Count, 0, OnComplete);
}

void ULootLockerSDKManager::GetProgressionTiers(const FString& ProgressionKey, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete)
{
    GetProgressionTiers(ProgressionKey, -1, 0, OnComplete);
}

//Missions
void ULootLockerSDKManager::GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::GetAllMissions(FMissionsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::GetMission(MissionId, FMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::StartMission(MissionId, FStartMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::FinishMission(MissionId, MissionData, FFinishMissionResponseDelegateBP(), OnCompletedRequest);
}

//Maps
void ULootLockerSDKManager::GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest)
{
    ULootLockerMapsRequestHandler::GetMaps(FGetMapsResponseDelegateBP(), OnCompletedRequest);
}

//Purchasing
void ULootLockerSDKManager::PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssets(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssetsIOS(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PollingOrderStatus(PurchaseId, FPurchaseStatusResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(AssetInstanceId, FActivateRentalAssetResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOrderDetails(int32 OrderId, const bool NoProducts, const FOrderStatusDetailsDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::GetOrderDetails(OrderId, NoProducts, FOrderStatusDetailsBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LootLockerPurchaseSingleCatalogItem(const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    LootLockerPurchaseCatalogItems(WalletId, { { CatalogItemListingId, 1 } }, OnCompletedRequest);
}

void ULootLockerSDKManager::LootLockerPurchaseCatalogItems(const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(WalletId, ItemsToPurchase, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemAppleAppStorePurchaseForPlayer(const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(TransactionId, Sandboxed, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed)
{
    ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(ClassId, TransactionId, Sandboxed, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForPlayer(const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(ProductId, PurchaseToken, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(ClassId, ProductId, PurchaseToken, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::BeginSteamPurchaseRedemption(const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(ClassId, SteamId, Currency, Language, CatalogItemId, FLootLockerBeginSteamPurchaseRedemptionDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::QuerySteamPurchaseRedemptionStatus(const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(EntitlementId, FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::FinalizeSteamPurchaseRedemption(const FString& EntitlementId, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(EntitlementId, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

//Trigger
void ULootLockerSDKManager::TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest)
{
    ULootLockerTriggerEventsRequestHandler::TriggerEvent(Event, FTriggerEventResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest)
{
    ULootLockerTriggerEventsRequestHandler::GetTriggeredEvents(FTriggersResponseDelegateBP(), OnCompletedRequest);
}

//Triggers
void ULootLockerSDKManager::InvokeTriggersByKey(const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseDelegate& OnComplete)
{
    ULootLockerTriggersRequestHandler::InvokeTriggersByKey(KeysToInvoke, FLootLockerInvokeTriggersByKeyResponseBP(), OnComplete);
}

//Notifications
void ULootLockerSDKManager::ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListNotifications(bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(ShowRead, OfType, WithSource, PerPage, Page, FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListNotificationsWithPriority(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    ULootLockerNotificationsRequestHandler::ListNotifications(WithPriority, ShowRead, OfType, WithSource, PerPage, Page, FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(FLootLockerReadNotificationsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::MarkNotificationsAsRead(const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    TArray<FString> UnreadNotificationIds;
    for (const FLootLockerNotification& Notification : Notifications)
    {
        if (!Notification.Read)
        {
            UnreadNotificationIds.Add(Notification.Id);
        }
    }
    MarkNotificationsAsReadByIds(UnreadNotificationIds, OnComplete);
}

void ULootLockerSDKManager::MarkNotificationsAsReadByIds(const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(NotificationIDs, FLootLockerReadNotificationsResponseBP(), OnComplete);
}

//Collectables
void ULootLockerSDKManager::GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest)
{
    ULootLockerCollectablesRequestHandler::GetAllCollectables(FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    ULootLockerCollectablesRequestHandler::CollectItem(Item, FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

//Messages
void ULootLockerSDKManager::GetMessages(const FMessagesResponseDelegate& OnCompletedRequest)
{
    ULootLockerMessagesRequestHandler::GetMessages(FMessagesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListLeaderboards(int Count, int After, const FLootLockerListLeaderboardsResponseDelegate& OnCompletedRequest)
{
    ULootLockerLeaderboardRequestHandler::ListLeaderboards(Count, After, FLootLockerListLeaderboardsResponseBP(), OnCompletedRequest);
}

// Leaderboards
void ULootLockerSDKManager::GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboard_key = LeaderboardKey;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(MemberRequest, FLootLockerGetMemberRankResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetByListMembersRequest, LeaderboardKey, FLootLockerGetByListOfMembersResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboard_key = LeaderboardKey;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, FLootLockerGetScoreListResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
    GetScoreList(LeaderboardKey, Count, -1, OnCompletedRequest);
}

void ULootLockerSDKManager::SubmitScore(FString MemberId, const FString LeaderboardKey, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(SubmitScoreRequest, LeaderboardKey, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetAllMemberRanksRequest GetAllMemberRanksRequest;
    GetAllMemberRanksRequest.after = After;
    GetAllMemberRanksRequest.count = Count;
    GetAllMemberRanksRequest.member_id = MemberId;
    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(GetAllMemberRanksRequest, FLootLockerGetAllMemberRanksResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest)
{
    ULootLockerLeaderboardArchiveRequestHandler::ListLeaderboardArchive(LeaderboardKey, FLootLockerLeaderboardArchiveResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest)
{
    ULootLockerLeaderboardArchiveRequestHandler::GetLeaderboardArchive(Key, Count, After, FLootLockerLeaderboardArchiveDetailReponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetLeaderboardDetails(const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest)
{
    ULootLockerLeaderboardRequestHandler::GetLeaderboardDetails(LeaderboardKey, FLootLockerLeaderboardDetailsResponseBP(), OnCompletedRequest);
}

// Droptables
void ULootLockerSDKManager::ComputeAndLockDropTable(const int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(TableId, FLootLockerComputeAndLockDropTableResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PickDropsFromDropTable(const TArray<int> Picks,const  int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
    FLootLockerPickDropsFromDropTableRequest Request;
    Request.picks = Picks;
    ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(Request, TableId, FFLootLockerPickDropsFromDropTableResponseBP(), OnCompletedRequest);
}

// Currencies

void ULootLockerSDKManager::ListCurrencies(const FLootLockerListCurrenciesResponseDelegate& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::ListCurrencies(FLootLockerListCurrenciesResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyDetails(const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDetails(CurrencyCode, FLootLockerGetCurrencyDetailsResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnCompletedRequest)
{
    ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(CurrencyCode, FLootLockerListDenominationsResponseBP(), OnCompletedRequest);
}

// Balances

void ULootLockerSDKManager::ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete)
{
    ULootLockerBalanceRequestHandler::ListBalancesInWallet(WalletID, FLootLockerListBalancesForWalletResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByWalletID(WalletID, FLootLockerGetWalletResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
    ULootLockerBalanceRequestHandler::GetWalletByHolderID(HolderULID, HolderType, FLootLockerGetWalletResponseBP(), OnComplete);
}

void ULootLockerSDKManager::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete)
{
    ULootLockerBalanceRequestHandler::CreditBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerCreditWalletResponseBP(), OnComplete);
}

void ULootLockerSDKManager::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete)
{
    ULootLockerBalanceRequestHandler::DebitBalanceToWallet(WalletID, CurrencyID, Amount, FLootLockerDebitWalletResponseBP(), OnComplete);
}

// Catalogs

void ULootLockerSDKManager::ListCatalogs(const FLootLockerListCatalogsResponseDelegate& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogs(FLootLockerListCatalogsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseDelegate& OnComplete)
{
    ULootLockerCatalogRequestHandler::ListCatalogItems(CatalogKey, Count, After, FLootLockerListCatalogPricesResponseBP(), OnComplete);
}

// Entitlements
void ULootLockerSDKManager::ListEntitlements(const int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete)
{
ULootLockerEntitlementRequestHandler::ListEntitlements(Count, After, FLootLockerListEntitlementsResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetEntitlement(const FString& EntitlementID, FLootLockerSingleEntitlementResponseDelegate& OnComplete)
{
    ULootLockerEntitlementRequestHandler::GetEntitlement(EntitlementID, FLootLockerSingleEntitlementResponseBP(), OnComplete);
}

// Feedback
void ULootLockerSDKManager::ListPlayerFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ELootLockerFeedbackType::Player, FLootLockerListFeedbackCategoryResponseBP(), OnComplete);

}

void ULootLockerSDKManager::ListGameFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ELootLockerFeedbackType::Game, FLootLockerListFeedbackCategoryResponseBP(), OnComplete);

}

void ULootLockerSDKManager::ListUGCFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete)
{
    ULootLockerFeedbackRequestHandler::ListFeedbackCategories(ELootLockerFeedbackType::Ugc, FLootLockerListFeedbackCategoryResponseBP(), OnComplete);

}

void ULootLockerSDKManager::SendPlayerFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(Ulid, Description, CategoryID, ELootLockerFeedbackType::Player, FLootLockerSendFeedbackResponseBP(), OnComplete);

}

void ULootLockerSDKManager::SendGameFeedback(const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback("", Description, CategoryID, ELootLockerFeedbackType::Game, FLootLockerSendFeedbackResponseBP(), OnComplete);

}

void ULootLockerSDKManager::SendUGCFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
    ULootLockerFeedbackRequestHandler::SendFeedback(Ulid, Description, CategoryID, ELootLockerFeedbackType::Ugc, FLootLockerSendFeedbackResponseBP(), OnComplete);

}

// Metadata

void ULootLockerSDKManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    ULootLockerMetadataRequestHandler::ListMetadata(Source, SourceID, -1, -1, FString(), TArray<FString>(), IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    ULootLockerMetadataRequestHandler::ListMetadata(Source, SourceID, Page, PerPage, FString(), TArray<FString>(), IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    ULootLockerMetadataRequestHandler::ListMetadata(Source, SourceID, -1, -1, FString(), Tags, IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    ULootLockerMetadataRequestHandler::ListMetadata(Source, SourceID, Page, PerPage, FString(), Tags, IgnoreFiles, FLootLockerListMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const FLootLockerGetMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    ULootLockerMetadataRequestHandler::GetMetadata(Source, SourceID, Key, IgnoreFiles, FLootLockerGetMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::GetMultisourceMetadata(const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet,	const FLootLockerGetMultisourceMetadataResponseDelegate& OnComplete, const bool IgnoreFiles)
{
    ULootLockerMetadataRequestHandler::GetMultisourceMetadata(SourcesAndKeysToGet, IgnoreFiles, FLootLockerGetMultisourceMetadataResponseBP(), OnComplete);
}

void ULootLockerSDKManager::SetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform,	const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
    ULootLockerMetadataRequestHandler::SetMetadata(Source, SourceID, MetadataToActionsToPerform, FLootLockerSetMetadataResponseBP(), OnComplete);
}

// Miscellaneous
void ULootLockerSDKManager::GetServerTime(const FTimeResponseDelegate& OnCompletedRequest)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(FTimeResponseDelegateBP(), OnCompletedRequest);
}

FString ULootLockerSDKManager::GetLastActivePlatform() {
    return ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform();
}
