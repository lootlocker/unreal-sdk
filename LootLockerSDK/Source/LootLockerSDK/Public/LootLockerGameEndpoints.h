// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerGameEndpoints.generated.h"

UENUM(BlueprintType)
enum class ELootLockerHTTPMethod : uint8
{
    GET = 0         UMETA(DisplayName = "GET"),
    POST = 1        UMETA(DisplayName = "POST"),
    DELETE = 2      UMETA(DisplayName = "DELETE"),
    PUT = 3         UMETA(DisplayName = "PUT"),
    HEAD = 4        UMETA(DisplayName = "HEAD"),
    CREATE = 5      UMETA(DisplayName = "CREATE"),
    OPTIONS = 6     UMETA(DisplayName = "OPTIONS"),
    PATCH = 7       UMETA(DisplayName = "PATCH"),
    UPLOAD = 8      UMETA(DisplayName = "UPLOAD")
};

USTRUCT(BlueprintType)
struct FLootLockerEndPoints
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString endpoint;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    ELootLockerHTTPMethod requestMethod = ELootLockerHTTPMethod::GET;
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
    static FLootLockerEndPoints StartEpicSessionEndpoint;
    static FLootLockerEndPoints RefreshEpicSessionEndpoint;
    static FLootLockerEndPoints VerifyPlayerIdEndPoint;
    static FLootLockerEndPoints EndSessionEndpoint;
    static FLootLockerEndPoints GuestloginEndpoint;
    static FLootLockerEndPoints MetaSessionEndpoint;

    // Remote Sessions
    static FLootLockerEndPoints LeaseRemoteSession;
    static FLootLockerEndPoints StartRemoteSession;

    // White Label
    static FLootLockerEndPoints WhiteLabelSignupEndpoint;
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

    //Player
    static FLootLockerEndPoints GetPlayerInfoEndPoint;
    static FLootLockerEndPoints GetPlayerInventoryEndPoint;
    static FLootLockerEndPoints SubmitXpEndpoint;
    static FLootLockerEndPoints GetOtherPlayersXpAndLevelEndpoint;
    static FLootLockerEndPoints GetMultipleOtherPlayersXPAndLevel;
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
    static FLootLockerEndPoints GetSinglePlayerProgression;
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
    static FLootLockerEndPoints ListPlayerCharactersEndpoint;
    static FLootLockerEndPoints ListCharacterTypesByIdEndpoint;
    static FLootLockerEndPoints UnEquipAssetToDefaultCharacterEndpoint;
    static FLootLockerEndPoints UnEquipAssetToCharacterByIdEndpoint;
    static FLootLockerEndPoints GetCurrentLoadoutToDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetEquippableContextstoDefaultCharacterEndpoint;
    static FLootLockerEndPoints GetEquippableContextsByCharacterIDEndpoint;

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

    //Missions
    static FLootLockerEndPoints GetAllMissionsEndpoint;
    static FLootLockerEndPoints GetMissionEndpoint;
    static FLootLockerEndPoints StartMissionEndpoint;
    static FLootLockerEndPoints FinishMissionEndpoint;

    //Maps
    static FLootLockerEndPoints GetAllMapsEndpoint;

    //Purchases
    static FLootLockerEndPoints PurchaseEndpoint;
    static FLootLockerEndPoints IOSPurchaseEndpoint;
    static FLootLockerEndPoints AndroidPurchaseEndpoint;
    static FLootLockerEndPoints PollingOrderStatusEndpoint;
    static FLootLockerEndPoints ActivateRentalAssetEndpoint;
    static FLootLockerEndPoints GetOrderDetailsEndpoint;
    static FLootLockerEndPoints PurchaseCatalogItem;

    //Trigger Events
    static FLootLockerEndPoints TriggerEventEndpoint;
    static FLootLockerEndPoints GetTriggeredEventsEndpoint;

    //Collectables
    static FLootLockerEndPoints GetAllCollectablesEndpoint;
    static FLootLockerEndPoints CollectItemEndpoint;

    //Messages
    static FLootLockerEndPoints GetMessagesEndpoint;

    //Leaderboard
    static FLootLockerEndPoints GetMemberRank;
    static FLootLockerEndPoints GetByListOfMembers;
    static FLootLockerEndPoints GetScoreList;
    static FLootLockerEndPoints GetScoreListAfter;
    static FLootLockerEndPoints SubmitScore;
    static FLootLockerEndPoints GetAllMemberRanks;

    //Progressions
    static FLootLockerEndPoints GetAllProgressions;
    static FLootLockerEndPoints GetSingleProgression;
    static FLootLockerEndPoints GetProgressionTiers;

    //DropTables
    static FLootLockerEndPoints ComputeAndLockDropTable;
    static FLootLockerEndPoints PickDropsFromDropTable;

    // Currencies
    static FLootLockerEndPoints ListCurrencies;
    static FLootLockerEndPoints GetCurrencyDenominationsByCode;

    // Balances
    static FLootLockerEndPoints ListBalancesInWallet;
    static FLootLockerEndPoints GetWalletByWalletId;
    static FLootLockerEndPoints GetWalletByHolderId;
    static FLootLockerEndPoints CreditBalanceToWallet;
    static FLootLockerEndPoints DebitBalanceToWallet;
    static FLootLockerEndPoints CreateWallet;

    // Catalogs
    static FLootLockerEndPoints ListCatalogs;
    static FLootLockerEndPoints ListCatalogItemsByKey;

    // Miscellaneous
    static FLootLockerEndPoints GetServerTimeEndpoint;

    // Crash
    static FLootLockerEndPoints Crashes;
private:
    static FString GameBaseUrl;

    static FLootLockerEndPoints InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method);
};
