// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"
#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "GameAPI/LootLockerDropTablesRequestHandler.h"
#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardArchiveRequestHandler.h"
#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "GameAPI/LootLockerPurchasesRequestHandler.h"
#include "GameAPI/LootLockerRemoteSessionRequestHandler.h"
#include "GameAPI/LootLockerTriggerEventsRequestHandler.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
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
     * Start a session for a Playstation Network user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param PsnOnlineId The PSN Online ID of the player
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Start a session for an Android user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param DeviceId The device id of the player
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartAndroidSession(const FString& DeviceId, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Start a session for a Amazon Luna user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param AmazonLunaGuid The Amazon Luna GUID of the player
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartAmazonLunaSession(const FString& AmazonLunaGuid, const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Verify a Steam user and then start a session for that user
     * You can optionally specify a steam app id if you have multiple ones for your game and have configured this in the LootLocker console
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param SteamId64 The Steam 64 bit Id as an FString
     * @param PlatformToken Platform-specific token.
     * @param OnCompletedRequest Delegate for handling the server response.
     * @param SteamAppId (Optional) The specific Steam App Id to verify the player for
     */
    static void VerifyPlayerAndStartSteamSession(const FString& SteamId64, const FString& PlatformToken, const FLootLockerSessionResponse& OnCompletedRequest, const int SteamAppId = -1);

    /**
     * Start a session for a Steam user
     * Note: Steam requires that you verify the player before starting a steam session. See the method VerifyPlayer
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.io/game-api/#authentication-request
     *
     * @param SteamId64 The Steam 64 bit Id as an FString
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartSteamSession(const FString& SteamId64, const FLootLockerSessionResponse& OnCompletedRequest);

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
     * Start a session for a Google user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.io/game-api/#sign-in-with-google
     *
     * @param IdToken The Id Token from your Google Sign In
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartGoogleSession(const FString& IdToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest);

    /**
     * Start a session for a Google user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The desired Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.io/game-api/#sign-in-with-google
     *
     * @param IdToken The Id Token from your Google Sign In
     * @param Platform Google OAuth2 ClientID platform
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest);

    /**
     * Refresh a previous session signed in with Google
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-google
     *
     * @param OnCompletedRequest Delegate for handling the response
     */
    static void RefreshGoogleSession(const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest) { RefreshGoogleSession("", OnCompletedRequest); };

    /**
     * Refresh a previous session signed in with Google
     * If you do not want to manually handle the refresh token we recommend using the RefreshGoogleSession(const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest) method.
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-google
     *
     * @param RefreshToken Token received in response from StartGoogleSession request
     * @param OnCompletedRequest Delegate for handling the response
     */
    static void RefreshGoogleSession(const FString& RefreshToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest);

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
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAppleSessionResponse
     */
    static void RefreshAppleSession(const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest) { RefreshAppleSession("", OnCompletedRequest); };

    /**
     * Refresh a previous session signed in with Apple
     * If you do not want to manually handle the refresh token we recommend using the RefreshAppleSession(const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest) method.
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Apple sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-apple
     *
     * @param RefreshToken Token received in response from StartAppleSession request
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAppleSessionResponse
     */
    static void RefreshAppleSession(const FString& RefreshToken, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest);

    /**
    * Create a new session for Sign in with Apple Game Center
    * The Apple sign in platform must be enabled in the web console for this to work.
    * https://ref.lootlocker.com/game-api/#sign-in-with-apple-game-center
    *
    * @param BundleId the Apple Game Center bundle id of your app
    * @param PlayerId the user's player id in Apple Game Center
    * @param PublicKeyUrl The url of the public key generated from Apple Game Center Identity Verification
    * @param Signature the signature generated from Apple Game Center Identity Verification
    * @param Salt the salt of the signature generated from Apple Game Center Identity Verification
    * @param Timestamp the timestamp of the verification generated from Apple Game Center Identity Verification
    * @param OnStartedAppleGameCenterSessionCompleted Delegate for handling the response of type  for handling the response of type FLootLockerAppleGameCenterSessionResponse
    */
    static void StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted);

    /**
    * Refresh a previous session signed in with Apple Game Center
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
    * The Apple sign in platform must be enabled in the web console for this to work.
    * https://ref.lootlocker.com/game-api/#sign-in-with-apple-game-center
    *
    * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAppleSessionResponse
    */
    static void RefreshAppleGameCenterSession(const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest) { RefreshAppleGameCenterSession("", OnCompletedRequest); };

    /**
    * Refresh a previous session signed in with Apple Game Center
    * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
    * The Apple sign in platform must be enabled in the web console for this to work.
    * https://ref.lootlocker.com/game-api/#sign-in-with-apple-game-center
    *
    * @param RefreshToken (Optional) Token received in response from StartAppleSession request. If not supplied we will attempt to resolve it from stored player data.
    * @param OnRefreshAppleGameCenterSessionCompleted Delegate for handling the response of type FLootLockerAppleGameCenterResponse
    */
    static void RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseDelegate& OnRefreshAppleGameCenterSessionCompleted);


    /**
     * Start a session for an Epic Online Services (EOS) user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The Epic sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.io/game-api/#sign-in-with-epic
     *
     * @param IdToken The Id Token from your Epic Sign In
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartEpicSession(const FString& IdToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest);

    /**
     * Refresh a previous session signed in with an Epic Online Services (EOS) user
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Epic sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-epic
     *
     * @param OnCompletedRequest Delegate for handling the response
     */
    static void RefreshEpicSession(const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest) { RefreshEpicSession("", OnCompletedRequest); };

    /**
     * Refresh a previous session signed in with an Epic Online Services (EOS) user
     * If you do not want to manually handle the refresh token we recommend using the RefreshEpicSession(const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest) method.
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Epic sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-epic
     *
     * @param RefreshToken Token received in response from StartEpicSession request
     * @param OnCompletedRequest Delegate for handling the response
     */
    static void RefreshEpicSession(const FString& RefreshToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest);

    /**
     * Start a session for an Meta / Oculus user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The Meta platform must be enabled in the web console for this to work.
     *
     * @param UserId The id recieved from Oculus
     * @param Nonce The nonce recieved from Oculus
     * @param OncompletedRequest Delegate for handling the server response.
     */
    static void StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseDelegate& OncompletedRequest);

    /**
     * Refresh a previous session signed in with Meta
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Meta platform must be enabled in the web console for this to work.
     *
     * @param OncompletedRequest Delegate for handling the response
     */
    static void RefreshMetaSession(const FLootLockerMetaSessionResponseDelegate& OncompletedRequest) { RefreshMetaSession("", OncompletedRequest); };
    
    /**
     * Refresh a previous session signed in with Meta
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Meta platform must be enabled in the web console for this to work.
     *
     * @param RefreshToken (Optional) Token received in response from StartMetaSession request. If not supplied we will attempt to resolve it from stored player data.
     * @param OncompletedRequest Delegate for handling the response
     */
    static void RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseDelegate& OncompletedRequest);

    /**
     * Start a guest session with an identifier, you can use something like a unique device identifier to tie the account to a device.
     * https://ref.lootlocker.com/game-api/#guest-login
     *
     * @param PlayerIdentifier Optional: Identifier for the player. Needs to be unique for each player, so only set this explicitly if you want to set a specific name for the guest player. Otherwise, an id will be generated for the player.
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
    static void GuestLogin(const FLootLockerSessionResponse& OnCompletedRequest, const FString& PlayerIdentifier = "");

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
    static void VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& Platform = FString(TEXT("")));

    /**
     * End active session (if any exists)
     * Terminates the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthorized error.
     * Succeeds if a session was ended or no sessions were active
     * https://ref.lootlocker.io/game-api/#ending-a-session
     *
     * @param OnCompletedRequest Delegate for handling the response of type LootLockerSessionResponse
     */
    static void EndSession(const FLootLockerDefaultDelegate& OnCompletedRequest);

    //==================================================
    // Connected Accounts
    //==================================================
    /**
     * List identity providers (like Apple, Google, etc.) that are connected to the currently logged in account
     *
     * @param OnComplete Delegate for handling the response
     */
    static void ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseDelegate& OnComplete);

    /**
     * Disconnect account from the currently logged in account
     *
     * Use this to disconnect an account (like a Google or Apple account) that can be used to start sessions for this LootLocker account so that it is no longer allowed to do that
     *
     * @param AccountToDisconnect What account to disconnect from this LootLocker Account
     * @param OnComplete Delegate for handling the response
     */
    static void DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete);

    /**
     * Connect a Google Account to the currently logged in LootLocker account allowing that google account to start sessions for this player
     *
     * @param IdToken The Id Token from google sign in
     * @param OnComplete Delegate for handling the response
     */
    static void ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete);

    /**
     * Connect a Google Account (with a Google Platform specified) to the currently logged in LootLocker account allowing that google account to start sessions for this player
     *
     * @param IdToken The Id Token from google sign in
     * @param Platform Google OAuth2 ClientID platform
     * @param OnComplete Delegate for handling the response
     */
    static void ConnectGoogleAccount(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete);

    /**
     * Connect an Apple Account (authorized by Rest Sign In) to the currently logged in LootLocker account allowing that google account to start sessions for this player
     *
     * @param AuthorizationCode Authorization code, provided by apple during Sign In
     * @param OnComplete Delegate for handling the response
     */
    static void ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete);

    //==================================================
    // Remote Sessions
    //==================================================

    /**
     * Start a remote session
     * If you want to let your local user sign in using another device then you use this method. First you will get the lease information needed to allow a secondary device to authenticate.
     * While the process is ongoing, the remoteSessionLeaseStatusUpdate action (if one is provided) will be invoked intermittently (about once a second) to update you on the status of the process.
     * When the process has come to an end (whether successfully or not), the onComplete action will be invoked with the updated information.
     *
     * @param RemoteSessionLeaseInformation Will be invoked once to provide the lease information that the secondary device can use to authenticate
     * @param RemoteSessionLeaseStatusUpdate Will be invoked intermittently to update the status lease process
     * @param OnComplete Invoked when the remote session process has run to completion containing either a valid session or information on why the process failed
     * @param PollingIntervalSeconds Optional: How often to poll the status of the remote session process
     * @param TimeOutAfterMinutes Optional: How long to allow the process to take in it's entirety
     */
    static FString StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegate& OnComplete, float PollingIntervalSeconds = 1.0f, float TimeOutAfterMinutes = 5.0f);

    /**
     * Cancel an ongoing remote session process
     *
     * @param ProcessID The id of the remote session process that you want to cancel
     */
    static void CancelRemoteSessionProcess(const FString& ProcessID);

    /**
     * Refresh a previous session signed in remotely
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     *
     * @param OnCompletedRequest Delegate for handling the response
     */
    static void RefreshRemoteSession(const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest) { RefreshRemoteSession("", OnCompletedRequest); };

    /**
     * Refresh a previous session signed in remotely
     * If you do not want to manually handle the refresh token we recommend using the RefreshRemoteSession(const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest) method.
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     *
     * @param RefreshToken Token received in response from StartRemoteSession request
     * @param OnCompletedRequest Delegate for handling the response
     */
    static void RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest);

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
     * Note: Use WhiteLabelLoginAndStartSession unless there's a specific purpose to use this method instead.
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
     * Note: Use WhiteLabelLoginAndStartSession unless there's a specific purpose to use this method instead.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#white-label-authentication
     *
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerAuthenticationResponse
     */
	static void WhiteLabelStartSession(const FLootLockerSessionResponse& OnCompletedRequest);

    /**
     * Login and Start a LootLocker Session using a White Label account
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#white-label-authentication
     *
     * @param Email - The Email for the white label account
     * @param Password - The Password for the white label account
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerWhiteLabelLoginAndSessionResponse
     * @param Remember - Optional flag to prolong the session lifetime
     */
    static void WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& OnCompletedRequest, const bool Remember = false);

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
     * Request verify account email for the user.
     * White Label platform must be enabled in the web console for this to work.
     * Account verification must also be enabled.
     * https://ref.lootlocker.com/game-api/#request-user-verification
     *
     * @param Email The Email for the white label user
     * @param OnCompletedRequest Delegate for handling the response of type FLootLockerResponse
     */
    static void WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest);

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
    * https://ref.lootlocker.io/game-api/#get-inventory-list
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
    * https://ref.lootlocker.io/game-api/#get-other-players-xp-and-level
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
    * @param Request Object specifying what ids to lookup
    * @param OnCompletedRequest Delegate to be invoked with the server response.
    */
	static void GetMultiplePlayersXp(FLootLockerMultiplePlayersXpRequest& Request, const FPMultiplePlayersXP& OnCompletedRequest);

    /**
    * Get assets that have been granted to the player since the last time this endpoint was called.
    * https://ref.lootlocker.io/game-api/#player-asset-notifications
    *
    * @param OnCompletedRequest Delegate to be invoked with the server response.
    */
	static void CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest);

    /**
    * This endpoint will return the amount of credits the current player have on their account.
    * https://ref.lootlocker.io/game-api/#get-currency-balance
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
    * https://ref.lootlocker.io/game-api/#get-dlcs-migrated
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void GetDLCsMigration(const FPDlcResponse& OnCompletedRequest);

    /**
    * This endpoint will set the players profile to private. This means that their
    * inventory will not be displayed publicly on Steam and other places.
    * https://ref.lootlocker.io/game-api/#set-profile-private
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void SetProfilePrivate(const FResponseCallback& OnCompletedRequest);

    /**
    * This endpoint will set the players profile to public. This means that their inventory will be
    * displayed publicly on Steam and other places.
    * https://ref.lootlocker.io/game-api/#set-profile-public
    *
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void SetProfilePublic(const FResponseCallback& OnCompletedRequest);

	/**
	* This endpoint will set the players name.
	* https://ref.lootlocker.io/game-api/#set-profile-public
	*
	* @param Name String player name
	* @param OnCompletedRequest Delegate for handling the server response.
	*/
	static void SetPlayerName(FString Name, const FPNameResponse& OnCompletedRequest);

	/**
	* This endpoint will get the players name.
	* https://ref.lootlocker.io/game-api/#set-profile-public
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

    /**
    * This method will mark the player for deletion. After 30 days the player will be deleted from the system.
    * https://ref.lootlocker.com/game-api/#delete-player
    *
    * @param OnCompletedRequest Delegate for handling the the server response.
    */
    static void DeletePlayer(const FLootLockerDefaultDelegate& OnCompletedRequest);

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
     * Update the specified file with the supplied content. The file will be owned by the currently active player.
     * https://ref.lootlocker.com/game-api/#update-a-file
     *
     * @param FileId Id of the file, can be retrieved with ListFiles or when the file is uploaded
     * @param Request Request of type FLootLockerFileUpdateRequest.
     * @param OnComplete Delegate for handling the response
     */
    static void UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete);

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
    // Player Progressions
    //==================================================

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param Count Amount of entries to receive
    * @param After Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetPlayerProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param Count Amount of entries to receive
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetPlayerProgressions(const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetPlayerProgressions(const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete);

    /**
    * Returns a single progression the player is currently on.
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPlayerProgressionsResponse
    */
    static void GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete);

    /**
    * Adds points to the specified player progression.
    *
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    static void AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete);

    /**
    * Subtracts points from the specified player progression.
    *
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    static void SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete);

    /**
    * Resets the specified player progression.
    *
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    static void ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete);

    /**
    * Deletes the specified player progression.

    * @param ProgressionKey Key of the progression you want to reset
    * @param OnComplete onComplete Action for handling the response of type FLootLockerDeleteProgression
    */
    static void DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete);

    //==================================================
    //Asset Instance Progressions   
    //==================================================

    /**
    * Returns multiple progressions the asset instance is currently on.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param Count Amount of entries to receive
    * @param After Used for pagination, id of the instance progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnComplete onComplete Action for handling the response of type FLootLockerResponse
    */
    static void GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedInstanceProgressionsResponseDelegate());
    /**
    * Returns multiple progressions the instance is currently on.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param Count Amount of entries to receive
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedInstanceProgressionsResponse
   */
    static void GetInstanceProgressions(const int32 AssetInstanceId, const int32& Count, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions the instance is currently on.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedInstanceProgressionsResponse
    */
    static void GetInstanceProgressions(const int32 AssetInstanceId, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete);
    
    /**
    * Returns a single progression the instance is currently on.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnComplete onComplete Action for handling the response of type FLootLockerInstanceProgressionResponse
    */
    static void GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseDelegate& OnComplete = FLootLockerInstanceProgressionResponseDelegate());
 
    /**
    * Adds points to the specified instance progression.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnComplete onComplete Action for handling the response of type FLootLockerInstanceProgressionWithRewardsResponse
    */
    static void AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate());
  
    /**
    * Subtracts points from the specified instance progression.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnComplete onComplete Action for handling the response of type FLootLockerInstanceProgressionWithRewardsResponse
    */
    static void SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate());
  
    /**
    * Resets the specified instance progression.
    *    
    * @param AssetInstanceId Key of the progression you want
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnComplete onComplete Action for handling the response of type FLootLockerInstanceProgressionWithRewardsResponse
    */
    static void ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate());
  
    /**
    * Deletes the specified instance progression.
    *
    * @param AssetInstanceId Key of the progression you want
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnComplete onComplete Action for handling the response of type FLootLockerDeleteProgression
    */
    static void DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete = FLootLockerDeleteProgressionDelegate());


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
     * Create a hero for the current player with the supplied name from the game hero specified with the supplied hero id, asset variation id, and whether to set as default.
     * https://ref.lootlocker.com/game-api/#creating-a-hero
     *
     * @param Request Request specifying the hero id for the game hero to use for creation and the name of the hero to create, an asset variation id for this hero, and whether this hero should be the default
     * @param OnCompleteRequest Delegate for handling the response
     */
	static void CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroDelegate& OnCompleteRequest);

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
     * Equip the specified Global Asset (default variation) to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetID The id of the global asset to equip
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void AddGlobalAssetToHeroLoadout(const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest);
 
    /**
     * Equip the specified Global Asset Variation to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param HeroID Id of the hero
     * @param AssetID The id of the global asset to equip
     * @param AssetVariationID The variation id of the global asset to equip
     * @param OnCompletedRequest Delegate for handling the response
     */
	static void AddGlobalAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate& OnCompletedRequest);

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
     * https://ref.lootlocker.io/game-api/#character-loadouts
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * This endpoint lets you set a character as default, and set the name of the character.
     * https://ref.lootlocker.io/game-api/#update-character
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
     * https://ref.lootlocker.io/game-api/#create-character
     *
     * @param IsDefault If this should be set as the default character.
     * @param CharacterName The name of the character.
     * @param CharacterTypeId The ID of the character type.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterTypeId,  const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * Call this endpoint to list the character types configured for your game.
     * https://ref.lootlocker.io/game-api/#list-character-types
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest);


    /**
     * Equip an asset to the default character.
     * https://ref.lootlocker.io/game-api/#equip-asset-to-default-character
     *
     * @param InstanceId The asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Equip an asset to the specified character.
     * https://ref.lootlocker.io/game-api/#equip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to equip an asset to.
     * @param AssetId the asset's instance_id that is returned from the inventory and loadout calls.
     * @param AssetVariationId the asset_variation_id.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Equip an asset to the specified character.
     * https://ref.lootlocker.io/game-api/#equip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to equip an asset to.
     * @param InstanceId the asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void EquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Unequip an asset from the default character.
     * https://ref.lootlocker.io/game-api/#unequip-asset-to-default-character
     *
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Unequip an asset from the specified character.
     * https://ref.lootlocker.io/game-api/#unequip-asset-to-character-by-id
     *
     * @param CharacterId ID of the character to unequip an asset from.
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest);

    /**
     * Getting the current loadout will return an array of assets that the user currently has equipped.
     * https://ref.lootlocker.io/game-api/#get-current-loadout-to-default-character
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest);

    /**
     * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
     * https://ref.lootlocker.io/game-api/#get-other-players-loadout-to-default-character
     *
     * @param OtherPlayerId other player's ID on the requested platform.
     * @param OnCompletedRequest Delegate for handling the server response.
     * @param OtherPlayerPlatform Optional: the platform the id refers to if different than the current platform
     */
	static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& OtherPlayerPlatform = FString(TEXT("")));

    /**
     * Get the contexts that the player's default character can equip.
     * https://ref.lootlocker.io/game-api/#get-equippable-contexts-to-default-character
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest);

    /**
     * Get the contexts that the specified player's default character can equip.
     * https://ref.lootlocker.io/game-api/#get-equippable-contexts-by-character-id
     *
     * @param OtherCharacterId other player's ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
	static void GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate& OnCompletedRequest);

    /**
    * Get list of Characters to a player
    * https://ref.lootlocker.com/game-api/#list-player-characters
    */
    static void ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponse& OnCompletedRequest);


    //==================================================
    // Character Progressions
    //==================================================

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param Count Amount of entries to receive
    * @param After Used for pagination, id of the character progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param Count Amount of entries to receive
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedCharacterProgressionsResponse
    */
    static void GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedCharacterProgressionsResponse
    */
    static void GetCharacterProgressions(const int32& CharacterId, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete);

    /**
    * Returns a single progression the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnComplete onComplete Action for handling the response of type FLootLockerCharacterProgressionsResponse
    */
    static void GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseDelegate& OnComplete);

    /**
    * Adds points to the specified character progression.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnComplete onComplete Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    static void AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete);

    /**
    * Subtracts points from the specified character progression.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnComplete onComplete Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    static void SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete);

    /**
    * Resets the specified character progression.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnComplete onComplete Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    static void ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to delete
    * @param OnComplete onComplete Action for handling the response of type FLootLockerResponse
    */
    static void DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete);

    //==================================================
    //Persistent Storage
    // https://ref.lootlocker.com/game-api/#persistent-player-storage
    //==================================================

    /**
     * This call returns all key/value pairs on record for the current player, beware that it may be a lot of data.
     * https://ref.lootlocker.io/game-api/#get-entire-persistent-storage
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Get Key/Value pair from the player's persistent storage.
     * https://ref.lootlocker.io/game-api/#get-a-single-key-from-persistent-storage
     *
     * @param Key Key of the key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Create/Update key/value pair(s).
     * https://ref.lootlocker.io/game-api/#updating-creating-key-value-pairs
     *
     * @param Items array of items to be created/updated.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Create/Update a key/value pair.
     * https://ref.lootlocker.io/game-api/#updating-creating-key-value-pairs
     *
     * @param Item item to be created/updated.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddItemsToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Delete a key/value pair.
     * https://ref.lootlocker.io/game-api/#deleting-a-key-value-pair
     *
     * @param Key key of a key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Read another players public key/value storage.
     * https://ref.lootlocker.io/game-api/#getting-other-players-public-key-value-pairs
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
     * https://ref.lootlocker.io/game-api/#getting-contexts
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetContexts(const FContextDelegate& OnCompletedRequest);

    /**
     * Get all assets in a paginated form.
     * https://ref.lootlocker.io/game-api/#getting-asset-list
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
	 * https://ref.lootlocker.io/game-api/#get-universal-assets
	 *
	 * @param After Last universal id to start after.
	 * @param ItemsCount Number of items to receive (50-200).
	 * @param OnCompletedRequest Delegate for handling the server response.
	 */
	static void GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegate &OnCompletedRequest);

    /**
     * Retrieve only specific Assets by their ID's.
     * https://ref.lootlocker.io/game-api/#getting-assets-by-ids
     *
     * @param AssetIds Array of the asset ID's to be fetched.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest);

    /**
     * This call will return you all the default bones.
     * If a binding overrides anything on a bone, it will be returned along with the binding.
     * https://ref.lootlocker.io/game-api/#getting-asset-bone-information
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest);

    /**
     * List the current players favourite assets.
     * https://ref.lootlocker.io/game-api/#listing-favourite-assets
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);

    /**
     * Add an asset to the list of favourites.
     * https://ref.lootlocker.io/game-api/#adding-favourite-assets
     *
     * @param AssetId Asset ID to be added.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);

    /**
     * Remove an asset from the list of favourites.
     * https://ref.lootlocker.io/game-api/#removing-favourite-assets
     *
     * @param AssetId asset ID to be removed.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest);

    /**
    * Grant an asset to the current Player.
    * https://ref.lootlocker.com/game-api/#grant-an-asset-to-the-player
    *
    * @param AssetID ID of the asset to be granted
    * @param AssetVariationID The ID of the Asset Variation you want to grant
    * @param AssetRentalOptionID The ID of the rental option you want to grant
    */
    static void GrantAssetToPlayerInventory(const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegate& OnCompletedRequest);

    /**
    * Grant an asset to the current Player.
    * https://ref.lootlocker.com/game-api/#grant-an-asset-to-the-player
    *
    * @param AssetID ID of the asset to be granted
    * @param AssetVariationID The ID of the Asset Variation you want to grant
    * @param AssetRentalOptionID The ID of the rental option you want to grant
    */
    static void GrantAssetToPlayerInventory(const int AssetID, const FGrantAssetResponseDelegate& OnCompletedRequest) {
        GrantAssetToPlayerInventory(AssetID, 0, 0, OnCompletedRequest);
    }


    //==================================================
    //Asset Instances
    // https://ref.lootlocker.com/game-api/#asset-instances
    //==================================================

    /**
     * Get all key/value pairs for an asset instance.
     * https://ref.lootlocker.io/game-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Get a key/value pair for an asset instance.
     * https://ref.lootlocker.io/game-api/#getting-a-key-value-pair-by-id
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId ID of the key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Create a key/value pair for an asset instance.
     * https://ref.lootlocker.io/game-api/#creating-a-key-value-pair
     *
     * @param AssetInstanceId asset instance ID.
     * @param Item key/value pair.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Update key/value pairs for an asset instance.
     * https://ref.lootlocker.io/game-api/#updating-one-or-more-key-value-pairs
     *
     * @param AssetInstanceId asset instance ID.
     * @param Items key/value pairs.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Update a key/value pair for an asset instance.
     * https://ref.lootlocker.io/game-api/#updating-a-key-value-pair-by-id
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
	 * @param Item Struct FLootLockerAssetInstanceStorageItem
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest);

    /**
     * Delete a key/value pair for an asset instance.
     * https://ref.lootlocker.io/game-api/#delete-a-key-value-pair
     *
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest);

    /**
     * Get the drop rates for a loot box asset instance.
     * https://ref.lootlocker.io/game-api/#inspect-a-loot-box
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest);

    /**
     * Open a loot box asset instance.
     * The loot box will be consumed and the contents will be added to the player's inventory.
     * https://ref.lootlocker.io/game-api/#open-a-loot-box
     *
     * @param AssetInstanceId asset instance ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest);

    /**
    * Delete an Asset Instance permanently from the active Player's Inventory.
    *
    * @param AssetInstanceID asset instance ID.
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    static void DeleteAssetInstanceFromPlayerInventory(int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest);


    //==================================================
    //User Generated Content
    //==================================================

    /**
     * Create an asset candidate.
     * https://ref.lootlocker.io/game-api/#creating-an-asset-candidate
     *
     * @param AssetCandidateData asset candidate data.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest);

    /**
     * Update an asset candidate.
     * https://ref.lootlocker.io/game-api/#updating-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param AssetCandidateData asset candidate data.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    /**
     * Delete an asset candidate.
     * https://ref.lootlocker.io/game-api/#deleting-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest);

    /**
     * Get all asset candidates.
     * https://ref.lootlocker.io/game-api/#listing-asset-candidates
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest);

    /**
     * Get an asset candidate.
     * https://ref.lootlocker.io/game-api/#getting-a-single-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    /**
     * Add a file to an asset candidate.
     * https://ref.lootlocker.io/game-api/#adding-files-to-asset-candidates
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param FilePath full absolute path to a file.
     * @param FilePurpose purpose of the file.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest);

    /**
     * Remove a file from an asset candidate.
     * https://ref.lootlocker.io/game-api/#removing-files-from-an-asset-candidate
     *
     * @param AssetCandidateId ID of the asset candidate.
     * @param FileId ID of the file.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest);

    //==================================================
    // Progressions
    //==================================================

    /**
    * Returns multiple progressions.
    *
    * @param Count Amount of entries to receive
    * @param After Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions.
    *
    * @param Count Amount of entries to receive
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgressions(const int32& Count, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete);

    /**
    * Returns multiple progressions.
    *
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgressions(const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete);

    /**
    * Returns the specified progression
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseDelegate& OnComplete);

    /**
    * Returns multiple progression tiers for the specified progression.
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param Count Amount of entries to receive
    * @param After Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const int32& After, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete);

    /**
    * Returns multiple progression tiers for the specified progression.
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param Count Amount of entries to receive
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete);

    /**
    * Returns multiple progression tiers for the specified progression.
    *
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnComplete onComplete Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    static void GetProgressionTiers(const FString& ProgressionKey, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete);

    //==================================================
    //Missions
    //==================================================

    /**
     * Get all missions.
     * https://ref.lootlocker.io/game-api/#getting-all-missions
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest);

    /**
     * Get a mission.
     * https://ref.lootlocker.io/game-api/#getting-a-single-mission
     *
     * @param MissionId mission ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest);

    /**
     * Start a mission.
     * https://ref.lootlocker.io/game-api/#starting-mission
     *
     * @param MissionId mission ID.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest);

    /**
     * Finish a mission.
     * https://ref.lootlocker.io/game-api/#finishing-mission
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
     * https://ref.lootlocker.io/game-api/#getting-all-maps
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
     * https://ref.lootlocker.io/game-api/#purchase-call
     *
     * @param PurchaseData Data about the assets to be purchased.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    [[deprecated("This purchasing system has been replaced with our new IAP system and will be removed at a later stage. Read more here: https://docs.lootlocker.com/content/in-app-purchases")]]
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);

    /**
     * Platform-specific purchase call for Android.
     * https://ref.lootlocker.io/game-api/#android-in-app-purchases
     *
     * @param PurchaseData Data about the assets to be purchased.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    [[deprecated("This purchasing system has been replaced with our new IAP system and will be removed at a later stage. Read more here: https://docs.lootlocker.com/content/in-app-purchases")]]
    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);

    /**
     * Platform-specific purchase call for iOS.
     * https://ref.lootlocker.io/game-api/#ios-in-app-purchases
     *
     * @param PurchaseData data about the assets to be purchased.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    [[deprecated("This purchasing system has been replaced with our new IAP system and will be removed at a later stage. Read more here: https://docs.lootlocker.com/content/in-app-purchases")]]
    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest);

    /**
     * Get the status of an order.
     * If you get a response that is considered final, you should issue a call to the player inventory endpoint if you're in a context where the inventory might change.
     *  https://ref.lootlocker.io/game-api/#polling-order-status
     *
     * @param PurchaseId ID of the purchase order.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    [[deprecated("This purchasing system has been replaced with our new IAP system and will be removed at a later stage. Read more here: https://docs.lootlocker.com/content/in-app-purchases")]]
    static void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest);

    /**
     * Activates specified rental asset
     * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player.
     * https://ref.lootlocker.io/game-api/#activating-a-rental-asset
     *
     * @param AssetInstanceId ID of the asset.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest);

    /**
     * Get details on an order, like what products it contains as well as the order status.
     * https://ref.lootlocker.com/game-api/#get-order-details
     *
     * @param OrderId ID of the order.
     * @param NoProducts Set to true if you do not want products in the order returned in the response.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    [[deprecated("This purchasing system has been replaced with our new IAP system and will be removed at a later stage. Read more here: https://docs.lootlocker.com/content/in-app-purchases")]]
    static void GetOrderDetails(int32 OrderId, const bool NoProducts, const FOrderStatusDetailsDelegate& OnCompletedRequest);

    /**
     * Purchase one catalog item using a specified wallet
     *
     * @param WalletId The id of the wallet to use for the purchase
     * @param CatalogItemListingId The unique listing id of the catalog item to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void LootLockerPurchaseSingleCatalogItem(const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     * Purchase one or more catalog items using a specified wallet
     * 
     * @param WalletId The id of the wallet to use for the purchase
     * @param ItemsToPurchase A list of items to purchase along with the quantity of each item to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void LootLockerPurchaseCatalogItems(const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Apple App Store for the current player
     *
     * @param TransactionId The id of the transaction successfully made towards the Apple App Store
     * @param Sandboxed Optional: Should this redemption be made towards sandbox App Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void RedeemAppleAppStorePurchaseForPlayer(const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed = false);

    /**
     * Redeem a purchase that was made successfully towards the Apple App Store for a class that the current player owns
     *
     * @param TransactionId The id of the transaction successfully made towards the Apple App Store
     * @param ClassId The id of the class to redeem this transaction for
     * @param Sandboxed Optional: Should this redemption be made towards sandbox App Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString& TransactionId, const FLootLockerDefaultDelegate& OnCompletedRequest, bool Sandboxed = false);

    /**
     * Redeem a purchase that was made successfully towards the Google Play Store for the current player
     *
     * @param ProductId The id of the product that this redemption refers to
     * @param PurchaseToken The token from the purchase successfully made towards the Google Play Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void RedeemGooglePlayStorePurchaseForPlayer(const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Google Play Store for a class that the current player owns
     *
     * @param ClassId The id of the class to redeem this purchase for
     * @param ProductId The id of the product that this redemption refers to
     * @param PurchaseToken The token from the purchase successfully made towards the Google Play Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     * Begin a Steam purchase with the given settings that when finalized will redeem the specified catalog item
     *
     * Steam in-app purchases need to be configured for this to work
     * Steam in-app purchases works slightly different from other platforms, you begin a purchase with this call which initiates it in Steams backend
     * While your app is waiting for the user to finalize that purchase you can use QuerySteamPurchaseRedemptionStatus to get the status, when that tells you that the purchase is Approved you can finalize the purchase using FinalizeSteamPurchaseRedemption
     *
     * @param SteamId Id of the Steam User that is making the purchase
     * @param Currency The currency to use for the purchase
     * @param Language The language to use for the purchase
     * @param CatalogItemId The LootLocker Catalog Item Id for the item you wish to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void BeginSteamPurchaseRedemption(const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest);

    /**
     * Begin a Steam purchase with the given settings that when finalized will redeem the specified catalog item for the specified class
     *
     * Steam in-app purchases need to be configured for this to work
     * Steam in-app purchases works slightly different from other platforms, you begin a purchase with this call which initiates it in Steams backend
     * While your app is waiting for the user to finalize that purchase you can use QuerySteamPurchaseRedemptionStatus to get the status, when that tells you that the purchase is Approved you can finalize the purchase using FinalizeSteamPurchaseRedemption
     *
     * @param ClassId Id of the class to make the purchase for
     * @param SteamId Id of the Steam User that is making the purchase
     * @param Currency The currency to use for the purchase
     * @param Language The language to use for the purchase
     * @param CatalogItemId The LootLocker Catalog Item Id for the item you wish to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompletedRequest);

    /**
     * Check the Steam Purchase status for a given entitlement
     *
     * Use this to check the status of an ongoing purchase to know when it's ready to finalize or has been aborted
     * or use this to get information for a completed purchase
     *
     * @param EntitlementId The id of the entitlement to check the status for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void QuerySteamPurchaseRedemptionStatus(const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompletedRequest);

    /**
     * Finalize a started Steam Purchase and subsequently redeem the catalog items that the entitlement refers to
     *
     * The steam purchase needs to be in status Approved for this call to work
     *
     * @param EntitlementId The id of the entitlement to finalize the purchase for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void FinalizeSteamPurchaseRedemption(const FString& EntitlementId, const FLootLockerDefaultDelegate& OnCompletedRequest);


    //==================================================
    //Trigger Events
    // https://ref.lootlocker.com/game-api/#trigger-events
    //==================================================

    /**
     * Trigger an event.
     * https://ref.lootlocker.io/game-api/#triggering-an-event
     *
     * @param Event data of the event to be triggered.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest);

    /**
     * This endpoint lists the triggers that a player have already completed.
     * https://ref.lootlocker.io/game-api/#listing-triggered-trigger-events
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest);

    //==================================================
    //Collectables
    // https://ref.lootlocker.com/game-api/#collectables
    //==================================================

    /**
     * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
     * https://ref.lootlocker.io/game-api/#getting-collectables
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest);

    /**
     * Collect an item.
     * https://ref.lootlocker.io/game-api/#collecting-an-item
     *
     * @param Item The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest);

    //==================================================
    //Messages
    // https://ref.lootlocker.com/game-api/#messages
    //==================================================

    /**
     * Get all messages for a player.
     * https://ref.lootlocker.io/game-api/#get-messages
     *
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    static void GetMessages(const FMessagesResponseDelegate& OnCompletedRequest);

    //==================================================
    //Leaderboard
    // https://ref.lootlocker.com/game-api/#leaderboards
    //==================================================

    /**
     * Get rank for single member for a leaderboard. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-member-rank
     *
     * @param LeaderboardKey the key of the leaderboard you need to connect to.
     * @param MemberId the id of player in the leaderboard
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest);

    /**
     * Get rank for a set of members for a leaderboard. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-by-list-of-members
     *
     * @param Members The ids of all leaderboard members you want to get info on.
     * @param LeaderboardKey the key of the leaderboard you need to connect to.
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest);

    /**
     * Get list of members in rank range.
     * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-score-list
     *
     * @param LeaderboardKey the key of the leaderboard you need to connect to.
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest);

    /**
     * Get list of members in rank range.
     * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.io/game-api/#get-score-list
     *
     * @param LeaderboardKey the key of the leaderboard you need to connect to.
     * @param Count Number of members returned per page
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest);

    /**
     * Submit score for member on leaderboard.
     * https://ref.lootlocker.com/game-api/#submit-score
     *
     * @param MemberId The id of player in the leaderboard.
     * @param LeaderboardKey The key of the leaderboard you need to connect to.
     * @param Score The score to be submitted.
     * @param Metadata Metadata for the score, will be used if metadata is enabled for the leaderboard
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void SubmitScore(FString MemberId, const FString LeaderboardKey, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest);

    /**
     * Get all leaderboards with member information on the ones the member is on, with rank and score, as well as player information if the leaderboard is of type player.
     * If metadata is enabled for the leaderboard, that will be returned in the response.
     * https://ref.lootlocker.com/game-api/#get-all-member-ranks
     *
     * @param MemberId player_id if player type leaderboard, otherwise id used when submitting the score
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate& OnCompletedRequest);
    
    /**
    * List the archive of a specific Leaderboard,
    * @param LeaderboardKey the Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    static void ListLeaderboardArchive(const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate& OnCompletedRequest);
    
    /**
    * Get the specified Archive which includes details such as ranks, scores and rewards.
    * @param Key the Key of the Leaderboard you want the list of archives
    * @param Count Optional: the count of how many archive entries you want
    * @param After Optional: cursor for pagination
    * @param OnCompletedRequest Delegate for handling the server response
    */
    static void GetLeaderboardArchive(const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest);

    /**
    * Get the specified Archive which includes details such as ranks, scores and rewards.
    * @param Key the Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequest Delegate for handling the server response
    */
    static void GetLeaderboardArchive(const FString& Key, const FLootLockerLeaderboardArchiveDetailResponseDelegate& OnCompletedRequest) { GetLeaderboardArchive(Key, -1, "", OnCompletedRequest); }

    /**
    * Get details on a Leaderboard which contains the schedule, rewards and the details on rewards.
    * @param LeaderboardKey the Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequest Delegate for handling the server response
    */
    static void GetLeaderboardDetails(const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseDelegate& OnCompletedRequest);

    //==================================================
    // Drop Table
    // https://ref.lootlocker.com/game-api/#drop-tables
    //==================================================

    /**
     * Compute and lock the specified drop table.
     * When you wish to evaluate a drop table and lock the drops from it in place, you call this method.
     * The response will hold information on the assets that are dropped, and can be picked up using the Pick endpoint.
     * https://ref.lootlocker.com/game-api/#compute-and-lock-drop-table
     *
     * @param TableId Drop table ID
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void ComputeAndLockDropTable(const int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest);

    /**
     * Picks drops from a locked drop table.
     * https://ref.lootlocker.com/game-api/#pick-drops-from-drop-table
     *
     * @param Picks List of the item IDs you want to pick. Submit empty list for no picks
     * @param TableId Drop table ID, needs to have been locked prior to this call
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void PickDropsFromDropTable(const TArray<int> Picks, const int TableId,const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest);

    //==================================================
    // Currencies
    // https://ref.lootlocker.com/game-api/#currencies
    //==================================================

    /**
     * Get a list of available currencies for the game
     *
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void ListCurrencies(const FLootLockerListCurrenciesResponseDelegate& OnCompletedRequest);

    /**
     * Get a list of the denominations available for a specific currency
     *
     * @param CurrencyCode The code of the currency to fetch denominations for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    static void GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnCompletedRequest);

    //==================================================
    // Balances
    // https://ref.lootlocker.com/game-api/#balances
    //==================================================

    /**
     * Get a list of balances in a specified wallet
     *
     * @param WalletID Unique ID of the wallet to get balances for
     * @param OnComplete Delegate for handling the server response
     */
    static void ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete);

    /**
     * Get information about a specified wallet
     *
     * @param WalletID Unique ID of the wallet to get information for
     * @param OnComplete Delegate for handling the server response
     */
    static void GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete);

    /**
     * Get information about a wallet for a specified holder
     *
     * @param HolderULID ULID of the holder of the wallet you want to get information for
     * @param HolderType The type of the holder to get the wallet for
     * @param OnComplete Delegate for handling the server response
     */
    static void GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete);

    /**
     * Credit (increase) the specified amount of the provided currency to the provided wallet
     *
     * @param WalletID Unique ID of the wallet to credit the given amount of the given currency to
     * @param CurrencyID Unique ID of the currency to credit
     * @param Amount The amount of the given currency to credit to the given wallet
     * @param OnComplete Delegate for handling the server response
     */
    static void CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete);

    /**
     * Debit (decrease) the specified amount of the provided currency to the provided wallet
     *
     * @param WalletID Unique ID of the wallet to debit the given amount of the given currency from
     * @param CurrencyID Unique ID of the currency to debit
     * @param Amount The amount of the given currency to debit from the given wallet
     * @param OnComplete Delegate for handling the server response
     */
    static void DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete);

    //==================================================
    // Catalogs
    //==================================================
    /**
     * List the catalogs available for the game
     *
     * @param OnComplete Delegate for handling the server response
     */
    static void ListCatalogs(const FLootLockerListCatalogsResponseDelegate& OnComplete);

    /**
     * List the items available in a specific catalog
     *
     * @param CatalogKey Unique Key of the catalog that you want to get items for
     * @param Count Optional: Amount of catalog items to receive. Use null to get the default amount.
     * @param After Optional: Used for pagination, this is the cursor to start getting items from. Use null to get items from the beginning. Use the cursor from a previous call to get the next count of items in the list.
     * @param OnComplete Delegate for handling the server response
     */
    static void ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseDelegate& OnComplete);

    /**
     * List the items available in a specific catalog
     *
     * @param CatalogKey Unique Key of the catalog that you want to get items for
     * @param OnComplete Delegate for handling the server response
     */
    static void ListCatalogItems(const FString& CatalogKey, const FLootLockerListCatalogPricesResponseDelegate& OnComplete) { ListCatalogItems(CatalogKey, -1, "", OnComplete);  }

    //==================================================
    // Entitlements
    //==================================================

    /**
     * List this player's historical entitlements
     * Use this to retrieve information on entitlements the player has received regardless of their origin (for example as an effect of progression, purchases, or leaderboard rewards)
     *
     * @param Count Optional: Amount of entitlement listings to receive. Use null to get the default amount.
     * @param After Optional: Used for pagination, this is the cursor to start getting items from. Use null to get items from the beginning. Use the cursor from a previous call to get the next count of items in the list.
     * @param OnComplete Delegate for handling the server response
     */
    static void ListEntitlements(int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete);

    /**
     * List this player's historical entitlements
     * Use this to retrieve information on entitlements the player has received regardless of their origin (for example as an effect of progression, purchases, or leaderboard rewards)
     *
     * @param OnComplete Delegate for handling the server response
     */
    static void ListEntitlements(const FLootLockerListEntitlementsResponseDelegate& OnComplete) { ListEntitlements(-1, "", OnComplete); }
    
    /**
    * Get information of an entitlement
    * Use this to retrieve information on entitlements the player has received regardless of their origin (for example as an effect of progression, purchases, or leaderboard rewards) 
    *
    * @param EntitlementID: Is the identifying ID which the entitlement is connected to
    * @param OnCompelte delegate for handling the server response
    */
    static void GetEntitlement(const FString& EntitlementID, FLootLockerSingleEntitlementResponseDelegate& OnComplete);

    //==================================================
    //Feedback
    //==================================================

    /**
    * Get a list of Categories to use for feedback to players, like reporting or giving feedback such as nice notes
    * @param OnComplete delegate for handling the server response
    */
    static void ListPlayerFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete);

    /**
    * Get a list of Categories to use for feedback to the game, like reporting or giving feedback such as nice notes
    * @param OnComplete delegate for handling the server response
    */
    static void ListGameFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete);

    /**
    * Get a list of Categories to use for feedback to a ugc asset, like reporting or giving feedback such as nice notes
    * @param OnComplete delegate for handling the server response
    */
    static void ListUGCFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete);

    /**
    * Send feedback about a player
    * @param Ulid is the ulid of who you're giving feedback about
    * @param Description is the text/reason of your feedback ("He is hacking", "He is a kind player!")
    * @param CategoryID is the ID of the category you're using for your feedback, use ListFeedbackCategories function to get the ids.
    */
    static void SendPlayerFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete);

    /**
    * Send feedback about the game
    * @param Ulid is the ulid of who you're giving feedback about
    * @param Description is the text/reason of your feedback ("Amazing game", "I found a bug here!")
    * @param CategoryID is the ID of the category you're using for your feedback, use ListFeedbackCategories function to get the ids.
    */
    static void SendGameFeedback(const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete);

    /**
    * Send feedback about a ugc asset
    * @param Ulid is the ulid of the asset you're giving feedback about
    * @param Description is the text/reason of your feedback ("Amazing Level", "I found a bug here!")
    * @param CategoryID is the ID of the category you're using for your feedback, use ListFeedbackCategories function to get the ids.
    */
    static void SendUGCFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseDelegate& OnComplete);


	//==================================================
	//Miscellaneous
	//==================================================

	/**
	* Get the current time of the server. Can also be used to ping the server
	* https://ref.lootlocker.com/game-api/#server-time
	*
	* @param OnCompleted
    
    Delegate for handling the server response.
	*/
	static void GetServerTime(const FTimeResponseDelegate& OnCompletedRequest);

    /**
    * Get the last used platform from an earlier session.
    */
    static FString GetLastActivePlatform();
};
