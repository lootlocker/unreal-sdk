// Copyright (c) 2020 LootLocker

#include "GameAPI/AssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"

UHttpClient* UAssetInstancesRequestHandler::HttpClient = nullptr;

UAssetInstancesRequestHandler::UAssetInstancesRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseGetKeyValuePairsForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAllKeyValuePairsForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponseGetKeyValuePairsForAssetInstance, true);
}
void UAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseGetKeyValuePairsForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAllKeyValuePairsToAnInstanceForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseGetKeyValuePairsForAssetInstance, true);
}
void UAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseGetKeyValuePairForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetKeyValuePairForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseGetKeyValuePairForAssetInstance, true);
}

void UAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseCreateStorageItemForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateStorageItemForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetInstanceStorageItem::StaticStruct(), &Item, ContentString, 0, 0);
    FEndPoints Endpoint = LootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseCreateStorageItemForAssetInstance, true);
}

void UAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseUpdateStorageItemsForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateOneOrMoreKeyValuePairForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FAssetInstanceStorageItems StorageItems;
    StorageItems.storage = Items;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetInstanceStorageItems::StaticStruct(), &StorageItems, ContentString, 0, 0);
    FEndPoints Endpoint = LootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseUpdateStorageItemsForAssetInstance, true);
}

void UAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseUpdateStorageItemForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateAKeyValuePairByIdForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetInstanceStorageItem::StaticStruct(), &Item, ContentString, 0, 0);
    FEndPoints Endpoint = LootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseUpdateStorageItemForAssetInstance, true);
}

void UAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseDeleteStorageItemForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeleteStorageItemForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseDeleteStorageItemForAssetInstance, true);
}

void UAssetInstancesRequestHandler::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseInspectLootBox = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootBoxContentResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootBoxContentResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("InspectLootBox failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::InspectLootBoxEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseInspectLootBox, true);
}

void UAssetInstancesRequestHandler::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseOpenLootBox = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FOpenLootBoxResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FOpenLootBoxResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("OpenLootBox failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::OpenLootBoxEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseOpenLootBox, true);
}
