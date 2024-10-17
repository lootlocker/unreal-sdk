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
 * Enum of the different kinds of notification bodies possible, use this to figure out how to parse the notification body
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerNotificationContentKind : uint8
{
    group_reward = 0,
    currency_reward = 1,
    asset_reward = 2,
    progression_reset_reward = 3,
    progression_points_reward = 4,
};

//==================================================
// Data Type Definitions
//==================================================


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
    ELootLockerNotificationContentKind Kind = ELootLockerNotificationContentKind::asset_reward;

    /**
      The details on the Asset.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardAssetDetails Asset;

    /**
      The details on the Currency.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardCurrencyDetails Currency;

    /**
      The Progression Points reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgression Progression_points;

    /**
      The Progression Reset reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardProgressionReset Progression_reset;

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
struct FLootLockerNotificationContentBody
{
    GENERATED_BODY()
    /**
      The kind of notification body this contains. Use it to know which field in this object will be populated. If the kind is asset_reward for example, the asset field will be populated, the rest will be null.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerNotificationContentKind Kind = ELootLockerNotificationContentKind::asset_reward;

    /**
      The currency reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardCurrency Currency;
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
    /**
      The Asset reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardAsset Asset;
    /**
      The Group reward, will be null if the reward is of another type.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationRewardGroup Group;
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
      The body for this notification content, use the kind variable to know which field will be filled with data.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerNotificationContentBody Body;
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
      The type of this notification
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Notification_type = "";
    /**
      The priority of this notification (default: medium)
     */
    ELootLockerNotificationPriority Priority = ELootLockerNotificationPriority::medium;
    /**
      The originating source of this notification (for example, did it originate from a purchase, a leaderboard reward, or a trigger?)
     */
    FString Source = "";
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
    static void ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseBP& OnCompleteBP = FLootLockerListNotificationsResponseBP(), const FLootLockerListNotificationsResponseDelegate& OnComplete = FLootLockerListNotificationsResponseDelegate());
    static void ListNotifications(bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP = FLootLockerListNotificationsResponseBP(), const FLootLockerListNotificationsResponseDelegate& OnComplete = FLootLockerListNotificationsResponseDelegate());
    static void ListNotifications(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP = FLootLockerListNotificationsResponseBP(), const FLootLockerListNotificationsResponseDelegate& OnComplete = FLootLockerListNotificationsResponseDelegate());
    static void MarkNotificationsAsRead(const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnCompleteBP = FLootLockerReadNotificationsResponseBP(), const FLootLockerReadNotificationsResponseDelegate& OnComplete = FLootLockerReadNotificationsResponseDelegate());
    static void MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseBP& OnCompleteBP = FLootLockerReadNotificationsResponseBP(), const FLootLockerReadNotificationsResponseDelegate& OnComplete = FLootLockerReadNotificationsResponseDelegate());
private:
    static void ListNotifications(const TMultiMap<FString, FString>& QueryParams, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete);
    static ULootLockerHttpClient* HttpClient;
};
