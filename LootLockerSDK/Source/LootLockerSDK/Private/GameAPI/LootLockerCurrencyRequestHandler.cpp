// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerCurrencyRequestHandler::ListCurrencies(const FLootLockerPlayerData& PlayerData, const FLootLockerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListCurrenciesResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCurrencies, { }, {}, PlayerData, OnResponseCompleted);
}

FString ULootLockerCurrencyRequestHandler::GetCurrencyDetails(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerGetCurrencyDetailsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDetails, { CurrencyCode }, {}, PlayerData, OnResponseCompleted);
}

FString ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListDenominationsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDenominationsByCode, { CurrencyCode }, {}, PlayerData, OnResponseCompleted);
}
