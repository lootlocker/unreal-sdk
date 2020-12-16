// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuthenticationRequestHandler.h"
#include "HttpClient.h"
#include "LootLockerConfig.h"
#include "Engine/DataAsset.h"
#include "PlayerRequestHandler.h"
#include "CharacterRequestHandler.h"
#include "PersistentStorageRequestHandler.h"
#include "AssetsRequestHandler.h"
#include "AssetInstancesRequestHandler.h"
#include "UserGeneratedContentRequestHandler.h"
#include "MissionsRequestHandler.h"
#include "MapsRequestHandler.h"
#include "PurchasesRequestHandler.h"
#include "TriggerEventsRequestHandler.h"
#include "CollectablesRequestHandler.h"
#include "MessagesRequestHandler.h"

#include "LootLockerSDKManager.generated.h"



UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerSDKManager : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULootLockerSDKManager();
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FAuthResponseBP OnStartedSessionRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FAuthDefaultResponseBP OnVerifyPlayerRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FAuthDefaultResponseBP OnEndSessionRequestCompleted;

	//Players
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPInfoResponseBP OnGetPlayerInfoRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPInventoryResponseBP OnGetInventoryRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPSubmitResponseBP OnSubmitXPRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPInfoResponseBP OnGetOtherPlayerInfoRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPAssetNotificationResponseBP OnCheckPlayerAssetActivationNotificationRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPAssetNotificationResponseBP OnCheckPlayerAssetDeactivationNotificationRequestCompleted;
	//Characters

	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterLoadoutResponseBP OnGetCharacterLoadoutRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterDefaultResponseBP OnEquipAssetToDefaultCharacterRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterDefaultResponseBP OnEquipAssetToCharacterByIdRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterDefaultResponseBP OnUnEquipAssetToDefaultCharacterRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterDefaultResponseBP OnUnEquipAssetToCharacterByIdRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterLoadoutResponseBP OnGetCurrentLoadoutToDefaultCharacterRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FPCharacterLoadoutResponseBP OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FContextDelegateBP OnGetEquipableContextsToDefaultCharacterRequestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
	FContextDelegateBP OnGetEquipableContextsByCharacterIdRequestCompleted;
    
    //Persistent Storage
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPersistentStorageItemsResponseDelegateBP OnPersistentStorageItemsRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPersistentStorageItemResponseDelegateBP OnPersistentStorageItemRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPersistentStorageItemsResponseDelegateBP OnPersistentStorageItemsAddRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPersistentStorageItemsResponseDelegateBP OnPersistentStorageItemDeleteRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPersistentStorageItemsResponseDelegateBP OnGetPlayerPersistentStorageRequestCompleted;
    
    //Assets
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FContextDelegateBP OnGetContextsRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetsResponseDelegateBP OnGetAssetsRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetsResponseDelegateBP OnGetAssetsByIdsRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetBonesResponseDelegateBP OnGetAssetBonesRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FGetFavouriteAssetIndicesResponseDelegateBP OnGetFavouriteAssetIndicesRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FGetFavouriteAssetIndicesResponseDelegateBP OnAddAssetToFavouritesRequestCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FGetFavouriteAssetIndicesResponseDelegateBP OnRemoveAssetFromFavouritesRequestCompleted;
    
    //Asset Instances
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetInstanceStorageItemsResponseDelegateBP OnGetKeyValuePairsForAssetInstanceCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetInstanceStorageItemsResponseDelegateBP OnGetKeyValuePairForAssetInstanceCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetInstanceStorageItemsResponseDelegateBP OnCreateStorageItemForAssetInstanceCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetInstanceStorageItemsResponseDelegateBP OnUpdateStorageItemsForAssetInstanceCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetInstanceStorageItemsResponseDelegateBP OnUpdateStorageItemForAssetInstanceCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetInstanceStorageItemsResponseDelegateBP OnDeleteStorageItemForAssetInstanceCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FLootBoxContentResponseDelegateBP OnInspectLootBoxCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FOpenLootBoxResponseDelegateBP OnOpenLootBoxCompleted;
    
    //User Generated Content
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FCreateAssetCandidateResponseDelegateBP OnCreateAssetCandidateCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetCandidateResponseDelegateBP OnUpdateAssetCandidateCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FResponseCallbackBP OnDeleteAssetCandidateCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetCandidatesResponseDelegateBP OnGetAllAssetCandidatesCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FAssetCandidateResponseDelegateBP OnGetAssetCandidateCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FResponseCallbackBP OnAddFileToAssetCandidateCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FResponseCallbackBP OnDeleteFileFromAssetCandidateCompleted;
    
    //Missions
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FMissionsResponseDelegateBP OnGetAllMissionsCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FMissionResponseDelegateBP OnGetMissionCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FStartMissionResponseDelegateBP OnStartMissionCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FFinishMissionResponseDelegateBP OnFinishMissionCompleted;
    
    //Maps
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FGetMapsResponseDelegateBP OnGetMapsCompleted;
    
    //Purchases
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPurchaseResponseDelegateBP OnPurchaseAssetsCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPurchaseResponseDelegateBP OnPurchaseAssetsAndroidCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPurchaseResponseDelegateBP OnVerifyPurchaseIosCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FPurchaseStatusResponseDelegateBP OnPollPurchaseStatusCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FActivateRentalAssetResponseDelegateBP OnActivateRentalAssetCompleted;
    
    //Trigger Events
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FTriggerEventResponseDelegateBP OnTriggerEventCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FTriggersResponseDelegateBP OnGetTriggeredEventsCompleted;
    
    //Collectables
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FCollectablesResponseDelegateBP OnGetAllCollectablesCompleted;
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FCollectablesResponseDelegateBP OnCollectItemCompleted;
    
    //Messages
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks")
    FMessagesResponseDelegateBP OnGetMessagesCompleted;

public:
	void StartSession(const FString& PlayerId, const FLootLockerSessionResponse& OnCompletedRequest);
	void VerifyPlayer(const FString& CachedSteamToken, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest);
	void EndSession(const FString& PlayerId, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest);
	//Player calls
	void GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest);
	void GetInventory(const FLootLockerInventoryResponse& OnCompletedRequest);
	void SubmitXP(const int32& Points, const FLootLockerSubmitXpResponse& OnCompletedRequest);
	void GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const FLootLockerPlayerInformationResponse& OnCompletedRequest);
	void CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest);
	void CheckPlayerAssetDeactivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest);
	//character calls
	void GetCharacterLoadout(const FLootLockerCharacterLoadoutResponse& OnCompletedRequest);
	void EquipAssetToDefaultCharacter(const int32& InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
	void EquipAssetToCharacterById(const int32& CharacterId,const  int32& AssetId,const  int32& AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
	void UnEquipAssetToDefaultCharacter(const int32& InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
	void UnEquipAssetToCharacterById(const int32& CharacterId,const int32& AssetId,const int32& AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
	void GetCurrentLoadoutToDefaultCharacter(const FLootLockerCharacterLoadoutResponse& OnCompletedRequest);
	void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest);
	void GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest);
	void GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const FContextDelegate& OnCompletedRequest);
    //Persistent Storage
    void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest);
    void AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    void GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    //Assets
    void GetContexts(const FContextDelegate& OnCompletedRequest);
    void GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex = 0, int ItemsCount = 50, EAssetFilter AssetFilter = EAssetFilter::None, bool IncludeUGC = false);
    void GetAssetsByIds(const TArray<int> AssetIds, const FAssetsResponseDelegate& OnCompletedRequest);
    void GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest);
    void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);
    void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);
    void RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);
    //Asset Instances
    void GetKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    void GetKeyValuePairForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    void CreateStorageItemForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    void UpdateStorageItemsForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    void UpdateStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    void DeleteStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    void InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest);
    void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest);
    //User Generated Content
    void CreateAssetCandidate(const FAssetCandidate& AsssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest);
    void UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate, const FAssetCandidateResponseDelegate& OnCompletedRequest);
    void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest);
    void GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest);
    void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest);
    void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest);
    void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest);
    //Missions
    void GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest);
    void GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest);
    void StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest);
    void FinishMission(int MissionId, const FFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest);
    //Maps
    void GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest);
    //Purchases
    void PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);
    void PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);
    void VerifyPurchaseIos(const TArray<FVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);
    void PollPurchaseStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest);
    void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest);
    //Trigger Events
    void TriggerEvent(const FTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest);
    void GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest);
    //Collectables
    void GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest);
    void CollectItem(const FCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest);
    //Messages
    void GetMessages(const FMessagesResponseDelegate& OnCompletedRequest);

	//For Blueprints
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPStartSession(const FString& playerId);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPVerifyPlayer(const FString& CachedSteamToken);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPEndSession(const FString& playerId);
	//Player calls
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetPlayerInfo();
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetInventory();
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPSubmitXP(const int32& points);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetOtherPlayerInfo(FLootLockerGetRequests& getRequests);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPCheckPlayerAssetActivationNotification();
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPCheckPlayerAssetDeactivationNotification();
	//character calls
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetCharacterLoadout();
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPEquipAssetToDefaultCharacter(const int32& instance_id);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPEquipAssetToCharacterById(const int32& characterId, const int32& asset_id, const int32& asset_variation_id);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPUnEquipAssetToDefaultCharacter(const int32& instance_id);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPUnEquipAssetToCharacterById(const int32& characterId, const int32& asset_id,const int32& asset_variation_id);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetCurrentLoadoutToDefaultCharacter();
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& otherPlayerId);
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetEquipableContextsToDefaultCharacter();
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods")
	void BPGetEquipableContextsByCharacterId(const FString& otherCharacterId);
    //Persistent Storage
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void BPGetEntirePersistentStorage();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void BPGetItemFromPersistentStorage(const FString& Key);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void BPAddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void BPDeleteItemFromPersistentStorage(const FString& Key);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void BPGetPlayerPersistentStorage(const FString& PlayerId);
    //Assets
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPGetContexts();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPGetAssets(int StartFromIndex = 0, int ItemsCount = 50, EAssetFilter AssetFilter = EAssetFilter::None, bool IncludeUGC = false);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPGetAssetsByIds(const TArray<int> AssetIds);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPGetAssetBones();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPGetFavouriteAssetIndices();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPAddAssetToFavourites(int AssetId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void BPRemoveAssetFromFavourites(int AssetId);
    //Asset Instances
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPGetKeyValuePairsForAssetInstance(int AssetInstanceId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPGetKeyValuePairForAssetInstance(int AssetInstanceId, int StorageItemId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPCreateStorageItemForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPUpdateStorageItemsForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPUpdateStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPDeleteStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPInspectLootBox(int AssetInstanceId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void BPOpenLootBox(int AssetInstanceId);
    //User Generated Content
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPCreateAssetCandidate(const FAssetCandidate& AsssetCandidate);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPUpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPDeleteAssetCandidate(int AssetCandidateId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPGetAllAssetCandidates();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPGetAssetCandidate(int AssetCandidateId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPAddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void BPDeleteFileFromAssetCandidate(int AssetCandidateId, int FileId);
    //Missions
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void BPGetAllMissions();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void BPGetMission(int MissionId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void BPStartMission(int MissionId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void BPFinishMission(int MissionId, const FFinishMissionData& MissionData);
    //Maps
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Maps")
    void BPGetMaps();
    //Purchases
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void BPPurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void BPPurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void BPVerifyPurchaseIos(const TArray<FVerifyPurchaseIosData>& PurchaseData);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void BPPollPurchaseStatus(int PurchaseId);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void BPActivateRentalAsset(int AssetId);
    //Trigger Events
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    void BPTriggerEvent(const FTriggerEvent& Event);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    void BPGetTriggeredEvents();
    //Collectables
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    void BPGetAllCollectables();
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    void BPCollectItem(const FCollectItemPayload& Item);
    //Messages
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Messages")
    void BPGetMessages();
};
