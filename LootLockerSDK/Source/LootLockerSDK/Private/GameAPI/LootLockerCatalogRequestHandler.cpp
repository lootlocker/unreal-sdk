// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCatalogRequestHandler::HttpClient = nullptr;

ULootLockerCatalogRequestHandler::ULootLockerCatalogRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCatalogRequestHandler::ListCatalogs(const FLootLockerListCatalogsResponseBP& OnCompleteBP, const FLootLockerListCatalogsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListCatalogsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCatalogs, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerCatalogRequestHandler::ListCatalogItems(const FString& CatalogKey, int Count, const FString& After, const FLootLockerListCatalogPricesResponseBP& OnCompleteBP, const FLootLockerListCatalogPricesResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("per_page", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("cursor", After); }

    const auto InternalResponseConverter = LLAPI<FInternalLootLockerListCatalogPricesResponse>::FResponseInspectorCallback::CreateLambda([OnCompleteBP, OnComplete](const FInternalLootLockerListCatalogPricesResponse& ResponseWithArrays)
    {
	    const auto MappedResponse = FLootLockerListCatalogPricesResponse(ResponseWithArrays);
        OnCompleteBP.ExecuteIfBound(MappedResponse);
        OnComplete.ExecuteIfBound(MappedResponse);
    });

    LLAPI<FInternalLootLockerListCatalogPricesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCatalogItemsByKey, { CatalogKey }, QueryParams, FInternalLootLockerListCatalogPricesResponseBP(), FInternalLootLockerListCatalogPricesResponseDelegate(), InternalResponseConverter);
}
