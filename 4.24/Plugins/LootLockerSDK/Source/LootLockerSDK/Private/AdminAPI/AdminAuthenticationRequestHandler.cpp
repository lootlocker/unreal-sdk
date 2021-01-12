// Copyright (c) 2020 LootLocker

#include "AdminAPI/AdminAuthenticationRequestHandler.h"

#include "LootLockerPersitentDataHolder.h"
#include "AdminAPI/LootLockerAdminEndpoints.h"

FResponseCallback UAdminAuthenticationRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminAuthenticationRequestHandler::HttpClient = nullptr;

UAdminAuthenticationRequestHandler::UAdminAuthenticationRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UAdminAuthenticationRequestHandler::AuthenticateUser(const FAUserData& UserData, const FAAuthenticationResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAuthenticationResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAuthenticationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ULootLockerPersitentDataHolder::AdminToken = ResponseStruct.auth_token;
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("AuthenticateUser failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(UserData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::AuthenticateUserEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("AuthenticateUser: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAuthenticationRequestHandler::VerifyUserCode(const FAVerifyUserData& UserData, const FAAuthenticationResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAuthenticationResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAuthenticationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ULootLockerPersitentDataHolder::AdminToken = ResponseStruct.auth_token;
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("VerifyUserCode failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(UserData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::VerifyUserCodeEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("VerifyUserCode: Admin API calls are only allowed in Editor"));
#endif
}
