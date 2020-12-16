// Fill out your copyright notice in the Description page of Project Settings.


#include "LootLockerSDKManager.h"

// Sets default values for this component's properties
ULootLockerSDKManager::ULootLockerSDKManager()
{

}

void ULootLockerSDKManager::StartSession(const FString& PlayerId, const FLootLockerSessionResponse& OnCompleteRequest)
{
	OnStartedSessionRequestCompleted.Clear();
	UAuthenticationRequestHandler::StartSession(PlayerId, OnStartedSessionRequestCompleted, OnCompleteRequest);
}


void ULootLockerSDKManager::VerifyPlayer(const FString& CachedSteamToken, const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	OnVerifyPlayerRequestCompleted.Clear();
	UAuthenticationRequestHandler::VerifyPlayer(CachedSteamToken, OnVerifyPlayerRequestCompleted,OnCompleteRequest);
}


void ULootLockerSDKManager::EndSession(const FString& PlayerId, const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	OnEndSessionRequestCompleted.Clear();
	UAuthenticationRequestHandler::EndSession(OnEndSessionRequestCompleted,OnCompleteRequest);
}

void ULootLockerSDKManager::GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	OnGetPlayerInfoRequestCompleted.Clear();
	UPlayerRequestHandler::GetPlayerInfo(OnGetPlayerInfoRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::GetInventory(const FLootLockerInventoryResponse& OnCompletedRequest)
{
	OnGetInventoryRequestCompleted.Clear();
	UPlayerRequestHandler::GetInventory(OnGetInventoryRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::SubmitXP(const int32& Points, const FLootLockerSubmitXpResponse& OnCompletedRequest)
{
	OnSubmitXPRequestCompleted.Clear();
	UPlayerRequestHandler::SubmitXp(Points, OnSubmitXPRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	OnGetOtherPlayerInfoRequestCompleted.Clear();
	UPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, OnGetOtherPlayerInfoRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	OnCheckPlayerAssetActivationNotificationRequestCompleted.Clear();
	UPlayerRequestHandler::CheckPlayerAssetNotification(OnCheckPlayerAssetActivationNotificationRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetDeactivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	OnCheckPlayerAssetDeactivationNotificationRequestCompleted.Clear();
	UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::GetCharacterLoadout(const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	OnGetCharacterLoadoutRequestCompleted.Clear();
	UCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToDefaultCharacter(const int32& InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	OnEquipAssetToDefaultCharacterRequestCompleted.Clear();
	UCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(const int32& CharacterId, const int32& AssetId,const  int32& AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{

	OnEquipAssetToCharacterByIdRequestCompleted.Clear();
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	UCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, OnEquipAssetToCharacterByIdRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(const int32& InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{

	OnUnEquipAssetToDefaultCharacterRequestCompleted.Clear();
	UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToCharacterById(const int32& CharacterId, const int32& AssetId, const int32& AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	OnUnEquipAssetToCharacterByIdRequestCompleted.Clear();
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	UCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, OnUnEquipAssetToCharacterByIdRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	OnGetCurrentLoadoutToDefaultCharacterRequestCompleted.Clear();
	UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(OnGetCurrentLoadoutToDefaultCharacterRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{

	OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted.Clear();
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherPlayerId);
	UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests, OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest)
{
	OnGetEquipableContextsToDefaultCharacterRequestCompleted.Clear();
	UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const FContextDelegate& OnCompletedRequest)
{

	OnGetEquipableContextsByCharacterIdRequestCompleted.Clear();
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherCharacterId);
	UCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, OnGetEquipableContextsByCharacterIdRequestCompleted,OnCompletedRequest);
}

void ULootLockerSDKManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnPersistentStorageItemsRequestCompleted.Clear();
    
    UPersistentStorageRequestHandler::GetEntirePersistentStorage(OnPersistentStorageItemsRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    OnPersistentStorageItemRequestCompleted.Clear();
    
    UPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, OnPersistentStorageItemRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnPersistentStorageItemsAddRequestCompleted.Clear();
    
    UPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, OnPersistentStorageItemsAddRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnPersistentStorageItemDeleteRequestCompleted.Clear();
    
    UPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, OnPersistentStorageItemDeleteRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnGetPlayerPersistentStorageRequestCompleted.Clear();
    
    UPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, OnGetPlayerPersistentStorageRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetContexts(const FContextDelegate& OnCompletedRequest)
{
    OnGetContextsRequestCompleted.Clear();
    
    UAssetsRequestHandler::GetContexts(OnGetContextsRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC)
{
    OnGetAssetsRequestCompleted.Clear();
    
    UAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, OnGetAssetsRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetsByIds(const TArray<int> AssetIds, const FAssetsResponseDelegate& OnCompletedRequest)
{
    OnGetAssetsByIdsRequestCompleted.Clear();
    
    UAssetsRequestHandler::GetAssetsByIds(AssetIds, OnGetAssetsByIdsRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    OnGetAssetBonesRequestCompleted.Clear();
    
    UAssetsRequestHandler::GetAssetBones(OnGetAssetBonesRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    OnGetFavouriteAssetIndicesRequestCompleted.Clear();
    
    UAssetsRequestHandler::GetFavouriteAssetIndices(OnGetFavouriteAssetIndicesRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    OnAddAssetToFavouritesRequestCompleted.Clear();
    
    UAssetsRequestHandler::AddAssetToFavourites(AssetId, OnAddAssetToFavouritesRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    OnRemoveAssetFromFavouritesRequestCompleted.Clear();
    
    UAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, OnRemoveAssetFromFavouritesRequestCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnGetKeyValuePairsForAssetInstanceCompleted.Clear();
    
    UAssetInstancesRequestHandler::GetKeyValuePairsForAssetInstance(AssetInstanceId, OnGetKeyValuePairsForAssetInstanceCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetKeyValuePairForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnGetKeyValuePairForAssetInstanceCompleted.Clear();
    
    UAssetInstancesRequestHandler::GetKeyValuePairForAssetInstance(AssetInstanceId, StorageItemId, OnGetKeyValuePairForAssetInstanceCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::CreateStorageItemForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnCreateStorageItemForAssetInstanceCompleted.Clear();
    
    UAssetInstancesRequestHandler::CreateStorageItemForAssetInstance(AssetInstanceId, Item, OnCreateStorageItemForAssetInstanceCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateStorageItemsForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnUpdateStorageItemsForAssetInstanceCompleted.Clear();
    
    UAssetInstancesRequestHandler::UpdateStorageItemsForAssetInstance(AssetInstanceId, Items, OnUpdateStorageItemsForAssetInstanceCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnUpdateStorageItemForAssetInstanceCompleted.Clear();
    
    UAssetInstancesRequestHandler::UpdateStorageItemForAssetInstance(AssetInstanceId, StorageItemId, Item, OnUpdateStorageItemForAssetInstanceCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    OnDeleteStorageItemForAssetInstanceCompleted.Clear();
    
    UAssetInstancesRequestHandler::DeleteStorageItemForAssetInstance(AssetInstanceId, StorageItemId, OnDeleteStorageItemForAssetInstanceCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    OnInspectLootBoxCompleted.Clear();
    
    UAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, OnInspectLootBoxCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    OnOpenLootBoxCompleted.Clear();
    
    UAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, OnOpenLootBoxCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAssetCandidate(const FAssetCandidate& AsssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    OnCreateAssetCandidateCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, OnCreateAssetCandidateCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    OnUpdateAssetCandidateCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, OnUpdateAssetCandidateCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest)
{
    OnDeleteAssetCandidateCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, OnDeleteAssetCandidateCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    OnGetAllAssetCandidatesCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::GetAllAssetCandidates(OnGetAllAssetCandidatesCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    OnGetAssetCandidateCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, OnGetAssetCandidateCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest)
{
    OnAddFileToAssetCandidateCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest)
{
    OnDeleteFileFromAssetCandidateCompleted.Clear();
    
    UUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest)
{
    OnGetAllMissionsCompleted.Clear();
    
    UMissionsRequestHandler::GetAllMissions(OnGetAllMissionsCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest)
{
    OnGetMissionCompleted.Clear();
    
    UMissionsRequestHandler::GetMission(MissionId, OnGetMissionCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    OnStartMissionCompleted.Clear();
    
    UMissionsRequestHandler::StartMission(MissionId, OnStartMissionCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::FinishMission(int MissionId, const FFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    OnFinishMissionCompleted.Clear();
    
    UMissionsRequestHandler::FinishMission(MissionId, MissionData, OnFinishMissionCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest)
{
    OnGetMapsCompleted.Clear();
    
    UMapsRequestHandler::GetMaps(OnGetMapsCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    OnPurchaseAssetsCompleted.Clear();
    
    UPurchasesRequestHandler::PurchaseAssets(PurchaseData, OnPurchaseAssetsCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    OnPurchaseAssetsAndroidCompleted.Clear();
    
    UPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, OnPurchaseAssetsAndroidCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::VerifyPurchaseIos(const TArray<FVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    OnVerifyPurchaseIosCompleted.Clear();
    
    UPurchasesRequestHandler::VerifyPurchaseIos(PurchaseData, OnVerifyPurchaseIosCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::PollPurchaseStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    OnPollPurchaseStatusCompleted.Clear();
    
    UPurchasesRequestHandler::PollPurchaseStatus(PurchaseId, OnPollPurchaseStatusCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    OnActivateRentalAssetCompleted.Clear();
    
    UPurchasesRequestHandler::ActivateRentalAsset(AssetId, OnActivateRentalAssetCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::TriggerEvent(const FTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest)
{
    OnTriggerEventCompleted.Clear();
    
    UTriggerEventsRequestHandler::TriggerEvent(Event, OnTriggerEventCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest)
{
    OnGetTriggeredEventsCompleted.Clear();
    
    UTriggerEventsRequestHandler::GetTriggeredEvents(OnGetTriggeredEventsCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest)
{
    OnGetAllCollectablesCompleted.Clear();
    
    UCollectablesRequestHandler::GetAllCollectables(OnGetAllCollectablesCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::CollectItem(const FCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    OnCollectItemCompleted.Clear();
    
    UCollectablesRequestHandler::CollectItem(Item, OnCollectItemCompleted, OnCompletedRequest);
}

void ULootLockerSDKManager::GetMessages(const FMessagesResponseDelegate& OnCompletedRequest)
{
    OnGetMessagesCompleted.Clear();
    
    UMessagesRequestHandler::GetMessages(OnGetMessagesCompleted, OnCompletedRequest);
}

//BluePrints

void ULootLockerSDKManager::BPStartSession(const FString& PlayerId)
{
	UAuthenticationRequestHandler::StartSession(PlayerId, OnStartedSessionRequestCompleted);
}

void ULootLockerSDKManager::BPVerifyPlayer(const FString& CachedSteamToken)
{
	UAuthenticationRequestHandler::VerifyPlayer(CachedSteamToken, OnVerifyPlayerRequestCompleted);
}

void ULootLockerSDKManager::BPEndSession(const FString& PlayerId)
{
	UAuthenticationRequestHandler::EndSession(OnEndSessionRequestCompleted);
}

void ULootLockerSDKManager::BPGetPlayerInfo()
{
	UPlayerRequestHandler::GetPlayerInfo(OnGetPlayerInfoRequestCompleted);
}

void ULootLockerSDKManager::BPGetInventory()
{
	UPlayerRequestHandler::GetInventory(OnGetInventoryRequestCompleted);
}

void ULootLockerSDKManager::BPSubmitXP(const int32& Points)
{
	UPlayerRequestHandler::SubmitXp(Points, OnSubmitXPRequestCompleted);
}

void ULootLockerSDKManager::BPGetOtherPlayerInfo(FLootLockerGetRequests& GetRequests)
{
	UPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, OnGetOtherPlayerInfoRequestCompleted);
}

void ULootLockerSDKManager::BPCheckPlayerAssetActivationNotification()
{
	UPlayerRequestHandler::CheckPlayerAssetNotification(OnCheckPlayerAssetActivationNotificationRequestCompleted);
}

void ULootLockerSDKManager::BPCheckPlayerAssetDeactivationNotification()
{
	UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
}

void ULootLockerSDKManager::BPGetCharacterLoadout()
{
	UCharacterRequestHandler::GetCharacterLoadout(OnGetCharacterLoadoutRequestCompleted);
}

void ULootLockerSDKManager::BPEquipAssetToDefaultCharacter(const int32& InstanceId)
{
	UCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, OnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerSDKManager::BPEquipAssetToCharacterById(const int32& CharacterId,const  int32& AssetId,const  int32& AssetVariationId)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	UCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId,OnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerSDKManager::BPUnEquipAssetToDefaultCharacter(const int32& InstanceId)
{
	UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, OnUnEquipAssetToDefaultCharacterRequestCompleted);
}

void ULootLockerSDKManager::BPUnEquipAssetToCharacterById(const int32& CharacterId,const int32& AssetId, const int32& AssetVariationId)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	UCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, OnUnEquipAssetToCharacterByIdRequestCompleted);
}

void ULootLockerSDKManager::BPGetCurrentLoadoutToDefaultCharacter()
{
	UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerSDKManager::BPGetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherPlayerId);
	UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests,OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
}

void ULootLockerSDKManager::BPGetEquipableContextsToDefaultCharacter()
{
	UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(OnGetEquipableContextsToDefaultCharacterRequestCompleted);
}

void ULootLockerSDKManager::BPGetEquipableContextsByCharacterId(const FString& OtherCharacterId)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherCharacterId);
	UCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, OnGetEquipableContextsByCharacterIdRequestCompleted);
}

void ULootLockerSDKManager::BPGetEntirePersistentStorage()
{
    UPersistentStorageRequestHandler::GetEntirePersistentStorage(OnPersistentStorageItemsRequestCompleted);
}

void ULootLockerSDKManager::BPGetItemFromPersistentStorage(const FString& Key)
{
    UPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, OnPersistentStorageItemRequestCompleted);
}

void ULootLockerSDKManager::BPAddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items)
{
    UPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, OnPersistentStorageItemsAddRequestCompleted);
}

void ULootLockerSDKManager::BPDeleteItemFromPersistentStorage(const FString& Key)
{
    UPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, OnPersistentStorageItemDeleteRequestCompleted);
}

void ULootLockerSDKManager::BPGetPlayerPersistentStorage(const FString& PlayerId)
{
    UPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, OnGetPlayerPersistentStorageRequestCompleted);
}

void ULootLockerSDKManager::BPGetContexts()
{
    UAssetsRequestHandler::GetContexts(OnGetContextsRequestCompleted);
}

void ULootLockerSDKManager::BPGetAssets(int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC)
{
    UAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, IncludeUGC, OnGetAssetsRequestCompleted);
}

void ULootLockerSDKManager::BPGetAssetsByIds(const TArray<int> AssetIds)
{
    UAssetsRequestHandler::GetAssetsByIds(AssetIds, OnGetAssetsByIdsRequestCompleted);
}

void ULootLockerSDKManager::BPGetAssetBones()
{
    UAssetsRequestHandler::GetAssetBones(OnGetAssetBonesRequestCompleted);
}

void ULootLockerSDKManager::BPGetFavouriteAssetIndices()
{
    UAssetsRequestHandler::GetFavouriteAssetIndices(OnGetFavouriteAssetIndicesRequestCompleted);
}

void ULootLockerSDKManager::BPAddAssetToFavourites(int AssetId)
{
    UAssetsRequestHandler::AddAssetToFavourites(AssetId, OnAddAssetToFavouritesRequestCompleted);
}

void ULootLockerSDKManager::BPRemoveAssetFromFavourites(int AssetId)
{
    UAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, OnRemoveAssetFromFavouritesRequestCompleted);
}

void ULootLockerSDKManager::BPGetKeyValuePairsForAssetInstance(int AssetInstanceId)
{
    UAssetInstancesRequestHandler::GetKeyValuePairsForAssetInstance(AssetInstanceId, OnGetKeyValuePairsForAssetInstanceCompleted);
}

void ULootLockerSDKManager::BPGetKeyValuePairForAssetInstance(int AssetInstanceId, int StorageItemId)
{
    UAssetInstancesRequestHandler::GetKeyValuePairForAssetInstance(AssetInstanceId, StorageItemId, OnGetKeyValuePairForAssetInstanceCompleted);
}

void ULootLockerSDKManager::BPCreateStorageItemForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item)
{
    UAssetInstancesRequestHandler::CreateStorageItemForAssetInstance(AssetInstanceId, Item, OnCreateStorageItemForAssetInstanceCompleted);
}

void ULootLockerSDKManager::BPUpdateStorageItemsForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items)
{
    UAssetInstancesRequestHandler::UpdateStorageItemsForAssetInstance(AssetInstanceId, Items, OnUpdateStorageItemsForAssetInstanceCompleted);
}

void ULootLockerSDKManager::BPUpdateStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item)
{
    UAssetInstancesRequestHandler::UpdateStorageItemForAssetInstance(AssetInstanceId, StorageItemId, Item, OnUpdateStorageItemForAssetInstanceCompleted);
}

void ULootLockerSDKManager::BPDeleteStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId)
{
    UAssetInstancesRequestHandler::DeleteStorageItemForAssetInstance(AssetInstanceId, StorageItemId, OnDeleteStorageItemForAssetInstanceCompleted);
}

void ULootLockerSDKManager::BPInspectLootBox(int AssetInstanceId)
{
    UAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, OnInspectLootBoxCompleted);
}

void ULootLockerSDKManager::BPOpenLootBox(int AssetInstanceId)
{
    UAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, OnOpenLootBoxCompleted);
}

void ULootLockerSDKManager::BPCreateAssetCandidate(const FAssetCandidate& AsssetCandidate)
{
    UUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, OnCreateAssetCandidateCompleted);
}

void ULootLockerSDKManager::BPUpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate)
{
    UUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, OnUpdateAssetCandidateCompleted);
}

void ULootLockerSDKManager::BPDeleteAssetCandidate(int AssetCandidateId)
{
    UUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, OnDeleteAssetCandidateCompleted);
}

void ULootLockerSDKManager::BPGetAllAssetCandidates()
{
    UUserGeneratedContentRequestHandler::GetAllAssetCandidates(OnGetAllAssetCandidatesCompleted);
}

void ULootLockerSDKManager::BPGetAssetCandidate(int AssetCandidateId)
{
    UUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, OnGetAssetCandidateCompleted);
}

void ULootLockerSDKManager::BPAddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose)
{
    UUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, OnAddFileToAssetCandidateCompleted);
}

void ULootLockerSDKManager::BPDeleteFileFromAssetCandidate(int AssetCandidateId, int FileId)
{
    UUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, OnDeleteFileFromAssetCandidateCompleted);
}

void ULootLockerSDKManager::BPGetAllMissions()
{
    UMissionsRequestHandler::GetAllMissions(OnGetAllMissionsCompleted);
}

void ULootLockerSDKManager::BPGetMission(int MissionId)
{
    UMissionsRequestHandler::GetMission(MissionId, OnGetMissionCompleted);
}

void ULootLockerSDKManager::BPStartMission(int MissionId)
{
    UMissionsRequestHandler::StartMission(MissionId, OnStartMissionCompleted);
}

void ULootLockerSDKManager::BPFinishMission(int MissionId, const FFinishMissionData& MissionData)
{
    UMissionsRequestHandler::FinishMission(MissionId, MissionData, OnFinishMissionCompleted);
}

void ULootLockerSDKManager::BPGetMaps()
{
    UMapsRequestHandler::GetMaps(OnGetMapsCompleted);
}

void ULootLockerSDKManager::BPPurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData)
{
    UPurchasesRequestHandler::PurchaseAssets(PurchaseData, OnPurchaseAssetsCompleted);
}

void ULootLockerSDKManager::BPPurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData)
{
    UPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, OnPurchaseAssetsAndroidCompleted);
}

void ULootLockerSDKManager::BPVerifyPurchaseIos(const TArray<FVerifyPurchaseIosData>& PurchaseData)
{
    UPurchasesRequestHandler::VerifyPurchaseIos(PurchaseData, OnVerifyPurchaseIosCompleted);
}

void ULootLockerSDKManager::BPPollPurchaseStatus(int PurchaseId)
{
    UPurchasesRequestHandler::PollPurchaseStatus(PurchaseId, OnPollPurchaseStatusCompleted);
}

void ULootLockerSDKManager::BPActivateRentalAsset(int AssetId)
{
    UPurchasesRequestHandler::ActivateRentalAsset(AssetId, OnActivateRentalAssetCompleted);
}

void ULootLockerSDKManager::BPTriggerEvent(const FTriggerEvent& Event)
{
    UTriggerEventsRequestHandler::TriggerEvent(Event, OnTriggerEventCompleted);
}

void ULootLockerSDKManager::BPGetTriggeredEvents()
{
    UTriggerEventsRequestHandler::GetTriggeredEvents(OnGetTriggeredEventsCompleted);
}

void ULootLockerSDKManager::BPGetAllCollectables()
{
    UCollectablesRequestHandler::GetAllCollectables(OnGetAllCollectablesCompleted);
}

void ULootLockerSDKManager::BPCollectItem(const FCollectItemPayload& Item)
{
    UCollectablesRequestHandler::CollectItem(Item, OnCollectItemCompleted);
}

void ULootLockerSDKManager::BPGetMessages()
{
    UMessagesRequestHandler::GetMessages(OnGetMessagesCompleted);
}
