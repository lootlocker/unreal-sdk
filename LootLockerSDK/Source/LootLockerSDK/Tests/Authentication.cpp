#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerAuthentication, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerAuthentication)

void FTestLootLockerAuthentication::Define()
{
	Describe("Authentication", [this]()
	{
		LatentIt("When Start/End session", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			// set this to enable test;
			const FString PlayerIdentifier="unreal_unit_test_user";
			
			TestFalse("PlayerIdentifier is set",PlayerIdentifier.IsEmpty());
			
			// start session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse,FLootLockerSessionResponse>();
		
				ULootLockerSDKManager::GuestLogin(Delegate, PlayerIdentifier);

				const auto Response = Promise ->get_future().get();
				ULootLockerStateData::SetToken(Response.session_token);
				TestTrue("Startsession success", Response.success);
				delete(Promise);
			}
			// end session
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse,FLootLockerDefaultAuthenticationResponse>();
		
				ULootLockerSDKManager::EndSession(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("Endsession success", Response.success);
				delete(Promise);
			}
			TestDone.Execute();
		});
	});
}
#endif

