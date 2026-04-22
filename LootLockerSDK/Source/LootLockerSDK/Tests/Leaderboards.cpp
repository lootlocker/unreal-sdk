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
	FString PlayerPublicUid;
END_DEFINE_SPEC(FLootLockersTestLeaderboards)

void FLootLockersTestLeaderboards::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		LeaderboardKey = TEXT("ci_lb_") + FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower();
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Leaderboards"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.CreateLeaderboard(LeaderboardKey, TEXT("generic"), TEXT("descending"));
		if (!bOk) { Done.Execute(); return; }
		Game.InitializeLootLockerSDK();
		test_util::StartSession();
		PlayerUlid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;
		PlayerPublicUid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerPublicUid;
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		Done.Execute();
	});

	Describe("Leaderboards", [this]()
	{
		LatentIt("SubmitScore_GetsReflectedInMemberRank", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Submit a score using the ULID as member ID (works for generic leaderboards)
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::SubmitScore(PlayerUlid, LeaderboardKey, 1000, TEXT(""), Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SubmitScore succeeded", Response.success);
			}

			// Verify via GetMemberRank (same member ID as used for submit)
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetMemberRankResponse, FLootLockerGetMemberRankResponseDelegate>();
				ULootLockerSDKManager::GetMemberRank(LeaderboardKey, PlayerUlid, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetMemberRank succeeded", Response.success);
				TestEqual("Score matches submitted value", Response.score, 1000);
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
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SubmitScore succeeded", Response.success);
			}

			// Get leaderboard and verify entry is present
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetScoreListResponse, FLootLockerGetScoreListResponseDelegate>();
				ULootLockerSDKManager::GetScoreListInitial(LeaderboardKey, 10, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetScoreListInitial succeeded", Response.success);
				TestTrue("Score list is non-empty", Response.items.Num() > 0);
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
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SubmitScore succeeded", Response.success);
			}

			// Query placement for a score value
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::QueryScore(LeaderboardKey, 750, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("QueryScore succeeded", Response.success);
				TestTrue("Rank is valid", Response.rank > 0);
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
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("Initial SubmitScore succeeded", Response.success);
			}

			// Increment by 100
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSubmitScoreResponse, FLootLockerSubmitScoreResponseDelegate>();
				ULootLockerSDKManager::IncrementScore(PlayerUlid, LeaderboardKey, 100, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("IncrementScore succeeded", Response.success);
				TestEqual("Score after increment is 300", Response.score, 300);
			}

			TestDone.Execute();
		});
	});
}
#endif

