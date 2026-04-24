// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerPlayerData.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"
#include "LootLockerStateData.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerAssetInstances, "LootLocker.AssetInstances",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	int32 AssetId    = 0;
	int32 InstanceId = 0;
	int32 PlayerId   = 0;
END_DEFINE_SPEC(FTestLootLockerAssetInstances)

void FTestLootLockerAssetInstances::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("AssetInstances"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.CreateAsset(AssetId, TEXT("CI-AssetInstance-Asset"));
		if (!bOk) { Done.Execute(); return; }
		Game.InitializeLootLockerSDK();

		// Do the guest login inline so we can capture the numeric player_id,
		// which is required by the admin grant endpoint (StartSession() does not store it).
		ULootLockerStateData::ClearAllSavedStates();
		{
			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse, FLootLockerSessionResponse>();
			ULootLockerSDKManager::GuestLogin(Delegate, TEXT("unreal_unit_test_user"));
			const auto Response = test_util::WaitAndGet(Promise, 60);
			if (!Response.success) { Done.Execute(); return; }
			PlayerId = Response.player_id;
			FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(
				Response.session_token, TEXT(""), Response.player_identifier,
				Response.player_ulid, Response.public_uid, TEXT(""), TEXT(""), TEXT(""),
				ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest),
				FDateTime::Now().ToString(), Response.player_created_at);
			ULootLockerStateData::SavePlayerData(NewPlayerData);
		}
		if (PlayerId == 0) { Done.Execute(); return; }
		Game.GrantAssetToPlayer(FString::FromInt(PlayerId), AssetId, InstanceId);
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		AssetId    = 0;
		InstanceId = 0;
		PlayerId   = 0;
		Done.Execute();
	});

	Describe("AssetInstances", [this]()
	{
		LatentIt("CreateKVP_ThenGetAll_Contains", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || InstanceId == 0)
			{
				AddError(TEXT("Game/asset setup failed")); TestDone.Execute(); return;
			}

			// Create a KVP
			{
				FLootLockerAssetInstanceStorageItem Item;
				Item.key   = TEXT("ci_key");
				Item.value = TEXT("ci_value");
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(InstanceId, Item, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("CreateAKeyValuePairForAssetInstance succeeded", Response.success);
			}

			// GetAll should contain the created key
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(InstanceId, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetAllKeyValuePairsForAssetInstance succeeded", Response.success);
				bool bFound = Response.storage.ContainsByPredicate([](const FLootLockerAssetInstanceStorageResponseItem& I)
				{
					return I.key == TEXT("ci_key") && I.value == TEXT("ci_value");
				});
				TestTrue("GetAll contains created KVP", bFound);
			}

			TestDone.Execute();
		});

		LatentIt("CreateKVP_ThenGetById_Matches", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || InstanceId == 0)
			{
				AddError(TEXT("Game/asset setup failed")); TestDone.Execute(); return;
			}

			int32 StorageItemId = 0;

			// Create a KVP
			{
				FLootLockerAssetInstanceStorageItem Item;
				Item.key   = TEXT("lookup_key");
				Item.value = TEXT("lookup_value");
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(InstanceId, Item, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("CreateAKeyValuePairForAssetInstance succeeded", Response.success);
				if (Response.storage.Num() > 0)
				{
					StorageItemId = Response.storage.Last().id;
				}
			}

			if (StorageItemId == 0) { AddError(TEXT("No storage item id returned")); TestDone.Execute(); return; }

			// Get by ID
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemResponse, FAssetInstanceStorageItemResponseDelegate>();
				ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(InstanceId, StorageItemId, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetAKeyValuePairByIdForAssetInstance succeeded", Response.success);
				TestEqual("Storage item key matches", Response.storage.key, FString(TEXT("lookup_key")));
			}

			TestDone.Execute();
		});

		LatentIt("CreateKVP_ThenUpdate_ValueChanges", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || InstanceId == 0)
			{
				AddError(TEXT("Game/asset setup failed")); TestDone.Execute(); return;
			}

			int32 StorageItemId = 0;

			// Create
			{
				FLootLockerAssetInstanceStorageItem Item;
				Item.key   = TEXT("update_key");
				Item.value = TEXT("original");
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(InstanceId, Item, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("CreateAKeyValuePairForAssetInstance succeeded", Response.success);
				if (Response.storage.Num() > 0) { StorageItemId = Response.storage.Last().id; }
			}

			if (StorageItemId == 0) { AddError(TEXT("No storage item id returned")); TestDone.Execute(); return; }

			// Update by ID
			{
				FLootLockerAssetInstanceStorageItem Updated;
				Updated.key   = TEXT("update_key");
				Updated.value = TEXT("modified");
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemResponse, FAssetInstanceStorageItemResponseDelegate>();
				ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(InstanceId, StorageItemId, Updated, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("UpdateAKeyValuePairByIdForAssetInstance succeeded", Response.success);
				TestEqual("Value updated", Response.storage.value, FString(TEXT("modified")));
			}

			TestDone.Execute();
		});

		LatentIt("CreateKVP_ThenDelete_RemovedFromList", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid() || InstanceId == 0)
			{
				AddError(TEXT("Game/asset setup failed")); TestDone.Execute(); return;
			}

			int32 StorageItemId = 0;

			// Create
			{
				FLootLockerAssetInstanceStorageItem Item;
				Item.key   = TEXT("delete_key");
				Item.value = TEXT("to_be_deleted");
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(InstanceId, Item, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("CreateAKeyValuePairForAssetInstance succeeded", Response.success);
				if (Response.storage.Num() > 0) { StorageItemId = Response.storage.Last().id; }
			}

			if (StorageItemId == 0) { AddError(TEXT("No storage item id returned")); TestDone.Execute(); return; }

			// Delete
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(InstanceId, StorageItemId, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("DeleteAKeyValuePairByIdForAssetInstance succeeded", Response.success);
			}

			// Verify gone
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse, FAssetInstanceStorageItemsResponseDelegate>();
				ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(InstanceId, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetAll after delete succeeded", Response.success);
				bool bStillPresent = Response.storage.ContainsByPredicate([StorageItemId](const FLootLockerAssetInstanceStorageResponseItem& I)
				{
					return I.id == StorageItemId;
				});
				TestFalse("Deleted KVP no longer present", bStillPresent);
			}

			TestDone.Execute();
		});
	});
}
#endif

