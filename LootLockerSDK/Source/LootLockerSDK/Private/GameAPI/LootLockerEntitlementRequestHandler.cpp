// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerEntitlementRequestHandler::ListEntitlements(const FLootLockerPlayerData& PlayerData, const int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete)
{
    return ListEntitlements(PlayerData, Count, After, TArray<FString>(), OnComplete);
}

FString ULootLockerEntitlementRequestHandler::ListEntitlements(const FLootLockerPlayerData& PlayerData, const int Count, const FString& After, const TArray<FString>& CatalogListingIds, const FLootLockerListEntitlementsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("per_page", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("cursor", After); }
    for (const FString& CatalogListingId : CatalogListingIds)
    {
        if (!CatalogListingId.IsEmpty()) { QueryParams.Add("catalog_listing_id", CatalogListingId); }
    }
	return LLAPI<FLootLockerEntitlementHistoryResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListEntitlements, {}, QueryParams, PlayerData, OnComplete);
}

FString ULootLockerEntitlementRequestHandler::GetEntitlement(const FLootLockerPlayerData& PlayerData, FString EntitlementID, const FLootLockerSingleEntitlementResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerSingleEntitlementResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEntitlement, { EntitlementID }, {}, PlayerData, OnComplete);
}
