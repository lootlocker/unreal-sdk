#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerAssetInstances, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerAssetInstances)

void FTestLootLockerAssetInstances::Define()
{
	Describe("AssetInstances", [this]()
	{
		LatentIt("When using AssetInstances", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();
			
			int AssetInstanceId=1;
			int StorageItemId=1;

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse,FAssetInstanceStorageItemsResponseDelegate>();
									
				ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId,StorageItemId, Delegate);

				const auto Response = Promise ->get_future().get();
				// this will fail if the entry does not exists
				delete(Promise);
			}

						
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse,FAssetInstanceStorageItemsResponseDelegate>();
				
				FLootLockerAssetInstanceStorageItem Item;

				Item.key="test_key";
				Item.value="test_value";

				
				ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("CreateAKeyValuePairForAssetInstance success", Response.success);
				delete(Promise);
			}
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse,FAssetInstanceStorageItemsResponseDelegate>();
		
				ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(1, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAllKeyValuePairsForAssetInstance success", Response.success);
				delete(Promise);
			}

			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemResponse,FAssetInstanceStorageItemResponseDelegate>();
		
				ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(1,1,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAKeyValuePairByIdForAssetInstance success", Response.success);
				delete(Promise);
			}
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemResponse,FAssetInstanceStorageItemResponseDelegate>();

				FLootLockerAssetInstanceStorageItem Item;
				//TODO: fill in item
				
				ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance( AssetInstanceId,  StorageItemId, Item,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("UpdateAKeyValuePairByIdForAssetInstance success", Response.success);
				delete(Promise);
			}
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetInstanceStorageItemsResponse,FAssetInstanceStorageItemsResponseDelegate>();
				FLootLockerAssetInstanceStorageItems Items;
				// TODO: fix item
				ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("UpdateOneOrMoreKeyValuePairForAssetInstance success", Response.success);
				delete(Promise);
			}
			


						
			TestDone.Execute();
		});
	});
}
#endif

