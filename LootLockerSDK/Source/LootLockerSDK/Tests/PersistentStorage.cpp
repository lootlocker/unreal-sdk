#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestPersistentStorage, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestPersistentStorage)

void FTestPersistentStorage::Define()
{
	Describe("PersistentStorage", [this]()
	{
		LatentIt("When Working with PersistentStorage", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{

			test_util::StartSession();

			FString TestKey = "testkey";

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPersistentStorageItemsResponse,FPersistentStorageItemsResponseDelegate>();

				// TODO: which key
				ULootLockerSDKManager::DeleteItemFromPersistentStorage(TestKey, Delegate);
							
				const auto Response = Promise ->get_future().get();
				TestTrue("DeleteItemFromPersistentStorage success", Response.success);

				delete(Promise);
				//TODO: check output
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPersistentStorageItemsResponse,FPersistentStorageItemsResponseDelegate>();

				FLootLockerPersistentStorageItems items;
				FLootLockerPersistentStorageItem item;
				item.key = "test_key";
				item.value = "test_value";
				
				ULootLockerSDKManager::AddItemsToPersistentStorage(items, Delegate);
										
				const auto Response = Promise ->get_future().get();
				TestTrue("AddItemsToPersistentStorage success", Response.success);

				delete(Promise);
				//TODO: check output
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPersistentStorageItemsResponse,FPersistentStorageItemsResponseDelegate>();

				ULootLockerSDKManager::GetEntirePersistentStorage(Delegate);
				
				const auto Response = Promise ->get_future().get();
				TestTrue("GetCharacterLoadouts success", Response.success);

				delete(Promise);
				//TODO: check output
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPersistentStorageItemResponse,FPersistentStorageItemResponseDelegate>();

				// TODO: which key
				ULootLockerSDKManager::GetItemFromPersistentStorage( "test_key", Delegate);
				
				const auto Response = Promise ->get_future().get();
				TestTrue("GetItemFromPersistentStorage success", Response.success);

				delete(Promise);
				//TODO: check output
			}
		});
	});
}
#endif

