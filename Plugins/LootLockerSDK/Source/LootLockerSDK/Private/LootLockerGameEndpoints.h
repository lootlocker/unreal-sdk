// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LootLockerConfig.h"

class LootLockerGameEndpoints
{
public:
    //Auth
    static FEndPoints StartSessionEndpoint;
    static FEndPoints VerifyPlayerIdEndPoint;
    static FEndPoints EndSessionEndpoint;

    //Player
    static FEndPoints GetPlayerInfoEndPoint;
    static FEndPoints GetPlayerInventoryEndPoint;
    static FEndPoints SubmitXpEndpoint;
    static FEndPoints GetOtherPlayerInfoEndpoint;
    static FEndPoints CheckPlayerAssetActivationEndpoint;
    static FEndPoints CheckPlayerAssetDeactivatonEndpoint;

    //Character
    static FEndPoints GetCharacterLoadoutEndpoint;
    static FEndPoints UpdateCharacterEndpoint;
    static FEndPoints EquipAssetToDefaultCharacterEndpoint;
    static FEndPoints EquipAssetToCharacterByIdEndpoint;
    static FEndPoints UnEquipAssetToDefaultCharacterEndpoint;
    static FEndPoints UnEquipAssetToCharacterByIdEndpoint;
    static FEndPoints GetCurrentLoadoutToDefaultCharacterEndpoint;
    static FEndPoints GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
    static FEndPoints GetEquippableContextstoDefaultCharacterEndpoint;
    static FEndPoints GetEquippableContextsByCharacterIDEndpoint;
    
    //Persistent Storage
    static FEndPoints GetEntirePersistentStorageEndpoint;
    static FEndPoints GetItemFromPersistentStorageEndpoint;
    static FEndPoints AddItemsToPersistentStorageEndpoint;
    static FEndPoints DeleteItemFromPersistentStorageEndpoint;
    static FEndPoints GetPlayerPersistentStorageEndpoint;
    
    //Assets
    static FEndPoints GetContextsEndpoint;
    static FEndPoints GetAssetsEndpoint;
    static FEndPoints GetAssetsByIdsEndpoint;
    static FEndPoints GetAssetBonesEndpoint;
    static FEndPoints GetFavouriteAssetIndicesEndpoint;
    static FEndPoints AddAssetToFavouritesEndpoint;
    static FEndPoints RemoveAssetFromFavouritesEndpoint;
    
    //Asset Instances
    static FEndPoints GetKeyValuePairsForAssetInstanceEndpoint;
    static FEndPoints GetKeyValuePairForAssetInstanceEndpoint;
    static FEndPoints CreateStorageItemForAssetInstanceEndpoint;
    static FEndPoints UpdateStorageItemsForAssetInstanceEndpoint;
    static FEndPoints UpdateStorageItemForAssetInstanceEndpoint;
    static FEndPoints DeleteStorageItemForAssetInstanceEndpoint;
    static FEndPoints InspectLootBoxEndpoint;
    static FEndPoints OpenLootBoxEndpoint;
    
    //User Generated Content
    static FEndPoints CreateAssetCandidateEndpoint;
    static FEndPoints UpdateAssetCandidateEndpoint;
    static FEndPoints DeleteAssetCandidateEndpoint;
    static FEndPoints GetAllAssetCandidatesEndpoint;
    static FEndPoints GetAssetCandidateEndpoint;
    static FEndPoints AddFileToAssetCandidateEndpoint;
    static FEndPoints DeleteFileFromAssetCandidateEndpoint;
    
    //Missions
    static FEndPoints GetAllMissionsEndpoint;
    static FEndPoints GetMissionEndpoint;
    static FEndPoints StartMissionEndpoint;
    static FEndPoints FinishMissionEndpoint;
    
    //Maps
    static FEndPoints GetAllMapsEndpoint;
    
    //Purchases
    static FEndPoints PurchaseAssetsEndpoint;
    static FEndPoints VerifyPurchaseIosEndpoint;
    static FEndPoints PollPurchaseStatusEndpoint;
    static FEndPoints ActivateRentalAssetEndpoint;
    
    //Trigger Events
    static FEndPoints TriggerEventEndpoint;
    static FEndPoints GetTriggeredEventsEndpoint;
    
    //Collectables
    static FEndPoints GetAllCollectablesEndpoint;
    static FEndPoints CollectItemEndpoint;
    
    //Messages
    static FEndPoints GetMessagesEndpoint;
    
private:
    static FString GameBaseUrl;

    static FEndPoints InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method);
};
