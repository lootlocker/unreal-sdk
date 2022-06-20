#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FLootLockersTestLeaderboards, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FLootLockersTestLeaderboards)

void FLootLockersTestLeaderboards::Define()
{
	Describe("Leaderboards", [this]()
	{
		LatentIt("When Working with Leaderboards", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			// get character loadout
			// TODO: add player id to start session
			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerCharacterLoadoutResponse,FCharacterLoadoutResponse>();

				// ULootLockerSDKManager::SubmitScore()

				const auto Response = Promise ->get_future().get();
				TestTrue("GetCharacterLoadouts success", Response.success);
				TestTrue("GetCharacterLoadouts available", Response.loadouts.Num()>0);
				delete(Promise);
			}
			
		});
	});
}
#endif

