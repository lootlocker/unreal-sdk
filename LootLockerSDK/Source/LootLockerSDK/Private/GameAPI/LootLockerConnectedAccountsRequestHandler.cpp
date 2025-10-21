// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"
#include "LootLockerLogger.h"

#include "Utils/LootLockerUtilities.h"

FString ULootLockerConnectedAccountsRequestHandler::ListConnectedAccounts(const FLootLockerPlayerData& PlayerData, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListConnectedAccountsEndpoint, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::DisconnectAccount(const FLootLockerPlayerData& PlayerData, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete)
{
    return LLAPI<FLootLockerResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::DisconnectAccountEndpoint, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAccountProvider"), static_cast<int32>(AccountToDisconnect)).ToLower() }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectGoogleProviderToAccountRequest{ IdToken }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectGoogleProviderToAccountWithPlatformRequest{ IdToken, ULootLockerEnumUtils::GetEnum(TEXT("EGoogleAccountProviderPlatform"), static_cast<int32>(Platform)) }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("google") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectAppleAccountByRestSignIn(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectAppleRestProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("apple-rest") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectEpicAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectEpicProviderToAccountRequest{ Token }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("epic") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectPlaystationAccount(const FLootLockerPlayerData& PlayerData, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectPlaystationProviderToAccountRequest{ Environment, Code }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("playstation") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectDiscordAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectDiscordProviderToAccountRequest{ Token }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("discord") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectTwitchAccount(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectTwitchProviderToAccountRequest{ AuthorizationCode }, ULootLockerGameEndpoints::ConnectProviderToAccountEndpoint, { FString("twitch") }, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::ConnectRemoteSessionAccount(const FLootLockerPlayerData& PlayerData, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerAccountConnectedResponse>::CallAPI(FLootLockerConnectRemoteSessionToAccountRequest{ Code, Nonce }, ULootLockerGameEndpoints::AttachRemoteSessionToAccountEndpoint, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerConnectedAccountsRequestHandler::TransferIdentityProvidersBetweenAccounts(const FLootLockerPlayerData& SourcePlayerData, const FLootLockerPlayerData& TargetPlayerData,	TArray<ELootLockerAccountProvider> ProvidersToTransfer,	const FLootLockerListConnectedAccountsResponseDelegate& OnComplete)
{
    if (SourcePlayerData.Token.IsEmpty())
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No valid session token found for source player", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, "No Headers");
        OnComplete.ExecuteIfBound(ErrorResponse);
        return "";
    }
    if (TargetPlayerData.Token.IsEmpty())
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No valid session token found for target player", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, "No Headers");
        OnComplete.ExecuteIfBound(ErrorResponse);
        return "";
    }
    if (ProvidersToTransfer.Num() == 0)
    {
        auto ErrorResponse = LootLockerResponseFactory::Error<FLootLockerListConnectedAccountsResponse>("No providers submitted", 403, SourcePlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(ErrorResponse, "No Headers");
        OnComplete.ExecuteIfBound(ErrorResponse);
        return "";
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

    return LLAPI<FLootLockerListConnectedAccountsResponse>::CallAPI(Request, ULootLockerGameEndpoints::TransferProvidersBetweenAccountsEndpoint, {}, {}, SourcePlayerData, OnComplete);
}
