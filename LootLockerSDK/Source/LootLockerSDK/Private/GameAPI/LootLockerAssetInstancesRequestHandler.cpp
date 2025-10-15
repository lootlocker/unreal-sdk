// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId, StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(Item, ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(Items, ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(Item, ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::InspectLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerLootBoxContentResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::InspectLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::OpenLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerOpenLootBoxResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::OpenLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(const FLootLockerPlayerData& PlayerData, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerDeleteAssetInstanceResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetInstanceFromPlayerInventory, { AssetInstanceID }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}