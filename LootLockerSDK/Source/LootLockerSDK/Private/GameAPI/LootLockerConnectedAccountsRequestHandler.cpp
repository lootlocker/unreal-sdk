// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"
#include "LootLockerLogger.h"

#include "Utils/LootLockerUtilities.h"

void ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(const FLootLockerPlayerData& PlayerData, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListConnectedAccountsEndpoint, {}, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(const FLootLockerPlayerData& PlayerData, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete)
{
    LLAPI<FLootLockerResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::DisconnectAccountEndpoint, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAccountProvider"), static_cast<int32>(AccountToDisconnect)).ToLower() }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectGoogleProviderToAccountRequest{ IdToken }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectGoogleProviderToAccountWithPlatformRequest{ IdToken, ULootLockerEnumUtils::GetEnum(TEXT("EGoogleAccountProviderPlatform"), static_cast<int32>(Platform)) }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectAppleRestProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("apple-rest") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectEpicAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectEpicProviderToAccountRequest{ Token }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("epic") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectPlaystationAccount(const FLootLockerPlayerData& PlayerData, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectPlaystationProviderToAccountRequest{ Environment, Code }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("playstation") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectDiscordAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectDiscordProviderToAccountRequest{ Token }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("discord") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectTwitchAccount(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectTwitchProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("twitch") }, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(const FLootLockerPlayerData& PlayerData, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectRemoteSessionToAccountRequest{ Code, Nonce }, ULootLockerGameEndpoints::AttachRemoteSessionToAccountEndpoint, {}, {}, PlayerData, OnComplete);
}

void ULootLockerConnectedAccountsRequestHandler::TransferIdentityProvidersBetweenAccounts(const FLootLockerPlayerData& SourcePlayerData, const FLootLockerPlayerData& TargetPlayerData,	TArray<ELootLockerAccountProvider> ProvidersToTransfer,	const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    if (SourcePlayerData.Token.IsEmpty())
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No valid session token found for source player", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.requestMethod)), ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.endpoint, "No Data", "No Headers");
        OnComplete.ExecuteIfBound(ErrorResponse);
        return;
    }
    if (TargetPlayerData.Token.IsEmpty())
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No valid session token found for target player", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.requestMethod)), ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.endpoint, "No Data", "No Headers");
        OnComplete.ExecuteIfBound(ErrorResponse);
        return;
    }
    if (ProvidersToTransfer.Num() == 0)
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No providers submitted", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.requestMethod)), ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint.endpoint, "No Data", "No Headers");
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

    LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(Request, ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint, {}, {}, SourcePlayerData, OnComplete);
}
