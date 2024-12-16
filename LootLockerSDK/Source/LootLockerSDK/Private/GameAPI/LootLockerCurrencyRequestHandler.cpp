// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerCurrencyRequestHandler::HttpClient = nullptr;

ULootLockerCurrencyRequestHandler::ULootLockerCurrencyRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCurrencyRequestHandler::ListCurrencies(const FLootLockerListCurrenciesResponseBP& OnResponseCompletedBP, const FLootLockerListCurrenciesResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListCurrenciesResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListCurrencies, { }, {}, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDetails(const FString& CurrencyCode, const FLootLockerGetCurrencyDetailsResponseBP& OnResponseCompletedBP, const FLootLockerGetCurrencyDetailsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerGetCurrencyDetailsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDetails, { CurrencyCode }, {}, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerCurrencyRequestHandler::GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnResponseCompletedBP, const FLootLockerListDenominationsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListDenominationsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetCurrencyDenominationsByCode, { CurrencyCode }, {}, OnResponseCompletedBP, OnResponseCompleted);
}
