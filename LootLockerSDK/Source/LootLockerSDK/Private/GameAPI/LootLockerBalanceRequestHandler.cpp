// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerBalanceRequestHandler::ListBalancesInWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerListBalancesForWalletResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListBalancesInWallet, { WalletID }, {}, PlayerData, OnComplete);
}

FString ULootLockerBalanceRequestHandler::GetWalletByWalletID(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerGetWalletResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByWalletId, { WalletID }, {}, PlayerData, OnComplete);
}

FString ULootLockerBalanceRequestHandler::GetWalletByHolderID(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete)
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

					LLAPI<FLootLockerGetWalletResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, PlayerData, OnComplete);
				});
			CreateWallet(PlayerData, HolderULID, HolderType, CreateWalletResponseHandler);
		});
	return LLAPI<FLootLockerGetWalletResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetWalletByHolderId, { HolderULID }, {}, PlayerData, Inspector);
}

FString ULootLockerBalanceRequestHandler::CreditBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerCreditWalletResponse>::CallAPI(FLootLockerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerGameEndpoints::CreditBalanceToWallet, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerBalanceRequestHandler::DebitBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerDebitWalletResponse>::CallAPI(FLootLockerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerGameEndpoints::DebitBalanceToWallet, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerBalanceRequestHandler::CreateWallet(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerCreateWalletResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerCreateWalletResponse>::CallAPI(
		FLootLockerCreateWalletRequest{ HolderULID, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() }, 
		ULootLockerGameEndpoints::CreateWallet, {}, EmptyQueryParams, PlayerData, OnComplete);
}
