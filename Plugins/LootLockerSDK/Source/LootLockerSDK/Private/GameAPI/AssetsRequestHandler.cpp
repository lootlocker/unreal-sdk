// Copyright (c) 2020 LootLocker

#include "GameAPI/AssetsRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "JsonObjectConverter.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

FResponseCallback UAssetsRequestHandler::sessionResponse = nullptr;
UHttpClient* UAssetsRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
UAssetsRequestHandler::UAssetsRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UAssetsRequestHandler::GetContexts(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetContextResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetContextResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetContexts failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetContextsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetsRequestHandler::GetAssets(int StartFromIndex, int ItemsCount, EAssetFilter AssetFilter, bool IncludeUGC, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetAssetsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetAssetsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetAssets failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAssetsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString EndpointUrl = Endpoint.endpoint;
    if (StartFromIndex != 0)
    {
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "after=" + FString::FromInt(StartFromIndex));
    }
    if (ItemsCount != 50)
    {
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "count=" + FString::FromInt(ItemsCount));
    }
    FString Filter = "";
    switch (AssetFilter)
    {
        case EAssetFilter::Purchasable:
            Filter = "purchasable";
            break;
        case EAssetFilter::NonPurchasable:
            Filter = "!purchasable";
            break;
        case EAssetFilter::Rentable:
            Filter = "rentable";
            break;
        case EAssetFilter::NonRentable:
            Filter = "!rentable";
            break;
        case EAssetFilter::Popular:
            Filter = "popular";
            break;
        case EAssetFilter::UnPopular:
            Filter = "!popular";
            break;
    }
    if (!Filter.IsEmpty())
    {
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "filter=" + Filter);
    }
    
    if (IncludeUGC)
    {
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "include_ugc=true");
    }
    HttpClient->SendApi(EndpointUrl, requestMethod, ContentString, sessionResponse, true);
}

void UAssetsRequestHandler::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetAssetsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetAssetsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetAssetsByIds failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAssetsByIdsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString EndpointUrl = Endpoint.endpoint;
    if (AssetIds.Num() > 0)
    {
        FString ItemsParameterString = "asset_ids=";
        for (auto Id : AssetIds)
        {
            ItemsParameterString += FString::FromInt(Id) + ",";
        }
        
        ItemsParameterString.RemoveFromEnd(",");
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, ItemsParameterString);
    }
    
    HttpClient->SendApi(EndpointUrl, requestMethod, ContentString, sessionResponse, true);
}

void UAssetsRequestHandler::GetAssetBones(const FAssetBonesResponseDelegateBP& OnCompletedRequestBP, const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetAssetBonesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetAssetBonesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAssetBonesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetsRequestHandler::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetFavouriteAssetIndicesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetFavouriteAssetIndicesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetsRequestHandler::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetFavouriteAssetIndicesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetFavouriteAssetIndicesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::AddAssetToFavouritesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UAssetsRequestHandler::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetFavouriteAssetIndicesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetFavouriteAssetIndicesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
