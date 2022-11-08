#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerAssets, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerAssets)

void FTestLootLockerAssets::Define()
{
	Describe("Assets", [this]()
	{
		LatentIt("When working with Assets", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();
			// set this to enable test;
			int AssetId = 1;
			
			// start session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetContextResponse,FContextDelegate>();
		
				ULootLockerSDKManager::GetContexts(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetContexts success", Response.success);
				delete(Promise);
			}
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetAssetsResponse,FAssetsResponseDelegate>();
		
				ULootLockerSDKManager::GetAssets(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAssets success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetAssetsResponse,FAssetsResponseDelegate>();

				TArray<int> AssetIds;
				AssetIds.Add(1);
				ULootLockerSDKManager::GetAssetsByIds(AssetIds,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAssetsByIds success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetAssetBonesResponse,FAssetBonesResponseDelegate>();
					
				ULootLockerSDKManager::GetAssetBones(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAssetBones success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetFavouriteAssetIndicesResponse,FGetFavouriteAssetIndicesResponseDelegate>();
					
				ULootLockerSDKManager::AddAssetToFavourites(AssetId,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("AddAssetToFavourites success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetFavouriteAssetIndicesResponse,FGetFavouriteAssetIndicesResponseDelegate>();
								
				ULootLockerSDKManager::GetFavouriteAssetIndices(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetFavouriteAssetIndices success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetFavouriteAssetIndicesResponse,FGetFavouriteAssetIndicesResponseDelegate>();
								
				ULootLockerSDKManager::RemoveAssetFromFavourites(AssetId,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("RemoveAssetFromFavourites success", Response.success);
				delete(Promise);
			}
						
			TestDone.Execute();
		});
	});
}
#endif

