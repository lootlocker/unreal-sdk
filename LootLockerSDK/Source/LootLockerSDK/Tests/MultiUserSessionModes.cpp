// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerConfig.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerSDKManager.h"
#include "LootLockerSessionOptionals.h"
#include "LootLockerStateData.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMultiUserSessionModes, "LootLocker.MultiUserSessionModes",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
END_DEFINE_SPEC(FTestLootLockerMultiUserSessionModes)

void FTestLootLockerMultiUserSessionModes::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("MultiUserSessionModes"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		Game.InitializeLootLockerSDK();
		ULootLockerStateData::ClearAllSavedStates();
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		Done.Execute();
	});

	Describe("SingleSession", [this]()
	{
		LatentIt("SecondAuth_ClearsFirst", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Given
			GetMutableDefault<ULootLockerConfig>()->MultiUserSessionMode = ELootLockerMultiUserSessionMode::SingleSession;

			test_util::StartSession();
			const FString Player1Ulid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;
			if (Player1Ulid.IsEmpty()) { AddError(TEXT("First session failed")); TestDone.Execute(); return; }

			// When
			const test_util::FTestPlayerSession P2 = test_util::StartAdditionalSession();
			if (!P2.bSuccess) { AddError(TEXT("Second session failed")); TestDone.Execute(); return; }

			// Then
			const TArray<FString> CachedUlids = ULootLockerStateData::GetCachedPlayerUlids();
			const TArray<FString> ActiveUlids = ULootLockerStateData::GetActivePlayerUlids();
			const FString DefaultUlid = ULootLockerStateData::GetDefaultPlayerUlid();

			TestEqual("SingleSession should retain only 1 cached player", CachedUlids.Num(), 1);
			TestEqual("SingleSession should retain only 1 active player", ActiveUlids.Num(), 1);
			TestFalse("First player should have been cleared from cache", CachedUlids.Contains(Player1Ulid));
			TestTrue("Second player should remain in cache", CachedUlids.Contains(P2.PlayerUlid));
			TestEqual("Second player should be the default", DefaultUlid, P2.PlayerUlid);

			TestDone.Execute();
		});

		LatentIt("ReauthSamePlayer_DoesNotClearPlayer", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Given
			GetMutableDefault<ULootLockerConfig>()->MultiUserSessionMode = ELootLockerMultiUserSessionMode::SingleSession;

			const FString Identifier = TEXT("reauth_test_user");

			// First login
			ULootLockerStateData::ClearAllSavedStates();
			const auto [Promise1, Delegate1] = test_util::CreateDelegate<FLootLockerAuthenticationResponse, FLootLockerSessionResponse>();
			ULootLockerSDKManager::GuestLogin(Delegate1, Identifier, FLootLockerSessionOptionals{});
			const auto Response1 = test_util::WaitAndGet(Promise1, 60);
			if (!Response1.success) { AddError(TEXT("First login failed")); TestDone.Execute(); return; }
			FLootLockerPlayerData PD1 = FLootLockerPlayerData::Create(
				Response1.session_token, TEXT(""), Response1.player_identifier, Response1.player_ulid,
				Response1.public_uid, TEXT(""), TEXT(""), TEXT(""),
				ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest),
				FDateTime::Now().ToString(), Response1.player_created_at);
			ULootLockerStateData::SavePlayerData(PD1);
			const FString Player1Ulid = Response1.player_ulid;

			// When — re-authenticate using the same identifier
			const auto [Promise2, Delegate2] = test_util::CreateDelegate<FLootLockerAuthenticationResponse, FLootLockerSessionResponse>();
			ULootLockerSDKManager::GuestLogin(Delegate2, Identifier, FLootLockerSessionOptionals{});
			const auto Response2 = test_util::WaitAndGet(Promise2, 60);
			if (!Response2.success) { AddError(TEXT("Re-auth login failed")); TestDone.Execute(); return; }
			FLootLockerPlayerData PD2 = FLootLockerPlayerData::Create(
				Response2.session_token, TEXT(""), Response2.player_identifier, Response2.player_ulid,
				Response2.public_uid, TEXT(""), TEXT(""), TEXT(""),
				ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest),
				FDateTime::Now().ToString(), Response2.player_created_at);
			ULootLockerStateData::SavePlayerData(PD2);

			// Then
			const TArray<FString> CachedUlids = ULootLockerStateData::GetCachedPlayerUlids();
			const TArray<FString> ActiveUlids = ULootLockerStateData::GetActivePlayerUlids();

			TestEqual("Re-authenticating same identifier should return same ULID", Response2.player_ulid, Player1Ulid);
			TestEqual("SingleSession should retain only 1 cached player after re-auth", CachedUlids.Num(), 1);
			TestEqual("SingleSession should retain only 1 active player after re-auth", ActiveUlids.Num(), 1);
			TestTrue("Re-authenticated player should still be cached", CachedUlids.Contains(Player1Ulid));

			TestDone.Execute();
		});
	});

	Describe("ProfileSwitching", [this]()
	{
		LatentIt("SecondAuth_DeactivatesFirstButKeepsBothCached", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Given
			GetMutableDefault<ULootLockerConfig>()->MultiUserSessionMode = ELootLockerMultiUserSessionMode::ProfileSwitching;

			test_util::StartSession();
			const FString Player1Ulid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;
			if (Player1Ulid.IsEmpty()) { AddError(TEXT("First session failed")); TestDone.Execute(); return; }

			// When
			const test_util::FTestPlayerSession P2 = test_util::StartAdditionalSession();
			if (!P2.bSuccess) { AddError(TEXT("Second session failed")); TestDone.Execute(); return; }

			// Then
			const TArray<FString> CachedUlids = ULootLockerStateData::GetCachedPlayerUlids();
			const TArray<FString> ActiveUlids = ULootLockerStateData::GetActivePlayerUlids();
			const FString DefaultUlid = ULootLockerStateData::GetDefaultPlayerUlid();

			TestEqual("ProfileSwitching should retain both players in cache", CachedUlids.Num(), 2);
			TestEqual("ProfileSwitching should leave only 1 active player", ActiveUlids.Num(), 1);
			TestTrue("First player should still be in cache", CachedUlids.Contains(Player1Ulid));
			TestTrue("Second player should be in cache", CachedUlids.Contains(P2.PlayerUlid));
			TestFalse("First player should be inactive", ActiveUlids.Contains(Player1Ulid));
			TestTrue("Second player should be active", ActiveUlids.Contains(P2.PlayerUlid));
			TestEqual("Second player should be the default", DefaultUlid, P2.PlayerUlid);

			TestDone.Execute();
		});
	});

	Describe("Hotseat", [this]()
	{
		LatentIt("MultipleAuths_AllRemainActive_FirstIsDefault", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Given
			GetMutableDefault<ULootLockerConfig>()->MultiUserSessionMode = ELootLockerMultiUserSessionMode::Hotseat;

			test_util::StartSession();
			const FString Player1Ulid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;
			if (Player1Ulid.IsEmpty()) { AddError(TEXT("First session failed")); TestDone.Execute(); return; }

			// When — start two more sessions
			const test_util::FTestPlayerSession P2 = test_util::StartAdditionalSession();
			if (!P2.bSuccess) { AddError(TEXT("Second session failed")); TestDone.Execute(); return; }

			const test_util::FTestPlayerSession P3 = test_util::StartAdditionalSession();
			if (!P3.bSuccess) { AddError(TEXT("Third session failed")); TestDone.Execute(); return; }

			// Then
			const TArray<FString> CachedUlids = ULootLockerStateData::GetCachedPlayerUlids();
			const TArray<FString> ActiveUlids = ULootLockerStateData::GetActivePlayerUlids();
			const FString DefaultUlid = ULootLockerStateData::GetDefaultPlayerUlid();

			TestEqual("Hotseat should retain all 3 players in cache", CachedUlids.Num(), 3);
			TestEqual("Hotseat should keep all 3 players active", ActiveUlids.Num(), 3);
			TestTrue("First player should be in cache", CachedUlids.Contains(Player1Ulid));
			TestTrue("Second player should be in cache", CachedUlids.Contains(P2.PlayerUlid));
			TestTrue("Third player should be in cache", CachedUlids.Contains(P3.PlayerUlid));
			TestEqual("First player should remain the default in Hotseat mode", DefaultUlid, Player1Ulid);

			TestDone.Execute();
		});
	});
}
#endif
