#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerPlayer, "LootLocker",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerAuthenticationResponse AuthenticationResponse;
END_DEFINE_SPEC(FTestLootLockerPlayer)

void FTestLootLockerPlayer::Define()
{
	Describe("Player", [this]()
	{
		LatentIt("When GetPlayerInfo", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			// Get player info
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPlayerInfoResponse,FLootLockerPlayerInformationResponse>();
				ULootLockerSDKManager::GetPlayerInfo(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetPlayerInfo ok", Response.success);
				delete(Promise);
			}
			

			test_util::EndSession();
			TestDone.Execute();			
		});
		
		LatentIt("When PlayerName", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();
			FString Name = "TestName";

			// Set player name
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerNameResponse,FPNameResponse>();
				ULootLockerSDKManager::SetPlayerName(Name, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("SetPlayerName ok", Response.success);
				delete(Promise);
			}
					
			// Get player name
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerNameResponse,FPNameResponse>();
				ULootLockerSDKManager::GetPlayerName(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetPlayerName ok", Response.success);
				TestTrue("Name set correctly", Response.name == Name);
				delete(Promise);
			}
			

			test_util::EndSession();
			TestDone.Execute();			
		});

		LatentIt("When GetPlayerInventory", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			// Get player info
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerInventoryResponse, FInventoryResponse>();
				ULootLockerSDKManager::GetInventory(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetInventory ok", Response.success);
				delete(Promise);
			}
					

			test_util::EndSession();
			TestDone.Execute();			
		});
		
	});
}
#endif
