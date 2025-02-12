// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCurrencyRequestHandler::HttpClient = nullptr;

ULootLockerCurrencyRequestHandler::ULootLockerCurrencyRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCurrencyRequestHandler::ListCurrencies(const FLootLockerPlayerData& PlayerData, const FLootLockerListCurrenciesResponseBP& OnResponseCompletedBP, const FLootLockerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListCurrenciesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCurrencies, { }, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDetails(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnResponseCompletedBP, const FLootLockerGetCurrencyDetailsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerGetCurrencyDetailsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDetails, { CurrencyCode }, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(const FLootLockerPlayerData& PlayerData, const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnResponseCompletedBP, const FLootLockerListDenominationsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListDenominationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDenominationsByCode, { CurrencyCode }, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}
