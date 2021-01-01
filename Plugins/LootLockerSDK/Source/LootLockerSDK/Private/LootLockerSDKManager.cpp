// Copyright (c) 2020 LootLocker


#include "LootLockerSDKManager.h"

//Authentication
void ULootLockerSDKManager::StartSession(const FString& PlayerId, const FLootLockerSessionResponse& OnCompleteRequest)
{
	UAuthenticationRequestHandler::StartSession(PlayerId, FAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::VerifyPlayer(const FString& CachedSteamToken, const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	UAuthenticationRequestHandler::VerifyPlayer(CachedSteamToken, FAuthDefaultResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::EndSession(const FString& PlayerId, const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	UAuthenticationRequestHandler::EndSession(FAuthDefaultResponseBP(), OnCompleteRequest);
}
//Player
void ULootLockerSDKManager::GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	UPlayerRequestHandler::GetPlayerInfo(FPInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetInventory(const FLootLockerInventoryResponse& OnCompletedRequest)
{
	UPlayerRequestHandler::GetInventory(FPInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SubmitXP(int Points, const FLootLockerSubmitXpResponse& OnCompletedRequest)
{
	UPlayerRequestHandler::SubmitXp(Points, FPSubmitResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	UPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, FPInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	UPlayerRequestHandler::CheckPlayerAssetNotification(FPAssetNotificationResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetDeactivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(FPAssetNotificationResponseBP(), OnCompletedRequest);
}

//Character
void ULootLockerSDKManager::GetCharacterLoadout(const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	UCharacterRequestHandler::GetCharacterLoadout(FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	UCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	UCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	UCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherPlayerId);
	UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest)
{
	UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const FContextDelegate& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherCharacterId);
	UCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, FContextDelegateBP(), OnCompletedRequest);
}

//Persisitent Storage
void ULootLockerSDKManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    UPersistentStorageRequestHandler::GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    UPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    UPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    UPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    UPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

//Assets
void ULootLockerSDKManager::GetContexts(const FContextDelegate& OnCompletedRequest)
{
    UAssetsRequestHandler::GetContexts(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC)
{
    UAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, FAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest)
{
    UAssetsRequestHandler::GetAssetsByIds(AssetIds, FAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    UAssetsRequestHandler::GetAssetBones(FAssetBonesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    UAssetsRequestHandler::GetFavouriteAssetIndices(FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    UAssetsRequestHandler::AddAssetToFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    UAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

//Asset Instance

void ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    UAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegateBP(), OnCompletedRequest);
}

//User Generated Candidate
void ULootLockerSDKManager::CreateAssetCandidate(const FAssetCandidate& AsssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::GetAllAssetCandidates(FAssetCandidatesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest)
{
    UUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, FResponseCallbackBP(), OnCompletedRequest);
}

//Missions
void ULootLockerSDKManager::GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest)
{
    UMissionsRequestHandler::GetAllMissions(FMissionsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest)
{
    UMissionsRequestHandler::GetMission(MissionId, FMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    UMissionsRequestHandler::StartMission(MissionId, FStartMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::FinishMission(int MissionId, const FFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    UMissionsRequestHandler::FinishMission(MissionId, MissionData, FFinishMissionResponseDelegateBP(), OnCompletedRequest);
}

//Maps
void ULootLockerSDKManager::GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest)
{
    UMapsRequestHandler::GetMaps(FGetMapsResponseDelegateBP(), OnCompletedRequest);
}

//Purchasing
void ULootLockerSDKManager::PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    UPurchasesRequestHandler::PurchaseAssets(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    UPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsIOS(const TArray<FVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    UPurchasesRequestHandler::PurchaseAssetsIOS(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    UPurchasesRequestHandler::PollingOrderStatus(PurchaseId, FPurchaseStatusResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    UPurchasesRequestHandler::ActivateRentalAsset(AssetId, FActivateRentalAssetResponseDelegateBP(), OnCompletedRequest);
}

//Trigger
void ULootLockerSDKManager::TriggerEvent(const FTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest)
{
    UTriggerEventsRequestHandler::TriggerEvent(Event, FTriggerEventResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest)
{
    UTriggerEventsRequestHandler::GetTriggeredEvents(FTriggersResponseDelegateBP(), OnCompletedRequest);
}

//Collectables
void ULootLockerSDKManager::GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest)
{
    UCollectablesRequestHandler::GetAllCollectables(FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CollectItem(const FCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    UCollectablesRequestHandler::CollectItem(Item, FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

//Messages
void ULootLockerSDKManager::GetMessages(const FMessagesResponseDelegate& OnCompletedRequest)
{
    UMessagesRequestHandler::GetMessages(FMessagesResponseDelegateBP(), OnCompletedRequest);
}
