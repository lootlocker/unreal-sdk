// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAssetsRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "JsonObjectConverter.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerAssetsRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerAssetsRequestHandler::ULootLockerAssetsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAssetsRequestHandler::GetContexts(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetContextResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetContextResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogLootLocker, Error, TEXT("GetContexts failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetContextsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerAssetsRequestHandler::GetAssets(int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetAssetsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetAssetsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogLootLocker, Error, TEXT("GetAssets failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAssetsEndpoint;
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
        case ELootLockerAssetFilter::Purchasable:
            Filter = "purchasable";
            break;
        case ELootLockerAssetFilter::NonPurchasable:
            Filter = "!purchasable";
            break;
        case ELootLockerAssetFilter::Rentable:
            Filter = "rentable";
            break;
        case ELootLockerAssetFilter::NonRentable:
            Filter = "!rentable";
            break;
        case ELootLockerAssetFilter::Popular:
            Filter = "popular";
            break;
        case ELootLockerAssetFilter::UnPopular:
            Filter = "!popular";
            break;
    }
    if (!Filter.IsEmpty())
    {
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "filter=" + Filter);
    }
	if(Context != 0)
	{
		EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "context_id=" + FString::FromInt(Context));
	}
    
    if (IncludeUGC)
    {
        EndpointUrl = LootLockerUtilities::AppendParameterToUrl(EndpointUrl, "include_ugc=true");
    }

    HttpClient->SendApi(EndpointUrl, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerAssetsRequestHandler::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegateBP& OnCompletedRequestBP, const FAssetsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetAssetsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetAssetsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogLootLocker, Error, TEXT("GetAssetsByIds failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAssetsByIdsEndpoint;
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

void ULootLockerAssetsRequestHandler::GetAssetBones(const FAssetBonesResponseDelegateBP& OnCompletedRequestBP, const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetAssetBonesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetAssetBonesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAssetBonesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetFavouriteAssetIndicesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetFavouriteAssetIndicesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetFavouriteAssetIndicesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerAssetsRequestHandler::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetFavouriteAssetIndicesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetFavouriteAssetIndicesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::AddAssetToFavouritesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegateBP& OnCompletedRequestBP, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerGetFavouriteAssetIndicesResponse ResponseStruct;
            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetFavouriteAssetIndicesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAssetBones failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::RemoveAssetFromFavouritesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
