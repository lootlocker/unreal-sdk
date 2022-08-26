#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FLootLockerTestUserGeneratedContent, "LootLocker.UGC",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerAuthenticationResponse AuthenticationResponse;
END_DEFINE_SPEC(FLootLockerTestUserGeneratedContent)

void FLootLockerTestUserGeneratedContent::Define()
{
	Describe("UserGeneratedContent", [this]()
	{
		LatentIt("When using UGC", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			int createdAssetId = -1;
			
			// create asset
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerCreateAssetCandidateResponse,FCreateAssetCandidateResponseDelegate>();

				FLootLockerContentKeyValuePair filter;
				filter.key = "filter_key";
				filter.value = "filter_value";

				FLootLockerContentKeyValuePair kv;
				kv.key = "kv_key";
				kv.value = "kv_value";

				FLootLockerAssetDataEntity de;
				de.name = "de_key";
				de.data = "de_value";
				
				FLootLockerCreateAssetCandidateData AssetCandidateData;
				AssetCandidateData.data.name = "TestAssets314";
				AssetCandidateData.data.context_id = 1000;
				AssetCandidateData.data.filters.Add(filter);
				AssetCandidateData.data.kv_storage.Add(kv);
				AssetCandidateData.data.data_entities.Add(de);
	
				ULootLockerSDKManager::CreateAssetCandidate(AssetCandidateData, Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("Create asset", Response.success);
				createdAssetId = Response.asset_candidate.Id;

				delete(Promise);
			}
			
			// update asset
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetCandidateResponse,FAssetCandidateResponseDelegate>();

				FLootLockerContentKeyValuePair filter;
				filter.key = "filter_key";
				filter.value = "filter_value_rev";
				FLootLockerContentKeyValuePair kv;
				kv.key = "kv_key";
				kv.value = "kv_value_rev";

				FLootLockerAssetDataEntity de;
				de.name = "de_key";
				de.data = "de_value_rev";
			
				FLootLockerUpdateAssetCandidateData AssetCandidateData;
				AssetCandidateData.data.name = "TestAssets314";
				AssetCandidateData.data.context_id = 1000;
				AssetCandidateData.data.filters.Add(filter);
				AssetCandidateData.data.kv_storage.Add(kv);
				AssetCandidateData.data.data_entities.Add(de);
				
				ULootLockerSDKManager::UpdateAssetCandidate(createdAssetId, AssetCandidateData, Delegate);
			
				const auto Response = Promise ->get_future().get();
				TestTrue("update ugc asset ok", Response.success);
				delete(Promise);
			}
			
			// list all assets
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAssetCandidatesResponse,FAssetCandidatesResponseDelegate>();
									
				ULootLockerSDKManager::GetAllAssetCandidates(Delegate);
			
				const auto Response = Promise ->get_future().get();
				TestTrue("GetFile ok", Response.success);
				//TODO: add som test to check results
				
				delete(Promise);
			}

			// get single asset
			{
				//const auto [Promise , Delegate] = test_util::CreateDelegate<void,FLootLockerFileDeletedDelegate>();
				std::promise<void>* Promise = new std::promise<void>();

				FLootLockerFileDeletedDelegate Delegate = FLootLockerFileDeletedDelegate::CreateLambda([Promise](FLootLockerResponse){Promise->set_value();});
									
				ULootLockerSDKManager::DeletePlayerFile(createdAssetId, Delegate);
						
				Promise->get_future().get();
				TestTrue("DeleteFile ok", true);
				delete(Promise);
			}


			int FileId=1;
			FString FileName;

			FFileHelper::SaveStringToFile(TEXT("TestDataAbc123"), TEXT("test-file.txt"));
			// add files to asset
			{
				//const auto [Promise , Delegate] = test_util::CreateDelegate<void,FLootLockerFileDeletedDelegate>();
				std::promise<void>* Promise = new std::promise<void>();

				auto Delegate = FResponseCallback::CreateLambda([Promise](FLootLockerResponse){Promise->set_value();});

				ELootLockerAssetFilePurpose FilePurpose;
				FilePurpose = ELootLockerAssetFilePurpose::FILE;
				
				ULootLockerSDKManager::AddFileToAssetCandidate(createdAssetId, "test-file.txt", FilePurpose, Delegate);
						
				Promise->get_future().get();
				TestTrue("DeleteFile ok", true);

				delete(Promise);
			}

			// remove file from asset
			

			{
				//const auto [Promise , Delegate] = test_util::CreateDelegate<void,FLootLockerFileDeletedDelegate>();
				std::promise<void>* Promise = new std::promise<void>();

				FLootLockerFileDeletedDelegate Delegate = FResponseCallback::CreateLambda([Promise](FLootLockerResponse){Promise->set_value();});
				
				ULootLockerSDKManager::DeleteFileFromAssetCandidate(createdAssetId,FileId,Delegate);
			
				Promise->get_future().get();
				TestTrue("DeleteFile ok", true);
				delete(Promise);
			}
			
			// delete single asset
			{
				std::promise<void>* Promise = new std::promise<void>();

				auto Delegate = FLootLockerFileDeletedDelegate::CreateLambda([Promise](FLootLockerResponse){Promise->set_value();});
				
				ULootLockerSDKManager::DeleteFileFromAssetCandidate(createdAssetId,FileId,Delegate);
			
				Promise->get_future().get();
				TestTrue("Delete asset succeded", true);
				delete(Promise);
			}
			
			test_util::EndSession();
			TestDone.Execute();			
		});
	});
}
#endif
