// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerBalances, "LootLocker.Balances",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString CurrencyId;
END_DEFINE_SPEC(FTestLootLockerBalances)

void FTestLootLockerBalances::Define()
{
	BeforeEach([this]()
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Balances"));
		if (!bOk) { return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { return; }
		bOk = Game.CreateCurrency(TEXT("CI Gold"), TEXT("CIGLD"), CurrencyId);
		if (!bOk) { return; }
		Game.InitializeLootLockerSDK();
		test_util::StartSession();
	});

	AfterEach([this]()
	{
		Game.DeleteGame();
	});

	Describe("Balances", [this]()
	{
		LatentIt("ListCurrencies_ContainsCreatedCurrency", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListCurrenciesResponse, FLootLockerListCurrenciesResponseDelegate>();
			ULootLockerSDKManager::ListCurrencies(Delegate);
			const auto Response = Promise->get_future().get();
			TestTrue("ListCurrencies succeeded", Response.success);
			bool bFound = false;
			for (const FLootLockerCurrency& C : Response.Currencies)
			{
				if (C.Id == CurrencyId) { bFound = true; break; }
			}
			TestTrue("Created currency appears in list", bFound);
			delete Promise;

			TestDone.Execute();
		});

		LatentIt("GetWalletByHolderID_Succeeds", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const FString PlayerUlid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;
			TestFalse("Player ULID is set", PlayerUlid.IsEmpty());

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetWalletResponse, FLootLockerGetWalletResponseDelegate>();
			ULootLockerSDKManager::GetWalletByHolderID(PlayerUlid, ELootLockerWalletHolderTypes::player, Delegate);
			const auto Response = Promise->get_future().get();
			TestTrue("GetWalletByHolderID succeeded", Response.success);
			TestFalse("Wallet ID is set", Response.Id.IsEmpty());
			delete Promise;

			TestDone.Execute();
		});
	});
}
#endif
