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


ULootLockerNotificationsRequestHandler::ULootLockerNotificationsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(const FLootLockerListNotificationsResponseBP& OnCompleteBP,	const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    ListNotifications(TMultiMap<FString, FString>(), OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");

    ListNotifications(QueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, int PerPage, int Page, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");
    QueryParams.Add("priority", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerNotificationPriority"), static_cast<int32>(WithPriority)));

    ListNotifications(QueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseBP& OnCompleteBP, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(HttpClient, FLootLockerReadNotificationsRequest{NotificationIDs}, ULootLockerGameEndpoints::ReadNotifications, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(const FLootLockerReadNotificationsResponseBP& OnCompleteBP, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ReadAllNotifications, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const TMultiMap<FString, FString>& QueryParams, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListNotificationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListNotifications, {}, QueryParams, FLootLockerListNotificationsResponseBP(), FLootLockerListNotificationsResponseDelegate(), LLAPI<FLootLockerListNotificationsResponse>::FResponseInspectorCallback::CreateLambda([OnComplete, OnCompleteBP] (FLootLockerListNotificationsResponse& Response)
    {
        if(Response.success)
        {
            for (FLootLockerNotification& Notification : Response.Notifications)
            {
                for (const FLootLockerNotificationContextEntry& ContextEntry : Notification.Content.Context)
                {
                    Notification.Content.ContextAsDictionary.Add(ContextEntry.Key, ContextEntry.Value);
                }
            }			
        }

        OnCompleteBP.ExecuteIfBound(Response);
        OnComplete.ExecuteIfBound(Response);
    }));
}
