#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "ServerAPI/LootLockerServerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_Authentication, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_Authentication)

void FTestLootLockerServer_Authentication::Define()
{
	Describe("Server_Authentication", [this]()
	{
		LatentIt("When Start/End server session", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{			
			// start session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerServerAuthenticationResponse,FServerAuthResponseDelegate>();
		
				ULootLockerSDKManager::Server_StartSession(Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_StartSession success", Response.success);
				TestFalse("Server_StartSession session token not empty", Response.token.IsEmpty());
				delete(Promise);
			}
			// end session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse,FServerEndSessionResponseDelegate>();
		
				ULootLockerSDKManager::Server_EndSession(Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_EndSession success", Response.success);
				delete(Promise);
			}
			TestDone.Execute();
		});
	});
}
#endif

