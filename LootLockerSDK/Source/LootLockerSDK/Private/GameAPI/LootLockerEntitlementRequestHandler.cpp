// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerEntitlementRequestHandler::HttpClient = nullptr;

ULootLockerEntitlementRequestHandler::ULootLockerEntitlementRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerEntitlementRequestHandler::ListEntitlements(const int Count, const FString& After, const FLootLockerListEntitlementsResponseBP& OnCompleteBP, const FLootLockerListEntitlementsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("per_page", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("cursor", After); }
	LLAPI<FLootLockerEntitlementHistoryResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListEntitlements, {}, QueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerEntitlementRequestHandler::GetEntitlement(FString EntitlementID, const FLootLockerSingleEntitlementResponseBP& OnCompleteBP, const FLootLockerSingleEntitlementResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerSingleEntitlementResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEntitlement, { EntitlementID }, {}, OnCompleteBP, OnComplete);

}
