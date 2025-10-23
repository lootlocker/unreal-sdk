// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "JsonObjectConverter.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

FString ULootLockerAssetsRequestHandler::GetContexts(const FLootLockerPlayerData& PlayerData, const FContextDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetContextResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetContextsEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::GetAssets(const FLootLockerPlayerData& PlayerData, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    if (StartFromIndex != 0)
    {
        QueryParams.Add("after", FString::FromInt(StartFromIndex));
    }

    if (ItemsCount != 50)
    {
        QueryParams.Add("count", FString::FromInt(ItemsCount));
    }

    const TMultiMap<ELootLockerAssetFilter, FString> AssetFilterMap = {
        {ELootLockerAssetFilter::Purchasable,		"purchasable"},
        {ELootLockerAssetFilter::NonPurchasable,	"!purchasable"},
        {ELootLockerAssetFilter::Rentable,			"rentable"},
        {ELootLockerAssetFilter::NonRentable,		"!rentable"},
        {ELootLockerAssetFilter::Popular,			"popular"},
        {ELootLockerAssetFilter::UnPopular,		"!popular"},
        {ELootLockerAssetFilter::None,				""}
    };

    const FString Filter = *AssetFilterMap.Find(AssetFilter);

    if (!Filter.IsEmpty())
    {
        QueryParams.Add("filter", Filter);
    }
    if (Context != 0)
    {
        QueryParams.Add("context_id", FString::FromInt(Context));
    }

    if (IncludeUGC)
    {
        QueryParams.Add("include_ugc", "true");
    }

    return LLAPI<FLootLockerGetAssetsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetsEndpoint, { }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::GetAssetsByIds(const FLootLockerPlayerData& PlayerData, const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    if (AssetIds.Num() > 0)
    {
        FString ItemsParameterString = "";
        for (const auto& Id : AssetIds)
        {
            ItemsParameterString += FString::FromInt(Id) + ",";
        }
        ItemsParameterString.RemoveFromEnd(",");

        QueryParams.Add("asset_ids", ItemsParameterString);
    }

    return LLAPI<FLootLockerGetAssetsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetsByIdsEndpoint, { }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::GetAssetBones(const FLootLockerPlayerData& PlayerData, const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetAssetBonesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetBonesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(const FLootLockerPlayerData& PlayerData, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::AddAssetToFavourites(const FLootLockerPlayerData& PlayerData, int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint, { AssetId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(const FLootLockerPlayerData& PlayerData, int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint, { AssetId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::GetUniversalAssets(const FLootLockerPlayerData& PlayerData, const int After, const int Count, const FUniversalAssetResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("count", FString::FromInt(Count));
    if (After >= 0)
    {
        QueryParams.Add("after", FString::FromInt(After));
    }
    return LLAPI<FLootLockerUniversalAssetsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetUniversalAssetsEndpoint, {}, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(const FLootLockerPlayerData& PlayerData, const int assetID, const int assetVariationID, const int assetRentalOptionID, const FGrantAssetResponseDelegate& OnCompletedRequest)
{
    FLootLockerGrantAssetRequest request;
    request.asset_id = assetID;
    request.asset_variation_id = assetVariationID;
    request.asset_rental_option_id = assetRentalOptionID;

    return LLAPI<FLootLockerGrantAssetResponse>::CallAPI(request, ULootLockerGameEndpoints::GrantAssetToPlayerInventory, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetsRequestHandler::ListAssets(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, ELootLockerOrderAssetListBy OrderBy, ELootLockerOrderAssetListDirection OrderDirection, const FListSimpleAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if(Page > 0) QueryParams.Add("page", FString::FromInt(Page));
    if(PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
    
    // Add ordering parameters
    if(OrderBy != ELootLockerOrderAssetListBy::None)
    {
        QueryParams.Add("order_by", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerOrderAssetListBy"), static_cast<int32>(OrderBy)));
    }
    
    if(OrderDirection != ELootLockerOrderAssetListDirection::None)
    {
        QueryParams.Add("order_direction", ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerOrderAssetListDirection"), static_cast<int32>(OrderDirection)));
    }

    LLAPI<FLootLockerListSimpleAssetsResponse>::FResponseInspectorCallback ResponseParser = LLAPI<FLootLockerListSimpleAssetsResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerListSimpleAssetsResponse& Response)
    {
        // Make sure we will have assets to parse before continuing
        if (!Response.success || Response.assets.Num() == 0)
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }
        TSharedPtr<FJsonObject> obj = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        // Ensure that the full response was parsed before continuing
        if (!obj.IsValid())
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        TArray<TSharedPtr<FJsonValue>> JsonAssets = obj.Get()->GetArrayField(TEXT("assets"));
        // Make sure that the assets array was parsed before continuing
        if (JsonAssets.Num() != Response.assets.Num())
        {
            OnCompletedRequest.ExecuteIfBound(Response);
            return;
        }

        auto findCorrectAsset = [](TArray<FLootLockerSimpleAsset>& assets, TArray<TSharedPtr<FJsonValue>>& JsonAssets, int asset_id, int startIndex) -> FLootLockerSimpleAsset*
        {
            int i = startIndex;
            do {
                FLootLockerSimpleAsset& Asset = assets[i];
                if (Asset.asset_id == asset_id)
                {
                    return &Asset;
                }
                i++;
                if (i >= JsonAssets.Num())
                {
                    i = 0;
                }
            } while (i != startIndex);
            return nullptr;
        };

        auto findCorrectMetadataEntry = [&](FLootLockerSimpleAsset& Asset, const FString& metadataKey, int startIndex) -> FLootLockerMetadataEntry*
        {
            int i = startIndex;
            do {
                FLootLockerMetadataEntry& MetadataEntry = Asset.metadata[i];
                if (MetadataEntry.Key.Equals(metadataKey))
                {
                    return &MetadataEntry;
                }
                i++;
                if (i >= Asset.metadata.Num())
                {
                    i = 0;
                }
            } while (i != startIndex);
            return nullptr;
        };

        for (int i = 0; i < JsonAssets.Num(); i++)
        {
            TSharedPtr<FJsonObject> JsonAssetObject = JsonAssets[i].Get()->AsObject();
            int AssetId = JsonAssetObject.Get()->GetIntegerField(TEXT("asset_id"));
            FLootLockerSimpleAsset* AssetPtr = findCorrectAsset(Response.assets, JsonAssets, AssetId, i);
            if (!AssetPtr)
            {
                continue;
            }
            FLootLockerSimpleAsset& Asset = *AssetPtr;
            TArray<TSharedPtr<FJsonValue>> JsonMetadataArray = JsonAssetObject.Get()->GetArrayField(TEXT("metadata"));
            // Make sure that the metadata array was parsed before continuing
            if (JsonMetadataArray.Num() != Asset.metadata.Num())
            {
                OnCompletedRequest.ExecuteIfBound(Response);
                return;
            }

            for (int j = 0; j < JsonMetadataArray.Num(); j++)
            {
                TSharedPtr<FJsonObject> JsonMetadataObject = JsonMetadataArray[j].Get()->AsObject();
                FString MetadataKey = JsonMetadataObject.Get()->GetStringField(TEXT("key"));
                FLootLockerMetadataEntry* MetadataEntryPtr = findCorrectMetadataEntry(Asset, MetadataKey, j);
                if (!MetadataEntryPtr)
                {
                    continue;
                }
                FLootLockerMetadataEntry& MetadataEntry = *MetadataEntryPtr;
                MetadataEntry._INTERNAL_SetJsonRepresentation(*JsonMetadataObject.Get());
            }
        }

        OnCompletedRequest.ExecuteIfBound(Response);
    });

    return LLAPI<FLootLockerListSimpleAssetsResponse>::CallAPI(Request, ULootLockerGameEndpoints::ListAssetsEndpoint, {}, QueryParams, PlayerData, FListSimpleAssetsResponseDelegate(), ResponseParser);
}