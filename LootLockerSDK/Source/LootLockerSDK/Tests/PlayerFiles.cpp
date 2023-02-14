#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FLootLockerTestPlayerFiles, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
//	FLootLockerAuthenticationResponse AuthenticationResponse;
END_DEFINE_SPEC(FLootLockerTestPlayerFiles)

void FLootLockerTestPlayerFiles::Define()
{
	Describe("PlayerFiles", [this]()
	{
		LatentIt("When PlayerFiles", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			int FileId = 0;
			FString FileName;

			FFileHelper::SaveStringToFile(TEXT("TestDataAbc123"), TEXT("test-file.txt"));

			// Upload file
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPlayerFileResponse,FLootLockerUploadFileDelegate>();

				FLootLockerFileUploadRequest Request;
				Request.file = "test-file.txt";
				Request.purpose = "test";
				ULootLockerSDKManager::UploadFile(Request, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("UploadFiles ok", Response.success);
				FileId = Response.id;
				FileName = Response.name;
				delete(Promise);
			}
			
			// List files
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerFileListResponse,FLootLockerFileListDelegate>();
			
				ULootLockerSDKManager::ListFiles(Delegate);
			
				const auto Response = Promise ->get_future().get();
				TestTrue("ListFiles ok", Response.success);
				delete(Promise);
			}
			
			// Get File
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPlayerFileResponse,FLootLockerUploadFileDelegate>();
									
				ULootLockerSDKManager::GetSingleFile(FileId, Delegate);
			
				const auto Response = Promise ->get_future().get();
				TestTrue("GetFile ok", Response.success);
				TestTrue("FileName Ok", FileName.Equals(Response.name));
				delete(Promise);
			}

			// Delete File
			{
				//const auto [Promise , Delegate] = test_util::CreateDelegate<void,FLootLockerFileDeletedDelegate>();
				std::promise<void>* Promise = new std::promise<void>();

				FLootLockerFileDeletedDelegate Delegate =
					FLootLockerFileDeletedDelegate::CreateLambda(
						[Promise](FLootLockerResponse){Promise->set_value();});
						
				ULootLockerSDKManager::DeletePlayerFile(FileId, Delegate);
			
				Promise->get_future().get();
				TestTrue("DeleteFile ok", true);
				delete(Promise);
			}

			std::remove("test-file.txt");

			test_util::EndSession();
			TestDone.Execute();			
		});
	});
}
#endif
