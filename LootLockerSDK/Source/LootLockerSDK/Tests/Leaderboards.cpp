#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FLootLockersTestLeaderboards, "LootLocker.Leaderboards", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString LeaderboardKey;
	FString PlayerUlid;
END_DEFINE_SPEC(FLootLockersTestLeaderboards)

void FLootLockersTestLeaderboards::Define()
{
	BeforeEach([this]()
	{
		LeaderboardKey = TEXT("ci_lb_") + FGuid::NewGuid().ToString(EGuidFormats::Short);
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Leaderboards"));
		if (!bOk) { return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { return; }
		bOk = Game.CreateLeaderboard(LeaderboardKey, TEXT("player"), TEXT("Descending"));
		if (!bOk) { return; }
		Game.InitializeLootLockerSDK();
		test_util::StartSession();
		PlayerUlid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;
	});

	AfterEach([this]()
	{
		Game.DeleteGame();
	});

	Describe("Leaderboards", [this]()
	{
		LatentIt("SubmitScore_GetsReflectedInMemberRank", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Submit a score
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::SubmitScore(PlayerUlid, LeaderboardKey, 1000, TEXT(""), Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("SubmitScore succeeded", Response.success);
				delete Promise;
			}

			// Verify via GetMemberRank
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetMemberRankResponse, FLootLockerGetMemberRankResponseDelegate>();
				ULootLockerSDKManager::GetMemberRank(LeaderboardKey, PlayerUlid, Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("GetMemberRank succeeded", Response.success);
				TestEqual("Score matches submitted value", Response.score, 1000);
				delete Promise;
			}

			TestDone.Execute();
		});

		LatentIt("GetScoreList_ContainsSubmittedScore", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Submit a score
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::SubmitScore(PlayerUlid, LeaderboardKey, 500, TEXT(""), Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("SubmitScore succeeded", Response.success);
				delete Promise;
			}

			// Get leaderboard and verify entry is present
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetScoreListResponse, FLootLockerGetScoreListResponseDelegate>();
				ULootLockerSDKManager::GetScoreListInitial(LeaderboardKey, 10, Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("GetScoreListInitial succeeded", Response.success);
				TestTrue("Score list is non-empty", Response.items.Num() > 0);
				delete Promise;
			}

			TestDone.Execute();
		});

		LatentIt("QueryScore_ReturnsPlacement", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Submit a score first so the leaderboard is non-empty
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::SubmitScore(PlayerUlid, LeaderboardKey, 750, TEXT(""), Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("SubmitScore succeeded", Response.success);
				delete Promise;
			}

			// Query placement for a score value
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::QueryScore(LeaderboardKey, 750, Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("QueryScore succeeded", Response.success);
				TestTrue("Rank is valid", Response.rank > 0);
				delete Promise;
			}

			TestDone.Execute();
		});

		LatentIt("IncrementScore_IncreasesExistingScore", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Submit initial score
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::SubmitScore(PlayerUlid, LeaderboardKey, 200, TEXT(""), Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("Initial SubmitScore succeeded", Response.success);
				delete Promise;
			}

			// Increment by 100
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::IncrementScore(PlayerUlid, LeaderboardKey, 100, Delegate);
				const auto Response = Promise->get_future().get();
				TestTrue("IncrementScore succeeded", Response.success);
				TestEqual("Score after increment is 300", Response.score, 300);
				delete Promise;
			}

			TestDone.Execute();
		});
	});
}
#endif

