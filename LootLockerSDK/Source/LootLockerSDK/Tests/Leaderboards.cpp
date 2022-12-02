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
			// get member rank
			// TODO: add player id to start session
			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGetMemberRankResponse,FLootLockerGetMemberRankResponseDelegate>();

				ULootLockerSDKManager::GetMemberRank("1", "1", Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetMemberRank success", Response.success);
				delete(Promise);
			}
			
		});
	});
}
#endif

