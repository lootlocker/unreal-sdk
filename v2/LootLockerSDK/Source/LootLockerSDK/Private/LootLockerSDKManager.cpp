// Copyright (c) 2021 LootLocker


#include "LootLockerSDKManager.h"

#include <concrt.h>

//Authentication
void ULootLockerSDKManager::WhiteLabelCreateAccount(const FString &Email, const FString &Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelCreateAccount(Email, Password, FLootLockerLoginResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate &OnCompletedRequest, const bool Remember /* = false */)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelLogin(Email, Password, Remember, FLootLockerLoginResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartSession(const FString& PlayerIdentifier, const FLootLockerSessionResponse& OnCompleteRequest)
{
	ULootLockerAuthenticationRequestHandler::StartSession(PlayerIdentifier, FAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::WhiteLabelStartSession(const FLootLockerSessionResponse &OnCompletedRequest)
{
	ULootLockerAuthenticationRequestHandler::WhiteLabelStartSession(FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelVerifySession(const FLootLockerWhiteLabelVerifySessionDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelVerifySession(FLootLockerVerifySessionResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelRequestUserVerification(const int &UserId, const FLootLockerDefaultDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestUserVerification(UserId, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::WhiteLabelRequestPasswordReset(const FString &Email, const FLootLockerDefaultDelegate &OnCompletedRequest)
{
    ULootLockerAuthenticationRequestHandler::WhiteLabelRequestPasswordReset(Email, FLootLockerDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GuestLogin(const FString& playerIdentifier, const FLootLockerSessionResponse &OnCompletedRequest)
{
	ULootLockerAuthenticationRequestHandler::GuestLogin(playerIdentifier, FAuthResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest, const FString Platform)
{
	ULootLockerAuthenticationRequestHandler::VerifyPlayer(PlatformToken, Platform, FAuthDefaultResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::EndSession(const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	ULootLockerAuthenticationRequestHandler::EndSession(FAuthDefaultResponseBP(), OnCompleteRequest);
}
//Player
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
	ULootLockerPlayerRequestHandler::GetFullInventory(FPInventoryResponseBP(),OnCompletedRequest, StartIndex);
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

void ULootLockerSDKManager::SetPlayerName(FString name, const FPNameResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::SetPlayerName(name, FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerName(const FPNameResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetPlayerName(FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(Request, FPMultiplePlayerNamesBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(Request, FPMultiplePlayersPlatformIdsBP(), OnCompletedRequest);
}

//Files
void ULootLockerSDKManager::UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
	ULLPlayerFilesRequestHandler::UploadFile(Request, FLootLockerUploadFileBP(), OnComplete);
}

void ULootLockerSDKManager::ListFiles(const FLootLockerFileListDelegate &OnComplete)
{
	ULLPlayerFilesRequestHandler::ListFiles(FLootLockerFileListBP(), OnComplete);
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

// heroes
void ULootLockerSDKManager::GetGameHeroes(const FLootLockerGameHeroListDelegate& OnCompleteRequest)
{
	ULootLockerHeroRequestHandler::GetGameHeroes(FLootLockerGameHeroListBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::ListPlayerHeroes(const FLootLockerHeroListDelegate &OnCompletedRequest)
{
	ULootLockerHeroRequestHandler::ListPlayerHeroes(FLootLockerHeroListBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListOtherPlayersHeroesBySteamID64(const int32 SteamID64, const FLootLockerHeroListDelegate &OnCompletedRequest)
{
	ULootLockerHeroRequestHandler::ListOtherPlayersHeroesBySteamID64(SteamID64, FLootLockerHeroListBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateHero(const FLootLockerCreateHeroRequest &Request, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
	ULootLockerHeroRequestHandler::CreateHero(Request, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetHero(const int32 HeroID, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
{
	ULootLockerHeroRequestHandler::GetHero(HeroID, FLootLockerPlayerHeroBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersDefaultHeroBySteamID64(const int32 SteamID64, const FLootLockerPlayerHeroDelegate &OnCompletedRequest)
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

void ULootLockerSDKManager::CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterId, const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(IsDefault, CharacterName, CharacterId, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
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

void ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(OtherCharacterId, FContextDelegateBP(), OnCompletedRequest);
}

//Persisitent Storage
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

//Asset Instance

void ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
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

//User Generated Candidate
void ULootLockerSDKManager::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(AssetCandidateData, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
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

void ULootLockerSDKManager::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(AssetId, FActivateRentalAssetResponseDelegateBP(), OnCompletedRequest);
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

// Leaderboards
void ULootLockerSDKManager::GetMemberRank(int LeaderboardId, int MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboardId = LeaderboardId;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(MemberRequest, FLootLockerGetMemberRankResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetByListOfMembers(TArray<FString> Members, int LeaderboardId, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetByListMembersRequest, LeaderboardId,FLootLockerGetByListOfMembersResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreList(int LeaderboardId, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboardId = LeaderboardId;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, FLootLockerGetScoreListResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreListInitial(int LeaderboardId, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = -1;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboardId = LeaderboardId;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, FLootLockerGetScoreListResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SubmitScore(FString MemberId, const int LeaderboardId, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    SubmitScoreRequest.metadata = Metadata;
    ULootLockerLeaderboardRequestHandler::SubmitScore(SubmitScoreRequest, LeaderboardId, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllMemberRanks(int MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetAllMemberRanksRequest GetAllMemberRanksRequest;
    GetAllMemberRanksRequest.after = After;
    GetAllMemberRanksRequest.count = Count;
    GetAllMemberRanksRequest.memberId = MemberId;
    ULootLockerLeaderboardRequestHandler::GetAllMemberRanks(GetAllMemberRanksRequest, FLootLockerGetAllMemberRanksResponseBP(), OnCompletedRequest);
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

// Miscellaneous
void ULootLockerSDKManager::GetServerTime(const FTimeResponseDelegate& OnCompletedRequest)
{
    ULootLockerMiscellaneousRequestHandler::GetServerTime(FTimeResponseDelegateBP(), OnCompletedRequest);
}
