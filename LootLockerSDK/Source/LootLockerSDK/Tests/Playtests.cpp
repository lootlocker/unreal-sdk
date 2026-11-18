// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerPlaytestsRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerPlaytests, "LootLocker.Playtests",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString PlaytestId;
	FString PlaytestSubdomain;
END_DEFINE_SPEC(FTestLootLockerPlaytests)

void FTestLootLockerPlaytests::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		PlaytestId.Empty();
		// Subdomains are globally unique, so derive one per run.
		PlaytestSubdomain = FString::Printf(TEXT("ci-playtest-%s"), *FGuid::NewGuid().ToString(EGuidFormats::Short).ToLower());

		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Playtests"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.CreatePlaytest(TEXT("CI Playtest"), PlaytestSubdomain, PlaytestId);
		if (!bOk) { Done.Execute(); return; }

		Game.InitializeLootLockerSDK();
		test_util::StartSession();
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		PlaytestId.Empty();
		PlaytestSubdomain.Empty();
		Done.Execute();
	});

	Describe("Playtests", [this]()
	{
		LatentIt("GetOnboardingStatus_ReturnsNotCompletedForNewPlayer", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPlaytestOnboardingStatusResponse, FLootLockerPlaytestOnboardingStatusResponseDelegate>();
			ULootLockerSDKManager::GetPlaytestOnboardingStatus(PlaytestSubdomain, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("GetPlaytestOnboardingStatus succeeded", Response.success);
			TestFalse("Onboarding is not completed yet", Response.completed);
			TestEqual("completed_at is unset when not completed", Response.completed_at, FDateTime(0));
			TestEqual("No acknowledged documents", Response.documents.Num(), 0);
			TestEqual("No stored answers", Response.answers.Num(), 0);

			TestDone.Execute();
		});

		LatentIt("CompleteOnboardingWithoutRequiredDocument_Fails", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			FString DocumentId;
			if (!Game.CreatePlaytestDocument(PlaytestId, TEXT("CI Document"), TEXT("Some terms"), true, {}, DocumentId))
			{
				AddError(TEXT("Failed to create playtest document"));
				TestDone.Execute();
				return;
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerCompletePlaytestOnboardingResponse, FLootLockerCompletePlaytestOnboardingResponseDelegate>();
			ULootLockerSDKManager::CompletePlaytestOnboarding(PlaytestSubdomain, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestFalse("Completion fails while a required document is unacknowledged", Response.success);

			TestDone.Execute();
		});

		LatentIt("CompleteOnboardingAfterAcknowledgingRequiredDocument_Succeeds", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			FString DocumentId;
			if (!Game.CreatePlaytestDocument(PlaytestId, TEXT("CI Document"), TEXT("Some terms"), true, {}, DocumentId))
			{
				AddError(TEXT("Failed to create playtest document"));
				TestDone.Execute();
				return;
			}

			{
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAcknowledgePlaytestDocumentResponse, FLootLockerAcknowledgePlaytestDocumentResponseDelegate>();
				ULootLockerSDKManager::AcknowledgePlaytestDocument(PlaytestSubdomain, DocumentId, FLootLockerAcknowledgePlaytestDocumentRequest(), Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("AcknowledgePlaytestDocument succeeded", Response.success);
				TestEqual("Acknowledged document id matches", Response.document_id, DocumentId);
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerCompletePlaytestOnboardingResponse, FLootLockerCompletePlaytestOnboardingResponseDelegate>();
			ULootLockerSDKManager::CompletePlaytestOnboarding(PlaytestSubdomain, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("CompletePlaytestOnboarding succeeded", Response.success);
			TestTrue("Onboarding is complete", Response.complete);
			TestNotEqual("completed_at is set", Response.completed_at, FDateTime(0));
			TestEqual("Completed playtest id matches", Response.playtest_id, PlaytestId);

			TestDone.Execute();
		});

		LatentIt("AcknowledgeDocumentWithStatements_IsReportedInStatus", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const FString StatementId = FGuid::NewGuid().ToString();
			FString DocumentId;
			if (!Game.CreatePlaytestDocument(PlaytestId, TEXT("CI Document"), TEXT("Some terms"), false, { StatementId }, DocumentId))
			{
				AddError(TEXT("Failed to create playtest document"));
				TestDone.Execute();
				return;
			}

			{
				FLootLockerAcknowledgePlaytestDocumentRequest Request;
				Request.statement_ids.Add(StatementId);
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAcknowledgePlaytestDocumentResponse, FLootLockerAcknowledgePlaytestDocumentResponseDelegate>();
				ULootLockerSDKManager::AcknowledgePlaytestDocument(PlaytestSubdomain, DocumentId, Request, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("AcknowledgePlaytestDocument succeeded", Response.success);
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPlaytestOnboardingStatusResponse, FLootLockerPlaytestOnboardingStatusResponseDelegate>();
			ULootLockerSDKManager::GetPlaytestOnboardingStatus(PlaytestSubdomain, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("GetPlaytestOnboardingStatus succeeded", Response.success);
			TestEqual("One acknowledged document", Response.documents.Num(), 1);
			if (Response.documents.Num() == 1)
			{
				TestEqual("Acknowledged document id matches", Response.documents[0].document_id, DocumentId);
				TestEqual("One acknowledged statement", Response.documents[0].statement_ids.Num(), 1);
				if (Response.documents[0].statement_ids.Num() == 1)
				{
					TestEqual("Acknowledged statement id matches", Response.documents[0].statement_ids[0], StatementId);
				}
			}

			TestDone.Execute();
		});

		LatentIt("SubmitAnswersThenCompleteOnboarding_Succeeds", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// The required question comes from a linked survey.
			if (!Game.CreateAndLinkPlaytestSurvey(PlaytestId, TEXT("CI Playtest Survey"), TEXT("ci_playtest_answer")))
			{
				AddError(TEXT("Failed to create and link the playtest survey"));
				TestDone.Execute();
				return;
			}

			{
				TMap<FString, FString> Answers;
				Answers.Add(TEXT("ci_playtest_answer"), TEXT("From a friend"));
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
				ULootLockerSDKManager::SubmitPlaytestAnswers(Answers, Delegate);
				const auto Response = test_util::WaitAndGet(Promise, 30);
				TestTrue("SubmitPlaytestAnswers succeeded", Response.success);
			}

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerCompletePlaytestOnboardingResponse, FLootLockerCompletePlaytestOnboardingResponseDelegate>();
			ULootLockerSDKManager::CompletePlaytestOnboarding(PlaytestSubdomain, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("Completion succeeds once the required answer is stored", Response.success);
			TestTrue("Onboarding is complete", Response.complete);

			TestDone.Execute();
		});

		LatentIt("GetOnboardingStatusForUnknownSubdomain_Fails", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerPlaytestOnboardingStatusResponse, FLootLockerPlaytestOnboardingStatusResponseDelegate>();
			ULootLockerSDKManager::GetPlaytestOnboardingStatus(TEXT("this-playtest-does-not-exist"), Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestFalse("Unknown subdomain fails", Response.success);

			TestDone.Execute();
		});
	});
}
#endif
