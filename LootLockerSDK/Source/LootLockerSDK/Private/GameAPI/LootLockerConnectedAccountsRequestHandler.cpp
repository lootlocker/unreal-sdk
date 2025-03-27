// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"

#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerConnectedAccountsRequestHandler::HttpClient = nullptr;

ULootLockerConnectedAccountsRequestHandler::ULootLockerConnectedAccountsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(const FLootLockerPlayerData& PlayerData, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListConnectedAccountsEndpoint, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(const FLootLockerPlayerData& PlayerData, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP, const FLootLockerDefaultDelegate& OnComplete)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::DisconnectAccountEndpoint, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAccountProvider"), static_cast<int32>(AccountToDisconnect)).ToLower() }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectGoogleProviderToAccountRequest{ IdToken }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectGoogleProviderToAccountWithPlatformRequest{ IdToken, ULootLockerEnumUtils::GetEnum(TEXT("EGoogleAccountProviderPlatform"), static_cast<int32>(Platform)) }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectAppleRestProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("apple-rest") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(const FLootLockerPlayerData& PlayerData, const FString& Code, const FString& Nonce,	const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectRemoteSessionToAccountRequest{ Code, Nonce }, ULootLockerGameEndpoints::AttachRemoteSessionToAccountEndpoint, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}
