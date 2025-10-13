// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerTriggersRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerTriggersRequestHandler::HttpClient = nullptr;

void ULootLockerTriggersRequestHandler::InvokeTriggersByKey(const FLootLockerPlayerData& PlayerData, const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerInvokeTriggersByKeyResponse>::CallAPI(HttpClient, FLootLockerInvokeTriggersByKeyRequest{ KeysToInvoke }, ULootLockerGameEndpoints::InvokeTriggers, {}, {}, PlayerData, OnComplete);
}

ULootLockerTriggersRequestHandler::ULootLockerTriggersRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}
