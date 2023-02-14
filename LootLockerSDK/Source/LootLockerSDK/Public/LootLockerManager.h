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
#include "GameAPI/LootLockerDropTablesRequestHandler.h"
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include "GameAPI/LootLockerProgressionsRequestHandler.h"

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
     * DEPRECATED: Start a session with the platform used in the platform selected in Project Settings -> Platform.
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param PlayerIdentifier The ID of the current device the player is on
     * @param OnStartedSessionRequestCompleted Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (DeprecatedFunction, DeprecationMessage = "This method has been deprecated. Please use the appropriate \"StartXSession\" instead.\nFor Android use StartAndroidSession. For iOS use StartAppleSession. For Steam use StartSteamSession. For PlayStation use StartPlaystationNetworkSession. For Amazon Luna use StartAmazonLunaSession. If you are unsure of what to use, use GuestLogin."))
    static void StartSession(const FString& PlayerIdentifier, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for a Playstation Network user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param PsnOnlineId The PSN Online ID of the player
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for an Android user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param DeviceId The device id of the player
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for a Amazon Luna user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param AmazonLunaGuid The Amazon Luna GUID of the player
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for a Steam user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param SteamId64 The Steam 64 bit Id as an FString
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartSteamSession(const FString& SteamId64, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Create a new session for a Nintendo Switch user
     * The Nintendo Switch platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#nintendo-switch
     *
     * @param NSAIdToken NSA (Nintendo Switch Account) id token as a string
     * @param OnStartedNintendoSwitchSessionRequestCompleted Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnStartedNintendoSwitchSessionRequestCompleted);

    /**
     * Create a new session for an Xbox user
     * The Xbox platform must be enabled in the web console for this to work.
     *
     * @param XboxUserToken Xbox user token as a string
     * @param OnStartedXboxSessionCompleted Delegate for handling the response of FLootLockerAuthenticationResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnStartedXboxSessionCompleted);

    /**
     * Create a new session for Sign in with Apple
     * The Apple sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-apple
     *
     * @param AuthorizationCode Authorization code, provided by apple
     * @param OnStartedAppleSessionCompleted Delegate for handling the response of type  for handling the response of type FLootLockerAppleSessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnStartedAppleSessionCompleted);

    /**
     * Refresh a previous session signed in with Apple
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Apple sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-apple
     *
     * @param RefreshToken Token received in response from StartAppleSession request
     * @param OnRefreshAppleSessionCompleted Delegate for handling the response of type FLootLockerAppleSessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void RefreshAppleSession(const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted);

    /**
     * Create a new user using the White Label login system.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-up
     *
     * @param Email E-mail for the new user
     * @param Password Password for the new user
     * @param OnWhiteLabelAccountCreationRequestCompleted Delegate for handling the response of type FLootLockerLoginResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelAccountCreationRequestCompleted);
    
    /**
     * Log in a White Label user with the given email and password combination, verify user, and start a White Label Session.
     * Note: Use WhiteLabelLoginAndStartSession unless there's a specific purpose to use this method instead.
     * Set remember=true to prolong the session lifetime
     * https://ref.lootlocker.com/game-api/#login
     *
     * White Label platform must be enabled in the web console for this to work.
     * @param Email The Email for the white label account
     * @param Password The Password for the white label account
     * @param OnWhiteLabelLoginRequestCompleted Delegate for handling the response of type FLootLockerLoginResponse
     * @param Remember Optional flag to prolong the session lifetime
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta=(AdvancedDisplay=3))
    static void WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelLoginRequestCompleted, const bool Remember = false);

    /**
     * Start a LootLocker Session using the cached White Label token and email if any exist
     * Note: Use WhiteLabelLoginAndStartSession unless there's a specific purpose to use this method instead.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#white-label-authentication
     *
     * @param OnStartWhiteLabelSessionRequestCompleted Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelStartSession(const FAuthResponseBP& OnStartWhiteLabelSessionRequestCompleted);

    /**
     * Login and Start a LootLocker Session using a White Label account
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#white-label-authentication
     *
     * @param Email - The Email for the white label account
     * @param Password - The Password for the white label account
     * @param OnWhiteLabelLoginAndStartSessionRequestCompleted Delegate for handling the response of type FLootLockerWhiteLabelLoginAndSessionResponse
     * @param Remember - Optional flag to prolong the session lifetime
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember = false);

    /**
     * Checks if the cached session token is valid for the provided White Label email.
     *
     * Depending on response of this method the developer can either start a session using the token, or show a login form.
     *
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#verify-session
     *
     * @param OnVerifyWhiteLabelSessionRequestCompleted Delegate for handling the response of type FLootLockerWhiteLabelVerifySessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
	static void WhiteLabelVerifySession(const FLootLockerVerifySessionResponseBP &OnVerifyWhiteLabelSessionRequestCompleted);

    /**
     * Request verify account email for the user.
     * White Label platform must be enabled in the web console for this to work.
     * Account verification must also be enabled.
     * https://ref.lootlocker.com/game-api/#request-user-verification
     *
     * @param UserId The UserId for the white label user
     * @param OnRequestWhiteLabelUserVerificationRequestCompleted Delegate for handling the response of type FLootLockerResponse
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
	static void WhiteLabelRequestUserVerification(const int &UserId, const FLootLockerDefaultResponseBP &OnRequestWhiteLabelUserVerificationRequestCompleted);

    /**
     * Request a password reset email for the given email address.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#request-reset-password
     *
     * @param Email The email for the white label user
     * @param OnResetWhiteLabelPasswordRequestCompleted Delegate for handling the response of type FLootLockerResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
	static void WhiteLabelResetPassword(const FString &Email, const FLootLockerDefaultResponseBP &OnResetWhiteLabelPasswordRequestCompleted);

    /**
     * Start a guest session with an identifier, you can use something like a unique device identifier to tie the account to a device.
     * https://ref.lootlocker.com/game-api/#guest-login
     *
     * @param PlayerIdentifier Optional: Identifier for the player. Needs to be unique for each player, so only set this explicitly if you want to set a specific name for the guest player. Otherwise, an id will be generated for the player.
     * @param OnCompletedRequestBP Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
	static void GuestLogin(const FAuthResponseBP& OnCompletedRequestBP, const FString& PlayerIdentifier = "");

    /**
     * Verify the player's identity with the server and selected platform.
     * If your game uses Player Verification, you need to call this endpoint before you can register a session.
     * https://ref.lootlocker.io/game-api/#player-verification
     *
     *
     * @param PlatformToken Platform-specific token.
     * @param OnVerifyPlayerRequestCompleted Response Delegate to handle the response
     * @param Platform Optional parameter to call explicitly for a specific platform
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void VerifyPlayer(const FString& PlatformToken, const FAuthDefaultResponseBP& OnVerifyPlayerRequestCompleted, const FString Platform = FString(TEXT("")));

    /**
     * End active session (if any exists)
     * Terminates the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthorized error.
     * Succeeds if a session was ended or no sessions were active
     * https://ref.lootlocker.io/game-api/#ending-a-session
     *
     * @param OnEndSessionRequestCompleted Delegate for handling the response of type LootLockerSessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void EndSession(const  FAuthDefaultResponseBP& OnEndSessionRequestCompleted);

    //==================================================
    //Players
    //==================================================

    /**
     * Get general information about the current current player, such as the XP, Level information and their account balance.
     * https://ref.lootlocker.io/game-api/#get-player-info
     *
     * @param OnGetPlayerInfoRequestComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetPlayerInfo(const FPInfoResponseBP& OnGetPlayerInfoRequestComplete);

    /**
    * Get a paginated list of the players inventory.
    * https://docs.lootlocker.io/game-api/#get-inventory-list
    *
    * @param OnGetInventoryRequestCompleted Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetInventory(const FPInventoryResponseBP& OnGetInventoryRequestCompleted);

    /**
    * Receive xp, and award it to the player.
    * https://ref.lootlocker.io/game-api/#submit-xp
    *
    * @param Points Number of XP points to grant to the player.
    * @param OnSubmitXPRequestCompleted Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SubmitXP(int Points, const FPSubmitResponseBP& OnSubmitXPRequestCompleted);

    /**
    * Get other players XP and level.
    * https://docs.lootlocker.io/game-api/#get-other-players-xp-and-level
    *
    * @param OtherPlayerId Other players id.
    * @param OnGetOtherPlayersXpAndLevelRequestCompleted Delegate for handling the the server response.
    * @param OtherPlayerPlatform Optional parameter to specify which platform the Id is for.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetOtherPlayersXpAndLevel(FString OtherPlayerId, const FPOtherPlayersXpAndLevelBP& OnGetOtherPlayersXpAndLevelRequestCompleted, FString OtherPlayerPlatform = FString(TEXT("")));

	/**
	* Get Multiple Other Players XP And Level.
	* https://ref.lootlocker.com/game-api/#get-multiple-other-players-xp-and-level
	*
    * @param Platform Specify which platform the Ids are for.
    * @param PlayerIDs Lost of player ids on the specified platform.
    * @param OnGetOtherPlayerInfoRequestCompleted Delegate for handling the the server response.
	*/
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void GetMultiplePlayersXp(FString Platform, TArray<FString> PlayerIDs, const  FPMultiplePlayersXPBP& OnGetOtherPlayerInfoRequestCompleted);

    /**
    * Get assets that have been granted to the player since the last time this endpoint was called.
    * https://docs.lootlocker.io/game-api/#player-asset-notifications
    *
    * @param OnCheckPlayerAssetDeactivationNotificationRequestCompleted Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
     static void CheckPlayerAssetActivationNotification(const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted);

    /**
    * This endpoint will return the amount of credits the current player have on their account.
    * https://docs.lootlocker.io/game-api/#get-currency-balance
    *
    * @param OnGetCurrencyBalance Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetCurrencyBalance(const FPBalanceResponseBP& OnGetCurrencyBalance);

    /**
    * This endpoint will initiate a DLC migration for the current player. 5 minutes after calling this endpoint you should issue
    * a call to the Player Asset Notifications call, to get the results of the migration, if any.
    *
    * https://ref.lootlocker.io/game-api/#initiate-dlc-migration
    *
    * @param OnInitiateDlcMigration Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void InitiateDLCMigration(const FResponseCallbackBP& OnInitiateDlcMigration);

    /**
    * This endpoint will return a list of DLC's migrated for the player. The DLC identifiers returned
    * will be the ones of the platform the DLC belongs to. The identifier will always be a string, even if the identifier is numeric.
    * https://ref.lootlocker.io/game-api/#get-dlcs-migrated
    *
    * @param OnGotDlcMigration Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetDLCsMigration(const FPDlcResponseBP& OnGotDlcMigration);

    /**
    * This endpoint will set the players profile to private. This means that their
    * inventory will not be displayed publicly on Steam and other places.
    * https://ref.lootlocker.io/game-api/#set-profile-private
    *
    * @param OnProfileSetPrivate Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SetProfilePrivate(const FResponseCallbackBP& OnProfileSetPrivate);

    /**
    * This endpoint will set the players profile to public. This means that their inventory will be
    * displayed publicly on Steam and other places.
    * https://ref.lootlocker.io/game-api/#set-profile-public
    *
    * @param OnProfileSetPublic Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SetProfilePublic(const FResponseCallbackBP& OnProfileSetPublic);

   /**
   * This endpoint will set the players name.
   * https://ref.lootlocker.io/game-api/#set-player-name
   *
   * @param Name String name to set.
   * @param OnSetPlayerName Delegate for handling the the server response.
   */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void SetPlayerName(FString Name, const FPNameResponseBP& OnSetPlayerName);

    /**
    * This endpoint will get the players name.
    * https://ref.lootlocker.io/game-api/#get-player-name
    *
    * @param OnGetPlayerName Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void GetPlayerName(const FPNameResponseBP& OnGetPlayerName);

	/**
	* This endpoint will return the names of the players on their last active platform.
	* https://ref.lootlocker.com/game-api/#lookup-multiple-player-names-using-ids
	*
	* @param Request Request array with platforms and Ids to search for.
	* @param OnCompletedRequest Delegate for handling the the server response.
	*/
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
	static void LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNamesBP& OnCompletedRequest);

    /**
    * This endpoint will return the names of the players on their last active platform.
    * https://ref.lootlocker.com/game-api/#lookup-multiple-player-1st-platform-ids-using-lootlocker-player-ids
    *
    * @param Request Request array with player ids and/or player public uids to search for.
    * @param OnCompletedRequest Delegate for handling the the server response.
    */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
	static void LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest &Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest);

    /**
    * This method will mark the player for deletion. After 30 days the player will be deleted from the system.
    * https://ref.lootlocker.com/game-api/#delete-player
    *
    * @param OnCompletedRequest Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players")
    static void DeletePlayer(const FLootLockerDefaultResponseBP& OnCompletedRequest);

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
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files")
	static void UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete);

    /**
     * Update the specified file with the supplied content. The file will be owned by the currently active player.
     * https://ref.lootlocker.com/game-api/#update-a-file
     *
     * @param FileId Id of the file, can be retrieved with ListFiles or when the file is uploaded
     * @param Request Request of type FLootLockerFileUpdateRequest.
     * @param OnComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files")
    static void UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete);

    /**
     * Returns all the files that your currently active player own.
     * https://ref.lootlocker.com/game-api/#list-files
     *
     * @param OnComplete Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files")
	static void ListFiles(const FLootLockerFileListBP& OnComplete);

    /**
     * Returns all public files that the player with the provided playerID owns.
     * https://ref.lootlocker.com/game-api/#list-another-players-public-files
     *
     * @param PlayerID Player ID of the player for whom to get the files
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files")
    static void ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP);

    /**
     * Returns a URL where you can access the file. You can get the ID of files when you upload them, or call the list endpoint.
     * https://ref.lootlocker.com/game-api/#get-single-file
     *
     * @param FileID Id of the file, can be retrieved with ListFiles or when the file is uploaded
     * @param OnComplete Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files")
	static void GetSingleFile(const int32 FileID, const FLootLockerUploadFileBP& OnComplete);

    /**
     * The file will be deleted immediately and the action can not be reversed. You will get the ID of files when you upload a file, or with ListFiles.
     * https://ref.lootlocker.com/game-api/#delete-file
     *
     * @param FileID Id of the file. You can get the ID of files when you upload a file, or with GetAllPlayerFiles()
     * @param OnComplete Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files")
	static void DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP& OnComplete);

    //==================================================
    // Player Progressions
    //==================================================

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "Count,After", Count = -1, After = ""))
    static void GetPlayerProgressions(const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest);

    /**
    * Returns a single progression the player is currently on.
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions")
    static void GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest);

    /**
    * Adds points to the specified player progression.
    *
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions")
    static void AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Subtracts points from the specified player progression.
    *
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions")
    static void SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Resets the specified player progression.
    *
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions")
    static void ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param ProgressionKey Key of the progression you want to delete
    * @param OnCompletedRequest Action for handling the response of type FLootLockerResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions")
    static void DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest);

	//==================================================
	//Heroes
    // https://ref.lootlocker.com/game-api/#heroes
	//==================================================

    /**
     * List heroes with names and character information
     * https://ref.lootlocker.com/game-api/#get-game-heroes
     *
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void GetGameHeroes(const FLootLockerGameHeroListBP& OnCompleteBP);

    /**
     * List heroes that the current player owns
     * https://ref.lootlocker.com/game-api/#list-player-heroes
     *
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void ListPlayerHeroes(const FLootLockerHeroListBP& OnCompleteBP);

    /**
     * List player that the player with the specified SteamID64 owns
     * https://ref.lootlocker.com/game-api/#list-other-players-heroes-by-steamid64
     *
     * @param SteamID64 Steam Id of the requested player
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP);

    /**
     * Create a hero for the current player with the supplied name from the game hero specified with the supplied hero id
     * https://ref.lootlocker.com/game-api/#creating-a-hero
     *
     * @param Request Request specifying the hero id for the game hero to use for creation and the name of the hero to create
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void CreateHero(const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Create a hero for the current player with the supplied name from the game hero specified with the supplied hero id, asset variation id, and whether to set as default.
     * https://ref.lootlocker.com/game-api/#creating-a-hero
     *
     * @param Request Request specifying the hero id for the game hero to use for creation and the name of the hero to create, an asset variation id for this hero, and whether this hero should be the default
     * @param OnCompleteBP Delegate for handling the response
     */
	static void CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Return information about the requested hero on the current player
     * https://ref.lootlocker.com/game-api/#getting-a-hero
     *
     * @param HeroID Id of the hero to get
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void GetHero(const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Get the default hero for the player with the specified SteamID64
     * https://ref.lootlocker.com/game-api/#get-other-players-default-hero-by-steamid64
     *
     * @param SteamID64 Steam Id of the requested player
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void GetOtherPlayersDefaultHeroBySteamID64(const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Update the name of the hero with the specified id and/or set it as default for the current player
     * https://ref.lootlocker.com/game-api/#updating-a-hero
     *
     * @param HeroID Id of the hero
     * @param Request Request specifying the new (or same) name to set for the hero and if it is to be the default hero for the player
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Remove the hero with the specified id from the current players list of heroes.
     * This action is currently irreversible.
     * When deleting a hero, the heroes inventory is returned to the player, and their loadout is reset.
     * https://ref.lootlocker.com/game-api/#deleting-a-hero
     *
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP);

    /**
     * List Asset Instances owned by the specified hero
     *
     * Note that this endpoint is paginated and will return the first 50 entries
     * https://ref.lootlocker.com/game-api/#get-hero-inventory
     *
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void GetHeroInventory(const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP);

    /**
     * List the loadout of the specified hero that the current player owns
     *
     * https://ref.lootlocker.com/game-api/#get-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * List the loadout of the specified hero that the another player owns
     * https://ref.lootlocker.com/game-api/#get-other-players-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Equip the specified Asset Instance to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetInstanceID Desc
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Equip the specified Asset Variation to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetID Desc
     * @param AssetVariationID Desc
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void AddAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Unequip the specified Asset Instance to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#remove-asset-from-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetInstanceID Desc
     * @param OnCompleteBP Delegate for handling the response
     */
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes")
	static void RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    //==================================================
    //Characters
    // https://ref.lootlocker.com/game-api/#characters
    //==================================================

    /**
    * This call will return all characters loadouts for a game, and have some additional information on the characters.
    * https://docs.lootlocker.io/game-api/#character-loadouts
    *
    * @param OnGetCharacterLoadoutRequestCompleted Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted);

    /**
     * This endpoint lets you set a character as default, and set the name of the character.
     * https://docs.lootlocker.io/game-api/#update-character
     *
     * @param CharacterId Id of the character to make the update for
     * @param IsDefault Should the character be set as default
     * @param Name The name to set for the character
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void UpdateCharacter(int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest);

    /**
     * Create a character of the specified character type with the given name
     * If IsDefault is set to true, the new character will be made the default character.
     * See List Character Types to get your games Character Types.
     * https://docs.lootlocker.io/game-api/#create-character
     *
     * @param IsDefault If this should be set as the default character.
     * @param CharacterName The name of the character.
     * @param CharacterTypeId The ID of the character type.
     * @param OnCompletedRequestBP Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void CreateCharacter(bool IsDefault,  FString CharacterName,  FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP);

    /**
     * Call this endpoint to list the character types configured for your game.
     * https://docs.lootlocker.io/game-api/#list-character-types
     *
     * @param OnCompletedRequestBP Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP);

    /**
     * Equip an asset to the default character.
     * https://docs.lootlocker.io/game-api/#equip-asset-to-default-character
     *
     * @param InstanceId The asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnEquipAssetToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void EquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted);

    /**
    * Equip an asset to the specified character.
    * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
    *
    * @param CharacterId ID of the character to equip an asset to.
    * @param AssetId the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId the asset_variation_id.
    * @param OnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

    /**
     * Equip an asset to the specified character.
     * https://docs.lootlocker.io/game-api/#equip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to equip an asset to.
     * @param InstanceId the asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void EquipAssetToCharacterByIdAndInstance(int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

    /**
     * Unequip an asset from the default character.
     * https://docs.lootlocker.io/game-api/#unequip-asset-to-default-character
     *
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnUnEquipAssetToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted);

    /**
     * Unequip an asset from the specified character.
     * https://docs.lootlocker.io/game-api/#unequip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to unequip an asset from.
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnUnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted);


    /**
     * Getting the current loadout will return an array of assets that the user currently has equipped.
     * https://docs.lootlocker.io/game-api/#get-current-loadout-to-default-character
     *
     * @param OnGetCurrentLoadoutToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);

    /**
     * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
     * https://docs.lootlocker.io/game-api/#get-other-players-loadout-to-default-character
     *
     * @param OtherPlayerId other player's ID on the requested platform.
     * @param OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted Delegate for handling the server response.
     * @param OtherPlayerPlatform Optional: the platform the id refers to if different than the current platform
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform = FString(TEXT("")));

    /**
     * Get the contexts that the player's default character can equip.
     * https://docs.lootlocker.io/game-api/#get-equippable-contexts-to-default-character
     *
     * @param OnGetEquipableContextsToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted);

    /**
     * Get the contexts that the specified player's default character can equip.
     * https://docs.lootlocker.io/game-api/#get-equippable-contexts-by-character-id
     *
     * @param OtherCharacterId other player's ID.
     * @param OnGetEquipableContextsByCharacterIdRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters")
    static void GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted);

    //==================================================
    // Character Progressions
    //==================================================

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the character progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "Count,After", Count = -1, After = ""))
    static void GetCharacterProgressions(const int32& CharacterId, const int32 Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest);
    
    /**
    * Returns a single progression the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions")
    static void GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest);

    /**
    * Adds points to the specified character progression.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions")
    static void AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Subtracts points from the specified character progression.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions")
    static void SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Resets the specified character progression.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions")
    static void ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to delete
    * @param OnCompletedRequest Action for handling the response of type FLootLockerResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions")
    static void DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest);

    //==================================================
    //Persistent Storage
    // https://ref.lootlocker.com/game-api/#persistent-player-storage
    //==================================================

    /**
     * This call returns all key/value pairs on record for the current player, beware that it may be a lot of data.
     * https://docs.lootlocker.io/game-api/#get-entire-persistent-storage
     *
     * @param OnPersistentStorageItemsRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted);

    /**
     * Get Key/Value pair from the player's persistent storage.
     * https://docs.lootlocker.io/game-api/#get-a-single-key-from-persistent-storage
     *
     * @param Key Key of the key/value pair.
     * @param OnPersistentStorageItemRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted);

    /**
     * Create/Update key/value pair(s).
     * https://docs.lootlocker.io/game-api/#updating-creating-key-value-pairs
     *
     * @param Items array of items to be created/updated.
     * @param OnPersistentStorageItemsAddRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void AddItemsToPersistentStorage(FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted);

    /**
     * Create/Update a key/value pair.
     * https://docs.lootlocker.io/game-api/#updating-creating-key-value-pairs
     *
     * @param Item item to be created/updated.
     * @param OnPersistentStorageItemAddRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void AddItemToPersistentStorage(FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted);

    /**
     * Delete a key/value pair.
     * https://docs.lootlocker.io/game-api/#deleting-a-key-value-pair
     *
     * @param Key key of a key/value pair.
     * @param OnPersistentStorageItemDeleteRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted);

    /**
     * Read another players public key/value storage.
     * https://docs.lootlocker.io/game-api/#getting-other-players-public-key-value-pairs
     *
     * @param PlayerId players id or their public UID.
     * @param OnGetPlayerPersistentStorageRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage")
    static void GetPlayerPersistentStorage(const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted);

    //==================================================
    //Assets
    //==================================================

    /**
     * Get all the contexts the game has.
     * https://docs.lootlocker.io/game-api/#getting-contexts
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetContexts(const FContextDelegateBP& OnGetContextsRequestCompleted);

    /**
     * Get all assets in a paginated form.
     * https://docs.lootlocker.io/game-api/#getting-asset-list
     *
     * @param OnGetAssetsRequestCompleted Delegate for handling the server response.
     * @param StartFromIndex Optional: Index of the item to start from, defaults to 0
     * @param ItemsCount Optional: Number of items to receive (50-200), defaults to 50
     * @param AssetFilter Optional: Filter to apply, defaults to None
     * @param Context Optional: Context filter to apply, defaults to 0
     * @param IncludeUGC Optional: Whether to include UGC Assets, defaults to false
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetAssets(const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, int Context = 0, bool IncludeUGC = false);

    /**
     * Retrieve only specific Assets by their ID's.
     * https://docs.lootlocker.io/game-api/#getting-assets-by-ids
     *
     * @param AssetIds Array of the asset ID's to be fetched.
     * @param OnGetAssetsByIdsRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted);

    /**
     * This call will return you all the default bones.
     * If a binding overrides anything on a bone, it will be returned along with the binding.
     * https://docs.lootlocker.io/game-api/#getting-asset-bone-information
     *
     * @param OnGetAssetBonesRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetAssetBones(const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted);

    /**
     * List the current players favourite assets.
     * https://docs.lootlocker.io/game-api/#listing-favourite-assets
     *
     * @param OnGetFavouriteAssetIndicesRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted);

    /**
     * Add an asset to the list of favourites.
     * https://docs.lootlocker.io/game-api/#adding-favourite-assets
     *
     * @param AssetId Asset ID to be added.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted);

    /**
     * Remove an asset from the list of favourites.
     * https://docs.lootlocker.io/game-api/#removing-favourite-assets
     *
     * @param AssetId asset ID to be removed.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
    static void RemoveAssetFromFavourites(int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted);

    /**
     * This call offers a paginated list of the games universal assets
     * https://docs.lootlocker.io/game-api/#get-universal-assets
     *
     * @param After Last universal id to start after.
     * @param ItemsCount Number of items to receive (50-200).
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets")
	static void GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegateBP &OnCompletedRequest);

    //==================================================
    //Asset Instances
    //==================================================

    /**
     * Get all key/value pairs for an asset instance.
     * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnGetAllKeyValuePairsForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted);

    /**
     * DEPRECATED
     * Get all key/value pairs for an asset instance.
     * https://docs.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated, Please use GetAllKeyValuePairsForAssetInstance"))
    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsToAnInstanceForAssetInstanceCompleted);

    /**
     * Get a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#getting-a-key-value-pair-by-id
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId ID of the key/value pair.
     * @param OnGetAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     * Create a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#creating-a-key-value-pair
     *
     * @param AssetInstanceId asset instance ID.
     * @param Item key/value pair.
     * @param OnCreateAKeyValuePairForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted);

    /**
     * Update key/value pairs for an asset instance.
     * https://docs.lootlocker.io/game-api/#updating-one-or-more-key-value-pairs
     *
     * @param AssetInstanceId asset instance ID.
     * @param Items key/value pairs.
     * @param OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);

    /**
     * Update a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#updating-a-key-value-pair-by-id
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
     * @param Item Struct FLootLockerAssetInstanceStorageItem
     * @param OnUpdateAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     * Delete a key/value pair for an asset instance.
     * https://docs.lootlocker.io/game-api/#delete-a-key-value-pair
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
     * @param OnDeleteAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     * Get the drop rates for a loot box asset instance.
     * https://docs.lootlocker.io/game-api/#inspect-a-loot-box
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnInspectLootBoxCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void InspectLootBox(int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted);

    /**
     * Open a loot box asset instance.
     * The loot box will be consumed and the contents will be added to the player's inventory.
     * https://docs.lootlocker.io/game-api/#open-a-loot-box
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnOpenLootBoxCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances")
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted);

    //==================================================
    //User Generated Content
    //==================================================

    /**
     * Create an asset candidate.
     * https://docs.lootlocker.io/game-api/#creating-an-asset-candidate
     *
     * @param AssetCandidateData asset candidate data.
     * @param OnCreateAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted);

    /**
     * Update an asset candidate.
     * https://docs.lootlocker.io/game-api/#updating-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param AssetCandidateData asset candidate data.
     * @param OnUpdateAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted);

    /**
     * Delete an asset candidate.
     * https://docs.lootlocker.io/game-api/#deleting-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnDeleteAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted);

    /**
     * Get all asset candidates.
     * https://docs.lootlocker.io/game-api/#listing-asset-candidates
     *
     * @param OnGetAllAssetCandidatesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted);

    /**
     * Get an asset candidate.
     * https://docs.lootlocker.io/game-api/#getting-a-single-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnGetAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted);

    /**
     * Add a file to an asset candidate.
     * https://docs.lootlocker.io/game-api/#adding-files-to-asset-candidates
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param FilePath full absolute path to a file.
     * @param FilePurpose purpose of the file.
     * @param OnAddFileToAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted);

    /**
     * Remove a file from an asset candidate.
     * https://docs.lootlocker.io/game-api/#removing-files-from-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param FileId ID of the file.
     * @param OnDeleteFileFromAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content")
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted);

    //==================================================
    // Progressions
    //==================================================

    /**
    * Returns multiple progressions.
    *
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "Count,After", Count = -1, After = ""))
    static void GetProgressions(const int32 Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest);

    /**
    * Returns the specified progression
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions")
    static void GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest);

    /**
    * Returns multiple progression tiers for the specified progression.
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta=(AdvancedDisplay="Count,After", Count=-1, After=-1))
    static void GetProgressionTiers(const FString& ProgressionKey, const int32 Count, const int32 After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest);

    //==================================================
    //Missions
    //==================================================

    /**
     * Get all missions.
     * https://docs.lootlocker.io/game-api/#getting-all-missions
     *
     * @param OnGetAllMissionsCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void GetAllMissions(const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted);

    /**
     * Get a mission.
     * https://docs.lootlocker.io/game-api/#getting-a-single-mission
     *
     * @param MissionId mission ID.
     * @param OnGetMissionCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void GetMission(int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted);

    /**
     * Start a mission.
     * https://docs.lootlocker.io/game-api/#starting-mission
     *
     * @param MissionId mission ID.
     * @param OnStartMissionCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void StartMission(int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted);

    /**
     * Finish a mission.
     * https://docs.lootlocker.io/game-api/#finishing-mission
     *
     * @param MissionId mission ID.
     * @param MissionData mission completion data.
     * @param OnFinishMissionCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions")
    static void FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted);

    //==================================================
    //Maps
    // https://ref.lootlocker.com/game-api/#maps
    //==================================================

    /**
     * Get maps data.
     * https://docs.lootlocker.io/game-api/#getting-all-maps
     *
     * @param OnGetMapsCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Maps")
    static void GetMaps(const FGetMapsResponseDelegateBP& OnGetMapsCompleted);

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
     * @param OnPurchaseAssetsCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsCompleted);

    /**
     * Platform-specific purchase call for Android.
     * https://docs.lootlocker.io/game-api/#android-in-app-purchases
     *
     * @param PurchaseData Data about the assets to be purchased.
     * @param OnPurchaseAssetsAndroidCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const  FPurchaseResponseDelegateBP& OnPurchaseAssetsAndroidCompleted);

    /**
     * Platform-specific purchase call for iOS.
     * https://docs.lootlocker.io/game-api/#ios-in-app-purchases
     *
     * @param PurchaseData data about the assets to be purchased.
     * @param OnPurchaseAssetsIOSCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnPurchaseAssetsIOSCompleted);

    /**
     * Get the status of an order.
     * If you get a response that is considered final, you should issue a call to the player inventory endpoint if you're in a context where the inventory might change.
     *  https://docs.lootlocker.io/game-api/#polling-order-status
     *
     * @param PurchaseId ID of the purchase order.
     * @param OnPollingStatusCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static  void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnPollingStatusCompleted);

    /**
     * Activates specified rental asset
     * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player.
     * https://docs.lootlocker.io/game-api/#activating-a-rental-asset
     *
     * @param AssetId ID of the asset.
     * @param OnActivateRentalAssetCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted);

    /**
     * Get details on an order, like what products it contains as well as the order status.
     * https://ref.lootlocker.com/game-api/#get-order-details
     *
     * @param OrderId ID of the order.
     * @param NoProducts Set to true if you do not want products in the order returned in the response.
     * @param OnCompleteBP Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases")
    static void GetOrderDetails(int32 OrderId, const bool NoProducts, const FOrderStatusDetailsBP& OnCompleteBP);

    //==================================================
    //Trigger Events
    // https://ref.lootlocker.com/game-api/#trigger-events
    //==================================================

    /**
     * Trigger an event.
     * https://docs.lootlocker.io/game-api/#triggering-an-event
     *
     * @param Event data of the event to be triggered.
     * @param OnTriggerEventCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    static void TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnTriggerEventCompleted);

    /**
     * This endpoint lists the triggers that a player have already completed.
     * https://docs.lootlocker.io/game-api/#listing-triggered-trigger-events
     *
     * @param OnGetTriggeredEventsCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Trigger Events")
    static void GetTriggeredEvents(const FTriggersResponseDelegateBP& OnGetTriggeredEventsCompleted);

    //==================================================
    //Collectables
    // https://ref.lootlocker.com/game-api/#collectables
    //==================================================

    /**
     * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
     * https://docs.lootlocker.io/game-api/#getting-collectables
     *
     * @param OnGetAllCollectablesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    static void GetAllCollectables(const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted);

    /**
     * Collect an item.
     * https://docs.lootlocker.io/game-api/#collecting-an-item
     *
     * @param Item The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
     * @param OnCollectItemCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables")
    static void CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted);

    //==================================================
    //Messages
    // https://ref.lootlocker.com/game-api/#messages
    //==================================================

    /**
     * Get all messages for a player.
     * https://docs.lootlocker.io/game-api/#get-messages
     *
     * @param OnGetMessagesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Messages")
    static void GetMessages(const FMessagesResponseDelegateBP& OnGetMessagesCompleted);

    //==================================================
    //Leaderboard
    // https://ref.lootlocker.com/game-api/#leaderboards
    //==================================================

    /**
     * Get rank for single member for a leaderboard. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-member-rank
     *
     * @param LeaderboardKey the key of the leaderboard you want to connect to.
     * @param MemberId the id of player in the leaderboard
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP);

    /**
     * Get all leaderboards with member information on the ones the member is on, with rank and score, as well as player information if the leaderboard is of type player.
     * If metadata is enabled for the leaderboard, that will be returned in the response.
     * https://ref.lootlocker.com/game-api/#get-all-member-ranks
     *
     * @param MemberId player_id if player type leaderboard, otherwise id used when submitting the score
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP);

    /**
     * Get rank for a set of members for a leaderboard. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-by-list-of-members
     *
     * @param Members The ids of all leaderboard members you want to get info on.
     * @param LeaderboardKey the key of the leaderboard you want to connect to.
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP);

    /**
     * Get list of members in rank range.
     * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-score-list
     *
     * @param LeaderboardKey the key of the leaderboard you want to connect to.
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP);

    /**
     * Get list of members in rank range.
     * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-score-list
     *
     * @param LeaderboardKey the key of the leaderboard you need to connect to.
     * @param Count Number of members returned per page
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP);

    /**
     * Submit score for member on leaderboard.
     * https://ref.lootlocker.com/game-api/#submit-score
     *
     * @param MemberId The id of player in the leaderboard.
     * @param LeaderboardKey The key of the leaderboard you need to connect to.
     * @param Score The score to be submitted.
     * @param Metadata Metadata for the score, will be used if metadata is enabled for the leaderboard
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard")
    static void SubmitScore(FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP);

    //==================================================
    //Drop Table
    // https://ref.lootlocker.com/game-api/#drop-tables
    //==================================================

    /**
     * Compute and lock the specified drop table.
     * When you wish to evaluate a drop table and lock the drops from it in place, you call this method.
     * The response will hold information on the assets that are dropped, and can be picked up using the Pick endpoint.
     * https://ref.lootlocker.com/game-api/#compute-and-lock-drop-table
     *
     * @param TableId Drop table ID
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable")
    static void ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP);

    /**
     * Picks drops from a locked drop table.
     * https://ref.lootlocker.com/game-api/#pick-drops-from-drop-table
     *
     * @param Picks List of the item IDs you want to pick. Submit empty list for no picks
     * @param TableId Drop table ID, needs to have been locked prior to this call
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable")
    static void PickDropsFromDropTable(TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP);

    //==================================================
    // Miscellaneous
    //==================================================

    /**
    * Get the current time of the server. Can also be used to ping the server
    * https://ref.lootlocker.com/game-api/#server-time
    *
    * @param OnCompletedRequestBP Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous")
    static void GetServerTime(const FTimeResponseDelegateBP& OnCompletedRequestBP);
};
