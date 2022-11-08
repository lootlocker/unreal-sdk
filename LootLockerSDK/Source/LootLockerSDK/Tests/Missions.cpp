#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMissions, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerMissions)

void FTestLootLockerMissions::Define()
{
	Describe("Missions", [this]()
	{
		LatentIt("When Working with Missions", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			int MissionId = 1;
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerMissionsResponse,FMissionsResponseDelegate>();

				ULootLockerSDKManager::GetAllMissions(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetAllMissions success", Response.success);
				delete(Promise);
			}

			//TODO: add a mission using admin api to perform the below tests
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerMissionResponse,FMissionResponseDelegate>();

				ULootLockerSDKManager::GetMission(MissionId,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetMission success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerStartMissionResponse,FStartMissionResponseDelegate>();

				ULootLockerSDKManager::StartMission(MissionId,Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("StartMission success", Response.success);
				delete(Promise);
			}

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerFinishMissionResponse,FFinishMissionResponseDelegate>();

				FLootLockerFinishMissionData MissionData;

				ULootLockerSDKManager::FinishMission(MissionId, MissionData, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("FinishMission success", Response.success);
				delete(Promise);
			}			
			
		});
	});
}
#endif

