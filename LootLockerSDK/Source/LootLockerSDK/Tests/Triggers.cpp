// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerTriggersRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerTriggers, "LootLocker.Triggers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString TriggerKey;
END_DEFINE_SPEC(FTestLootLockerTriggers)

void FTestLootLockerTriggers::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		TriggerKey = TEXT("ci_trig_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Triggers"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.CreateTrigger(TriggerKey, TEXT("CI Trigger"));
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

	Describe("Triggers", [this]()
	{
		LatentIt("InvokeTrigger_Succeeds", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerInvokeTriggersByKeyResponse, FLootLockerInvokeTriggersByKeyResponseDelegate>();
			ULootLockerSDKManager::InvokeTriggersByKey({ TriggerKey }, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("InvokeTriggersByKey succeeded", Response.success);

			TestDone.Execute();
		});

		LatentIt("InvokeMultipleTriggers_AllSucceed", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Create a second trigger
			FString TriggerKey2 = TEXT("ci_trig2_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();
			if (!Game.CreateTrigger(TriggerKey2, TEXT("CI Trigger 2")))
			{
				AddError(TEXT("Failed to create second trigger")); TestDone.Execute(); return;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerInvokeTriggersByKeyResponse, FLootLockerInvokeTriggersByKeyResponseDelegate>();
			ULootLockerSDKManager::InvokeTriggersByKey({ TriggerKey, TriggerKey2 }, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("InvokeTriggersByKey with multiple keys succeeded", Response.success);

			TestDone.Execute();
		});
	});
}
#endif
