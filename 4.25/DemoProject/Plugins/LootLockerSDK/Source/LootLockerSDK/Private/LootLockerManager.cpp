// Copyright (c) 2020 LootLocker

#include "LootLockerManager.h"

void ULootLockerManager::StartSession(const FString& PlayerId)
{
    UAuthenticationRequestHandler::StartSession(PlayerId, OnStartedSessionRequestCompleted);
}

void ULootLockerManager::VerifyPlayer(const FString& CachedSteamToken)
{
    UAuthenticationRequestHandler::VerifyPlayer(CachedSteamToken, OnVerifyPlayerRequestCompleted);
}

void ULootLockerManager::EndSession(const FString& PlayerId)
{
    UAuthenticationRequestHandler::EndSession(OnEndSessionRequestCompleted);
}

void ULootLockerManager::GetPlayerInfo()
{
    UPlayerRequestHandler::GetPlayerInfo(OnGetPlayerInfoRequestCompleted);
}

void ULootLockerManager::GetInventory()
{
    UPlayerRequestHandler::GetInventory(OnGetInventoryRequestCompleted);
}

void ULootLockerManager::SubmitXP(int Points)
{
    UPlayerRequestHandler::SubmitXp(Points, OnSubmitXPRequestCompleted);
}

void ULootLockerManager::GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests)
{
    UPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, OnGetOtherPlayerInfoRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetActivationNotification()
{
    UPlayerRequestHandler::CheckPlayerAssetNotification(OnCheckPlayerAssetActivationNotificationRequestCompleted);
}

void ULootLockerManager::CheckPlayerAssetDeactivationNotification()
{
    UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerManager::GetCharacterLoadout()
{
    UCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerManager::EquipAssetToDefaultCharacter(int InstanceId)
{
    UCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(CharacterId);
    UCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId,OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToDefaultCharacter(int InstanceId)
{
    UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::UnEquipAssetToCharacterById(int CharacterId,int AssetId, int AssetVariationId)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(CharacterId);
    UCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerManager::GetCurrentLoadoutToDefaultCharacter()
{
    UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(OtherPlayerId);
    UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests,OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsToDefaultCharacter()
{
    UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerManager::GetEquipableContextsByCharacterId(const FString& OtherCharacterId)
{
    FLootLockerGetRequests GetRequests;
    GetRequests.args.Add(OtherCharacterId);
    UCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

void ULootLockerManager::GetEntirePersistentStorage()
{
    UPersistentStorageRequestHandler::GetEntirePersistentStorage(OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerManager::GetItemFromPersistentStorage(const FString& Key)
{
    UPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerManager::AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items)
{
    UPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, OnPersistentStorageItemsAddRequestCompleted);
}

void ULootLockerManager::DeleteItemFromPersistentStorage(const FString& Key)
{
    UPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, OnPersistentStorageItemDeleteRequestCompleted);
}

void ULootLockerManager::GetPlayerPersistentStorage(const FString& PlayerId)
{
    UPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, OnGetPlayerPersistentStorageRequestCompleted);
}

void ULootLockerManager::GetContexts()
{
    UAssetsRequestHandler::GetContexts(OnGetContextsRequestCompleted);
}

void ULootLockerManager::GetAssets(int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC)
{
    UAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, OnGetAssetsRequestCompleted);
}

void ULootLockerManager::GetAssetsByIds(const TArray<int>& AssetIds)
{
    UAssetsRequestHandler::GetAssetsByIds(AssetIds, OnGetAssetsByIdsRequestCompleted);
}

void ULootLockerManager::GetAssetBones()
{
    UAssetsRequestHandler::GetAssetBones(OnGetAssetBonesRequestCompleted);
}

void ULootLockerManager::GetFavouriteAssetIndices()
{
    UAssetsRequestHandler::GetFavouriteAssetIndices(OnGetFavouriteAssetIndicesRequestCompleted);
}

void ULootLockerManager::AddAssetToFavourites(int AssetId)
{
    UAssetsRequestHandler::AddAssetToFavourites(AssetId, OnAddAssetToFavouritesRequestCompleted);
}

void ULootLockerManager::RemoveAssetFromFavourites(int AssetId)
{
    UAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, OnRemoveAssetFromFavouritesRequestCompleted);
}

void ULootLockerManager::GetAllKeyValuePairsForAssetInstance()
{
    UAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(OnGetAllKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId)
{
    UAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted);
}

void ULootLockerManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId)
{
    UAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, OnGetAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item)
{
    UAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, OnCreateAKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items)
{
    UAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item)
{
    UAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId)
{
    UAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);
}

void ULootLockerManager::InspectLootBox(int AssetInstanceId)
{
    UAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, OnInspectLootBoxCompleted);
}

void ULootLockerManager::OpenLootBox(int AssetInstanceId)
{
    UAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, OnOpenLootBoxCompleted);
}

void ULootLockerManager::CreateAssetCandidate(const FAssetCandidate& AsssetCandidate)
{
    UUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, OnCreateAssetCandidateCompleted);
}

void ULootLockerManager::UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate)
{
    UUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, OnUpdateAssetCandidateCompleted);
}

void ULootLockerManager::DeleteAssetCandidate(int AssetCandidateId)
{
    UUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, OnDeleteAssetCandidateCompleted);
}

void ULootLockerManager::GetAllAssetCandidates()
{
    UUserGeneratedContentRequestHandler::GetAllAssetCandidates(OnGetAllAssetCandidatesCompleted);
}

void ULootLockerManager::GetAssetCandidate(int AssetCandidateId)
{
    UUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, OnGetAssetCandidateCompleted);
}

void ULootLockerManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose)
{
    UUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted);
}

void ULootLockerManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId)
{
    UUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted);
}

void ULootLockerManager::GetAllMissions()
{
    UMissionsRequestHandler::GetAllMissions(OnGetAllMissionsCompleted);
}

void ULootLockerManager::GetMission(int MissionId)
{
    UMissionsRequestHandler::GetMission(MissionId, OnGetMissionCompleted);
}

void ULootLockerManager::StartMission(int MissionId)
{
    UMissionsRequestHandler::StartMission(MissionId, OnStartMissionCompleted);
}

void ULootLockerManager::FinishMission(int MissionId, const FFinishMissionData& MissionData)
{
    UMissionsRequestHandler::FinishMission(MissionId, MissionData, OnFinishMissionCompleted);
}

void ULootLockerManager::GetMaps()
{
    UMapsRequestHandler::GetMaps(OnGetMapsCompleted);
}

void ULootLockerManager::PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData)
{
    UPurchasesRequestHandler::PurchaseAssets(PurchaseData, OnPurchaseAssetsCompleted);
}

void ULootLockerManager::PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData)
{
    UPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, OnPurchaseAssetsAndroidCompleted);
}

void ULootLockerManager::PurchaseAssetsIOS(const TArray<FVerifyPurchaseIosData>& PurchaseData)
{
    UPurchasesRequestHandler::PurchaseAssetsIOS(PurchaseData, OnPurchaseAssetsIOSCompleted);
}

void ULootLockerManager::PollingOrderStatus(int PurchaseId)
{
    UPurchasesRequestHandler::PollingOrderStatus(PurchaseId, OnPollingStatusCompleted);
}

void ULootLockerManager::ActivateRentalAsset(int AssetId)
{
    UPurchasesRequestHandler::ActivateRentalAsset(AssetId, OnActivateRentalAssetCompleted);
}

void ULootLockerManager::TriggerEvent(const FTriggerEvent& Event)
{
    UTriggerEventsRequestHandler::TriggerEvent(Event, OnTriggerEventCompleted);
}

void ULootLockerManager::GetTriggeredEvents()
{
    UTriggerEventsRequestHandler::GetTriggeredEvents(OnGetTriggeredEventsCompleted);
}

void ULootLockerManager::GetAllCollectables()
{
    UCollectablesRequestHandler::GetAllCollectables(OnGetAllCollectablesCompleted);
}

void ULootLockerManager::CollectItem(const FCollectItemPayload& Item)
{
    UCollectablesRequestHandler::CollectItem(Item, OnCollectItemCompleted);
}

void ULootLockerManager::GetMessages()
{
    UMessagesRequestHandler::GetMessages(OnGetMessagesCompleted);
}
