// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
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
#include "LootLockerSessionOptionals.h"
#include "LootLockerManager.generated.h"

UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerManager : public UObject
{
    GENERATED_BODY()

public:
    //==================================================
    // General Response Delegates
    //==================================================
    /** Blueprint response delegate for basic LootLocker responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDefaultResponseBP, FLootLockerResponse, Var);
    /** Blueprint response delegate for general LootLocker API responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FResponseCallbackBP, FLootLockerResponse, Response);
    /** Blueprint response delegate for standard LootLocker responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerResponseCallback, FLootLockerResponse, Response);
    /** Blueprint response delegate for getting context information */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FContextDelegateBP, FLootLockerGetContextResponse, ContextsResponse);

    //==================================================
    // Authentication Delegates
    //==================================================
    /** Blueprint response delegate for authentication responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAuthResponseBP, FLootLockerAuthenticationResponse, Var);
    /** Blueprint response delegate for Apple authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAppleSessionResponseBP, FLootLockerAppleSessionResponse, Var);
    /** Blueprint response delegate for Google authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FGoogleSessionResponseBP, FLootLockerGoogleSessionResponse, Var);
    /** Blueprint response delegate for Google Play Games authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FGooglePlayGamesSessionResponseBP, FLootLockerGooglePlayGamesSessionResponse, Var);
    /** Blueprint response delegate for Epic Games authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FEpicSessionResponseBP, FLootLockerEpicSessionResponse, Var);
    /** Blueprint response delegate for login responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLoginResponseDelegateBP, FLootLockerLoginResponse, AuthVar);
    /** Blueprint response delegate for session verification responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerVerifySessionResponseBP, FLootLockerWhiteLabelVerifySessionResponse, Response);
    /** Blueprint response delegate for white label login and session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP, FLootLockerWhiteLabelLoginAndSessionResponse, Var);
    /** Blueprint response delegate for Apple Game Center authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerAppleGameCenterSessionResponseBP, FLootLockerAppleGameCenterSessionResponse, Response);
    /** Blueprint response delegate for Meta authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerMetaSessionResponseBP, FLootLockerMetaSessionResponse, Var);
    /** Blueprint response delegate for Discord authentication session responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FDiscordSessionResponseBP, FLootLockerDiscordSessionResponse, Var);

    //==================================================
    // Connected Accounts Delegates
    //==================================================
    /**
     * Blueprint response delegate for connecting a provider to an account
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerAccountConnectedResponseBP, FLootLockerAccountConnectedResponse, Response);
    /**
     * Blueprint response delegate for listing connected accounts
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListConnectedAccountsResponseBP, FLootLockerListConnectedAccountsResponse, Response);

    //==================================================
    // Remote Session Delegates
    //==================================================
    /**
     * Blueprint response delegate for receiving the remote session lease information
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaseRemoteSessionResponseDelegateBP, FLootLockerLeaseRemoteSessionResponse, Response);
    /**
     * Blueprint response delegate for receiving continual polling updates
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerRemoteSessionStatusPollingResponseDelegateBP, FLootLockerRemoteSessionStatusPollingResponse, Response);
    /**
     * Blueprint response delegate for receiving the finalized remote session data (whether successful or not)
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerStartRemoteSessionResponseDelegateBP, FLootLockerStartRemoteSessionResponse, Response);
    /**
     * Blueprint response delegate for receiving the refreshed remote session
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerRefreshRemoteSessionResponseDelegateBP, FLootLockerRefreshRemoteSessionResponse, Response);

    //==================================================
    // Player Delegates
    //==================================================
    /** Blueprint response delegate for getting current player information */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetCurrentPlayerInfoResponseBP, FLootLockerGetCurrentPlayerInfoResponse, Value);
    /** Blueprint response delegate for listing player information */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListPlayerInfoResponseBP, FLootLockerListPlayerInfoResponse, Value);
    /** Blueprint response delegate for player inventory responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPInventoryResponseBP, FLootLockerInventoryResponse, Value);
    /** Blueprint response delegate for player asset notification responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPAssetNotificationResponseBP, FLootLockerPlayerAssetNotificationResponse, Value);
    /** Blueprint response delegate for player balance responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPBalanceResponseBP, FLootLockerBalanceResponse, Value);
    /** Blueprint response delegate for player DLC responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPDlcResponseBP, FLootLockerDlcResponse, Value);
    /** Blueprint response delegate for player name responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPNameResponseBP, FLootLockerNameResponse, Value);
    /** Blueprint response delegate for multiple player names responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPMultiplePlayerNamesBP, FLootLockerMultiplePlayersNamesResponse, Value);
    /** Blueprint response delegate for multiple players platform IDs responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPMultiplePlayersPlatformIdsBP, FLootLockerMultiplePlayersPlatformIdsResponse, Value);

    //==================================================
    // Player Files Delegates
    //==================================================
    /** Blueprint response delegate for uploading player files */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerUploadFileBP, FLootLockerPlayerFileResponse, Response);
    /** Blueprint response delegate for listing player files */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFileListBP, FLootLockerFileListResponse, Response);
    /** Blueprint response delegate for deleting player files */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFileDeletedBP, FLootLockerResponse, Response);

    //==================================================
    // Player Progression Delegates
    //==================================================
    /** Blueprint response delegate for player progression responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerProgressionResponseBP, FLootLockerPlayerProgressionResponse, Response);
    /** Blueprint response delegate for paginated player progressions responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedPlayerProgressionsResponseBP, FLootLockerPaginatedPlayerProgressionResponse, Response);
    /** Blueprint response delegate for player progression with rewards responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerProgressionWithRewardsResponseBP, FLootLockerPlayerProgressionWithRewardsResponse, Response);
    /** Blueprint response delegate for deleting player progression */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDeleteProgressionBP, FLootLockerResponse, Response);

    //==================================================
    // Hero Delegates
    //==================================================
    /** Blueprint response delegate for hero responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerHeroBP, FLootLockerHeroResponse, Response);
    /** Blueprint response delegate for game hero list responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGameHeroListBP, FLootLockerGameHeroListResponse, Response);
    /** Blueprint response delegate for hero list responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerHeroListBP, FLootLockerHeroListResponse, Response);
    /** Blueprint response delegate for player hero responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerHeroBP, FLootLockerPlayerHeroResponse, Response);
    /** Blueprint response delegate for hero default responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLLHeroDefaultResponseBP, FLootLockerResponse, Response);
    /** Blueprint response delegate for hero loadout responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FHeroLoadoutReseponseBP, FLootLockerHeroLoadoutResponse, Response);

    //==================================================
    // Character Delegates
    //==================================================
    /** Blueprint response delegate for character loadout responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterLoadoutResponseBP, FLootLockerCharacterLoadoutResponse, Var);
    /** Blueprint response delegate for character default responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPCharacterDefaultResponseBP, FLootLockerResponse, Var);
    /** Blueprint response delegate for listing character types responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPLootLockerListCharacterTypesResponseBP, FLootLockerListCharacterTypesResponse, Var);
    /** Blueprint response delegate for listing player characters responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPLootLockerListPlayerCharactersResponseBP, FLootLockerListPlayerCharactersResponse, Var);

    //==================================================
    // Character Progression Delegates
    //==================================================
    /** Blueprint response delegate for character progression responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCharacterProgressionResponseBP, FLootLockerCharacterProgressionResponse, Response);
    /** Blueprint response delegate for paginated character progressions responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedCharacterProgressionsResponseBP, FLootLockerPaginatedCharacterProgressionResponse, Response);
    /** Blueprint response delegate for character progression with rewards responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCharacterProgressionWithRewardsResponseBP, FLootLockerCharacterProgressionWithRewardsResponse, Response);

    //==================================================
    // Persistent Storage Delegates
    //==================================================
    /** Blueprint response delegate for persistent storage items responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegateBP, FLootLockerPersistentStorageItemsResponse, Response);
    /** Blueprint response delegate for persistent storage item responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemResponseDelegateBP, FLootLockerPersistentStorageItemResponse, Response);

    //==================================================
    // Asset Delegates
    //==================================================
    /** Blueprint response delegate for assets responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetsResponseDelegateBP, FLootLockerGetAssetsResponse, AssetsResponse);
    /** Blueprint response delegate for asset bones responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetBonesResponseDelegateBP, FLootLockerGetAssetBonesResponse, AssetBonesResponse);
    /** Blueprint response delegate for getting favourite asset indices responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FGetFavouriteAssetIndicesResponseDelegateBP, FLootLockerGetFavouriteAssetIndicesResponse, FavouriteAssetIndicesResponse);
    /** Blueprint response delegate for universal assets responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FUniversalAssetResponseDelegateBP, FLootLockerUniversalAssetsResponse, UniversalAssetsResponse);
    /** Blueprint response delegate for grant asset responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FGrantAssetResponseDelegateBP, FLootLockerGrantAssetResponse, Response);
    /** Blueprint response delegate for listing simple assets responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FListSimpleAssetsResponseDelegateBP, FLootLockerListSimpleAssetsResponse, Response);

    //==================================================
    // Asset Instance Delegates
    //==================================================
    /** Blueprint response delegate for asset instance storage items responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetInstanceStorageItemsResponseDelegateBP, FLootLockerAssetInstanceStorageItemsResponse, Response);
    /** Blueprint response delegate for asset instance storage item responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetInstanceStorageItemResponseDelegateBP, FLootLockerAssetInstanceStorageItemResponse, Response);
    /** Blueprint response delegate for loot box content responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootBoxContentResponseDelegateBP, FLootLockerLootBoxContentResponse, Response);
    /** Blueprint response delegate for opening loot box responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FOpenLootBoxResponseDelegateBP, FLootLockerOpenLootBoxResponse, Response);
    /** Blueprint response delegate for deleting asset instance responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FDeleteAssetInstanceResponseDelegateBP, FLootLockerDeleteAssetInstanceResponse, Response);

    //==================================================
    // User Generated Content Delegates
    //==================================================
    /** Blueprint response delegate for creating asset candidate responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FCreateAssetCandidateResponseDelegateBP, FLootLockerCreateAssetCandidateResponse, Response);
    /** Blueprint response delegate for asset candidate responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCandidateResponseDelegateBP, FLootLockerAssetCandidateResponse, Response);
    /** Blueprint response delegate for asset candidates responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCandidatesResponseDelegateBP, FLootLockerAssetCandidatesResponse, Response);

    //==================================================
    // Progression Delegates
    //==================================================
    /** Blueprint response delegate for progression responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerProgressionResponseBP, FLootLockerProgressionResponse, Response);
    /** Blueprint response delegate for paginated progressions responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedProgressionsResponseBP, FLootLockerPaginatedProgressionsResponse, Response);
    /** Blueprint response delegate for paginated progression tiers responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedProgressionTiersResponseBP, FLootLockerPaginatedProgressionTiersResponse, Response);

    //==================================================
    // Instance Progression Delegates
    //==================================================
    /** Blueprint response delegate for instance progression responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInstanceProgressionResponseBP, FLootLockerInstanceProgressionResponse, Response);
    /** Blueprint response delegate for paginated instance progressions responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedInstanceProgressionsResponseBP, FLootLockerPaginatedInstanceProgressionResponse, Response);
    /** Blueprint response delegate for instance progression with rewards responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInstanceProgressionWithRewardsResponseBP, FLootLockerInstanceProgressionWithRewardsResponse, Response);

    //==================================================
    // Mission Delegates
    //==================================================
    /** Blueprint response delegate for missions responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FMissionsResponseDelegateBP, FLootLockerMissionsResponse, Response);
    /** Blueprint response delegate for mission responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FMissionResponseDelegateBP, FLootLockerMissionResponse, Response);
    /** Blueprint response delegate for starting mission responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FStartMissionResponseDelegateBP, FLootLockerStartMissionResponse, Response);
    /** Blueprint response delegate for finishing mission responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FFinishMissionResponseDelegateBP, FLootLockerFinishMissionResponse, Response);

    //==================================================
    // Map Delegates
    //==================================================
    /** Blueprint response delegate for getting maps responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FGetMapsResponseDelegateBP, FLootLockerGetMapsResponse, Response);

    //==================================================
    // Purchase Delegates
    //==================================================
    /** Blueprint response delegate for activating rental asset responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FActivateRentalAssetResponseDelegateBP, FLootLockerActivateRentalAssetResponse, Response);
    /** Blueprint response delegate for beginning Steam purchase redemption responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerBeginSteamPurchaseRedemptionDelegateBP, FLootLockerBeginSteamPurchaseRedemptionResponse, Response);
    /** Blueprint response delegate for querying Steam purchase redemption status responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP, FLootLockerQuerySteamPurchaseRedemptionStatusResponse, Response);

    //==================================================
    // Trigger Delegates
    //==================================================
    /** Blueprint response delegate for invoking triggers by key responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInvokeTriggersByKeyResponseBP, FLootLockerInvokeTriggersByKeyResponse, Response);

    //==================================================
    // Notification Delegates
    //==================================================
    /** Blueprint response delegate for listing notifications responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListNotificationsResponseBP, FLootLockerListNotificationsResponse, Response);
    /** Blueprint response delegate for reading notifications responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerReadNotificationsResponseBP, FLootLockerReadNotificationsResponse, Response);

    //==================================================
    // Broadcast Delegates
    //==================================================
    /** Blueprint response delegate for listing broadcasts responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListBroadcastsResponseBP, FLootLockerListBroadcastsResponse, Response);
    /** Blueprint response delegate for internal listing broadcasts responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInternalListBroadcastsResponseBP, FLootLockerInternalListBroadcastsResponse, Response);

    //==================================================
    // Collectables Delegates
    //==================================================
    /** Blueprint response delegate for collectables responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FCollectablesResponseDelegateBP, FLootLockerCollectablesResponse, Response);

    //==================================================
    // Message Delegates
    //==================================================
    /** Blueprint response delegate for messages responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FMessagesResponseDelegateBP, FLootLockerMessagesResponse, Response);

    //==================================================
    // Leaderboard Delegates
    //==================================================
    /** Blueprint response delegate for listing leaderboards responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListLeaderboardsResponseBP, FLootLockerListLeaderboardsResponse, Response);
    /** Blueprint response delegate for getting member rank responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetMemberRankResponseBP, FLootLockerGetMemberRankResponse, Response);
    /** Blueprint response delegate for getting leaderboard by list of members responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetByListOfMembersResponseBP, FLootLockerGetByListOfMembersResponse, Response);
    /** Blueprint response delegate for getting score list responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetScoreListResponseBP, FLootLockerGetScoreListResponse, Response);
    /** Blueprint response delegate for submitting score responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSubmitScoreResponseBP, FLootLockerSubmitScoreResponse, Response);
    /** Blueprint response delegate for getting all member ranks responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetAllMemberRanksResponseBP, FLootLockerGetAllMemberRanksResponse, Response);
    /** Blueprint response delegate for leaderboard details responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaderboardDetailsResponseBP, FLootLockerLeaderboardDetailsResponse, Response);
    /** Blueprint response delegate for leaderboard archive responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaderboardArchiveResponseBP, FLootLockerLeaderboardArchiveResponse, Response);
    /** Blueprint response delegate for leaderboard archive detail responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaderboardArchiveDetailResponseBP, FLootLockerLeaderboardArchiveDetailsResponse, Response);

    //==================================================
    // Drop Table Delegates
    //==================================================
    /** Blueprint response delegate for computing and locking drop table responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerComputeAndLockDropTableResponseBP, FLootLockerComputeAndLockDropTableResponse, Response);
    /** Blueprint response delegate for picking drops from drop table responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FFLootLockerPickDropsFromDropTableResponseBP, FLootLockerPickDropsFromDropTableResponse, Response);

    //==================================================
    // Currency Delegates
    //==================================================
    /** Blueprint response delegate for listing currencies responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListCurrenciesResponseBP, FLootLockerListCurrenciesResponse, Response);
    /** Blueprint response delegate for getting currency details responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetCurrencyDetailsResponseBP, FLootLockerGetCurrencyDetailsResponse, Response);
    /** Blueprint response delegate for listing denominations responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListDenominationsResponseBP, FLootLockerListDenominationsResponse, Response);

    //==================================================
    // Balance Delegates
    //==================================================
    /** Blueprint response delegate for listing balances for wallet responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListBalancesForWalletResponseBP, FLootLockerListBalancesForWalletResponse, Response);
    /** Blueprint response delegate for getting wallet responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetWalletResponseBP, FLootLockerGetWalletResponse, Response);
    /** Blueprint response delegate for crediting wallet responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCreditWalletResponseBP, FLootLockerCreditWalletResponse, Response);
    /** Blueprint response delegate for debiting wallet responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDebitWalletResponseBP, FLootLockerDebitWalletResponse, Response);
    /** Blueprint response delegate for creating wallet responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCreateWalletResponseBP, FLootLockerCreateWalletResponse, Response);

    //==================================================
    // Catalog Delegates
    //==================================================
    /** Blueprint response delegate for listing catalogs responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListCatalogsResponseBP, FLootLockerListCatalogsResponse, Response);
    /** Blueprint response delegate for listing catalog prices responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListCatalogPricesResponseBP, FLootLockerListCatalogPricesResponse, Response);
    /** Blueprint response delegate for internal listing catalog prices responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FInternalLootLockerListCatalogPricesResponseBP, FInternalLootLockerListCatalogPricesResponse, Response);

    //==================================================
    // Entitlement Delegates
    //==================================================
    /** Blueprint response delegate for listing entitlements responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListEntitlementsResponseBP, FLootLockerEntitlementHistoryResponse, Response);
    /** Blueprint response delegate for single entitlement responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSingleEntitlementResponseBP, FLootLockerSingleEntitlementResponse, Response);

    //==================================================
    // Feedback Delegates
    //==================================================
    /** Blueprint response delegate for listing feedback categories responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListFeedbackCategoryResponseBP, FLootLockerFeedbackCategoryResponse, Response);
    /** Blueprint response delegate for sending feedback responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSendFeedbackResponseBP, FLootLockerResponse, Response);

    //==================================================
    // Metadata Delegates
    //==================================================
    /** Blueprint response delegate for listing metadata responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListMetadataResponseBP, FLootLockerListMetadataResponse, Response);
    /** Blueprint response delegate for getting metadata responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetMetadataResponseBP, FLootLockerGetMetadataResponse, Response);
    /** Blueprint response delegate for getting multisource metadata responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetMultisourceMetadataResponseBP, FLootLockerGetMultisourceMetadataResponse, Response);
    /** Blueprint response delegate for setting metadata responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSetMetadataResponseBP, FLootLockerSetMetadataResponse, Response);

    //==================================================
    // Follower Delegates
    //==================================================
    /** Blueprint response delegate for listing followers responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListFollowersResponseBP, FLootLockerListFollowersResponse, Response);
    /** Blueprint response delegate for follow action responses */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFollowActionResponseBP, FLootLockerFollowActionResponse, Response);

    //==================================================
    // Friend Delegates
    //==================================================
    /** Blueprint response delegate for listing friends */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListFriendsResponseBP, FLootLockerListFriendsResponse, Response);
    /** Blueprint response delegate for listing incoming friend requests */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListIncomingFriendRequestsResponseBP, FLootLockerListIncomingFriendRequestsResponse, Response);
    /** Blueprint response delegate for listing outgoing friend requests */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListOutgoingFriendRequestsResponseBP, FLootLockerListOutgoingFriendRequestsResponse, Response);
    /** Blueprint response delegate for actions taken towards the friends list */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFriendActionResponseBP, FLootLockerFriendActionResponse, Response);
    /** Blueprint response delegate for listing blocked players */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListBlockedPlayersResponseBP, FLootLockerListBlockedPlayersResponse, Response);
    /** Blueprint response delegate for getting a friend */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetFriendResponseBP, FLootLockerGetFriendResponse, Response);

    //==================================================
    // Miscellaneous Delegates
    //==================================================
    /**
     * Blueprint response delegate for fetching server time
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FTimeResponseDelegateBP, FLootLockerTimeResponse, Response);
    /**
     * Blueprint response delegate for fetching game info
     */
    DECLARE_DYNAMIC_DELEGATE_OneParam(FGameInfoResponseDelegateBP, FLootLockerGameInfoResponse, Response);

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
     Add a player state manually from externally sourced data (e.g. after a server side token exchange) without performing an authentication call.
     Use when you already possess valid session / refresh tokens and player metadata and just want to prime the local cache.

     @param SessionToken Session token to use for authenticated requests for this player
     @param PlayerUlid Unique ULID identifying the player whose state is being cached
     @param CurrentPlatform Platform / authentication method this session represents
     @param RefreshToken Optional: Refresh token used to renew the session when it expires
     @param PlayerIdentifier Optional: Player identifier used when the session was created
     @param PlayerPublicUid Optional: Public UID of the player
     @param PlayerName Optional: Display name of the player
     @param WhiteLabelEmail Optional: White Label email (only when platform is White Label)
     @param WhiteLabelToken Optional: Token identifying the current White Label session
     @param LastSignIn Optional: Timestamp string of when the player last authenticated
     @param PlayerCreatedAt Optional: Timestamp string of when the player account was created
     @param SessionOptionals Optional: Additional session option values associated with the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = 3, RefreshToken = "", PlayerIdentifier = "", PlayerUlid = "", PlayerPublicUid = "", PlayerName = "", WhiteLabelEmail = "", WhiteLabelToken = "", LastSignIn = "", PlayerCreatedAt = "", AutoCreateRefTerm = "SessionOptionals"))
    static void StartSessionManual(const FString& SessionToken, const FString& PlayerUlid, FLootLockerPlatformRepresentation CurrentPlatform, const FString& RefreshToken, const FString& PlayerIdentifier, const FString& PlayerPublicUid, const FString& PlayerName, const FString& WhiteLabelEmail, const FString& WhiteLabelToken, const FString& LastSignIn, const FString& PlayerCreatedAt, const FLootLockerSessionOptionals& SessionOptionals);

    /**
     Start a session for a PlayStation Network user (Deprecated – use VerifyPlayerAndStartPlaystationNetworkSession).
     A game can support multiple platforms, but it is recommended that a build only supports one platform per build.

     @param PsnOnlineId PSN Online ID of the player
     @param OnStartedSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (DeprecationMessage="This method is deprecated, please use VerifyPlayerAndStartPlaystationNetworkSession instead.", AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals")) // Deprecation date 2025-09-24
    static void StartPlaystationNetworkSession(const FString& PsnOnlineId, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a PlayStation Network session using an authorization code (v1/v2 flow). For v3 tokens (prefixed with v3) use VerifyPlayerAndStartPlaystationNetworkV3Session.
     A game can support multiple platforms, but each build should typically target only one.

     @param AuthCode Authorization code received from PSN after successful login
     @param AccountID Numeric account identifier returned by PSN
     @param OnCompletedRequest Delegate for handling the server response
     @param PsnIssuerId Optional: PSN issuer id to use (defaults to 256 = production) when verifying the player
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "PsnIssuerId,Optionals", PsnIssuerId = 256, AutoCreateRefTerm = "Optionals"))
    static void VerifyPlayerAndStartPlaystationNetworkSession(const FString& AuthCode, const FString& AccountID, const FAuthResponseBP& OnCompletedRequest, int PsnIssuerId, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a PlayStation Network session using the v3 authentication flow (tokens starting with v3 indicate this flow).
     A game can support multiple platforms, but each build should typically target only one.

     @param AuthCode Authorization code received from PSN (v3 flow)
     @param EnvIssuerId Optional: Environment issuer id to use (defaults to 256 = production)
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "EnvIssuerId,Optionals", EnvIssuerId = 256, AutoCreateRefTerm = "Optionals"))
    static void VerifyPlayerAndStartPlaystationNetworkV3Session(const FString& AuthCode, const FAuthResponseBP& OnCompletedRequest, int EnvIssuerId, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for an Android user.
     A game can support multiple platforms, but each build should typically target only one.

     @param DeviceId Device identifier for the player (e.g. generated unique device id)
     @param OnStartedSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartAndroidSession(const FString& DeviceId, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for an Amazon Luna user.
     A game can support multiple platforms, but each build should typically target only one.

     @param AmazonLunaGuid Amazon Luna GUID identifying the player
     @param OnStartedSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartAmazonLunaSession(const FString& AmazonLunaGuid, const FAuthResponseBP& OnStartedSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for a Steam user using a session ticket.
     Optionally specify a Steam App ID if multiple are configured for your game in the LootLocker console.
     A game can support multiple platforms, but each build should typically target only one.

     @param SteamSessionTicket Platform-specific Steam session ticket
     @param SteamAppId Optional: Specific Steam App ID to verify against (blank = default)
     @param OnCompletedRequest Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "SteamAppId,Optionals", SteamAppId = "", AutoCreateRefTerm = "Optionals"))
    static void StartSteamSessionUsingTicket(const FString& SteamSessionTicket, const FString& SteamAppId, const FAuthResponseBP& OnCompletedRequest, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for a Nintendo Switch user.
     The Nintendo Switch platform must be enabled for your game in the LootLocker web console.

     @param NSAIdToken Nintendo Switch Account (NSA) id token
     @param OnStartedNintendoSwitchSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartNintendoSwitchSession(const FString& NSAIdToken, const FAuthResponseBP& OnStartedNintendoSwitchSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for an Xbox user.
     The Xbox platform must be enabled for your game in the LootLocker web console.

     @param XboxUserToken Xbox user token
     @param OnStartedXboxSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartXboxSession(const FString& XboxUserToken, const FAuthResponseBP& OnStartedXboxSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session using Sign in with Apple.
     The Apple sign-in platform must be enabled for your game in the LootLocker web console.

     @param AuthorizationCode Authorization code provided by Apple
     @param OnStartedAppleSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartAppleSession(const FString& AuthorizationCode, const FAppleSessionResponseBP& OnStartedAppleSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Sign in with Apple session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Apple sign-in platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartAppleSession (resolved from stored data if empty)
     @param OnRefreshAppleSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", AutoCreateRefTerm = "Optionals"))
    static void RefreshAppleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FAppleSessionResponseBP& OnRefreshAppleSessionCompleted, const FLootLockerSessionOptionals& Optionals);

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
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartAppleGameCenterSession(const FString& BundleId, const FString& PlayerId, const FString& PublicKeyUrl, const FString& Signature, const FString& Salt, const FString& Timestamp, const FLootLockerAppleGameCenterSessionResponseBP& OnStartedAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Apple Game Center session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Apple platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartAppleGameCenterSession (resolved from stored data if empty)
     @param OnRefreshAppleGameCenterSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", AutoCreateRefTerm = "Optionals"))
    static void RefreshAppleGameCenterSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerAppleGameCenterSessionResponseBP& OnRefreshAppleGameCenterSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for a Google user (default platform).
     The Google sign-in platform must be enabled for your game.

     @param IdToken Google ID token for the player
     @param OnStartedGoogleSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartGoogleSession(const FString& IdToken, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for a Google user targeting a specific Google OAuth2 Client ID platform.
     The desired Google platform must be enabled for your game.

     @param IdToken Google ID token for the player
     @param Platform Google OAuth2 client platform enum value
     @param OnStartedGoogleSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartGoogleSessionForPlatform(const FString& IdToken, ELootLockerGoogleClientPlatform Platform, const FGoogleSessionResponseBP& OnStartedGoogleSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Google session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Google platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartGoogleSession (resolved from stored data if empty)
     @param OnRefreshGoogleSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", AutoCreateRefTerm = "Optionals"))
    static void RefreshGoogleSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGoogleSessionResponseBP& OnRefreshGoogleSessionCompleted, const FLootLockerSessionOptionals& Optionals);
    
    /**
     Start a LootLocker session for a Google Play Games user.
     The Google Play Games platform must be enabled for your game.

     @param AuthCode Authorization code from Google Play Games Sign-In
     @param OnStartedGooglePlayGamesSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartGooglePlayGamesSession(const FString& AuthCode, const FGooglePlayGamesSessionResponseBP& OnStartedGooglePlayGamesSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Google Play Games session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Google Play Games platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartGooglePlayGamesSession (resolved from stored data if empty)
     @param OnRefreshGooglePlayGamesSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", RefreshToken="", AutoCreateRefTerm = "Optionals"))
    static void RefreshGooglePlayGamesSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FGooglePlayGamesSessionResponseBP& OnRefreshGooglePlayGamesSessionCompleted, const FLootLockerSessionOptionals& Optionals);
    
    /**
     Start a LootLocker session for an Epic Online Services (EOS) user.
     The Epic Games platform must be enabled for your game.

     @param IdToken EOS id token for the player
     @param OnStartedEpicSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartEpicSession(const FString& IdToken, const FEpicSessionResponseBP& OnStartedEpicSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Epic session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Epic Games platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartEpicSession (resolved from stored data if empty)
     @param OnRefreshEpicSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", AutoCreateRefTerm = "Optionals"))
    static void RefreshEpicSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FEpicSessionResponseBP& OnRefreshEpicSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Start a LootLocker session for a Meta / Oculus user.
     The Meta platform must be enabled for your game.

     @param UserId User id received from Oculus
     @param Nonce Nonce received from Oculus
     @param OnMetaSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartMetaSession(const FString& UserId, const FString& Nonce, const FLootLockerMetaSessionResponseBP& OnMetaSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Meta / Oculus session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Meta platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartMetaSession (resolved from stored data if empty)
     @param OnRefreshMetaSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", AutoCreateRefTerm = "Optionals"))
    static void RefreshMetaSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerMetaSessionResponseBP& OnRefreshMetaSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Create a new user using the White Label login system.
     The White Label platform must be enabled for your game.

     @param Email Email for the new user
     @param Password Password for the new user
     @param OnWhiteLabelAccountCreationRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelCreateAccount(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelAccountCreationRequestCompleted);

    /**
     Log in a White Label user (email + password) and verify credentials without starting a LootLocker session.
     Prefer WhiteLabelLoginAndStartSession unless you intentionally need a separated flow.
     Set Remember=true to prolong session lifetime.

     @param Email Email for the White Label account
     @param Password Password for the White Label account
     @param OnWhiteLabelLoginRequestCompleted Delegate for handling the server response
     @param Remember Optional: Whether to prolong the session lifetime
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = 3))
    static void WhiteLabelLogin(const FString& Email, const FString& Password, const FLootLockerLoginResponseDelegateBP& OnWhiteLabelLoginRequestCompleted, const bool Remember = false);

    /**
     Start a LootLocker session using cached White Label credentials (token + email) if present.
     Prefer WhiteLabelLoginAndStartSession unless you intentionally need a separated flow.

     @param OnStartWhiteLabelSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void WhiteLabelStartSession(const FAuthResponseBP& OnStartWhiteLabelSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Log in and start a LootLocker session in a single step using a White Label account.
     Use this as the primary White Label authentication flow.

     @param Email Email for the White Label account
     @param Password Password for the White Label account
     @param OnWhiteLabelLoginAndStartSessionRequestCompleted Delegate for handling the server response
     @param Remember Optional: Whether to prolong the session lifetime
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void WhiteLabelLoginAndStartSession(const FString& Email, const FString& Password, const FLootLockerWhiteLabelLoginAndSessionResponseDelegateBP& OnWhiteLabelLoginAndStartSessionRequestCompleted, const bool Remember, const FLootLockerSessionOptionals& Optionals);

    /**
     Verify that a cached White Label session token (for the stored email) is still valid.
     Use the response to decide whether to start a session with WhiteLabelStartSession or prompt for login.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnVerifyWhiteLabelSessionRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void WhiteLabelVerifySession(const FString& ForPlayerWithUlid, const FLootLockerVerifySessionResponseBP& OnVerifyWhiteLabelSessionRequestCompleted);

    /**
     Request that a verification email is sent to the specified White Label user id.
     White Label and account verification must both be enabled for your game.

     @param UserId User id for the White Label user
     @param OnRequestWhiteLabelUserVerificationRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelRequestUserVerification(const int& UserId, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted);

    /**
     Request that a verification email is sent to the White Label user with the specified email.
     White Label and account verification must both be enabled for your game.

     @param Email Email of the White Label user
     @param OnRequestWhiteLabelUserVerificationRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelRequestUserVerificationByEmail(const FString& Email, const FLootLockerDefaultResponseBP& OnRequestWhiteLabelUserVerificationRequestCompleted);

    /**
     Request a password reset email for the specified White Label user email.
     The White Label platform must be enabled for your game.

     @param Email Email of the White Label user
     @param OnResetWhiteLabelPasswordRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void WhiteLabelResetPassword(const FString& Email, const FLootLockerDefaultResponseBP& OnResetWhiteLabelPasswordRequestCompleted);

    /**
     Start a guest session. Optionally provide a custom unique PlayerIdentifier (otherwise one will be generated).

     @param OnCompletedRequestBP Delegate for handling the server response
     @param PlayerIdentifier Optional: Custom unique identifier to associate with this guest player (auto-generated if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void GuestLogin(const FAuthResponseBP& OnCompletedRequestBP, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals);
    
    /**
     Start a LootLocker session for a Discord user.
     The Discord sign-in platform must be enabled for your game.

     @param AccessToken Access token from Discord OAuth
     @param OnStartedDiscordSessionRequestCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "Optionals", AutoCreateRefTerm = "Optionals"))
    static void StartDiscordSession(const FString& AccessToken, const FDiscordSessionResponseBP& OnStartedDiscordSessionRequestCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Refresh an existing Discord session.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new login is required.
     The Discord platform must be enabled for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartDiscordSession (resolved from stored data if empty)
     @param OnRefreshDiscordSessionCompleted Delegate for handling the server response
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid,Optionals", ForPlayerWithUlid="", RefreshToken="", AutoCreateRefTerm = "Optionals"))
    static void RefreshDiscordSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FDiscordSessionResponseBP& OnRefreshDiscordSessionCompleted, const FLootLockerSessionOptionals& Optionals);

    /**
     Verify the player's identity with the selected platform (Deprecated – use VerifyPlayerAndStartPlaystationNetworkSession or VerifyPlayerAndStartSteamSession).
     Required only if using the legacy separate verification + start session flow.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param PlatformToken Platform-specific authentication token
     @param OnVerifyPlayerRequestCompleted Delegate for handling the server response
     @param Platform Optional: Explicit platform name to verify against (auto-detected if empty)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication", meta = (DeprecationMessage="This method is deprecated, please use VerifyPlayerAndStartPlaystationNetworkSession or VerifyPlayerAndStartSteamSession instead.")) // Deprecation date 2025-09-24
    static void VerifyPlayer(const FString& ForPlayerWithUlid, const FString& PlatformToken, const FLootLockerDefaultResponseBP& OnVerifyPlayerRequestCompleted, FString Platform = FString(TEXT("")));

    /**
     End the active session for a player (no-op if no active session).
     Terminates the server-side session; further requests with its token will receive 401 Unauthorized.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnEndSessionRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Authentication")
    static void EndSession(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnEndSessionRequestCompleted);

    //==================================================
    // Connected Accounts
    //==================================================

    /**
     List identity providers (Apple, Google, etc.) connected to the current player's LootLocker account.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListConnectedAccounts(const FString& ForPlayerWithUlid, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP);

    /**
     Disconnect a linked identity provider account so it can no longer start sessions for this LootLocker player.
     Use to revoke a previously connected provider (Google, Apple, etc.).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AccountToDisconnect Identity provider to disconnect
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DisconnectAccount(const FString& ForPlayerWithUlid, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP);

    /**
     Connect a Google account to this LootLocker player, allowing future Google authentications to start sessions.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param IdToken Google ID token from sign-in
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectGoogleAccount(const FString& ForPlayerWithUlid, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect a Google account (for a specific OAuth2 Client Platform) to this LootLocker player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param IdToken Google ID token from sign-in
     @param Platform Google OAuth2 client platform
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectGoogleAccountWithPlatform(const FString& ForPlayerWithUlid, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect an Apple account (authorized via REST Sign In) to this LootLocker player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AuthorizationCode Authorization code provided by Apple during sign-in
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectAppleAccountByRestSignIn(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect a Twitch account to this LootLocker player enabling Twitch-based session starts.
     IMPORTANT: When using multiple players ensure you supply the correct ForPlayerWithUlid, or the account may link to the wrong player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AuthorizationCode Authorization code provided by Twitch during sign-in
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectTwitchAccount(const FString& ForPlayerWithUlid, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect an Epic account to this LootLocker player enabling Epic-based session starts.
     IMPORTANT: When using multiple players ensure you supply the correct ForPlayerWithUlid.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Token Token provided by Epic during sign-in
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectEpicAccount(const FString& ForPlayerWithUlid, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect a PlayStation account to this LootLocker player enabling PlayStation-based session starts.
     IMPORTANT: When using multiple players ensure you supply the correct ForPlayerWithUlid.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Environment PlayStation environment (e.g. prod, dev, qa)
     @param Code Authorization / linkage code returned by PlayStation flow
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectPlaystationAccount(const FString& ForPlayerWithUlid, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect a Discord account to this LootLocker player enabling Discord-based session starts.
     IMPORTANT: When using multiple players ensure you supply the correct ForPlayerWithUlid.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Token Token provided by Discord during sign-in
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectDiscordAccount(const FString& ForPlayerWithUlid, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Connect an account authenticated via a remote session lease to this LootLocker player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Code Lease code returned when starting the remote session leasing process
     @param Nonce Nonce returned when starting the remote session leasing process
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ConnectRemoteSessionAccount(const FString& ForPlayerWithUlid, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP);

    /**
     Transfer one or more identity provider connections from one authenticated player to another.
     All requested providers must be transferable or the whole operation fails (no partial transfer).
     IMPORTANT: This is destructive for the source player; transferred providers will no longer authenticate that player.
     Limitations: Source must own the providers; destination must not already have them; providers must be active in game settings.

     @param FromPlayerWithUlid ULID of the authenticated source player (providers moved FROM)
     @param ToPlayerWithUlid ULID of the authenticated destination player (providers moved TO)
     @param ProvidersToTransfer List of identity providers to transfer
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Connected Accounts")
    static void TransferIdentityProvidersBetweenAccounts(const FString& FromPlayerWithUlid, const FString& ToPlayerWithUlid, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP);

    //==================================================
    // Remote Sessions
    //==================================================

    /**
     Start a remote session (Deprecated – use AsyncStartRemoteSession or AsyncStartRemoteSessionForLinking).
     Provides lease information for a secondary device and polls its status until completion or timeout.

     @param RemoteSessionLeaseInformation Delegate invoked once with lease info for the secondary device
     @param RemoteSessionLeaseStatusUpdate Delegate invoked periodically with updated lease status
     @param OnComplete Delegate invoked when the process completes (success or failure)
     @param PollingIntervalSeconds Optional: Seconds between status polls (default 1.0)
     @param TimeOutAfterMinutes Optional: Total minutes before timing out the process (default 5.0)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Remote Session", meta = (AdvancedDisplay = "PollingIntervalSeconds,TimeOutAfterMinutes", PollingIntervalSeconds = 1.0f, TimeOutAfterMinutes = 5.0f, DeprecatedFunction, DeprecationMessage = "This method is deprecated in favor of either method AsyncStartRemoteSession or AsyncStartRemoteSessionForLinking depending on your use case")) // Deprecation date 20250327
    static FString StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformation, const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdate, const FLootLockerStartRemoteSessionResponseDelegateBP& OnComplete, float PollingIntervalSeconds, float TimeOutAfterMinutes);

    /**
     Cancel an ongoing remote session process.

     @param ProcessID Identifier of the remote session process to cancel
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Remote Session")
    static void CancelRemoteSessionProcess(FString ProcessID);

    /**
     Refresh a session originally established through a remote session flow.
     HTTP 401 (Unauthorized) indicates the refresh token expired and a new remote session flow is required.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param RefreshToken Optional: Refresh token from StartRemoteSession (resolved from stored data if empty)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Remote Session", meta = (AdvancedDisplay = "RefreshToken,ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RefreshRemoteSession(const FString& ForPlayerWithUlid, const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompletedRequest);

    //==================================================
    //Players
    //==================================================

    /**
     Get profile information for the current player (ids, name and related identifiers) used in subsequent calls.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrentPlayerInfo(const FString& ForPlayerWithUlid, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequest);

    /**
     Retrieve profile information for multiple players using ULIDs, legacy ids, and/or public UIDs.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param PlayerIdsToLookUp Array of player ULIDs to look up
     @param PlayerLegacyIdsToLookUp Array of legacy integer player ids to look up
     @param PlayerPublicUidsToLookUp Array of public player UIDs to look up
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerInfo(const FString& ForPlayerWithUlid, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequest);

    /**
     Get the full list of inventory asset instances owned by a player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetInventoryRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetInventory(const FString& ForPlayerWithUlid, const FPInventoryResponseBP& OnGetInventoryRequestCompleted);

    /**
     Get a paginated segment of the player's inventory starting after a given asset instance id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param StartIndex Pagination pointer; returns items after this asset instance id
     @param OnGetInventoryRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetFullInventory(const FString ForPlayerWithUlid, int32 StartIndex, const FPInventoryResponseBP& OnGetInventoryRequestCompleted);

    /**
     Get recently granted player assets since the last activation notification check.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCheckPlayerAssetDeactivationNotificationRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CheckPlayerAssetActivationNotification(const FString& ForPlayerWithUlid, const FPAssetNotificationResponseBP& OnCheckPlayerAssetDeactivationNotificationRequestCompleted);

    /**
     Get the current credit / currency balance of a player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetCurrencyBalance Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrencyBalance(const FString& ForPlayerWithUlid, const FPBalanceResponseBP& OnGetCurrencyBalance);

    /**
     Initiate DLC migration for the player (results appear later via asset notifications; poll after ~5 minutes).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnInitiateDlcMigration Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void InitiateDLCMigration(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnInitiateDlcMigration);

    /**
     List DLC identifiers migrated for the player (identifiers are returned as strings regardless of underlying numeric nature).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGotDlcMigration Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetDLCsMigration(const FString& ForPlayerWithUlid, const FPDlcResponseBP& OnGotDlcMigration);

    /**
     Set the player's profile visibility to private (inventory not shown publicly on external platforms).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnProfileSetPrivate Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetProfilePrivate(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPrivate);

    /**
     Set the player's profile visibility to public (inventory may be shown on external platforms).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnProfileSetPublic Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetProfilePublic(const FString& ForPlayerWithUlid, const FResponseCallbackBP& OnProfileSetPublic);

    /**
     Set (or change) the player's display name.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Name New display name to set
     @param OnSetPlayerName Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SetPlayerName(const FString& ForPlayerWithUlid, FString Name, const FPNameResponseBP& OnSetPlayerName);

    /**
     Get the player's current display name.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetPlayerName Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetPlayerName(const FString& ForPlayerWithUlid, const FPNameResponseBP& OnGetPlayerName);

    /**
     Look up player names on their last active platform (Deprecated – use LookupMultiplePlayersDataUsingIDs).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request Request payload containing platforms and ids for lookup
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid="", DeprecatedFunction, DeprecationMessage = "This method is deprecated in favor of method LookupMultiplePlayersDataUsingIDs")) // Deprecation date 20250304
    static void LookupMultiplePlayerNamesUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesRequest &Request, const FPMultiplePlayerNamesBP& OnCompletedRequest);
    
    /**
     Look up multiple players' data using a mix of supported identifier types.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request Request payload containing platforms and ids for player data lookup
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LookupMultiplePlayersDataUsingIDs(const FString& ForPlayerWithUlid, const FLootLockerLookupMultiplePlayersDataRequest& Request, const FPMultiplePlayerNamesBP& OnCompletedRequest);

    /**
     Look up player names using first-platform player ids and/or public UIDs.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request Request payload with player ids and/or public UIDs
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LookupMultiplePlayerNames1stPlatformIDs(const FString& ForPlayerWithUlid, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequest);

    /**
     Mark the player for deletion (permanently removed after a 30 day grace period).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Players", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeletePlayer(const FString& ForPlayerWithUlid, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    //==================================================
    //Files
    //==================================================

    /**
     Upload a file owned by the player.
     Use for initial creation; subsequent updates use UpdateFile.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request File upload request payload
     @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UploadFile(const FString& ForPlayerWithUlid, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnComplete);

    /**
     Update an existing player-owned file with new content or metadata.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param FileId File id (retrieved from upload response or ListFiles)
     @param Request File update request payload
     @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateFile(const FString& ForPlayerWithUlid, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnComplete);

    /**
     List all files owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListFiles(const FString& ForPlayerWithUlid, const FLootLockerFileListBP& OnComplete);

    /**
     List all public files owned by another player (by legacy PlayerID).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param PlayerID Legacy player id of the target player
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListOtherPlayersPublicFiles(const FString& ForPlayerWithUlid, const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP);

    /**
     Retrieve metadata (including access URL) for a single file.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param FileID File id (retrieved from upload response or ListFiles)
     @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetSingleFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerUploadFileBP& OnComplete);

    /**
     Permanently delete a file (irreversible).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param FileID File id to delete (from upload response or ListFiles)
     @param OnComplete Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Files", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeletePlayerFile(const FString& ForPlayerWithUlid, const int32 FileID, const FLootLockerFileDeletedBP& OnComplete);

    //==================================================
    // Player Progressions
    //==================================================

    /**
     List progressions the player is currently on (paginated).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Count Optional: Max number of entries to return (-1 = server default)
     @param After Optional: Pagination cursor (player progression id) to start after (use next_cursor / previous_cursor)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetPlayerProgressions(const FString& ForPlayerWithUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest);

    /**
     Get a single progression state for the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Key of the progression to fetch
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest);

    /**
     Add points to a player progression (may trigger rewards if thresholds crossed).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Key of the progression to increment
     @param Amount Number of points to add
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddPointsToPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     Subtract points from a player progression.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Key of the progression to decrement
     @param Amount Number of points to subtract
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubtractPointsFromPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     Reset a player progression to its initial state.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Key of the progression to reset
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ResetPlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     Delete a player progression (removes progress data for that progression).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Key of the progression to delete
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeletePlayerProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest);

    /**
     List progressions for another specified player (paginated).

     @param ForPlayerWithUlid Optional: Execute for the calling player ULID (default player if empty)
     @param PlayerUlid ULID of the target player whose progressions to list
     @param Count Optional: Max number of entries to return (-1 = server default)
     @param After Optional: Pagination cursor id to start after
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersProgressions(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequest);

    /**
     Get a single progression state for another specified player.

     @param ForPlayerWithUlid Optional: Execute for the calling player ULID (default player if empty)
     @param PlayerUlid ULID of the target player
     @param ProgressionKey Key of the progression to fetch
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Player Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetOtherPlayersProgression(const FString& ForPlayerWithUlid, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequest);

    //==================================================
    // Heroes
    //==================================================

    /**
     List all game hero templates (heroes available in the title) including names and character info.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetGameHeroes(const FString& ForPlayerWithUlid, const FLootLockerGameHeroListBP& OnCompleteBP);

    /**
     List heroes owned by the current player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerHeroes(const FString& ForPlayerWithUlid, const FLootLockerHeroListBP& OnCompleteBP);

    /**
     List heroes owned by another player identified by SteamID64.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param SteamID64 SteamID64 of the target player
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListOtherPlayersHeroesBySteamID64(const FString& ForPlayerWithUlid, const int64 SteamID64, const FLootLockerHeroListBP& OnCompleteBP);

    /**
     Create a hero for the player from a game hero template.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request Request containing game hero template id and hero name
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateHero(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     Create a hero from a game hero template including variation and optional default flag.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request Request including template id, hero name, variation id and default flag
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateHeroWithVariation(const FString& ForPlayerWithUlid, const FLootLockerCreateHeroWithVariationRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     Get information about a specific hero owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero to fetch
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     Get the default hero for another player identified by SteamID64.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param SteamID64 SteamID64 of the target player
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersDefaultHeroBySteamID64(const FString& ForPlayerWithUlid, const int32 SteamID64, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     Update a hero's name and/or mark it as the player's default hero.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero to update
     @param Request Request specifying new name and default flag
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLootLockerUpdateHeroRequest& Request, const FLootLockerPlayerHeroBP& OnCompleteBP);

    /**
     Delete a hero owned by the player (irreversible; hero inventory items are returned to general inventory, loadout reset).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero to delete
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteHero(const FString& ForPlayerWithUlid, const int32 HeroID, const FLLHeroDefaultResponseBP& OnCompleteBP);

    /**
     List asset instances equipped/owned by a specific hero (first page only; endpoint is paginated server-side).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetHeroInventory(const FString& ForPlayerWithUlid, const int32 HeroID, const FPInventoryResponseBP& OnCompleteBP);

    /**
     Get the loadout (equipped items) for a hero owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     Get the loadout for another player's hero.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     Equip an existing asset instance to a hero owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param AssetInstanceID Id of the asset instance to equip
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     Equip a global asset (default variation) directly to a hero owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param AssetID Id of the global asset
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddGlobalAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     Equip a specific global asset variation to a hero owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param AssetID Id of the global asset
     @param AssetVariationID Variation id of the global asset
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddGlobalAssetVariationToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetID, const int32 AssetVariationID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    /**
     Unequip an asset instance from a hero owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param HeroID Id of the hero
     @param AssetInstanceID Id of the asset instance to unequip
     @param OnCompleteBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Heroes", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RemoveAssetToHeroLoadout(const FString& ForPlayerWithUlid, const int32 HeroID, const int32 AssetInstanceID, const FHeroLoadoutReseponseBP& OnCompleteBP);

    //==================================================
    // Characters
    //==================================================

    /**
     List loadouts for all characters owned by the player including basic character info.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetCharacterLoadoutRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCharacterLoadout(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCharacterLoadoutRequestCompleted);

    /**
     Update a character's name and/or mark it as the default character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character to update
     @param IsDefault Whether this character should become default
     @param Name New character name (can be unchanged)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateCharacter(const FString& ForPlayerWithUlid, int CharacterId, bool IsDefault, FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequest);

    /**
     Create a character of a specified type and name (optionally set as default).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param IsDefault Whether the new character should be default
     @param CharacterName Name of the character
     @param CharacterTypeId Id of the character type (see ListCharacterTypes)
     @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateCharacter(const FString& ForPlayerWithUlid, bool IsDefault, FString CharacterName, FString CharacterTypeId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP);

    /**
     Delete a character by id (irreversible) and free associated loadout slots/items back to inventory.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character to delete
     @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteCharacter(const FString& ForPlayerWithUlid, int CharacterId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP);

    /**
     List character types configured for your game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListCharacterTypes(const FString& ForPlayerWithUlid, const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP);

    /**
     List characters owned by the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListPlayerCharacters(const FString& ForPlayerWithUlid, const FPLootLockerListPlayerCharactersResponseBP& OnCompletedRequestBP);
    /**
     Equip an asset instance to the player's default character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param InstanceId Asset instance id to equip
     @param OnEquipAssetToDefaultCharacterRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void EquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToDefaultCharacterRequestCompleted);

    /**
     Equip an asset (by asset id and variation) to a specific character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character to equip
     @param AssetId Asset id to equip
     @param AssetVariationId Variation id of the asset
     @param OnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void EquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

    /**
     Equip an asset instance to a specific character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character to equip
     @param InstanceId Asset instance id to equip
     @param OnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void EquipAssetToCharacterByIdAndInstance(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const FPCharacterDefaultResponseBP& OnEquipAssetToCharacterByIdRequestCompleted);

    /**
     Unequip an asset instance from the default character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param InstanceId Asset instance id to unequip
     @param OnUnEquipAssetToDefaultCharacterRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnEquipAssetToDefaultCharacter(const FString& ForPlayerWithUlid, int InstanceId, const FPCharacterDefaultResponseBP& OnUnEquipAssetToDefaultCharacterRequestCompleted);

    /**
     Unequip an asset instance from a specific character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param InstanceId Asset instance id to unequip
     @param OnUnEquipAssetToCharacterByIdRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnEquipAssetToCharacterById(const FString& ForPlayerWithUlid, int CharacterId, int InstanceId, const  FPCharacterDefaultResponseBP& OnUnEquipAssetToCharacterByIdRequestCompleted);


    /**
     Get the asset instances currently equipped on the player's default character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetCurrentLoadoutToDefaultCharacterRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, const FPCharacterLoadoutResponseBP& OnGetCurrentLoadoutToDefaultCharacterRequestCompleted);

    /**
     Get the default character loadout for another player identified by a platform-specific id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OtherPlayerId Platform-specific id of the target player
     @param OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted Delegate for handling the server response
     @param OtherPlayerPlatform Optional: Platform the id refers to (if different than current)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& ForPlayerWithUlid, FString OtherPlayerId, const FPCharacterLoadoutResponseBP& OnGetOtherPlayersCurrentLoadoutToDefaultCharacterRequestCompleted, const FString& OtherPlayerPlatform = FString(TEXT("")));

    /**
     List equipable contexts (slots/categories) for the player's default character.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetEquipableContextsToDefaultCharacterRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEquipableContextsToDefaultCharacter(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetEquipableContextsToDefaultCharacterRequestCompleted);

    /**
     List equipable contexts for another player's character by character id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OtherCharacterId Target character id
     @param OnGetEquipableContextsByCharacterIdRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEquipableContextsByCharacterId(const FString& ForPlayerWithUlid, int OtherCharacterId, const FContextDelegateBP& OnGetEquipableContextsByCharacterIdRequestCompleted);

    /**
     Get character loadouts for another player by platform-specific id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OtherPlayerId Platform-specific id of the target player
     @param OtherPlayerPlatform Optional: Platform the id refers to (if differing)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid,OtherPlayerPlatform", ForPlayerWithUlid="", OtherPlayerPlatform=""))
    static void GetOtherPlayersCharacterLoadouts(const FString& ForPlayerWithUlid, const FString& OtherPlayerId, const FString& OtherPlayerPlatform, const FPCharacterLoadoutResponseBP& OnCompletedRequest);

    /**
     Get character loadouts for another player by their public UID.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OtherPlayerUid Public UID of the target player
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Characters", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetOtherPlayersCharacterLoadoutsByUid(const FString& ForPlayerWithUlid, const FString& OtherPlayerUid, const FPCharacterLoadoutResponseBP& OnCompletedRequest);


    //==================================================
    // Character Progressions
    //==================================================

    /**
     List character progressions the character is currently on (paginated).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param Count Optional: Number of entries to return (-1 = server default)
     @param After Optional: Cursor id to continue pagination (use next_cursor/previous_cursor)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetCharacterProgressions(const FString& ForPlayerWithUlid, const int32& CharacterId, const int32 Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequest);

    /**
     Get a specific progression for the character by progression key.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param ProgressionKey Progression key to fetch
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequest);

    /**
     Add points to a character progression and return any newly earned rewards.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param ProgressionKey Progression key to modify
     @param Amount Points to add (positive integer)
     @param OnCompletedRequest Delegate for handling the server response (includes rewards)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddPointsToCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     Subtract points from a character progression (clamped at zero) and return any adjusted reward state.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param ProgressionKey Progression key to modify
     @param Amount Points to subtract (positive integer)
     @param OnCompletedRequest Delegate for handling the server response (includes rewards)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubtractPointsFromCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     Reset a character progression to its initial state and return resulting reward changes.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param ProgressionKey Progression key to reset
     @param OnCompletedRequest Delegate for handling the server response (includes rewards)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ResetCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequest);

    /**
     Delete a character progression entirely (progress and rewards association removed).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param CharacterId Id of the character
     @param ProgressionKey Progression key to delete
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Character Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteCharacterProgression(const FString& ForPlayerWithUlid, const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequest);

    //==================================================
    // Persistent Storage
    //==================================================

    /**
     Retrieve all key/value pairs stored for the player (may be large; prefer metadata for new integrations).

     Note: Player Persistent Storage is being superseded by Player Metadata. Prefer Player Metadata unless already deeply integrated.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnPersistentStorageItemsRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetEntirePersistentStorage(const FString& ForPlayerWithUlid, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsRequestCompleted);

    /**
     Get a single key/value pair from the player's persistent storage.

     Note: Player Persistent Storage is being superseded by Player Metadata. Prefer Player Metadata unless already deeply integrated.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Key Key to retrieve
     @param OnPersistentStorageItemRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemRequestCompleted);

    /**
     Create or update multiple key/value pairs in player persistent storage.

     Note: Player Persistent Storage is being superseded by Player Metadata. Prefer Player Metadata unless already deeply integrated.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Items Array of items to create or update
     @param OnPersistentStorageItemsAddRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddItemsToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemsAddRequestCompleted);

    /**
     Create or update a single key/value pair in player persistent storage.

     Note: Player Persistent Storage is being superseded by Player Metadata. Prefer Player Metadata unless already deeply integrated.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Item Item to create or update
     @param OnPersistentStorageItemAddRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddItemToPersistentStorage(const FString& ForPlayerWithUlid, FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnPersistentStorageItemAddRequestCompleted);

    /**
     Delete a key/value pair from player persistent storage.

     Note: Player Persistent Storage is being superseded by Player Metadata. Prefer Player Metadata unless already deeply integrated.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Key Key to delete
     @param OnPersistentStorageItemDeleteRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteItemFromPersistentStorage(const FString& ForPlayerWithUlid, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnPersistentStorageItemDeleteRequestCompleted);

    /**
     Read another player's public key/value persistent storage (public items only).

     Note: Player Persistent Storage is being superseded by Player Metadata. Prefer Player Metadata unless already deeply integrated.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param PlayerId Player id or public UID
     @param OnGetPlayerPersistentStorageRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Persistent Storage", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetPlayerPersistentStorage(const FString& ForPlayerWithUlid, const FString& PlayerId, const  FPersistentStorageItemsResponseDelegateBP& OnGetPlayerPersistentStorageRequestCompleted);

    //==================================================
    // Assets
    //==================================================

    /**
     List all asset contexts configured for the game.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetContextsRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetContexts(const FString& ForPlayerWithUlid, const FContextDelegateBP& OnGetContextsRequestCompleted);

    /**
     Retrieve assets in paginated form with optional filtering.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetAssetsRequestCompleted Delegate for handling the server response
     @param StartFromIndex Optional: Index to start from (default 0)
     @param ItemsCount Optional: Number of items (50-200, default 50)
     @param AssetFilter Optional: Filter enum for asset type (default None)
     @param Context Optional: Context id to restrict results (default 0 = all)
     @param IncludeUGC Optional: Include user generated assets (default false)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssets(const FString& ForPlayerWithUlid, const FAssetsResponseDelegateBP& OnGetAssetsRequestCompleted, int StartFromIndex = 0, int ItemsCount = 50, ELootLockerAssetFilter AssetFilter = ELootLockerAssetFilter::None, int Context = 0, bool IncludeUGC = false);

    /**
     Retrieve specific assets by id list (non-paginated).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetIds Asset ids to fetch
     @param OnGetAssetsByIdsRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssetsByIds(const FString& ForPlayerWithUlid, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnGetAssetsByIdsRequestCompleted);

    /**
     List all default asset bones and any binding overrides.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetAssetBonesRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssetBones(const FString& ForPlayerWithUlid, const  FAssetBonesResponseDelegateBP& OnGetAssetBonesRequestCompleted);

    /**
     List the player's favourite asset indices.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetFavouriteAssetIndicesRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetFavouriteAssetIndices(const FString& ForPlayerWithUlid, const FGetFavouriteAssetIndicesResponseDelegateBP& OnGetFavouriteAssetIndicesRequestCompleted);

    /**
     Add an asset to the player's favourites list.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetId Asset id to add
     @param OnAddAssetToFavouritesRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddAssetToFavourites(const FString& ForPlayerWithUlid, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnAddAssetToFavouritesRequestCompleted);

    /**
     Remove an asset from the player's favourites list.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetId Asset id to remove
     @param OnRemoveAssetFromFavouritesRequestCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RemoveAssetFromFavourites(const FString& ForPlayerWithUlid, int AssetId, const  FGetFavouriteAssetIndicesResponseDelegateBP& OnRemoveAssetFromFavouritesRequestCompleted);

    /**
     List universal assets (global across game) with cursor pagination.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param After Optional: Last universal asset id to start after (cursor)
     @param ItemsCount Number of items to return (50-200)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetUniversalAssets(const FString& ForPlayerWithUlid, int After, int ItemsCount, const FUniversalAssetResponseDelegateBP& OnCompletedRequest);

    /**
     Grant an asset (optionally with variation or rental option) to the player's inventory.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetID Asset id to grant
     @param AssetVariationID Optional: Variation id (0 for none)
     @param AssetRentalOptionID Optional: Rental option id (0 for none)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GrantAssetWithVariationToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const int AssetVariationID, const int AssetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequest);

    /**
     Grant a base asset (no variation or rental) to the player's inventory.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetID Asset id to grant
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GrantAssetToPlayerInventory(const FString& ForPlayerWithUlid, const int AssetID, const FGrantAssetResponseDelegateBP& OnCompletedRequest) {
        GrantAssetWithVariationToPlayerInventory(ForPlayerWithUlid, AssetID, 0, 0, OnCompletedRequest);
    }

    /**
     List assets using default server parameters (no filters) returning a lightweight subset of fields.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ListAssetsWithDefaultParameters(const FString& ForPlayerWithUlid, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest);

    /**
     List assets with a configurable projection (include/exclude fields, filters, ordering, pagination) for optimized payloads.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Request Field selection and filter configuration
     @param PerPage Optional: Page size (0 = no pagination)
     @param Page Optional: Page index (0 = no pagination)
     @param OrderBy Optional: Field to order by (unordered if unset)
     @param OrderDirection Optional: Ascending/Descending (unordered if unset)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets", meta = (AdvancedDisplay = "PerPage,Page,OrderBy,OrderDirection,ForPlayerWithUlid", PerPage=0,Page=0,ForPlayerWithUlid=""))
    static void ListAssets(const FString& ForPlayerWithUlid, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, ELootLockerOrderAssetListBy OrderBy, ELootLockerOrderAssetListDirection OrderDirection, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequest);

    //==================================================
    // Asset Instances
    //==================================================

    /**
     List all key/value storage entries attached to an asset instance.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Asset instance id
     @param OnGetAllKeyValuePairsForAssetInstanceCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllKeyValuePairsForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FAssetInstanceStorageItemsResponseDelegateBP& OnGetAllKeyValuePairsForAssetInstanceCompleted);

    /**
     Get a single key/value storage entry by id for an asset instance.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Asset instance id
     @param StorageItemId Storage (key/value) entry id
     @param OnGetAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnGetAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     Create a new key/value storage entry for an asset instance.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Asset instance id
     @param Item Key/value entry to create
     @param OnCreateAKeyValuePairForAssetInstanceCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateAKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCreateAKeyValuePairForAssetInstanceCompleted);

    /**
     Bulk update or add multiple key/value storage entries for an asset instance.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Asset instance id
     @param Items Entries to upsert
     @param OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnUpdateOneOrMoreKeyValuePairForAssetInstanceCompleted);

    /**
     Update a single key/value storage entry for an asset instance by entry id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Asset instance id
     @param StorageItemId Storage entry id to update
     @param Item Updated entry data
     @param OnUpdateAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnUpdateAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     Delete a key/value storage entry from an asset instance by entry id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Asset instance id
     @param StorageItemId Storage entry id to delete
     @param OnDeleteAKeyValuePairByIdForAssetInstanceCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteAKeyValuePairByIdForAssetInstance(const FString& ForPlayerWithUlid, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnDeleteAKeyValuePairByIdForAssetInstanceCompleted);

    /**
     Inspect a loot box asset instance to view potential contents and drop rates (non-destructive).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Loot box asset instance id
     @param OnInspectLootBoxCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void InspectLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const  FLootBoxContentResponseDelegateBP& OnInspectLootBoxCompleted);

    /**
     Open (consume) a loot box asset instance and grant its awarded contents to the player's inventory.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceId Loot box asset instance id
     @param OnOpenLootBoxCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void OpenLootBox(const FString& ForPlayerWithUlid, int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnOpenLootBoxCompleted);

    /**
     Permanently delete an asset instance from the player's inventory.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetInstanceID Asset instance id to delete
     @param OnCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Assets Instances", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteAssetInstanceFromPlayerInventory(const FString& ForPlayerWithUlid, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompleted);

    //==================================================
    // User Generated Content
    //==================================================

    /**
     Create an asset candidate (initial draft before adding files and finalizing).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateData Candidate data payload (title, description, etc.)
     @param OnCreateAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateAssetCandidate(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted);

    /**
     Create an asset candidate and immediately mark it as completed (single-step publish flow).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateData Candidate data payload
     @param OnCreateAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CreateAssetCandidateAndMarkComplete(const FString& ForPlayerWithUlid, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCreateAssetCandidateCompleted);

    /**
     Update an existing asset candidate (metadata edits before completion).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateId Asset candidate id
     @param AssetCandidateData Updated candidate data
     @param OnUpdateAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UpdateAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnUpdateAssetCandidateCompleted);

    /**
     Delete an asset candidate (removes draft and associated files).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateId Asset candidate id
     @param OnDeleteAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FResponseCallbackBP& OnDeleteAssetCandidateCompleted);

    /**
     List all asset candidates created by or visible to the player.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param OnGetAllAssetCandidatesCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllAssetCandidates(const FString& ForPlayerWithUlid, const FAssetCandidatesResponseDelegateBP& OnGetAllAssetCandidatesCompleted);

    /**
     Get a single asset candidate by id.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateId Asset candidate id
     @param OnGetAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnGetAssetCandidateCompleted);

    /**
     Add a file to an asset candidate (uploads binary under specified purpose).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateId Asset candidate id
     @param FilePath Absolute path to the file to upload
     @param FilePurpose Purpose classification for the file
     @param OnAddFileToAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddFileToAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegateBP& OnAddFileToAssetCandidateCompleted);

    /**
     Remove a previously uploaded file from an asset candidate.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param AssetCandidateId Asset candidate id
     @param FileId File id to remove
     @param OnDeleteFileFromAssetCandidateCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | User Generated Content", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteFileFromAssetCandidate(const FString& ForPlayerWithUlid, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnDeleteFileFromAssetCandidateCompleted);

    //==================================================
    // Progressions
    //==================================================

    /**
     List game progressions (paginated).

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param Count Optional: Number of entries to return (-1 = server default)
     @param After Optional: Cursor id to continue pagination (use next_cursor/previous_cursor)
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetProgressions(const FString& ForPlayerWithUlid, const int32 Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequest);

    /**
     Get a single progression definition by key.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Progression key to fetch
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetProgression(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequest);

    /**
     List tiers of a progression (paginated) to inspect level thresholds and rewards.

     @param ForPlayerWithUlid Optional: Execute for the specified player ULID (default player if empty)
     @param ProgressionKey Progression key whose tiers to list
     @param Count Optional: Number of tier entries (-1 = server default)
     @param After Optional: Cursor (tier id) to continue pagination
     @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = -1, ForPlayerWithUlid=""))
    static void GetProgressionTiers(const FString& ForPlayerWithUlid, const FString& ProgressionKey, const int32 Count, const int32 After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequest);

    //==================================================
    // Instance Progressions
    //==================================================

    /**
     Returns multiple progressions the asset instance is currently on.
     List progressions attached to an asset instance (cursor pagination).
    
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param AssetInstanceId Id of the asset instance to fetch progressions for
     @param Count Optional: Number of entries to return. Use -1 to use the server default
     @param After Optional: Cursor id of the last received instance progression. Use next_cursor or previous_cursor from a prior response
     @param OnCompletedRequestBP Delegate for handling the response (FLootLockerPaginatedInstanceProgressionsResponse)
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "Count,After,ForPlayerWithUlid", Count = -1, After = "", ForPlayerWithUlid=""))
    static void GetInstanceProgressions(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequestBP);

    /**
     Get a single progression for an asset instance.
    
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param AssetInstanceId Id of the asset instance
     @param ProgressionKey Key of the progression to fetch
     @param OnCompletedRequestBP Delegate for handling the response (FLootLockerInstanceProgressionResponse)
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequestBP);

    /**
     Add points to an instance progression (may trigger rewards).
    
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param AssetInstanceId Id of the asset instance
     @param ProgressionKey Key of the progression to add points to
     @param Amount Number of points to add
     @param OnCompletedRequestBP Delegate for handling the response (FLootLockerInstanceProgressionWithRewardsResponse)
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AddPointsToInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
     Subtract points from an instance progression (may adjust completed tiers).
    
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param AssetInstanceId Id of the asset instance
     @param ProgressionKey Key of the progression to subtract points from
     @param Amount Number of points to subtract
     @param OnCompletedRequestBP Delegate for handling the response (FLootLockerInstanceProgressionWithRewardsResponse)
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SubtractPointsFromInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
     Reset an instance progression to its initial state (may re‑issue initial rewards).
    
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param AssetInstanceId Id of the asset instance
     @param ProgressionKey Key of the progression to reset
     @param OnCompletedRequestBP Delegate for handling the response (FLootLockerInstanceProgressionWithRewardsResponse)
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ResetInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP);

    /**
     Delete an instance progression permanently.
    
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param AssetInstanceId Id of the asset instance
     @param ProgressionKey Key of the progression to delete
     @param OnCompletedRequestBP Delegate for handling the response (FLootLockerResponse)
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Instance Progressions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteInstanceProgression(const FString& ForPlayerWithUlid, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP);

    //==================================================
    // Missions
    //==================================================

    /**
      List all missions accessible to the player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param OnGetAllMissionsCompleted Delegate for handling the server response (Missions list)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllMissions(const FString& ForPlayerWithUlid, const FMissionsResponseDelegateBP& OnGetAllMissionsCompleted);

    /**
      Get details for a single mission.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param MissionId Id of the mission to fetch
      @param OnGetMissionCompleted Delegate for handling the server response (Mission details)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMission(const FString& ForPlayerWithUlid, int MissionId, const FMissionResponseDelegateBP& OnGetMissionCompleted);

    /**
      Start (begin) a mission for the player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param MissionId Id of the mission to start
      @param OnStartMissionCompleted Delegate for handling the server response (start confirmation / state)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void StartMission(const FString& ForPlayerWithUlid, int MissionId, const  FStartMissionResponseDelegateBP& OnStartMissionCompleted);

    /**
      Finish a mission and submit completion data.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param MissionId Id of the mission to finish
      @param MissionData Completion data (objectives, scores, etc.)
      @param OnFinishMissionCompleted Delegate for handling the server response (final mission results / rewards)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Missions", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void FinishMission(const FString& ForPlayerWithUlid, int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnFinishMissionCompleted);

    //==================================================
    // Maps
    //==================================================

    /**
      List available maps for the game.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param OnGetMapsCompleted Delegate for handling the server response (maps list)
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Maps", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMaps(const FString& ForPlayerWithUlid, const FGetMapsResponseDelegateBP& OnGetMapsCompleted);

    //==================================================
    // Purchases
    //==================================================

    /**
      Activate a purchased rental asset instance for the player.
     
      Once a rental asset is purchased it must be activated before it becomes usable.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param AssetInstanceId Id of the rental asset instance to activate
      @param OnActivateRentalAssetCompleted Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ActivateRentalAsset(const FString& ForPlayerWithUlid, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnActivateRentalAssetCompleted);

    /**
      Purchase a single catalog item using a specified wallet.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param WalletId Id of the wallet to charge
      @param CatalogItemListingId Listing id of the catalog item to purchase
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LootLockerPurchaseSingleCatalogItem(const FString& ForPlayerWithUlid, const FString& WalletId, const FString& CatalogItemListingId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Purchase one or more catalog items (with quantities) using a specified wallet.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param WalletId Id of the wallet to charge
      @param ItemsToPurchase Items and quantities to purchase
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void LootLockerPurchaseCatalogItems(const FString& ForPlayerWithUlid, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair> ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem an Apple App Store purchase for the current player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param TransactionId Id of the successful App Store transaction
      @param Sandboxed Optional: Redeem against the App Store sandbox environment
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "Sandboxed,ForPlayerWithUlid", Sandboxed = false, ForPlayerWithUlid=""))
    static void RedeemAppleAppStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem an Apple App Store purchase for a class owned by the player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param TransactionId Id of the successful App Store transaction
      @param ClassId Id of the class to receive the entitlement
      @param Sandboxed Optional: Redeem against the App Store sandbox environment
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "Sandboxed,ForPlayerWithUlid", Sandboxed = false, ForPlayerWithUlid=""))
    static void RedeemAppleAppStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& TransactionId, bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem a Google Play purchase for the current player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param ProductId Id of the purchased product
      @param PurchaseToken Purchase token provided by Google Play
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemGooglePlayStorePurchaseForPlayer(const FString& ForPlayerWithUlid, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem a Google Play purchase for a class owned by the player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param ClassId Id of the class to receive the entitlement
      @param ProductId Id of the purchased product
      @param PurchaseToken Purchase token provided by Google Play
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemGooglePlayStorePurchaseForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem Epic Games Store entitlements for the current player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param AccountId Epic Account Id that owns the entitlements
      @param BearerToken Epic bearer/auth token allowing backend verification (Server Auth Ticket)
      @param EntitlementIds Ids of the entitlements to redeem
      @param SandboxId Epic sandbox id configured for the game
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemEpicStorePurchase(const FString& ForPlayerWithUlid, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem Epic Games Store entitlements for a character owned by the player.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param CharacterId Ulid of the character receiving the entitlements
      @param AccountId Epic Account Id that owns the entitlements
      @param BearerToken Epic bearer/auth token allowing backend verification (Server Auth Ticket)
      @param EntitlementIds Ids of the entitlements to redeem
      @param SandboxId Epic sandbox id configured for the game
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void RedeemEpicStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

#ifdef LOOTLOCKER_BETA_PLAYSTATION_IAP
    /**
      Redeem a purchase that was made successfully towards the PlayStation Store for the current player
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
      @param TransactionId The transaction id from the PlayStation Store of the purchase to redeem
      @param AuthCode The authorization code from the PlayStation Store of the purchase to redeem
      @param EntitlementLabel The entitlement label configured in the NP service for the entitlement that this redemption relates to
      @param ServiceLabel Optional: The NP service label
      @param ServiceName Optional: The abbreviation of the service name of the ASM service ID service that was used when configuring the serviceIds. Possible Values: pssdc, cce. Default Value: pssdc
      @param Environment Optional: The id of the environment you wish to make the request against. Allowed values: 1, 8, 256
      @param UseCount Optional: The use count for this redemption
      @param OnCompletedRequest Delegate for handling the server response
     */
    //UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid,ServiceLabel,ServiceName,Environment,UseCount", ForPlayerWithUlid="", ServiceLabel="", ServiceName="", Environment=-1, UseCount=-1))
    //static void RedeemPlayStationStorePurchase(const FString& ForPlayerWithUlid, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    /**
      Redeem a purchase that was made successfully towards the PlayStation Store for a character that the current player owns
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
      @param CharacterId The ulid of the character to redeem this purchase for
      @param TransactionId The transaction id from the PlayStation Store of the purchase to redeem
      @param AuthCode The authorization code from the PlayStation Store of the purchase to redeem
      @param EntitlementLabel The entitlement label configured in the NP service for the entitlement that this redemption relates to
      @param ServiceLabel Optional: The NP service label
      @param ServiceName Optional: The abbreviation of the service name of the ASM service ID service that was used when configuring the serviceIds. Possible Values: pssdc, cce. Default Value: pssdc
      @param Environment Optional: The id of the environment you wish to make the request against. Allowed values: 1, 8, 256
      @param UseCount Optional: The use count for this redemption
      @param OnCompletedRequest Delegate for handling the server response
     */
    //UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid,ServiceLabel,ServiceName,Environment,UseCount", ForPlayerWithUlid="", ServiceLabel="", ServiceName="", Environment=-1, UseCount=-1))
    //static void RedeemPlayStationStorePurchaseForCharacter(const FString& ForPlayerWithUlid, const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedRequest);
#endif

    /**
      Begin a Steam purchase for a catalog item (initiate entitlement creation).
     
      Steam IAP must be configured. Call this to create a pending entitlement in Steam. Poll status with QuerySteamPurchaseRedemptionStatus until Approved, then finalize with FinalizeSteamPurchaseRedemption.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param SteamId Steam user id making the purchase
      @param Currency Currency code to use
      @param Language Language code to use
      @param CatalogItemId LootLocker catalog item id to purchase
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void BeginSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest);

    /**
      Begin a Steam purchase for a catalog item on a specific class.
     
      Same Steam purchase flow as BeginSteamPurchaseRedemption but class‑scoped.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param ClassId Id of the class the purchased item should be associated with
      @param SteamId Steam user id making the purchase
      @param Currency Currency code to use
      @param Language Language code to use
      @param CatalogItemId LootLocker catalog item id to purchase
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void BeginSteamPurchaseRedemptionForClass(const FString& ForPlayerWithUlid, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedRequest);

    /**
      Query the status of a Steam purchase entitlement.
     
      Use to poll a pending purchase (awaiting approval) or inspect a completed one.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param EntitlementId Id of the entitlement to check
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void QuerySteamPurchaseRedemptionStatus(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedRequest);

    /**
      Finalize an Approved Steam purchase (redeem entitlement items).
     
      Steam entitlement must be in Approved state first.
     
      @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
      @param EntitlementId Id of the entitlement to finalize
      @param OnCompletedRequest Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Purchases", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void FinalizeSteamPurchaseRedemption(const FString& ForPlayerWithUlid, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedRequest);

    //==================================================
    // Triggers
    //==================================================

    /**
     Invoke triggers by their keys.

     Response lists:
     - succeeded: keys that executed successfully
     - failed: keys that failed and the reason

     The overall request may succeed even if some triggers fail; inspect both lists.

     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used
     @param KeysToInvoke Keys of the triggers to invoke
     @param OnComplete Delegate for handling the server response
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
    // Broadcasts
    //==================================================

    /**
     List broadcast messages for this game with specified localisation and pagination settings

     @param Languages Optional: Array of language codes to get localized broadcasts for
     @param PerPage Optional: Number of broadcasts per page
     @param Page Optional: Page number for pagination
     @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     @param OnComplete Delegate for handling the server response
    */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Broadcasts", meta = (AdvancedDisplay = "Languages,PerPage,Page,ForPlayerWithUlid", ForPlayerWithUlid = "", PerPage = -1, Page = -1, AutoCreateRefTerm="Languages"))
    static void ListBroadcasts(const TArray<FString>& Languages, int32 PerPage, int32 Page, const FString& ForPlayerWithUlid, const FLootLockerListBroadcastsResponseBP& OnComplete);

    //==================================================
    // Collectables
    //==================================================

    /**
     * This endpoint will return all the collectables a game has set up. It will hold a set of Collectables, with Groups inside which in turn contain Items.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetAllCollectablesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllCollectables(const FString& ForPlayerWithUlid, const FCollectablesResponseDelegateBP& OnGetAllCollectablesCompleted);

    /**
     * Collect an item.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param Item The slug is a combination of the name of the Collectable, the Group and the Item. Simply concatenate them with a . as a seperator.
     * @param OnCollectItemCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Collectables", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CollectItem(const FString& ForPlayerWithUlid, const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCollectItemCompleted);

    //==================================================
    // Messages
    //==================================================

    /**
     * Get all messages for a player.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param OnGetMessagesCompleted Delegate for handling the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Messages", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetMessages(const FString& ForPlayerWithUlid, const FMessagesResponseDelegateBP& OnGetMessagesCompleted);

    //==================================================
    // Leaderboard
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
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param MemberId player_id if player type leaderboard, otherwise this is the identifier you wish to use for this score
     * @param Count Number of members returned per page
     * @param After Cursor for pagination, a cursor will be returned in the response
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Leaderboard", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetAllMemberRanks(const FString& ForPlayerWithUlid, FString MemberId, const int Count, const int After, const FLootLockerGetAllMemberRanksResponseBP& OnCompletedRequestBP);

    /**
     * Get rank for a set of members for a leaderboard. If leaderboard is of type player a player will also be in the response.
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
    static void GetLeaderboardArchive(const FString& ForPlayerWithUlid, const FString& Key, int Count, const FString& After, const FLootLockerLeaderboardArchiveDetailResponseBP& OnCompletedRequestBP);

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
    // Drop Table
    //==================================================

    /**
     * Compute and lock the specified drop table.
     * When you wish to evaluate a drop table and lock the drops from it in place, you call this method.
     * The response will hold information on the assets that are dropped, and can be picked up using the Pick endpoint.
     *
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param TableId Drop table ID
     * @param OnCompletedRequestBP Delegate for handling the server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | DropTable", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void ComputeAndLockDropTable(const FString& ForPlayerWithUlid, int TableId, const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP);

    /**
     * Picks drops from a locked drop table.
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
     * List followers for a specific player (cursor pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context (empty uses default player)
     * @param PlayerPublicUid Public UID whose followers to list
     * @param Cursor Optional: pagination cursor (empty for first page)
     * @param Count Optional: items per page (<=0 uses backend default)
     * @param OnResponseCompletedBP Delegate for server response
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "Cursor,Count,ForPlayerWithUlid", Cursor="", Count=-1, ForPlayerWithUlid=""))
    static void ListFollowersForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * List followers for the requesting player (cursor pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param Cursor Optional pagination cursor
     * @param Count Optional items per page
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "Cursor,Count,ForPlayerWithUlid", Cursor="", Count=-1, ForPlayerWithUlid=""))
    static void ListFollowers(const FString& ForPlayerWithUlid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * List players a specific player is following (cursor pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param PlayerPublicUid Public UID whose following list to fetch
     * @param Cursor Optional pagination cursor
     * @param Count Optional items per page
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "Cursor,Count,ForPlayerWithUlid", Cursor="", Count=-1, ForPlayerWithUlid=""))
    static void ListFollowingForPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /**
     * List players the requesting player is following (cursor pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param Cursor Optional pagination cursor
     * @param Count Optional items per page
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "Cursor,Count,ForPlayerWithUlid", Cursor="", Count=-1, ForPlayerWithUlid=""))
    static void ListFollowing(const FString& ForPlayerWithUlid, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP);

    /** 
     * Follow a player.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerPublicUid Public UID to follow
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void FollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP);
    
    /** 
     * Unfollow a player.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerPublicUid Public UID to unfollow
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Followers", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnfollowPlayer(const FString& ForPlayerWithUlid, const FString& PlayerPublicUid, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP);

    //==================================================
    // Friends
    //==================================================

    /** 
     * List friends for the requesting player (page-based pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param Page Optional 1-based page index (<=0 = default)
     * @param PerPage Optional items per page (<=0 backend default)
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "Page,PerPage,ForPlayerWithUlid", Page=-1, PerPage=-1, ForPlayerWithUlid=""))
    static void ListFriends(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP);

    /** 
     * List incoming friend requests (page-based pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param Page Optional page index
     * @param PerPage Optional items per page
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "Page,PerPage,ForPlayerWithUlid", Page=-1, PerPage=-1, ForPlayerWithUlid=""))
    static void ListIncomingFriendRequests(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP);

    /** 
     * List outgoing friend requests (page-based pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param Page Optional page index
     * @param PerPage Optional items per page
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "Page,PerPage,ForPlayerWithUlid", Page=-1, PerPage=-1, ForPlayerWithUlid=""))
    static void ListOutgoingFriendRequests(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP);
    
    /** 
     * Send friend request.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID ULID to send request to
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void SendFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);
    
    /** 
     * Delete friend.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID ULID of friend to delete
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeleteFriend(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);
    
    /** 
     * Cancel outgoing friend request.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID Target ULID
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void CancelOutgoingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);
    
    /** 
     * Accept incoming friend request.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID ULID whose request is accepted
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void AcceptIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);
    
    /**
     * Decline incoming friend request.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID ULID whose request is declined
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void DeclineIncomingFriendRequest(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);
    
    /** 
     * List blocked players (page-based pagination supported).
     * @param ForPlayerWithUlid Optional player ulid context
     * @param Page Optional page index
     * @param PerPage Optional items per page
     * @param OnResponseCompletedBP Delegate
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "Page,PerPage,ForPlayerWithUlid", Page=-1, PerPage=-1, ForPlayerWithUlid=""))
    static void ListBlockedPlayers(const FString& ForPlayerWithUlid, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP);
    
    /** 
     * Get friend info.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param FriendUlid Friend ULID
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void GetFriend(const FString& ForPlayerWithUlid, const FString& FriendUlid, const FLootLockerGetFriendResponseBP& OnResponseCompletedBP);
    
    /** 
     * Block player.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID ULID to block
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void BlockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);
    
    /** 
     * Unblock player.
     * 
     * @param ForPlayerWithUlid Optional: Execute the request for the player with the specified ulid. If not supplied, the default player will be used.
     * @param PlayerULID ULID to unblock
     * @param OnResponseCompletedBP Delegate for handling the the server response.
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Friends", meta = (AdvancedDisplay = "ForPlayerWithUlid", ForPlayerWithUlid=""))
    static void UnblockPlayer(const FString& ForPlayerWithUlid, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP);

    //==================================================
    // Miscellaneous
    //==================================================

    /**
    * Get the current time of the server. Can also be used to ping the server
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
