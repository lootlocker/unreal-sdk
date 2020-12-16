// Fill out your copyright notice in the Description page of Project Settings.

#include "AdminAPI/AdminPlayerRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FResponseCallback UAdminPlayerRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminPlayerRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminPlayerRequestHandler::SearchForPlayer(int GameId, const FString& Query, const FAPlayerSearchResponseDelegate& OnComplete, int Offset)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAPlayerSearchResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAPlayerSearchResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("SearchForPlayer failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::SearchForPlayerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    endpoint = LootLockerUtilities::AppendParameterToUrl(endpoint, "query=" + Query);
    if (Offset != 0) {
        endpoint = LootLockerUtilities::AppendParameterToUrl(endpoint, "offset=" + FString::FromInt(Offset));
    }
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("SearchForPlayer: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::GetPlayer(int GameId, int PlayerId, const FAPlayersResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAPlayersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAPlayersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetPlayer failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetPlayerEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetPlayer: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::GetPlayerScore(int GameId, int PlayerId, const FAPlayerScoreResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAPlayerScoreResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAPlayerScoreResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetPlayerScore failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetPlayerScoreEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetPlayerScore: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::AddPlayerScore(int Score, int GameId, int PlayerId, const FAPlayerScoreResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAPlayerScoreResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAPlayerScoreResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("AddPlayerScore failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FAPlayerScoreData ScoreData;
    ScoreData.score = Score;
    FJsonObjectConverter::UStructToJsonObjectString(ScoreData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::AddPlayerScoreEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("AddPlayerScore: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::ResetPlayerScore(int GameId, int PlayerId, const FAPlayerScoreResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAPlayerScoreResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAPlayerScoreResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("ResetPlayerScore failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::ResetPlayerScoreEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("ResetPlayerScore: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::GetPlayerSteamProfile(int GameId, const FString& SteamId, const FASteamPlayerResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FASteamPlayerResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FASteamPlayerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetPlayerSteamProfile failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetPlayerSteamProfileEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, SteamId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetPlayerSteamProfile: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::GetPlayerInventory(int GameId, int PlayerId, const FAInventoryItemsResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAInventoryItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAInventoryItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetPlayerInventory failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetPlayerInventoryEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetPlayerInventory: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::RefundPlayerPurchase(int GameId, int PlayerId, int ItemId, const FAInventoryItemsResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAInventoryItemsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAInventoryItemsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("RefundPlayerPurchase failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::RefundPlayerPurchaseEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId, ItemId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("RefundPlayerPurchase: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::GetPlayerCurrencies(int GameId, int PlayerId, const FACurrenciesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FACurrenciesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FACurrenciesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetPlayerCurrencies failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetPlayerCurrenciesEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetPlayerCurrencies: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::GetPlayerOrders(int GameId, int PlayerId, const FAOrdersResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAOrdersResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAOrdersResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetPlayerOrders failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetPlayerOrdersEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetPlayerOrders: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::SetPlayerProfilePublic(bool Public, int GameId, int PlayerId, const FLootLockerResponseCallback& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            if (!response.success) {
                UE_LOG(LogTemp, Error, TEXT("SetPlayerProfilePublic failed from lootlocker"));
            }
        
            OnComplete.ExecuteIfBound(response);
        });

    FString ContentString;
    FEndPoints Endpoint =  Public ?
        LootLockerAdminEndpoints::SetPlayerProfilePublicEndpoint :
        LootLockerAdminEndpoints::SetPlayerProfilePrivateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("SetPlayerProfilePublic: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminPlayerRequestHandler::ResetPlayerProfile(int GameId, int PlayerId, const FLootLockerResponseCallback& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            if (!response.success) {
                UE_LOG(LogTemp, Error, TEXT("ResetPlayerProfile failed from lootlocker"));
            }
        
            OnComplete.ExecuteIfBound(response);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::ResetPlayerProfileEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, PlayerId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("ResetPlayerProfile: Admin API calls are only allowed in Editor"));
#endif
}
