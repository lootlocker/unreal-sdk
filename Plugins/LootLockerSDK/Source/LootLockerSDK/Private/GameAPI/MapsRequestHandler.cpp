// Copyright (c) 2020 LootLocker

#include "GameAPI/MapsRequestHandler.h"
#include "LootLockerGameEndpoints.h"

FResponseCallback UMapsRequestHandler::sessionResponse = nullptr;
UHttpClient* UMapsRequestHandler::HttpClient = nullptr;

UMapsRequestHandler::UMapsRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UMapsRequestHandler::GetMaps(const FGetMapsResponseDelegateBP& OnCompletedRequestBP, const FGetMapsResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FGetMapsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FGetMapsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetMaps failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAllMapsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}
