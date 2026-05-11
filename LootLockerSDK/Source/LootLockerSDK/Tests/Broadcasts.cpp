// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerBroadcastRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"
#include "LootLockerConfig.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerBroadcasts, "LootLocker.Broadcasts",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString BroadcastId;
	FString ExpectedHeadline;
	FString BroadcastName;
END_DEFINE_SPEC(FTestLootLockerBroadcasts)

void FTestLootLockerBroadcasts::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Broadcasts"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }

		// Broadcast names are org-scoped — must be unique per test run to avoid conflicts.
		const FString Uid = FGuid::NewGuid().ToString(EGuidFormats::Short);
		BroadcastName    = FString::Printf(TEXT("CI-Broadcast-%s"), *Uid);
		ExpectedHeadline = FString::Printf(TEXT("CI Broadcast %s"), *Uid);
		bOk = Game.CreateBroadcast(
			BroadcastName,
			ExpectedHeadline,
			TEXT("Automated CI broadcast body"),
			BroadcastId);
		if (!bOk) { Done.Execute(); return; }

		Game.InitializeLootLockerSDK();
		test_util::StartSession();
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		BroadcastId.Empty();
		ExpectedHeadline.Empty();
		BroadcastName.Empty();
		Done.Execute();
	});

	Describe("Broadcasts", [this]()
	{
		LatentIt("ListTopBroadcasts_ReturnsSuccess", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListBroadcastsResponse, FLootLockerListBroadcastsResponseDelegate>();
			ULootLockerSDKManager::ListTopBroadcasts(Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);

			TestTrue("ListTopBroadcasts succeeded", Response.success);

			TestDone.Execute();
		});

		LatentIt("ListTopBroadcasts_ContainsCreatedBroadcast", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || BroadcastId.IsEmpty())
			{
				AddError(TEXT("Game/broadcast setup failed")); TestDone.Execute(); return;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListBroadcastsResponse, FLootLockerListBroadcastsResponseDelegate>();
			ULootLockerSDKManager::ListBroadcasts({"en"}, 100, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);

			TestTrue("ListTopBroadcasts succeeded", Response.success);

			bool bFound = false;
			for (const FLootLockerBroadcast& B : Response.broadcasts)
			{
				if (B.id == BroadcastId)
				{
					bFound = true;
					// Verify the English headline
					const FLootLockerBroadcastLanguage* EnLang = B.languages.Find(TEXT("en"));
					if (EnLang)
					{
						TestEqual("Broadcast headline matches", EnLang->headline, ExpectedHeadline);
					}
					else
					{
						AddError(TEXT("Broadcast has no 'en' language entry"));
					}
					break;
				}
			}
			TestTrue("Created broadcast appears in ListTopBroadcasts", bFound);

			TestDone.Execute();
		});

		LatentIt("ListBroadcasts_WithLanguage_ReturnsSuccess", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListBroadcastsResponse, FLootLockerListBroadcastsResponseDelegate>();
			ULootLockerSDKManager::ListBroadcasts(TArray<FString>{TEXT("en")}, 10, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);

			TestTrue("ListBroadcasts with language succeeded", Response.success);

			TestDone.Execute();
		});
	});
}
#endif
