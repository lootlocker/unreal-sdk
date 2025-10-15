// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerCurrencyRequestHandler::ListCurrencies(const FLootLockerPlayerData& PlayerData, const FLootLockerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListCurrenciesResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCurrencies, { }, {}, PlayerData, OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDetails(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerGetCurrencyDetailsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDetails, { CurrencyCode }, {}, PlayerData, OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListDenominationsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDenominationsByCode, { CurrencyCode }, {}, PlayerData, OnResponseCompleted);
}
