// Fill out your copyright notice in the Description page of Project Settings.

#include "AdminAPI/AdminGamesRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"

FResponseCallback UAdminGamesRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminGamesRequestHandler::HttpClient = nullptr;

UAdminGamesRequestHandler::UAdminGamesRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UAdminGamesRequestHandler::GetAllGamesForCurrentUser(const FAGamesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAGamesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAGamesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAllGamesForCurrentUser failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetAllGamesForCurrentUserEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetAllGamesForCurrentUser: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminGamesRequestHandler::CreateGame(const FACreateGamePayload& GameData, const FAFullGameResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAFullGameResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAFullGameResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateGame failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(GameData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateGameEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CreateGame: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminGamesRequestHandler::GetGameInfo(int GameId, const FAFullGameResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAFullGameResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAFullGameResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetGameInfo failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetGameInfoEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetGameInfo: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminGamesRequestHandler::UpdateGame(int GameId, const FAUpdateGamePayload& GameData, const FAFullGameResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAFullGameResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAFullGameResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateGame failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(GameData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::UpdateGameEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateGame: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminGamesRequestHandler::DeleteGame(int GameId, const FLootLockerResponseCallback& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            if (!response.success) {
                UE_LOG(LogTemp, Error, TEXT("DeleteGame failed from lootlocker"));
            }
                                                      
            OnComplete.ExecuteIfBound(response);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::DeleteGameEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("DeleteGame: Admin API calls are only allowed in Editor"));
#endif
}
