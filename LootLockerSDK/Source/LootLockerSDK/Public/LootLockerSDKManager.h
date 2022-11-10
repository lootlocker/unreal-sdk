// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerConfig.h"
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
#include "GameAPI/LootLockerDropTablesRequestHandler.h"
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
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
     * Start a session with the platform used in the platform selected in Project Settings -> Platform.
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param PlayerIdentifier The ID of the player on the platform the game is currently running on.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void StartSession(const FString& PlayerIdentifier, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Create a new session for a Nintendo Switch user
     * The Nintendo Switch platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#nintendo-switch
     *
     * @param NSAIdToken NSA (Nintendo Switch Account) id token as a string
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
    static void StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Create a new session for an Xbox user
     * The Xbox platform must be enabled in the web console for this to work.
     *
     * @param XboxUserToken Xbox user token as a string
     * @param OnCompletedRequest Delegate for handling the response of FLootLockerAuthenticationResponse
     */
    static void StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Create a new session for Sign in with Apple
     * The Apple sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-apple
     *
     * @param AuthorizationCode Authorization code, provided by apple
     * @param OnCompletedRequest Delegate for handling the response of type  for handling the response of type FLootLockerAppleSessionResponse
     */
    static void StartAppleSession(const FString& AuthorizationCode, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest);

    /**
     * Refresh a previous session signed in with Apple
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Apple sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-apple
     *
     * @param RefreshToken Token received in response from StartAppleSession request
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAppleSessionResponse
     */
    static void RefreshAppleSession(const FString& RefreshToken, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest);

    /**
     * Start a guest session with an identifier, you can use something like a unique device identifier to tie the account to a device.
     * https://ref.lootlocker.com/game-api/#guest-login
     *
     * @param PlayerIdentifier Identifier for the player
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
    static void GuestLogin(const FString& PlayerIdentifier, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Verify the player's identity with the server and selected platform.
     * If your game uses Player Verification, you need to call this endpoint before you can register a session.
     * https://ref.lootlocker.io/game-api/#player-verification
     *
     *
     * @param PlatformToken Platform-specific token.
     * @param OnCompletedRequest Response Delegate to handle the response
     * @param Platform Optional parameter to call explicitly for a specific platform
     */
    static void VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest, const FString Platform = FString(TEXT("")));

    /**
     * End active session (if any exists)
     * Terminates the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthorized error.
     * Succeeds if a session was ended or no sessions were active
     * https://ref.lootlocker.io/game-api/#ending-a-session
     *
     * @param OnCompletedRequest Delegate for handling the response of type LootLockerSessionResponse
     */
    static void EndSession(const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest);

    //==================================================
    // White Label
    //==================================================

    /**
     * Create a new user using the White Label login system.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-up
     *
     * @param Email E-mail for the new user
     * @param Password Password for the new user
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerLoginResponse
     */
    static void WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate& OnCompletedRequest);

    /**
     * Log in a White Label user with the given email and password combination, verify user, and start a White Label Session.
     * Set remember=true to prolong the session lifetime
     * https://ref.lootlocker.com/game-api/#login
     *
     * White Label platform must be enabled in the web console for this to work.
     * @param Email - The Email for the white label account
     * @param Password - The Password for the white label account
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerLoginResponse
     * @param Remember - Optional flag to prolong the session lifetime
     */
    static void WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate& OnCompletedRequest, const bool Remember = false);

    /**
     * Start a LootLocker Session using the cached White Label token and email if any exist
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#white-label-authentication
     *
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
	static void WhiteLabelStartSession(const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Checks if the cached session token is valid for the provided White Label email.
     *
     * Depending on response of this method the developer can either start a session using the token, or show a login form.
     *
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#verify-session
     *
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerWhiteLabelVerifySessionResponse
     */
	static void WhiteLabelVerifySession(const FLootLockerWhiteLabelVerifySessionDelegate &OnCompletedRequest);

    /**
     * Request verify account email for the user.
     * White Label platform must be enabled in the web console for this to work.
     * Account verification must also be enabled.
     * https://ref.lootlocker.com/game-api/#request-user-verification
     *
     * @param UserId The UserId for the white label user
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerResponse
     */
    static void WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     * Request a password reset email for the given email address.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#request-reset-password
     *
     * @param Email The email for the white label user
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerResponse
     */
    static void WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest);

    //==================================================
	//Player calls
    //==================================================

    /**
     * Get general information about the current current player, such as the XP, Level information and their account balance.
     * https://ref.lootlocker.io/game-api/#get-player-info
     *
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest);

    /**
    * Get a paginated list of the players inventory.
    * https://docs.lootlocker.io/game-api/#get-inventory-list
    *
    * @param OnCompletedRequest Delegate to be invoked with the server response.
    */
	static void GetInventory(const FInventoryResponse& OnCompletedRequest);

	// Same as above but actually gets your full inventory lol.
	static void GetFullInventory(const FInventoryResponse& OnCompletedRequest, int32 StartIndex);

    /**
    * Receive xp, and award it to the player.
    * https://ref.lootlocker.io/game-api/#submit-xp
    *
    * @param Points Number of XP points to grant to the player.
    * @param OnCompletedRequest Delegate to be invoked with the server response.
    */
	static void SubmitXP(int Points, const FSubmitXpResponse& OnCompletedRequest);

    /**
    * Get other players XP and level.
    * https://docs.lootlocker.io/game-api/#get-other-players-xp-and-level
    *
    * @param OtherPlayerId Other players id.
    * @param OnCompletedRequest Delegate to be invoked with the server response.
    * @param OtherPlayerPlatform Optional parameter to specify which platform the Id is for.
    */
	static void GetOtherPlayersXpAndLevel(FString OtherPlayerId, const FOtherPlayersXpAndLevelResponse & OnCompletedRequest, FString OtherPlayerPlatform = FString(TEXT("")));

    /**
    * Get Multiple Other Players XP And Level.
    * https://ref.lootlocker.com/game-api/#get-multiple-other-players-xp-and-level
    *
    * @param Platform Specify which platform the Ids are for.
    * @param PlayerIDs Lost of player ids on the specified platform.
    * @param OnGetOtherPlayerInfoRequestCompleted Delegate to be invoked with the server response.
    */
	static void GetMultiplePlayersXp(FLootLockerMultiplePlayersXpRequest& Request, const FPMultiplePlayersXP& OnCompletedRequest);

    /**
    * Get assets that have been granted to the player since the last time this endpoint was called.
    * https://docs.lootlocker.io/game-api/#player-asset-notifications
    *
    * @param OnCompletedRequest Delegate to be invoked with the server response.
    */
	static void CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest);

    /**
    * This endpoint will return the amount of credits the current player have on their account.
    * https://docs.lootlocker.io/game-api/#get-currency-balance
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void GetCurrencyBalance(const FPBalanceResponse& OnCompletedRequest);

    /**
    * This endpoint will initiate a DLC migration for the current player. 5 minutes after calling this endpoint you should issue
    * a call to the Player Asset Notifications call, to get the results of the migration, if any.
    *
    * https://ref.lootlocker.io/game-api/#initiate-dlc-migration
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void InitiateDLCMigration(const FResponseCallback& OnCompletedRequest);

    /**
    * This endpoint will return a list of DLC's migrated for the player. The DLC identifiers returned
    * will be the ones of the platform the DLC belongs to. The identifier will always be a string, even if the identifier is numeric.
    * https://docs.lootlocker.io/game-api/#get-dlcs-migrated
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void GetDLCsMigration(const FPDlcResponse& OnCompletedRequest);

    /**
    * This endpoint will set the players profile to private. This means that their
    * inventory will not be displayed publicly on Steam and other places.
    * https://docs.lootlocker.io/game-api/#set-profile-private
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void SetProfilePrivate(const FResponseCallback& OnCompletedRequest);

    /**
    * This endpoint will set the players profile to public. This means that their inventory will be
    * displayed publicly on Steam and other places.
    * https://docs.lootlocker.io/game-api/#set-profile-public
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void SetProfilePublic(const FResponseCallback& OnCompletedRequest);

	/**
	* This endpoint will set the players name.
	* https://docs.lootlocker.io/game-api/#set-profile-public
	*
	* @param Name String player name
	* @param OnCompletedRequest Delegate for handling the server response.
	*/
	static void SetPlayerName(FString Name, const FPNameResponse& OnCompletedRequest);

	/**
	* This endpoint will get the players name.
	* https://docs.lootlocker.io/game-api/#set-profile-public
	*
	* @param OnCompletedRequest Delegate for handling the server response.
	*/
	static void GetPlayerName(const FPNameResponse& OnCompletedRequest);

    /**
    * This endpoint will return all known players 1st party platform id's.
    * https://ref.lootlocker.com/game-api/#lookup-multiple-player-names-using-ids
    *
    * @param Request Request array with platforms and Ids to search for.
    * @param OnCompletedRequest Delegate for handling the server response.
    */
	static void LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNames& OnCompletedRequest);

    /**
    * This endpoint will return all known players 1st party platform id's.
    * https://ref.lootlocker.com/game-api/#lookup-multiple-player-1st-platform-ids-using-lootlocker-player-ids
    *
    * @param Request Request array with player ids and/or player public uids to search for.
    * @param OnCompletedRequest Delegate for handling the server response.
    */
	static void LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest);

    //==================================================
	//Files
	// https://ref.lootlocker.io/game-api/#player-files
    //==================================================

    /**
     * Upload a file with the provided name and content. The file will be owned by the currently active player.
     * https://ref.lootlocker.com/game-api/#upload-a-file
     *
     * @param Request Request of type FLootLockerFileUploadRequest.
     * @param OnComplete Delegate for handling the response
     */
    static void UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete);

    /**
     * Returns all the files that your currently active player own.
     * https://ref.lootlocker.com/game-api/#list-files
     *
     * @param OnComplete Delegate for handling the response of type LootLockerPlayerFilesResponse
     */
    static void ListFiles(const FLootLockerFileListDelegate& OnComplete);

    /**
     * Returns all public files that the player with the provided playerID owns.
     * https://ref.lootlocker.com/game-api/#list-another-players-public-files
     *
     * @param PlayerID Player ID of the player for whom to get the files
     * @param OnComplete Delegate for handling the response of type LootLockerPlayerFilesResponse
     */
    static void ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete);

    /**
     * Returns a URL where you can access the file. You can get the ID of files when you upload them, or call the list endpoint.
     * https://ref.lootlocker.com/game-api/#get-single-file
     *
     * @param FileID Id of the file, can be retrieved with ListFiles or when the file is uploaded
     * @param OnComplete Delegate for handling the response
     */
    static void GetSingleFile(const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete);

    /**
     * The file will be deleted immediately and the action can not be reversed. You will get the ID of files when you upload a file, or with ListFiles.
     * https://ref.lootlocker.com/game-api/#delete-file
     *
     * @param FileID Id of the file. You can get the ID of files when you upload a file, or with GetAllPlayerFiles()
     * @param OnComplete Delegate for handling the response
     */
    static void DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete);

	//==================================================
	//Heroes
	//==================================================

    /**
     * List heroes with names and character information
     * https://ref.lootlocker.com/game-api/#get-game-heroes
     *
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void GetGameHeroes(const FLootLockerGameHeroListDelegate& OnCompleteRequest);

    /**
     * List heroes that the current player owns
     * https://ref.lootlocker.com/game-api/#list-player-heroes
     *
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void ListPlayerHeroes(const FLootLockerHeroListDelegate& OnCompleteRequest);

    /**
     * List player that the player with the specified SteamID64 owns
     * https://ref.lootlocker.com/game-api/#list-other-players-heroes-by-steamid64
     *
     * @param SteamID64 Steam Id of the requested player
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListDelegate& OnCompleteRequest);

    /**
     * Create a hero for the current player with the supplied name from the game hero specified with the supplied hero id
     * https://ref.lootlocker.com/game-api/#creating-a-hero
     *
     * @param Request Request specifying the hero id for the game hero to use for creation and the name of the hero to create
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void CreateHero(const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompleteRequest);

    /**
     * Return information about the requested hero on the current player
     * https://ref.lootlocker.com/game-api/#getting-a-hero
     *
     * @param HeroID Id of the hero to get
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void GetHero(const int32 HeroID, const FLootLockerPlayerHeroDelegate& OnCompletedRequest);

    /**
     * Get the default hero for the player with the specified SteamID64
     * https://ref.lootlocker.com/game-api/#get-other-players-default-hero-by-steamid64
     *
     * @param SteamID64 Steam Id of the requested player
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroDelegate& OnCompleteRequest);

    /**
     * Update the name of the hero with the specified id and/or set it as default for the current player
     * https://ref.lootlocker.com/game-api/#updating-a-hero
     *
     * @param HeroID Id of the hero
     * @param Request Request specifying the new (or same) name to set for the hero and if it is to be the default hero for the player
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest &Request, const FLootLockerPlayerHeroDelegate &OnCompletedRequest);

    /**
     * Remove the hero with the specified id from the current players list of heroes.
     * This action is currently irreversible.
     * When deleting a hero, the heroes inventory is returned to the player, and their loadout is reset.
     * https://ref.lootlocker.com/game-api/#deleting-a-hero
     *
     * @param HeroID Id of the hero
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseDelegate& OnCompletedRequest);

    /**
     * List Asset Instances owned by the specified hero
     *
     * Note that this endpoint is paginated and will return the first 50 entries
     * https://ref.lootlocker.com/game-api/#get-hero-inventory
     *
     * @param HeroID Id of the hero
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void GetHeroInventory(const int32 HeroID, const FInventoryResponse& OnCompleteRequest);

    /**
     * List the loadout of the specified hero that the current player owns
     *
     * https://ref.lootlocker.com/game-api/#get-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest);

    /**
     * List the loadout of the specified hero that the another player owns
     * https://ref.lootlocker.com/game-api/#get-other-players-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest);

    /**
     * Equip the specified Asset Instance to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetInstanceID Desc
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest);

    /**
     * Unequip the specified Asset Instance to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#remove-asset-from-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetInstanceID Desc
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest);
	
    //==================================================
	//Characters
    // https://ref.lootlocker.com/game-api/#characters
    //==================================================

    /**
     * This call will return all characters loadouts for a game, and have some additional information on the characters.
     * https://docs.lootlocker.io/game-api/#character-loadouts
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * This endpoint lets you set a character as default, and set the name of the character.
     * https://docs.lootlocker.io/game-api/#update-character
     *
     * @param CharacterId Id of the character to make the update for
     * @param IsDefault Should the character be set as default
     * @param Name The name to set for the character
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateCharacter(int CharacterId, bool IsDefault, FString& Name, const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * Create a character of the specified character type with the given name
     * If IsDefault is set to true, the new character will be made the default character.
     * See List Character Types to get your games Character Types.
     * https://docs.lootlocker.io/game-api/#create-character
     *
     * @param IsDefault If this should be set as the default character.
     * @param CharacterName The name of the character.
     * @param CharacterTypeId The ID of the character type.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterTypeId,  const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * Call this endpoint to list the character types configured for your game.
     * https://docs.lootlocker.io/game-api/#list-character-types
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest);


    /**
     * Equip an asset to the default character.
     * https://docs.lootlocker.io/game-api/#equip-asset-to-default-character
     *
     * @param InstanceId The asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Equip an asset to the specified character.
     * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to equip an asset to.
     * @param AssetId the asset's instance_id that is returned from the inventory and loadout calls.
     * @param AssetVariationId the asset_variation_id.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Equip an asset to the specified character.
     * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to equip an asset to.
     * @param InstanceId the asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void EquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Unequip an asset from the default character.
     * https://docs.lootlocker.io/game-api/#unequip-asset-to-default-character
     *
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Unequip an asset from the specified character.
     * https://docs.lootlocker.io/game-api/#unequip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to unequip an asset from.
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Getting the current loadout will return an array of assets that the user currently has equipped.
     * https://docs.lootlocker.io/game-api/#get-current-loadout-to-default-character
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
     * https://docs.lootlocker.io/game-api/#get-other-players-loadout-to-default-character
     *
     * @param OtherPlayerId other player's ID on the requested platform.
     * @param OnCompletedRequest Delegate for handling the server response.
     * @param OtherPlayerPlatform Optional: the platform the id refers to if different than the current platform
     */
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& OtherPlayerPlatform = FString(TEXT("")));

    /**
     * Get the contexts that the player's default character can equip.
     * https://docs.lootlocker.io/game-api/#get-equippable-contexts-to-default-character
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest);

    /**
     * Get the contexts that the specified player's default character can equip.
     * https://docs.lootlocker.io/game-api/#get-equippable-contexts-by-character-id
     *
     * @param OtherCharacterId other player's ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate& OnCompletedRequest);

    //==================================================
    //Persistent Storage
    // https://ref.lootlocker.com/game-api/#persistent-player-storage
    //==================================================

    /**
     * This call returns all key/value pairs on record for the current player, beware that it may be a lot of data.
     * https://docs.lootlocker.io/game-api/#get-entire-persistent-storage
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Get Key/Value pair from the player's persistent storage.
     * https://docs.lootlocker.io/game-api/#get-a-single-key-from-persistent-storage
     *
     * @param Key Key of the key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Create/Update key/value pair(s).
     * https://docs.lootlocker.io/game-api/#updating-creating-key-value-pairs
     *
     * @param Items array of items to be created/updated.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Create/Update a key/value pair.
     * https://docs.lootlocker.io/game-api/#updating-creating-key-value-pairs
     *
     * @param Item item to be created/updated.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddItemsToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Delete a key/value pair.
     * https://docs.lootlocker.io/game-api/#deleting-a-key-value-pair
     *
     * @param Key key of a key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Read another players public key/value storage.
     * https://docs.lootlocker.io/game-api/#getting-other-players-public-key-value-pairs
     *
     * @param PlayerId players id or their public UID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    //==================================================
    //Assets
    //==================================================

    /**
     * Get all the contexts the game has.
     * https://docs.lootlocker.io/game-api/#getting-contexts
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetContexts(const FContextDelegate& OnCompletedRequest);

    /**
     * Get all assets in a paginated form.
     * https://docs.lootlocker.io/game-api/#getting-asset-list
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     * @param StartFromIndex Optional: Index of the item to start from, defaults to 0
     * @param ItemsCount Optional: Number of items to receive (50-200), defaults to 50
     * @param AssetFilter Optional: Filter to apply, defaults to None
     * @param Context Optional: Context filter to apply, defaults to 0
     * @param IncludeUGC Optional: Whether to include UGC Assets, defaults to false
     */
    static void GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, int Context = 0, bool IncludeUGC = false);

	/**
	 * This call offers a paginated list of the games universal assets
	 * https://docs.lootlocker.io/game-api/#get-universal-assets
	 *
	 * @param After Last universal id to start after.
	 * @param ItemsCount Number of items to receive (50-200).
	 * @param OnCompletedRequest Delegate for handling the server response.
	 */
	static void GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegate &OnCompletedRequest);

    /**
     * Retrieve only specific Assets by their ID's.
     * https://docs.lootlocker.io/game-api/#getting-assets-by-ids
     *
     * @param AssetIds Array of the asset ID's to be fetched.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest);

    /**
     * This call will return you all the default bones.
     * If a binding overrides anything on a bone, it will be returned along with the binding.
     * https://docs.lootlocker.io/game-api/#getting-asset-bone-information
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest);

    /**
     * List the current players favourite assets.
     * https://docs.lootlocker.io/game-api/#listing-favourite-assets
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);

    /**
     * Add an asset to the list of favourites.
     * https://docs.lootlocker.io/game-api/#adding-favourite-assets
     *
     * @param AssetId Asset ID to be added.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);

    /**
     * Remove an asset from the list of favourites.
     * https://docs.lootlocker.io/game-api/#removing-favourite-assets
     *
     * @param AssetId asset ID to be removed.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);

    //==================================================
    //Asset Instances
    // https://ref.lootlocker.com/game-api/#asset-instances
    //==================================================

    /**
     * Get all key/value pairs for an asset instance.
     * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Get all key/value pairs for an asset instance.
     * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Get a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#getting-a-key-value-pair-by-id
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId ID of the key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Create a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#creating-a-key-value-pair
     *
     * @param AssetInstanceId asset instance ID.
     * @param Item key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Update key/value pairs for an asset instance.
     * https://docs.lootlocker.io/game-api/#updating-one-or-more-key-value-pairs
     *
     * @param AssetInstanceId asset instance ID.
     * @param Items key/value pairs.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Update a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#updating-a-key-value-pair-by-id
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
	 * @param Item Struct FLootLockerAssetInstanceStorageItem
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Delete a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#delete-a-key-value-pair
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Asset instances with the type set to loot box can be inspected, to see what assets the player might possibly get when opening them.
     * https://docs.lootlocker.io/game-api/#inspect-a-loot-box
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest);

    /**
     * Asset instances with the type set to loot box can be opened, using this endpoint.
     * Once you call this endpoint, the Loot Box will be removed from the players inventory, and a new asset will be added to the inventory,
     * with the acquisition_source set to grant_loot_box. You will be asked to check the grant notifications to see which asset was granted.
     *  https://docs.lootlocker.io/game-api/#open-a-loot-box
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest);

    //==================================================
    //User Generated Content
    //==================================================

    /**
     * Create an asset candidate.
     * https://docs.lootlocker.io/game-api/#creating-an-asset-candidate
     *
     * @param AssetCandidateData asset candidate data.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest);

    /**
     * Update an asset candidate.
     * https://docs.lootlocker.io/game-api/#updating-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param AssetCandidateData asset candidate data.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    /**
     * Delete an asset candidate.
     * https://docs.lootlocker.io/game-api/#deleting-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest);

    /**
     * Get all asset candidates.
     * https://docs.lootlocker.io/game-api/#listing-asset-candidates
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest);

    /**
     * Get an asset candidate.
     * https://docs.lootlocker.io/game-api/#getting-a-single-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    /**
     * Add a file to an asset candidate.
     * https://docs.lootlocker.io/game-api/#adding-files-to-asset-candidates
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param FilePath full absolute path to a file.
     * @param FilePurpose purpose of the file.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest);

    /**
     * Remove a file from an asset candidate.
     * https://docs.lootlocker.io/game-api/#removing-files-from-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param FileId ID of the file.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest);

    //==================================================
    //Missions
    //==================================================

    /**
     * Get all missions.
     * https://docs.lootlocker.io/game-api/#getting-all-missions
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest);

    /**
     * Get a mission.
     * https://docs.lootlocker.io/game-api/#getting-a-single-mission
     *
     * @param MissionId mission ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest);

    /**
     * Start a mission.
     * https://docs.lootlocker.io/game-api/#starting-mission
     *
     * @param MissionId mission ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest);

    /**
     * Finish a mission.
     * https://docs.lootlocker.io/game-api/#finishing-mission
     *
     * @param MissionId mission ID.
     * @param MissionData mission completion data.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest);

    //==================================================
    //Maps
    // https://ref.lootlocker.com/game-api/#maps
    //==================================================

    /**
     * Get maps data.
     * https://docs.lootlocker.io/game-api/#getting-all-maps
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest);

    //==================================================
    //Purchases
    // https://ref.lootlocker.com/game-api/#purchasing
    //==================================================

    /**
     * Purchase an asset
     * If your game uses soft currency, it will check the players account balance and grant the assets to the player if there is coverage.
     * If there is no coverage, an error will be returned.
     * https://docs.lootlocker.io/game-api/#purchase-call
     *
     * @param PurchaseData Data about the assets to be purchased.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);

    /**
     * Platform-specific purchase call for Android.
     * https://docs.lootlocker.io/game-api/#android-in-app-purchases
     *
     * @param PurchaseData Data about the assets to be purchased.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);

    /**
     * Platform-specific purchase call for iOS.
     * https://docs.lootlocker.io/game-api/#ios-in-app-purchases
     *
     * @param PurchaseData data about the assets to be purchased.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);

    /**
     * Get the status of an order.
     * If you get a response that is considered final, you should issue a call to the player inventory endpoint if you're in a context where the inventory might change.
     *  https://docs.lootlocker.io/game-api/#polling-order-status
     *
     * @param PurchaseId ID of the purchase order.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest);

    /**
     * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player. This endpoint achieves that.
     * https://docs.lootlocker.io/game-api/#activating-a-rental-asset
     *
     * @param AssetId ID of the asset.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest);

    /**
     * Get details on an order, like what products it contains as well as the order status.
     * https://ref.lootlocker.com/game-api/#get-order-details
     *
     * @param OrderId ID of the order.
     * @param NoProducts Set to true if you do not want products in the order returned in the response.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetOrderDetails(int32 OrderId, const bool NoProducts, const FOrderStatusDetailsDelegate& OnCompletedRequest);

    //==================================================
    //Trigger Events
    // https://ref.lootlocker.com/game-api/#trigger-events
    //==================================================

    /**
     * Trigger an event.
     * https://docs.lootlocker.io/game-api/#triggering-an-event
     *
     * @param Event data of the event to be triggered.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest);

    /**
    * This endpoint lists the triggers that a player have already completed.
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    * https://docs.lootlocker.io/game-api/#listing-triggered-trigger-events
    */
    static void GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest);

    //==================================================
    //Collectables
    //==================================================

    /**
    * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    * https://docs.lootlocker.io/game-api/#getting-collectables
    */
    static void GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest);

    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    *
    * @param Item the slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param OnCompletedRequest Delegate for handling the server response.
    * https://docs.lootlocker.io/game-api/#collecting-an-item
    */
    static void CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest);

    //==================================================
    //Messages
    //==================================================

    /**
    * Get all messages for a player.
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    * https://docs.lootlocker.io/game-api/#get-messages
    */
    static void GetMessages(const FMessagesResponseDelegate& OnCompletedRequest);

     //==================================================
    //Leaderboard
    //==================================================

     /**
    * Get rank for single member for a leaderboard. If leaderboard is of type player a player will also be in the response.
    *
    * @param LeaderboardId the id of the leaderboard you need to connect to.
    * @param MemberId the id of player in the leaderboard
    * @param OnCompletedRequest FLootLockerGetMemberRankResponseDelegate
    *
    * https://ref.lootlocker.io/game-api/#get-member-rank
    */
    static void GetMemberRank(int LeaderboardId, int MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest);


     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param Members the ids of all leaderboard members you need to get info on.
    * @param LeaderboardId int32
    * @param OnCompletedRequest FLootLockerGetByListOfMembersResponseDelegate
    * https://ref.lootlocker.io/game-api/#get-by-list-of-members
    */
    static void GetByListOfMembers(TArray<FString> Members, int LeaderboardId, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest);

     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId the id of the leaderboard you need to connect to.
    * @param Count Number of members returned per page
    * @param After Curser for pagination, a cursor will be returned in the response
    *
    * https://ref.lootlocker.io/game-api/#get-score-list
    */
    static void GetScoreList(int LeaderboardId, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest);

    /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId the id of the leaderboard you need to connect to.
    * @param Count Number of members returned per page
    * @param OnCompletedRequest FLootLockerGetScoreListResponseDelegate
    *
    * https://ref.lootlocker.io/game-api/#get-score-list
    */
    static void GetScoreListInitial(int LeaderboardId, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest);


     /**
    * Collecting an Item is done by calling this endpoint with a payload equal to the slug of the Item.
    * The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
    * @param LeaderboardId the id of the leaderboard you need to connect to.
    * @param MemberId the id of player in the leaderboard.
    * @param Score the score to be submitted.
    * @param OnCompletedRequest FLootLockerSubmitScoreResponseDelegate
    * https://ref.lootlocker.io/game-api/#submit-scorem
    */
    static void SubmitScore(FString MemberId, const int LeaderboardId, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest);

	/**
	* Get all leaderboards with member information on the ones the member is on, with rank and score, as well as player information if the leaderboard is of type player.
   * If metadata is enabled for the leaderboard, that will be returned in the response.
   * @param MemberId player_id if player type leaderboard, otherwise id used when submitting the score
   * @param Count Number of members returned per page
   * @param After Curser for pagination, a cursor will be returned in the response
   *
   * https://ref.lootlocker.com/game-api/#get-all-member-ranks
   */
	static void GetAllMemberRanks(int MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest);
	
     //==================================================
    //Drop Table
    //==================================================
    /**
    * Compute drop table
    *
    * @param TableId Drop table ID
    * @param OnCompletedRequest FLootLockerComputeAndLockDropTableResponseDelegate
    *
    * https://ref.lootlocker.io/game-api/#submit-scorem
    */
    static void ComputeAndLockDropTable(const int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest);

    /**
   * Picks drops from drop table.
   *
   * @param Picks TArray int32 picked item IDs
   * @param TableId drop table ID
   * @param OnCompletedRequest FFLootLockerPickDropsFromDropTableResponseDelegate
   *
   * https://ref.lootlocker.io/game-api/#submit-scorem
   */
    static void PickDropsFromDropTable(const TArray<int> Picks,const int TableId,const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest);

	//==================================================
	//Miscellaneous
	//==================================================

	/**
	* Get the current time of the server. Can also be used to ping the server
	*
	* @param OnCompletedRequest Delegate for handling the server response.
	* https://ref.lootlocker.com/game-api/#server-time
	*/
	static void GetServerTime(const FTimeResponseDelegate& OnCompletedRequest);

};
