// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerProgressions, "LootLocker.Progressions",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString ProgressionKey;
END_DEFINE_SPEC(FTestLootLockerProgressions)

void FTestLootLockerProgressions::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		ProgressionKey = TEXT("ci_prog_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Progressions"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.CreateProgression(ProgressionKey, TEXT("CI Progression"));
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

	Describe("Progressions", [this]()
	{
		LatentIt("GetPlayerProgressions_ReturnsSuccess", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPaginatedPlayerProgressionResponse, FLootLockerPaginatedPlayerProgressionsResponseDelegate>();
			ULootLockerSDKManager::GetPlayerProgressions(Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("GetPlayerProgressions succeeded", Response.success);

			TestDone.Execute();
		});

		LatentIt("AddPointsToPlayerProgression_PointsAreReflected", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Add points to the progression
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPlayerProgressionWithRewardsResponse, FLootLockerPlayerProgressionWithRewardsResponseDelegate>();
				ULootLockerSDKManager::AddPointsToPlayerProgression(ProgressionKey, 100, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("AddPointsToPlayerProgression succeeded", Response.success);
				TestEqual("Points added correctly", Response.Points, 100);
			}

			// Verify via list
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPaginatedPlayerProgressionResponse, FLootLockerPaginatedPlayerProgressionsResponseDelegate>();
				ULootLockerSDKManager::GetPlayerProgressions(Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetPlayerProgressions succeeded after add", Response.success);
				bool bFound = false;
				for (const FLootLockerPlayerProgression& Entry : Response.Items)
				{
					if (Entry.Progression_Key == ProgressionKey)
					{
						TestEqual("Points reflected in progression list", Entry.Points, 100);
						bFound = true;
						break;
					}
				}
				TestTrue("Progression entry present in list", bFound);
			}

			TestDone.Execute();
		});
	});
}
#endif
