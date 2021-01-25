// Copyright (c) 2021 LootLocker

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
    static FEndPoints GetCurrencyBalance;
    static FEndPoints CheckPlayerAssetActivationEndpoint;
    static FEndPoints CheckPlayerAssetDeactivatonEndpoint;
    static FEndPoints InitiateDLCMigration;
    static FEndPoints GetDLCsMigrated;
    static FEndPoints SetProfilePrivate;
    static FEndPoints SetProfilePublic;

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
    static FEndPoints GetASingleKeyFromPersistentStorageEndpoint;
    static FEndPoints UpdateOrCreateKeyValuePairToPersistentStorageEndpoint;
    static FEndPoints DeleteAKeyValuePairFromPersistentStorageEndpoint;
    static FEndPoints GetOtherPlayersPublicKeyValuePairs;
    
    //Assets
    static FEndPoints GetContextsEndpoint;
    static FEndPoints GetAssetsEndpoint;
    static FEndPoints GetAssetsByIdsEndpoint;
    static FEndPoints GetAssetBonesEndpoint;
    static FEndPoints GetFavouriteAssetIndicesEndpoint;
    static FEndPoints AddAssetToFavouritesEndpoint;
    static FEndPoints RemoveAssetFromFavouritesEndpoint;
    
    //Asset Instances
    static FEndPoints GetAllKeyValuePairsForAssetInstance;
    static FEndPoints GetAllKeyValuePairsToAnInstanceForAssetInstance;
    static FEndPoints GetAKeyValuePairByIdForAssetInstanceEndpoint;
    static FEndPoints CreateAKeyValuePairForAssetInstanceEndpoint;
    static FEndPoints UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint;
    static FEndPoints UpdateAKeyValuePairByIdForAssetInstanceEndpoint;
    static FEndPoints DeleteAKeyValuePairByIdForAssetInstanceEndpoint;
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
    static FEndPoints PurchaseEndpoint;
    static FEndPoints IOSPurchaseEndpoint;
    static FEndPoints AndroidPurchaseEndpoint;
    static FEndPoints PollingOrderStatusEndpoint;
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
