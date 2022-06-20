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

void ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::FinishMissionEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    TMap<FString, FString> QueryParams;

    QueryParams.Add("key",Key);
    LLAPI<FLootLockerPersistentStorageItemResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint, {  }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, Items, ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    TMap<FString, FString> QueryParams;

    QueryParams.Add("key",Key);
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint, {  }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPersistentStorageItemsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs, { PlayerId },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}
