// Copyright (c) 2021 LootLocker

#include "AdminAPI/AdminHeroesRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FResponseCallback UAdminHeroesRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminHeroesRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminHeroesRequestHandler::ListHeroes(int GameId, const FAHeroesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("ListHeroes failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::ListHeroesEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("ListHeroes: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::GetHero(int GameId, int HeroId, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetHero failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetHeroEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetHero: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::CreateHero(int GameId, const FAHeroData& HeroData, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateHero failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(HeroData, ContentString);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateHeroEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CreateHero: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::UpdateHero(int GameId, int HeroId, const FAHeroData& HeroData, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateHero failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(HeroData, ContentString);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::UpdateHeroEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateHero: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::DeleteHero(int GameId, int HeroId, const FLootLockerResponseCallback& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FLootLockerResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeleteHero failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::DeleteHeroEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("DeleteHero: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::AddAssetToDefaultHeroLoadout(int GameId, int HeroId, const FAHeroAssetData& AssetData, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("AddAssetToDefaultHeroLoadout failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
    if (FJsonObjectConverter::UStructToJsonObject(FAHeroAssetData::StaticStruct(), &AssetData, ItemJson, 0, 0) && AssetData.asset_variation_id < 0)
    {
        ItemJson->RemoveField("asset_variation_id");
    }
    
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemJson, Writer);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::AddAssetToDefaultHeroLoadoutEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("AddAssetToDefaultHeroLoadout: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::RemoveAssetFromDefaultHeroLoadout(int GameId, int HeroId, int AssetId, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("RemoveAssetFromDefaultHeroLoadout failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::RemoveAssetFromDefaultHeroLoadoutEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId, AssetId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("RemoveAssetFromDefaultHeroLoadout: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::AddHeroException(int GameId, int HeroId, const FAHeroExceptionData& ExceptionData, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("AddHeroException failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
    FJsonObjectConverter::UStructToJsonObject(FAHeroExceptionData::StaticStruct(), &ExceptionData, ItemJson, 0, 0);
    if (ExceptionData.asset_id < 0)
    {
        ItemJson->RemoveField("asset_id");
    }
    if (ExceptionData.context_id < 0)
    {
        ItemJson->RemoveField("context_id");
    }
    
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemJson, Writer);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::AddHeroExceptionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("AddHeroException: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminHeroesRequestHandler::RemoveHeroException(int GameId, int HeroId, int ExceptionId, const FAHeroInfoResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAHeroInfoResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAHeroInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("RemoveHeroException failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::RemoveHeroExceptionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, HeroId, ExceptionId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("RemoveHeroException: Admin API calls are only allowed in Editor"));
#endif
}
