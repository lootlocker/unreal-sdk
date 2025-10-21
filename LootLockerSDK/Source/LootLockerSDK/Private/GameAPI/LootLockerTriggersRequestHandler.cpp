// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerTriggersRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerTriggersRequestHandler::InvokeTriggersByKey(const FLootLockerPlayerData& PlayerData, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerInvokeTriggersByKeyResponse>::CallAPI(FLootLockerInvokeTriggersByKeyRequest{ KeysToInvoke }, ULootLockerGameEndpoints::InvokeTriggers, {}, {}, PlayerData, OnComplete);
}
