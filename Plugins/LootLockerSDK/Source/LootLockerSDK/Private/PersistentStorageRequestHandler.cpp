// Fill out your copyright notice in the Description page of Project Settings.

#include "PersistentStorageRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"

FResponseCallback UPersistentStorageRequestHandler::sessionResponse = nullptr;
UHttpClient* UPersistentStorageRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
UPersistentStorageRequestHandler::UPersistentStorageRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UPersistentStorageRequestHandler::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetEntirePersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetEntirePersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UPersistentStorageRequestHandler::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPersistentStorageItemResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPersistentStorageItemResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("GetItemFromPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetItemFromPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint + "?key=" + Key, requestMethod, ContentString, sessionResponse, true);
}

void UPersistentStorageRequestHandler::AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("AddItemsToPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
    
    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : Items)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FPersistentStorageItem::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::AddItemsToPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("DeleteItemFromPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::DeleteItemFromPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint + "?key=" + Key, requestMethod, ContentString, sessionResponse, true);
}

void UPersistentStorageRequestHandler::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FPersistentStorageItemsResponse ResponseStruct;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FPersistentStorageItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.success = true;
            }
            else {
                ResponseStruct.success = false;
                UE_LOG(LogTemp, Error, TEXT("DeleteItemFromPersistentStorage failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetPlayerPersistentStorageEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    FString endpoint = FString::Format(*(Endpoint.endpoint), { PlayerId });
    UE_LOG(LogTemp, Verbose, TEXT("endpoint: %s"), *endpoint);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
