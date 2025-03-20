// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerNotificationsRequestHandler::HttpClient = nullptr;

const FString LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired = "pull.reward.acquired";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Triggers = "triggers";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::SteamStore = "purchasing.steam_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::AppleAppStore = "purchasing.apple_app_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore = "purchasing.google_play_store";
const FString LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::LootLocker = "purchasing.lootlocker";
const FString LootLockerNotificationsStaticStrings::NotificationSources::TwitchDrop = "twitch_drop";
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
const FString LootLockerNotificationsStaticStrings::StandardContextKeys::TwitchDrop::TwitchRewardId = "twitch_reward_id";

void FLootLockerListNotificationsResponse::PopulateConvenienceStructures()
{
    if (Notifications.Num() == 0)
    {
        return;
    }

    int i = 0;
    for(FLootLockerNotification& Notification : Notifications)
    {
        for (const FLootLockerNotificationContextEntry& ContextEntry : Notification.Content.Context)
        {
            Notification.Content.ContextAsDictionary.Add(ContextEntry.Key, ContextEntry.Value);
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
			|| !notification.Content.ContextAsDictionary.Contains(LookupStruct.IdentifyingContextKey) 
			|| !notification.Content.ContextAsDictionary.Find(LookupStruct.IdentifyingContextKey)->Equals(IdentifyingValue)
            )
        {
            // The notifications array is not the same as when the lookup table was populated
            return false;
        }
        OutNotifications.Add(notification);
    }

    return true;
}

ULootLockerNotificationsRequestHandler::ULootLockerNotificationsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(const FLootLockerPlayerData& PlayerData, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    ListNotifications(PlayerData, TMultiMap<FString, FString>(), OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");

    ListNotifications(PlayerData, QueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");
    QueryParams.Add("priority", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerNotificationPriority"), static_cast<int32>(WithPriority)));

    ListNotifications(PlayerData, QueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnCompleteBP, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(HttpClient, FLootLockerReadNotificationsRequest{ NotificationIDs }, ULootLockerGameEndpoints::ReadNotifications, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const FLootLockerReadNotificationsResponseBP& OnCompleteBP, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ReadAllNotifications, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, const TMultiMap<FString, FString>& QueryParams, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListNotificationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListNotifications, {}, QueryParams, PlayerData, FLootLockerListNotificationsResponseBP(), FLootLockerListNotificationsResponseDelegate(), LLAPI<FLootLockerListNotificationsResponse>::FResponseInspectorCallback::CreateLambda([OnComplete, OnCompleteBP] (FLootLockerListNotificationsResponse& Response)
    {
        if(Response.success && Response.Notifications.Num() > 0)
        {
            Response.PopulateConvenienceStructures();
        }

        OnCompleteBP.ExecuteIfBound(Response);
        OnComplete.ExecuteIfBound(Response);
    }));
}
