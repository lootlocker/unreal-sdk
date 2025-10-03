// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerBalanceRequestHandler::HttpClient = nullptr;

ULootLockerBalanceRequestHandler::ULootLockerBalanceRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerBalanceRequestHandler::ListBalancesInWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerListBalancesForWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListBalancesInWallet, { WalletID }, {}, PlayerData, FLootLockerListBalancesForWalletResponseBP(), OnComplete);
}

void ULootLockerBalanceRequestHandler::GetWalletByWalletID(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByWalletId, { WalletID }, {}, PlayerData, FLootLockerGetWalletResponseBP(), OnComplete);
}

void ULootLockerBalanceRequestHandler::GetWalletByHolderID(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	const auto Inspector = FLootLockerGetWalletResponseDelegate::CreateLambda([HolderULID, HolderType, PlayerData, OnComplete](const FLootLockerGetWalletResponse& Response)
		{
			if (Response.success)
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			// Create Wallet and then get again
			const auto CreateWalletResponseHandler = FLootLockerCreateWalletResponseDelegate::CreateLambda([HolderULID, PlayerData, OnComplete, Response](const FLootLockerCreateWalletResponse& CreateWalletResponse)
				{
					if (!CreateWalletResponse.success)
					{
						OnComplete.ExecuteIfBound(Response);
						return;
					}

					LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, PlayerData, FLootLockerGetWalletResponseBP(), OnComplete);
				});
			CreateWallet(PlayerData, HolderULID, HolderType, CreateWalletResponseHandler);
		});
	LLAPI<FLootLockerGetWalletResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, PlayerData, FLootLockerGetWalletResponseBP(), Inspector);
}

void ULootLockerBalanceRequestHandler::CreditBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete)
{

	LLAPI<FLootLockerCreditWalletResponse>::CallAPI(HttpClient, FLootLockerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerGameEndpoints::CreditBalanceToWallet, {}, {}, PlayerData, FLootLockerCreditWalletResponseBP(), OnComplete);
}

void ULootLockerBalanceRequestHandler::DebitBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerDebitWalletResponse>::CallAPI(HttpClient, FLootLockerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerGameEndpoints::DebitBalanceToWallet, {}, {}, PlayerData, FLootLockerDebitWalletResponseBP(), OnComplete);
}

void ULootLockerBalanceRequestHandler::CreateWallet(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerCreateWalletResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerCreateWalletResponse>::CallAPI(HttpClient, 
		FLootLockerCreateWalletRequest{ HolderULID, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() }, 
		ULootLockerGameEndpoints::CreateWallet, {}, EmptyQueryParams, PlayerData, FLootLockerCreateWalletResponseBP(), OnComplete);
}
