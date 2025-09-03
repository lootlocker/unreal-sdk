// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
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
#include "GameAPI/LootLockerFollowersRequestHandler.h"
#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardArchiveRequestHandler.h"
#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "GameAPI/LootLockerPurchasesRequestHandler.h"
#include "GameAPI/LootLockerRemoteSessionRequestHandler.h"
#include "GameAPI/LootLockerTriggersRequestHandler.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "LootLockerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerManager : public UObject
{
    GENERATED_BODY()

public:

    //==================================================
    // Player State
    //==================================================
    /**
    Get a list of player ulids that have been active since game start (or state initialization)

    @returns Array of player ulids that are considered "active" since game start
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static TArray<FString> GetActivePlayerUlids();

    /**
    Make the state for the player with the specified ulid to be "inactive"

    @param PlayerUlid The ulid of the player to set to inactive
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static void SetPlayerUlidToInactive(const FString& PlayerUlid);

    /**
    Make the state for all currently active players to be "inactive"
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static void SetAllPlayersToInactive();

    /**
    Make the state for all currently active players except the specified player to be "inactive"

    @param PlayerUlid The ulid of the player to keep active
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static void SetAllPlayersToInactiveExceptForPlayer(const FString& PlayerUlid);

    /**
    Get a list of player ulids that there is a stored state for

    @returns Array of player ulids that there is a state stored for
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static TArray<FString> GetCachedPlayerUlids();

    /**
    Get the ulid of the player state that is used as the default state for calls with no other player specified

    @returns The Ulid of the "default" player (the player used for requests where no player is specified)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static FString GetDefaultPlayerUlid();

    /**
    Set the player state that is used as the default state for calls with no other player specified

    @param PlayerUlid The ulid of the player to set as default
    @returns If the operation was successful or not
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static bool SetDefaultPlayer(const FString& PlayerUlid);

    /**
    Get the player state for the player with the specified ulid
        or the default player state if the supplied player ulid is empty
        or an empty state if none of the previous are present

    @param PlayerUlid The ulid of the player to get state for
    @returns The player state that was retrieved for the specified player, or the default player, or an empty state if none of the previous are present
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static FLootLockerPlayerData GetSavedStateOrDefaultOrEmptyForPlayer(const FString& PlayerUlid);

    /**
    Remove stored state information for the specified player if present (player will need to re-authenticate)

    @param PlayerUlid The ulid of the player to clear cache for
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static void ClearCacheForPlayer(const FString& PlayerUlid);

    /**
    Remove all stored state information (players will need to re-authenticate) except for the specified player

    @param PlayerUlid The ulid of the player to save the cache for
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static void ClearAllPlayerCachesExceptForPlayer(const FString& PlayerUlid);

    /**
    Remove all stored state information (players will need to re-authenticate)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player State")
    static void ClearAllPlayerCaches();

    //==================================================
    //Authentication
    //==================================================

    /**
    Add a player state manually from data sourced externally. Use this for example with the token exchange feature in a server context.

    @param SessionToken The Session Token to use when making requests for this player
    @param PlayerUlid The Ulid of the player, this is the identifier used to select which token to use for requests
    @param CurrentPlatform The platform/authentication method used for this player
    @param RefreshToken (Optional) The token to use when refreshing sessions for this player
    @param PlayerIdentifier (Optional) The player identifier of the player
    @param PlayerPublicUid (Optional) The public uid of the player
    @param PlayerName (Optional) The name of the player if any has been set
    @param WhiteLabelEmail (Optional) The email used for white label authentication (only if the platform is White Label)
    @param WhiteLabelToken (Optional) The Token identifying the White Label Session
    @param LastSignIn (Optional) When this player was last authenticated
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = 3, RefreshToken = "", PlayerIdentifier = "", PlayerUlid = "", PlayerPublicUid = "", PlayerName = "", WhiteLabelEmail = "", WhiteLabelToken = "", LastSignIn = ""))
    static void StartSessionManual(const FString& SessionToken, const FString& PlayerUlid, FLootLockerPlatformRepresentation CurrentPlatform, const FString& RefreshToken, const FString& PlayerIdentifier, const FString& PlayerPublicUid, const FString& PlayerName, const FString& WhiteLabelEmail, const FString& WhiteLabelToken, const FString& LastSignIn);

    /**
     * Start a session for a Playstation Network user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.com/game-api/#authentication-request
     *
     * @param PsnOnlineId The PSN Online ID of the player
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for an Android user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.com/game-api/#authentication-request
     *
     * @param DeviceId The device id of the player
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for a Amazon Luna user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.com/game-api/#authentication-request
     *
     * @param AmazonLunaGuid The Amazon Luna GUID of the player
     * @param OnStartedSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnStartedSessionRequestCompleted);

    /**
     * Start a session for a steam user
     * You can optionally specify a steam app id if you have multiple ones for your game and have configured this in the LootLocker console
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * https://ref.lootlocker.com/game-api/#authentication-request
     *
     * @param SteamSessionTicket Platform-specific token.
     * @param SteamAppId (Optional) The specific Steam App Id to verify the player for
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "SteamAppId", SteamAppId = ""))
    static void StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FString& SteamAppId, const FAuthResponseBP& OnCompletedRequest);

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
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param RefreshToken (Optional) Token received in response from StartAppleSession request. If not supplied we will attempt to resolve it from stored player data.
     * @param OnRefreshAppleSessionCompleted Delegate for handling the response of type FLootLockerAppleSessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshAppleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted);

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
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted);

    /**
     * Refresh a previous session signed in with Apple Game Center
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Apple sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-apple-game-center
     *
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param RefreshToken (Optional) Token received in response from StartAppleSession request. If not supplied we will attempt to resolve it from stored player data.
     * @param OnRefreshAppleGameCenterSessionCompleted Delegate for handling the response of type FLootLockerAppleGameCenterResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshAppleGameCenterSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted);

    /**
     * Start a session for a Google user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-google
     *
     * @param IdToken The device id of the player
     * @param OnStartedGoogleSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted);

    /**
     * Start a session for a Google user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The desired Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-google
     *
     * @param IdToken The device id of the player
     * @param Platform Google OAuth2 ClientID platform
     * @param OnStartedGoogleSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted);

    /**
     * Refresh a previous session signed in with Google
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Google sign in platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-google
     *
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param RefreshToken (Optional) Token received in response from StartGoogleSession request. If not supplied we will attempt to resolve it from stored player data.
     * @param OnRefreshGoogleSessionCompleted Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshGoogleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted);
    
    /**
    * Start a session for a Google Play Games user
    * The Google Play Games sign in platform must be enabled in the web console for this to work.
    *
    * @param AuthCode The authorization code from your Google Play Games Sign In
    * @param OnStartedGooglePlayGamesSessionRequestCompleted Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartGooglePlayGamesSession(const FString& AuthCode, const FGooglePlayGamesSessionResponseBP& OnStartedGooglePlayGamesSessionRequestCompleted);

    /**
    * Refresh a previous session signed in with Google Play Games
    * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
    * The Google Play Games sign in platform must be enabled in the web console for this to work.
    *
    * @param ForPlayerWithUlid Optional : Execute the request for the specified player. If not supplied, the default player will be used.
    * @param RefreshToken (Optional) Token received in response from StartGooglePlayGamesSession request. If not supplied we will attempt to resolve it from stored player data.
    * @param OnRefreshGooglePlayGamesSessionCompleted Delegate for handling the response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid="", RefreshToken=""))
    static void RefreshGooglePlayGamesSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGooglePlayGamesSessionResponseBP& OnRefreshGooglePlayGamesSessionCompleted);
    
    /**
     * Start a session for an Epic Online Services (EOS) user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The Epic Games platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-epic-games
     *
     * @param IdToken The device id of the player
     * @param OnStartedEpicSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted);

    /**
     * Refresh a previous session signed in with Epic
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Epic Games platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#sign-in-with-epic-games
     *
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param RefreshToken (Optional) Token received in response from StartEpicSession request. If not supplied we will attempt to resolve it from stored player data.
     * @param OnRefreshEpicSessionCompleted Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshEpicSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted);

    /**
     * Start a session for an Meta / Oculus user
     * A game can support multiple platforms, but it is recommended that a build only supports one platform.
     * The Meta platform must be enabled in the web console for this to work.
     *
     * @param UserId The id recieved from Oculus
     * @param Nonce The nonce recieved from Oculus
     * @param OnMetaSessionRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted);

    /**
     * Refresh a previous session signed in with Meta
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     * The Meta platform must be enabled in the web console for this to work.
     *
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param RefreshToken (Optional) Token received in response from StartMetaSession request. If not supplied we will attempt to resolve it from stored player data.
     * @param OnRefreshMetaSessionCompleted Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshMetaSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnRefreshMetaSessionCompleted);

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
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = 3))
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
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnVerifyWhiteLabelSessionRequestCompleted Delegate for handling the response of type FLootLockerWhiteLabelVerifySessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void WhiteLabelVerifySession(const FString& ForPlayerWithUlid, const FLootLockerVerifySessionResponseBP& OnVerifyWhiteLabelSessionRequestCompleted);

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
    static void WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted);

    /**
     * Request verify account email for the user.
     * White Label platform must be enabled in the web console for this to work.
     * Account verification must also be enabled.
     * https://ref.lootlocker.com/game-api/#request-user-verification
     *
     * @param Email The Email of the user
     * @param OnRequestWhiteLabelUserVerificationRequestCompleted Delegate for handling the response of type FLootLockerResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted);

    /**
     * Request a password reset email for the given email address.
     * White Label platform must be enabled in the web console for this to work.
     * https://ref.lootlocker.com/game-api/#request-reset-password
     *
     * @param Email The email for the white label user
     * @param OnResetWhiteLabelPasswordRequestCompleted Delegate for handling the response of type FLootLockerResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelResetPassword(const FString& Email, const FLootLockerDefaultResponseBP& OnResetWhiteLabelPasswordRequestCompleted);

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
    * Start a session for a Discord user
    * The Discord sign in platform must be enabled in the web console for this to work.
    *
    * @param AccessToken The access token from Discord OAuth
    * @param OnStartedDiscordSessionRequestCompleted Delegate for handling the server response.
    */
    static void StartDiscordSession(const FString& AccessToken, const FDiscordSessionResponseBP& OnStartedDiscordSessionRequestCompleted);

    /**
    * Refresh a previous session signed in with Discord
    * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
    * The Discord sign in platform must be enabled in the web console for this to work.
    *
    * @param ForPlayerWithUlid Optional : Execute the request for the specified player. If not supplied, the default player will be used.
    * @param RefreshToken (Optional) Token received in response from StartDiscordSession request. If not supplied we will attempt to resolve it from stored player data.
    * @param OnRefreshDiscordSessionCompleted Delegate for handling the response
    */
    static void RefreshDiscordSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FDiscordSessionResponseBP& OnRefreshDiscordSessionCompleted);

    /**
     * Verify the player's identity with the server and selected platform.
     * If your game uses Player Verification, you need to call this endpoint before you can register a session.
     * https://ref.lootlocker.com/game-api/#player-verification
     *
     *
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param PlatformToken Platform-specific token.
     * @param OnVerifyPlayerRequestCompleted Response Delegate to handle the response
     * @param Platform Optional parameter to call explicitly for a specific platform
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void VerifyPlayer(const FString& ForPlayerWithUlid, const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, FString Platform = FString(TEXT("")));

    /**
     * End active session (if any exists)
     * Terminates the session on the LootLocker servers. Any further requests with this session's token will be rejected with an 401 Unauthorized error.
     * Succeeds if a session was ended or no sessions were active
     * https://ref.lootlocker.com/game-api/#ending-a-session
     *
     * @param ForPlayerWithUlid (Optional) Execute the request for player with the the ulidplayer. If not supplied, the default player will be used.
     * @param OnEndSessionRequestCompleted Delegate for handling the response of type LootLockerSessionResponse
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void EndSession(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted);

    //==================================================
    // Connected Accounts
    //==================================================
    /**
     * List identity providers (like Apple, Google, etc.) that are connected to the currently logged in account
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListConnectedAccounts(const FString& ForPlayerWithUlid, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP);

    /**
     * Disconnect account from the currently logged in account
     *
     * Use this to disconnect an account (like a Google or Apple account) that can be used to start sessions for this LootLocker account so that it is no longer allowed to do that
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AccountToDisconnect What account to disconnect from this LootLocker Account
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DisconnectAccount(const FString& ForPlayerWithUlid, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP);

    /**
     * Connect a Google Account to the currently logged in LootLocker account allowing that google account to start sessions for this player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param IdToken The Id Token from google sign in
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectGoogleAccount(const FString& ForPlayerWithUlid, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     * Connect a Google Account (with a Google Platform specified) to the currently logged in LootLocker account allowing that google account to start sessions for this player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param IdToken The Id Token from google sign in
     * @param Platform Google OAuth2 ClientID platform
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectGoogleAccountWithPlatform(const FString& ForPlayerWithUlid, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     * Connect an Apple Account (authorized by Rest Sign In) to the currently logged in LootLocker account allowing that google account to start sessions for this player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AuthorizationCode Authorization code, provided by apple during Sign In
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectAppleAccountByRestSignIn(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     * Connect an account (authorized using a remote session) to the currently logged in LootLocker account allowing that authentication method to start sessions for this player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Code The lease code returned with the response when starting a lease process
     * @param Nonce The nonce returned with the response when starting a lease process
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectRemoteSessionAccount(const FString& ForPlayerWithUlid, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     This endpoint lets you transfer identity providers between two players, provided you have a valid session for both.
     The designated identity providers will be transferred FROM the player designated by the `FromPlayerWithUlid` parameter and TO the player designated by the `ToPlayerWithUlid` parameter.
     If any of the providers can not be transferred the whole operation will fail and NO identity providers will be transferred.

     IMPORTANT: This is a destructive action. Once an identity provider has been transferred they will allow authentication for the target player and no longer authenticate for the source player.
     This can leave the source player without means of authentication and thus unusable from the game.

     ** Limitations **
      - You can not move an identity provider that the source player does not have
      - You can not move an identity provider to a player that already has an account from said identity provider associated with their account.
      - You can not move an identity provider which isn't active in your game settings.
     *
     * @param FromPlayerWithUlid The ULID of an authenticated player that you wish to move identity providers FROM
     * @param ToPlayerWithUlid The ULID of an authenticated player that you wish to move identity providers TO
     * @param ProvidersToTransfer Which identity providers you wish to transfer
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts")
    static void TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid, const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP);

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
     * @param TimeOutAfterMinutes Optional: How long to allow the process to take in its entirety
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Remote Session", meta = (AdvancedDisplay = "PollingIntervalSeconds,TimeOutAfterMinutes", PollingIntervalSeconds = 1.0f, TimeOutAfterMinutes = 5.0f, DeprecatedFunction, DeprecationMessage = "This method is deprecated in favor of either method AsyncStartRemoteSession or AsyncStartRemoteSessionForLinking depending on your use case")) // Deprecation date 20250327
    static FString StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegateBP& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes);

    /**
     * Cancel an ongoing remote session process
     *
     * @param ProcessID The id of the remote session process that you want to cancel
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Remote Session")
    static void CancelRemoteSessionProcess(FString ProcessID);

    /**
     * Refresh a previous session signed in remotely
     * A response code of 401 (Unauthorized) means the refresh token has expired and you'll need to sign in again
     *
     * @param RefreshToken (OPTIONAL) Refresh token received in response from StartRemoteSession request
     * @param OnCompletedRequest Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Remote Session", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshRemoteSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest);

    //==================================================
    //Players
    //==================================================

    /**
    * Get information about the currently logged in player such as name and different ids to use for subsequent calls to LootLocker methods
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrentPlayerInfo(const FString& ForPlayerWithUlid, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest);

    /**
    * List information for one or more other players
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param PlayerIdsToLookUp A list of ULID ids of players to look up. These ids are in the form of ULIDs and are sometimes called player_ulid or similar
    * @param PlayerLegacyIdsToLookUp A list of legacy ids of players to look up. These ids are in the form of integers and are sometimes called simply player_id or id
    * @param PlayerPublicUidsToLookUp A list of public uids to look up. These ids are in the form of UIDs
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerInfo(const FString& ForPlayerWithUlid, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest);

    /**
    * Get a paginated list of the players inventory.
    * https://ref.lootlocker.com/game-api/#get-inventory-list
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnGetInventoryRequestCompleted Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetInventory(const FString& ForPlayerWithUlid, const FPInventoryResponseBP& OnGetInventoryRequestCompleted);

    /**
    * Get assets that have been granted to the player since the last time this endpoint was called.
    * https://ref.lootlocker.com/game-api/#player-asset-notifications
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnCheckPlayerAssetDeactivationNotificationRequestCompleted Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CheckPlayerAssetActivationNotification(const FString& ForPlayerWithUlid, const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted);

    /**
    * This endpoint will return the amount of credits the current player have on their account.
    * https://ref.lootlocker.com/game-api/#get-currency-balance
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnGetCurrencyBalance Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrencyBalance(const FString& ForPlayerWithUlid, const FPBalanceResponseBP& OnGetCurrencyBalance);

    /**
    * This endpoint will initiate a DLC migration for the current player. 5 minutes after calling this endpoint you should issue
    * a call to the Player Asset Notifications call, to get the results of the migration, if any.
    *
    * https://ref.lootlocker.com/game-api/#initiate-dlc-migration
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnInitiateDlcMigration Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void InitiateDLCMigration(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnInitiateDlcMigration);

    /**
    * This endpoint will return a list of DLC's migrated for the player. The DLC identifiers returned
    * will be the ones of the platform the DLC belongs to. The identifier will always be a string, even if the identifier is numeric.
    * https://ref.lootlocker.com/game-api/#get-dlcs-migrated
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnGotDlcMigration Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetDLCsMigration(const FString& ForPlayerWithUlid, const FPDlcResponseBP& OnGotDlcMigration);

    /**
    * This endpoint will set the players profile to private. This means that their
    * inventory will not be displayed publicly on Steam and other places.
    * https://ref.lootlocker.com/game-api/#set-profile-private
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnProfileSetPrivate Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetProfilePrivate(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPrivate);

    /**
    * This endpoint will set the players profile to public. This means that their inventory will be
    * displayed publicly on Steam and other places.
    * https://ref.lootlocker.com/game-api/#set-profile-public
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnProfileSetPublic Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetProfilePublic(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPublic);

    /**
    * This endpoint will set the players name.
    * https://ref.lootlocker.com/game-api/#set-player-name
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Name String name to set.
    * @param OnSetPlayerName Delegate for handling the the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetPlayerName(const FString& ForPlayerWithUlid, FString Name, const FPNameResponseBP& OnSetPlayerName);

    /**
    * This endpoint will get the players name.
    * https://ref.lootlocker.com/game-api/#get-player-name
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnGetPlayerName Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetPlayerName(const FString& ForPlayerWithUlid, const FPNameResponseBP& OnGetPlayerName);

    /**
    * This endpoint will return the names of the players on their last active platform.
    * https://ref.lootlocker.com/game-api/#lookup-multiple-player-names-using-ids
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Request Request array with platforms and Ids to search for.
    * @param OnCompletedRequest Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid="", DeprecatedFunction, DeprecationMessage = "This method is deprecated in favor of method LookupMultiplePlayersDataUsingIDs")) // Deprecation date 20250304
    static void LookupMultiplePlayerNamesUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNamesBP& OnCompletedRequest);
    
    /**
    * Look up multiple player's data using different identifiers
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Request Request array with platforms and Ids to lookup player data for.
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LookupMultiplePlayersDataUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest);

    /**
    * This endpoint will return the names of the players on their last active platform.
    * https://ref.lootlocker.com/game-api/#lookup-multiple-player-1st-platform-ids-using-lootlocker-player-ids
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Request Request array with player ids and/or player public uids to search for.
    * @param OnCompletedRequest Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LookupMultiplePlayerNames1stPlatformIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest);

    /**
    * This method will mark the player for deletion. After 30 days the player will be deleted from the system.
    * https://ref.lootlocker.com/game-api/#delete-player
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnCompletedRequest Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeletePlayer(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    //==================================================
    //Files
    // https://ref.lootlocker.com/game-api/#player-files
    //==================================================

    /**
     * Upload a file with the provided name and content. The file will be owned by the currently active player.
     * https://ref.lootlocker.com/game-api/#upload-a-file
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Request Request of type FLootLockerFileUploadRequest.
     * @param OnComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UploadFile(const FString& ForPlayerWithUlid, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete);

    /**
     * Update the specified file with the supplied content. The file will be owned by the currently active player.
     * https://ref.lootlocker.com/game-api/#update-a-file
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param FileId Id of the file, can be retrieved with ListFiles or when the file is uploaded
     * @param Request Request of type FLootLockerFileUpdateRequest.
     * @param OnComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateFile(const FString& ForPlayerWithUlid, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete);

    /**
     * Returns all the files that your currently active player own.
     * https://ref.lootlocker.com/game-api/#list-files
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFiles(const FString& ForPlayerWithUlid, const FLootLockerFileListBP& OnComplete);

    /**
     * Returns all public files that the player with the provided playerID owns.
     * https://ref.lootlocker.com/game-api/#list-another-players-public-files
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerID Player ID of the player for whom to get the files
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListOtherPlayersPublicFiles(const FString& ForPlayerWithUlid, const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP);

    /**
     * Returns a URL where you can access the file. You can get the ID of files when you upload them, or call the list endpoint.
     * https://ref.lootlocker.com/game-api/#get-single-file
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param FileID Id of the file, can be retrieved with ListFiles or when the file is uploaded
     * @param OnComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetSingleFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerUploadFileBP& OnComplete);

    /**
     * The file will be deleted immediately and the action can not be reversed. You will get the ID of files when you upload a file, or with ListFiles.
     * https://ref.lootlocker.com/game-api/#delete-file
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param FileID Id of the file. You can get the ID of files when you upload a file, or with GetAllPlayerFiles()
     * @param OnComplete Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeletePlayerFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerFileDeletedBP& OnComplete);

    //==================================================
    // Player Progressions
    //==================================================

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetPlayerProgressions(const FString& ForPlayerWithUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest);

    /**
    * Returns a single progression the player is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest);

    /**
    * Adds points to the specified player progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddPointsToPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Subtracts points from the specified player progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubtractPointsFromPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Resets the specified player progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ResetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Returns multiple progressions the player is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to delete
    * @param OnCompletedRequest Action for handling the response of type FLootLockerResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeletePlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest);

    /**
    * Returns multiple progressions that the specified player is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param PlayerUlid The ulid of the player you want to fetch progressions for
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersProgressions(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest);

    /**
    * Returns a single progression that the specified player is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param PlayerUlid The ulid of the player you want to fetch the progression for
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetOtherPlayersProgression(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest);

    //==================================================
    //Heroes
    // https://ref.lootlocker.com/game-api/#heroes
    //==================================================

    /**
     * List heroes with names and character information
     * https://ref.lootlocker.com/game-api/#get-game-heroes
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetGameHeroes(const FString& ForPlayerWithUlid, const FLootLockerGameHeroListBP& OnCompleteBP);

    /**
     * List heroes that the current player owns
     * https://ref.lootlocker.com/game-api/#list-player-heroes
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerHeroes(const FString& ForPlayerWithUlid, const FLootLockerHeroListBP& OnCompleteBP);

    /**
     * List player that the player with the specified SteamID64 owns
     * https://ref.lootlocker.com/game-api/#list-other-players-heroes-by-steamid64
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param SteamID64 Steam Id of the requested player
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListOtherPlayersHeroesBySteamID64(const FString& ForPlayerWithUlid, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP);

    /**
     * Create a hero for the current player with the supplied name from the game hero specified with the supplied hero id
     * https://ref.lootlocker.com/game-api/#creating-a-hero
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Request Request specifying the hero id for the game hero to use for creation and the name of the hero to create
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateHero(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Create a hero for the current player with the supplied name from the game hero specified with the supplied hero id, asset variation id, and whether to set as default.
     * https://ref.lootlocker.com/game-api/#creating-a-hero
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Request Request specifying the hero id for the game hero to use for creation and the name of the hero to create, an asset variation id for this hero, and whether this hero should be the default
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateHeroWithVariation(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Return information about the requested hero on the current player
     * https://ref.lootlocker.com/game-api/#getting-a-hero
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero to get
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Get the default hero for the player with the specified SteamID64
     * https://ref.lootlocker.com/game-api/#get-other-players-default-hero-by-steamid64
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param SteamID64 Steam Id of the requested player
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersDefaultHeroBySteamID64(const FString& ForPlayerWithUlid, const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Update the name of the hero with the specified id and/or set it as default for the current player
     * https://ref.lootlocker.com/game-api/#updating-a-hero
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param Request Request specifying the new (or same) name to set for the hero and if it is to be the default hero for the player
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     * Remove the hero with the specified id from the current players list of heroes.
     * This action is currently irreversible.
     * When deleting a hero, the heroes inventory is returned to the player, and their loadout is reset.
     * https://ref.lootlocker.com/game-api/#deleting-a-hero
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP);

    /**
     * List Asset Instances owned by the specified hero
     *
     * Note that this endpoint is paginated and will return the first 50 entries
     * https://ref.lootlocker.com/game-api/#get-hero-inventory
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetHeroInventory(const FString& ForPlayerWithUlid, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP);

    /**
     * List the loadout of the specified hero that the current player owns
     *
     * https://ref.lootlocker.com/game-api/#get-hero-loadout
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * List the loadout of the specified hero that the another player owns
     * https://ref.lootlocker.com/game-api/#get-other-players-hero-loadout
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Equip the specified Asset Instance to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param AssetInstanceID The ID of the already existing asset instance
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Equip the specified Global Asset (default variation) to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param AssetID The id of the global asset to equip
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddGlobalAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Equip the specified Global Asset Variation to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#add-asset-to-hero-loadout
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param AssetID The id of the global asset to equip
     * @param AssetVariationID The variation id of the global asset to equip
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddGlobalAssetVariationToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     * Unequip the specified Asset Instance to the specified Hero that the current player owns
     * https://ref.lootlocker.com/game-api/#remove-asset-from-hero-loadout
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HeroID Id of the hero
     * @param AssetInstanceID Desc
     * @param OnCompleteBP Delegate for handling the response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RemoveAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    //==================================================
    //Characters
    // https://ref.lootlocker.com/game-api/#characters
    //==================================================

    /**
    * This call will return all characters loadouts for a game, and have some additional information on the characters.
    * https://ref.lootlocker.com/game-api/#character-loadouts
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnGetCharacterLoadoutRequestCompleted Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCharacterLoadout(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted);

    /**
     * This endpoint lets you set a character as default, and set the name of the character.
     * https://ref.lootlocker.com/game-api/#update-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CharacterId Id of the character to make the update for
     * @param IsDefault Should the character be set as default
     * @param Name The name to set for the character
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateCharacter(const FString& ForPlayerWithUlid, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest);

    /**
     * Create a character of the specified character type with the given name
     * If IsDefault is set to true, the new character will be made the default character.
     * See List Character Types to get your games Character Types.
     * https://ref.lootlocker.com/game-api/#create-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param IsDefault If this should be set as the default character.
     * @param CharacterName The name of the character.
     * @param CharacterTypeId The ID of the character type.
     * @param OnCompletedRequestBP Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateCharacter(const FString& ForPlayerWithUlid, bool IsDefault, FString CharacterName, FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP);

    /**
     * Delete the character with the specified instance id.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CharacterId The ID of the character to delete.
     * @param OnCompletedRequestBP Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteCharacter(const FString& ForPlayerWithUlid, int CharacterId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP);

    /**
     * Call this endpoint to list the character types configured for your game.
     * https://ref.lootlocker.com/game-api/#list-character-types
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnCompletedRequestBP Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListCharacterTypes(const FString& ForPlayerWithUlid, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP);

    /**
    * Get list of Characters to a player
    * https://ref.lootlocker.com/game-api/#list-player-characters
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnCompletedRequestBP Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerCharacters(const FString& ForPlayerWithUlid, const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP);
    /**
     * Equip an asset to the default character.
     * https://ref.lootlocker.com/game-api/#equip-asset-to-default-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param InstanceId The asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnEquipAssetToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void EquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted);

    /**
    * Equip an asset to the specified character.
    * https://ref.lootlocker.com/game-api/#equip-asset-to-character-by-id
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId ID of the character to equip an asset to.
    * @param AssetId the asset's instance_id that is returned from the inventory and loadout calls.
    * @param AssetVariationId the asset_variation_id.
    * @param OnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void EquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

    /**
     * Equip an asset to the specified character.
     * https://ref.lootlocker.com/game-api/#equip-asset-to-character-by-id
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CharacterId ID of the character to equip an asset to.
     * @param InstanceId the asset's instance_id that is returned from the inventory and loadout calls.
     * @param OnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void EquipAssetToCharacterByIdAndInstance(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

    /**
     * Unequip an asset from the default character.
     * https://ref.lootlocker.com/game-api/#unequip-asset-to-default-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnUnEquipAssetToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnEquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted);

    /**
     * Unequip an asset from the specified character.
     * https://ref.lootlocker.com/game-api/#unequip-asset-to-character-by-id
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CharacterId ID of the character to unequip an asset from.
     * @param InstanceId the asset's instance id that is returned from the inventory and loadout calls.
     * @param OnUnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnEquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted);


    /**
     * Getting the current loadout will return an array of assets that the user currently has equipped.
     * https://ref.lootlocker.com/game-api/#get-current-loadout-to-default-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetCurrentLoadoutToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);

    /**
     * This method will return the exact same response as the GetCharacterLoadout, except that it will be for another player.
     * https://ref.lootlocker.com/game-api/#get-other-players-loadout-to-default-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OtherPlayerId other player's ID on the requested platform.
     * @param OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted Delegate for handling the server response.
     * @param OtherPlayerPlatform Optional: the platform the id refers to if different than the currentplatform
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform = FString(TEXT("")));

    /**
     * Get the contexts that the player's default character can equip.
     * https://ref.lootlocker.com/game-api/#get-equippable-contexts-to-default-character
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetEquipableContextsToDefaultCharacterRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEquipableContextsToDefaultCharacter(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted);

    /**
     * Get the contexts that the specified player's default character can equip.
     * https://ref.lootlocker.com/game-api/#get-equippable-contexts-by-character-id
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OtherCharacterId other player's ID.
     * @param OnGetEquipableContextsByCharacterIdRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEquipableContextsByCharacterId(const FString& ForPlayerWithUlid, int OtherCharacterId, const FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted);

    /**
     * Get a character loadout from a specific player and platform
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OtherPlayerId The platform specific id of the player you want to fetch the character loadouts for.
     * @param OtherPlayerPlatform Optional: the platform the id refers to if different than the current platform
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid,OtherPlayerPlatform", ForPlayerWithUlid="", OtherPlayerPlatform=""))
    static void GetOtherPlayersCharacterLoadouts(const FString& ForPlayerWithUlid, const FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequest);

    /**
     * Get a character loadout from a specific player by their public uid.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OtherPlayerUid The public uid of the player you want to fetch the character loadouts for.
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersCharacterLoadoutsByUid(const FString& ForPlayerWithUlid, const FString& OtherPlayerUid, const FPCharacterLoadoutResponseBP& OnCompletedRequest);


    //==================================================
    // Character Progressions
    //==================================================

    /**
    * Returns multiple progressions the character is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the character progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedCharacterProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetCharacterProgressions(const FString& ForPlayerWithUlid, const int32& CharacterId, const int32 Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest);

    /**
    * Returns a single progression the character is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest);

    /**
    * Adds points to the specified character progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddPointsToCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Subtracts points from the specified character progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubtractPointsFromCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * Resets the specified character progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnCompletedRequest Action for handling the response of type FLootLockerCharacterProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ResetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
    * deletes the specified character progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param CharacterId Id of the character you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to delete
    * @param OnCompletedRequest Action for handling the response of type FLootLockerResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest);

    //==================================================
    //Persistent Storage
    // https://ref.lootlocker.com/game-api/#persistent-player-storage
    //==================================================

    /**
     * This call returns all key/value pairs on record for the current player, beware that it may be a lot of data.
     * https://ref.lootlocker.com/game-api/#get-entire-persistent-storage
     * Note: The Player Metadata feature will over time replace Player Persistent Storage.
     * If you are not already deeply integrated with the Player Persistent Storage in your game, consider moving to Player Metadata.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnPersistentStorageItemsRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEntirePersistentStorage(const FString& ForPlayerWithUlid, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted);

    /**
     * Get Key/Value pair from the player's persistent storage.
     * https://ref.lootlocker.com/game-api/#get-a-single-key-from-persistent-storage
     * Note: The Player Metadata feature will over time replace Player Persistent Storage.
     * If you are not already deeply integrated with the Player Persistent Storage in your game, consider moving to Player Metadata.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Key Key of the key/value pair.
     * @param OnPersistentStorageItemRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted);

    /**
     * Create/Update key/value pair(s).
     * https://ref.lootlocker.com/game-api/#updating-creating-key-value-pairs
     * Note: The Player Metadata feature will over time replace Player Persistent Storage.
     * If you are not already deeply integrated with the Player Persistent Storage in your game, consider moving to Player Metadata.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Items array of items to be created/updated.
     * @param OnPersistentStorageItemsAddRequestCompleted Delegate for handling theserver response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddItemsToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted);

    /**
     * Create/Update a key/value pair.
     * https://ref.lootlocker.com/game-api/#updating-creating-key-value-pairs
     * Note: The Player Metadata feature will over time replace Player Persistent Storage.
     * If you are not already deeply integrated with the Player Persistent Storage in your game, consider moving to Player Metadata.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Item item to be created/updated.
     * @param OnPersistentStorageItemAddRequestCompleted Delegate for handling theserver response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddItemToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted);

    /**
     * Delete a key/value pair.
     * https://ref.lootlocker.com/game-api/#deleting-a-key-value-pair
     * Note: The Player Metadata feature will over time replace Player Persistent Storage.
     * If you are not already deeply integrated with the Player Persistent Storage in your game, consider moving to Player Metadata.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Key key of a key/value pair.
     * @param OnPersistentStorageItemDeleteRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted);

    /**
     * Read another players public key/value storage.
     * https://ref.lootlocker.com/game-api/#getting-other-players-public-key-value-pairs
     * Note: The Player Metadata feature will over time replace Player Persistent Storage.
     * If you are not already deeply integrated with the Player Persistent Storage in your game, consider moving to Player Metadata.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerId players id or their public UID.
     * @param OnGetPlayerPersistentStorageRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetPlayerPersistentStorage(const FString& ForPlayerWithUlid, const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted);

    //==================================================
    //Assets
    //==================================================

    /**
     * Get all the contexts the game has.
     * https://ref.lootlocker.com/game-api/#getting-contexts
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetContextsRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetContexts(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetContextsRequestCompleted);

    /**
     * Get all assets in a paginated form.
     * https://ref.lootlocker.com/game-api/#getting-asset-list
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetAssetsRequestCompleted Delegate for handling the server response.
     * @param StartFromIndex Optional: Index of the item to start from, defaults to 0
     * @param ItemsCount Optional: Number of items to receive (50-200), defaults to 50
     * @param AssetFilter Optional: Filter to apply, defaults to None
     * @param Context Optional: Context filter to apply, defaults to 0
     * @param IncludeUGC Optional: Whether to include UGC Assets,defaults to false
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssets(const FString& ForPlayerWithUlid, const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, int Context = 0, bool IncludeUGC = false);

    /**
     * Retrieve only specific Assets by their ID's.
     * https://ref.lootlocker.com/game-api/#getting-assets-by-ids
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetIds Array of the asset ID's to be fetched.
     * @param OnGetAssetsByIdsRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssetsByIds(const FString& ForPlayerWithUlid, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted);

    /**
     * This call will return you all the default bones.
     * If a binding overrides anything on a bone, it will be returned along with the binding.
     * https://ref.lootlocker.com/game-api/#getting-asset-bone-information
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetAssetBonesRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssetBones(const FString& ForPlayerWithUlid, const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted);

    /**
     * List the current players favourite assets.
     * https://ref.lootlocker.com/game-api/#listing-favourite-assets
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetFavouriteAssetIndicesRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetFavouriteAssetIndices(const FString& ForPlayerWithUlid, const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted);

    /**
     * Add an asset to the list of favourites.
     * https://ref.lootlocker.com/game-api/#adding-favourite-assets
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetId Asset ID to be added.
     * @param OnAddAssetToFavouritesRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddAssetToFavourites(const FString& ForPlayerWithUlid, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted);

    /**
     * Remove an asset from the list of favourites.
     * https://ref.lootlocker.com/game-api/#removing-favourite-assets
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetId asset ID to be removed.
     * @param OnRemoveAssetFromFavouritesRequestCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RemoveAssetFromFavourites(const FString& ForPlayerWithUlid, int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted);

    /**
     * This call offers a paginated list of the games universal assets
     * https://ref.lootlocker.com/game-api/#get-universal-assets
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param After Last universal id to start after.
     * @param ItemsCount Number of items to receive (50-200).
     * @param OnCompletedRequest Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetUniversalAssets(const FString& ForPlayerWithUlid, int After, int ItemsCount, const FUniversalAssetResponseDelegateBP& OnCompletedRequest);

    /**
    * Grant an asset to the Player
    * https://ref.lootlocker.com/game-api/#grant-an-asset-to-the-player
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetID asset ID to be granted.
    * @param AssetVariationID The ID of the Asset Variation you want to grant
    * @param AssetRentalOptionID The ID of the rental option you want to grant
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GrantAssetWithVariationToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest);

    /**
    * Grant an asset to the Player
    * https://ref.lootlocker.com/game-api/#grant-an-asset-to-the-player
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetID asset ID to be granted.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GrantAssetToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const FGrantAssetResponseDelegateBP& OnCompletedRequest) {
        GrantAssetWithVariationToPlayerInventory(ForPlayerWithUlid, AssetID, 0, 0, OnCompletedRequest);
    }

    /**
    * List assets with default parameters (no filters, first page, default page size)
    * Lightweight alternative for retrieving assets where only selected data is needed
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListAssetsWithDefaultParameters(const FString& ForPlayerWithUlid, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest);

    /**
    * List assets with configurable response data. Use this to limit the fields returned in the response and improve performance.
    * Lightweight alternative for retrieving assets where only selected data is needed
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Request Request object with settings on what fields to include, exclude, and what assets to filter
    * @param PerPage Optional: Used together with Page to apply pagination to this Request. PerPage designates how many notifications are considered a "page". Set to 0 to not use this filter.
    * @param Page Optional: Used together with PerPage to apply pagination to this Request. Page designates which "page" of items to fetch. Set to 0 to not use this filter.
    * @param OnCompletedRequest Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "PerPage,Page,ForPlayerWithUlid", PerPage=0,Page=0,ForPlayerWithUlid=""))
    static void ListAssets(const FString& ForPlayerWithUlid, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest);

    //==================================================
    //Asset Instances
    //==================================================

    /**
     * Get all key/value pairs for an asset instance.
     * https://ref.lootlocker.com/game-api/#getting-all-key-value-pairs-to-an-instance
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param OnGetAllKeyValuePairsForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllKeyValuePairsForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted);

    /**
     * Get a key/value pair for an asset instance.
     * https://ref.lootlocker.com/game-api/#getting-a-key-value-pair-by-id
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId ID of the key/value pair.
     * @param OnGetAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     * Create a key/value pair for an asset instance.
     * https://ref.lootlocker.com/game-api/#creating-a-key-value-pair
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param Item key/value pair.
     * @param OnCreateAKeyValuePairForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateAKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted);

    /**
     * Update key/value pairs for an asset instance.
     * https://ref.lootlocker.com/game-api/#updating-one-or-more-key-value-pairs
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param Items key/value pairs.
     * @param OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);

    /**
     * Update a key/value pair for an asset instance.
     * https://ref.lootlocker.com/game-api/#updating-a-key-value-pair-by-id
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
     * @param Item Struct FLootLockerAssetInstanceStorageItem
     * @param OnUpdateAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     * Delete a key/value pair for an asset instance.
     * https://ref.lootlocker.com/game-api/#delete-a-key-value-pair
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param StorageItemId key/value pair ID.
     * @param OnDeleteAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     * Get the drop rates for a loot box asset instance.
     * https://ref.lootlocker.com/game-api/#inspect-a-loot-box
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param OnInspectLootBoxCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void InspectLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted);

    /**
     * Open a loot box asset instance.
     * The loot box will be consumed and the contents will be added to the player's inventory.
     * https://ref.lootlocker.com/game-api/#open-a-loot-box
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId asset instance ID.
     * @param OnOpenLootBoxCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void OpenLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted);

    /**
    * Delete an Asset Instance permanently from a Player's Inventory.
    * https://ref.lootlocker.com/game-api/#remove-an-asset-from-the-player-inventory
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceID asset instance ID.
    * @param OnCompleted Delegate for handling the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteAssetInstanceFromPlayerInventory(const FString& ForPlayerWithUlid, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted);

    //==================================================
    //User Generated Content
    //==================================================

    /**
     * Create an asset candidate.
     * https://ref.lootlocker.com/game-api/#creating-an-asset-candidate
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateData asset candidate data.
     * @param OnCreateAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateAssetCandidate(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted);

    /**
     * Create an asset candidate and immediately mark it as completed
     * https://ref.lootlocker.com/game-api/#creating-an-asset-candidate
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateData asset candidate data.
     * @param OnCreateAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateAssetCandidateAndMarkComplete(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted);

    /**
     * Update an asset candidate.
     * https://ref.lootlocker.com/game-api/#updating-an-asset-candidate
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateId ID of the asset candidate.
     * @param AssetCandidateData asset candidate data.
     * @param OnUpdateAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted);

    /**
     * Delete an asset candidate.
     * https://ref.lootlocker.com/game-api/#deleting-an-asset-candidate
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnDeleteAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted);

    /**
     * Get all asset candidates.
     * https://ref.lootlocker.com/game-api/#listing-asset-candidates
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetAllAssetCandidatesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllAssetCandidates(const FString& ForPlayerWithUlid, const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted);

    /**
     * Get an asset candidate.
     * https://ref.lootlocker.com/game-api/#getting-a-single-asset-candidate
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateId ID of the asset candidate.
     * @param OnGetAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted);

    /**
     * Add a file to an asset candidate.
     * https://ref.lootlocker.com/game-api/#adding-files-to-asset-candidates
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateId ID of the asset candidate.
     * @param FilePath full absolute path to a file.
     * @param FilePurpose purpose of the file.
     * @param OnAddFileToAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddFileToAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnAddFileToAssetCandidateCompleted);

    /**
     * Remove a file from an asset candidate.
     * https://ref.lootlocker.com/game-api/#removing-files-from-an-asset-candidate
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetCandidateId ID of the asset candidate.
     * @param FileId ID of the file.
     * @param OnDeleteFileFromAssetCandidateCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteFileFromAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted);

    //==================================================
    // Progressions
    //==================================================

    /**
    * Returns multiple progressions.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetProgressions(const FString& ForPlayerWithUlid, const int32 Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest);

    /**
    * Returns the specified progression
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest);

    /**
    * Returns multiple progression tiers for the specified progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param ProgressionKey Key of the progression you want to fetch
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the player progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequest Action for handling the response of type FLootLockerPaginatedPlayerProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = -1, ForPlayerWithUlid=""))
    static void GetProgressionTiers(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32 Count, const int32 After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest);

    //==================================================
    //Instance Progressions
    //==================================================

    /**
    * Returns multiple progressions the asset instance is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceId Id of the instance you want to fetch progressions for
    * @param Count Optional: Amount of entries to receive
    * @param After Optional: Used for pagination, id of the instance progression from which the pagination starts from, use the next_cursor and previous_cursor values
    * @param OnCompletedRequestBP Action for handling the response of type FLootLockerPaginatedInstanceProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetInstanceProgressions(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequestBP);

    /**
    * Returns a single progression the instance is currently on.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceId Id of the instance you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to fetch
    * @param OnCompletedRequestBP Action for handling the response of type FLootLockerInstanceProgressionsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequestBP);

    /**
    * Adds points to the specified instance progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceId Id of the instance you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to add points to
    * @param Amount Amount of points to be added
    * @param OnCompletedRequestBP Action for handling the response of type FLootLockerinstanceProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddPointsToInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
    * Subtracts points from the specified instance progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceId Id of the instance you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to subtract points from
    * @param Amount Amount of points to be subtracted
    * @param OnCompletedRequestBP Action for handling the response of type FLootLockerInstanceProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubtractPointsFromInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
    * Resets the specified instance progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceId Id of the instance you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to reset
    * @param OnCompletedRequestBP Action for handling the response of type FLootLockerInstanceProgressionWithRewardsResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ResetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
    * Deletes the specified instance progression.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param AssetInstanceId Id of the instance you want to fetch progressions for
    * @param ProgressionKey Key of the progression you want to delete
    * @param OnCompletedRequestBP Action for handling the response of type FLootLockerResponse
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP);

    //==================================================
    //Missions
    //==================================================

    /**
     * Get all missions.
     * https://ref.lootlocker.com/game-api/#getting-all-missions
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetAllMissionsCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllMissions(const FString& ForPlayerWithUlid, const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted);

    /**
     * Get a mission.
     * https://ref.lootlocker.com/game-api/#getting-a-single-mission
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param MissionId mission ID.
     * @param OnGetMissionCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMission(const FString& ForPlayerWithUlid, int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted);

    /**
     * Start a mission.
     * https://ref.lootlocker.com/game-api/#starting-mission
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param MissionId mission ID.
     * @param OnStartMissionCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void StartMission(const FString& ForPlayerWithUlid, int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted);

    /**
     * Finish a mission.
     * https://ref.lootlocker.com/game-api/#finishing-mission
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param MissionId mission ID.
     * @param MissionData mission completion data.
     * @param OnFinishMissionCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void FinishMission(const FString& ForPlayerWithUlid, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted);

    //==================================================
    //Maps
    // https://ref.lootlocker.com/game-api/#maps
    //==================================================

    /**
     * Get maps data.
     * https://ref.lootlocker.com/game-api/#getting-all-maps
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetMapsCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Maps", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMaps(const FString& ForPlayerWithUlid, const FGetMapsResponseDelegateBP& OnGetMapsCompleted);

    //==================================================
    //Purchases
    // https://ref.lootlocker.com/game-api/#purchasing
    //==================================================

    /**
     * Activates specified rental asset
     * Once you have purchased a rental asset, you need to activate the rental for it to become available for the player.
     * https://ref.lootlocker.com/game-api/#activating-a-rental-asset
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AssetInstanceId ID of the asset.
     * @param OnActivateRentalAssetCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ActivateRentalAsset(const FString& ForPlayerWithUlid, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted);

    /**
     * Purchase one catalog item using a specified wallet
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param WalletId The id of the wallet to use for the purchase
     * @param CatalogItemListingId The unique listing id of the catalog item to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LootLockerPurchaseSingleCatalogItem(const FString& ForPlayerWithUlid, const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Purchase one or more catalog items using a specified wallet
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param WalletId The id of the wallet to use for the purchase
     * @param ItemsToPurchase A list of items to purchase along with the quantity of each item to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LootLockerPurchaseCatalogItems(const FString& ForPlayerWithUlid, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Apple App Store for the current player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param TransactionId The id of the transaction successfully made towards the Apple App Store
     * @param Sandboxed Optional: Should this redemption be made towards sandbox App Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "Sandboxed,ForPlayerWithUlid", Sandboxed = false, ForPlayerWithUlid=""))
    static void RedeemAppleAppStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Apple App Store for a class that the current player owns
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param TransactionId The id of the transaction successfully made towards the Apple App Store
     * @param ClassId The id of the class to redeem this transaction for
     * @param Sandboxed Optional: Should this redemption be made towards sandbox App Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "Sandboxed,ForPlayerWithUlid", Sandboxed = false, ForPlayerWithUlid=""))
    static void RedeemAppleAppStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Google Play Store for the current player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param ProductId The id of the product that this redemption refers to
     * @param PurchaseToken The token from the purchase successfully made towards the Google Play Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemGooglePlayStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Google Play Store for a class that the current player owns
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param ClassId The id of the class to redeem this purchase for
     * @param ProductId The id of the product that this redemption refers to
     * @param PurchaseToken The token from the purchase successfully made towards the Google Play Store
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemGooglePlayStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Epic Store for the current player
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param AccountId The epic account id of the account that this purchase was made for
     * @param BearerToken This is the token from epic used to allow the LootLocker backend to verify ownership of the specified entitlements. This is sometimes referred to as the Server Auth Ticket or Auth Token depending on your Epic integration.
     * @param EntitlementIds The ids of the purchased entitlements that you wish to redeem
     * @param SandboxId The Sandbox Id configured for the game making the purchase (this is the sandbox id from your epic online service configuration)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemEpicStorePurchase(const FString& ForPlayerWithUlid, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Redeem a purchase that was made successfully towards the Epic Store for a class that the current player owns
     *
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CharacterId The ulid of the character to redeem this purchase for
     * @param AccountId The epic account id of the account that this purchase was made for
     * @param BearerToken This is the token from epic used to allow the LootLocker backend to verify ownership of the specified entitlements. This is sometimes referred to as the Server Auth Ticket or Auth Token depending on your Epic integration.
     * @param EntitlementIds The ids of the purchased entitlements that you wish to redeem
     * @param SandboxId The Sandbox Id configured for the game making the purchase (this is the sandbox id from your epic online service configuration)
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemEpicStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
     * Begin a Steam purchase with the given settings that when finalized will redeem the specified catalog item
     *
     * Steam in-app purchases need to be configured for this to work
     * Steam in-app purchases works slightly different from other platforms, you begin a purchase with this call which initiates it in Steams backend
     * While your app is waiting for the user to finalize that purchase you can use QuerySteamPurchaseRedemptionStatus to get the status, when that tells you that the purchase is Approved you can finalize the purchase using FinalizeSteamPurchaseRedemption
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param SteamId Id of the Steam User that is making the purchase
     * @param Currency The currency to use for the purchase
     * @param Language The language to use for the purchase
     * @param CatalogItemId The LootLocker Catalog Item Id for the item you wish to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void BeginSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest);

    /**
     * Begin a Steam purchase with the given settings that when finalized will redeem the specified catalog item for the specified class
     *
     * Steam in-app purchases need to be configured for this to work
     * Steam in-app purchases works slightly different from other platforms, you begin a purchase with this call which initiates it in Steams backend
     * While your app is waiting for the user to finalize that purchase you can use QuerySteamPurchaseRedemptionStatus to get the status, when that tells you that the purchase is Approved you can finalize the purchase using FinalizeSteamPurchaseRedemption
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param ClassId Id of the class to make the purchase for
     * @param SteamId Id of the Steam User that is making the purchase
     * @param Currency The currency to use for the purchase
     * @param Language The language to use for the purchase
     * @param CatalogItemId The LootLocker Catalog Item Id for the item you wish to purchase
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void BeginSteamPurchaseRedemptionForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest);

    /**
     * Check the Steam Purchase status for a given entitlement
     *
     * Use this to check the status of an ongoing purchase to know when it's ready to finalize or has been aborted
     * or use this to get information for a completed purchase
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param EntitlementId The id of the entitlement to check the status for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void QuerySteamPurchaseRedemptionStatus(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest);

    /**
     * Finalize a started Steam Purchase and subsequently redeem the catalog items that the entitlement refers to
     *
     * The steam purchase needs to be in status Approved for this call to work
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param EntitlementId The id of the entitlement to finalize the purchase for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void FinalizeSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    //==================================================
    // Triggers
    //==================================================

    /**
     * Invoke a set of triggers by key
     *
     * Note that the response contains two lists:
     * - One listing the keys of the triggers that were successfully executed
     * - One listing the triggers that failed as well as the reason they did so
     *
     * This means that the request can "succeed" but still contain triggers that failed. So make sure to check the inner results.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param KeysToInvoke List of keys of the triggers to invoke
     * @param OnComplete Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Triggers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void InvokeTriggersByKey(const FString& ForPlayerWithUlid, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnComplete);

    //==================================================
    // Notifications
    //==================================================

    /**
     List notifications without filters and with default pagination settings

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListNotificationsWithDefaultParameters(const FString& ForPlayerWithUlid, const FLootLockerListNotificationsResponseBP& OnComplete);

    /**
     List notifications according to specified filters and with pagination settings

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param ShowRead Return previously read notifications
     @param CustomNotificationsFilter (Optional) Whether to filter for custom, non custom, or all notifications
     @param OfType (Optional) Return only notifications with the specified type, if this is a custom notification then the type is set by the sender of the notification and must match pattern ^[a-z_-]+\.[a-z_-]+\.[a-z_-]+$
     @param WithSource (Optional) Return only notifications with the specified source
     @param PerPage (Optional) Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
     @param Page (Optional) Used together with Page to apply pagination to this request. PerPage designates how many notifications are considered a "page"
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid = ""))
    static void ListNotifications(const FString& ForPlayerWithUlid, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete);

    /**
     List notifications according to specified filters and with pagination settings

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param WithPriority Return only notifications with the specified priority
     @param ShowRead Return previously read notifications
     @param CustomNotificationsFilter (Optional) Whether to filter for custom, non custom, or all notifications
     @param OfType (Optional) Return only notifications with the specified type, if this is a custom notification then the type is set by the sender of the notification and must match pattern ^[a-z_-]+\.[a-z_-]+\.[a-z_-]+$
     @param WithSource (Optional) Return only notifications with the specified source
     @param PerPage (Optional) Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
     @param Page (Optional) Used together with Page to apply pagination to this request. PerPage designates how many notifications are considered a "page"
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListNotificationsWithPriority(const FString& ForPlayerWithUlid, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnComplete);

    /*
     Try to parse the body property from a notification content object as a String

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsString(const FLootLockerNotificationContent& Content, FString& OutValue);

    /*
     Try to parse the body property from a notification content object as a Float

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsFloat(const FLootLockerNotificationContent& Content, float& OutValue);

    /*
     Try to parse the body property from a notification content object as an Integer

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsInteger(const FLootLockerNotificationContent& Content, int& OutValue);

    /*
     Try to parse the body property from a notification content object as a Bool

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsBool(const FLootLockerNotificationContent& Content, bool& OutValue);

    /*
     Try to parse the body property from a notification content object as a Float Array

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsFloatArray(const FLootLockerNotificationContent& Content, TArray<float>& OutValue);

    /*
     Try to parse the body property from a notification content object as an Integer Array

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsIntegerArray(const FLootLockerNotificationContent& Content, TArray<int>& OutValue);

    /*
     Try to parse the body property from a notification content object as a Bool Array

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsBoolArray(const FLootLockerNotificationContent& Content, TArray<bool>& OutValue);

    /*
     Try to parse the body property from a notification content object as a Reward Notification

     @param Content The content object from which to parse the body
     @param OutValue If parsing succeeded, this will be populated with the parsed value
     @return Whether the parsing succeeded or not
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Notifications", meta = (ReturnDisplayName = "Success"))
    static bool TryGetContentBodyAsRewardNotification(const FLootLockerNotificationContent& Content, FLootLockerNotificationContentRewardBody& OutValue);


    /**
     Mark all unread notifications as read

     Warning: This will mark ALL unread notifications as read, so if you have listed notifications but due to filters and/or pagination not pulled all of them you may have unviewed unread notifications

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void MarkAllNotificationsAsRead(const FString& ForPlayerWithUlid, const FLootLockerReadNotificationsResponseBP& OnComplete);

    /**
     Mark the specified notifications as read (if they are currently unread)

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param Notifications List of ids of notifications to mark as read
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void MarkNotificationsAsRead(const FString& ForPlayerWithUlid, const TArray<FLootLockerNotification>& Notifications, const FLootLockerReadNotificationsResponseBP& OnComplete);

    /**
     Mark the specified notifications as read

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param NotificationIDs List of ids of notifications to mark as read
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void MarkNotificationsAsReadByIds(const FString& ForPlayerWithUlid, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnComplete);

    /**
    * Get notifications by their identifying value. The out is an array because many notifications are not unique. For example triggers that can be triggered multiple times.
    * For Triggers the identifying value is the key of the trigger
    * For Google Play Store purchases it is the product id
    * For Apple App Store purchases it is the transaction id
    * For Steam Store purchases it is the entitlement id
    * For LootLocker virtual purchases it is the catalog item id
    * For Twitch Drops it is the Twitch reward id
    * For custom notifications (notifications with the field Custom = true and with the source being either LootLocker Console or LootLocker Server API) the content of the notification is defined by the sender, so the identifying value is simply the Notification type matching the pattern ^[a-z0-9_-]+\.[a-z0-9_-]+\.[a-z0-9_-]+$
    *
    * @param NotificationsResponse The response from which you want to find the notifications.
    * @param IdentifyingValue The identifying value of the notification you want to fetch.
    * @param Notifications A list of notifications that were found for the given identifying value or null if none were found.
    * @returns True if notifications were found for the identifying value. False if notifications couldn't be found for this value or if the underlying lookup table is corrupt.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Notifications", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static bool TryGetNotificationsByIdentifyingValue(const FLootLockerListNotificationsResponse& NotificationsResponse, const FString& IdentifyingValue, TArray<FLootLockerNotification>& Notifications);

    //==================================================
    //Collectables
    // https://ref.lootlocker.com/game-api/#collectables
    //==================================================

    /**
     * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
     * https://ref.lootlocker.com/game-api/#getting-collectables
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetAllCollectablesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllCollectables(const FString& ForPlayerWithUlid, const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted);

    /**
     * Collect an item.
     * https://ref.lootlocker.com/game-api/#collecting-an-item
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Item The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
     * @param OnCollectItemCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CollectItem(const FString& ForPlayerWithUlid, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted);

    //==================================================
    //Messages
    // https://ref.lootlocker.com/game-api/#messages
    //==================================================

    /**
     * Get all messages for a player.
     * https://ref.lootlocker.com/game-api/#get-messages
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetMessagesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Messages", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMessages(const FString& ForPlayerWithUlid, const FMessagesResponseDelegateBP& OnGetMessagesCompleted);

    //==================================================
    //Leaderboard
    // https://ref.lootlocker.com/game-api/#leaderboards
    //==================================================

    /**
     * List leaderboards with details on each leaderboard
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Count Optional: The count of items you want to retrieve.
     * @param After Optional: Used for pagination, id from which the pagination starts from.
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = 50, After = 0, ForPlayerWithUlid=""))
    static void ListLeaderboards(const FString& ForPlayerWithUlid, int Count, int After, const FLootLockerListLeaderboardsResponseBP& OnCompletedRequestBP);

    /**
     * Get rank for single member for a leaderboard. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.com/game-api/#get-member-rank
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param LeaderboardKey the key of the leaderboard you want to connect to.
     * @param MemberId the id of player in the leaderboard
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMemberRank(const FString& ForPlayerWithUlid, FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseBP& OnCompletedRequestBP);

    /**
     * Get all leaderboards with member information on the ones the member is on, with rank and score, as well as player information if the leaderboard is of type player.
     * If metadata is enabled for the leaderboard, that will be returned in the response.
     * https://ref.lootlocker.com/game-api/#get-all-member-ranks
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param MemberId player_id if player type leaderboard, otherwise id used when submitting the score
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllMemberRanks(const FString& ForPlayerWithUlid, FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP);

    /**
     * Get rank for a set of members for a leaderboard. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.com/game-api/#get-by-list-of-members
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Members The ids of all leaderboard members you want to get info on.
     * @param LeaderboardKey the key of the leaderboard you want to connect to.
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetByListOfMembers(const FString& ForPlayerWithUlid, TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseBP& OnCompletedRequestBP);

    /**
     * Get list of members in rank range.
     * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.com/game-api/#get-score-list
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param LeaderboardKey the key of the leaderboard you want to connect to.
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetScoreList(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP);

    /**
     * Get list of members in rank range.
     * Maximum allowed members to query for at a time is currently 2000. If leaderboard is of type player a player will also be in the response.
     * https://ref.lootlocker.com/game-api/#get-score-list
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param LeaderboardKey the key of the leaderboard you need to connect to.
     * @param Count Number of members returned per page
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetScoreListInitial(const FString& ForPlayerWithUlid, FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseBP& OnCompletedRequestBP);

    /**
     * Submit score for member on leaderboard.
     * https://ref.lootlocker.com/game-api/#submit-score
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param MemberId The id of player in the leaderboard.
     * @param LeaderboardKey The key of the leaderboard you need to connect to.
     * @param Score The score to be submitted.
     * @param Metadata Metadata for the score, will be used if metadata is enabled for the leaderboard
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubmitScore(const FString& ForPlayerWithUlid, FString MemberId, FString LeaderboardKey, int Score, FString Metadata, const FLootLockerSubmitScoreResponseBP& OnCompletedRequestBP);

    /**
     * Query a leaderboard for which rank a specific score would achieve. Does not submit the score but returns the projected rank.
     *
     * @param LeaderboardKey The key of the leaderboard you need to connect to.
     * @param Score The score to use for the query.
     * @param OnCompletedRequestBP Delegate for handling the server response
     * @param ForPlayerWithUlid Optional: Execute the request for the specified player. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void QueryScore(const FString LeaderboardKey, const int Score, const FLootLockerSubmitScoreResponseBP & OnCompletedRequestBP, const FString& ForPlayerWithUlid = "");

    /**
     * Increment an existing score on a leaderboard by the given amount.
     *
     * @param MemberId Can be left blank if it is a player leaderboard, otherwise this is the identifier you wish to use for this score
     * @param LeaderboardKey The key of the leaderboard you need to connect to.
     * @param Amount The amount with which to increment the current score on the given leaderboard (can be positive or negative)
     * @param OnCompletedRequestBP Delegate for handling the server response
     * @param ForPlayerWithUlid Optional: Execute the request for the specified player. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void IncrementScore(FString MemberId, const FString LeaderboardKey, const int Amount, const FLootLockerSubmitScoreResponseBP & OnCompletedRequestBP, const FString& ForPlayerWithUlid = "");

    /**
    * List the archive of a specific Leaderboard,
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param LeaderboardKey the Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardArchiveResponseBP& OnCompletedRequestBP);

    /**
    * Get the specified Archive which includes details such as ranks, scores and rewards.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Key the Key of the Leaderboard you want the list of archives
    * @param Count Optional: The count of items you want to retrieve.
    * @param After Optional: Used for pagination, id from which the pagination starts from.
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailReponseBP& OnCompletedRequestBP);

    /**
    * Get details on a Leaderboard which contains the schedule, rewards and the details on rewards.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param LeaderboardKey the Key of the Leaderboard you want the list of archives
    * @param OnCompletedRequestBP Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetLeaderboardDetails(const FString& ForPlayerWithUlid, const FString& LeaderboardKey, const FLootLockerLeaderboardDetailsResponseBP& OnCompletedRequestBP);

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
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param TableId Drop table ID
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ComputeAndLockDropTable(const FString& ForPlayerWithUlid, int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP);

    /**
     * Picks drops from a locked drop table.
     * https://ref.lootlocker.com/game-api/#pick-drops-from-drop-table
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Picks List of the item IDs you want to pick. Submit empty list for no picks
     * @param TableId Drop table ID, needs to have been locked prior to this call
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void PickDropsFromDropTable(const FString& ForPlayerWithUlid, TArray<int> Picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP);

    //==================================================
    // Currencies
    // https://ref.lootlocker.com/game-api/#currencies
    //==================================================

    /**
     * Get a list of available currencies for the game
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Currency", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListCurrencies(const FString& ForPlayerWithUlid, const FLootLockerListCurrenciesResponseBP& OnCompletedRequest);

    /**
     * Get details about the specified currency
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CurrencyCode The code of the currency to get details for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Currency", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrencyDetails(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnCompletedRequest);

    /**
     * Get a list of the denominations available for a specific currency
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CurrencyCode The code of the currency to fetch denominations for
     * @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Currency", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrencyDenominationsByCode(const FString& ForPlayerWithUlid, const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnCompletedRequest);

    //==================================================
    // Balances
    // https://ref.lootlocker.com/game-api/#balances
    //==================================================

    /**
     * Get a list of balances in a specified wallet
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param WalletID Unique ID of the wallet to get balances for
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Balance", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListBalancesInWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnComplete);

    /**
     * Get information about a specified wallet
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param WalletID Unique ID of the wallet to get information for
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Balance", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetWalletByWalletID(const FString& ForPlayerWithUlid, const FString& WalletID, const FLootLockerGetWalletResponseBP& OnComplete);

    /**
     * Get information about a wallet for a specified holder
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param HolderULID ULID of the holder of the wallet you want to get information for
     * @param HolderType The type of the holder to get the wallet for
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Balance", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetWalletByHolderID(const FString& ForPlayerWithUlid, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnComplete);

    /**
     * Credit (increase) the specified amount of the provided currency to the provided wallet
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param WalletID Unique ID of the wallet to credit the given amount of the given currency to
     * @param CurrencyID Unique ID of the currency to credit
     * @param Amount The amount of the given currency to credit to the given wallet
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Balance", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreditBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnComplete);

    /**
     * Debit (decrease) the specified amount of the provided currency to the provided wallet
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param WalletID Unique ID of the wallet to debit the given amount of the given currency from
     * @param CurrencyID Unique ID of the currency to debit
     * @param Amount The amount of the given currency to debit from the given wallet
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Balance", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DebitBalanceToWallet(const FString& ForPlayerWithUlid, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnComplete);

    //==================================================
    // Catalogs
    //==================================================
    /**
     * List the catalogs available for the game
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Catalog", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListCatalogs(const FString& ForPlayerWithUlid, const FLootLockerListCatalogsResponseBP& OnComplete);

    /**
     * List the items available in a specific catalog
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param CatalogKey Unique Key of the catalog that you want to get items for
     * @param Count Optional: Amount of catalog items to receive. Use null to simply get the default amount.
     * @param After Optional: Used for pagination, this is the cursor to start getting items from. Use null to get items from the beginning. Use the cursor from a previous call to get the next count of items in the list.
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Catalog", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void ListCatalogItems(const FString& ForPlayerWithUlid, const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnComplete);

    /**
     * Inline the "data items" from a catalog response into the catalog items themselves
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Catalog")
    static TArray<FLootLockerInlinedCatalogEntry> ConvertCatalogToInlineItems(const FLootLockerListCatalogPricesResponse& Catalog);

    //==================================================
    // Entitlements
    //==================================================

    /**
     * List this player's historical entitlements
     * Use this to retrieve information on entitlements the player has received regardless of their origin (for example as an effect of progression, purchases, or leaderboard rewards)
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Count Optional: Amount of entitlement listings to receive. Use null to get the default amount.
     * @param After Optional: Used for pagination, this is the cursor to start getting items from. Use null to get items from the beginning. Use the cursor from a previous call to get the next count of items in the list.
     * @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Entitlements", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void ListEntitlements(const FString& ForPlayerWithUlid, int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnComplete);

    /**
    * Get information of an entitlement, its status and more data.
    * Use this to retrieve information on entitlements the player has received regardless of their origin (for example as an effect of progression, purchases, or leaderboard rewards)
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param EntitlementID: Is the identifying ID which the entitlement is connected to
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Entitlements", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEntitlement(const FString& ForPlayerWithUlid, const FString& EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnComplete);

    //==================================================
    // Feedback
    //==================================================

    /**
    * Get a list of Categories to use for giving feedback to players, this can be anything from reporting players, or giving feedback such as nice notes
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Feedback", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete);

    /**
    * Get a list of Categories to use for giving feedback to the game, this can be anything from reporting bugs, or giving feedback such as nice notes
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Feedback", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListGameFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete);

    /**
    * Get a list of Categories to use for giving feedback to User Generated Content, this can be anything from reporting inappropriate UGC content, or giving feedback such as nice notes about a UGC
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Feedback", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListUGCFeedbackCategories(const FString& ForPlayerWithUlid, const FLootLockerListFeedbackCategoryResponseBP& OnComplete);

    /**
    * Send feedback about a player
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Ulid is the ulid of who you're giving feedback about
    * @param Description is the text/reason of your feedback ("He is hacking", "He is a kind player!")
    * @param CategoryID is the ID of the category you're using for your feedback, use ListFeedbackCategories function to get the ids.
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Feedback", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SendPlayerFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete);

    /**
    * Send feedback about the game
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Description is the text/reason of your feedback ("Amazing game", "I found a bug here!")
    * @param CategoryID is the ID of the category you're using for your feedback, use ListFeedbackCategories function to get the ids.
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Feedback", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SendGameFeedback(const FString& ForPlayerWithUlid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete);

    /**
    * Send feedback about a ugc asset
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param Ulid is the ulid of the asset you're giving feedback about
    * @param Description is the text/reason of your feedback ("Amazing Level", "I found a bug here!")
    * @param CategoryID is the ID of the category you're using for your feedback, use ListFeedbackCategories function to get the ids.
    * @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Feedback", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SendUGCFeedback(const FString& ForPlayerWithUlid, const FString& Ulid, const FString& Description, const FString& CategoryID, const FLootLockerSendFeedbackResponseBP& OnComplete);

    //==================================================
    // Metadata
    //==================================================

    /**
    List the requested page of Metadata for the specified source with the specified pagination (if you don't specify pagination settings then default pagination will be used)


    @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata, note that if the source is self then this too should be set to "self"
    @param Page Optional: Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
    @param PerPage Optional: Used together with Page to apply pagination to this request.PerPage designates how many items are considered a "page"
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Page,PerPage,IgnoreFiles,ForPlayerWithUlid", Page = -1, PerPage = -1, IgnoreFiles = false, ForPlayerWithUlid=""))
    static void ListMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete);

    /**
    List the requested page of Metadata for the specified source that has all of the provided tags and paginate according to the supplied pagination settings (if you don't specify pagination settings then default pagination will be used)

    @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata, note that if the source is self then this too should be set to "self"
    @param Tags The tags that the requested metadata should have, only metadata matching *all of* the given tags will be returned
    @param Page Optional: Used together with PerPage to apply pagination to this request. Page designates which "page" of items to fetch
    @param PerPage Optional: Used together with Page to apply pagination to this request.PerPage designates how many items are considered a "page"
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Page,PerPage,Tags,IgnoreFiles,ForPlayerWithUlid", Page = -1, PerPage = -1, IgnoreFiles = false, ForPlayerWithUlid=""))
    static void ListMetadataWithTags(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FString>& Tags, const int Page, const int PerPage, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnComplete);

    /**
    Get Metadata for the specified source with the given key

    @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    @param Source The source type for which to request metadata
    @param SourceID The specific source id for which to request metadata, note that if the source is self then this too should be set to "self"
    @param Key The key of the metadata to fetch, use this to fetch metadata for a specific key for the specified source.
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "IgnoreFiles,ForPlayerWithUlid", IgnoreFiles = false, ForPlayerWithUlid=""))
    static void GetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnComplete);

    /**
    Get Metadata for the specified keys on the specified sources

    @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    @param SourcesAndKeysToGet The combination of sources to get keys for, and the keys to get for those sources
    @param IgnoreFiles Optional: Base64 values will be set to content_type "application/x-redacted" and the content will be an empty String. Use this to avoid accidentally fetching large data files.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "IgnoreFiles,ForPlayerWithUlid", IgnoreFiles = false, ForPlayerWithUlid=""))
    static void GetMultisourceMetadata(const FString& ForPlayerWithUlid, const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseBP& OnComplete);

    /*
     Parse a LootLocker Metadata Entry

     This is a convenience node that replaces switching on the metadata type and converting the values manually
     The output execution pin corresponding to the Entry Type will be triggered at which point the corresponding value pin for that type will be populated.
     If the entry could not be parsed, the OnError execution pin will be triggered and the ErrorMessage will be populated.

     @param Entry The entry to parse
     @param MetadataTypeSwitch Generated output execution pins for the possible metadata types
     @param StringValue The parsed String Value, populated if the OnString output pin was triggered
     @param IntegerValue The parsed integer Value, populated if the OnInteger output pin was triggered
     @param FloatValue The parsed decimal Value, populated if the OnFloat output pin was triggered
     @param NumberString The parsed Number String Value, populated if the OnNumber output pin was triggered
     @param BoolValue The parsed boolean Value, populated if the OnBool output pin was triggered
     @param JsonStringValue The parsed Json String Value, populated if the OnJsonString output pin was triggered
     @param Base64Value The parsed Base64 Value, populated if the OnBase64 output pin was triggered
     @param ErrorMessage An error message populated if the parsing failed and the OnError output pin was triggered
     @param OutEntry Outputs a reference to the entry that was parsed for convenience
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Metadata", meta = (ExpandEnumAsExecs = "MetadataTypeSwitch", AdvancedDisplay = "OutEntry"))
    static void ParseLootLockerMetadataEntry(const FLootLockerMetadataEntry& Entry,
        ELootLockerMetadataParserOutputTypes& MetadataTypeSwitch,
        FString& StringValue,
        int& IntegerValue,
        float& FloatValue,
        FString& NumberString,
        bool& BoolValue,
        FString& JsonStringValue,
        FLootLockerMetadataBase64Value& Base64Value,
        FString& ErrorMessage,
        FLootLockerMetadataEntry& OutEntry);

    /**
    Set the provided metadata for the specified source

    Use the provided Make<type>MetadataAction nodes when constructing the array of actions to perform.
    Note that a subset of the specified operations can fail without the full request failing. Make sure to check the errors array in the response.

    @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    @param Source The source type for which to set metadata
    @param SourceID The specific source id for which to set metadata
    @param MetadataToActionsToPerform List of actions to take during this set operation.
    @param OnComplete delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetMetadata(const FString& ForPlayerWithUlid, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseBP& OnComplete);

    /**
    Construct a Metadata Action consisting of a metadata entry with a String value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read" and "game_api.write"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerSetMetadataAction MakeMetadataActionString(ELootLockerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Decimal value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read" and "game_api.write"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerSetMetadataAction MakeMetadataActionFloat(ELootLockerMetadataActions Action, const FString& Key, const float& Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with an Integer value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read" and "game_api.write"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerSetMetadataAction MakeMetadataActionInteger(ELootLockerMetadataActions Action, const FString& Key, const int Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Bool value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read" and "game_api.write"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerSetMetadataAction MakeMetadataActionBool(ELootLockerMetadataActions Action, const FString& Key, const bool Value, const TArray<FString>& Tags, const TArray<FString>& Access);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Json value in string format

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read" and "game_api.write"
    @param Succeeded Output: True if the json string could be parsed as an array or object, false if it could not be parsed
    @param ConstructedEntry Output: A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static void MakeMetadataActionJson(ELootLockerMetadataActions Action, const FString& Key, const FString& Value, const TArray<FString>& Tags, const TArray<FString>& Access, bool& Succeeded, FLootLockerSetMetadataAction& ConstructedEntry);

    /**
    Construct a Metadata Action consisting of a metadata entry with a Base64 value

    @param Action The action to take for this set operation. Update and Delete operations will fail if the key does not exist. Create operation will fail if the key does exist.
    @param Key The key to perform this action towards
    @param Value The value to set for the specified key
    @param Tags The tags to apply to the specified key
    @param Access The access settings to apply to the specified key. None means that the game api can not read nor write this metadata entry (this is the default). But you can supply either or both of "game_api.read" and "game_api.write"
    @return A Metadata Action Object that you can use in the method SetMetadata
    */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Metadata", meta = (AdvancedDisplay = "Tags,Access", AutoCreateRefTerm = "Tags,Access"))
    static FLootLockerSetMetadataAction MakeMetadataActionBase64(ELootLockerMetadataActions Action, const FString& Key, const FLootLockerMetadataBase64Value& Value, const TArray<FString>& Tags, const TArray<FString>& Access);
    
    //==================================================
    // Followers
    //==================================================    

    /**
     * List followers for a specific player by public UID.
     * 
     * @param PlayerPublicUid The public UID of the player to list followers for
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFollowersForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * List followers for the requesting player.
     * 
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFollowers(const FString& ForPlayerWithUlid, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * List players that a specific player is following by public UID.
     * 
     * @param PlayerPublicUid The public UID of the player to list following for
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFollowingForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * List players that the requesting player is following.
     * 
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFollowing(const FString& ForPlayerWithUlid, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * Follow a player by public UID.
     * 
     * @param PlayerPublicUid The public UID of the player to follow
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void FollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP);

    /**
     * Unfollow a player by public UID.
     * 
     * @param PlayerPublicUid The public UID of the player to unfollow
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnfollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP);

    //==================================================
    // Friends
    //==================================================

    /** 
     * List friends for the requesting player.
     *
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFriends(const FString& ForPlayerWithUlid, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP);

    /**
     * List incoming friend requests for the requesting player.
     *
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListIncomingFriendRequests(const FString& ForPlayerWithUlid, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP);

    /**
     * List outgoing friend requests for the requesting player.
     *
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListOutgoingFriendRequests(const FString& ForPlayerWithUlid, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP);

    /**
     * Send a friend request to another player
     *
     * @param PlayerId The player ulid of the player to send the friend request to
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SendFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    /**
     * Delete a friend
     *
     * @param PlayerULID The player ulid of the player to delete
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteFriend(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    /**
     * Cancel outgoing friend request
     * 
     * @param PlayerULID The player ulid of the player to cancel the friend request for
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CancelOutgoingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    /**
     * Accept incoming friend request
     * 
     * @param PlayerULID The player ulid of the player to accept the friend request from
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AcceptIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    /**
     * Decline incoming friend request
     *
     * @param PlayerULID The player ulid of the player to decline the friend request from
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeclineIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    /**
     * List blocked players
     * 
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListBlockedPlayers(const FString& ForPlayerWithUlid, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP);

    /**
     * Block a player
     *
     * @param PlayerULID The player ulid of the player to block
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void BlockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    /**
     * Unblock a player
     *
     * @param PlayerULID The player ulid of the player to unblock
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnblockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    //==================================================
    // Miscellaneous
    //==================================================

    /**
    * Get the current time of the server. Can also be used to ping the server
    * https://ref.lootlocker.com/game-api/#server-time
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    * @param OnCompletedRequestBP Delegate for handling the the server response.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetServerTime(const FString& ForPlayerWithUlid, const FTimeResponseDelegateBP& OnCompletedRequestBP);

    /**
    * Get the last used platform from a prior session.
    *
    * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static FString GetLastActivePlatform(const FString& ForPlayerWithUlid);

    /**
    * Get meta information about the game from LootLocker
    * 
    * @param OnCompletedRequestBP Blueprint delegate for handling the response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous")
    static void GetGameInfo(const FGameInfoResponseDelegateBP& OnCompletedRequestBP);
};
