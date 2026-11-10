// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerGameEndpoints.generated.h"

UENUM(BlueprintType)
enum class ELootLockerHTTPMethod : uint8
{
    LL_GET = 0          UMETA(DisplayName = "GET"),
    LL_POST = 1         UMETA(DisplayName = "POST"),
    LL_DELETE = 2       UMETA(DisplayName = "DELETE"),
    LL_PUT = 3          UMETA(DisplayName = "PUT"),
    LL_HEAD = 4         UMETA(DisplayName = "HEAD"),
    LL_CREATE = 5       UMETA(DisplayName = "CREATE"),
    LL_OPTIONS = 6      UMETA(DisplayName = "OPTIONS"),
    LL_PATCH = 7        UMETA(DisplayName = "PATCH"),
    LL_UPLOAD = 8       UMETA(DisplayName = "UPLOAD")
};

/**
 * Maps ELootLockerHTTPMethod to the verb sent in the HTTP request line.
 *
 * The mapping is written out explicitly rather than read back from the enum's DisplayName
 * metadata: UEnum::GetDisplayNameTextByValue() only honours UMETA(DisplayName=...) when
 * WITH_EDITOR is set (WITH_METADATA is WITH_EDITORONLY_DATA, so the metadata is stripped at
 * cook time) and silently falls back to the C++ enumerator name in a packaged build. Deriving
 * the verb from metadata therefore works in the editor and breaks in a shipped game.
 *
 * Keep this switch exhaustive; it has no default so that adding a member to the enum produces
 * a -Wswitch build error rather than a silently wrong verb.
 */
namespace LootLockerHttpMethodUtils
{
    inline FString GetVerbString(ELootLockerHTTPMethod Method)
    {
        switch (Method)
        {
        case ELootLockerHTTPMethod::LL_GET:     return TEXT("GET");
        case ELootLockerHTTPMethod::LL_POST:    return TEXT("POST");
        case ELootLockerHTTPMethod::LL_DELETE:  return TEXT("DELETE");
        case ELootLockerHTTPMethod::LL_PUT:     return TEXT("PUT");
        case ELootLockerHTTPMethod::LL_HEAD:    return TEXT("HEAD");
        case ELootLockerHTTPMethod::LL_CREATE:  return TEXT("CREATE");
        case ELootLockerHTTPMethod::LL_OPTIONS: return TEXT("OPTIONS");
        case ELootLockerHTTPMethod::LL_PATCH:   return TEXT("PATCH");
        case ELootLockerHTTPMethod::LL_UPLOAD:  return TEXT("UPLOAD");
        }
        return TEXT("");
    }
}

UENUM(BlueprintType)
enum class ELootLockerApiType : uint8
{
    LL_GAME = 0         UMETA(DisplayName = "GAME"),
    LL_WHITELABEL = 1   UMETA(DisplayName = "WL"),
    LL_WEBSOCKET = 2    UMETA(DisplayName = "WEBSOCKET"),
};

USTRUCT(BlueprintType)
struct FLootLockerEndPoints
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString endpoint = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    ELootLockerHTTPMethod requestMethod = ELootLockerHTTPMethod::LL_GET;
};

UCLASS()
class LOOTLOCKERSDK_API ULootLockerGameEndpoints : public UObject
{
    GENERATED_BODY()
public:
    //Auth
    static FLootLockerEndPoints StartSessionEndpoint;
    static FLootLockerEndPoints StartNintendoSwitchSessionEndpoint;
    static FLootLockerEndPoints StartXboxSessionEndpoint;
    static FLootLockerEndPoints StartAppleSessionEndpoint;
    static FLootLockerEndPoints RefreshAppleSessionEndpoint;
    static FLootLockerEndPoints StartAppleGameCenterSessionEndpoint;
    static FLootLockerEndPoints RefreshAppleGameCenterSessionEndpoint;
    static FLootLockerEndPoints StartGoogleSessionEndpoint;
    static FLootLockerEndPoints RefreshGoogleSessionEndpoint;
    static FLootLockerEndPoints StartGooglePlayGamesSessionEndpoint;
    static FLootLockerEndPoints RefreshGooglePlayGamesSessionEndpoint;
    static FLootLockerEndPoints StartEpicSessionEndpoint;
    static FLootLockerEndPoints RefreshEpicSessionEndpoint;
    static FLootLockerEndPoints VerifyPlayerIdEndPoint;
    static FLootLockerEndPoints EndSessionEndpoint;
    static FLootLockerEndPoints GuestloginEndpoint;
    static FLootLockerEndPoints MetaSessionEndpoint;
    static FLootLockerEndPoints SteamSessionEndpoint;
    static FLootLockerEndPoints StartDiscordSessionEndpoint;
    static FLootLockerEndPoints RefreshDiscordSessionEndpoint;
    static FLootLockerEndPoints PlaystationNetworkV3SessionEndpoint;
    static FLootLockerEndPoints GetPlayerBanStatusEndpoint;

    // Connected Accounts
    static FLootLockerEndPoints ListConnectedAccountsEndpoint;
    static FLootLockerEndPoints DisconnectAccountEndpoint;
    static FLootLockerEndPoints ConnectProviderToAccountEndpoint;
    static FLootLockerEndPoints AttachRemoteSessionToAccountEndpoint;
    static FLootLockerEndPoints TransferProvidersBetweenAccountsEndpoint;

    // Friends
    static FLootLockerEndPoints ListFriendsEndpoint;
    static FLootLockerEndPoints GetFriendEndpoint;
    static FLootLockerEndPoints ListIncomingFriendRequestsEndpoint;
    static FLootLockerEndPoints ListOutgoingFriendRequestsEndpoint;
    static FLootLockerEndPoints SendFriendRequestEndpoint;
    static FLootLockerEndPoints DeleteFriendEndpoint;
    static FLootLockerEndPoints CancelOutgoingFriendRequestEndpoint;
    static FLootLockerEndPoints AcceptIncomingFriendRequestEndpoint;
    static FLootLockerEndPoints DeclineIncomingFriendRequestEndpoint;
    static FLootLockerEndPoints ListBlockedPlayersEndpoint;
    static FLootLockerEndPoints BlockPlayerEndpoint;
    static FLootLockerEndPoints UnblockPlayerEndpoint;

    // Followers
    static FLootLockerEndPoints ListFollowersEndpoint;
    static FLootLockerEndPoints ListFollowingEndpoint;
    static FLootLockerEndPoints FollowPlayerEndpoint;
    static FLootLockerEndPoints UnfollowPlayerEndpoint;

    // Remote Sessions
    static FLootLockerEndPoints LeaseRemoteSessionEndpoint;
    static FLootLockerEndPoints LeaseRemoteSessionForLinkingEndpoint;
    static FLootLockerEndPoints StartRemoteSessionEndpoint;
    static FLootLockerEndPoints RefreshRemoteSessionEndpoint;

    // White Label
    static FLootLockerEndPoints WhiteLabelSignupEndpoint;
    static FLootLockerEndPoints WhiteLabelSignupFieldsEndpoint;
    static FLootLockerEndPoints WhiteLabelLoginEndpoint;
    static FLootLockerEndPoints WhiteLabelAuthEndpoint;
    static FLootLockerEndPoints WhiteLabelVerifySessionEndpoint;
    static FLootLockerEndPoints WhiteLabelRequestPasswordResetEndpoint;
    static FLootLockerEndPoints WhiteLabelRequestVerificationEndpoint;

    // Files
    static FLootLockerEndPoints FileUploadEndpoint;
    static FLootLockerEndPoints FileUpdateEndpoint;
    static FLootLockerEndPoints ListFilesEndpoint;
    static FLootLockerEndPoints GetSingleFileEndpoint;
    static FLootLockerEndPoints DeleteFileEndpoint;
    static FLootLockerEndPoints ListOtherPlayersFilesEndpoint;
    static FLootLockerEndPoints ListFileRevisionsEndpoint;
    static FLootLockerEndPoints GetFileRevisionEndpoint;
    static FLootLockerEndPoints PromoteFileRevisionEndpoint;
    static FLootLockerEndPoints GetFileByKeyEndpoint;
    static FLootLockerEndPoints ListFileRevisionsByKeyEndpoint;
    static FLootLockerEndPoints GetFileRevisionByKeyEndpoint;
    static FLootLockerEndPoints PromoteFileRevisionByKeyEndpoint;
    static FLootLockerEndPoints DeleteFileByKeyEndpoint;
    static FLootLockerEndPoints CreateFileDownloadLinkEndpoint;

    //Player
    static FLootLockerEndPoints GetInfoFromSession;
    static FLootLockerEndPoints ListPlayerInfo;
    static FLootLockerEndPoints GetPlayerInventoryEndPoint;
    static FLootLockerEndPoints ListPlayerSimpleInventoryEndPoint;
    static FLootLockerEndPoints GetCurrencyBalance;
    static FLootLockerEndPoints CheckPlayerAssetActivationEndpoint;
    static FLootLockerEndPoints CheckPlayerAssetDeactivationEndpoint;
    static FLootLockerEndPoints InitiateDLCMigration;
    static FLootLockerEndPoints GetDLCsMigrated;
    static FLootLockerEndPoints SetProfilePrivate;
    static FLootLockerEndPoints SetProfilePublic;
    static FLootLockerEndPoints SetPlayerName;
    static FLootLockerEndPoints GetPlayerName;
    static FLootLockerEndPoints LookupMultiplePlayerNamesUsingIDs;
    static FLootLockerEndPoints LookupMultiplePlayer1stPlatformID;
    static FLootLockerEndPoints DeletePlayer;

    // Items & Item Templates
    static FLootLockerEndPoints ListItemTemplatesEndpoint;
    static FLootLockerEndPoints ListPlayerInventoryItemsEndpoint;
    static FLootLockerEndPoints GetPlayerInventoryItemEndpoint;
    static FLootLockerEndPoints DeletePlayerInventoryItemEndpoint;
    static FLootLockerEndPoints ConsumePlayerInventoryItemEndpoint;
    static FLootLockerEndPoints SplitPlayerInventoryItemStackEndpoint;
    static FLootLockerEndPoints MergePlayerInventoryItemStacksEndpoint;

    //Heroes
    static FLootLockerEndPoints GetGameHeroes;
    static FLootLockerEndPoints ListPlayerHeroes;
    static FLootLockerEndPoints ListOtherPlayersHeroesBySteamID64;
    static FLootLockerEndPoints CreateHero;
    static FLootLockerEndPoints GetHero;
    static FLootLockerEndPoints GetOtherPlayersDefaultHeroBySteamID64;
    static FLootLockerEndPoints UpdateHero;
    static FLootLockerEndPoints DeleteHero;
    static FLootLockerEndPoints GetHeroInventory;
    static FLootLockerEndPoints GetHeroLoadout;
    static FLootLockerEndPoints GetOtherPlayersHeroLoadout;
    static FLootLockerEndPoints AddAssetToHeroLoadout;
    static FLootLockerEndPoints RemoveAssetToHeroLoadout;

    //Player Progressions
    static FLootLockerEndPoints GetAllPlayerProgressions;
    static FLootLockerEndPoints GetAllOtherPlayersProgressions;
    static FLootLockerEndPoints GetSinglePlayerProgression;
    static FLootLockerEndPoints GetSingleOtherPlayersProgression;
    static FLootLockerEndPoints AddPointsToPlayerProgression;
    static FLootLockerEndPoints SubtractPointsFromPlayerProgression;
    static FLootLockerEndPoints ResetPlayerProgression;
    static FLootLockerEndPoints DeletePlayerProgression;

    //Character
    static FLootLockerEndPoints GetCharacterLoadoutEndpoint;
    static FLootLockerEndPoints UpdateCharacterEndpoint;
    static FLootLockerEndPoints EquipAssetToDefaultCharacterEndpoint;
    static FLootLockerEndPoints EquipAssetToCharacterByIdEndpoint;
    static FLootLockerEndPoints CreateCharacterEndpoint;
    static FLootLockerEndPoints DeleteCharacterEndpoint;
    static FLootLockerEndPoints ListPlayerCharactersEndpoint;
    static FLootLockerEndPoints ListCharacterTypesByIdEndpoint;
    static FLootLockerEndPoints UnEquipAssetToDefaultCharacterEndpoint;
    static FLootLockerEndPoints UnEquipAssetToCharacterByIdEndpoint;
    static FLootLockerEndPoints GetCurrentLoadoutToDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetEquippableContextstoDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetEquippableContextsByCharacterIDEndpoint;
    static FLootLockerEndPoints GetOtherPlayersCharacterLoadouts;
    static FLootLockerEndPoints GetOtherPlayersCharacterLoadoutsByUid;

    //Character Progressions
    static FLootLockerEndPoints GetAllCharacterProgressions;
    static FLootLockerEndPoints GetSingleCharacterProgression;
    static FLootLockerEndPoints AddPointsToCharacterProgression;
    static FLootLockerEndPoints SubtractPointsFromCharacterProgression;
    static FLootLockerEndPoints ResetCharacterProgression;
    static FLootLockerEndPoints DeleteCharacterProgression;

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
    static FLootLockerEndPoints GetUniversalAssetsEndpoint;
    static FLootLockerEndPoints GrantAssetToPlayerInventory;
    static FLootLockerEndPoints ListAssetsEndpoint;

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
    static FLootLockerEndPoints DeleteAssetInstanceFromPlayerInventory;

    //Instance Progressions
    static FLootLockerEndPoints GetAllInstanceProgressions;
    static FLootLockerEndPoints GetSingleInstanceProgression;
    static FLootLockerEndPoints AddPointsToInstanceProgression;
    static FLootLockerEndPoints SubtractPointsFromInstanceProgression;
    static FLootLockerEndPoints ResetInstanceProgression;
    static FLootLockerEndPoints DeleteInstanceProgression;

    //User Generated Content
    static FLootLockerEndPoints CreateAssetCandidateEndpoint;
    static FLootLockerEndPoints UpdateAssetCandidateEndpoint;
    static FLootLockerEndPoints DeleteAssetCandidateEndpoint;
    static FLootLockerEndPoints GetAllAssetCandidatesEndpoint;
    static FLootLockerEndPoints GetAssetCandidateEndpoint;
    static FLootLockerEndPoints AddFileToAssetCandidateEndpoint;
    static FLootLockerEndPoints DeleteFileFromAssetCandidateEndpoint;

    //Maps
    static FLootLockerEndPoints GetAllMapsEndpoint;

    //Purchases
    static FLootLockerEndPoints ActivateRentalAssetEndpoint;

    static FLootLockerEndPoints PurchaseCatalogItem;
    static FLootLockerEndPoints RedeemAppleAppStorePurchase;
    static FLootLockerEndPoints RedeemGooglePlayStorePurchase;
    static FLootLockerEndPoints RedeemEpicStorePurchase;
    static FLootLockerEndPoints RedeemPlayStationStorePurchase;

    static FLootLockerEndPoints XboxServiceTicket;
    static FLootLockerEndPoints RedeemXboxStorePurchase;

    static FLootLockerEndPoints BeginSteamPurchaseRedemption;
    static FLootLockerEndPoints QuerySteamPurchaseRedemptionStatus;
    static FLootLockerEndPoints FinalizeSteamPurchaseRedemption;
    static FLootLockerEndPoints RefundByEntitlementIds;

    static FLootLockerEndPoints CreateStripeCheckoutSession;

    static FLootLockerEndPoints InitiateAsyncPurchase;
    static FLootLockerEndPoints PollAsyncPurchaseStatus;
    static FLootLockerEndPoints RetryAsyncPurchase;

    //Trigger Events
    static FLootLockerEndPoints TriggerEventEndpoint;
    static FLootLockerEndPoints GetTriggeredEventsEndpoint;

    //Triggers
    static FLootLockerEndPoints InvokeTriggers;

    //Notifications
    static FLootLockerEndPoints ListNotifications;
    static FLootLockerEndPoints ReadNotifications;
    static FLootLockerEndPoints ReadAllNotifications;

    // Broadcasts
    static FLootLockerEndPoints ListBroadcasts;

    //Messages
    static FLootLockerEndPoints GetMessagesEndpoint;

    //Leaderboard
    static FLootLockerEndPoints ListLeaderboards;
    static FLootLockerEndPoints GetMemberRank;
    static FLootLockerEndPoints GetByListOfMembers;
    static FLootLockerEndPoints GetScoreList;
    static FLootLockerEndPoints GetScoreListAfter;
    static FLootLockerEndPoints SubmitScore;
    static FLootLockerEndPoints QueryScore;
    static FLootLockerEndPoints IncrementScore;
    static FLootLockerEndPoints GetAllMemberRanks;
    static FLootLockerEndPoints ListLeaderboardArchive;
    static FLootLockerEndPoints GetLeaderboardArchive;
    static FLootLockerEndPoints GetLeaderboardDetails;

    //Progressions
    static FLootLockerEndPoints GetAllProgressions;
    static FLootLockerEndPoints GetSingleProgression;
    static FLootLockerEndPoints GetProgressionTiers;

    //DropTables
    static FLootLockerEndPoints ComputeAndLockDropTable;
    static FLootLockerEndPoints PickDropsFromDropTable;

    // Currencies
    static FLootLockerEndPoints ListCurrencies;
    static FLootLockerEndPoints GetCurrencyDetails;
    static FLootLockerEndPoints GetCurrencyDenominationsByCode;

    // Platform Keys
    static FLootLockerEndPoints ListPlatformKeys;

    // Balances
    static FLootLockerEndPoints ListBalancesInWallet;
    static FLootLockerEndPoints GetWalletByWalletId;
    static FLootLockerEndPoints GetWalletByHolderId;
    static FLootLockerEndPoints CreditBalanceToWallet;
    static FLootLockerEndPoints DebitBalanceToWallet;
    static FLootLockerEndPoints CreateWallet;

    // Catalogs
    static FLootLockerEndPoints ListCatalogs;
    static FLootLockerEndPoints DeprecatedListCatalogItemsByKey;
    static FLootLockerEndPoints ListCatalogItemsByKey;
    static FLootLockerEndPoints ListCatalogItemsById;

    // Entitlements
    static FLootLockerEndPoints ListEntitlements;
    static FLootLockerEndPoints GetEntitlement;

    // Miscellaneous
    static FLootLockerEndPoints GetServerTimeEndpoint;
    static FLootLockerEndPoints GetGameInfoEndpoint;

    // Crash
    static FLootLockerEndPoints Crashes;

    // Feedback
    static FLootLockerEndPoints ListFeedbackCategories;
    static FLootLockerEndPoints SendFeedback;

    // Error Reporting
    static FLootLockerEndPoints ReportSDKError;

    // Metadata
    static FLootLockerEndPoints ListMetadata;
    static FLootLockerEndPoints GetMultisourceMetadata;
    static FLootLockerEndPoints MetadataActions;

    // Presence (WebSocket)
    static FLootLockerEndPoints PresenceWebSocketEndpoint;

private:
    static FString BaseUrl;
    static FString GameUrlSuffix;
    static FLootLockerEndPoints InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method, ELootLockerApiType ApiType = ELootLockerApiType::LL_GAME);
public:
    /** Returns the configured base URL (e.g. "https://{domainKey}api.lootlocker.com/"). */
    static const FString& GetBaseUrl() { return BaseUrl; }
};
