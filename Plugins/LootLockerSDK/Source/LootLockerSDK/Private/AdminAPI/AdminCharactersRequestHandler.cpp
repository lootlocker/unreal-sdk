// Fill out your copyright notice in the Description page of Project Settings.

#include "AdminAPI/AdminCharactersRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FResponseCallback UAdminCharactersRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminCharactersRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminCharactersRequestHandler::ListCharacterClasses(int GameId, const FACharacterClassesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FACharacterClassesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FACharacterClassesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("ListCharacterClasses failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::ListCharacterClassesEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("ListCharacterClasses: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminCharactersRequestHandler::CreateCharacterClass(int GameId, const FACharacterClassPayload& Data, const FACharacterClassesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FACharacterClassesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FACharacterClassesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateCharacterClass failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(Data, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateCharacterClassEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, FString("new") });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CreateCharacterClass: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminCharactersRequestHandler::UpdateCharacterClass(int GameId, int ClassId, const FACharacterClassPayload& Data, const FACharacterClassesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FACharacterClassesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FACharacterClassesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateCharacterClass failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(Data, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateCharacterClassEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, ClassId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateCharacterClass: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminCharactersRequestHandler::DeleteCharacterClass(int GameId, int ClassId, const FACharacterClassDeleteResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FACharacterClassDeleteResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FACharacterClassDeleteResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeleteCharacterClass failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::DeleteCharacterClassEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, ClassId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("DeleteCharacterClass: Admin API calls are only allowed in Editor"));
#endif
}
