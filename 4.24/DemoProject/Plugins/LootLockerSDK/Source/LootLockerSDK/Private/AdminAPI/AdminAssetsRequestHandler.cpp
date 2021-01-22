// Copyright (c) 2021 LootLocker

#include "AdminAPI/AdminAssetsRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FResponseCallback UAdminAssetsRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminAssetsRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminAssetsRequestHandler::GetAssets(int GameId, const FAAssetsResponseDelegate& OnComplete, const FString& SearchQuery, int Page)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssets failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetAssetsEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    if (!SearchQuery.IsEmpty()) {
        endpoint = LootLockerUtilities::AppendParameterToUrl(endpoint, "search=" + SearchQuery);
    }
    if (Page != 0) {
        endpoint = LootLockerUtilities::AppendParameterToUrl(endpoint, "page=" + FString::FromInt(Page));
    }
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetAssets: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::GetAssetsByIds(const TArray<int>& AssetIds, int GameId, const FAAssetsResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetsByIds failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetAssetsEndpoint;
    
    FString AssetsString;
    for (int i = 0; i < AssetIds.Num(); i++) {
        FString Separator = i == 0 ? "/" : ",";
        AssetsString += Separator + FString::FromInt(AssetIds[i]);
    }
    
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId }) + AssetsString;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetAssetsByIds: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::GetDetailedAssetInfo(int GameId, int AssetId, const FADetailedAssetResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FADetailedAssetResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FADetailedAssetResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetDetailedAssetInfo failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetDetailedAssetInfoEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, AssetId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetDetailedAssetInfo: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::CreateAsset(const FADetailedAssetData& AssetData, const FADetailedAssetResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FADetailedAssetResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FADetailedAssetResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateAsset failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(AssetData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateAssetEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CreateAsset: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::CheckIfAssetCanBeActivated(int AssetId, const FAAssetActivationResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetActivationResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetActivationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CheckIfAssetCanBeActivated failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::CheckIfAssetCanBeActivatedEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CheckIfAssetCanBeActivated: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::ActivateAsset(int AssetId, const FAAssetActivationResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetActivationResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetActivationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("ActivateAsset failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::ActivateAssetEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("ActivateAsset: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::DeactivateAsset(int AssetId, const FAAssetDeactivationData& DeactivationData, const FAAssetDeactivationResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetDeactivationResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetDeactivationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeactivateAsset failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(DeactivationData, ContentString);
    FEndPoints Endpoint = LootLockerAdminEndpoints::DeactivateAssetEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("DeactivateAsset: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::GetAssetContexts(int GameId, const FAAssetContextsResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetContextsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetContextsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetContexts failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetAssetContextsEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetAssetContexts: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::UpdateAssetContexts(int GameId, const TArray<FAAssetContextData>& Contexts, const FAAssetContextsResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetContextsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetContextsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateAssetContexts failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });
    
    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : Contexts)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FAAssetContextData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            if (Item.Id <= 0) {
                ItemJson->RemoveField("Id");
            }
            
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::UpdateAssetContextsEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateAssetContexts: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminAssetsRequestHandler::GetAssetTypes(int GameId, const FAAssetTypesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAAssetTypesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAAssetTypesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetTypes failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetAssetTypesEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetAssetTypes: Admin API calls are only allowed in Editor"));
#endif
}
