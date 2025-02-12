// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerBalanceRequestHandler::HttpClient = nullptr;

ULootLockerBalanceRequestHandler::ULootLockerBalanceRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerBalanceRequestHandler::ListBalancesInWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnCompleteBP, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerListBalancesForWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListBalancesInWallet, { WalletID }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::GetWalletByWalletID(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerGetWalletResponseBP& OnCompleteBP, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByWalletId, { WalletID }, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::GetWalletByHolderID(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnCompleteBP, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	const auto Inspector = FLootLockerGetWalletResponseDelegate::CreateLambda([HolderULID, HolderType, PlayerData, OnCompleteBP, OnComplete](const FLootLockerGetWalletResponse& Response)
		{
			if (Response.success)
			{
				OnCompleteBP.ExecuteIfBound(Response);
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			// Create Wallet and then get again
			const auto CreateWalletResponseHandler = FLootLockerCreateWalletResponseDelegate::CreateLambda([HolderULID, PlayerData, OnCompleteBP, OnComplete, Response](const FLootLockerCreateWalletResponse& CreateWalletResponse)
				{
					if (!CreateWalletResponse.success)
					{
						OnCompleteBP.ExecuteIfBound(Response);
						OnComplete.ExecuteIfBound(Response);
						return;
					}

					LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, PlayerData, OnCompleteBP, OnComplete);
				});
			CreateWallet(PlayerData, HolderULID, HolderType, FLootLockerCreateWalletResponseBP(), CreateWalletResponseHandler);
		});
	LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, PlayerData, FLootLockerGetWalletResponseBP(), Inspector);
}

void ULootLockerBalanceRequestHandler::CreditBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnCompleteBP, const FLootLockerCreditWalletResponseDelegate& OnComplete)
{

	LLAPI<FLootLockerCreditWalletResponse>::CallAPI(HttpClient, FLootLockerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerGameEndpoints::CreditBalanceToWallet, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::DebitBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnCompleteBP, const FLootLockerDebitWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerDebitWalletResponse>::CallAPI(HttpClient, FLootLockerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerGameEndpoints::DebitBalanceToWallet, {}, {}, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerBalanceRequestHandler::CreateWallet(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerCreateWalletResponseBP& OnCompleteBP, const FLootLockerCreateWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerCreateWalletResponse>::CallAPI(HttpClient, 
		FLootLockerCreateWalletRequest{ HolderULID, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() }, 
		ULootLockerGameEndpoints::CreateWallet, {}, EmptyQueryParams, PlayerData, OnCompleteBP, OnComplete);
}
