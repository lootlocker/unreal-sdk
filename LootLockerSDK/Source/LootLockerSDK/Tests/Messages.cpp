#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerMessages, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerMessages)

void FTestLootLockerMessages::Define()
{
	Describe("Messages", [this]()
	{
		LatentIt("When Working with Messages", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerMessagesResponse, FMessagesResponseDelegate>();

				ULootLockerSDKManager::GetMessages(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetMessages success", Response.success);

				delete(Promise);
			}

			test_util::EndSession();
			
		});
	});
}
#endif

