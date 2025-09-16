// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"
#include "LootLockerLogger.h"

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

void ULootLockerConnectedAccountsRequestHandler::ConnectEpicAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectEpicProviderToAccountRequest{ Token }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("epic") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectPlaystationAccount(const FLootLockerPlayerData& PlayerData, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectPlaystationProviderToAccountRequest{ Environment, Code }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("playstation") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectDiscordAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectDiscordProviderToAccountRequest{ Token }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("discord") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectTwitchAccount(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectTwitchProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("twitch") }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(const FLootLockerPlayerData& PlayerData, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(HttpClient, FLootLockerConnectRemoteSessionToAccountRequest{ Code, Nonce }, ULootLockerGameEndpoints::AttachRemoteSessionToAccountEndpoint, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::TransferIdentityProvidersBetweenAccounts(const FLootLockerPlayerData& SourcePlayerData, const FLootLockerPlayerData& TargetPlayerData,	TArray<ELootLockerAccountProvider> ProvidersToTransfer,	const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP,	const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    if (SourcePlayerData.Token.IsEmpty())
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No valid session token found for source player", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.requestMethod)), ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.endpoint, "No Data", "No Headers");
        OnCompleteBP.ExecuteIfBound(ErrorResponse);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return;
    }
    if (TargetPlayerData.Token.IsEmpty())
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No valid session token found for target player", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.requestMethod)), ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.endpoint, "No Data", "No Headers");
        OnCompleteBP.ExecuteIfBound(ErrorResponse);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return;
    }
    if (ProvidersToTransfer.Num() == 0)
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No providers submitted", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.requestMethod)), ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.endpoint, "No Data", "No Headers");
        OnCompleteBP.ExecuteIfBound(ErrorResponse);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return;
    }

    TArray<FString> providers;
    for (const auto& Provider : ProvidersToTransfer)
    {
        providers.Add(ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAccountProvider"), static_cast<int32>(Provider)).ToLower());
    }

    FLootLockerTransferProvidersBetweenAccountsRequest Request{
        SourcePlayerData.Token,
        TargetPlayerData.Token,
        providers
    };

    LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint, {}, {}, SourcePlayerData, OnCompleteBP, OnComplete);
}
