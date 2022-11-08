#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerDroptables, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerDroptables)

void FTestLootLockerDroptables::Define()
{
	Describe("Droptables", [this]()
	{
		LatentIt("When Start/End session", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			constexpr int TableId = 1;

			test_util::StartSession();
			
			// start session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerComputeAndLockDropTableResponse,FLootLockerComputeAndLockDropTableResponseDelegate>();
		
				ULootLockerSDKManager::ComputeAndLockDropTable(TableId, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("ComputeAndLockDropTable success", Response.success);
				delete(Promise);
			}
			// end session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPickDropsFromDropTableResponse,FFLootLockerPickDropsFromDropTableResponseDelegate>();

				const TArray<int> Picks;
				
				ULootLockerSDKManager::PickDropsFromDropTable(Picks,TableId,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("PickDropsFromDropTable success", Response.success);
				delete(Promise);
			}
			TestDone.Execute();
		});
	});
}
#endif

