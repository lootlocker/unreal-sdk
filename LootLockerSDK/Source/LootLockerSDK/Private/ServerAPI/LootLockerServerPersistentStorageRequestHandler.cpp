// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerPersistentStorageRequestHandler.h"
#include "LootLockerServerEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerServerPersistentStorageRequestHandler::HttpClient = nullptr;

// Sets default values for this component's properties
ULootLockerServerPersistentStorageRequestHandler::ULootLockerServerPersistentStorageRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerServerPersistentStorageRequestHandler::AddItemsToPersistentStorage(const FString& PlayerId, const TArray<FLootLockerPersistentStorageItem>& Items, const FServerPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP /*= FServerPersistentStorageItemsResponseDelegateBP()*/, const FServerPersistentStorageItemsResponseDelegate& OnCompletedRequest /*= FServerPersistentStorageItemsResponseDelegate()*/)
{
	FLootLockerPlayerPersistentStorageSets StorageItems;
	StorageItems.player_id = PlayerId;
	StorageItems.sets = Items;

	FLootLockerServerPersistentStorageItemsRequest ItemsRequest;
	ItemsRequest.payload.Add(StorageItems);

	LLAPI<FLootLockerServerPersistentStorageItemsResponse>::CallServerAPI(HttpClient, ItemsRequest, ULootLockerServerEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint, {}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerServerPersistentStorageItemsResponse>::FResponseInspectorCallback());
}

void ULootLockerServerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FString& PlayerId, const FString& Key, const FServerPersistentStorageDeleteItemResponseDelegateBP& OnCompletedRequestBP /*= FServerPersistentStorageDeleteItemResponseDelegateBP()*/, const FServerPersistentStorageDeleteItemResponseDelegate& OnCompletedRequest /*= FServerPersistentStorageDeleteItemResponseDelegate()*/)
{
	TMultiMap<FString, FString> AdditionalData;
	AdditionalData.Add(TEXT("player_ids"), PlayerId);
	AdditionalData.Add(TEXT("keys"), Key);

	LLAPI<FLootLockerResponse>::CallServerAPI(HttpClient, LootLockerEmptyRequest, ULootLockerServerEndpoints::DeleteKeyFromPersistentStorageEndpoint, {}, AdditionalData, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback());
}

void ULootLockerServerPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FString& PlayerId, const FServerPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP /*= FServerPersistentStorageItemsResponseDelegateBP()*/, const FServerPersistentStorageItemsResponseDelegate& OnCompletedRequest /*= FServerPersistentStorageItemsResponseDelegate()*/)
{
	TMultiMap<FString, FString> AdditionalData;
	AdditionalData.Add(TEXT("player_ids"), PlayerId);

	LLAPI<FLootLockerServerPersistentStorageItemsResponse>::CallServerAPI(HttpClient, LootLockerEmptyRequest, ULootLockerServerEndpoints::GetEntirePersistentStorageEndpoint, {}, AdditionalData, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerServerPersistentStorageItemsResponse>::FResponseInspectorCallback());
}
