// Fill out your copyright notice in the Description page of Project Settings.

#include "AssetInstancesRequestHandler.h"

FResponseCallback UAssetInstancesRequestHandler::sessionResponse = nullptr;
UHttpClient* UAssetInstancesRequestHandler::HttpClient = nullptr;

UAssetInstancesRequestHandler::UAssetInstancesRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UAssetInstancesRequestHandler::GetKeyValuePairsForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetKeyValuePairsForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->GetKeyValuePairsForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::GetKeyValuePairForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->GetKeyValuePairForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::CreateStorageItemForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->CreateStorageItemForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::UpdateStorageItemsForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateStorageItemsForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FAssetInstanceStorageItems StorageItems;
    StorageItems.storage = Items;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetInstanceStorageItems::StaticStruct(), &StorageItems, ContentString, 0, 0);
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->UpdateStorageItemsForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::UpdateStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateStorageItemForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetInstanceStorageItem::StaticStruct(), &Item, ContentString, 0, 0);
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->UpdateStorageItemForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::DeleteStorageItemForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->DeleteStorageItemForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->InspectLootBoxEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetInstancesRequestHandler::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->OpenLootBoxEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
