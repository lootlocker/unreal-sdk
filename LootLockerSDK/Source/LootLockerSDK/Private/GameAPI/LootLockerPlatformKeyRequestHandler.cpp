// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPlatformKeyRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerPlatformKeyRequestHandler::ListPlatformKeys(const FLootLockerPlayerData& PlayerData, const FLootLockerListPlatformKeysResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListPlatformKeysResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListPlatformKeys, {}, {}, PlayerData, OnResponseCompleted);
}
