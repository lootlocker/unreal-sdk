// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerErrorReportRequestHandler.h"
#include "LootLockerGameEndpoints.h"

FString ULootLockerErrorReportRequestHandler::ReportSDKError(const FLootLockerPlayerData& PlayerData, const FLootLockerErrorReportRequest& Report, const FLootLockerResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerResponse>::CallAPI(Report, ULootLockerGameEndpoints::ReportSDKError, {}, {}, PlayerData, OnComplete);
}
