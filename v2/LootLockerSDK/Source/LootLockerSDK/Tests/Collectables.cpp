#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerCollectables, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerCollectables)

void FTestLootLockerCollectables::Define()
{
	Describe("Collectables", [this]()
	{
		LatentIt("When working with Collectables", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerCollectablesResponse,FCollectablesResponseDelegate>();
		
				ULootLockerSDKManager::GetAllCollectables(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAllCollectables success", Response.success);
				TestTrue("More than one collectable returned:",Response.collectables.Num()>0);
				delete(Promise);
			}

			test_util::EndSession();
			
			TestDone.Execute();
		});
	});
}

#endif

