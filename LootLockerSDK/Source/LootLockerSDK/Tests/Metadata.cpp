// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMetadata, "LootLocker.Metadata",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
END_DEFINE_SPEC(FTestLootLockerMetadata)

void FTestLootLockerMetadata::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Metadata"));
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

	Describe("Metadata", [this]()
	{
		LatentIt("SetMetadata_String_ThenListContainsIt", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const FString Key   = TEXT("ci_string_key");
			const FString Value = TEXT("ci_string_value");

			// Create the entry on self
			{
				FLootLockerSetMetadataAction Action;
				Action.Action = ELootLockerMetadataActions::Create_or_Update;
				Action.Entry  = FLootLockerMetadataEntry::MakeStringEntry(Key, {}, {}, Value);

				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SetMetadata(ELootLockerMetadataSources::self, TEXT("self"), {Action}, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SetMetadata (Create) succeeded", Response.success);
				TestEqual("SetMetadata has no per-entry errors", Response.Errors.Num(), 0);
			}

			// List and verify
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListMetadataResponse, FLootLockerListMetadataResponseDelegate>();
				ULootLockerSDKManager::ListMetadata(ELootLockerMetadataSources::self, TEXT("self"), Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("ListMetadata succeeded", Response.success);

				bool bFound = false;
				for (const FLootLockerMetadataEntry& Entry : Response.Entries)
				{
					if (Entry.Key == Key)
					{
						FString Out;
						if (Entry.TryGetValueAsString(Out))
						{
							TestEqual("Metadata value matches", Out, Value);
						}
						else
						{
							AddError(TEXT("Failed to parse metadata value as string"));
						}
						bFound = true;
						break;
					}
				}
				TestTrue("Set key appears in ListMetadata", bFound);
			}

			TestDone.Execute();
		});

		LatentIt("GetMetadata_ByKey_ReturnsCorrectEntry", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const FString Key   = TEXT("ci_get_key");
			const FString Value = TEXT("ci_get_value");

			// Create
			{
				FLootLockerSetMetadataAction Action;
				Action.Action = ELootLockerMetadataActions::Create_or_Update;
				Action.Entry  = FLootLockerMetadataEntry::MakeStringEntry(Key, {}, {}, Value);

				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SetMetadata(ELootLockerMetadataSources::self, TEXT("self"), {Action}, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SetMetadata succeeded", Response.success);
			}

			// Get by key
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetMetadataResponse, FLootLockerGetMetadataResponseDelegate>();
				ULootLockerSDKManager::GetMetadata(ELootLockerMetadataSources::self, TEXT("self"), Key, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetMetadata succeeded", Response.success);
				TestEqual("GetMetadata key matches", Response.Entry.Key, Key);

				FString Out;
				if (Response.Entry.TryGetValueAsString(Out))
				{
					TestEqual("GetMetadata value matches", Out, Value);
				}
				else
				{
					AddError(TEXT("Failed to parse GetMetadata value as string"));
				}
			}

			TestDone.Execute();
		});

		LatentIt("SetMetadata_Update_ChangesValue", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const FString Key      = TEXT("ci_update_key");
			const FString Original = TEXT("original_value");
			const FString Updated  = TEXT("updated_value");

			// Create
			{
				FLootLockerSetMetadataAction CreateAction;
				CreateAction.Action = ELootLockerMetadataActions::Create_or_Update;
				CreateAction.Entry  = FLootLockerMetadataEntry::MakeStringEntry(Key, {}, {}, Original);

				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SetMetadata(ELootLockerMetadataSources::self, TEXT("self"), {CreateAction}, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SetMetadata (Create) succeeded", Response.success);
			}

			// Update
			{
				FLootLockerSetMetadataAction UpdateAction;
				UpdateAction.Action = ELootLockerMetadataActions::Update;
				UpdateAction.Entry  = FLootLockerMetadataEntry::MakeStringEntry(Key, {}, {}, Updated);

				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SetMetadata(ELootLockerMetadataSources::self, TEXT("self"), {UpdateAction}, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SetMetadata (Update) succeeded", Response.success);
			}

			// Verify
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetMetadataResponse, FLootLockerGetMetadataResponseDelegate>();
				ULootLockerSDKManager::GetMetadata(ELootLockerMetadataSources::self, TEXT("self"), Key, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("GetMetadata after update succeeded", Response.success);

				FString Out;
				if (Response.Entry.TryGetValueAsString(Out))
				{
					TestEqual("Updated value is reflected", Out, Updated);
				}
				else
				{
					AddError(TEXT("Failed to parse updated metadata value as string"));
				}
			}

			TestDone.Execute();
		});

		LatentIt("SetMetadata_Delete_RemovedFromList", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid())
			{
				AddError(TEXT("Game setup failed")); TestDone.Execute(); return;
			}

			const FString Key   = TEXT("ci_delete_key");
			const FString Value = TEXT("ci_delete_value");

			// Create
			{
				FLootLockerSetMetadataAction CreateAction;
				CreateAction.Action = ELootLockerMetadataActions::Create_or_Update;
				CreateAction.Entry  = FLootLockerMetadataEntry::MakeStringEntry(Key, {}, {}, Value);

				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SetMetadata(ELootLockerMetadataSources::self, TEXT("self"), {CreateAction}, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SetMetadata (Create) succeeded", Response.success);
			}

			// Delete
			{
				FLootLockerSetMetadataAction DeleteAction;
				DeleteAction.Action = ELootLockerMetadataActions::Delete;
				// MakeStringEntry is used (not MakeEntryExceptValue) because the SDK requires
				// TryGetRawValue() to succeed even for delete actions; the value is ignored server-side.
				DeleteAction.Entry  = FLootLockerMetadataEntry::MakeStringEntry(Key, {}, {}, Value);

				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SetMetadata(ELootLockerMetadataSources::self, TEXT("self"), {DeleteAction}, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SetMetadata (Delete) succeeded", Response.success);
			}

			// Verify gone
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListMetadataResponse, FLootLockerListMetadataResponseDelegate>();
				ULootLockerSDKManager::ListMetadata(ELootLockerMetadataSources::self, TEXT("self"), Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("ListMetadata after delete succeeded", Response.success);

				bool bStillPresent = Response.Entries.ContainsByPredicate(
					[Key](const FLootLockerMetadataEntry& E) { return E.Key == Key; });
				TestFalse("Deleted key no longer present", bStillPresent);
			}

			TestDone.Execute();
		});
	});
}
#endif
