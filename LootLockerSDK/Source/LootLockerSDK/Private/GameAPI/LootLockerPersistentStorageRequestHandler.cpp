// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(const FLootLockerPlayerData& PlayerData, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    QueryParams.Add("key", Key);
    LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(const FLootLockerPlayerData& PlayerData, const FLootLockerPersistentStorageItems& payload, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(payload, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(const FLootLockerPlayerData& PlayerData, const FLootLockerPersistentStorageItem& payload, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    FLootLockerPersistentStorageItems singleItem;
    singleItem.payload.Add(payload);
    LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(singleItem, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    QueryParams.Add("key", Key);
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs, { PlayerId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
