// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerConfig.h"
#include "LootLockerGameEndpoints.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ULootLockerGameEndpoints : public UObject
{
    GENERATED_BODY()
public:
    //Auth
    static FLootLockerEndPoints StartSessionEndpoint;
    static FLootLockerEndPoints VerifyPlayerIdEndPoint;
    static FLootLockerEndPoints EndSessionEndpoint;

    //Player
    static FLootLockerEndPoints GetPlayerInfoEndPoint;
    static FLootLockerEndPoints GetPlayerInventoryEndPoint;
    static FLootLockerEndPoints SubmitXpEndpoint;
    static FLootLockerEndPoints GetOtherPlayerInfoEndpoint;
    static FLootLockerEndPoints GetCurrencyBalance;
    static FLootLockerEndPoints CheckPlayerAssetActivationEndpoint;
    static FLootLockerEndPoints CheckPlayerAssetDeactivatonEndpoint;
    static FLootLockerEndPoints InitiateDLCMigration;
    static FLootLockerEndPoints GetDLCsMigrated;
    static FLootLockerEndPoints SetProfilePrivate;
    static FLootLockerEndPoints SetProfilePublic;
    static FLootLockerEndPoints SetPlayerName;
    static FLootLockerEndPoints GetPlayerName;

    //Character
    static FLootLockerEndPoints GetCharacterLoadoutEndpoint;
    static FLootLockerEndPoints UpdateCharacterEndpoint;
    static FLootLockerEndPoints EquipAssetToDefaultCharacterEndpoint;
    static FLootLockerEndPoints EquipAssetToCharacterByIdEndpoint;
    static FLootLockerEndPoints CreateCharacterEndpoint;
    static FLootLockerEndPoints ListCharacterTypesByIdEndpoint;
    static FLootLockerEndPoints UnEquipAssetToDefaultCharacterEndpoint;
    static FLootLockerEndPoints UnEquipAssetToCharacterByIdEndpoint;
    static FLootLockerEndPoints GetCurrentLoadoutToDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetEquippableContextstoDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetEquippableContextsByCharacterIDEndpoint;
    
    //Persistent Storage
    static FLootLockerEndPoints GetEntirePersistentStorageEndpoint;
    static FLootLockerEndPoints GetASingleKeyFromPersistentStorageEndpoint;
    static FLootLockerEndPoints UpdateOrCreateKeyValuePairToPersistentStorageEndpoint;
    static FLootLockerEndPoints DeleteAKeyValuePairFromPersistentStorageEndpoint;
    static FLootLockerEndPoints GetOtherPlayersPublicKeyValuePairs;
    
    //Assets
    static FLootLockerEndPoints GetContextsEndpoint;
    static FLootLockerEndPoints GetAssetsEndpoint;
    static FLootLockerEndPoints GetAssetsByIdsEndpoint;
    static FLootLockerEndPoints GetAssetBonesEndpoint;
    static FLootLockerEndPoints GetFavouriteAssetIndicesEndpoint;
    static FLootLockerEndPoints AddAssetToFavouritesEndpoint;
    static FLootLockerEndPoints RemoveAssetFromFavouritesEndpoint;
    
    //Asset Instances
    static FLootLockerEndPoints GetAllKeyValuePairsForAssetInstance;
    static FLootLockerEndPoints GetAllKeyValuePairsToAnInstanceForAssetInstance;
    static FLootLockerEndPoints GetAKeyValuePairByIdForAssetInstanceEndpoint;
    static FLootLockerEndPoints CreateAKeyValuePairForAssetInstanceEndpoint;
    static FLootLockerEndPoints UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint;
    static FLootLockerEndPoints UpdateAKeyValuePairByIdForAssetInstanceEndpoint;
    static FLootLockerEndPoints DeleteAKeyValuePairByIdForAssetInstanceEndpoint;
    static FLootLockerEndPoints InspectLootBoxEndpoint;
    static FLootLockerEndPoints OpenLootBoxEndpoint;
    
    //User Generated Content
    static FLootLockerEndPoints CreateAssetCandidateEndpoint;
    static FLootLockerEndPoints UpdateAssetCandidateEndpoint;
    static FLootLockerEndPoints DeleteAssetCandidateEndpoint;
    static FLootLockerEndPoints GetAllAssetCandidatesEndpoint;
    static FLootLockerEndPoints GetAssetCandidateEndpoint;
    static FLootLockerEndPoints AddFileToAssetCandidateEndpoint;
    static FLootLockerEndPoints DeleteFileFromAssetCandidateEndpoint;
    
    //Missions
    static FLootLockerEndPoints GetAllMissionsEndpoint;
    static FLootLockerEndPoints GetMissionEndpoint;
    static FLootLockerEndPoints StartMissionEndpoint;
    static FLootLockerEndPoints FinishMissionEndpoint;
    
    //Maps
    static FLootLockerEndPoints GetAllMapsEndpoint;
    
    //Purchases
    static FLootLockerEndPoints PurchaseEndpoint;
    static FLootLockerEndPoints IOSPurchaseEndpoint;
    static FLootLockerEndPoints AndroidPurchaseEndpoint;
    static FLootLockerEndPoints PollingOrderStatusEndpoint;
    static FLootLockerEndPoints ActivateRentalAssetEndpoint;
    
    //Trigger Events
    static FLootLockerEndPoints TriggerEventEndpoint;
    static FLootLockerEndPoints GetTriggeredEventsEndpoint;
    
    //Collectables
    static FLootLockerEndPoints GetAllCollectablesEndpoint;
    static FLootLockerEndPoints CollectItemEndpoint;
    
    //Messages
    static FLootLockerEndPoints GetMessagesEndpoint;

    //Leaderboard
    static FLootLockerEndPoints GetMemberRank;
    static FLootLockerEndPoints GetByListOfMembers;
    static FLootLockerEndPoints GetScoreList;
    static FLootLockerEndPoints SubmitScore;

    //DropTables
    static FLootLockerEndPoints ComputeAndLockDropTable; 
    static FLootLockerEndPoints PickDropsFromDropTable;
    
private:
    static FString GameBaseUrl;

    static FLootLockerEndPoints InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method);
};
