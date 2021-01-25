// Copyright (c) 2021 LootLocker

#include "LootLockerManager.h"

void ULootLockerManager::StartSession(const FString& PlayerId, const FAuthResponseBP& OnStartedSessionRequestCompleted)
{
    UAuthenticationRequestHandler::StartSession(PlayerId, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::VerifyPlayer(const FString& CachedSteamToken, const FAuthDefaultResponseBP& OnVerifyPlayerRequestCompleted)
{
    UAuthenticationRequestHandler::VerifyPlayer(CachedSteamToken, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const FString& PlayerId, const  FAuthDefaultResponseBP& OnEndSessionRequestCompleted)
{
    UAuthenticationRequestHandler::EndSession(OnEndSessionRequestCompleted);
}

void ULootLockerManager::GetPlayerInfo(const FPInfoResponseBP& OnGetPlayerInfoRequestComplete)
{
    UPlayerRequestHandler::GetPlayerInfo(OnGetPlayerInfoRequestComplete);
}

void ULootLockerManager::GetInventory(const FPInventoryResponseBP& OnGetInventoryRequestCompleted)
{
    UPlayerRequestHandler::GetInventory(OnGetInventoryRequestCompleted);
}

void ULootLockerManager::SubmitXP(int Points, const FPSubmitResponseBP& OnSubmitXPRequestCompleted)
{
    UPlayerRequestHandler::SubmitXp(Points, OnSubmitXPRequestCompleted);
}

void ULootLockerManager::GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const  FPInfoResponseBP& OnGetOtherPlayerInfoRequestCompleted)
{
    UPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, OnGetOtherPlayerInfoRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    UPlayerRequestHandler::CheckPlayerAssetNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted)
{
    UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::GetCurrencyBalance(const FPBalanceResponseBP& OnGetCurrencyBalance)
{
    UPlayerRequestHandler::GetCurrencyBalance(OnGetCurrencyBalance);
}


void ULootLockerManager::InitiateDLCMigration(const FResponseCallbackBP& OnInitiateDlcMigration)
{
    UPlayerRequestHandler::InitiateDLCMigration(OnInitiateDlcMigration);
}


void ULootLockerManager::GetDLCsMigration(const FPDlcResponseBP& OnGotDlcMigration)
{
    UPlayerRequestHandler::GetDLCsMigration(OnGotDlcMigration);
}


void ULootLockerManager::SetProfilePrivate(const FResponseCallbackBP& OnProfileSetPrivate)
{
    UPlayerRequestHandler::SetProfilePrivate(OnProfileSetPrivate);
}

void ULootLockerManager::SetProfilePublic(const FResponseCallbackBP& OnProfileSetPublic)
{
    UPlayerRequestHandler::SetProfilePublic(OnProfileSetPublic);
}


void ULootLockerManager::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted)
{
    UCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::UpdateCharacter(bool isDefault, FString& Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest)
{
    UCharacterRequestHandler::UpdateCharacter(isDefault, Name, OnCompletedRequest);
}

void ULootLockerManager::EquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted)
{
    UCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(CharacterId);
    UCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId,OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted)
{
    UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToCharacterById(int CharacterId,int AssetId, int AssetVariationId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(CharacterId);
    UCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter(const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(OtherPlayerId);
    UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests,OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted)
{
    UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(OtherCharacterId);
    UCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

void ULootLockerManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted)
{
    UPersistentStorageRequestHandler::GetEntirePersistentStorage(OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted)
{
    UPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerManager::AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted)
{
    UPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, OnPersistentStorageItemsAddRequestCompleted);
}

void ULootLockerManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted)
{
    UPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, OnPersistentStorageItemDeleteRequestCompleted);
}

void ULootLockerManager::GetPlayerPersistentStorage(const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted)
{
    UPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, OnGetPlayerPersistentStorageRequestCompleted);
}

void ULootLockerManager::GetContexts(const FContextDelegateBP& OnGetContextsRequestCompleted)
{
    UAssetsRequestHandler::GetContexts(OnGetContextsRequestCompleted);
}

void ULootLockerManager::GetAssets(const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted,int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC)
{
    UAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, OnGetAssetsRequestCompleted);
}

void ULootLockerManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted)
{
    UAssetsRequestHandler::GetAssetsByIds(AssetIds, OnGetAssetsByIdsRequestCompleted);
}

void ULootLockerManager::GetAssetBones(const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted)
{
    UAssetsRequestHandler::GetAssetBones(OnGetAssetBonesRequestCompleted);
}

void ULootLockerManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted)
{
    UAssetsRequestHandler::GetFavouriteAssetIndices(OnGetFavouriteAssetIndicesRequestCompleted);
}

void ULootLockerManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted)
{
    UAssetsRequestHandler::AddAssetToFavourites(AssetId, OnAddAssetToFavouritesRequestCompleted);
}

void ULootLockerManager::RemoveAssetFromFavourites(int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted)
{
    UAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, OnRemoveAssetFromFavouritesRequestCompleted);
}

void ULootLockerManager::GetAllKeyValuePairsForAssetInstance(const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(OnGetAllKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, OnGetAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, OnCreateAKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted)
{
    UAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::InspectLootBox(int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted)
{
    UAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, OnInspectLootBoxCompleted);
}

void ULootLockerManager::OpenLootBox(int AssetInstanceId, const  FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted)
{
    UAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, OnOpenLootBoxCompleted);
}

void ULootLockerManager::CreateAssetCandidate(const FAssetCandidate& AsssetCandidate, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted)
{
    UUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted)
{
    UUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, OnUpdateAssetCandidateCompleted);
}

void ULootLockerManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted)
{
    UUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, OnDeleteAssetCandidateCompleted);
}

void ULootLockerManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted)
{
    UUserGeneratedContentRequestHandler::GetAllAssetCandidates(OnGetAllAssetCandidatesCompleted);
}

void ULootLockerManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted)
{
    UUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, OnGetAssetCandidateCompleted);
}

void ULootLockerManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted)
{
    UUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted);
}

void ULootLockerManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted)
{
    UUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted);
}

void ULootLockerManager::GetAllMissions(const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted)
{
    UMissionsRequestHandler::GetAllMissions(OnGetAllMissionsCompleted);
}

void ULootLockerManager::GetMission(int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted)
{
    UMissionsRequestHandler::GetMission(MissionId, OnGetMissionCompleted);
}

void ULootLockerManager::StartMission(int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted)
{
    UMissionsRequestHandler::StartMission(MissionId, OnStartMissionCompleted);
}

void ULootLockerManager::FinishMission(int MissionId, const FFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted)
{
    UMissionsRequestHandler::FinishMission(MissionId, MissionData, OnFinishMissionCompleted);
}

void ULootLockerManager::GetMaps(const FGetMapsResponseDelegateBP& OnGetMapsCompleted)
{
    UMapsRequestHandler::GetMaps(OnGetMapsCompleted);
}

void ULootLockerManager::PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsCompleted)
{
    UPurchasesRequestHandler::PurchaseAssets(PurchaseData, OnPurchaseAssetsCompleted);
}

void ULootLockerManager::PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData, const  FPurchaseResponseDelegateBP& OnPurchaseAssetsAndroidCompleted)
{
    UPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, OnPurchaseAssetsAndroidCompleted);
}

void ULootLockerManager::PurchaseAssetsIOS(const TArray<FVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsIOSCompleted)
{
    UPurchasesRequestHandler::PurchaseAssetsIOS(PurchaseData, OnPurchaseAssetsIOSCompleted);
}

void ULootLockerManager::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnPollingStatusCompleted)
{
    UPurchasesRequestHandler::PollingOrderStatus(PurchaseId, OnPollingStatusCompleted);
}

void ULootLockerManager::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted)
{
    UPurchasesRequestHandler::ActivateRentalAsset(AssetId, OnActivateRentalAssetCompleted);
}

void ULootLockerManager::TriggerEvent(const FTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnTriggerEventCompleted)
{
    UTriggerEventsRequestHandler::TriggerEvent(Event, OnTriggerEventCompleted);
}

void ULootLockerManager::GetTriggeredEvents(const FTriggersResponseDelegateBP& OnGetTriggeredEventsCompleted)
{
    UTriggerEventsRequestHandler::GetTriggeredEvents(OnGetTriggeredEventsCompleted);
}

void ULootLockerManager::GetAllCollectables(const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted)
{
    UCollectablesRequestHandler::GetAllCollectables(OnGetAllCollectablesCompleted);
}

void ULootLockerManager::CollectItem(const FCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted)
{
    UCollectablesRequestHandler::CollectItem(Item, OnCollectItemCompleted);
}

void ULootLockerManager::GetMessages(const FMessagesResponseDelegateBP& OnGetMessagesCompleted)
{
    UMessagesRequestHandler::GetMessages(OnGetMessagesCompleted);
}
