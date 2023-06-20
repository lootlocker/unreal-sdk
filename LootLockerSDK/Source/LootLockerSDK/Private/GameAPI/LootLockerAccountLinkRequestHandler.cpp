// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerAccountLinkRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerAccountLinkRequestHandler::HttpClient = nullptr;

ULootLockerAccountLinkRequestHandler::ULootLockerAccountLinkRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerAccountLinkRequestHandler::StartAccountLinkingProcess(const FLootLockerAccountLinkStartResponseBP& OnResponseCompletedBP, const FLootLockerAccountLinkStartResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerAccountLinkStartResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::StartAccountLinkingProcess, { }, {}, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerAccountLinkRequestHandler::CheckAccountLinkingProcessStatus(const FString& LinkID, const FLootLockerAccountLinkProcessStatusResponseBP& OnResponseCompletedBP, const FLootLockerAccountLinkProcessStatusResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerAccountLinkProcessStatusResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::CheckAccountLinkingProcessStatus, { LinkID }, {}, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerAccountLinkRequestHandler::CancelAccountLinkingProcess(const FString& LinkID, const FLootLockerCancelAccountLinkingProcessResponseBP& OnResponseCompletedBP, const FLootLockerCancelAccountLinkingProcessResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerCancelAccountLinkingProcessResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::CancelAccountLinkingProcess, { LinkID }, {}, OnResponseCompletedBP, OnResponseCompleted);
}

void ULootLockerAccountLinkRequestHandler::UnlinkProviderFromAccount(const ELootLockerPlatform Provider, const FLootLockerUnlinkProviderFromAccountResponseBP& OnResponseCompletedBP, const FLootLockerUnlinkProviderFromAccountResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerUnlinkProviderFromAccountResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::UnlinkProviderFromAccount, { ULootLockerCurrentPlatform::GetPlatformRepresentationForPlatform(Provider).AuthenticationProviderString }, {}, OnResponseCompletedBP, OnResponseCompleted);
}

