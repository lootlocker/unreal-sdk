// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMiscellaneous, "LootLocker.Miscellaneous",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
END_DEFINE_SPEC(FTestLootLockerMiscellaneous)

void FTestLootLockerMiscellaneous::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Miscellaneous"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		Game.InitializeLootLockerSDK();
		test_util::StartSession();
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		Done.Execute();
	});

	Describe("Miscellaneous", [this]()
	{
		LatentIt("GetServerTime_ReturnsValidTime", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerTimeResponse, FTimeResponseDelegate>();
			ULootLockerSDKManager::GetServerTime(Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);

			TestTrue("GetServerTime succeeded", Response.success);
			TestFalse("ServerTime date is non-empty", Response.date.IsEmpty());

			TestDone.Execute();
		});
	});
}
#endif

