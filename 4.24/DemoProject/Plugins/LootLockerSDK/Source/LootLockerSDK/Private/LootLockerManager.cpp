// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

void ULootLockerManager::StartSession(const FString& PlayerId, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::StartSession(PlayerId, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::VerifyPlayer(const FString& CachedSteamToken, const FAuthDefaultResponseBP& OnVerifyPlayerRequestCompleted)
{
    ULootLockerAuthenticationRequestHandler::VerifyPlayer(CachedSteamToken, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const FString& PlayerId, const  FAuthDefaultResponseBP& OnEndSessionRequestCompleted)
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

void ULootLockerManager::GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const  FPInfoResponseBP& OnGetOtherPlayerInfoRequestCompleted)
{
    ULootLockerPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, OnGetOtherPlayerInfoRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    ULootLockerPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
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


void ULootLockerManager::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::UpdateCharacter(bool isDefault, FString& Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(isDefault, Name, OnCompletedRequest);
}

void ULootLockerManager::CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP)
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
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(CharacterId);
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId,OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToCharacterById(int CharacterId,int AssetId, int AssetVariationId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(CharacterId);
    ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(OtherPlayerId);
    ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests,OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(OtherCharacterId);
    ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

void ULootLockerManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerManager::AddItemsToPersistentStorage(const TArray<FLootLockerPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, OnPersistentStorageItemsAddRequestCompleted);
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

void ULootLockerManager::GetAssets(const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted,int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, bool IncludeUGC)
{
    ULootLockerAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, OnGetAssetsRequestCompleted);
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

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FLootLockerAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
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

void ULootLockerManager::CreateAssetCandidate(const FLootLockerAssetCandidate2& AsssetCandidate, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerAssetCandidate2& AsssetCandidate, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, OnUpdateAssetCandidateCompleted);
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
