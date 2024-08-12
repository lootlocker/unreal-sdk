// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCatalogRequestHandler::HttpClient = nullptr;

FLootLockerInlinedCatalogEntry::FLootLockerInlinedCatalogEntry(const FLootLockerCatalogEntry& Entry, const FLootLockerListCatalogPricesResponse& CatalogListing)
{
	Created_at = Entry.Created_at;
	Entity_kind = Entry.Entity_kind;
	Entity_name = Entry.Entity_name;
	Entity_id = Entry.Entity_id;
	Listings = Entry.Listings;
	Prices = Entry.Prices;
	Catalog_listing_id = Entry.Catalog_listing_id;
	Purchasable = Entry.Purchasable;

	const FLootLockerItemDetailsKey& DetailsKey{
		Entry.Catalog_listing_id,
		Entry.Entity_id
	};
	switch (Entity_kind)
	{
	case ELootLockerCatalogEntryEntityKind::Asset:
	{
		if (CatalogListing.Asset_Details.Contains(DetailsKey)) 
		{
			this->AssetDetails = CatalogListing.Asset_Details.FindRef(DetailsKey);
		}
	}
		break;
	case ELootLockerCatalogEntryEntityKind::Currency:
	{
		if (CatalogListing.Currency_Details.Contains(DetailsKey)) 
		{
			this->CurrencyDetails = CatalogListing.Currency_Details.FindRef(DetailsKey);
		}
	}
		break;
	case ELootLockerCatalogEntryEntityKind::Progression_Points:
	{	
		if (CatalogListing.Progression_Point_Details.Contains(DetailsKey)) 
		{
			this->ProgressionPointDetails = CatalogListing.Progression_Point_Details.FindRef(DetailsKey);
		}
	}
		break;
	case ELootLockerCatalogEntryEntityKind::Progression_Reset:
	{
		if (CatalogListing.Progression_Reset_Details.Contains(DetailsKey)) 
		{
			this->ProgressionResetDetails = CatalogListing.Progression_Reset_Details.FindRef(DetailsKey);
		}
	}
		break;
	case ELootLockerCatalogEntryEntityKind::Group: 
	{

		if (!CatalogListing.Group_Details.Contains(DetailsKey))
			break;

		auto CatalogLevelGroup = CatalogListing.Group_Details.FindRef(DetailsKey);

		FLootLockerInlinedGroupDetails InlinedGroupDetails;

		InlinedGroupDetails.Name = CatalogLevelGroup.Name;
		InlinedGroupDetails.Description = CatalogLevelGroup.Description;
		InlinedGroupDetails.Metadata = CatalogLevelGroup.Metadata;
		InlinedGroupDetails.Id = CatalogLevelGroup.Id;
		InlinedGroupDetails.Associations = CatalogLevelGroup.Associations;
		InlinedGroupDetails.Catalog_listing_id = CatalogLevelGroup.Catalog_listing_id;

		for (const auto& association : CatalogLevelGroup.Associations)
		{
			const FLootLockerItemDetailsKey& GroupDetailsKey {
				association.Catalog_listing_id,
				association.Id
			};

			switch (association.Kind)
			{
			case ELootLockerCatalogEntryEntityKind::Asset:
			{
				if (CatalogListing.Asset_Details.Contains(GroupDetailsKey))
				{
					InlinedGroupDetails.AssetDetails.Add(CatalogListing.Asset_Details.FindRef(GroupDetailsKey));
				}
			}
			break;
			case ELootLockerCatalogEntryEntityKind::Currency:
			{
				if (CatalogListing.Currency_Details.Contains(GroupDetailsKey))
				{
					InlinedGroupDetails.CurrencyDetails.Add(CatalogListing.Currency_Details.FindRef(GroupDetailsKey));
				}
			}
			break;
			case ELootLockerCatalogEntryEntityKind::Progression_Points:
			{
				if (CatalogListing.Progression_Point_Details.Contains(GroupDetailsKey))
				{
					InlinedGroupDetails.ProgressionPointDetails.Add(CatalogListing.Progression_Point_Details.FindRef(GroupDetailsKey));
				}
			}
			break;
			case ELootLockerCatalogEntryEntityKind::Progression_Reset:
			{
				if (CatalogListing.Progression_Reset_Details.Contains(GroupDetailsKey))
				{
					InlinedGroupDetails.ProgressionResetDetails.Add(CatalogListing.Progression_Reset_Details.FindRef(GroupDetailsKey));
				}
			}
			break;
			case ELootLockerCatalogEntryEntityKind::Group:
			default:
				break;
			}
		}

		this->GroupDetails = InlinedGroupDetails;
	}
		break;
	default:
		break;
	}

}

void FLootLockerListCatalogPricesResponse::AppendCatalogItems(FLootLockerListCatalogPricesResponse AdditionalCatalogPrices)
{
	if (!AdditionalCatalogPrices.success)
	{
		return;
	}

	Pagination.Total = AdditionalCatalogPrices.Pagination.Total;
	Pagination.Next_Cursor = AdditionalCatalogPrices.Pagination.Next_Cursor;

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

	for (const auto& Detail : AdditionalCatalogPrices.Group_Details) {
		Group_Details.Add(Detail.Key, Detail.Value);
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
		Asset_Details.Add(FLootLockerItemDetailsKey{
			Detail.Catalog_listing_id,
			Detail.Id
			}, Detail);
	}

	for (const auto& Detail : ArrayResponse.Progression_Points_Details)
	{
		Progression_Point_Details.Add(FLootLockerItemDetailsKey{
			Detail.Catalog_listing_id,
			Detail.Id
			}, Detail);
	}

	for (const auto& Detail : ArrayResponse.Progression_Resets_Details)
	{
		Progression_Reset_Details.Add(FLootLockerItemDetailsKey{
			Detail.Catalog_listing_id,
			Detail.Id
			}, Detail);
	}

	for (const auto& Detail : ArrayResponse.Currency_Details)
	{
		Currency_Details.Add(FLootLockerItemDetailsKey{
			Detail.Catalog_listing_id,
			Detail.Id
			}, Detail);
	}

	for (const auto& Detail : ArrayResponse.Group_Details) 
	{
		Group_Details.Add(FLootLockerItemDetailsKey{
			Detail.Catalog_listing_id,
			Detail.Id
			}, Detail);


	}
}

TArray<FLootLockerInlinedCatalogEntry> FLootLockerListCatalogPricesResponse::GetLootLockerInlinedCatalogEntries() const
{
	TArray<FLootLockerInlinedCatalogEntry> InlinedEntries;
	for (const auto& CatalogEntry : Entries)
	{

		const auto& EntityKind = CatalogEntry.Entity_kind;
		InlinedEntries.Add(FLootLockerInlinedCatalogEntry(
			CatalogEntry,
			*this
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
