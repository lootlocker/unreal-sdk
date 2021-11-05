// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerHttpClient.h"
#include "LootLockerConfig.h"
#include "Engine/DataAsset.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "GameAPI/LootLockerPurchasesRequestHandler.h"
#include "GameAPI/LootLockerTriggerEventsRequestHandler.h"
#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "GameAPI/LLDropTablesRequestHandler.h"

#include "LootLockerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerManager : public UObject
{
    GENERATED_BODY()
 
public:
    
    //==================================================
    //Authentication
    //==================================================
    
    /**
    * Register a session.
    *
    * @param playerIdentifier - the ID of the player on the platform the game is currently running on.
    *  https://ref.lootlocker.io/game-api/#authentication-request
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartSession(const FString& playerIdentifier, const FAuthResponseBP& OnStartedSessionRequestCompleted);
    
    /**
    * If your game uses Player Verification, you need to call this endpoint before you can register a session.
    *
    * @param SteamSessionTicket - platform-specific token.
    * https://ref.lootlocker.io/game-api/#player-verification
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void VerifyPlayer(const FString& SteamSessionTicket, const FAuthDefaultResponseBP& OnVerifyPlayerRequestCompleted);
    
    /**
    * Terminate the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthroized error.
    *
    * https://ref.lootlocker.io/game-api/#ending-a-session
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void EndSession(const  FAuthDefaultResponseBP& OnEndSessionRequestCompleted);

    //==================================================
    //Players
    //==================================================
    
    /**
    * Get general information about the player, such as the XP, Level information and their account balance.
    * https://ref.lootlocker.io/game-api/#get-player-info
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetPlayerInfo(const FPInfoResponseBP& OnGetPlayerInfoRequestComplete);
    
    /**
    * Get a paginated list of the players inventory.
    * https://ref.lootlocker.io/game-api/#get-inventory-list
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void GetInventory(const FPInventoryResponseBP& OnGetInventoryRequestCompleted);
    
    /**
    * Receive xp, and award it to the player.
    *
    * @param Points - number of XP points to grant to the player.
    * https://ref.lootlocker.io/game-api/#submit-xp
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void SubmitXP(int points, const FPSubmitResponseBP& OnSubmitXPRequestCompleted);
    
    /**
    * Get other players XP and level.
    *
    * @param GetRequests - request data.
    *  https://ref.lootlocker.io/game-api/#get-other-players-xp-and-level
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void GetOtherPlayerInfo(FLootLockerGetRequests& getRequests, const  FPInfoResponseBP& OnGetOtherPlayerInfoRequestCompleted);
    
    /**
    * Get assets that have been granted (given to) the player since the last time this endpoint was called.
    * https://ref.lootlocker.io/game-api/#player-asset-notifications
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void CheckPlayerAssetActivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted);
    
    /**
    * Get asset deactivations since the last time it's been checked.
    * Do not expect both replacement_asset_id and reason to have values at the same time. They can have, but it is not required.
    * https://ref.lootlocker.io/game-api/#player-asset-deactivation-notifications
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted);

    /**
    * This endpoint will return the amount of credits the current player have on their account.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://ref.lootlocker.io/game-api/#get-currency-balance
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetCurrencyBalance(const FPBalanceResponseBP& OnGetCurrencyBalance);

    /**
    * This endpoint will initiate a DLC migration for the current player. 5 minutes after calling this endpoint you should issue 
    * a call to the Player Asset Notifications call, to get the results of the migration, if any.
    *
    * https://ref.lootlocker.io/game-api/#initiate-dlc-migration
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void InitiateDLCMigration(const FResponseCallbackBP& OnInitiateDlcMigration);

    /**
    * This endpoint will return a list of DLC's migrated for the player. The DLC identifiers returned 
    * will be the ones of the platform the DLC belongs to. The identifier will always be a string, even if the identifier is numeric.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://ref.lootlocker.io/game-api/#get-dlcs-migrated
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetDLCsMigration(const FPDlcResponseBP& OnGotDlcMigration);

    /**
    * This endpoint will set the players profile to private. This means that their 
    * inventory will not be displayed publicly on Steam and other places.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://ref.lootlocker.io/game-api/#set-profile-private
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SetProfilePrivate(const FResponseCallbackBP& OnProfileSetPrivate);

    /**
    * This endpoint will set the players profile to public. This means that their inventory will be 
    * displayed publicly on Steam and other places.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://ref.lootlocker.io/game-api/#set-profile-public
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SetProfilePublic(const FResponseCallbackBP& OnProfileSetPublic);

   /**
   * This endpoint will set the players name. 
   *
   * @param name - String name to set.
   * @param OnCompletedRequest - callback to be invoked with the server response.
   * https://ref.lootlocker.io/game-api/#set-player-name
   */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SetPlayerName(FString name, const FPNameResponseBP& OnSetPlayerName);
 
    /**
    * This endpoint will get the players name. 
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://ref.lootlocker.io/game-api/#get-player-name
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetPlayerName(const FPNameResponseBP& OnGetPlayerName);
    
    //==================================================
    //Characters
    //==================================================
    
    /**
    * This call will return all characters loadouts for a game, and have some additional information on the characters.
    * https://ref.lootlocker.io/game-api/#character-loadouts
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted);
    
    /**
    * Equip an asset to the specified character.
    *
    * @param Name - the name of the character.
    * @param IsDefault - if this should be set as the default character.
    * https://ref.lootlocker.io/game-api/#create-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void UpdateCharacter(int CharacterId,bool isDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest);


    /**
    * When creating a character there is only one required field: character_type_id.
    * See List Character Types to get your games Character Types. The other parameters
    * are optional and are the same as for the Update Character call.
    *
    * @param CharacterTypeId - the ID of the type.
    * @param CharacterName - the name of the character.
    * @param IsDefault - if this should be set as the default character.
    * https://ref.lootlocker.io/game-api/#create-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void CreateCharacter(bool IsDefault,  FString CharacterName,  FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP);

    /**

    * Call this endpoint to list the character types configured for your game.
    * 
    * https://ref.lootlocker.io/game-api/#list-character-types
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP);


    /**
    * Equip an asset to the default character.
    *
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    *  https://ref.lootlocker.io/game-api/#equip-asset-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void EquipAssetToDefaultCharacter(int instance_id, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted);
    
    /**
    * Equip an asset to the specified character.
    *
    * @param CharacterId - ID of the character to equip an asset to.
    * @param asset_id - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * https://ref.lootlocker.io/game-api/#equip-asset-to-character-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void EquipAssetToCharacterById(int characterId, int asset_id, int asset_variation_id, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

        /**
    * Equip an asset to the specified character.
    *
    * @param CharacterId - ID of the character to equip an asset to.
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * https://ref.lootlocker.io/game-api/#equip-asset-to-character-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void EquipAssetToCharacterByIdAndInstance(FString CharacterId, int InstanceId,const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);
    
    /**
    * Unequip an asset from the default character.
    *
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * https://ref.lootlocker.io/game-api/#unequip-asset-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void UnEquipAssetToDefaultCharacter(int instance_id, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted);
    
    /**
    * Unequip an asset from the specified character.
    *
    * @param CharacterId - ID of the character to unequip an asset from.
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * https://ref.lootlocker.io/game-api/#unequip-asset-to-character-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void UnEquipAssetToCharacterById(int characterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted);
    
    /**
    * Getting the current loadout will return an array of assets that the user currently has equipped.
    * https://ref.lootlocker.io/game-api/#get-current-loadout-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetCurrentLoadoutToDefaultCharacter(const  FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);
    
    /**
    * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
    *
    * @param OtherPlayerId - other player's ID.
    * https://ref.lootlocker.io/game-api/#get-other-players-loadout-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetOtherPlayersCurrentLoadoutToDefaultCharacter( FString otherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted);
    
    /**
    * 
    * Get the contexts that the player's default character can equip.
    * https://ref.lootlocker.io/game-api/#get-equippable-contexts-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted);
    
    /**
    * 
    * Get the contexts that the specified player's default character can equip.
    *
    * @param otherCharacterId - other player's ID.
    * https://ref.lootlocker.io/game-api/#get-equippable-contexts-by-character-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetEquipableContextsByCharacterId(FString otherCharacterId, const  FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted);
    
    //==================================================
    //Persistent Storage
    //==================================================
    
    /**
    * This call returns all key/value pairs on record for the current player, and can thus be slow if you create many.
    * https://ref.lootlocker.io/game-api/#get-entire-persistent-storage
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted);
    
    /**
    * Get Key/Value pair from the player's persistent storage.
    *
    * @param Key - key of the key/value pair.
    * https://ref.lootlocker.io/game-api/#get-a-single-key-from-persistent-storage
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted);
    
    /**
    * Create/Update key/value pair(s).
    *
    * @param Items - array of items to be created/updated.
    * https://ref.lootlocker.io/game-api/#updating-creating-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void AddItemsToPersistentStorage(const TArray<FLootLockerPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted);
    
    /**
    * Delete a key/value pair.
    *
    * @param Key - key of a key/value pair.
    * https://ref.lootlocker.io/game-api/#deleting-a-key-value-pair
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted);
    
    /**
    * Read another players public key/value storage.
    *
    * @param PlayerId - players id or their public UID.
    * https://ref.lootlocker.io/game-api/#getting-other-players-public-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void GetPlayerPersistentStorage(const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted);
    
    //==================================================
    //Assets
    //==================================================

    /**
    * Get all the contexts the game has.
    * https://ref.lootlocker.io/game-api/#getting-contexts
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetContexts(const FContextDelegateBP& OnGetContextsRequestCompleted);
    
    /**
    * Get all assets in a paginated form.
    *
    * @param StartFromIndex - index of the item to start from.
    * @param ItemsCount - number of items to receive (50-200).
    * @param AssetFilter - optional filter.
    * @param IncludeUGC - whether to include UGC Assets.
    * https://ref.lootlocker.io/game-api/#getting-asset-list
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetAssets(const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted,int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, bool IncludeUGC = false);
    
    /**
    * Retrieve only specific Assets by their ID's.
    *
    * @param AssetIds - array of the asset ID's to be fetched.
    * https://ref.lootlocker.io/game-api/#getting-assets-by-ids
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted);
    
    /**
    * This call will return you all the default bones.
    * If a binding overrides anything on a bone, it will be returned along with the binding.
    * https://ref.lootlocker.io/game-api/#getting-asset-bone-information
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetAssetBones(const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted);
    
    /**
    * This call will simply list the current players favourite assets.
    * https://ref.lootlocker.io/game-api/#listing-favourite-assets
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted);
    
    /**
    * Add an asset to the list of favourites.
    *
    * @param AssetId - asset ID to be added.
    * https://ref.lootlocker.io/game-api/#adding-favourite-assets
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted);
    
    /**
    * Remove an asset from the list of favourites.
    *
    * @param AssetId - asset ID to be removed.
    * https://ref.lootlocker.io/game-api/#removing-favourite-assets
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void RemoveAssetFromFavourites(int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted);
    
    //==================================================
    //Asset Instances
    //==================================================
    
    
    /**
    * Get all key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://ref.lootlocker.io/game-api/#getting-all-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void GetAllKeyValuePairsForAssetInstance(const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted);

    /**
    * Get all key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://ref.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted);

    /**
    * Get a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - ID of the key/value pair.
    * https://ref.lootlocker.io/game-api/#getting-a-key-value-pair-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted);
    
    /**
    * Create a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param Item - key/value pair.
    * https://ref.lootlocker.io/game-api/#creating-a-key-value-pair
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted);
    
    /**
    * Update key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param Items - key/value pairs.
    * https://ref.lootlocker.io/game-api/#updating-one-or-more-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FLootLockerAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);
    
    /**
    * Update a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - key/value pair ID.
    * https://ref.lootlocker.io/game-api/#updating-a-key-value-pair-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);
    
    /**
    * Delete a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - key/value pair ID.
    * https://ref.lootlocker.io/game-api/#delete-a-key-value-pair
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);
    
    /**
    * Asset instances with the type set to loot box can be inspected, to see what assets the player might possibly get when opening them.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://ref.lootlocker.io/game-api/#inspect-a-loot-box
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void InspectLootBox(int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted);
    
    /**
    * 
    * Asset instances with the type set to loot box can be opened, using this endpoint.
    * Once you call this endpoint, the Loot Box will be removed from the players inventory, and a new asset will be added to the inventory,
    * with the acquisition_source set to grant_loot_box. You will be asked to check the grant notifications to see which asset was granted.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://ref.lootlocker.io/game-api/#open-a-loot-box
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted);
    
    //==================================================
    //User Generated Content
    //==================================================
   
    
    /**
    * Create an asset candidate.
    *
    * @param AsssetCandidate - asset candidate data.
    * https://ref.lootlocker.io/game-api/#creating-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void CreateAssetCandidate(const FLootLockerAssetCandidate2& AsssetCandidate, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted);
    
    /**
    * Update an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param AsssetCandidate - asset candidate data.
    * https://ref.lootlocker.io/game-api/#updating-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void UpdateAssetCandidate(int AssetCandidateId, const FLootLockerAssetCandidate2& AsssetCandidate, const  FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted);
    
    /**
    * Delete an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * https://ref.lootlocker.io/game-api/#deleting-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted);
    
    /**
    * Get all asset candidates.
    * https://ref.lootlocker.io/game-api/#listing-asset-candidates
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted);
    
    /**
    * Get an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * https://ref.lootlocker.io/game-api/#getting-a-single-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted);
    
    /**
    * Add a file to an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param FilePath - full absolute path to a file.
    * @param FilePurpose - purpose of the file.
    * https://ref.lootlocker.io/game-api/#adding-files-to-asset-candidates
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted);
    
    /**
    * 
    * Remove a file from an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param FileId - ID of the file.
    * https://ref.lootlocker.io/game-api/#removing-files-from-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted);
    
    //==================================================
    //Missions
    //==================================================
    
    /**
    * Get all missions.
    *  https://ref.lootlocker.io/game-api/#getting-all-missions
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void GetAllMissions(const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted);
    
    /**
    * Get a mission.
    *
    * @param MissionId - mission ID.
    * https://ref.lootlocker.io/game-api/#getting-a-single-mission
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void GetMission(int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted);
    
    /**
    * Start a mission.
    *
    * @param MissionId - mission ID.
    * https://ref.lootlocker.io/game-api/#starting-mission
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void StartMission(int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted);
    
    /**
    * Finish a mission.
    *
    * @param MissionId - mission ID.
    * @param MissionData - mission completion data.
    * https://ref.lootlocker.io/game-api/#finishing-mission
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted);
    
    //==================================================
    //Maps
    //==================================================
    
    /**
    * Get maps data.
    * https://ref.lootlocker.io/game-api/#getting-all-maps
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Maps")
    static void GetMaps(const FGetMapsResponseDelegateBP& OnGetMapsCompleted);
    
    //==================================================
    //Purchases
    //==================================================

    
    /**
    * Sending a request to this endpoint with asset information, will facilitate a purchase.
    * If your game uses soft currency, it will check the players account balance and grant the assets to the player if there is coverage.
    * If there is no coverage, an error will be returned.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * https://ref.lootlocker.io/game-api/#purchase-call
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsCompleted);
    
    /**
    * Platform-specific purchase call for Android.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * https://ref.lootlocker.io/game-api/#android-in-app-purchases
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const  FPurchaseResponseDelegateBP& OnPurchaseAssetsAndroidCompleted);
    
    /**
    * Platform-specific purchase call for iOS.
    *
    * @param PurchaseData - data about the assets to be purchased.
    *  https://ref.lootlocker.io/game-api/#ios-in-app-purchases
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsIOSCompleted);
    
    /**
    * This call will let you know the current status of an order.
    * If you get a response that is considered final, you should issue a call to the player inventory endpoint if you're in a context where the inventory might change.
    *
    * @param PurchaseId - ID of the purchase order.
    *  https://ref.lootlocker.io/game-api/#polling-order-status
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static  void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnPollingStatusCompleted);
    
    /**
    * 
    * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player. This endpoint achieves that.
    * 
    * @param AssetId - ID of the asset.
    * https://ref.lootlocker.io/game-api/#activating-a-rental-asset
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted);
    
    //==================================================
    //Trigger Events
    //==================================================

    /**
    * Trigger an event.
    * 
    * @param Event - data of the event to be triggered.
    * https://ref.lootlocker.io/game-api/#triggering-an-event
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    static void TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnTriggerEventCompleted);
    
    /**
    * This endpoint lists the triggers that a player have already completed.
    * https://ref.lootlocker.io/game-api/#listing-triggered-trigger-events
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    static void GetTriggeredEvents(const FTriggersResponseDelegateBP& OnGetTriggeredEventsCompleted);
    
    //==================================================
    //Collectables
    //==================================================
    
    /**
    * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
    * https://ref.lootlocker.io/game-api/#getting-collectables
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    static void GetAllCollectables(const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted);
    
    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param Item - the slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * 
    * https://ref.lootlocker.io/game-api/#collecting-an-item
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    static void CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted);
    
    //==================================================
    //Messages
    //==================================================

    /**
    * Get all messages for a player.
    * https://ref.lootlocker.io/game-api/#get-messages
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Messages")
    static void GetMessages(const FMessagesResponseDelegateBP& OnGetMessagesCompleted);

    //==================================================
    //Leaderboard
    //==================================================

     /**
    * Get rank for single member for a leaderboard. If leaderboard is of type player a player will also be in the response.
    * 
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param MemberId - the id of player in the leaderboard
    *
    * https://ref.lootlocker.io/game-api/#get-member-rank
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetMemberRank(int LeaderboardId, int MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP);


     /**
    * Get ranks for list of members for a leaderboard. This can be helpful when getting a players friends on leaderboard. 
    * If leaderboard is of type player a player will also be in the response.
    * @param Members - the ids of all leaderboard members you need to get info on.
    * 
    * https://ref.lootlocker.io/game-api/#get-by-list-of-members
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetByListOfMembers(TArray<FString> Members, int LeaderboardId, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP);

     /**
    * Get list of members in rank range. Result is sorted by rank ascending. 
    * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param Count - Number of members returned per page
    * @param After - Curser for pagination, a cursor will be returned in the response
    * 
    * https://ref.lootlocker.io/game-api/#get-score-list
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard") 
    static void GetScoreList(int LeaderboardId, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP);

    /**
    * Get list of members in rank range. Result is sorted by rank ascending.
    * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param Count - Number of members returned per page
    * @param After - Curser for pagination, a cursor will be returned in the response
    * 
    * https://ref.lootlocker.io/game-api/#get-score-list
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetScoreListInitial(int LeaderboardId, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP);

     /**
    * Submit scores for member on leaderboard.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param MemberId - the id of player in the leaderboard.
    * @param Score - the score to be submitted.
    * 
    * https://ref.lootlocker.io/game-api/#submit-scorem
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard") 
    static void SubmitScore(FString MemberId, int LeaderboardId, int Score, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP);
    //==================================================
    //Drop Table
    //==================================================
    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param MemberId - the id of player in the leaderboard.
    * @param Score - the score to be submitted.
    * 
    * https://ref.lootlocker.io/game-api/#compute-and-lock-drop-table
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable")
    static void ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP);

     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param MemberId - the id of player in the leaderboard.
    * @param Score - the score to be submitted.
    * 
    * https://ref.lootlocker.io/game-api/#pick-drops-from-drop-table
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable")
    static void PickDropsFromDropTable(TArray<int> picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP);
};
