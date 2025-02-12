// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAssetInstancesRequestHandler::HttpClient = nullptr;

ULootLockerAssetInstancesRequestHandler::ULootLockerAssetInstancesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId, StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, Items, ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::InspectLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerLootBoxContentResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::InspectLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::OpenLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerOpenLootBoxResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::OpenLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(const FLootLockerPlayerData& PlayerData, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegateBP& OnCompletedRequestBP, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerDeleteAssetInstanceResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetInstanceFromPlayerInventory, { AssetInstanceID }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}