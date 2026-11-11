// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerSDK.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerLogger.h"

const FString LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired = "pull.reward.acquired";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Triggers = "triggers";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::SteamStore = "purchasing.steam_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::AppleAppStore = "purchasing.apple_app_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore = "purchasing.google_play_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::LootLocker = "purchasing.lootlocker";
const FString LootLockerNotificationsStaticStrings::NotificationSources::TwitchDrop = "twitch_drop";
const FString LootLockerNotificationsStaticStrings::NotificationSources::LootLockerConsole = "lootlocker.console";
const FString LootLockerNotificationsStaticStrings::NotificationSources::LootLockerServerApi = "lootlocker.server_api";
const FString LootLockerNotificationsStaticStrings::NotificationSources::LootLockerAdminApi = "lootlocker.admin_api";
const FString LootLockerNotificationsStaticStrings::NotificationSources::MagicTriggers = "magic_triggers";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::PlaystationStore = "purchasing.playstation_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::StripeStore = "purchasing.stripe_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::EpicGamesStore = "purchasing.epic_games_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::LeaderboardReward = "leaderboard.reward";
const FString LootLockerNotificationsStaticStrings::NotificationSources::RewardCampaign = "reward_campaign";
const FString LootLockerNotificationsStaticStrings::NotificationSources::RewardsGrant = "rewards.grant";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Unknown = "unknown";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Id = "trigger_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Key = "trigger_key";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Limit = "trigger_limit";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::CatalogId = "catalog_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::EntitlementId = "entitlement_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::CharacterId = "character_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::CatalogId = "catalog_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::TransactionId = "transaction_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::CatalogId = "catalog_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::ProductId = "product_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogId = "catalog_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::CatalogId = "catalog_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::TransactionId = "transaction_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::EntitlementLabel = "entitlement_label";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::StripeStore::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::StripeStore::EntitlementId = "entitlement_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::CatalogId = "catalog_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::CatalogItemId = "catalog_item_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::EpicEntitlementId = "epic_entitlement_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::LeaderboardReward::LeaderboardId = "leaderboard_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::LeaderboardReward::PlayerPublicId = "player_public_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardCampaign::GiveawayId = "giveaway_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardCampaign::RewardId = "reward_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::ItemTemplateId = "item_template_id";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::TemplateName = "template_name";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::RequestedCount = "requested_count";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::GrantedCount = "granted_count";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::Source = "source";
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::TwitchDrop::TwitchRewardId = "twitch_reward_id";

void FLootLockerListNotificationsResponse::PopulateConvenienceStructures()
{
    // Rebuild from scratch: a previous population pass (or a reused response) would otherwise
    // leave stale identifying values queryable and append duplicate lookup records.
    NotificationLookupTable.Empty();

    if (Notifications.Num() == 0)
    {
        return;
    }

    TSharedPtr<FJsonObject> ResponseAsJson = LootLockerUtilities::JsonObjectFromFString(FullTextFromServer);
    TArray<TSharedPtr<FJsonObject>> JsonNotifications;
    if (ResponseAsJson.IsValid())
    {
        const TArray<TSharedPtr<FJsonValue>>* OutJsonNotifications;
        if (!ResponseAsJson->TryGetArrayField(TEXT("notifications"), OutJsonNotifications)
            || OutJsonNotifications == nullptr
			|| OutJsonNotifications->Num() != Notifications.Num())
        {
            FLootLockerLogger::LogWarning("Failed to properly parse notification content");
        }
    	else
        {
	        for (auto OutJsonNotification : *OutJsonNotifications)
	        {
                JsonNotifications.Add(OutJsonNotification->AsObject());
	        }
        }
    }

    int i = 0;
    for(FLootLockerNotification& Notification : Notifications)
    {
        // Rebuild from scratch: a second population pass would otherwise keep entries whose
        // context has since changed, and they could satisfy a later identifying key.
        Notification.Content.ContextAsDictionary.Empty();
        for (const FLootLockerNotificationContextEntry& ContextEntry : Notification.Content.Context)
        {
            Notification.Content.ContextAsDictionary.Add(ContextEntry.Key, ContextEntry.Value);
        }

        for (TSharedPtr<FJsonObject> jsonNotification : JsonNotifications)
        {
            if (!jsonNotification.IsValid())
            {
	            continue;
            }
            FString jsonNotificationId = "";
            if (!jsonNotification->TryGetStringField(TEXT("id"), jsonNotificationId))
            {
                continue;
            }
	        if (Notification.Id.Equals(jsonNotificationId, ESearchCase::IgnoreCase))
	        {
                if (jsonNotification->HasField(TEXT("content"))) {
	                TSharedPtr<FJsonObject> contentJson = jsonNotification->GetObjectField(TEXT("content"));
                    if (contentJson.IsValid() && contentJson->HasField(TEXT("body"))) {
                        TSharedPtr<FJsonValue> bodyJsonValue = contentJson->GetField<EJson::None>(TEXT("body"));
                        Notification.Content.BodyAsJsonValue = bodyJsonValue;
                        Notification.Content.BodyAsJsonString = LootLockerUtilities::JsonValueToString(bodyJsonValue.ToSharedRef());
                        if (bodyJsonValue.IsValid())
                        {
                            switch (bodyJsonValue->Type)
                            {
                            case EJson::Null:
                                Notification.Content.BodyType = ELootLockerNotificationContentBodyType::null;
                                break;
                            case EJson::String:
                                Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_string;
                                break;
                            case EJson::Number:
                                Notification.Content.BodyType = Notification.Content.BodyAsJsonString.Contains(".") ? ELootLockerNotificationContentBodyType::json_decimal : ELootLockerNotificationContentBodyType::json_integer;
                                break;
                            case EJson::Boolean:
                                Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_bool;
                                break;
                            case EJson::Object:
                                Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_object;
                                if (Notification.Content.BodyAsJsonValue->AsObject()->HasField(TEXT("kind")) && Notification.Notification_type.Equals(LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired))
                                {
                                    Notification.Content.BodyType = ELootLockerNotificationContentBodyType::reward;
                                }
                                break;
                            case EJson::Array:
                            {
                                TArray<TSharedPtr<FJsonValue>> bodyJsonArray = bodyJsonValue->AsArray();
                                if (bodyJsonArray.Num() == 0 || !bodyJsonArray[0].IsValid())
                                {
                                    Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_array;
                                }
                                else
                                {
                                    switch (bodyJsonArray[0]->Type) {
                                    case EJson::String:
                                        Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_array_string;
                                        break;
                                    case EJson::Number:
                                        Notification.Content.BodyType = LootLockerUtilities::JsonValueToString(bodyJsonArray[0].ToSharedRef()).Contains(".") ? ELootLockerNotificationContentBodyType::json_array_decimal : ELootLockerNotificationContentBodyType::json_array_integer;
                                        break;
                                    case EJson::Boolean:
                                        Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_array_bool;
                                        break;
                                    case EJson::Object:
                                        Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_array_object;
                                        break;
                                    default:
                                    case EJson::Null:
                                    case EJson::None:
                                    case EJson::Array:
                                        Notification.Content.BodyType = ELootLockerNotificationContentBodyType::json_array;
                                        break;
                                    };
                                }
                            }
                            break;
                            case EJson::None:
                            default:
                                Notification.Content.BodyType = ELootLockerNotificationContentBodyType::unknown;
                                break;
                            }
                        }
                    }
                	else
                    {
                        Notification.Content.BodyType = ELootLockerNotificationContentBodyType::none;
                    }
                }
	        	else
                {
                    Notification.Content.BodyType = ELootLockerNotificationContentBodyType::none;
                }
	        }
        }

        if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Triggers, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::triggers;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Key;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::SteamStore, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_steam_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::SteamStore::EntitlementId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::LootLocker, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_lootlocker_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogItemId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_google_play_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::ProductId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::AppleAppStore, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_apple_app_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::TransactionId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::TwitchDrop, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::twitch_drop;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::TwitchDrop::TwitchRewardId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::LootLockerConsole, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::lootlocker_console;
            Notification.Content.IdentifyingContextKey = Notification.Notification_type;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::LootLockerServerApi, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::lootlocker_server_api;
            Notification.Content.IdentifyingContextKey = Notification.Notification_type;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::LootLockerAdminApi, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::lootlocker_admin_api;
            Notification.Content.IdentifyingContextKey = Notification.Notification_type;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::MagicTriggers, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::magic_triggers;
            Notification.Content.IdentifyingContextKey = Notification.Notification_type;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::PlaystationStore, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_playstation_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::TransactionId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::StripeStore, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_stripe_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::StripeStore::EntitlementId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::EpicGamesStore, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::purchasing_epic_games_store;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::EpicEntitlementId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::LeaderboardReward, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::leaderboard_reward;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::LeaderboardReward::LeaderboardId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::RewardCampaign, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::reward_campaign;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::RewardCampaign::GiveawayId;
        }
        else if (Notification.Source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::RewardsGrant, ESearchCase::IgnoreCase))
        {
            Notification.SourceEnum = ELootLockerNotificationSource::rewards_grant;
            Notification.Content.IdentifyingContextKey = LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::ItemTemplateId;
        }
        else
        {
            Notification.SourceEnum = ELootLockerNotificationSource::unknown;
            // Unknown sources are not registered for lookup, so clear any key left over from a previous population pass
            Notification.Content.IdentifyingContextKey = "";
        }

        if (!Notification.Content.IdentifyingContextKey.IsEmpty())
        {
            if(Notification.Content.ContextAsDictionary.Contains(Notification.Content.IdentifyingContextKey))
            {
                const FString& IdentifyingValue = *Notification.Content.ContextAsDictionary.Find(Notification.Content.IdentifyingContextKey);

                FLootLockerNotificationIdentifyingValueLookupStruct LookupStruct
                {
                    Notification.Content.IdentifyingContextKey,
                    Notification.Id,
                    i
                };

                if(NotificationLookupTable.Contains(IdentifyingValue))
                {
                    NotificationLookupTable.Find(IdentifyingValue)->Add(LookupStruct);
                }
                else
                {
                    NotificationLookupTable.Add(IdentifyingValue, TArray<FLootLockerNotificationIdentifyingValueLookupStruct>{LookupStruct});
                }
            }
            else if (Notification.Content.IdentifyingContextKey.Equals(Notification.Notification_type))
            {
                FLootLockerNotificationIdentifyingValueLookupStruct LookupStruct
                {
                    Notification.Content.IdentifyingContextKey,
                    Notification.Id,
                    i
                };

                if (NotificationLookupTable.Contains(Notification.Notification_type))
                {
                    NotificationLookupTable.Find(Notification.Notification_type)->Add(LookupStruct);
                }
                else
                {
                    NotificationLookupTable.Add(Notification.Notification_type, TArray<FLootLockerNotificationIdentifyingValueLookupStruct>{LookupStruct});
                }
	            
            }
        }
        ++i;
    }	    
}

bool FLootLockerListNotificationsResponse::TryGetNotificationsByIdentifyingValue(const FString& IdentifyingValue, TArray<FLootLockerNotification>& OutNotifications) const
{
    OutNotifications.Empty();

    if (!NotificationLookupTable.Contains(IdentifyingValue))
    {
        return false;
    }

    const TArray<FLootLockerNotificationIdentifyingValueLookupStruct>& LookupStructs = *NotificationLookupTable.Find(IdentifyingValue);
    for(const FLootLockerNotificationIdentifyingValueLookupStruct& LookupStruct : LookupStructs)
    {
        if (LookupStruct.NotificationArrayIndex < 0 || LookupStruct.NotificationArrayIndex >= Notifications.Num())
        {
            // The notifications array is not the same as when the lookup table was populated
            return false;
        }
        const FLootLockerNotification& notification = Notifications[LookupStruct.NotificationArrayIndex];
        if(!LookupStruct.NotificationULID.Equals(notification.Id, ESearchCase::IgnoreCase)
			|| ((!notification.Content.ContextAsDictionary.Contains(LookupStruct.IdentifyingContextKey) || !notification.Content.ContextAsDictionary.Find(LookupStruct.IdentifyingContextKey)->Equals(IdentifyingValue)) 
                && !notification.Notification_type.Equals(IdentifyingValue))
            )
        {
            // The notifications array is not the same as when the lookup table was populated
            return false;
        }
        OutNotifications.Add(notification);
    }

    return true;
}

FString ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(const FLootLockerPlayerData& PlayerData, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    return ListNotifications(PlayerData, TMultiMap<FString, FString>(), OnComplete);
}

FString ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");
    if (CustomNotificationsFilter != ELootLockerCustomNotificationFiltering::All) QueryParams.Add("custom", CustomNotificationsFilter == ELootLockerCustomNotificationFiltering::Custom_only ? "true" : "false");

    return ListNotifications(PlayerData, QueryParams, OnComplete);
}

FString ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("priority", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerNotificationPriority"), static_cast<int32>(WithPriority)));

    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");
    if (CustomNotificationsFilter != ELootLockerCustomNotificationFiltering::All) QueryParams.Add("custom", CustomNotificationsFilter == ELootLockerCustomNotificationFiltering::Custom_only ? "true" : "false");

    return ListNotifications(PlayerData, QueryParams, OnComplete);
}

FString ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(FLootLockerReadNotificationsRequest{ NotificationIDs }, ULootLockerGameEndpoints::ReadNotifications, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ReadAllNotifications, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, const TMultiMap<FString, FString>& QueryParams, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerListNotificationsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListNotifications, {}, QueryParams, PlayerData, FLootLockerListNotificationsResponseDelegate(), LLAPI<FLootLockerListNotificationsResponse>::FResponseInspectorCallback::CreateLambda([OnComplete] (FLootLockerListNotificationsResponse& Response)
    {
        if(Response.success && Response.Notifications.Num() > 0)
        {
            Response.PopulateConvenienceStructures();
        }

        OnComplete.ExecuteIfBound(Response);
    }));
}

bool FLootLockerNotificationContent::TryGetContentBodyAsString(FString& Output) const
{
    return BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetString(Output);
}

bool FLootLockerNotificationContent::TryGetContentBodyAsFloat(float& Output) const
{
#if ENGINE_MAJOR_VERSION > 5
    return BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetNumber(Output);
#else
    double outDouble = 0.0f;
    bool success = BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetNumber(outDouble);
    Output = static_cast<float>(outDouble);
    return success;
#endif
}

bool FLootLockerNotificationContent::TryGetContentBodyAsInteger(int& Output) const
{
    return BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetNumber(Output);
}

bool FLootLockerNotificationContent::TryGetContentBodyAsBool(bool& Output) const
{
    return BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetBool(Output);
}

bool FLootLockerNotificationContent::TryGetContentBodyAsStringArray(TArray<FString>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetContentBodyAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<FString>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        FString convertedValue = "";
        if (JsonValue->TryGetString(convertedValue))
        {
            Output.Add(convertedValue);
        }
        else
        {
            allSucceeded = false;
        }
    }
    return allSucceeded;
}

bool FLootLockerNotificationContent::TryGetContentBodyAsFloatArray(TArray<float>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetContentBodyAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<float>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        float convertedValue = 0.0f;
#if ENGINE_MAJOR_VERSION > 5
        if (!(BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetNumber(convertedValue)))
        {
            allSucceeded = false;
            continue;
        }
#else
        double outDouble = 0.0f;
        if (!(BodyAsJsonValue.IsValid() && BodyAsJsonValue->TryGetNumber(outDouble)))
        {
            allSucceeded = false;
            continue;
        }
        convertedValue = static_cast<float>(outDouble);
#endif
        Output.Add(convertedValue);
    }
    return allSucceeded;
}

bool FLootLockerNotificationContent::TryGetContentBodyAsIntegerArray(TArray<int>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetContentBodyAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<int>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        int convertedValue = 0;
        if (JsonValue->TryGetNumber(convertedValue))
        {
            Output.Add(convertedValue);
        }
        else
        {
            allSucceeded = false;
        }
    }
    return allSucceeded;
}

bool FLootLockerNotificationContent::TryGetContentBodyAsBoolArray(TArray<bool>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetContentBodyAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<bool>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        bool convertedValue = false;
        if (JsonValue->TryGetBool(convertedValue))
        {
            Output.Add(convertedValue);
        }
        else
        {
            allSucceeded = false;
        }
    }
    return allSucceeded;
}

bool FLootLockerNotificationContent::TryGetRawValue(TSharedPtr<FJsonValue>& Output) const
{
    if (BodyAsJsonValue.IsValid())
    {
        Output = BodyAsJsonValue;
        return true;
    }
    return false;
}

bool FLootLockerNotificationContent::TryGetContentBodyAsJsonObject(TSharedPtr<FJsonObject>& Output) const
{
    if (BodyAsJsonValue.IsValid() && BodyAsJsonValue->Type == EJson::Object)
    {
        Output = BodyAsJsonValue->AsObject();
        return Output.IsValid();
    }
    return false;
}

bool FLootLockerNotificationContent::TryGetContentBodyAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const
{
    if (BodyAsJsonValue.IsValid() && BodyAsJsonValue->Type == EJson::Array)
    {
        Output = BodyAsJsonValue->AsArray();
        return true;
    }
    return false;
}

bool FLootLockerNotificationContent::TryGetContentBodyAsRewardNotification(FLootLockerNotificationContentRewardBody& Output) const
{
    TSharedPtr<FJsonObject> jsonObject;
    if (!TryGetContentBodyAsJsonObject(jsonObject))
    {
        return false;
    }
    return FJsonObjectConverter::JsonObjectToUStruct<FLootLockerNotificationContentRewardBody>(jsonObject.ToSharedRef(), &Output, 0, 0);
}
