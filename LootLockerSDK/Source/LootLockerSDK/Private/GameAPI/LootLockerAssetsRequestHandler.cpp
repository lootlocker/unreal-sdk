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

void ULootLockerAssetsRequestHandler::GetContexts(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetContextResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetContextsEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetAssets(int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString,FString> QueryParams;
    
    if (StartFromIndex != 0)
    {
        QueryParams.Add("after",FString::FromInt(StartFromIndex));
    }

    if (ItemsCount != 50)
    {
        QueryParams.Add("count",FString::FromInt(ItemsCount));
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
        QueryParams.Add("filter",Filter);
    }
    if (Context != 0)
    {
        QueryParams.Add("context_id",FString::FromInt(Context));
    }

	if (IncludeUGC)
	{
		QueryParams.Add("include_ugc","true");
	}
	
    LLAPI<FLootLockerGetAssetsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetsEndpoint, { },QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString,FString> QueryParams;

    if (AssetIds.Num() > 0)
    {
        FString ItemsParameterString;
        for (const auto& Id : AssetIds)
        {
            ItemsParameterString += FString::FromInt(Id) + ",";
        }
        ItemsParameterString.RemoveFromEnd(",");
        
        QueryParams.Add("asset_ids", ItemsParameterString);
    }
    
    LLAPI<FLootLockerGetAssetsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetsByIdsEndpoint, { },QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetAssetBones(const FAssetBonesResponseDelegateBP& OnCompletedRequestBP, const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetAssetBonesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetBonesEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint, { AssetId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerGetFavouriteAssetIndicesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint, { AssetId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetsRequestHandler::GetUniversalAssets(const int After, const int Count, const FUniversalAssetResponseDelegateBP &OnCompletedRequestBP, const FUniversalAssetResponseDelegate &OnCompletedRequest)
{
    TMultiMap<FString,FString> QueryParams;
    QueryParams.Add("count", FString::FromInt(Count));
    if (After >= 0)
    {
        QueryParams.Add("after", FString::FromInt(After));
    }
    LLAPI<FLootLockerUniversalAssetsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetUniversalAssetsEndpoint, {}, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
