#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMiscellaneous, "LootLocker.Miscellaneous", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerMiscellaneous)

void FTestLootLockerMiscellaneous::Define()
{
	Describe("Miscellaneous", [this]()
	{
		LatentIt("When Working with ServerTime", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			// TODO: uses blocking future::get() without timeout — hangs if backend is slow; rewrite with WaitAndGet
			UE_LOG(LogTemp, Warning, TEXT("SKIPPED: When Working with ServerTime — uses blocking get() without timeout"));
			TestDone.Execute();
			return;

			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerTimeResponse,FTimeResponseDelegate>();

				ULootLockerSDKManager::GetServerTime(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetMaps success", Response.success);
				// TestTrue("GetCharacterLoadouts available", Response.loadouts.Num()>0);
				delete(Promise);
			}

			test_util::EndSession();
		});
	});
}
#endif

