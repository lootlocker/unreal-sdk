#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "ServerAPI/LootLockerServerPlayerFileRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerServer_PlayerFiles, "LootLockerServer", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerServer_PlayerFiles)

void FTestLootLockerServer_PlayerFiles::Define()
{
	Describe("Server_PlayerFiles", [this]()
	{
		LatentIt("When Server PlayerFiles", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartServerSession();

			FString PlayerId;
			// client login is needed for client calls below!
			test_util::StartGuestSession(PlayerId);

			int FileId = 0;
			const FString FileName = "test-file.txt";

			// Upload file
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerPlayerFileResponse, FLootLockerServerUploadPlayerFileResponseDelegate>();

				FString Purpose = "test";
				ULootLockerSDKManager::Server_UploadPlayerFile(PlayerId, FileName, "TestDataAbc123", Purpose, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Server_UploadPlayerFile Ok", Response.success);
				TestTrue("Server_UploadPlayerFile FileName Ok", FileName.Equals(Response.Name));

				FileId = Response.Id;

				delete(Promise);
			}

			// List files
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerListPlayerFilesResponse, FLootLockerServerListPlayerFilesResponseDelegate>();

				ULootLockerSDKManager::Server_ListPlayerFiles(PlayerId, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("ListFiles ok", Response.success);
				TestTrue("ListFiles ok", Response.Items.Num() > 0);
				delete(Promise);
			}

			// Get File
			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPlayerFileResponse, FLootLockerUploadFileDelegate>();

				ULootLockerSDKManager::GetSingleFile(FileId, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("GetFile ok", Response.success);
				TestTrue("FileName Ok", FileName.Equals(Response.name));
				delete(Promise);
			}

			// Delete File
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse, FLootLockerServerDeletePlayerFileResponseDelegate>();

				ULootLockerSDKManager::DeletePlayerFile(FileId, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("DeleteFile ok", Response.success);
				delete(Promise);
			}

			test_util::EndSession();
			test_util::EndServerSession();

			TestDone.Execute();
		});
	});
}
#endif

