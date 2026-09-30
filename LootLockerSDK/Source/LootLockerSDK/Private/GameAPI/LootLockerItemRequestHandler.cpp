// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerItemRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerSDK.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerLogger.h"

void FLootLockerGetPlayerInventoryItemResponse::PopulateConvenienceStructures()
{
    TSharedPtr<FJsonObject> ResponseAsJson = LootLockerUtilities::JsonObjectFromFString(FullTextFromServer);
    if (!ResponseAsJson.IsValid() || !ResponseAsJson->HasField(TEXT("metadata")))
    {
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* JsonMetadataArray;
    if (!ResponseAsJson->TryGetArrayField(TEXT("metadata"), JsonMetadataArray))
    {
        return;
    }

    if (JsonMetadataArray == nullptr || JsonMetadataArray->Num() != Metadata.Num())
    {
        FLootLockerLogger::LogWarning("Failed to properly parse item metadata");
        return;
    }

    for (FLootLockerMetadataEntry& Entry : Metadata)
    {
        for (const TSharedPtr<FJsonValue>& JsonMetadataValue : *JsonMetadataArray)
        {
            if (!JsonMetadataValue.IsValid() || JsonMetadataValue->Type != EJson::Object)
            {
                continue;
            }

            const TSharedPtr<FJsonObject> JsonMetadataObject = JsonMetadataValue->AsObject();
            if (!JsonMetadataObject.IsValid())
            {
                continue;
            }

            FString MetadataKey = "";
            if (!JsonMetadataObject->TryGetStringField(TEXT("key"), MetadataKey))
            {
                continue;
            }

            if (Entry.Key.Equals(MetadataKey, ESearchCase::IgnoreCase))
            {
                Entry._INTERNAL_SetJsonRepresentation(*JsonMetadataObject.Get());
                break;
            }
        }
    }
}

void FLootLockerListPlayerInventoryItemsResponse::PopulateConvenienceStructures()
{
    if (Items.Num() == 0)
    {
        return;
    }

    TSharedPtr<FJsonObject> ResponseAsJson = LootLockerUtilities::JsonObjectFromFString(FullTextFromServer);
    if (!ResponseAsJson.IsValid())
    {
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* JsonItems;
    if (!ResponseAsJson->TryGetArrayField(TEXT("items"), JsonItems)
        || JsonItems == nullptr
        || JsonItems->Num() != Items.Num())
    {
        FLootLockerLogger::LogWarning("Failed to properly parse item metadata");
        return;
    }

    for (int32 i = 0; i < JsonItems->Num(); i++)
    {
        const TSharedPtr<FJsonValue>& JsonItemValue = (*JsonItems)[i];
        if (!JsonItemValue.IsValid() || JsonItemValue->Type != EJson::Object)
        {
            continue;
        }

        const TSharedPtr<FJsonObject> JsonItem = JsonItemValue->AsObject();
        if (!JsonItem.IsValid())
        {
            continue;
        }

        FString JsonItemId = "";
        if (!JsonItem->TryGetStringField(TEXT("id"), JsonItemId))
        {
            continue;
        }

        FLootLockerInventoryItem* MatchedItem = nullptr;
        for (FLootLockerInventoryItem& Item : Items)
        {
            if (Item.Id.Equals(JsonItemId, ESearchCase::IgnoreCase))
            {
                MatchedItem = &Item;
                break;
            }
        }

        if (MatchedItem == nullptr)
        {
            continue;
        }

        const TArray<TSharedPtr<FJsonValue>>* JsonMetadataArray;
        if (!JsonItem->TryGetArrayField(TEXT("metadata"), JsonMetadataArray)
            || JsonMetadataArray->Num() != MatchedItem->Metadata.Num())
        {
            continue;
        }

        for (FLootLockerMetadataEntry& Entry : MatchedItem->Metadata)
        {
            for (const TSharedPtr<FJsonValue>& JsonMetadataValue : *JsonMetadataArray)
            {
                if (!JsonMetadataValue.IsValid() || JsonMetadataValue->Type != EJson::Object)
                {
                    continue;
                }

                const TSharedPtr<FJsonObject> JsonMetadataObject = JsonMetadataValue->AsObject();
                if (!JsonMetadataObject.IsValid())
                {
                    continue;
                }

                FString MetadataKey = "";
                if (!JsonMetadataObject->TryGetStringField(TEXT("key"), MetadataKey))
                {
                    continue;
                }

                if (Entry.Key.Equals(MetadataKey, ESearchCase::IgnoreCase))
                {
                    Entry._INTERNAL_SetJsonRepresentation(*JsonMetadataObject.Get());
                    break;
                }
            }
        }
    }
}

FString ULootLockerItemRequestHandler::ListItemTemplates(const FLootLockerPlayerData& PlayerData, int32 PerPage, int32 Page, const FLootLockerListItemTemplatesResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));

    return LLAPI<FLootLockerListItemTemplatesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListItemTemplatesEndpoint, { }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::ListPlayerInventoryItems(const FLootLockerPlayerData& PlayerData, int32 PerPage, int32 Page, const FString& Name, ELootLockerItemType ItemType, ELootLockerItemConsumableFilter ConsumableFilter, ELootLockerItemSortField Sort, ELootLockerItemSortOrder Order, const FLootLockerListPlayerInventoryItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!Name.IsEmpty()) QueryParams.Add("name", Name);
    if (ItemType != ELootLockerItemType::None) QueryParams.Add("item_type", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerItemType"), static_cast<int32>(ItemType)).ToLower());
    if (ConsumableFilter != ELootLockerItemConsumableFilter::All) QueryParams.Add("consumable", ConsumableFilter == ELootLockerItemConsumableFilter::Consumable ? "true" : "false");
    if (Sort != ELootLockerItemSortField::None)
    {
        // GetEnum returns the enum display text, which uses spaces ("created at"), so normalize to
        // the backend's snake_case query values.
        FString SortAsString = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerItemSortField"), static_cast<int32>(Sort)).ToLower();
        SortAsString.ReplaceCharInline(' ', '_');
        QueryParams.Add("sort", SortAsString);
    }
    if (Order != ELootLockerItemSortOrder::None) QueryParams.Add("order", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerItemSortOrder"), static_cast<int32>(Order)).ToUpper());

    return LLAPI<FLootLockerListPlayerInventoryItemsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListPlayerInventoryItemsEndpoint, { }, QueryParams, PlayerData, FLootLockerListPlayerInventoryItemsResponseDelegate(), LLAPI<FLootLockerListPlayerInventoryItemsResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerListPlayerInventoryItemsResponse& Response)
    {
        if (Response.success && Response.Items.Num() > 0)
        {
            Response.PopulateConvenienceStructures();
        }

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerItemRequestHandler::GetPlayerInventoryItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerGetPlayerInventoryItemResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetPlayerInventoryItemResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryItemEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, FLootLockerGetPlayerInventoryItemResponseDelegate(), LLAPI<FLootLockerGetPlayerInventoryItemResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerGetPlayerInventoryItemResponse& Response)
    {
        if (Response.success)
        {
            Response.PopulateConvenienceStructures();
        }

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerItemRequestHandler::DeletePlayerInventoryItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayerInventoryItemEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::ConsumePlayerInventoryItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerConsumeInventoryItemRequest& Request, const FLootLockerConsumePlayerInventoryItemResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerConsumePlayerInventoryItemResponse>::CallAPI(Request, ULootLockerGameEndpoints::ConsumePlayerInventoryItemEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::SplitPlayerInventoryItemStack(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerSplitInventoryItemStackRequest& Request, const FLootLockerSplitInventoryItemStackResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerSplitInventoryItemStackResponse>::CallAPI(Request, ULootLockerGameEndpoints::SplitPlayerInventoryItemStackEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::MergePlayerInventoryItemStacks(const FLootLockerPlayerData& PlayerData, const FLootLockerMergeInventoryItemStacksRequest& Request, const FLootLockerMergeInventoryItemStacksResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerMergeInventoryItemStacksResponse>::CallAPI(Request, ULootLockerGameEndpoints::MergePlayerInventoryItemStacksEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}