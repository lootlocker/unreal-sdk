// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "LootLockerSDKManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerSDKManager : public UObject
{
	GENERATED_BODY()

public:
    
    //==================================================
    //Authentication
    //==================================================
    
    /**
     * Register a session.
     * @param PlayerIdentifier - the ID of the player on the platform the game is currently running on.
     * @param OnCompletedRequest - callback to be invoked with the server response.
     * https://docs.lootlocker.io/game-api/#authentication-request
     */
	static void StartSession(const FString& PlayerIdentifier, const FLootLockerSessionResponse& OnCompletedRequest);
    
    /**
    * If your game uses Player Verification, you need to call this endpoint before you can register a session.
    * @param SteamSessionTicket - platform-specific token.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#player-verification
    */
	static void VerifyPlayer(const FString& SteamSessionTicket, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest);
    
    /**
    * Terminate the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthroized error.
    *
    * @param PlayerId - the ID of the player on the platform the game is currently running on.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#ending-a-session
    */
	static void EndSession(const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest);
    
    //==================================================
	//Player calls
    //==================================================
    
    /**
    * Get general information about the player, such as the XP, Level information and their account balance.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-player-info
    */
	static void GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest);
    
    /**
    * Get a paginated list of the players inventory.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-inventory-list
    */
	static void GetInventory(const FInventoryResponse& OnCompletedRequest);
    
	/**
	* Get a list of the games universal assets.
	*
	* @param OnCompletedRequest - callback to be invoked with the server response.
	* https://ref.lootlocker.com/game-api/#get-universal-assets
	*/
	static void GetUniversalAssets(const FUniversalAssetsResponse& OnCompletedRequest);

	
    /**
    * Receive xp, and award it to the player.
    *
    * @param Points - number of XP points to grant to the player.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#submit-xp
    */
	static void SubmitXP(int Points, const FSubmitXpResponse& OnCompletedRequest);
    
    /**
    * Get other players XP and level.
    *
    * @param GetRequests - request data.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-other-players-xp-and-level
    */
	static void GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const FLootLockerPlayerInformationResponse& OnCompletedRequest);
    
    /**
    * Get assets that have been granted (given to) the player since the last time this endpoint was called.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#player-asset-notifications
    */
	static void CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest);
    
    /**
    * Get asset deactivations since the last time it's been checked.
    * Do not expect both replacement_asset_id and reason to have values at the same time. They can have, but it is not required.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#player-asset-deactivation-notifications
    */
	static void CheckPlayerAssetDeactivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest);
    
    /**
    * This endpoint will return the amount of credits the current player have on their account.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-currency-balance
    */
    static void GetCurrencyBalance(const FPBalanceResponse& onCompletedRequest);

    /**
    * This endpoint will initiate a DLC migration for the current player. 5 minutes after calling this endpoint you should issue 
    * a call to the Player Asset Notifications call, to get the results of the migration, if any.
    *
    * https://docs.lootlocker.io/game-api/#initiate-dlc-migration
    */
    static void InitiateDLCMigration(const FResponseCallback& OnCompletedRequest);

    /**
    * This endpoint will return a list of DLC's migrated for the player. The DLC identifiers returned 
    * will be the ones of the platform the DLC belongs to. The identifier will always be a string, even if the identifier is numeric.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-dlcs-migrated
    */
    static void GetDLCsMigration(const FPDlcResponse& OnCompletedRequest);

    /**
    * This endpoint will set the players profile to private. This means that their 
    * inventory will not be displayed publicly on Steam and other places.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#set-profile-private
    */
    static void SetProfilePrivate(const FResponseCallback& OnCompletedRequest);

    /**
    * This endpoint will set the players profile to public. This means that their inventory will be 
    * displayed publicly on Steam and other places.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#set-profile-public
    */
    static void SetProfilePublic(const FResponseCallback& OnCompletedRequest);

	/**
	* This endpoint will set the players name. 
	* @param name - String player name
	* @param OnCompletedRequest - callback to be invoked with the server response.
	* https://docs.lootlocker.io/game-api/#set-player-name
	*/
	static void SetPlayerName(FString name, const FPNameResponse& OnCompletedRequest);

	/**
	* This endpoint will get the players name. 
	* @param OnCompletedRequest - callback to be invoked with the server response.
	* https://docs.lootlocker.io/game-api/#get-player-name
	*/
	static void GetPlayerName(const FPNameResponse& OnCompletedRequest);

    //==================================================
	//Characters
    //==================================================
    
    /**
    * This call will return all characters loadouts for a game, and have some additional information on the characters.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#character-loadouts
    */
	static void GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest);
    
    /**
    * This endpoint lets you set a character as default, and set the name of the character. None of the parameters are required.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#update-character
    */
    static void UpdateCharacter(int CharacterId, bool isDefault, FString& Name, const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
    * When creating a character there is only one required field: character_type_id.
    * See List Character Types to get your games Character Types. The other parameters
    * are optional and are the same as for the Update Character call.
    *
    * @param CharacterTypeId - the ID of the type.
    * @param CharacterName - the name of the character.
    * @param IsDefault - if this should be set as the default character.
    * https://docs.lootlocker.io/game-api/#create-character
    */
    static void CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterId,  const FCharacterLoadoutResponse& OnCompletedRequest);

    /**

    * Call this endpoint to list the character types configured for your game.
    * 
    * https://docs.lootlocker.io/game-api/#list-character-types
    */
    static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest);


    /**
    * Equip an asset to the default character.
    *
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#equip-asset-to-default-character
    */
	static void EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
    
    /**
    * Equip an asset to the specified character.
    *
    * @param CharacterId - ID of the character to equip an asset to.
    * @param AssetId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
    */
	static void EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
    
        /**
    * Equip an asset to the specified character.
    *
    * @param CharacterId - ID of the character to equip an asset to.
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
    */
	static void EquipAssetToCharacterById(FString CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
    * Unequip an asset from the default character.
    *
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#unequip-asset-to-default-character
    */
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
    
    /**
    * Unequip an asset from the specified character.
    *
    * @param CharacterId - ID of the character to unequip an asset from.
    * @param InstanceId - the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId - the asset_variation_id.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#unequip-asset-to-character-by-id
    */
	static void UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);
    
    /**
    * Getting the current loadout will return an array of assets that the user currently has equipped.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#get-current-loadout-to-default-character
    */
	static void GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest);
    
    /**
    * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
    *
    * @param OtherPlayerId - other player's ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-other-players-loadout-to-default-character
    */
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest);
    
    /**
    * Get the contexts that the player's default character can equip.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-equippable-contexts-to-default-character
    */
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest);
    
    /**
    * Get the contexts that the specified player's default character can equip.
    *
    * @param OtherPlayerId - other player's ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-equippable-contexts-by-character-id
    */
	static void GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const FContextDelegate& OnCompletedRequest);
    
	//==================================================
	//Heroes
	//==================================================

	static void GetGameHeroes(const FGameHeroesResponse& OnGetGameHeroesRequestCompleted);

	static void ListPlayerHeroes(const FHeroesResponse& OnListPlayerHeroesRequestCompleted);
	
	static void CreateHero(FString CharacterName, int HeroId, const FHeroResponse& OnCompletedRequestBP);
	
	static void GetHero(int HeroId, const FHeroResponse& OnCompletedRequestBP);
	
	static void GetHeroLoadout(int HeroId, const FHeroLoadoutResponse& OnCompletedRequestBP);
	
	static void DeleteHero(int HeroId, const FHeroDefaultResponse& OnCompletedRequestBP);

    //==================================================
    //Persistent Storage
    //==================================================
    
    /**
    * This call returns all key/value pairs on record for the current player, and can thus be slow if you create many.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-entire-persistent-storage
    */
    static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Get Key/Value pair from the player's persistent storage.
    *
    * @param Key - key of the key/value pair.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-a-single-key-from-persistent-storage
    */
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest);
    
    /**
    * Create/Update key/value pair(s).
    *
    * @param Items - array of items to be created/updated.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#updating-creating-key-value-pairs
    */
    static void AddItemsToPersistentStorage(const TArray<FLootLockerPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Delete a key/value pair.
    *
    * @param Key - key of a key/value pair.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#deleting-a-key-value-pair
    */
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Read another players public key/value storage.
    *
    * @param PlayerId - players id or their public UID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-other-players-public-key-value-pairs
    */
    static void GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Assets
    //==================================================
    
    /**
    * Get all the contexts the game has.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-contexts
    */
    static void GetContexts(const FContextDelegate& OnCompletedRequest);
    
    /**
    * Get all assets in a paginated form.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * @param StartFromIndex - index of the item to start from.
    * @param ItemsCount - number of items to receive (50-200).
    * @param AssetFilter - optional filter.
    * @param Context - optional context filter.
    * @param IncludeUGC - whether to include UGC Assets.
    * https://docs.lootlocker.io/game-api/#getting-asset-list
    */
    static void GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, int Context = 0, bool IncludeUGC = false);
    
    /**
    * Retrieve only specific Assets by their ID's.
    *
    * @param AssetIds - array of the asset ID's to be fetched.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#getting-assets-by-ids
    */
    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest);
    
    /**
    * This call will return you all the default bones.
    * If a binding overrides anything on a bone, it will be returned along with the binding.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-asset-bone-information
    */
    static void GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest);
    
    /**
    * This call will simply list the current players favourite assets.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#listing-favourite-assets
    */
    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);
    
    /**
    * Add an asset to the list of favourites.
    *
    * @param AssetId - asset ID to be added.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#adding-favourite-assets
    */
    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);
    
    /**
    * Remove an asset from the list of favourites.
    *
    * @param AssetId - asset ID to be removed.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#removing-favourite-assets
    */
    static void RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Asset Instances
    //==================================================
    
    /**
    * Get all key/value pairs for an asset instance.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
    */
    static void GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Get all key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
    */
    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
    * Get a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - ID of the key/value pair.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-a-key-value-pair-by-id
    */
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Create a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param Item - key/value pair.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#creating-a-key-value-pair
    */
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Update key/value pairs for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param Items - key/value pairs.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#updating-one-or-more-key-value-pairs
    */
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FLootLockerAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Update a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - key/value pair ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#updating-a-key-value-pair-by-id
    */
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Delete a key/value pair for an asset instance.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param StorageItemId - key/value pair ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#delete-a-key-value-pair
    */
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);
    
    /**
    * Asset instances with the type set to loot box can be inspected, to see what assets the player might possibly get when opening them.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#inspect-a-loot-box
    */
    static void InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest);
    
    /**
    * Asset instances with the type set to loot box can be opened, using this endpoint.
    * Once you call this endpoint, the Loot Box will be removed from the players inventory, and a new asset will be added to the inventory,
    * with the acquisition_source set to grant_loot_box. You will be asked to check the grant notifications to see which asset was granted.
    *
    * @param AssetInstanceId - asset instance ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#open-a-loot-box
    */
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //User Generated Content
    //==================================================
    
    /**
    * Create an asset candidate.
    *
    * @param AsssetCandidate - asset candidate data.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#creating-an-asset-candidate
    */
    static void CreateAssetCandidate(const FLootLockerAssetCandidate2& AsssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest);
    
    /**
    * Update an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param AsssetCandidate - asset candidate data.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#updating-an-asset-candidate
    */
    static void UpdateAssetCandidate(int AssetCandidateId, const FLootLockerAssetCandidate2& AsssetCandidate, const FAssetCandidateResponseDelegate& OnCompletedRequest);
    
    /**
    * Delete an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#deleting-an-asset-candidate
    */
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest);
    
    /**
    * Get all asset candidates.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#listing-asset-candidates
    */
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest);
    
    /**
    * Get an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-a-single-asset-candidate
    */
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest);
    
    /**
    * Add a file to an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param FilePath - full absolute path to a file.
    * @param FilePurpose - purpose of the file.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#adding-files-to-asset-candidates
    */
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest);
    
    /**
    * Remove a file from an asset candidate.
    *
    * @param AssetCandidateId - ID of the asset candidate.
    * @param FileId - ID of the file.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#removing-files-from-an-asset-candidate
    */
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest);
    
    //==================================================
    //Missions
    //==================================================
    
    /**
    * Get all missions.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-all-missions
    */
    static void GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest);
    
    /**
    * Get a mission.
    *
    * @param MissionId - mission ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-a-single-mission
    */
    static void GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest);
    
    /**
    * Start a mission.
    *
    * @param MissionId - mission ID.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#starting-mission
    */
    static void StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest);
    
    /**
    * Finish a mission.
    *
    * @param MissionId - mission ID.
    * @param MissionData - mission completion data.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#finishing-mission
    */
    static void FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Maps
    //==================================================
    
    /**
    * Get maps data.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-all-maps
    */
    static void GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Purchases
    //==================================================
    
    /**
    * Sending a request to this endpoint with asset information, will facilitate a purchase.
    * If your game uses soft currency, it will check the players account balance and grant the assets to the player if there is coverage.
    * If there is no coverage, an error will be returned.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#purchase-call
    */
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);
    
    /**
    * Platform-specific purchase call for Android.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#android-in-app-purchases
    */
    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);
    
    /**
    * Platform-specific purchase call for iOS.
    *
    * @param PurchaseData - data about the assets to be purchased.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#ios-in-app-purchases
    */
    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);
    
    /**
    * This call will let you know the current status of an order.
    * If you get a response that is considered final, you should issue a call to the player inventory endpoint if you're in a context where the inventory might change.
    *
    * @param PurchaseId - ID of the purchase order.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    *  https://docs.lootlocker.io/game-api/#polling-order-status
    */
    static void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest);
    
    /**
    * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player. This endpoint achieves that.
    *
    * @param AssetId - ID of the asset.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#activating-a-rental-asset
    */
    static void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Trigger Events
    //==================================================
    
    /**
    * Trigger an event.
    *
    * @param Event - data of the event to be triggered.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#triggering-an-event
    */
    static void TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest);
    
    /**
    * This endpoint lists the triggers that a player have already completed.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#listing-triggered-trigger-events
    */
    static void GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Collectables
    //==================================================
    
    /**
    * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#getting-collectables
    */
    static void GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest);
    
    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    *
    * @param Item - the slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#collecting-an-item
    */
    static void CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest);
    
    //==================================================
    //Messages
    //==================================================
    
    /**
    * Get all messages for a player.
    *
    * @param OnCompletedRequest - callback to be invoked with the server response.
    * https://docs.lootlocker.io/game-api/#get-messages
    */
    static void GetMessages(const FMessagesResponseDelegate& OnCompletedRequest);

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
    static void GetMemberRank(int LeaderboardId, int MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest);


     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param Members - the ids of all leaderboard members you need to get info on.
    * 
    * https://ref.lootlocker.io/game-api/#get-by-list-of-members
    */
    static void GetByListOfMembers(TArray<FString> Members, int LeaderboardId, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest);

     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param Count - Number of members returned per page
    * @param After - Curser for pagination, a cursor will be returned in the response
    * 
    * https://ref.lootlocker.io/game-api/#get-score-list
    */
    static void GetScoreList(int LeaderboardId, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest);

    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param Count - Number of members returned per page
    * @param After - Curser for pagination, a cursor will be returned in the response
    *
    * https://ref.lootlocker.io/game-api/#get-score-list
    */
    static void GetScoreListInitial(int LeaderboardId, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest);


     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId - the id of the leaderboard you need to connect to.
    * @param MemberId - the id of player in the leaderboard.
    * @param Score - the score to be submitted.
    * 
    * https://ref.lootlocker.io/game-api/#submit-scorem
    */
    static void SubmitScore(FString MemberId, int LeaderboardId, int Score, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest);

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
    * https://ref.lootlocker.io/game-api/#submit-scorem
    */
    static void ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest);

    /**
   * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
   * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
   * @param LeaderboardId - the id of the leaderboard you need to connect to.
   * @param MemberId - the id of player in the leaderboard.
   * @param Score - the score to be submitted.
   *
   * https://ref.lootlocker.io/game-api/#submit-scorem
   */
    static void PickDropsFromDropTable(TArray<int> picks, int TableId,const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest);


};
