// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerItemRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerSDK.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerLogger.h"

void FLootLockerGetPlayerItemResponse::PopulateConvenienceStructures()
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

void FLootLockerListPlayerItemsResponse::PopulateConvenienceStructures()
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

        FLootLockerItem* MatchedItem = nullptr;
        for (FLootLockerItem& Item : Items)
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

FString ULootLockerItemRequestHandler::ListPlayerItems(const FLootLockerPlayerData& PlayerData, int32 PerPage, int32 Page, const FString& Name, const FString& ItemType, ELootLockerItemConsumableFilter ConsumableFilter, const FString& Sort, const FString& Order, const FLootLockerListPlayerItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    if (!Name.IsEmpty()) QueryParams.Add("name", Name);
    if (!ItemType.IsEmpty()) QueryParams.Add("item_type", ItemType);
    if (ConsumableFilter != ELootLockerItemConsumableFilter::All) QueryParams.Add("consumable", ConsumableFilter == ELootLockerItemConsumableFilter::Consumable ? "true" : "false");
    if (!Sort.IsEmpty()) QueryParams.Add("sort", Sort);
    if (!Order.IsEmpty()) QueryParams.Add("order", Order);

    return LLAPI<FLootLockerListPlayerItemsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListPlayerItemsEndpoint, { }, QueryParams, PlayerData, FLootLockerListPlayerItemsResponseDelegate(), LLAPI<FLootLockerListPlayerItemsResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerListPlayerItemsResponse& Response)
    {
        if (Response.success && Response.Items.Num() > 0)
        {
            Response.PopulateConvenienceStructures();
        }

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerItemRequestHandler::GetPlayerItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerGetPlayerItemResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetPlayerItemResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerItemEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, FLootLockerGetPlayerItemResponseDelegate(), LLAPI<FLootLockerGetPlayerItemResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerGetPlayerItemResponse& Response)
    {
        if (Response.success)
        {
            Response.PopulateConvenienceStructures();
        }

        OnCompletedRequest.ExecuteIfBound(Response);
    }));
}

FString ULootLockerItemRequestHandler::DeletePlayerItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayerItemEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::ConsumePlayerItem(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerConsumeItemRequest& Request, const FLootLockerConsumePlayerItemResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerConsumePlayerItemResponse>::CallAPI(Request, ULootLockerGameEndpoints::ConsumePlayerItemEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::SplitPlayerItemStack(const FLootLockerPlayerData& PlayerData, const FString& InventoryId, const FLootLockerSplitItemStackRequest& Request, const FLootLockerSplitItemStackResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerSplitItemStackResponse>::CallAPI(Request, ULootLockerGameEndpoints::SplitPlayerItemStackEndpoint, { InventoryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerItemRequestHandler::MergePlayerItemStacks(const FLootLockerPlayerData& PlayerData, const FLootLockerMergeItemStacksRequest& Request, const FLootLockerMergeItemStacksResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerMergeItemStacksResponse>::CallAPI(Request, ULootLockerGameEndpoints::MergePlayerItemStacksEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}