// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAssetInstancesRequestHandler::HttpClient = nullptr;

ULootLockerAssetInstancesRequestHandler::ULootLockerAssetInstancesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance, { AssetInstanceId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId, StorageItemId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, Items, ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemResponse>::CallAPI(HttpClient, Item, ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetInstanceStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint, { AssetInstanceId,  StorageItemId }, EmptyQueryParams, PlayerData, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::InspectLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerLootBoxContentResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::InspectLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, FLootBoxContentResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::OpenLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerOpenLootBoxResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::OpenLootBoxEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, FOpenLootBoxResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAssetInstanceFromPlayerInventory(const FLootLockerPlayerData& PlayerData, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerDeleteAssetInstanceResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetInstanceFromPlayerInventory, { AssetInstanceID }, EmptyQueryParams, PlayerData, FDeleteAssetInstanceResponseDelegateBP(), OnCompletedRequest);
}