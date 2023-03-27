#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "ServerAPI/LootLockerServerPersistentStorageRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_PersistentStorage, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_PersistentStorage)

void FTestLootLockerServer_PersistentStorage::Define()
{
	Describe("Server_PersistentStorage", [this]()
	{
		LatentIt("When Server PersistentStorage", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartServerSession();

			const FString PlayerId = "3245521";

			FLootLockerPersistentStorageItem TestItem;
			TestItem.key = "test_key";
			TestItem.value = "test_value";
			TestItem.is_public = false;
			TestItem.order = 0;

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPersistentStorageItemsResponse, FServerPersistentStorageItemsResponseDelegate>();

				TArray<FLootLockerPersistentStorageItem> Items;
				Items.Add(TestItem);

				ULootLockerSDKManager::Server_AddItemsToPersistentStorage(PlayerId, Items, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_AddItemsToPersistentStorage success", Response.success);
				TestEqual("Server_AddItemsToPersistentStorage items returned", Response.items.Num(), 1u);
				TestEqual("Server_AddItemsToPersistentStorage player items returned", Response.items[0].player_id, PlayerId);
				TestEqual("Server_AddItemsToPersistentStorage player items count is 1", Response.items[0].items.Num(), 1);
				TestTrue("Server_AddItemsToPersistentStorage player items ok", Response.items[0].items.ContainsByPredicate([key = TestItem.key](FLootLockerPersistentStorageItem& target)
				{
					return key == target.key;
				}));
				delete(Promise);
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPersistentStorageItemsResponse, FServerPersistentStorageItemsResponseDelegate>();

				ULootLockerSDKManager::Server_GetPlayerPersistentStorage(PlayerId, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_GetPlayerPersistentStorage success", Response.success);
				TestEqual("Server_GetPlayerPersistentStorage items returned", Response.items.Num(), 1u);
				TestEqual("Server_GetPlayerPersistentStorage player items returned", Response.items[0].player_id, PlayerId);
				delete(Promise);
			}
		
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerResponse, FServerPersistentStorageDeleteItemResponseDelegate>();

				ULootLockerSDKManager::Server_DeleteItemFromPersistentStorage(PlayerId, TestItem.key, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("DeleteItemFromPersistentStorage success", Response.success);
				delete(Promise);
			}

			test_util::EndServerSession();

			TestDone.Execute();
		});
	});
}
#endif

