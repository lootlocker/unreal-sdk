// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerPersistentStorageRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerPersistentStorageRequestHandler::ULootLockerPersistentStorageRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(const FLootLockerPlayerData& PlayerData, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    QueryParams.Add("key", Key);
    LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint, {  }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(const FLootLockerPlayerData& PlayerData, const FLootLockerPersistentStorageItems& payload, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, payload, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::AddItemToPersistentStorage(const FLootLockerPlayerData& PlayerData, const FLootLockerPersistentStorageItem& payload, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    FLootLockerPersistentStorageItems singleItem;
    singleItem.payload.Add(payload);
    LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(HttpClient, singleItem, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;

    QueryParams.Add("key", Key);
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint, {  }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FLootLockerPlayerData& PlayerData, const FString& PlayerId, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs, { PlayerId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}
