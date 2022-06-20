#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMaps, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerMaps)

void FTestLootLockerMaps::Define()
{
	Describe("Maps", [this]()
	{
		LatentIt("When Working with Maps", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetMapsResponse,FGetMapsResponseDelegate>();

				ULootLockerSDKManager::GetMaps(Delegate);

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

