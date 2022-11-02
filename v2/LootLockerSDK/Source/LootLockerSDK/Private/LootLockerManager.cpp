// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

#include <concrt.h>

void ULootLockerManager::StartSession(const FString& playerIdentifier, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartSession(playerIdentifier, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::WhiteLabelStartSession(const FAuthResponseBP &OnStartWhiteLabelSessionRequestCompleted)
{
	ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(OnStartWhiteLabelSessionRequestCompleted);
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

void ULootLockerManager::GuestLogin(const FString& playerIdentifier, const FAuthResponseBP &OnCompletedRequestBP)
{
	ULootLockerAuthenticationRequestHandler::GuestLogin(playerIdentifier, OnCompletedRequestBP);
}

void ULootLockerManager::VerifyPlayer(const FString& SteamSessionTicket, const FAuthDefaultResponseBP& OnVerifyPlayerRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(SteamSessionTicket, OnVerifyPlayerRequestCompleted);
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
void ULootLockerManager::SetPlayerName(FString name, const FPNameResponseBP& OnSetPlayerName)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(name, OnSetPlayerName);
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


void ULootLockerManager::UploadFile(const FLootLockerFileUploadRequest &Request, const FLootLockerUploadFileBP &OnComplete)
{
	ULLPlayerFilesRequestHandler::UploadFile(Request, OnComplete, FLootLockerUploadFileDelegate());
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
	ULLPlayerFilesRequestHandler::GetSingleFile(FileID, OnComplete, FLootLockerUploadFileDelegate());
}

void ULootLockerManager::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP &OnComplete)
{
	ULLPlayerFilesRequestHandler::DeletePlayerFile(FileID, OnComplete, FLootLockerFileDeletedDelegate());
}

void ULootLockerManager::GetGameHeroes(const FLootLockerGameHeroListBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::GetGameHeroes(OnCompleteBP, FLootLockerGameHeroListDelegate());
}

void ULootLockerManager::ListPlayerHeroes(const FLootLockerHeroListBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::ListPlayerHeroes(OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::ListOtherPlayersHeroesBySteamID64(const int32 SteamID64, const FLootLockerHeroListBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(SteamID64, OnCompleteBP, FLootLockerHeroListDelegate());
}

void ULootLockerManager::CreateHero(const FLootLockerCreateHeroRequest &Request, const FLootLockerPlayerHeroBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::CreateHero(Request, OnCompleteBP, FLootLockerPlayerHeroDelegate());
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

void ULootLockerManager::GetHeroInventory(const int32 HeroID, const FPInventoryResponseBP &OnCompleteBp)
{
	ULootLockerHeroRequestHandler::GetHeroInventory(HeroID, OnCompleteBp, FInventoryResponse());
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

void ULootLockerManager::RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP &OnCompleteBP)
{
	ULootLockerHeroRequestHandler::RemoveAssetToHeroLoadout(HeroID, AssetInstanceID, OnCompleteBP, FHeroLoadoutReseponseDelegate());
}

void ULootLockerManager::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::UpdateCharacter(int CharacterId, bool isDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(CharacterId,isDefault, Name, OnCompletedRequest);
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
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId,OnEquipAssetToCharacterByIdRequestCompleted);
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

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter( FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId ,OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId( int OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(OtherCharacterId, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

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


void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(OnGetAllKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
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

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
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

void ULootLockerManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidate, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AssetCandidate, OnUpdateAssetCandidateCompleted);
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

void ULootLockerManager::GetOrderDetails(int32 OrderId, const bool noProductes, const FOrderStatusDetailsBP &OnCompleteBP)
{
	ULootLockerPurchasesRequestHandler::GetOrderDetails(OrderId, noProductes, OnCompleteBP, FOrderStatusDetailsDelegate());
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

void ULootLockerManager::GetMemberRank(int LeaderboardId, int MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboardId = LeaderboardId;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(MemberRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetAllMemberRanks(int MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetAllMemberRanksRequest MemberRanksRequest;
    MemberRanksRequest.memberId = MemberId;
    MemberRanksRequest.after = After;
    MemberRanksRequest.count = Count;

    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(MemberRanksRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetByListOfMembers(TArray<FString> Members, int LeaderboardId, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetByListMembersRequest, LeaderboardId, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreList(int LeaderboardId, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboardId = LeaderboardId;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, OnCompletedRequestBP);
}

void ULootLockerManager::GetScoreListInitial(int LeaderboardId, int Count,  const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = -1;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboardId = LeaderboardId;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, OnCompletedRequestBP);
}


void ULootLockerManager::SubmitScore(FString MemberId, int LeaderboardId, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(SubmitScoreRequest, LeaderboardId,OnCompletedRequestBP);
}

void ULootLockerManager::ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP)
{
    ULootLockerDropTablesRequestHandler::ComputeAndLockDropTable(TableId, OnCompletedRequestBP);
}

void ULootLockerManager::PickDropsFromDropTable(TArray<int> picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP)
{
    FLootLockerPickDropsFromDropTableRequest request;
    request.picks = picks;
    ULootLockerDropTablesRequestHandler::PickDropsFromDropTable(request,TableId, OnCompletedRequestBP);
}


