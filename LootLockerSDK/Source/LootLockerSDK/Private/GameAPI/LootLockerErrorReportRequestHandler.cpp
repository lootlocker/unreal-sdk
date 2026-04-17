// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerErrorReportRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerErrorReportRequestHandler::ReportSDKError(const FLootLockerPlayerData& PlayerData, const FLootLockerErrorReportRequest& Report, const FLootLockerSendErrorReportDelegate& OnComplete)
{
    return LLAPI<FLootLockerResponse>::CallAPI(Report, ULootLockerGameEndpoints::ReportSDKError, {}, {}, PlayerData, OnComplete);
}
