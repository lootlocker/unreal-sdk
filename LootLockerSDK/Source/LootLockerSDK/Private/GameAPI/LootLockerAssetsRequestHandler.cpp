// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "JsonObjectConverter.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerAssetsRequestHandler::HttpClient = nullptr;

ULootLockerAssetsRequestHandler::ULootLockerAssetsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAssetsRequestHandler::GetContexts(const FLootLockerPlayerData& PlayerData, const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetContextResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetContextsEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetAssets(const FLootLockerPlayerData& PlayerData, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
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

    LLAPI<FLootLockerGetAssetsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetsEndpoint, { }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetAssetsByIds(const FLootLockerPlayerData& PlayerData, const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
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

    LLAPI<FLootLockerGetAssetsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetsByIdsEndpoint, { }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetAssetBones(const FLootLockerPlayerData& PlayerData, const FAssetBonesResponseDelegateBP& OnCompletedRequestBP, const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetAssetBonesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetBonesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(const FLootLockerPlayerData& PlayerData, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::AddAssetToFavourites(const FLootLockerPlayerData& PlayerData, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint, { AssetId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(const FLootLockerPlayerData& PlayerData, int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint, { AssetId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetUniversalAssets(const FLootLockerPlayerData& PlayerData, const int After, const int Count, const FUniversalAssetResponseDelegateBP& OnCompletedRequestBP, const FUniversalAssetResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add("count", FString::FromInt(Count));
    if (After >= 0)
    {
        QueryParams.Add("after", FString::FromInt(After));
    }
    LLAPI<FLootLockerUniversalAssetsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetUniversalAssetsEndpoint, {}, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GrantAssetToPlayerInventory(const FLootLockerPlayerData& PlayerData, const int assetID, const int assetVariationID, const int assetRentalOptionID, const FGrantAssetResponseDelegateBP& OnCompletedRequestBP, const FGrantAssetResponseDelegate& OnCompletedRequest)
{
    FLootLockerGrantAssetRequest request;
    request.asset_id = assetID;
    request.asset_variation_id = assetVariationID;
    request.asset_rental_option_id = assetRentalOptionID;

    LLAPI<FLootLockerGrantAssetResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::GrantAssetToPlayerInventory, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::ListAssets(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimpleAssetsRequest& Request, int PerPage, int Page, ELootLockerOrderAssetListBy OrderBy, ELootLockerOrderAssetListDirection OrderDirection, const FListSimpleAssetsResponseDelegateBP& OnCompletedRequestBP, const FListSimpleAssetsResponseDelegate& OnCompletedRequest)
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

    LLAPI<FLootLockerListSimpleAssetsResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::ListAssetsEndpoint, {}, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}