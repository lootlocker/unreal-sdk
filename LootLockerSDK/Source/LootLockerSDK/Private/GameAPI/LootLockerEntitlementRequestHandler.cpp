// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerEntitlementRequestHandler::ListEntitlements(const FLootLockerPlayerData& PlayerData, const int Count, const FString& After, const FLootLockerListEntitlementsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("per_page", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("cursor", After); }
	LLAPI<FLootLockerEntitlementHistoryResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListEntitlements, {}, QueryParams, PlayerData, OnComplete);
}

void ULootLockerEntitlementRequestHandler::GetEntitlement(const FLootLockerPlayerData& PlayerData, FString EntitlementID, const FLootLockerSingleEntitlementResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerSingleEntitlementResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetEntitlement, { EntitlementID }, {}, PlayerData, OnComplete);

}
