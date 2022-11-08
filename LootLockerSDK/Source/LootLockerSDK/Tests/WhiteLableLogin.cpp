#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FWhiteLabelLogin, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FWhiteLabelLogin)

void FWhiteLabelLogin::Define()
{
	Describe("WhiteLableLogin", [this]()
	{

		LatentIt("When Working with WhiteLable Login (requires manual steps)", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			// Fill this in to be able to test the login.
			// If starting from signup enable TestSignup 
			FString TestEmail;
			FString TestPassword;
			bool TestSignup = false; // change this to true to generate verification mail, needs to be manually confirmed/verified
			
			TestFalse("Test email needs to be specified", TestEmail.IsEmpty());
			TestFalse("Test password needs to be specified", TestPassword.IsEmpty());

			//TODO: check if this is needed
			//test_util::StartSession();

			if (TestSignup)
			{
				// signup
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerLoginResponse,FLootLockerLoginResponseDelegate>();
		
				ULootLockerSDKManager::WhiteLabelCreateAccount(TestEmail,TestPassword,Delegate);
		
				const auto Response = Promise ->get_future().get();
				TestTrue("Signup success", Response.success);
				delete(Promise);
			} else
			{
				// signin
				/*const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse, FLootLockerSessionResponse>();
						
				ULootLockerSDKManager::WhiteLabelStartSession(TestEmail,Delegate);
						
				const auto Response = Promise ->get_future().get();
				TestTrue("Signup success", Response.success);
				delete(Promise);*/
				TestTrue("Hehe", true);
			}

			//TODO: check if this is needed
			// test_util::EndSession();
		});
	});
}
#endif

