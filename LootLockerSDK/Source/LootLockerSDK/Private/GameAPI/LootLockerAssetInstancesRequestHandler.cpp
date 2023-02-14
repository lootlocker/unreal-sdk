// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAssetInstancesRequestHandler::HttpClient = nullptr;

ULootLockerAssetInstancesRequestHandler::ULootLockerAssetInstancesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance, { AssetInstanceId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance, {  AssetInstanceId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint, {  AssetInstanceId, StorageItemId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, Items, ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint, {  AssetInstanceId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerLootBoxContentResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::InspectLootBoxEndpoint, { AssetInstanceId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerOpenLootBoxResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::OpenLootBoxEndpoint, { AssetInstanceId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
