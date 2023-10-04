// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerBalanceRequestHandler::HttpClient = nullptr;

ULootLockerBalanceRequestHandler::ULootLockerBalanceRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerBalanceRequestHandler::ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnCompleteBP, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerListBalancesForWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListBalancesInWallet, { WalletID }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseBP& OnCompleteBP, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByWalletId , { WalletID }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnCompleteBP, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	const auto Inspector = FLootLockerGetWalletResponseDelegate::CreateLambda([HolderULID, HolderType, OnCompleteBP, OnComplete](const FLootLockerGetWalletResponse& Response)
	{
		if(Response.success)
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;
		}

		// Create Wallet and then get again
		const auto CreateWalletResponseHandler = FLootLockerCreateWalletResponseDelegate::CreateLambda([HolderULID, OnCompleteBP, OnComplete, Response](const FLootLockerCreateWalletResponse& CreateWalletResponse)
		{
			if(!CreateWalletResponse.success)
			{
				OnCompleteBP.ExecuteIfBound(Response);
				OnComplete.ExecuteIfBound(Response);
				return;				
			}

			LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, OnCompleteBP, OnComplete);
		});
		CreateWallet(HolderULID, HolderType, FLootLockerCreateWalletResponseBP(), CreateWalletResponseHandler);
	});
	LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, FLootLockerGetWalletResponseBP(), Inspector);
}

void ULootLockerBalanceRequestHandler::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnCompleteBP, const FLootLockerCreditWalletResponseDelegate& OnComplete)
{

	LLAPI<FLootLockerCreditWalletResponse>::CallAPI(HttpClient, FLootLockerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerGameEndpoints::CreditBalanceToWallet, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnCompleteBP, const FLootLockerDebitWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerDebitWalletResponse>::CallAPI(HttpClient, FLootLockerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerGameEndpoints::DebitBalanceToWallet, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::CreateWallet(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerCreateWalletResponseBP& OnCompleteBP, const FLootLockerCreateWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerCreateWalletResponse>::CallAPI(HttpClient, 
		FLootLockerCreateWalletRequest{ HolderULID, ULootLockerConfig::GetEnum(TEXT("ELootLockerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() }, 
		ULootLockerGameEndpoints::CreateWallet, {}, EmptyQueryParams, OnCompleteBP, OnComplete);
}
