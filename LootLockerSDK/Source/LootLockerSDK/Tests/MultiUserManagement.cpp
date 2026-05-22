// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "LootLockerStateData.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMultiUserManagement, "LootLocker.MultiUserManagement",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString Player1Ulid;
	FString Player2Ulid;
END_DEFINE_SPEC(FTestLootLockerMultiUserManagement)

void FTestLootLockerMultiUserManagement::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("MultiUser"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		Game.InitializeLootLockerSDK();
		GetMutableDefault<ULootLockerConfig>()->MultiUserSessionMode = ELootLockerMultiUserSessionMode::Hotseat;

		// Start player 1 as the main session
		test_util::StartSession();
		Player1Ulid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;

		// Start a second independent session
		const test_util::FTestPlayerSession P2 = test_util::StartAdditionalSession();
		if (!P2.bSuccess) { Done.Execute(); return; }
		Player2Ulid = P2.PlayerUlid;

		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		Player1Ulid.Empty();
		Player2Ulid.Empty();
		Done.Execute();
	});

	Describe("MultiUserManagement", [this]()
	{
		LatentIt("TwoSessions_HaveDistinctUlids", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game/session setup failed")); TestDone.Execute(); return;
			}

			TestFalse("Player1 and Player2 have different ULIDs", Player1Ulid == Player2Ulid);

			// Both should appear in the cached player list
			const TArray<FString> CachedUlids = ULootLockerSDKManager::GetCachedPlayerUlids();
			TestTrue("Player1 ULID in cached list", CachedUlids.Contains(Player1Ulid));
			TestTrue("Player2 ULID in cached list", CachedUlids.Contains(Player2Ulid));

			TestDone.Execute();
		});

		LatentIt("SetDefaultPlayer_ChangesDefaultUlid", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game/session setup failed")); TestDone.Execute(); return;
			}

			// Initially Player1 should be the default (it was set first)
			const FString InitialDefault = ULootLockerSDKManager::GetDefaultPlayerUlid();
			TestEqual("Initial default is Player1", InitialDefault, Player1Ulid);

			// Switch default to Player2
			const bool bSet = ULootLockerSDKManager::SetDefaultPlayer(Player2Ulid);
			TestTrue("SetDefaultPlayer succeeded", bSet);

			const FString NewDefault = ULootLockerSDKManager::GetDefaultPlayerUlid();
			TestEqual("Default is now Player2", NewDefault, Player2Ulid);

			// Restore
			ULootLockerSDKManager::SetDefaultPlayer(Player1Ulid);

			TestDone.Execute();
		});

		LatentIt("ClearCacheForPlayer_RemovesFromCachedList", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game/session setup failed")); TestDone.Execute(); return;
			}

			ULootLockerSDKManager::ClearCacheForPlayer(Player1Ulid);

			const TArray<FString> Remaining = ULootLockerSDKManager::GetCachedPlayerUlids();
			TestFalse("Player1 no longer in cached list after clear", Remaining.Contains(Player1Ulid));
			TestTrue("Player2 still in cached list", Remaining.Contains(Player2Ulid));

			TestDone.Execute();
		});

		LatentIt("ClearAllExcept_OnlyRetainsSpecifiedPlayer", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game/session setup failed")); TestDone.Execute(); return;
			}

			ULootLockerSDKManager::ClearAllPlayerCachesExceptForPlayer(Player2Ulid);

			const TArray<FString> Remaining = ULootLockerSDKManager::GetCachedPlayerUlids();
			TestFalse("Player1 cleared from list", Remaining.Contains(Player1Ulid));
			TestTrue("Player2 retained in list", Remaining.Contains(Player2Ulid));

			TestDone.Execute();
		});
	});
}
#endif
