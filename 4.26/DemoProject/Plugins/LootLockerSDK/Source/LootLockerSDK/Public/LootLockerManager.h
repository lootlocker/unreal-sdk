// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameAPI/AuthenticationRequestHandler.h"
#include "HttpClient.h"
#include "LootLockerConfig.h"
#include "Engine/DataAsset.h"
#include "GameAPI/PlayerRequestHandler.h"
#include "GameAPI/CharacterRequestHandler.h"
#include "GameAPI/PersistentStorageRequestHandler.h"
#include "GameAPI/AssetsRequestHandler.h"
#include "GameAPI/AssetInstancesRequestHandler.h"
#include "GameAPI/UserGeneratedContentRequestHandler.h"
#include "GameAPI/MissionsRequestHandler.h"
#include "GameAPI/MapsRequestHandler.h"
#include "GameAPI/PurchasesRequestHandler.h"
#include "GameAPI/TriggerEventsRequestHandler.h"
#include "GameAPI/CollectablesRequestHandler.h"
#include "GameAPI/MessagesRequestHandler.h"

#include "LootLockerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerManager : public UObject
{
    GENERATED_BODY()
 
public:
    
    //==================================================
    //Authentication
    //==================================================
    
    /**Invoked after StartSession call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Authentication")
    FAuthResponseBP OnStartedSessionRequestCompleted;
    
    /**Invoked after VerifyPlayer call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Authentication")
    FAuthDefaultResponseBP OnVerifyPlayerRequestCompleted;
    
    /**Invoked after EndSession call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Authentication")
    FAuthDefaultResponseBP OnEndSessionRequestCompleted;
    
    /**
    * Register a session.
    *
    * @param PlayerId - the ID of the player on the platform the game is currently running on.
    *  https://docs.lootlocker.io/game-api/#authentication-request
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    void StartSession(const FString& playerId);
    
    /**
    * If your game uses Player Verification, you need to call this endpoint before you can register a session.
    *
    * @param CachedSteamToken - platform-specific token.
    * https://docs.lootlocker.io/game-api/#player-verification
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    void VerifyPlayer(const FString& CachedSteamToken);
    
    /**
    * Terminate the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthroized error.
    *
    * @param PlayerId - the ID of the player on the platform the game is currently running on.
    * https://docs.lootlocker.io/game-api/#ending-a-session
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    void EndSession(const FString& playerId);

    //==================================================
    //Players
    //==================================================
    
    /**Invoked after GetPlayerInfo call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Players")
    FPInfoResponseBP OnGetPlayerInfoRequestCompleted;
    
    /**Invoked after GetInventory call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Players")
    FPInventoryResponseBP OnGetInventoryRequestCompleted;
    
    /**Invoked after SubmitXP call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Players")
    FPSubmitResponseBP OnSubmitXPRequestCompleted;
    
    /**Invoked after GetOtherPlayerInfo call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Players")
    FPInfoResponseBP OnGetOtherPlayerInfoRequestCompleted;
    
    /**Invoked after CheckPlayerAssetActivationNotification call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Players")
    FPAssetNotificationResponseBP OnCheckPlayerAssetActivationNotificationRequestCompleted;
    
    /**Invoked after CheckPlayerAssetDeactivationNotification call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Players")
    FPAssetNotificationResponseBP OnCheckPlayerAssetDeactivationNotificationRequestCompleted;
    
    /**
    * Get general information about the player, such as the XP, Level information and their account balance.
    * https://docs.lootlocker.io/game-api/#get-player-info
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    void GetPlayerInfo();
    
    /**
    * Get a paginated list of the players inventory.
    * https://docs.lootlocker.io/game-api/#get-inventory-list
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    void GetInventory();
    
    /**
    * Receive xp, and award it to the player.
    *
    * @param Points - number of XP points to grant to the player.
    * https://docs.lootlocker.io/game-api/#submit-xp
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    void SubmitXP(int points);
    
    /**
    * Get other players XP and level.
    *
    * @param GetRequests - request data.
    *  https://docs.lootlocker.io/game-api/#get-other-players-xp-and-level
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    void GetOtherPlayerInfo(FLootLockerGetRequests& getRequests);
    
    /**
    * Get assets that have been granted (given to) the player since the last time this endpoint was called.
    * https://docs.lootlocker.io/game-api/#player-asset-notifications
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    void CheckPlayerAssetActivationNotification();
    
    /**
    * Get asset deactivations since the last time it's been checked.
    * Do not expect both replacement_asset_id and reason to have values at the same time. They can have, but it is not required.
    * https://docs.lootlocker.io/game-api/#player-asset-deactivation-notifications
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    void CheckPlayerAssetDeactivationNotification();
    
    //==================================================
    //Characters
    //==================================================
    
    /**Invoked after GetCharacterLoadout call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterLoadoutResponseBP OnGetCharacterLoadoutRequestCompleted;
    
    /**Invoked after EquipAssetToDefaultCharacter call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterDefaultResponseBP OnEquipAssetToDefaultCharacterRequestCompleted;
    
    /**Invoked after EquipAssetToCharacterById call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterDefaultResponseBP OnEquipAssetToCharacterByIdRequestCompleted;
    
    /**Invoked after UnEquipAssetToDefaultCharacter call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterDefaultResponseBP OnUnEquipAssetToDefaultCharacterRequestCompleted;
    
    /**Invoked after UnEquipAssetToCharacterById call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterDefaultResponseBP OnUnEquipAssetToCharacterByIdRequestCompleted;
    
    /**Invoked after GetCurrentLoadoutToDefaultCharacter call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterLoadoutResponseBP OnGetCurrentLoadoutToDefaultCharacterRequestCompleted;
    
    /**Invoked after GetOtherPlayersCurrentLoadoutToDefaultCharacter call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FPCharacterLoadoutResponseBP OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted;
    
    /**Invoked after GetEquipableContextsToDefaultCharacter call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FContextDelegateBP OnGetEquipableContextsToDefaultCharacterRequestCompleted;
    
    /**Invoked after GetEquipableContextsByCharacterId call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Characters")
    FContextDelegateBP OnGetEquipableContextsByCharacterIdRequestCompleted;
    
    /**
    * This call will return all characters loadouts for a game, and have some additional information on the characters.
    * https://docs.lootlocker.io/game-api/#character-loadouts
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void GetCharacterLoadout();
    
    /**
    * Equip an asset to the default character.
    *
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    *  https://docs.lootlocker.io/game-api/#equip-asset-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void EquipAssetToDefaultCharacter(int instance_id);
    
    /**
    * Equip an asset to the specified character.
    *
    * @param CharacterId - ID of the character to equip an asset to.
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void EquipAssetToCharacterById(int characterId, int asset_id, int asset_variation_id);
    
    /**
    * Unequip an asset from the default character.
    *
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * https://docs.lootlocker.io/game-api/#unequip-asset-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void UnEquipAssetToDefaultCharacter(int instance_id);
    
    /**
    * Unequip an asset from the specified character.
    *
    * @param CharacterId - ID of the character to unequip an asset from.
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * https://docs.lootlocker.io/game-api/#unequip-asset-to-character-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void UnEquipAssetToCharacterById(int characterId, int asset_id,int asset_variation_id);
    
    /**
    * Getting the current loadout will return an array of assets that the user currently has equipped.
    * https://docs.lootlocker.io/game-api/#get-current-loadout-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void GetCurrentLoadoutToDefaultCharacter();
    
    /**
    * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
    *
    * @param OtherPlayerId - other player's ID.
    * https://docs.lootlocker.io/game-api/#get-other-players-loadout-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& otherPlayerId);
    
    /**
    * 
    * Get the contexts that the player's default character can equip.
    * https://docs.lootlocker.io/game-api/#get-equippable-contexts-to-default-character
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void GetEquipableContextsToDefaultCharacter();
    
    /**
    * 
    * Get the contexts that the specified player's default character can equip.
    *
    * @param otherCharacterId - other player's ID.
    * https://docs.lootlocker.io/game-api/#get-equippable-contexts-by-character-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    void GetEquipableContextsByCharacterId(const FString& otherCharacterId);
    
    //==================================================
    //Persistent Storage
    //==================================================
    
    /**Invoked after GetEntirePersistentStorage call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Persistent Storage")
    FPersistentStorageItemsResponseDelegateBP OnPersistentStorageItemsRequestCompleted;
    
    /**Invoked after GetItemFromPersistentStorage call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Persistent Storage")
    FPersistentStorageItemResponseDelegateBP OnPersistentStorageItemRequestCompleted;
    
    /**Invoked after AddItemsToPersistentStorage call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Persistent Storage")
    FPersistentStorageItemsResponseDelegateBP OnPersistentStorageItemsAddRequestCompleted;
    
    /**Invoked after DeleteItemFromPersistentStorage call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Persistent Storage")
    FPersistentStorageItemsResponseDelegateBP OnPersistentStorageItemDeleteRequestCompleted;
    
    /**Invoked after GetPlayerPersistentStorage call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Persistent Storage")
    FPersistentStorageItemsResponseDelegateBP OnGetPlayerPersistentStorageRequestCompleted;
    
    /**
    * This call returns all key/value pairs on record for the current player, and can thus be slow if you create many.
    * https://docs.lootlocker.io/game-api/#get-entire-persistent-storage
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void GetEntirePersistentStorage();
    
    /**
    * Get Key/Value pair from the player's persistent storage.
    *
    * @param Key - key of the key/value pair.
    * https://docs.lootlocker.io/game-api/#get-a-single-key-from-persistent-storage
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void GetItemFromPersistentStorage(const FString& Key);
    
    /**
    * Create/Update key/value pair(s).
    *
    * @param Items - array of items to be created/updated.
    * https://docs.lootlocker.io/game-api/#updating-creating-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items);
    
    /**
    * Delete a key/value pair.
    *
    * @param Key - key of a key/value pair.
    * https://docs.lootlocker.io/game-api/#deleting-a-key-value-pair
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void DeleteItemFromPersistentStorage(const FString& Key);
    
    /**
    * Read another players public key/value storage.
    *
    * @param PlayerId - players id or their public UID.
    * https://docs.lootlocker.io/game-api/#getting-other-players-public-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    void GetPlayerPersistentStorage(const FString& PlayerId);
    
    //==================================================
    //Assets
    //==================================================
    
    /**Invoked after GetContexts call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FContextDelegateBP OnGetContextsRequestCompleted;
    
    /**Invoked after GetAssets call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FAssetsResponseDelegateBP OnGetAssetsRequestCompleted;
    
    /**Invoked after GetAssetsByIds call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FAssetsResponseDelegateBP OnGetAssetsByIdsRequestCompleted;
    
    /**Invoked after GetAssetBones call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FAssetBonesResponseDelegateBP OnGetAssetBonesRequestCompleted;
    
    /**Invoked after GetFavouriteAssetIndices call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FGetFavouriteAssetIndicesResponseDelegateBP OnGetFavouriteAssetIndicesRequestCompleted;
    
    /**Invoked after AddAssetToFavourites call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FGetFavouriteAssetIndicesResponseDelegateBP OnAddAssetToFavouritesRequestCompleted;
    
    /**Invoked after RemoveAssetFromFavourites call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets")
    FGetFavouriteAssetIndicesResponseDelegateBP OnRemoveAssetFromFavouritesRequestCompleted;
    
    /**
    * Get all the contexts the game has.
    * https://docs.lootlocker.io/game-api/#getting-contexts
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void GetContexts();
    
    /**
    * Get all assets in a paginated form.
    *
    * @param StartFromIndex - index of the item to start from.
    * @param ItemsCount - number of items to receive (50-200).
    * @param AssetFilter - optional filter.
    * @param IncludeUGC - whether to include UGC Assets.
    * https://docs.lootlocker.io/game-api/#getting-asset-list
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void GetAssets(int StartFromIndex = 0, int ItemsCount = 50, EAssetFilter AssetFilter = EAssetFilter::None, bool IncludeUGC = false);
    
    /**
    * Retrieve only specific Assets by their ID's.
    *
    * @param AssetIds - array of the asset ID's to be fetched.
    * https://docs.lootlocker.io/game-api/#getting-assets-by-ids
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void GetAssetsByIds(const TArray<int>& AssetIds);
    
    /**
    * This call will return you all the default bones.
    * If a binding overrides anything on a bone, it will be returned along with the binding.
    * https://docs.lootlocker.io/game-api/#getting-asset-bone-information
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void GetAssetBones();
    
    /**
    * This call will simply list the current players favourite assets.
    * https://docs.lootlocker.io/game-api/#listing-favourite-assets
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void GetFavouriteAssetIndices();
    
    /**
    * Add an asset to the list of favourites.
    *
    * @param AssetId - asset ID to be added.
    * https://docs.lootlocker.io/game-api/#adding-favourite-assets
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void AddAssetToFavourites(int AssetId);
    
    /**
    * Remove an asset from the list of favourites.
    *
    * @param AssetId - asset ID to be removed.
    * https://docs.lootlocker.io/game-api/#removing-favourite-assets
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    void RemoveAssetFromFavourites(int AssetId);
    
    //==================================================
    //Asset Instances
    //==================================================
    
    /**Invoked after GetAllKeyValuePairsForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnGetAllKeyValuePairsForAssetInstanceCompleted;
    
    /**Invoked after GetAllKeyValuePairsToAnInstanceForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted;
    
    /**Invoked after GetAKeyValuePairByIdForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnGetAKeyValuePairByIdForAssetInstanceCompleted;

    /**Invoked after CreateAKeyValuePairForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnCreateAKeyValuePairForAssetInstanceCompleted;

    /**Invoked after UpdateOneOrMoreKeyValuePairForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted;
    
    /**Invoked after UpdateStorageItemForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnUpdateAKeyValuePairByIdForAssetInstanceCompleted;
    
    /**Invoked after UpdateAKeyValuePairByIdForAssetInstance call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FAssetInstanceStorageItemsResponseDelegateBP OnDeleteAKeyValuePairByIdForAssetInstanceCompleted;
    
    /**Invoked after InspectLootBox call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FLootBoxContentResponseDelegateBP OnInspectLootBoxCompleted;
    
    /**Invoked after OpenLootBox call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Assets Instances")
    FOpenLootBoxResponseDelegateBP OnOpenLootBoxCompleted;
    
    /**
    * Get all key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void GetAllKeyValuePairsForAssetInstance();

    /**
    * Get all key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId);

    /**
    * Get a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - ID of the key/value pair.
    * https://docs.lootlocker.io/game-api/#getting-a-key-value-pair-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId);
    
    /**
    * Create a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param Item - key/value pair.
    * https://docs.lootlocker.io/game-api/#creating-a-key-value-pair
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item);
    
    /**
    * Update key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param Items - key/value pairs.
    * https://docs.lootlocker.io/game-api/#updating-one-or-more-key-value-pairs
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items);
    
    /**
    * Update a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - key/value pair ID.
    * https://docs.lootlocker.io/game-api/#updating-a-key-value-pair-by-id
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item);
    
    /**
    * Delete a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - key/value pair ID.
    * https://docs.lootlocker.io/game-api/#delete-a-key-value-pair
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId);
    
    /**
    * Asset instances with the type set to loot box can be inspected, to see what assets the player might possibly get when opening them.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://docs.lootlocker.io/game-api/#inspect-a-loot-box
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void InspectLootBox(int AssetInstanceId);
    
    /**
    * 
    * Asset instances with the type set to loot box can be opened, using this endpoint.
    * Once you call this endpoint, the Loot Box will be removed from the players inventory, and a new asset will be added to the inventory,
    * with the acquisition_source set to grant_loot_box. You will be asked to check the grant notifications to see which asset was granted.
    *
    * @param AssetInstanceId - asset instance ID.
    * https://docs.lootlocker.io/game-api/#open-a-loot-box
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    void OpenLootBox(int AssetInstanceId);
    
    //==================================================
    //User Generated Content
    //==================================================
    
    /**Invoked after CreateAssetCandidate call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FCreateAssetCandidateResponseDelegateBP OnCreateAssetCandidateCompleted;
    
    /**Invoked after UpdateAssetCandidate call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FAssetCandidateResponseDelegateBP OnUpdateAssetCandidateCompleted;
    
    /**Invoked after DeleteAssetCandidate call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FResponseCallbackBP OnDeleteAssetCandidateCompleted;
    
    /**Invoked after GetAllAssetCandidates call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FAssetCandidatesResponseDelegateBP OnGetAllAssetCandidatesCompleted;
    
    /**Invoked after GetAssetCandidate call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FAssetCandidateResponseDelegateBP OnGetAssetCandidateCompleted;
    
    /**Invoked after AddFileToAssetCandidate call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FResponseCallbackBP OnAddFileToAssetCandidateCompleted;
    
    /**Invoked after DeleteFileFromAssetCandidate call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | User Generated Content")
    FResponseCallbackBP OnDeleteFileFromAssetCandidateCompleted;
    
    /**
    * Create an asset candidate.
    *
    * @param AsssetCandidate - asset candidate data.
    * https://docs.lootlocker.io/game-api/#creating-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void CreateAssetCandidate(const FAssetCandidate& AsssetCandidate);
    
    /**
    * Update an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param AsssetCandidate - asset candidate data.
    * https://docs.lootlocker.io/game-api/#updating-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate);
    
    /**
    * Delete an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * https://docs.lootlocker.io/game-api/#deleting-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void DeleteAssetCandidate(int AssetCandidateId);
    
    /**
    * Get all asset candidates.
    * https://docs.lootlocker.io/game-api/#listing-asset-candidates
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void GetAllAssetCandidates();
    
    /**
    * Get an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * https://docs.lootlocker.io/game-api/#getting-a-single-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void GetAssetCandidate(int AssetCandidateId);
    
    /**
    * Add a file to an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param FilePath - full absolute path to a file.
    * @param FilePurpose - purpose of the file.
    * https://docs.lootlocker.io/game-api/#adding-files-to-asset-candidates
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose);
    
    /**
    * 
    * Remove a file from an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param FileId - ID of the file.
    * https://docs.lootlocker.io/game-api/#removing-files-from-an-asset-candidate
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId);
    
    //==================================================
    //Missions
    //==================================================
    
    /**Invoked after GetAllMissions call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Missions")
    FMissionsResponseDelegateBP OnGetAllMissionsCompleted;
    
    /**Invoked after GetMission call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Missions")
    FMissionResponseDelegateBP OnGetMissionCompleted;
    
    /**Invoked after StartMission call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Missions")
    FStartMissionResponseDelegateBP OnStartMissionCompleted;
    
    /**Invoked after FinishMission call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Missions")
    FFinishMissionResponseDelegateBP OnFinishMissionCompleted;
    
    /**
    * Get all missions.
    *  https://docs.lootlocker.io/game-api/#getting-all-missions
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void GetAllMissions();
    
    /**
    * Get a mission.
    *
    * @param MissionId - mission ID.
    * https://docs.lootlocker.io/game-api/#getting-a-single-mission
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void GetMission(int MissionId);
    
    /**
    * Start a mission.
    *
    * @param MissionId - mission ID.
    * https://docs.lootlocker.io/game-api/#starting-mission
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void StartMission(int MissionId);
    
    /**
    * Finish a mission.
    *
    * @param MissionId - mission ID.
    * @param MissionData - mission completion data.
    * https://docs.lootlocker.io/game-api/#finishing-mission
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    void FinishMission(int MissionId, const FFinishMissionData& MissionData);
    
    //==================================================
    //Maps
    //==================================================
    
    /**Invoked after GetMaps call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Maps")
    FGetMapsResponseDelegateBP OnGetMapsCompleted;
    
    /**
    * Get maps data.
    * https://docs.lootlocker.io/game-api/#getting-all-maps
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Maps")
    void GetMaps();
    
    //==================================================
    //Purchases
    //==================================================
    
    /**Invoked after PurchaseAssets call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Purchases")
    FPurchaseResponseDelegateBP OnPurchaseAssetsCompleted;
    
    /**Invoked after PurchaseAssetsAndroid call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Purchases")
    FPurchaseResponseDelegateBP OnPurchaseAssetsAndroidCompleted;
    
    /**Invoked after VerifyPurchaseIos call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Purchases")
    FPurchaseResponseDelegateBP OnPurchaseAssetsIOSCompleted;
    
    /**Invoked after PollPurchaseStatus call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Purchases")
    FPurchaseStatusResponseDelegateBP OnPollingStatusCompleted;
    
    /**Invoked after ActivateRentalAsset call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Purchases")
    FActivateRentalAssetResponseDelegateBP OnActivateRentalAssetCompleted;
    
    /**
    * Sending a request to this endpoint with asset information, will facilitate a purchase.
    * If your game uses soft currency, it will check the players account balance and grant the assets to the player if there is coverage.
    * If there is no coverage, an error will be returned.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * https://docs.lootlocker.io/game-api/#purchase-call
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData);
    
    /**
    * Platform-specific purchase call for Android.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * https://docs.lootlocker.io/game-api/#android-in-app-purchases
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData);
    
    /**
    * Platform-specific purchase call for iOS.
    *
    * @param PurchaseData - data about the assets to be purchased.
    *  https://docs.lootlocker.io/game-api/#ios-in-app-purchases
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void PurchaseAssetsIOS(const TArray<FVerifyPurchaseIosData>& PurchaseData);
    
    /**
    * This call will let you know the current status of an order.
    * If you get a response that is considered final, you should issue a call to the player inventory endpoint if you're in a context where the inventory might change.
    *
    * @param PurchaseId - ID of the purchase order.
    *  https://docs.lootlocker.io/game-api/#polling-order-status
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void PollingOrderStatus(int PurchaseId);
    
    /**
    * 
    * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player. This endpoint achieves that.
    * 
    * @param AssetId - ID of the asset.
    * https://docs.lootlocker.io/game-api/#activating-a-rental-asset
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    void ActivateRentalAsset(int AssetId);
    
    //==================================================
    //Trigger Events
    //==================================================
    
    /**Invoked after TriggerEvent call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Trigger Events")
    FTriggerEventResponseDelegateBP OnTriggerEventCompleted;
    
    /**Invoked after GetTriggeredEvents call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Trigger Events")
    FTriggersResponseDelegateBP OnGetTriggeredEventsCompleted;
    
    /**
    * Trigger an event.
    * 
    * @param Event - data of the event to be triggered.
    * https://docs.lootlocker.io/game-api/#triggering-an-event
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    void TriggerEvent(const FTriggerEvent& Event);
    
    /**
    * This endpoint lists the triggers that a player have already completed.
    * https://docs.lootlocker.io/game-api/#listing-triggered-trigger-events
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    void GetTriggeredEvents();
    
    //==================================================
    //Collectables
    //==================================================
    
    /**Invoked after GetAllCollectables call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Collectables")
    FCollectablesResponseDelegateBP OnGetAllCollectablesCompleted;
    
    /**Invoked after CollectItem call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Collectables")
    FCollectablesResponseDelegateBP OnCollectItemCompleted;
    
    /**
    * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
    * https://docs.lootlocker.io/game-api/#getting-collectables
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    void GetAllCollectables();
    
    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param Item - the slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * 
    * https://docs.lootlocker.io/game-api/#collecting-an-item
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    void CollectItem(const FCollectItemPayload& Item);
    
    //==================================================
    //Messages
    //==================================================
    
    /**Invoked after GetMessages call.*/
    UPROPERTY(BlueprintAssignable, Category = "LootLocker Callbacks | Messages")
    FMessagesResponseDelegateBP OnGetMessagesCompleted;
    
    /**
    * Get all messages for a player.
    * https://docs.lootlocker.io/game-api/#get-messages
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Messages")
    void GetMessages();
};
