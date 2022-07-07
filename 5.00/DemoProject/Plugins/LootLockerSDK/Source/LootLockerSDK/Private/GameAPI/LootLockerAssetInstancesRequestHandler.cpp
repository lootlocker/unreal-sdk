// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerAssetInstancesRequestHandler::HttpClient = nullptr;

ULootLockerAssetInstancesRequestHandler::ULootLockerAssetInstancesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseGetKeyValuePairsForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAllKeyValuePairsForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAllKeyValuePairsForAssetInstance;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponseGetKeyValuePairsForAssetInstance, true);
}
void ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseGetKeyValuePairsForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAllKeyValuePairsToAnInstanceForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAllKeyValuePairsToAnInstanceForAssetInstance;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseGetKeyValuePairsForAssetInstance, true);
}
void ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseGetKeyValuePairForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetKeyValuePairForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAKeyValuePairByIdForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseGetKeyValuePairForAssetInstance, true);
}

void ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseCreateStorageItemForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("CreateStorageItemForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAssetInstanceStorageItem::StaticStruct(), &Item, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::CreateAKeyValuePairForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseCreateStorageItemForAssetInstance, true);
}

void ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FLootLockerAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseUpdateStorageItemsForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("UpdateOneOrMoreKeyValuePairForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerAssetInstanceStorageItems StorageItems;
    StorageItems.storage = Items;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAssetInstanceStorageItems::StaticStruct(), &StorageItems, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::UpdateOneOrMoreKeyValuePairForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseUpdateStorageItemsForAssetInstance, true);
}

void ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseUpdateStorageItemForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("UpdateAKeyValuePairByIdForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAssetInstanceStorageItem::StaticStruct(), &Item, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::UpdateAKeyValuePairByIdForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseUpdateStorageItemForAssetInstance, true);
}

void ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseDeleteStorageItemForAssetInstance = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetInstanceStorageItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetInstanceStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("DeleteStorageItemForAssetInstance failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::DeleteAKeyValuePairByIdForAssetInstanceEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId, StorageItemId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseDeleteStorageItemForAssetInstance, true);
}

void ULootLockerAssetInstancesRequestHandler::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseInspectLootBox = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerLootBoxContentResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerLootBoxContentResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("InspectLootBox failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::InspectLootBoxEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseInspectLootBox, true);
}

void ULootLockerAssetInstancesRequestHandler::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponseOpenLootBox = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerOpenLootBoxResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerOpenLootBoxResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("OpenLootBox failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::OpenLootBoxEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetInstanceId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponseOpenLootBox, true);
}
