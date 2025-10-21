// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId, StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(Item, ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(Items, ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(Item, ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::InspectLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerLootBoxContentResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::InspectLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::OpenLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerOpenLootBoxResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::OpenLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(const FLootLockerPlayerData& PlayerData, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerDeleteAssetInstanceResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetInstanceFromPlayerInventory, { AssetInstanceID }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}