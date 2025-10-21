// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "GameAPI/LootLockerBroadcastRequestHandler.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"
#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "GameAPI/LootLockerDropTablesRequestHandler.h"
#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
#include "GameAPI/LootLockerFollowersRequestHandler.h"
#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardArchiveRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "GameAPI/LootLockerPurchasesRequestHandler.h"
#include "GameAPI/LootLockerRemoteSessionRequestHandler.h"
#include "GameAPI/LootLockerTriggersRequestHandler.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "LootLockerSessionOptionals.h"
#include "LootLockerSDKManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerSDKManager : public UObject
{
    GENERATED_BODY()

public:

    //==================================================
    // Player State
    //==================================================
    /**
     Get active player ULIDs since game start (or state initialization)

     @return Array of player ULIDs considered active since game start
     */
    static TArray<FString> GetActivePlayerUlids();

    /**
     Mark a player's state as inactive

     @param PlayerUlid ULID of the player to set inactive
     */
    static void SetPlayerUlidToInactive(const FString& PlayerUlid);

    /**
     Mark all currently active players as inactive
     */
    static void SetAllPlayersToInactive();

    /**
     Mark all players inactive except the specified player

     @param PlayerUlid ULID of the player to keep active
     */
    static void SetAllPlayersToInactiveExceptForPlayer(const FString& PlayerUlid);

    /**
     Get ULIDs that have a cached state

     @return Array of player ULIDs with cached state
     */
    static TArray<FString> GetCachedPlayerUlids();

    /**
     Get the default player ULID used when no player is specified

     @return ULID of the default player used for unspecified requests
     */
    static FString GetDefaultPlayerUlid();

    /**
     Set the default player state used when no player is specified

     @param PlayerUlid ULID of the player to set as default
     @return True if the operation succeeded; false otherwise
     */
    static bool SetDefaultPlayer(const FString& PlayerUlid);

    /**
     Get saved state for a player ULID (or default if none supplied; empty if neither exist)

     @param PlayerUlid ULID of the player to retrieve state for (empty uses default)
     @return Player state for the specified ULID, or the default player, or an empty state if none exist
     */
    static FLootLockerPlayerData GetSavedStateOrDefaultOrEmptyForPlayer(const FString& PlayerUlid);

    /**
     Clear cached state for the specified player (forces re-authentication)

     @param PlayerUlid ULID of the player whose cache to clear
     */
    static void ClearCacheForPlayer(const FString& PlayerUlid);

    /**
     Clear cached state for all players except the specified one

     @param PlayerUlid ULID of the player whose cache to retain
     */
    static void ClearAllPlayerCachesExceptForPlayer(const FString& PlayerUlid);

    /**
     Clear cached state for all players (forces re-authentication)
     */
    static void ClearAllPlayerCaches();

    //==================================================
    // Authentication
    //==================================================

    /**
     Add a player state manually from externally sourced data (e.g. after a server token exchange) without performing an authentication call.

     @param ForPlayer Player state to cache and use for future requests
     */
    static void StartSessionManual(const FLootLockerPlayerData& ForPlayer);

    /**
     Start a PlayStation Network session (Deprecated – use VerifyPlayerAndStartPlaystationNetworkSession).
     A game can support multiple platforms, but each build should typically target only one.

     @param PsnOnlineId PSN Online ID of the player
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    [[deprecated("This method is deprecated, please use VerifyPlayerAndStartPlaystationNetworkSession instead.")]] // Deprecation date 20250922
    static FString StartPlaystationNetworkSession(const FString& PsnOnlineId, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a PlayStation Network session (v1/v2). If your token starts with v3 use VerifyPlayerAndStartPlaystationNetworkV3Session.
     A game can support multiple platforms, but each build should typically target only one.

     @param AuthCode Authorization code received from PSN after login
     @param AccountID Numeric account id returned by PSN
     @param OnCompletedRequest Delegate for handling the server response
     @param PsnIssuerId Optional: PSN issuer id (default 256 = production)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, const FLootLockerSessionResponse& OnCompletedRequest, int PsnIssuerId = 256, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a PlayStation Network session (v3 flow – tokens starting with v3).
     A game can support multiple platforms, but each build should typically target only one.

     @param AuthCode Authorization code received from PSN (v3)
     @param OnCompletedRequest Delegate for handling the server response
     @param EnvIssuerId Optional: Environment issuer id (default 256 = production)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, const FLootLockerSessionResponse& OnCompletedRequest, int EnvIssuerId = 256, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for an Android user.
     A game can support multiple platforms, but each build should typically target only one.

     @param DeviceId Device identifier for the player
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartAndroidSession(const FString& DeviceId, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for an Amazon Luna user.
     A game can support multiple platforms, but each build should typically target only one.

     @param AmazonLunaGuid Amazon Luna GUID identifying the player
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartAmazonLunaSession(const FString& AmazonLunaGuid, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for a Steam user using a session ticket.
     Optionally specify a Steam App ID if multiple are configured for your game.
     A game can support multiple platforms, but each build should typically target only one.

     @param SteamSessionTicket Steam session ticket token
     @param OnCompletedRequest Delegate for handling the server response
     @param SteamAppId Optional: Specific Steam App ID to verify against (blank = default)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FLootLockerSessionResponse& OnCompletedRequest, const FString& SteamAppId = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for a Nintendo Switch user.
     The Nintendo Switch platform must be enabled for your game.

     @param NSAIdToken Nintendo Switch Account (NSA) id token
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartNintendoSwitchSession(const FString& NSAIdToken, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for an Xbox user.
     The Xbox platform must be enabled for your game.

     @param XboxUserToken Xbox user token
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartXboxSession(const FString& XboxUserToken, const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for a Google user (default platform).
     The Google sign-in platform must be enabled for your game.

     @param IdToken Google ID token
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartGoogleSession(const FString& IdToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for a Google user targeting a specific Google OAuth2 Client ID platform.
     The desired Google platform must be enabled for your game.

     @param IdToken Google ID token
     @param Platform Google OAuth2 client platform enum value
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh an existing Google session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Google platform must be enabled for your game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshGoogleSession(const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshGoogleSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest, Optionals); };

    /**
     Refresh an existing Google session using an explicit refresh token.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Google platform must be enabled for your game.

     @param RefreshToken Refresh token from StartGoogleSession
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshGoogleSession(const FString& RefreshToken, const FLootLockerGoogleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());
    
    /**
     Start a LootLocker session for a Google Play Games user.
     The Google Play Games platform must be enabled for your game.

     @param AuthCode Authorization code from Google Play Games sign-in
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartGooglePlayGamesSession(const FString& AuthCode, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh an existing Google Play Games session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Google Play Games platform must be enabled for your game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshGooglePlayGamesSession(const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshGooglePlayGamesSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest, Optionals); };

    /**
     Refresh an existing Google Play Games session using an explicit refresh token.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Google Play Games platform must be enabled for your game.

     @param RefreshToken Refresh token from StartGooglePlayGamesSession
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshGooglePlayGamesSession(const FString& RefreshToken, const FLootLockerGooglePlayGamesSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session using Sign in with Apple.
     The Apple sign-in platform must be enabled for your game.

     @param AuthorizationCode Authorization code provided by Apple
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartAppleSession(const FString& AuthorizationCode, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh an existing Sign in with Apple session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Apple sign-in platform must be enabled for your game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshAppleSession(const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshAppleSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest, Optionals); };

    /**
     Refresh an existing Sign in with Apple session using an explicit refresh token.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Apple sign-in platform must be enabled for your game.

     @param RefreshToken Refresh token from StartAppleSession
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshAppleSession(const FString& RefreshToken, const FLootLockerAppleSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session using Apple Game Center identity verification.
     The Apple platform must be enabled for your game.

     @param BundleId Apple Game Center bundle id of your app
     @param PlayerId Apple Game Center player id
     @param PublicKeyUrl Public key URL from Apple Game Center Identity Verification
     @param Signature Signature from Apple Game Center Identity Verification
     @param Salt Salt value from Apple Game Center Identity Verification
     @param Timestamp Timestamp from Apple Game Center Identity Verification
     @param OnStartedAppleGameCenterSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseDelegate& OnStartedAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh an existing Apple Game Center session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Apple platform must be enabled for your game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshAppleGameCenterSession(const FLootLockerAppleGameCenterSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshAppleGameCenterSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest, Optionals); };

    /**
     Refresh an existing Apple Game Center session using an explicit refresh token.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Apple platform must be enabled for your game.

     @param RefreshToken Refresh token from StartAppleGameCenterSession (resolved from stored data if empty)
     @param OnRefreshAppleGameCenterSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshAppleGameCenterSession(const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseDelegate& OnRefreshAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for an Epic Online Services (EOS) user.
     The Epic Games platform must be enabled for your game.

     @param IdToken EOS ID token
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartEpicSession(const FString& IdToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh an existing Epic session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Epic Games platform must be enabled for your game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshEpicSession(const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshEpicSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest, Optionals); };

    /**
     Refresh an existing Epic session using an explicit refresh token.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Epic Games platform must be enabled for your game.

     @param RefreshToken Refresh token from StartEpicSession (resolved from stored data if empty)
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshEpicSession(const FString& RefreshToken, const FLootLockerEpicSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for a Meta / Oculus user.
     The Meta platform must be enabled for your game.

     @param UserId User id received from Oculus
     @param Nonce Nonce received from Oculus
     @param OncompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseDelegate& OncompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh an existing Meta / Oculus session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Meta platform must be enabled for your game.

     @param OncompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshMetaSession(const FLootLockerMetaSessionResponseDelegate& OncompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshMetaSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OncompletedRequest, Optionals); };

    /**
     Refresh an existing Meta / Oculus session using an explicit refresh token.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Meta platform must be enabled for your game.

     @param RefreshToken Refresh token from StartMetaSession (resolved from stored data if empty)
     @param OncompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString RefreshMetaSession(const FString& RefreshToken, const FLootLockerMetaSessionResponseDelegate& OncompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a guest session. Optionally provide a custom unique player identifier (otherwise one will be generated).

     @param PlayerIdentifier Optional: Custom unique identifier to associate with this guest player (auto-generated if empty)
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString GuestLogin(const FLootLockerSessionResponse& OnCompletedRequest, const FString& PlayerIdentifier = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Start a LootLocker session for a Discord user.
     The Discord sign-in platform must be enabled for your game.

     @param AccessToken Access token from Discord OAuth
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    static FString StartDiscordSession(const FString& AccessToken, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Refresh a Discord session.

     HTTP 401 means the refresh token expired and a new login is required. Discord platform must be enabled.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Optionals Optional: Additional session options when starting the session
     */
    static FString RefreshDiscordSession(const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals()) { return RefreshDiscordSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest, Optionals); };

    /**
     Refresh a Discord session with an explicit refresh token.

     HTTP 401 means the refresh token expired and a new login is required.

     @param RefreshToken Refresh token from StartDiscordSession
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options when starting the session
     */
    static FString RefreshDiscordSession(const FString& RefreshToken, const FLootLockerDiscordSessionResponseDelegate& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     (Deprecated) Verify player identity for a platform before starting a session.

     @param PlatformToken Platform-specific token
     @param OnCompletedRequest Delegate for handling the server response
     @param Platform Optional: Explicit platform identifier override
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    [[deprecated("This method is deprecated, please use VerifyPlayerAndStartPlaystationNetworkSession or VerifyPlayerAndStartSteamSession instead.")]] // Deprecation date 20250922
    static FString VerifyPlayer(const FString& PlatformToken, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& Platform = FString(TEXT("")), const FString& ForPlayerWithUlid = "");

    /**
     End the active session (if any).

     Terminates the session; subsequent requests with its token return 401. Succeeds if a session existed or none were active.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString EndSession(const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Connected Accounts
    //==================================================
    /**
     List connected identity providers (Apple, Google, etc.).

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Disconnect a linked identity provider.

     @param AccountToDisconnect Provider to disconnect
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link a Google account.

     @param IdToken ID token from Google sign-in
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link a Google account for a specific Google platform.

     @param IdToken ID token from Google sign-in
     @param Platform Google OAuth2 client platform
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectGoogleAccount(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link an Apple account (REST sign-in).

     @param AuthorizationCode Authorization code from Apple sign-in
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link a Twitch account.

     @param AuthorizationCode Authorization code from Twitch sign-in
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectTwitchAccount(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link an Epic account.

     @param Token Token from Epic sign-in
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectEpicAccount(const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link a PlayStation account.

     @param Environment PlayStation environment (e.g. prod, dev, qa)
     @param Code Authorization code (parameter missing in original doc)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectPlaystationAccount(const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link a Discord account.

     @param Token Token from Discord sign-in
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectDiscordAccount(const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Link an account via remote session lease.

     @param Code Lease code from start remote session
     @param Nonce Nonce from start remote session
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ConnectRemoteSessionAccount(const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Transfer identity providers between two authenticated players.

     Destructive: providers move from source to target player. Entire operation fails if any provider cannot be transferred.

     Limitations:
      - Source must own each provider
      - Target must not already have provider
      - Provider must be active in game settings

     @param FromPlayerWithUlid Source player ULID
     @param ToPlayerWithUlid Target player ULID
     @param ProvidersToTransfer Providers to transfer
     @param OnComplete Delegate for handling the server response
     */
    static FString TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid, const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete);

    //==================================================
    // Remote Sessions
    //==================================================

    /**
     Start a remote session lease process.

     Provides lease info, polls status, then returns success or failure.

     @param RemoteSessionLeaseInformation Called once with lease info for secondary device
     @param RemoteSessionLeaseStatusUpdate Called periodically with status updates
     @param OnComplete Called when process completes (success or failure)
     @param PollingIntervalSeconds Optional: Status polling interval seconds
     @param TimeOutAfterMinutes Optional: Max duration minutes before timeout
     @return Remote session process id
     */
    static FString StartRemoteSession(
        const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
        const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
        const FLootLockerStartRemoteSessionResponseDelegate& OnComplete,
        float PollingIntervalSeconds = 1.0f,
        float TimeOutAfterMinutes = 5.0f);

    /**
     Start a remote session lease process for linking into a specific player.

     @param ForPlayerWithUlid Player ULID to link into
     @param RemoteSessionLeaseInformation Called once with lease info for secondary device
     @param RemoteSessionLeaseStatusUpdate Called periodically with status updates
     @param OnComplete Called when process completes (success or failure)
     @param PollingIntervalSeconds Optional: Status polling interval seconds
     @param TimeOutAfterMinutes Optional: Max duration minutes before timeout
     @return Remote session process id
     */
    static FString StartRemoteSessionForLinking(
        const FString& ForPlayerWithUlid,
        const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
        const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
        const FLootLockerStartRemoteSessionResponseDelegate& OnComplete,
        float PollingIntervalSeconds = 1.0f,
        float TimeOutAfterMinutes = 5.0f);

    /**
     Cancel a remote session process.

     @param ProcessID Remote session process id
     */
    static void CancelRemoteSessionProcess(const FString& ProcessID);

    /**
     Refresh a remotely started session.

     401 means the refresh token expired and a new login is required.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RefreshRemoteSession(const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "") { return RefreshRemoteSession(GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid).RefreshToken, OnCompletedRequest); };

    /**
     Refresh a remotely started session with explicit refresh token.

     401 means the refresh token expired and a new login is required.

     @param RefreshToken Refresh token from StartRemoteSession
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegate& OnCompletedRequest);

    //==================================================
    // White Label
    //==================================================

    /**
     Create a White Label user.

     White Label platform must be enabled.

     @param Email User email
     @param Password User password
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate& OnCompletedRequest);

    /**
     Log in a White Label user (without starting session).

     Use WhiteLabelLoginAndStartSession unless you need manual control. Set Remember=true to prolong lifetime.

     @param Email Account email
     @param Password Account password
     @param OnCompletedRequest Delegate for handling the server response
     @param Remember Optional: Prolong session lifetime
     */
    static FString WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegate& OnCompletedRequest, const bool Remember = false);

    /**
     Start a session using cached White Label credentials.

     Use WhiteLabelLoginAndStartSession unless manual control required.

     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options
     */
    static FString WhiteLabelStartSession(const FLootLockerSessionResponse& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Log in and start a session (White Label).

     @param Email Account email
     @param Password Account password
     @param OnCompletedRequest Delegate for handling the server response
     @param Remember Optional: Prolong session lifetime
     @param Optionals Optional: Additional session options
     */
    static FString WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegate& OnCompletedRequest, const bool Remember = false, const FLootLockerSessionOptionals& Optionals = FLootLockerSessionOptionals());

    /**
     Verify cached White Label session token.

     Use result to decide whether to start a session or prompt for login.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString WhiteLabelVerifySession(const FLootLockerWhiteLabelVerifySessionDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Request account verification email (by user id).

     @param UserId White Label user id
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     Request account verification email (by email).

     @param Email User email
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest);

    /**
     Request password reset email.

     @param Email User email
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString WhiteLabelRequestPasswordReset(const FString& Email, const FLootLockerDefaultDelegate& OnCompletedRequest);

    //==================================================
    // Player calls
    //==================================================

    /**
     Get current player profile information (ids, name and identifiers) for subsequent requests.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCurrentPlayerInfo(const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List profile information for multiple players.

     @param PlayerIdsToLookUp Array of player ULIDs to look up
     @param PlayerLegacyIdsToLookUp Array of legacy integer player ids to look up
     @param PlayerPublicUidsToLookUp Array of public player UIDs to look up
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListPlayerInfo(TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get all inventory asset instances owned by the player.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetInventory(const FInventoryResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a paginated segment of the player's inventory starting after a given asset instance id.

     @param OnCompletedRequest Delegate for handling the server response
     @param StartIndex Pagination pointer; returns items after this asset instance id
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetFullInventory(const FInventoryResponse & OnCompletedRequest, int32 StartIndex, const FString& ForPlayerWithUlid = "");

    /**
     Get assets granted to the player since the last activation notification check.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the player's current credit / currency balance.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCurrencyBalance(const FPBalanceResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Initiate a DLC migration for the current player. Poll asset notifications after ~5 minutes for results.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString InitiateDLCMigration(const FResponseCallback & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List DLC identifiers migrated for the player (always returned as strings regardless of numeric value).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetDLCsMigration(const FPDlcResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Set the player's profile visibility to private (inventory not publicly visible on external platforms).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SetProfilePrivate(const FResponseCallback & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Set the player's profile visibility to public (inventory may be displayed on external platforms).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SetProfilePublic(const FResponseCallback & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Set (or change) the player's display name.

     @param Name New player display name
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SetPlayerName(FString Name, const FPNameResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the player's current display name.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetPlayerName(const FPNameResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Look up multiple player names on their last active platform (Deprecated – use LookupMultiplePlayersDataUsingIDs).

     @param Request Payload containing platform and id combinations to search
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    [[deprecated("This method is deprecated in favor of method LookupMultiplePlayersDataUsingIDs")]] // Deprecation date 20250304
    static FString LookupMultiplePlayerNamesUsingIDs(const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNames& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Look up multiple players' data using various identifier types.

     @param Request Payload containing platforms and ids for player data lookup
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString LookupMultiplePlayersDataUsingIDs(const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNames& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Look up player names using first-platform player ids and/or public UIDs.

     @param Request Payload containing player ids and/or public UIDs
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest & Request, const FPMultiplePlayersPlatformIdsNames & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Mark the player for deletion (permanently removed after a 30 day grace period).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeletePlayer(const FLootLockerDefaultDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Files
    //==================================================

    /**
     Upload a file owned by the player (initial creation).
     Use UpdateFile to modify existing files.

     @param Request File upload request payload
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UploadFile(const FLootLockerFileUploadRequest & Request, const FLootLockerUploadFileDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Update an existing player-owned file with new content or metadata.

     @param FileId File id (retrieved from upload response or ListFiles)
     @param Request File update request payload
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest & Request, const FLootLockerUploadFileDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List all files owned by the player.

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFiles(const FLootLockerFileListDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List all public files owned by another player (by legacy PlayerID).

     @param PlayerID Legacy player id of the target player
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Retrieve metadata (including access URL) for a single file.

     @param FileID File id (retrieved from upload response or ListFiles)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetSingleFile(const int32 FileID, const FLootLockerUploadFileDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Permanently delete a player-owned file (irreversible).

     @param FileID File id to delete (from upload response or ListFiles)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Player Progressions
    //==================================================

    /**
     List player progressions (paginated).

     @param Count Number of entries to receive
     @param After Pagination cursor (player progression id) to start after (use next_cursor / previous_cursor values)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetPlayerProgressions(const int32 & Count, const FString & After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List player progressions (first page only, limited by Count).

     @param Count Number of entries to receive
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetPlayerProgressions(const int32 & Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List player progressions (using server default pagination settings).

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetPlayerProgressions(const FLootLockerPaginatedPlayerProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Get a single progression state for the player.

     @param ProgressionKey Key of the progression to fetch
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetPlayerProgression(const FString & ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Add points to a player progression (may trigger rewards if thresholds are crossed).

     @param ProgressionKey Key of the progression to increment
     @param Amount Number of points to add
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddPointsToPlayerProgression(const FString & ProgressionKey, const int32 & Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Subtract points from a player progression.

     @param ProgressionKey Key of the progression to decrement
     @param Amount Number of points to subtract
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SubtractPointsFromPlayerProgression(const FString & ProgressionKey, const int32 & Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Reset a player progression to its initial state.

     @param ProgressionKey Key of the progression to reset
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ResetPlayerProgression(const FString & ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Delete a player progression (removes progress data for that progression).

     @param ProgressionKey Key of the progression to delete
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeletePlayerProgression(const FString & ProgressionKey, const FLootLockerDeleteProgressionDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progressions for another specified player (paginated).

     @param PlayerUlid ULID of the target player
     @param Count Number of entries to receive
     @param After Pagination cursor (player progression id) to start after
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the calling player ULID (default player if empty)
     */
    static FString GetOtherPlayersProgressions(const FString& PlayerUlid, const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progressions for another specified player (first page only, limited by Count).

     @param PlayerUlid ULID of the target player
     @param Count Number of entries to receive
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the calling player ULID (default player if empty)
     */
    static FString GetOtherPlayersProgressions(const FString& PlayerUlid, const int32& Count, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progressions for another specified player (server default pagination).

     @param PlayerUlid ULID of the target player
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the calling player ULID (default player if empty)
     */
    static FString GetOtherPlayersProgressions(const FString& PlayerUlid, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Get a single progression state for another specified player.

     @param PlayerUlid ULID of the target player
     @param ProgressionKey Key of the progression to fetch
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the calling player ULID (default player if empty)
     */
    static FString GetOtherPlayersProgression(const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Asset Instance Progressions   
    //==================================================

        /**
         List progressions the asset instance is on (paginated).

         @param AssetInstanceId Id of the asset instance
         @param Count Number of entries to receive
         @param After Pagination cursor (instance progression id) to start after (use next_cursor / previous_cursor)
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString & After, const FLootLockerPaginatedInstanceProgressionsResponseDelegate & OnComplete = FLootLockerPaginatedInstanceProgressionsResponseDelegate(), const FString& ForPlayerWithUlid = "");
        /**
         List progressions for an asset instance (first page only, limited by Count).

         @param AssetInstanceId Id of the asset instance
         @param Count Number of entries to receive
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString GetInstanceProgressions(const int32 AssetInstanceId, const int32 & Count, const FLootLockerPaginatedInstanceProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

        /**
         List progressions for an asset instance (server default pagination settings).

         @param AssetInstanceId Id of the asset instance
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString GetInstanceProgressions(const int32 AssetInstanceId, const FLootLockerPaginatedInstanceProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

        /**
         Get a single progression state for an asset instance.

         @param AssetInstanceId Id of the asset instance
         @param ProgressionKey Key of the progression to fetch
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString GetInstanceProgression(const int32 AssetInstanceId, const FString & ProgressionKey, const FLootLockerInstanceProgressionResponseDelegate & OnComplete = FLootLockerInstanceProgressionResponseDelegate(), const FString& ForPlayerWithUlid = "");

        /**
         Add points to an instance progression (may trigger rewards if thresholds are crossed).

         @param AssetInstanceId Id of the asset instance
         @param ProgressionKey Key of the progression to increment
         @param Amount Number of points to add
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString & ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate & OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate(), const FString& ForPlayerWithUlid = "");

        /**
         Subtract points from an instance progression.

         @param AssetInstanceId Id of the asset instance
         @param ProgressionKey Key of the progression to decrement
         @param Amount Number of points to subtract
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString & ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate & OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate(), const FString& ForPlayerWithUlid = "");

        /**
         Reset an instance progression to its initial state.

         @param AssetInstanceId Id of the asset instance
         @param ProgressionKey Key of the progression to reset
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString ResetInstanceProgression(const int32 AssetInstanceId, const FString & ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseDelegate & OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate(), const FString& ForPlayerWithUlid = "");

        /**
         Delete an instance progression (removes progress data for that progression).

         @param AssetInstanceId Id of the asset instance
         @param ProgressionKey Key of the progression to delete
         @param OnComplete Delegate for handling the server response
         @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
         */
    static FString DeleteInstanceProgression(const int32 AssetInstanceId, const FString & ProgressionKey, const FLootLockerDeleteProgressionDelegate & OnComplete = FLootLockerDeleteProgressionDelegate(), const FString& ForPlayerWithUlid = "");


    //==================================================
    // Heroes
    //==================================================

    /**
     List game hero templates (names and character info).

     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetGameHeroes(const FLootLockerGameHeroListDelegate & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     List heroes owned by the player.

     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListPlayerHeroes(const FLootLockerHeroListDelegate & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     List heroes owned by another player identified by SteamID64.

     @param SteamID64 SteamID64 of the target player
     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListOtherPlayersHeroesBySteamID64(const int64 SteamID64, const FLootLockerHeroListDelegate & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create a hero from a game hero template.

     @param Request Request containing template hero id and desired hero name
     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreateHero(const FLootLockerCreateHeroRequest & Request, const FLootLockerPlayerHeroDelegate & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create a hero with a specific variation and optional default flag.

     @param Request Request including template hero id, hero name, variation id and default flag
     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreateHeroWithVariation(const FLootLockerCreateHeroWithVariationRequest & Request, const FLootLockerPlayerHeroDelegate & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get information about a specific hero owned by the player.

     @param HeroID Id of the hero to fetch
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetHero(const int32 HeroID, const FLootLockerPlayerHeroDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the default hero for another player by SteamID64.

     @param SteamID64 SteamID64 of the target player
     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetOtherPlayersDefaultHeroBySteamID64(const int64 SteamID64, const FLootLockerPlayerHeroDelegate & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     Update a hero's name and/or mark it as the default hero.

     @param HeroID Id of the hero to update
     @param Request Request specifying new name and default flag
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UpdateHero(const int32 HeroID, const FLootLockerUpdateHeroRequest & Request, const FLootLockerPlayerHeroDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Delete a hero (irreversible; hero inventory is returned to player inventory and loadout reset).

     @param HeroID Id of the hero to delete
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteHero(const int32 HeroID, const FLLHeroDefaultResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List asset instances owned by the specified hero (first page only; endpoint is paginated).

     @param HeroID Id of the hero
     @param OnCompleteRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetHeroInventory(const int32 HeroID, const FInventoryResponse & OnCompleteRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the loadout (equipped items) for a hero owned by the player.

     @param HeroID Id of the hero
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the loadout for another player's hero.

     @param HeroID Id of the hero
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetOtherPlayersHeroLoadout(const int32 HeroID, const FHeroLoadoutReseponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Equip an existing asset instance to a hero.

     @param HeroID Id of the hero
     @param AssetInstanceID Id of the asset instance to equip
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Equip a global asset (default variation) to a hero.

     @param HeroID Id of the hero
     @param AssetID Id of the global asset
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddGlobalAssetToHeroLoadout(const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Equip a specific global asset variation to a hero.

     @param HeroID Id of the hero
     @param AssetID Id of the global asset
     @param AssetVariationID Variation id of the global asset
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddGlobalAssetVariationToHeroLoadout(const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Unequip an asset instance from a hero.

     @param HeroID Id of the hero
     @param AssetInstanceID Id of the asset instance to unequip
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RemoveAssetToHeroLoadout(const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Characters
    //==================================================

    /**
     List loadouts for all characters owned by the player including basic character info.
     Succeeds even if there are no characters (response may be empty).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCharacterLoadout(const FCharacterLoadoutResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Update a character's name and/or mark it as the default character.

     @param CharacterId Id of the character to update
     @param IsDefault Whether the character should become default
     @param Name New character name
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UpdateCharacter(int CharacterId, bool IsDefault, FString & Name, const FCharacterLoadoutResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create a character of a specified type and name (optionally set as default).
     Use ListCharacterTypes to enumerate available character types.

     @param IsDefault Whether the new character should be default
     @param CharacterName Character name
     @param CharacterTypeId Character type id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreateCharacter(bool IsDefault, const FString & CharacterName, const FString & CharacterTypeId, const FCharacterLoadoutResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Delete a character by id (irreversible) and return its equipped items to inventory.

     @param CharacterId Id of the character to delete
     @param OnCompletedRequestBP Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteCharacter(int CharacterId, const FLootLockerCharacterDefaultResponse& OnCompletedRequestBP, const FString& ForPlayerWithUlid = "");

    /**
     List character types configured for the game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListCharacterTypes(const FPLootLockerListCharacterTypesResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");


    /**
     Equip an asset instance to the player's default character.

     @param InstanceId Asset instance id (from inventory or loadout)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Equip an asset (by asset id and variation) to a specific character.

     @param CharacterId Id of the character
     @param AssetId Asset id
     @param AssetVariationId Asset variation id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Equip an asset instance to a specific character.

     @param CharacterId Id of the character
     @param InstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString EquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Unequip an asset instance from the player's default character.

     @param InstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Unequip an asset instance from a specific character.

     @param CharacterId Id of the character
     @param InstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the asset instances currently equipped on the player's default character.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the default character loadout for another player identified by a platform-specific id.

     @param OtherPlayerId Platform-specific id of the target player
     @param OnCompletedRequest Delegate for handling the server response
     @param OtherPlayerPlatform Optional: Platform the id refers to (if different than current)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetOtherPlayersCurrentLoadoutToDefaultCharacter(FString OtherPlayerId, const FCharacterLoadoutResponse & OnCompletedRequest, const FString & OtherPlayerPlatform = FString(TEXT("")), const FString& ForPlayerWithUlid = "");

    /**
     List equipable contexts (slots/categories) for the player's default character.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetEquipableContextsToDefaultCharacter(const FContextDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List equipable contexts for another player's character by character id.

     @param OtherCharacterId Target character id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetEquipableContextsByCharacterId(int OtherCharacterId, const FContextDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List characters owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListPlayerCharacters(const FPLootLockerListPlayerCharactersResponse & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get character loadouts for another player by platform-specific id.

     @param OtherPlayerId Platform-specific id of the target player
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OtherPlayerPlatform Optional: Platform the id refers to (if differing)
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString GetOtherPlayersCharacterLoadouts(const FString& OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid = "", const FString& OtherPlayerPlatform = "");

    /**
     Get character loadouts for another player by public UID.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OtherPlayerUid Public UID of the target player
     @param OnCompletedRequest Delegate for handling the server response
     */
    static FString GetOtherPlayersCharacterLoadoutsByUid(const FString& OtherPlayerUid, const FCharacterLoadoutResponse& OnCompletedRequest, const FString& ForPlayerWithUlid = "");


    //==================================================
    // Character Progressions
    //==================================================

    /**
     List progressions the character is currently on (paginated).

     @param CharacterId Id of the character
     @param Count Number of entries to return (page size)
     @param After Optional: Pagination cursor (previous character progression id); use next_cursor / previous_cursor from prior response
     @param OnComplete Delegate for handling the server response (paginated character progressions)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCharacterProgressions(const int32 & CharacterId, const int32 & Count, const FString & After, const FLootLockerPaginatedCharacterProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progressions the character is currently on (first page only).

     @param CharacterId Id of the character
     @param Count Number of entries to return
     @param OnComplete Delegate for handling the server response (paginated character progressions)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCharacterProgressions(const int32 & CharacterId, const int32 & Count, const FLootLockerPaginatedCharacterProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List all progressions the character is currently on (returns server default page size).

     @param CharacterId Id of the character
     @param OnComplete Delegate for handling the server response (paginated character progressions)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCharacterProgressions(const int32 & CharacterId, const FLootLockerPaginatedCharacterProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Get a single progression for the character by key.

     @param CharacterId Id of the character
     @param ProgressionKey Progression key
     @param OnComplete Delegate for handling the server response (character progression)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCharacterProgression(const int32 & CharacterId, const FString & ProgressionKey, const FLootLockerCharacterProgressionResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Add points to a character progression and return any threshold rewards granted.

     @param CharacterId Id of the character
     @param ProgressionKey Progression key
     @param Amount Points to add
     @param OnComplete Delegate for handling the server response (progression with rewards)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddPointsToCharacterProgression(const int32 & CharacterId, const FString & ProgressionKey, const int32 & Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Subtract points from a character progression and return any threshold rewards revoked (if applicable).

     @param CharacterId Id of the character
     @param ProgressionKey Progression key
     @param Amount Points to subtract
     @param OnComplete Delegate for handling the server response (progression with rewards)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SubtractPointsFromCharacterProgression(const int32 & CharacterId, const FString & ProgressionKey, const int32 & Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Reset a character progression to its initial state (points and level) and return any threshold rewards affected.

     @param CharacterId Id of the character
     @param ProgressionKey Progression key
     @param OnComplete Delegate for handling the server response (progression with rewards)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ResetCharacterProgression(const int32 & CharacterId, const FString & ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Delete a progression from the character (irreversible).

     @param CharacterId Id of the character
     @param ProgressionKey Progression key to delete
     @param OnComplete Delegate for handling the server response (delete progression)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteCharacterProgression(const int32 & CharacterId, const FString & ProgressionKey, const FLootLockerDeleteProgressionDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Persistent Storage
    //==================================================

    /**
     List all key/value pairs in the player's persistent storage (may return a large payload).
     Player Metadata will eventually replace Persistent Storage; prefer Metadata for new integrations.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a single key/value pair from the player's persistent storage.
     Player Metadata will eventually replace Persistent Storage; prefer Metadata for new integrations.

     @param Key Key to fetch
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetItemFromPersistentStorage(const FString & Key, const FPersistentStorageItemResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create or update multiple key/value pairs in persistent storage.
     Player Metadata will eventually replace Persistent Storage; prefer Metadata for new integrations.

     @param Items Items to create or update
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create or update a single key/value pair in persistent storage.
     Player Metadata will eventually replace Persistent Storage; prefer Metadata for new integrations.

     @param Item Item to create or update
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddItemsToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Delete a key/value pair from persistent storage.
     Player Metadata will eventually replace Persistent Storage; prefer Metadata for new integrations.

     @param Key Key of the key/value pair
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteItemFromPersistentStorage(const FString & Key, const FPersistentStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Read another player's public persistent storage key/value pairs.
     Player Metadata will eventually replace Persistent Storage; prefer Metadata for new integrations.

     @param PlayerId Player id or public UID
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetPlayerPersistentStorage(const FString & PlayerId, const FPersistentStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Assets
    //==================================================

    /**
     Get all the contexts the game has.
     
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetContexts(const FContextDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List assets (paginated) with optional filtering.

     @param OnCompletedRequest Delegate for handling the server response
     @param StartFromIndex Optional: Index of first item (default 0)
     @param ItemsCount Optional: Number of items (50-200, default 50)
     @param AssetFilter Optional: Asset filter (default None)
     @param Context Optional: Context id filter (default 0 = all)
     @param IncludeUGC Optional: Include UGC assets (default false)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAssets(const FAssetsResponseDelegate & OnCompletedRequest, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, int Context = 0, bool IncludeUGC = false, const FString& ForPlayerWithUlid = "");

    /**
     List universal assets (paginated).

     @param After Optional: Last universal asset id to start after
     @param ItemsCount Number of items to return (50-200)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetUniversalAssets(int After, int ItemsCount, const FUniversalAssetResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Retrieve specific assets by id.

     @param AssetIds Asset ids to fetch
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAssetsByIds(const TArray<int>&AssetIds, const FAssetsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List default bones and any binding overrides.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAssetBones(const FAssetBonesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List the player's favourite asset ids.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Add an asset to the player's favourites.

     @param AssetId Asset id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Remove an asset from the player's favourites.

     @param AssetId Asset id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Grant an asset (optionally with variation and rental option) to the player.

     @param AssetID Asset id to grant
     @param AssetVariationID Asset variation id (0 for none)
     @param AssetRentalOptionID Rental option id (0 for none)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GrantAssetToPlayerInventory(const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Grant an asset to the player (no variation or rental option).

     @param AssetID Asset id to grant
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GrantAssetToPlayerInventory(const int AssetID, const FGrantAssetResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "") {
        return GrantAssetToPlayerInventory(AssetID, 0, 0, OnCompletedRequest, ForPlayerWithUlid);
    }
    
    /**
     List assets with default pagination and no filters (lightweight helper).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListAssetsWithDefaultParameters(const FListSimpleAssetsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List assets returning only selected fields (performance focused).
     Use filters and field selection to minimize payload size.

     @param Request Field include/exclude and asset filtering settings
     @param OnCompletedRequest Delegate for handling the server response
     @param PerPage Optional: Page size (used with Page). Set 0 to disable pagination.
     @param Page Optional: Page index (1-based). Set 0 to disable pagination.
     @param OrderBy Optional: Field to order by
     @param OrderDirection Optional: Ordering direction
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListAssets(const FLootLockerListSimpleAssetsRequest& Request, const FListSimpleAssetsResponseDelegate & OnCompletedRequest, int PerPage = 0, int Page = 0, ELootLockerOrderAssetListBy OrderBy = ELootLockerOrderAssetListBy::None, ELootLockerOrderAssetListDirection OrderDirection = ELootLockerOrderAssetListDirection::None, const FString& ForPlayerWithUlid = "");


    //==================================================
    // Asset Instances
    //==================================================

    /**
     List all key/value pairs for an asset instance.

     @param AssetInstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a single key/value pair for an asset instance.

     @param AssetInstanceId Asset instance id
     @param StorageItemId Storage item id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create a key/value pair for an asset instance.

     @param AssetInstanceId Asset instance id
     @param Item Key/value pair to create
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem & Item, const FAssetInstanceStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Update one or more key/value pairs for an asset instance.

     @param AssetInstanceId Asset instance id
     @param Items Key/value pairs to update
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Update a single key/value pair for an asset instance by storage item id.

     @param AssetInstanceId Asset instance id
     @param StorageItemId Storage item id
     @param Item Storage item data
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Delete a key/value pair for an asset instance by storage item id.

     @param AssetInstanceId Asset instance id
     @param StorageItemId Storage item id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Inspect a loot box asset instance for drop rates and potential contents.

     @param AssetInstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Open a loot box asset instance (consumes the instance and grants contents).

     @param AssetInstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Delete an asset instance permanently from the player's inventory (irreversible).

     @param AssetInstanceID Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteAssetInstanceFromPlayerInventory(int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");


    //==================================================
    // User Generated Content
    //==================================================

    /**
     Create an asset candidate (UGC submission draft).

     @param AssetCandidateData Asset candidate data
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreateAssetCandidate(const FLootLockerCreateAssetCandidateData & AssetCandidateData, const FCreateAssetCandidateResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Create an asset candidate and immediately mark it completed for review.

     @param AssetCandidateData Asset candidate data
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreateAssetCandidateAndMarkComplete(const FLootLockerCreateAssetCandidateData & AssetCandidateData, const FCreateAssetCandidateResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Update an existing asset candidate.

     @param AssetCandidateId Asset candidate id
     @param AssetCandidateData Updated asset candidate data
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData & AssetCandidateData, const FAssetCandidateResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Delete an asset candidate (irreversible).

     @param AssetCandidateId Asset candidate id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List all asset candidates created by the player.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAllAssetCandidates(const FAssetCandidatesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a single asset candidate by id.

     @param AssetCandidateId Asset candidate id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Add a file to an asset candidate.

     @param AssetCandidateId Asset candidate id
     @param FilePath Absolute path to the file
     @param FilePurpose Purpose of the file
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AddFileToAssetCandidate(int AssetCandidateId, const FString & FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Remove a file from an asset candidate.

     @param AssetCandidateId Asset candidate id
     @param FileId File id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Progressions
    //==================================================

    /**
     List progressions (paginated).

     @param Count Number of entries to return (page size)
     @param After Optional: Pagination cursor (progression id to start after)
     @param OnComplete Delegate for handling the server response (paginated progressions)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgressions(const int32 & Count, const FString & After, const FLootLockerPaginatedProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progressions (first page only).

     @param Count Number of entries to return
     @param OnComplete Delegate for handling the server response (paginated progressions)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgressions(const int32 & Count, const FLootLockerPaginatedProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progressions (default page size, first page).

     @param OnComplete Delegate for handling the server response (paginated progressions)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgressions(const FLootLockerPaginatedProgressionsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Get a single progression by key.

     @param ProgressionKey Progression key
     @param OnComplete Delegate for handling the server response (progression)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgression(const FString & ProgressionKey, const FLootLockerProgressionResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progression tiers (paginated) for a progression.

     @param ProgressionKey Progression key
     @param Count Number of tiers to return (page size)
     @param After Optional: Pagination cursor (tier id); use next_cursor / previous_cursor from prior response
     @param OnComplete Delegate for handling the server response (paginated progression tiers)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgressionTiers(const FString & ProgressionKey, const int32 & Count, const int32 & After, const FLootLockerPaginatedProgressionTiersResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progression tiers (first page only) for a progression.

     @param ProgressionKey Progression key
     @param Count Number of tiers to return
     @param OnComplete Delegate for handling the server response (paginated progression tiers)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgressionTiers(const FString & ProgressionKey, const int32 & Count, const FLootLockerPaginatedProgressionTiersResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List progression tiers (default page size, first page) for a progression.

     @param ProgressionKey Progression key
     @param OnComplete Delegate for handling the server response (paginated progression tiers)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetProgressionTiers(const FString & ProgressionKey, const FLootLockerPaginatedProgressionTiersResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Missions
    //==================================================

    /**
     List all missions available to the player.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAllMissions(const FMissionsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a mission by id.

     @param MissionId Mission id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetMission(int MissionId, const FMissionResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Start a mission for the player.

     @param MissionId Mission id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString StartMission(int MissionId, const FStartMissionResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Finish a mission and submit completion data (rewards granted on success).

     @param MissionId Mission id
     @param MissionData Mission completion data
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString FinishMission(int MissionId, const FLootLockerFinishMissionData & MissionData, const FFinishMissionResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Maps
    //==================================================

    /**
     List maps configured for the game.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetMaps(const FGetMapsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Purchases
    //==================================================

    /**
     Activate a purchased rental asset so it becomes available to the player.

     @param AssetInstanceId Asset instance id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Purchase a single catalog item using a wallet.

     @param WalletId Wallet id to debit
     @param CatalogItemListingId Catalog item listing id to purchase
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString LootLockerPurchaseSingleCatalogItem(const FString & WalletId, const FString & CatalogItemListingId, const FLootLockerDefaultDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Purchase multiple catalog items (with quantities) using a wallet.

     @param WalletId Wallet id to debit
     @param ItemsToPurchase Items and quantities to purchase
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString LootLockerPurchaseCatalogItems(const FString & WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Redeem an Apple App Store transaction for the player.

     @param TransactionId Apple transaction id
     @param Sandboxed Optional: Redeem against sandbox store (default false)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RedeemAppleAppStorePurchaseForPlayer(const FString & TransactionId, const FLootLockerDefaultDelegate & OnCompletedRequest, bool Sandboxed = false, const FString& ForPlayerWithUlid = "");

    /**
     Redeem an Apple App Store transaction for a class.

     @param ClassId Class id to receive items
     @param TransactionId Apple transaction id
     @param Sandboxed Optional: Redeem against sandbox store (default false)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString & TransactionId, const FLootLockerDefaultDelegate & OnCompletedRequest, bool Sandboxed = false, const FString& ForPlayerWithUlid = "");

    /**
     Redeem a Google Play Store purchase for the player.

     @param ProductId Product id
     @param PurchaseToken Google Play purchase token
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RedeemGooglePlayStorePurchaseForPlayer(const FString & ProductId, const FString & PurchaseToken, const FLootLockerDefaultDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Redeem a Google Play Store purchase for a class.

     @param ClassId Class id
     @param ProductId Product id
     @param PurchaseToken Google Play purchase token
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString & ProductId, const FString & PurchaseToken, const FLootLockerDefaultDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Redeem Epic Games Store entitlements for the player.

     @param AccountId Epic account id
     @param BearerToken Epic bearer/auth token (server auth ticket)
     @param EntitlementIds Entitlement ids to redeem
     @param SandboxId Epic sandbox id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RedeemEpicStorePurchase(const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Redeem Epic Games Store entitlements for a character.

     @param CharacterId Character ULID
     @param AccountId Epic account id
     @param BearerToken Epic bearer/auth token
     @param EntitlementIds Entitlement ids to redeem
     @param SandboxId Epic sandbox id (use for sandbox purchases)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString RedeemEpicStorePurchaseForCharacter(const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

#ifdef LOOTLOCKER_BETA_PLAYSTATION_IAP
    /**
      Redeem a purchase that was made successfully towards the PlayStation Store for the current player
      
      @param TransactionId The transaction id from the PlayStation Store of the purchase to redeem
      @param AuthCode The authorization code from the PlayStation Store of the purchase to redeem
      @param EntitlementLabel The entitlement label configured in the NP service for the entitlement that this redemption relates to
      @param OnCompletedRequest Delegate for handling the server response
      @param ServiceLabel Optional: The NP service label
      @param ServiceName Optional: The abbreviation of the service name of the ASM service ID service that was used when configuring the serviceIds. Possible Values: pssdc, cce. Default Value: pssdc
      @param Environment Optional: The id of the environment you wish to make the request against. Allowed values: 1, 8, 256
      @param UseCount Optional: The use count for this redemption
    @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    //static FString RedeemPlayStationStorePurchase(const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ServiceLabel = "", const FString& ServiceName = "", const int Environment = -1, const int UseCount = -1, const FString& ForPlayerWithUlid = "");

    /**
      Redeem a purchase that was made successfully towards the PlayStation Store for a character that the current player owns
      
      @param CharacterId The ulid of the character to redeem this purchase for
      @param TransactionId The transaction id from the PlayStation Store of the purchase to redeem
      @param AuthCode The authorization code from the PlayStation Store of the purchase to redeem
      @param EntitlementLabel The entitlement label configured in the NP service for the entitlement that this redemption relates to
      @param OnCompletedRequest Delegate for handling the server response
      @param ServiceLabel Optional: The NP service label
      @param ServiceName Optional: The abbreviation of the service name of the ASM service ID service that was used when configuring the serviceIds. Possible Values: pssdc, cce. Default Value: pssdc
      @param Environment Optional: The id of the environment you wish to make the request against. Allowed values: 1, 8, 256
      @param UseCount Optional: The use count for this redemption
    @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    //static FString RedeemPlayStationStorePurchaseForCharacter(const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FLootLockerDefaultDelegate& OnCompletedRequest, const FString& ServiceLabel = "", const FString& ServiceName = "", const int Environment = -1, const int UseCount = -1, const FString& ForPlayerWithUlid = "");
#endif

    /**
     Begin a Steam purchase (player) that can later be finalized and redeemed.
     Use QuerySteamPurchaseRedemptionStatus for status; finalize with FinalizeSteamPurchaseRedemption when Approved.

     @param SteamId Steam user id
     @param Currency Currency code
     @param Language Language code
     @param CatalogItemId Catalog item id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString BeginSteamPurchaseRedemption(const FString & SteamId, const FString & Currency, const FString & Language, const FString & CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Begin a Steam purchase (class) to later finalize and redeem to that class.
     Use QuerySteamPurchaseRedemptionStatus for status; finalize with FinalizeSteamPurchaseRedemption when Approved.

     @param ClassId Class id
     @param SteamId Steam user id
     @param Currency Currency code
     @param Language Language code
     @param CatalogItemId Catalog item id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString & SteamId, const FString & Currency, const FString & Language, const FString & CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Query Steam purchase status for an entitlement (poll until Approved before finalizing).

     @param EntitlementId Entitlement id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString QuerySteamPurchaseRedemptionStatus(const FString & EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Finalize an Approved Steam purchase and redeem associated catalog items.

     @param EntitlementId Entitlement id (must be Approved)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString FinalizeSteamPurchaseRedemption(const FString & EntitlementId, const FLootLockerDefaultDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Triggers
    //==================================================

    /**
     Invoke triggers by key.

     The response includes lists of executed trigger keys and failed triggers (with reasons); a successful request may still contain failures—inspect inner results.

     @param KeysToInvoke Trigger keys to invoke
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString InvokeTriggersByKey(const TArray<FString>&KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Notifications
    //==================================================

    /**
     List notifications (default pagination, no filters).

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List notifications with filters (paginated).

     @param ShowRead Return only previously read notifications
     @param OfType Optional: Filter by notification type
     @param WithSource Optional: Filter by notification source
     @param CustomNotificationsFilter Optional: Filter for custom / non-custom / all
     @param PerPage Optional: Page size (0 to ignore pagination)
     @param Page Optional: Page index (ignored if PerPage == 0)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListNotifications(bool ShowRead, const FString & OfType, const FString & WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List notifications filtered by priority (paginated, other filters available).

     @param WithPriority Priority to filter by
     @param ShowRead Return only previously read notifications
     @param OfType Optional: Filter by notification type
     @param WithSource Optional: Filter by notification source
     @param CustomNotificationsFilter Optional: Filter for custom / non-custom / all
     @param PerPage Optional: Page size (0 to ignore pagination)
     @param Page Optional: Page index (ignored if PerPage == 0)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListNotificationsWithPriority(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString & OfType, const FString & WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /*
     Get the content body as a UStruct of your choice. Returns true if value could be parsed in which case Output contains the parsed UStruct, returns false if the value field was not present or not parseable.

     @param Content The notification content for which you want to get the body parsed as a UStruct.
     @param Output The UStruct object that you want to be filled with data if the body was successfully parsed.
     @return True if the body could be parsed as the provided UStruct
     */
    template<typename T>
    static bool TryGetNotificationContentBodyAsUStruct(const FLootLockerNotificationContent& Content, T& Output)
    {
        TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
        if (!Content.TryGetContentBodyAsJsonObject(jsonObject))
        {
            return false;
        }
        return FJsonObjectConverter::JsonObjectToUStruct<T>(jsonObject.ToSharedRef(), &Output, 0, 0);
    }

    /**
     Mark all unread notifications as read.
     Warning: Marks all unread notifications, including those not yet paged into the client.

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Mark specified notifications as read.

     @param Notifications Notifications to mark as read
     @param OnComplete Delegate for handling the response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString MarkNotificationsAsRead(const TArray<FLootLockerNotification>&Notifications, const FLootLockerReadNotificationsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Mark specified notifications as read by id.

     @param NotificationIDs Notification ids to mark as read
     @param OnComplete Delegate for handling the response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString MarkNotificationsAsReadByIds(const TArray<FString>&NotificationIDs, const FLootLockerReadNotificationsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Broadcasts
    //==================================================

    /**
     List top broadcast messages (default localization & pagination).

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListTopBroadcasts(const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List top broadcast messages with localization (default pagination).

     @param Languages Language codes for localized broadcasts
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListTopBroadcastsLocalized(const TArray<FString>& Languages, const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List broadcast messages chronologically (paginated, localized).

     @param Languages Language codes for localized broadcasts
     @param PerPage Broadcasts per page
     @param Page Page index
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListBroadcasts(const TArray<FString>& Languages, int32 PerPage, int32 Page, const FLootLockerListBroadcastsResponseDelegate& OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Collectables
    //==================================================

    /**
     List all collectables configured for the game (collectables -> groups -> items).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAllCollectables(const FCollectablesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Collect a collectable item.

     @param Item Item slug (Collectable.Group.Item)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CollectItem(const FLootLockerCollectItemPayload & Item, const FCollectablesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Messages
    //==================================================

    /**
     List all messages for the player.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetMessages(const FMessagesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Leaderboard
    //==================================================

    /**
     List leaderboards with their details.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListLeaderboards(const FLootLockerListLeaderboardsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "") {
        return ListLeaderboards(-1, 0, OnCompletedRequest, ForPlayerWithUlid);
    };

    /**
     List leaderboards (paginated) with details.

     @param Count Optional: Number of items to retrieve
     @param After Optional: Pagination cursor id to start after
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListLeaderboards(int Count, int After, const FLootLockerListLeaderboardsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get rank for a single member. If the leaderboard is player type, player info is included.

     @param LeaderboardKey Leaderboard key
     @param MemberId Member/player id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetMemberRank(FString LeaderboardKey, FString MemberId, const FLootLockerGetMemberRankResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get ranks for multiple members. If the leaderboard is player type, player info is included.

     @param Members Member/player ids to query
     @param LeaderboardKey Leaderboard key
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetByListOfMembers(TArray<FString> Members, FString LeaderboardKey, const FLootLockerGetByListOfMembersResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List ranked members (paginated). Max 2000 per request. Player info included for player leaderboards.

     @param LeaderboardKey Leaderboard key
     @param Count Members per page
     @param After Pagination cursor
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetScoreList(FString LeaderboardKey, int Count, int After, const FLootLockerGetScoreListResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List ranked members starting from top (initial page). Max 2000. Player info included for player leaderboards.

     @param LeaderboardKey Leaderboard key
     @param Count Members to return
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetScoreListInitial(FString LeaderboardKey, int Count, const FLootLockerGetScoreListResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Submit a score for a member.

     @param MemberId Member/player id (blank for player leaderboard to use default)
     @param LeaderboardKey Leaderboard key
     @param Score Score value
     @param Metadata Optional: Metadata (if enabled for leaderboard)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SubmitScore(FString MemberId, const FString LeaderboardKey, const int Score, FString Metadata, const FLootLockerSubmitScoreResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Query the projected rank for a hypothetical score (does not submit).

     @param LeaderboardKey Leaderboard key
     @param Score Score value to evaluate
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString QueryScore(const FString LeaderboardKey, const int Score, const FLootLockerSubmitScoreResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Increment an existing score by an amount (positive or negative).

     @param MemberId Member/player id (blank for player leaderboard default)
     @param LeaderboardKey Leaderboard key
     @param Amount Amount to add (or subtract if negative)
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString IncrementScore(FString MemberId, const FString LeaderboardKey, const int Amount, const FLootLockerSubmitScoreResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List all leaderboards with this member's rank/score (and player info for player leaderboards). Metadata included if enabled.

     @param MemberId Member/player id
     @param Count Members per page
     @param After Pagination cursor
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetAllMemberRanks(FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List archived versions of a leaderboard.

     @param LeaderboardKey Leaderboard key
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListLeaderboardArchive(const FString & LeaderboardKey, const FLootLockerLeaderboardArchiveResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a leaderboard archive (paginated entries with ranks, scores, rewards).

     @param Key Leaderboard key
     @param Count Optional: Entry count
     @param After Optional: Pagination cursor
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString GetLeaderboardArchive(const FString & Key, int Count, const FString & After, const FLootLockerLeaderboardArchiveDetailResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get a leaderboard archive (all entries).

     @param Key Leaderboard key
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString GetLeaderboardArchive(const FString & Key, const FLootLockerLeaderboardArchiveDetailResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "") { return GetLeaderboardArchive(Key, -1, "", OnCompletedRequest); }

    /**
     Get leaderboard details (schedule, rewards, reward details).

     @param LeaderboardKey Leaderboard key
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString GetLeaderboardDetails(const FString & LeaderboardKey, const FLootLockerLeaderboardDetailsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Drop Table
    //==================================================

    /**
     Compute and lock a drop table (generates drops for later pickup).

     @param TableId Drop table id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ComputeAndLockDropTable(const int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Pick selected drops from a locked drop table.

     @param Picks Item ids to pick (empty for no picks)
     @param TableId Locked drop table id
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString PickDropsFromDropTable(const TArray<int> Picks, const int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Currencies
    //==================================================

    /**
     List available game currencies.

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListCurrencies(const FLootLockerListCurrenciesResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get currency details.

     @param CurrencyCode Currency code
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCurrencyDetails(const FString & CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     List available denominations for a currency.

     @param CurrencyCode Currency code
     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetCurrencyDenominationsByCode(const FString & CurrencyCode, const FLootLockerListDenominationsResponseDelegate & OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Balances
    //==================================================

    /**
     List balances in a wallet.

     @param WalletID Wallet id
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListBalancesInWallet(const FString & WalletID, const FLootLockerListBalancesForWalletResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Get wallet information by wallet id.

     @param WalletID Wallet id
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetWalletByWalletID(const FString & WalletID, const FLootLockerGetWalletResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Get wallet information by holder ULID and type.

     @param HolderULID Holder ULID
     @param HolderType Holder type
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetWalletByHolderID(const FString & HolderULID, const ELootLockerWalletHolderTypes & HolderType, const FLootLockerGetWalletResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Credit (increase) a wallet balance.

     @param WalletID Wallet id
     @param CurrencyID Currency id
     @param Amount Amount to credit
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CreditBalanceToWallet(const FString & WalletID, const FString & CurrencyID, const FString & Amount, const FLootLockerCreditWalletResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Debit (decrease) a wallet balance.

     @param WalletID Wallet id
     @param CurrencyID Currency id
     @param Amount Amount to debit
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DebitBalanceToWallet(const FString & WalletID, const FString & CurrencyID, const FString & Amount, const FLootLockerDebitWalletResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Catalogs
    //==================================================
    /**
     List game catalogs.

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListCatalogs(const FLootLockerListCatalogsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List catalog items (paginated).

     @param CatalogKey Catalog key
     @param Count Optional: Items to return (-1 or similar for default)
     @param After Optional: Pagination cursor (empty for start)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListCatalogItems(const FString & CatalogKey, int Count, const FString & After, const FLootLockerListCatalogPricesResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List catalog items (all/default page) for a catalog.

     @param CatalogKey Catalog key
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListCatalogItems(const FString & CatalogKey, const FLootLockerListCatalogPricesResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "") { return ListCatalogItems(CatalogKey, -1, "", OnComplete); }

    //==================================================
    // Entitlements
    //==================================================

    /**
     List player's historical entitlements (paginated, all origins: progression, purchases, rewards).

     @param Count Optional: Entries to return (-1 for default)
     @param After Optional: Pagination cursor (empty for start)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListEntitlements(int Count, const FString & After, const FLootLockerListEntitlementsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List player's historical entitlements (default pagination).

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListEntitlements(const FLootLockerListEntitlementsResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "") { return ListEntitlements(-1, "", OnComplete, ForPlayerWithUlid); }

    /**
     Get entitlement details.

     @param EntitlementID Entitlement id
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString GetEntitlement(const FString & EntitlementID, FLootLockerSingleEntitlementResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Feedback
    //==================================================

    /**
     List player feedback categories (for reporting or positive notes).

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListPlayerFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List game feedback categories.

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListGameFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     List UGC asset feedback categories.

     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListUGCFeedbackCategories(const FLootLockerListFeedbackCategoryResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Send feedback about a player.

     @param Ulid Player ULID being reported/praised
     @param Description Feedback text
     @param CategoryID Feedback category id (see list category calls)
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString SendPlayerFeedback(const FString & Ulid, const FString & Description, const FString & CategoryID, const FLootLockerSendFeedbackResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Send feedback about the game.

     @param Description Feedback text
     @param CategoryID Feedback category id
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString SendGameFeedback(const FString & Description, const FString & CategoryID, const FLootLockerSendFeedbackResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /**
     Send feedback about a UGC asset.

     @param Ulid UGC asset ULID
     @param Description Feedback text
     @param CategoryID Feedback category id
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString SendUGCFeedback(const FString & Ulid, const FString & Description, const FString & CategoryID, const FLootLockerSendFeedbackResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Metadata
    //==================================================

    /**
     List metadata (default pagination) for a source.

     @param Source Metadata source type
     @param SourceID Source id (use "self" when Source is self)
     @param OnComplete Delegate for handling the server response
     @param IgnoreFiles Optional: Redact file contents (empty payload with content_type application/x-redacted)
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListMetadata(const ELootLockerMetadataSources Source, const FString & SourceID, const FLootLockerListMetadataResponseDelegate & OnComplete, const bool IgnoreFiles = false, const FString& ForPlayerWithUlid = "");

    /**
     List metadata (paginated) for a source.

     @param Source Metadata source type
     @param SourceID Source id (use "self" when Source is self)
     @param Page Page index
     @param PerPage Items per page
     @param OnComplete Delegate for handling the server response
     @param IgnoreFiles Optional: Redact file contents
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListMetadata(const ELootLockerMetadataSources Source, const FString & SourceID, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate & OnComplete, const bool IgnoreFiles = false, const FString& ForPlayerWithUlid = "");

    /**
     List metadata with tags (default pagination). All specified tags must match.

     @param Source Metadata source type
     @param SourceID Source id
     @param Tags Tags required (must all be present)
     @param OnComplete Delegate for handling the server response
     @param IgnoreFiles Optional: Redact file contents
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString & SourceID, const TArray<FString>&Tags, const FLootLockerListMetadataResponseDelegate & OnComplete, const bool IgnoreFiles = false, const FString& ForPlayerWithUlid = "");

    /**
     List metadata with tags (paginated). All specified tags must match.

     @param Source Metadata source type
     @param SourceID Source id
     @param Tags Tags required
     @param Page Page index
     @param PerPage Items per page
     @param OnComplete Delegate for handling the server response
     @param IgnoreFiles Optional: Redact file contents
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString ListMetadataWithTags(const ELootLockerMetadataSources Source, const FString & SourceID, const TArray<FString>&Tags, const int Page, const int PerPage, const FLootLockerListMetadataResponseDelegate & OnComplete, const bool IgnoreFiles = false, const FString& ForPlayerWithUlid = "");

    /**
     Get metadata by key.

     @param Source Metadata source type
     @param SourceID Source id
     @param Key Metadata key
     @param OnComplete Delegate for handling the server response
     @param IgnoreFiles Optional: Redact file contents
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString GetMetadata(const ELootLockerMetadataSources Source, const FString & SourceID, const FString & Key, const FLootLockerGetMetadataResponseDelegate & OnComplete, const bool IgnoreFiles = false, const FString& ForPlayerWithUlid = "");

    /**
     Get metadata for multiple sources/keys.

     @param SourcesAndKeysToGet Sources and their keys
     @param OnComplete Delegate for handling the server response
     @param IgnoreFiles Optional: Redact file contents
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString GetMultisourceMetadata(const TArray<FLootLockerMetadataSourceAndKeys>&SourcesAndKeysToGet, const FLootLockerGetMultisourceMetadataResponseDelegate & OnComplete, const bool IgnoreFiles = false, const FString& ForPlayerWithUlid = "");

    /**
     Set metadata for a source. Some operations may fail independently; inspect errors array.

     @param Source Metadata source type
     @param SourceID Source id
     @param MetadataToActionsToPerform Metadata actions to perform
     @param OnComplete Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
    */
    static FString SetMetadata(const ELootLockerMetadataSources Source, const FString & SourceID, const TArray<FLootLockerSetMetadataAction>&MetadataToActionsToPerform, const FLootLockerSetMetadataResponseDelegate & OnComplete, const FString& ForPlayerWithUlid = "");

    /*
    Get the value as a UStruct of your choice. Returns true if value could be found in which case Output contains the parsed UStruct, returns false if the value field was not present or not parseable.

    @param Entry The entry for which you want to get the UStruct value.
    @param Output The UStruct object that you want to be filled with data if the value was successfully parsed.
    @return True if the value could be parsed as the provided UStruct
     */
    template<typename T>
    static bool TryGetMetadataValueAsUStruct(const FLootLockerMetadataEntry& Entry, T& Output)
    {
        TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
        if (!Entry.TryGetValueAsJsonObject(jsonObject))
        {
            return false;
        }
        return FJsonObjectConverter::JsonObjectToUStruct<T>(jsonObject.ToSharedRef(), &Output, 0, 0);
    }

    /*
    Factory method that makes an FLootLockerMetadataEntry with a UStruct Value

    @param Entry The key you want for this entry
    @param Tags The tags you want for this entry
    @param Access The access level you want to set for this entry
    @param Value The UStruct object that you to be converted to json and set as the value for this metadata entry
    @return The filled out metadata entry (or empty if it could not be constructed).
     */
    template<typename T>
    static FLootLockerMetadataEntry MakeMetadataEntryWithUStructValue(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const T& Value)
    {
        TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Value);
        if (!JsonObject.IsValid())
        {
            return FLootLockerMetadataEntry();
        }
        FLootLockerMetadataEntry Entry = FLootLockerMetadataEntry::MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Json);
        Entry.SetValueAsJsonObject(*JsonObject);
        return Entry;
    }
    
    //==================================================
    // Followers
    //==================================================    

    /**
     List followers for a player (by public UID).

     @param PlayerPublicId Player public UID
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowers(const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     List followers for the requesting player.

     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowers(const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    
    /**
     List followers for the requesting player (cursor paginated).

     @param Cursor Optional: Pagination cursor (empty for first page)
     @param Count Optional: Page size (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowersPaginated(const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    
    /**
     List followers for a player (cursor paginated).

     @param PlayerPublicId Player public UID
     @param Cursor Optional: Pagination cursor
     @param Count Optional: Page size (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowersPaginated(const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     List accounts a player is following (by public UID).

     @param PlayerPublicId Player public UID
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowing(const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     List accounts the requesting player is following.

     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowing(const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    /**
     List accounts the requesting player is following (cursor paginated).

     @param Cursor Optional: Pagination cursor (empty for first page)
     @param Count Optional: Page size (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowingPaginated(const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    /**
     List accounts a player is following (cursor paginated).

     @param PlayerPublicId Player public UID
     @param Cursor Optional: Pagination cursor
     @param Count Optional: Page size (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFollowingPaginated(const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Follow a player.

     @param PlayerPublicId Player public UID to follow
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString FollowPlayer(const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Unfollow a player.

     @param PlayerPublicId Player public UID to unfollow
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UnfollowPlayer(const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Friends
    //==================================================

    /**
     List friends for the requesting player.

     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFriends(const FLootLockerListFriendsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    /**
     List friends (page paginated).

     @param Page Optional: 1-based page index (<=0 uses 1)
     @param PerPage Optional: Items per page (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListFriendsPaginated(int32 Page, int32 PerPage, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     List incoming friend requests.

     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListIncomingFriendRequests(const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    /**
     List incoming friend requests (page paginated).

     @param Page Optional: 1-based page index (<=0 uses 1)
     @param PerPage Optional: Items per page (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListIncomingFriendRequestsPaginated(int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     List outgoing friend requests.

     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListOutgoingFriendRequests(const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    /**
     List outgoing friend requests (page paginated).

     @param Page Optional: 1-based page index (<=0 uses 1)
     @param PerPage Optional: Items per page (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListOutgoingFriendRequestsPaginated(int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Send a friend request.

     @param PlayerULID ULID of the player to request
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString SendFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Delete a friend.

     Removes the friend relationship for both players.

     @param PlayerULID Friend's ULID
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeleteFriend(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Cancel an outgoing friend request.

     @param PlayerULID ULID of the player whose request to cancel
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString CancelOutgoingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Accept an incoming friend request.

     @param PlayerULID ULID of the player whose request to accept
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString AcceptIncomingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Decline an incoming friend request.

     @param PlayerULID ULID of the player whose request to decline
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString DeclineIncomingFriendRequest(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     List blocked players.

     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListBlockedPlayers(const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");
    /**
     List blocked players (page paginated).

     @param Page Optional: 1-based page index (<=0 uses 1)
     @param PerPage Optional: Items per page (<=0 uses default)
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString ListBlockedPlayersPaginated(int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Get a friend by ULID.

     @param FriendUlid Friend ULID
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetFriend(const FString& FriendUlid, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Block a player.

     @param PlayerULID ULID of the player to block
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString BlockPlayer(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    /**
     Unblock a player.

     @param PlayerULID ULID of the player to unblock
     @param OnResponseCompleted Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString UnblockPlayer(const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted, const FString& ForPlayerWithUlid = "");

    //==================================================
    // Miscellaneous
    //==================================================

    /**
     Get current server time (ping).

     @param OnCompletedRequest Delegate for handling the server response
     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     */
    static FString GetServerTime(const FTimeResponseDelegate& OnCompletedRequest, const FString& ForPlayerWithUlid = "");

    /**
     Get the last active platform from a previous session.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @return Last active platform identifier (empty if none recorded)
     */
    static FString GetLastActivePlatform(const FString& ForPlayerWithUlid = "");

    /**
     Get game meta information.

     @param OnComplete Delegate for handling the server response
     */
    static FString GetGameInfo(const FGameInfoResponseDelegate& OnComplete);
};
