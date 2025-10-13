// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerSDK.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerLogger.h"

ULootLockerHttpClient* ULootLockerNotificationsRequestHandler::HttpClient = nullptr;

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

ULootLockerNotificationsRequestHandler::ULootLockerNotificationsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerNotificationsRequestHandler::ListNotificationsWithDefaultParameters(const FLootLockerPlayerData& PlayerData, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    ListNotifications(PlayerData, TMultiMap<FString, FString>(), FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");
    if (CustomNotificationsFilter != ELootLockerCustomNotificationFiltering::All) QueryParams.Add("custom", CustomNotificationsFilter == ELootLockerCustomNotificationFiltering::Custom_only ? "true" : "false");

    ListNotifications(PlayerData, QueryParams, FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, ELootLockerNotificationPriority WithPriority, bool ShowRead, const FString& OfType, const FString& WithSource, ELootLockerCustomNotificationFiltering CustomNotificationsFilter, int PerPage, int Page, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("priority", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerNotificationPriority"), static_cast<int32>(WithPriority)));

    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!WithSource.IsEmpty()) QueryParams.Add("source", WithSource);
    if (!OfType.IsEmpty()) QueryParams.Add("notification_type", OfType);
    if (ShowRead) QueryParams.Add("read", "true"); else QueryParams.Add("read", "false");
    if (CustomNotificationsFilter != ELootLockerCustomNotificationFiltering::All) QueryParams.Add("custom", CustomNotificationsFilter == ELootLockerCustomNotificationFiltering::Custom_only ? "true" : "false");

    ListNotifications(PlayerData, QueryParams, FLootLockerListNotificationsResponseBP(), OnComplete);
}

void ULootLockerNotificationsRequestHandler::MarkNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const TArray<FString>& NotificationIDs, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(HttpClient, FLootLockerReadNotificationsRequest{ NotificationIDs }, ULootLockerGameEndpoints::ReadNotifications, {}, {}, PlayerData, OnComplete);
}

void ULootLockerNotificationsRequestHandler::MarkAllNotificationsAsRead(const FLootLockerPlayerData& PlayerData, const FLootLockerReadNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerReadNotificationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ReadAllNotifications, {}, {}, PlayerData, OnComplete);
}

void ULootLockerNotificationsRequestHandler::ListNotifications(const FLootLockerPlayerData& PlayerData, const TMultiMap<FString, FString>& QueryParams, const FLootLockerListNotificationsResponseBP& OnCompleteBP, const FLootLockerListNotificationsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListNotificationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListNotifications, {}, QueryParams, PlayerData, FLootLockerListNotificationsResponseDelegate(), LLAPI<FLootLockerListNotificationsResponse>::FResponseInspectorCallback::CreateLambda([OnComplete, OnCompleteBP] (FLootLockerListNotificationsResponse& Response)
    {
        if(Response.success && Response.Notifications.Num() > 0)
        {
            Response.PopulateConvenienceStructures();
        }

        OnCompleteBP.ExecuteIfBound(Response);
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
