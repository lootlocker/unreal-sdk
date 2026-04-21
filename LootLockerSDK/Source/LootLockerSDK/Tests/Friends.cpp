// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "LootLockerStateData.h"
#include "LootLockerPlatformManager.h"
#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerFriends, "LootLocker.Friends",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString Player1Ulid;
	FString Player2Ulid;
END_DEFINE_SPEC(FTestLootLockerFriends)

void FTestLootLockerFriends::Define()
{
	BeforeEach([this]()
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Friends"));
		if (!bOk) { return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { return; }
		Game.InitializeLootLockerSDK();

		// Start player 1 (main session)
		test_util::StartSession();
		Player1Ulid = ULootLockerStateData::GetSavedStateForFirstPlayer().PlayerUlid;

		// Start player 2 (additional session)
		const test_util::FTestPlayerSession P2 = test_util::StartAdditionalSession();
		if (!P2.bSuccess) { return; }
		Player2Ulid = P2.PlayerUlid;
	});

	AfterEach([this]()
	{
		Game.DeleteGame();
	});

	Describe("Friends", [this]()
	{
		LatentIt("SendFriendRequest_AppearInOutgoing", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Player 1 sends a friend request to Player 2
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerFriendActionResponse, FLootLockerFriendActionResponseDelegate>();
				ULootLockerSDKManager::SendFriendRequest(Player2Ulid, Delegate, Player1Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("SendFriendRequest succeeded", Response.success);
				delete Promise;
			}

			// Player 1's outgoing list should contain Player 2
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListOutgoingFriendRequestsResponse, FLootLockerListOutgoingFriendRequestsResponseDelegate>();
				ULootLockerSDKManager::ListOutgoingFriendRequests(Delegate, Player1Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("ListOutgoingFriendRequests succeeded", Response.success);
				bool bFound = false;
				for (const FLootLockerFriend& F : Response.Outgoing)
				{
					if (F.Player_id == Player2Ulid) { bFound = true; break; }
				}
				TestTrue("Player 2 appears in Player 1 outgoing requests", bFound);
				delete Promise;
			}

			TestDone.Execute();
		});

		LatentIt("SendFriendRequest_AppearInIncoming", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Player 1 sends request to Player 2
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerFriendActionResponse, FLootLockerFriendActionResponseDelegate>();
				ULootLockerSDKManager::SendFriendRequest(Player2Ulid, Delegate, Player1Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("SendFriendRequest succeeded", Response.success);
				delete Promise;
			}

			// Player 2's incoming list should contain Player 1
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListIncomingFriendRequestsResponse, FLootLockerListIncomingFriendRequestsResponseDelegate>();
				ULootLockerSDKManager::ListIncomingFriendRequests(Delegate, Player2Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("ListIncomingFriendRequests succeeded", Response.success);
				bool bFound = false;
				for (const FLootLockerFriend& F : Response.Incoming)
				{
					if (F.Player_id == Player1Ulid) { bFound = true; break; }
				}
				TestTrue("Player 1 appears in Player 2 incoming requests", bFound);
				delete Promise;
			}

			TestDone.Execute();
		});

		LatentIt("AcceptFriendRequest_AppearInFriendsList", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || Player1Ulid.IsEmpty() || Player2Ulid.IsEmpty())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			// Player 1 sends request to Player 2
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerFriendActionResponse, FLootLockerFriendActionResponseDelegate>();
				ULootLockerSDKManager::SendFriendRequest(Player2Ulid, Delegate, Player1Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("SendFriendRequest succeeded", Response.success);
				delete Promise;
			}

			// Player 2 accepts the request
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerFriendActionResponse, FLootLockerFriendActionResponseDelegate>();
				ULootLockerSDKManager::AcceptIncomingFriendRequest(Player1Ulid, Delegate, Player2Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("AcceptIncomingFriendRequest succeeded", Response.success);
				delete Promise;
			}

			// Player 1's friends list should contain Player 2
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListFriendsResponse, FLootLockerListFriendsResponseDelegate>();
				ULootLockerSDKManager::ListFriends(Delegate, Player1Ulid);
				const auto Response = Promise->get_future().get();
				TestTrue("ListFriends succeeded", Response.success);
				bool bFound = false;
				for (const FLootLockerAcceptedFriend& F : Response.Friends)
				{
					if (F.Player_id == Player2Ulid) { bFound = true; break; }
				}
				TestTrue("Player 2 appears in Player 1 friends list", bFound);
				delete Promise;
			}

			TestDone.Execute();
		});
	});
}
#endif
