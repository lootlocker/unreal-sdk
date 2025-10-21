// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(const FLootLockerPlayerData& PlayerData, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    QueryParams.Add("key", Key);
    return LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(const FLootLockerPlayerData& PlayerData, const FLootLockerPersistentStorageItems& payload, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(payload, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(const FLootLockerPlayerData& PlayerData, const FLootLockerPersistentStorageItem& payload, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    FLootLockerPersistentStorageItems singleItem;
    singleItem.payload.Add(payload);
    return LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(singleItem, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    QueryParams.Add("key", Key);
    return LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs, { PlayerId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
