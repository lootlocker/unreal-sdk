// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerPersistentStorageRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerPersistentStorageRequestHandler::ULootLockerPersistentStorageRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetEntirePersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetEntirePersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerPersistentStorageItemResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPersistentStorageItemResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetItemFromPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetASingleKeyFromPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint + "?key=" + Key, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(const TArray<FLootLockerPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("AddItemsToPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
    
    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : Items)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FLootLockerPersistentStorageItem::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("DeleteItemFromPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::DeleteAKeyValuePairFromPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint + "?key=" + Key, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("DeleteItemFromPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetOtherPlayersPublicKeyValuePairs;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
    UE_LOG(LogTemp, Verbose, TEXT("endpoint: %s"), *endpoint);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
