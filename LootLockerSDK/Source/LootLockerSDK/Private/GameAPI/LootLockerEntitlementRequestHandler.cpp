// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerEntitlementRequestHandler::HttpClient = nullptr;

ULootLockerEntitlementRequestHandler::ULootLockerEntitlementRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerEntitlementRequestHandler::ListEntitlements(const FLootLockerPlayerData& PlayerData, const int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("per_page", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("cursor", After); }
	LLAPI<FLootLockerEntitlementHistoryResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListEntitlements, {}, QueryParams, PlayerData, FLootLockerListEntitlementsResponseBP(), OnComplete);
}

void ULootLockerEntitlementRequestHandler::GetEntitlement(const FLootLockerPlayerData& PlayerData, FString EntitlementID, const FLootLockerSingleEntitlementResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerSingleEntitlementResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEntitlement, { EntitlementID }, {}, PlayerData, FLootLockerSingleEntitlementResponseBP(), OnComplete);

}
