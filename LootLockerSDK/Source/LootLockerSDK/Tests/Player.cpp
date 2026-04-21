#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerPlayer, "LootLocker.Player",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
END_DEFINE_SPEC(FTestLootLockerPlayer)

void FTestLootLockerPlayer::Define()
{
	BeforeEach([this]()
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Player"));
		if (!bOk) { return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { return; }
		Game.InitializeLootLockerSDK();
		test_util::StartSession();
	});

	AfterEach([this]()
	{
		Game.DeleteGame();
	});

	Describe("Player", [this]()
	{
		LatentIt("SetPlayerName_ThenGetPlayerName_ReturnsSetName", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			FString Name = TEXT("TestName");

			// Set player name
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerNameResponse, FPNameResponse>();
				ULootLockerSDKManager::SetPlayerName(Name, Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("SetPlayerName ok", Response.success);
				delete Promise;
			}

			// Get player name
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerNameResponse, FPNameResponse>();
				ULootLockerSDKManager::GetPlayerName(Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("GetPlayerName ok", Response.success);
				TestEqual("Name set correctly", Response.name, Name);
				delete Promise;
			}

			TestDone.Execute();
		});

		LatentIt("GetInventory_Succeeds", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerInventoryResponse, FInventoryResponse>();
			ULootLockerSDKManager::GetInventory(Delegate);
			const auto Response = Promise->get_future().get();
			TestTrue("GetInventory ok", Response.success);
			delete Promise;

			TestDone.Execute();
		});
	});
}
#endif
