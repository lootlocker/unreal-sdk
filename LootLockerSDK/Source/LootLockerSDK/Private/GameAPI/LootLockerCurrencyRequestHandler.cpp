// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCurrencyRequestHandler::HttpClient = nullptr;

ULootLockerCurrencyRequestHandler::ULootLockerCurrencyRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCurrencyRequestHandler::ListCurrencies(const FLootLockerPlayerData& PlayerData, const FLootLockerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListCurrenciesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCurrencies, { }, {}, PlayerData, FLootLockerListCurrenciesResponseBP(), OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDetails(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerGetCurrencyDetailsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDetails, { CurrencyCode }, {}, PlayerData, FLootLockerGetCurrencyDetailsResponseBP(), OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerListDenominationsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListDenominationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDenominationsByCode, { CurrencyCode }, {}, PlayerData, FLootLockerListDenominationsResponseBP(), OnResponseCompleted);
}
