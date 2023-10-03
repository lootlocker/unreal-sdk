// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCatalogRequestHandler::HttpClient = nullptr;

FLootLockerInlinedCatalogEntry::FLootLockerInlinedCatalogEntry(const FLootLockerCatalogEntry& Entry, const FLootLockerAssetDetails& AssetDetails, const FLootLockerProgressionPointDetails& ProgressionPointDetails, const FLootLockerProgressionResetDetails& ProgressionResetDetails, const FLootLockerCurrencyDetails& CurrencyDetails)
{
	Created_at = Entry.Created_at;
	Entity_kind = Entry.Entity_kind;
	Entity_name = Entry.Entity_name;
	Entity_id = Entry.Entity_id;
	Prices = Entry.Prices;
	Catalog_listing_id = Entry.Catalog_listing_id;
	Purchasable = Entry.Purchasable;
	this->AssetDetails = AssetDetails;
	this->ProgressionPointDetails = ProgressionPointDetails;
	this->ProgressionResetDetails = ProgressionResetDetails;
	this->CurrencyDetails = CurrencyDetails;
}

void FLootLockerListCatalogPricesResponse::AppendCatalogItems(FLootLockerListCatalogPricesResponse AdditionalCatalogPrices)
{
	if (!AdditionalCatalogPrices.success)
	{
		return;
	}

	Pagination.Total = AdditionalCatalogPrices.Pagination.Total;
	Pagination.Cursor = AdditionalCatalogPrices.Pagination.Cursor;

	for (auto& Entry : AdditionalCatalogPrices.Entries)
	{
		Entries.Add(Entry);
	}

	for (const auto& Detail : AdditionalCatalogPrices.Asset_Details)
	{
		Asset_Details.Add(Detail.Key, Detail.Value);
	}

	for (const auto& Detail : AdditionalCatalogPrices.Progression_Point_Details)
	{
		Progression_Point_Details.Add(Detail.Key, Detail.Value);
	}

	for (const auto& Detail : AdditionalCatalogPrices.Progression_Reset_Details)
	{
		Progression_Reset_Details.Add(Detail.Key, Detail.Value);
	}

	for (const auto& Detail : AdditionalCatalogPrices.Currency_Details)
	{
		Currency_Details.Add(Detail.Key, Detail.Value);
	}
}

FLootLockerListCatalogPricesResponse::FLootLockerListCatalogPricesResponse(const FInternalLootLockerListCatalogPricesResponse& ArrayResponse)
{
	success = ArrayResponse.success;
	StatusCode = ArrayResponse.StatusCode;
	FullTextFromServer = ArrayResponse.FullTextFromServer;
	ErrorData = ArrayResponse.ErrorData;
	if (!success)
	{
		return;
	}

	Catalog = ArrayResponse.Catalog;
	Entries = ArrayResponse.Entries;
	Pagination = ArrayResponse.Pagination;

	for (const auto& Detail : ArrayResponse.Assets_Details)
	{
		Asset_Details.Add(Detail.Catalog_listing_id, Detail);
	}

	for (const auto& Detail : ArrayResponse.Progression_Points_Details)
	{
		Progression_Point_Details.Add(Detail.Catalog_listing_id, Detail);
	}

	for (const auto& Detail : ArrayResponse.Progression_Resets_Details)
	{
		Progression_Reset_Details.Add(Detail.Catalog_listing_id, Detail);
	}

	for (const auto& Detail : ArrayResponse.Currency_Details)
	{
		Currency_Details.Add(Detail.Catalog_listing_id, Detail);
	}
}

TArray<FLootLockerInlinedCatalogEntry> FLootLockerListCatalogPricesResponse::GetLootLockerInlinedCatalogEntries()
{
	TArray<FLootLockerInlinedCatalogEntry> InlinedEntries;
	for (const auto& CatalogEntry : Entries)
	{
		const FString& CatalogListingID = CatalogEntry.Catalog_listing_id;
		const auto& EntityKind = CatalogEntry.Entity_kind;
		InlinedEntries.Add(FLootLockerInlinedCatalogEntry(
			CatalogEntry,
			ELootLockerCatalogEntryEntityKind::Asset == EntityKind && Asset_Details.Contains(CatalogListingID) ? Asset_Details.FindRef(CatalogListingID) : FLootLockerAssetDetails(),
			ELootLockerCatalogEntryEntityKind::Progression_Points == EntityKind && Progression_Point_Details.Contains(CatalogListingID) ? Progression_Point_Details.FindRef(CatalogListingID) : FLootLockerProgressionPointDetails(),
			ELootLockerCatalogEntryEntityKind::Progression_Reset == EntityKind && Progression_Reset_Details.Contains(CatalogListingID) ? Progression_Reset_Details.FindRef(CatalogListingID) : FLootLockerProgressionResetDetails(),
			ELootLockerCatalogEntryEntityKind::Currency == EntityKind && Currency_Details.Contains(CatalogListingID) ? Currency_Details.FindRef(CatalogListingID) : FLootLockerCurrencyDetails()
		));
	}
	return InlinedEntries;
}

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
