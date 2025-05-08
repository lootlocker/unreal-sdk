// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerNotificationsRequestHandler.generated.h"

//==================================================
// Enum Definitions
//==================================================

/**
 * Enum of the different available priorities for notifications
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerNotificationPriority : uint8
{
    low = 0,
    medium = 1,
    high = 2,
    emergency = 3,
};

/**
 * Enum of the different available sources for notifications
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerNotificationSource : uint8
{
    triggers = 0,
    purchasing_steam_store = 1,
    purchasing_apple_app_store = 2,
    purchasing_google_play_store = 3,
    purchasing_lootlocker_store = 4,
    twitch_drop = 5,
    lootlocker_console = 6,
    lootlocker_server_api = 7,
};

/**
 * Enum of the different types of values that can be in the notification body. Use this to know how to parse the body.
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerNotificationContentBodyType : uint8
{
    none = 0,
    null = 1,
    reward = 2,
    json_string = 3,
    json_integer = 4,
    json_decimal = 5,
    json_bool = 6,
    json_object = 7,
    json_array = 8,
    json_array_string = 9,
    json_array_integer = 10,
    json_array_decimal = 11,
    json_array_bool = 12,
    json_array_object = 13,
    unknown = 14,
};

/**
 * Enum of the different kinds of notification bodies possible, use this to figure out how to parse the notification body
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerNotificationContentRewardKind : uint8
{
    group = 0,
    currency = 1,
    asset = 2,
    progression_reset = 3,
    progression_points = 4,
};

/**
 * Enum for custom notification filtering
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerCustomNotificationFiltering : uint8
{
    All = 0,
    Custom_only = 1,
    LootLocker_only = 2,
};

//==================================================
// Static String Definitions
//==================================================

/**
 * Set of static string definitions to use for matching in different Notification contexts
 */
struct LootLockerNotificationsStaticStrings
{
    /**
     * Possible types of notifications
     */
    struct NotificationTypes
    {
        static const FString PullRewardAcquired;
    };

    /**
     * Possible sources for notifications
     */
    struct NotificationSources
    {
        static const FString Triggers;
        struct Purchasing
        {
            static const FString SteamStore;
            static const FString AppleAppStore;
            static const FString GooglePlayStore;
            static const FString LootLocker;
        };
        static const FString TwitchDrop;
        static const FString LootLockerConsole;
        static const FString LootLockerServerApi;
    };

    /**
     * The standard context keys to expect for different notification sources
     */
    struct StandardContextKeys
    {
        /**
         * Standard context keys to expect when source is triggers
         */
        struct Triggers
        {
            static const FString Id;
            static const FString Key;
            static const FString Limit;
        };

        /**
         * Standard context keys to expect when source is purchasing
         */
        struct Purchasing
        {
            /**
             * Standard context keys to expect when source is purchasing from the Steam store
             */
            struct SteamStore
            {
                static const FString CatalogId;
                static const FString CatalogItemId;
                static const FString EntitlementId;
                static const FString CharacterId;
            };
            /**
             * Standard context keys to expect when source is purchasing from the Apple app store
             */
            struct AppleAppStore
            {
                static const FString CatalogId;
                static const FString CatalogItemId;
                static const FString TransactionId;
            };
            /**
             * Standard context keys to expect when source is purchasing from the GooglePlay store
             */
            struct GooglePlayStore
            {
                static const FString CatalogId;
                static const FString CatalogItemId;
                static const FString ProductId;
            };
            /**
             * Standard context keys to expect when source is purchasing from LootLocker
             */
            struct LootLocker
            {
                static const FString CatalogId;
                static const FString CatalogItemId;
            };
        };
        /**
         * Standard context keys to expect when source is a Twitch Drop
         */
        struct TwitchDrop
        {
            static const FString TwitchRewardId;
        };
    };
};

/**
 * Blueprint exposure of the set of static string definitions to use for matching in different Notification contexts
 */
UCLASS(Blueprintable)
class LOOTLOCKERSDK_API ULootLockerStaticNotificationStringBlueprintCallables : public UObject
{
    GENERATED_BODY()
public:
    /**
     * Static String for use in Notifications -- Matching Notification type Pull Reward Acquired
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Types")
    static FString GetTypePullRewardAcquiredString() { return LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired; };
    /**
     * Static String for use in Notifications -- Matching Notification source Triggers
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | Triggers")
    static FString GetNotificationsSourceTriggersString() { return LootLockerNotificationsStaticStrings::NotificationSources::Triggers; };
    /**
     * Static String for use in Notifications -- Matching Notification source Purchasing SteamStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | Purchasing")
    static FString GetNotificationsSourcePurchasingSteamStoreString() { return LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::SteamStore; };
    /**
     * Static String for use in Notifications -- Matching Notification source Purchasing AppleAppStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | Purchasing")
    static FString GetNotificationsSourcePurchasingAppleAppStoreString() { return LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::AppleAppStore; };
    /**
     * Static String for use in Notifications -- Matching Notification source Purchasing GooglePlayStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | Purchasing")
    static FString GetNotificationsSourcePurchasingGooglePlayStoreString() { return LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore; };
    /**
     * Static String for use in Notifications -- Matching Notification source Purchasing LootLocker
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | Purchasing")
    static FString GetNotificationsSourcePurchasingLootLockerString() { return LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::LootLocker; };
    /**
     * Static String for use in Notifications -- Matching Notification source Twitch Drop
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | Twitch Drop")
    static FString GetNotificationsSourceTwitchDropString() { return LootLockerNotificationsStaticStrings::NotificationSources::TwitchDrop; };
    /**
     * Static String for use in Notifications -- Matching Notification source LootLocker Console
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | LootLocker Console")
    static FString GetNotificationsSourceLootLockerConsoleString() { return LootLockerNotificationsStaticStrings::NotificationSources::LootLockerConsole; };
    /**
     * Static String for use in Notifications -- Matching Notification source LootLocker Server API
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Sources | LootLocker Server API")
    static FString GetNotificationsSourceLootLockerServerAPIString() { return LootLockerNotificationsStaticStrings::NotificationSources::LootLockerServerApi; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Triggers
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Triggers")
    static FString GetStandardTriggersContextKeyIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Id; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Triggers
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Triggers")
    static FString GetStandardTriggersContextKeyKeyString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Key; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Triggers
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Triggers")
    static FString GetStandardTriggersContextKeyLimitString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Limit; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.SteamStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | SteamStore")
    static FString GetStandardPurchasingSteamStoreContextKeyCatalogIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::CatalogId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.SteamStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | SteamStore")
    static FString GetStandardPurchasingSteamStoreContextKeyCatalogItemIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::CatalogItemId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.SteamStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | SteamStore")
    static FString GetStandardPurchasingSteamStoreContextKeyEntitlementIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::EntitlementId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.SteamStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | SteamStore")
    static FString GetStandardPurchasingSteamStoreContextKeyCharacterIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::CharacterId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.AppleAppStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | AppleAppStore")
    static FString GetStandardPurchasingAppleAppStoreContextKeyCatalogIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::CatalogId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.AppleAppStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | AppleAppStore")
    static FString GetStandardPurchasingAppleAppStoreContextKeyCatalogItemIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::CatalogItemId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.AppleAppStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | AppleAppStore")
    static FString GetStandardPurchasingAppleAppStoreContextKeyTransactionIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::TransactionId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.GooglePlayStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | GooglePlayStore")
    static FString GetStandardPurchasingGooglePlayStoreContextKeyCatalogIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::CatalogId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.GooglePlayStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | GooglePlayStore")
    static FString GetStandardPurchasingGooglePlayStoreContextKeyCatalogItemIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::CatalogItemId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.GooglePlayStore
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | GooglePlayStore")
    static FString GetStandardPurchasingGooglePlayStoreContextKeyProductIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::ProductId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.LootLocker
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | LootLocker")
    static FString GetStandardPurchasingLootLockerContextKeyCatalogIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Purchasing.LootLocker
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | LootLocker")
    static FString GetStandardPurchasingLootLockerContextKeyCatalogItemIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogItemId; };
    /**
     * Static String for use in Notification contexts -- Standard Context Key for Twitch Drops
     */
    UFUNCTION(BlueprintPure, Category = "LootLocker Methods | Static Strings | Notifications | Standard Context Keys | Purchasing | LootLocker")
    static FString GetStandardTwitchDropContextKeyTwitchRewardIdString() { return LootLockerNotificationsStaticStrings::StandardContextKeys::TwitchDrop::TwitchRewardId; };
};

//==================================================
// Data Type Definitions
//==================================================

struct FLootLockerNotificationIdentifyingValueLookupStruct
{
    FString IdentifyingContextKey = "";
    FString NotificationULID = "";
    int NotificationArrayIndex = -1;
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationContextEntry
{
    GENERATED_BODY()
    /**
      The key for this context entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
    /**
      The value of this context entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Value = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardCurrencyDetails
{
    GENERATED_BODY()
    /**
      The name of the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
      The code of the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
    /**
      The amount of the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
      The ID of the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardCurrency
{
    GENERATED_BODY()
    /**
      The date the Currency reward was created.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
      The date the Currency reward was last updated.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";
    /**
      The amount of Currency to be rewarded.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
      The details on the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardCurrencyDetails Details;
    /**
      The ID of a reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_id = "";
    /**
      The ID of the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardProgressionDetails
{
    GENERATED_BODY()
    /**
      The key of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
    /**
      The name of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
      The amount of Progression Points to be rewarded.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount = 0;
    /**
      The ID of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardProgression
{
    GENERATED_BODY()
    /**
      The date the Progression Points reward was created.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
      The date the Progression Points was last updated.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";
    /**
      The details of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgressionDetails Details;
    /**
      The amount of Progression Points to be rewarded.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Amount = 0;
    /**
      The ID of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_id = "";
    /**
      The ID of the reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardProgressionResetDetails
{
    GENERATED_BODY()
    /**
      The key of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
    /**
      The name of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
      The ID of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardProgressionReset
{
    GENERATED_BODY()
    /**
      The date the Progression Reset reward was created.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
      The date the Progression Reset reward was last updated.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";
    /**
      The details of the Progression reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgressionResetDetails Details;
    /**
      The ID of the Progression.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Progression_id = "";
    /**
      The ID of the reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardAssetDetails
{
    GENERATED_BODY()
    /**
      The name of the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
      The url to the thumbnail, will be null if it's not set in the LootLocker console.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Thumbnail = "";
    /**
      The name of the Variation Asset, will be null if it's not a Variation Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Variation_name = "";
    /**
      The name of the Rental Asset, will be null if it's not a Variation Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Rental_option_name = "";
    /**
      The ID of the Variation, will be 0 if it's not a Variation Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Variation_id = 0;
    /**
      The ID of the rental option, will be 0 if it's not a Rental Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Rental_option_id = 0;
    /**
      The ID of the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Legacy_id = 0;
    /**
      the ULID of the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardAsset
{
    GENERATED_BODY()
    /**
      The date the Asset reward was created.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
      The date the Asset reward was last updated.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";
    /**
      The details on the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardAssetDetails Details;
    /**
      The Asset variation ID, will be 0 if it's not a variation.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Asset_variation_id = 0;
    /**
      The Asset rental option ID, will be 0 if it's not a rental.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Asset_rental_option_id = 0;
    /**
      The ID of the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Asset_id = 0;
    /**
      The ID of the reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_id = "";
    /**
      The ULID of the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Asset_ulid = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationGroupRewardAssociations
{
    GENERATED_BODY()
    /**
      The kind of reward, (asset / currency / progression points / progression reset). Note that a group is not allowed to contain another group
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerNotificationContentRewardKind Kind = ELootLockerNotificationContentRewardKind::asset;
    /**
      The details on the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardCurrency Currency;
    /**
      The details on the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardAsset Asset;
    /**
      The Progression Reset reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgressionReset Progression_reset;
    /**
      The Progression Points reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgression Progression_points;
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationRewardGroup
{
    GENERATED_BODY()
    /**
      The date the Group reward was created.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";

    /**
      The name of the Group.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";

    /**
      The description of the Group.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Description = "";

    /**
      Associations for the Group reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerNotificationGroupRewardAssociations> Associations;

    /**
      The ID of the reward.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Reward_id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationContentRewardBody
{
    GENERATED_BODY()
    /**
      The kind of notification body this contains. Use it to know which field in this object will be populated. If the kind is asset for example, the asset field will be populated, the rest will be null.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerNotificationContentRewardKind Kind = ELootLockerNotificationContentRewardKind::asset;
    /**
      The Group reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardGroup Group;
    /**
      The currency reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardCurrency Currency;
    /**
      The Asset reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardAsset Asset;
    /**
      The Progression Reset reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgressionReset Progression_reset;
    /**
      The Progression Points reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgression Progression_points;
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotificationContent
{
    GENERATED_BODY()
    /**
      The context for this content. This is a set of key value pairs that hold additional context information about this notification.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerNotificationContextEntry> Context;
    /**
      The context for this content. This is a set of key value pairs that hold additional context information about this notification.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> ContextAsDictionary;
    /**
      The key from the context that will most likely help in identifying this notification
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString IdentifyingContextKey = "";
    /**
      The interpreted type of the content body. Use this as a hint on how to parse the body.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerNotificationContentBodyType BodyType = ELootLockerNotificationContentBodyType::unknown;
    /**
      The body for this notification content as a json string, use the dedicated methods to parse this
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString BodyAsJsonString;
    /**
      The body for this notification content as a json value, use the dedicated methods to parse this
     */
    TSharedPtr<FJsonValue> BodyAsJsonValue;

    /*
     Get the body as a String. Returns true if body could be parsed in which case Output contains the string body untouched, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsString(FString& Output) const;
    /*
     Get the body as a float. Returns true if body could be parsed in which case Output contains the float, returns false if parsing failed which can happen if the body is not numeric, the conversion under or overflows, or the string body precision is larger than can be dealt within a float.
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsFloat(float& Output) const;
    /*
     Get the body as an integer. TReturns true if body could be parsed in which case Output contains the int, returns false if parsing failed which can happen if
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsInteger(int& Output) const;
    /*
     Get the body as a boolean. Returns true if body could be parsed in which case Output contains the bool, returns false if parsing failed which can happen if the string is not a convertible to a boolean (those are for example "0", "1", "true", "False", "yes", "NO", etc).
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsBool(bool& Output) const;
    /*
     Get the body as a String. Returns true if body could be parsed in which case Output contains the string body untouched, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsStringArray(TArray<FString>& Output) const;
    /*
     Get the body as a float. Returns true if body could be parsed in which case Output contains the float, returns false if parsing failed which can happen if the body is not numeric, the conversion under or overflows, or the string body precision is larger than can be dealt within a float.
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsFloatArray(TArray<float>& Output) const;
    /*
     Get the body as an integer. TReturns true if body could be parsed in which case Output contains the int, returns false if parsing failed which can happen if
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsIntegerArray(TArray<int>& Output) const;
    /*
     Get the body as a boolean. Returns true if body could be parsed in which case Output contains the bool, returns false if parsing failed which can happen if the string is not a convertible to a boolean (those are for example "0", "1", "true", "False", "yes", "NO", etc).
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsBoolArray(TArray<bool>& Output) const;
    /*
     Get the body as an unparsed json body. Returns true if body could be found in which case Output contains the JsonValue, returns false if the body field was not present.
     */
    LOOTLOCKERSDK_API bool TryGetRawValue(TSharedPtr<FJsonValue>& Output) const;
    /*
     Get the body as a Json Object. Returns true if body could be parsed in which case Output contains the Json Object, returns false if parsing failed which can happen if the body is not a valid json object string.
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsJsonObject(TSharedPtr<FJsonObject>& Output) const;
    /*
     Get the body as a Json Array. Returns true if body could be parsed in which case Output contains the Json Array, returns false if parsing failed which can happen if the body is not a valid json array string
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const;
    /*
     Get the body as a LootLockerNotificationContentBody object. Returns true if body could be parsed in which case Output contains the FLootLockerMetadataBase64Value, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetContentBodyAsRewardNotification(FLootLockerNotificationContentRewardBody& Output) const;
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerNotification
{
    GENERATED_BODY()
    /**
      The time that this notification was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
      At what time that this notification expires, after this time, the notification is no longer returned
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Expiration_date = "";
    /**
      The time that this notification was read. Will be empty if the notification has not been read
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Read_at = "";
    /**
      The type of this notification, if this is a custom notification then this is set by the sender of the notification and must match pattern ^[a-z_-]+\.[a-z_-]+\.[a-z_-]+$
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Notification_type = "";
    /**
      The priority of this notification (default: medium)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerNotificationPriority Priority = ELootLockerNotificationPriority::medium;
    /**
      The originating source of this notification (for example, did it originate from a purchase, a leaderboard reward, or a trigger?)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Source = "";
    /**
      The originating source of this notification (for example, did it originate from a purchase, a leaderboard reward, or a trigger?) packaged in an enum
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerNotificationSource SourceEnum = ELootLockerNotificationSource::triggers;
    /**
      The actual content of this notification
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationContent Content;
    /**
      The id of the notification, use this when marking as read
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
      The id of the player that this notification is for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_id = "";
    /**
      Whether this notification has been read or not
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Read = false;
    /**
      Whether this notification is a custom notification (custom defined by this game) or not (default defined by LootLocker)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Custom = false;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerReadNotificationsRequest
{
    GENERATED_BODY()
    /**
     * List of ids of the notifications to mark as read
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Notifications;
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerReadNotificationsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    // Empty unless there are errors
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListNotificationsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * List of the requested notifications according to pagination settings
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerNotification> Notifications;
    /**
     * Pagination data for this set of notifications
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;

    void PopulateConvenienceStructures();

    /**
    * Get notifications by their identifying value. The out is an array because many notifications are not unique. For example triggers that can be triggered multiple times.
    * For Triggers the identifying value is the key of the trigger
    * For Google Play Store purchases it is the product id
    * For Apple App Store purchases it is the transaction id
    * For LootLocker virtual purchases it is the catalog item id
    * For Twitch Drops it is the Twitch reward id
    * For custom notifications (notifications with the field Custom = true and with the source being either LootLocker Console or LootLocker Server API) the content of the notification is defined by the sender, so the identifying value is simply the Notification type matching the pattern ^[a-z0-9_-]+\.[a-z0-9_-]+\.[a-z0-9_-]+$
    * 
    * @param IdentifyingValue The identifying value of the notification you want to fetch.
    * @param OutNotifications A list of notifications that were found for the given identifying value or null if none were found.
    * @returns True if notifications were found for the identifying value. False if notifications couldn't be found for this value or if the underlying lookup table is corrupt.
    */
    bool TryGetNotificationsByIdentifyingValue(const FString& IdentifyingValue, TArray<FLootLockerNotification>& OutNotifications) const;

private:
    TMap<FString, TArray<FLootLockerNotificationIdentifyingValueLookupStruct>> NotificationLookupTable;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for handling List Notifications Responses
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListNotificationsResponseBP, FLootLockerListNotificationsResponse, Response);
/**
 * Blueprint response delegate for handling read notifications response
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerReadNotificationsResponseBP, FLootLockerReadNotificationsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/**
 * C++ response delegate for handling List Notifications Responses
 */
DECLARE_DELEGATE_OneParam(FLootLockerListNotificationsResponseDelegate, FLootLockerListNotificationsResponse);
/**
 * C++ response delegate for handling read notifications response
 */
DECLARE_DELEGATE_OneParam(FLootLockerReadNotificationsResponseDelegate, FLootLockerReadNotificationsResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerNotificationsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerNotificationsRequestHandler();
    static void ListNotificationsWithDefaultParameters(const FLootLockerPlayerData& PlayerData, const FLootLockerListNotificationsResponseBP& OnCompleteBP = FLootLockerListNotificationsResponseBP(), const FLootLockerListNotificationsResponseDelegate& OnComplete = FLootLockerListNotificationsResponseDelegate());
    static void ListNotifications(const FLootLockerPlayerData& PlayerData, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP = FLootLockerListNotificationsResponseBP(), const FLootLockerListNotificationsResponseDelegate& OnComplete = FLootLockerListNotificationsResponseDelegate());
    static void ListNotifications(const FLootLockerPlayerData& PlayerData, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP = FLootLockerListNotificationsResponseBP(), const FLootLockerListNotificationsResponseDelegate& OnComplete = FLootLockerListNotificationsResponseDelegate());
    static void MarkNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnCompleteBP = FLootLockerReadNotificationsResponseBP(), const FLootLockerReadNotificationsResponseDelegate& OnComplete = FLootLockerReadNotificationsResponseDelegate());
    static void MarkAllNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const FLootLockerReadNotificationsResponseBP& OnCompleteBP = FLootLockerReadNotificationsResponseBP(), const FLootLockerReadNotificationsResponseDelegate& OnComplete = FLootLockerReadNotificationsResponseDelegate());
private:
    static void ListNotifications(const FLootLockerPlayerData& PlayerData, const TMultiMap<FString, FString>& QueryParams, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete);
    static ULootLockerHttpClient* HttpClient;
};
