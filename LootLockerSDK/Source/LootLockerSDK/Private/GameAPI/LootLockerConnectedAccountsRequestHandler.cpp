// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerConnectedAccountsRequestHandler::HttpClient = nullptr;

ULootLockerConnectedAccountsRequestHandler::ULootLockerConnectedAccountsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListConnectedAccountsEndpoint, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP, const FLootLockerDefaultDelegate& OnComplete)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::DisconnectAccountEndpoint, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAccountProvider"), static_cast<int32>(AccountToDisconnect)).ToLower() }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectGoogleProviderToAccountRequest{ IdToken }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectGoogleProviderToAccountWithPlatformRequest{ IdToken, ULootLockerEnumUtils::GetEnum(TEXT("EGoogleAccountProviderPlatform"), static_cast<int32>(Platform)) }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectAppleRestProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("apple-rest") }, {}, OnCompleteBP, OnComplete);
}
