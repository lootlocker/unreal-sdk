#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FWhiteLabelLogin, "LootLocker.WhiteLabel", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FWhiteLabelLogin)

void FWhiteLabelLogin::Define()
{
	Describe("WhiteLabelLogin", [this]()
	{

		LatentIt("When Working with WhiteLabel Login (requires manual steps)", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			// Fill this in to be able to test the login with your information.
			FString TestEmail = "";
			FString TestPassword = "";
			bool SkipSignup = false; // change this to true if you don't want to create the account

			if(TestEmail.IsEmpty() && !SkipSignup)
			{
				TestEmail = FString::Format(TEXT("erik+unrealci+{0}@lootlocker.com"), { FGuid::NewGuid().ToString() });
				TestPassword = "12345678";
			}

			
			TestFalse("Test email needs to be specified", TestEmail.IsEmpty());
			TestFalse("Test password needs to be specified", TestPassword.IsEmpty());

			if (!SkipSignup)
			{
				// signup
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerLoginResponse, FLootLockerLoginResponseDelegate>();

				ULootLockerSDKManager::WhiteLabelCreateAccount(TestEmail, TestPassword, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Signup success", Response.success);
				delete(Promise);
			}

			{
				// signin
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerWhiteLabelLoginAndSessionResponse, FLootLockerWhiteLabelLoginAndSessionResponseDelegate>();

				ULootLockerSDKManager::WhiteLabelLoginAndStartSession(TestEmail, TestPassword, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Signin success", Response.success);
				TestTrue("Seen Before flag has the expected value", Response.StartSessionResponse.seen_before == SkipSignup);
				TestTrue("Player has a ulid", !Response.StartSessionResponse.player_ulid.IsEmpty());
				delete(Promise);
			}

			TestDone.Execute();
		});
	});
}
#endif

