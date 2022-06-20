#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerTriggerEvents, "LootLocker",EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerTriggerEvents)

void FTestLootLockerTriggerEvents::Define()
{
	Describe("PlayerFiles", [this]()
	{
		LatentIt("When PlayerFiles", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerTriggerEventResponse,FTriggerEventResponseDelegate>();

				FLootLockerTriggerEvent Request;
				Request.name = "triggername";

				ULootLockerSDKManager::TriggerEvent(Request, Delegate);
				
				const auto Response = Promise ->get_future().get();
				TestTrue("Trigger event ok", Response.success);
				delete(Promise);
			}
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerTriggersResponse,FTriggersResponseDelegate>();
			
				ULootLockerSDKManager::GetTriggeredEvents(Delegate);
			
				const auto Response = Promise ->get_future().get();
				TestTrue("ListFiles ok", Response.success);
				delete(Promise);
			}

			test_util::EndSession();
			TestDone.Execute();			
		});
	});
}
#endif
