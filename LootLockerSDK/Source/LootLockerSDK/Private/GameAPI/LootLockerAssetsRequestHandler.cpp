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

    return LLAPI<FLootLockerListSimpleAssetsResponse>::CallAPI(Request, ULootLockerGameEndpoints::ListAssetsEndpoint, {}, QueryParams, PlayerData, OnCompletedRequest);
}