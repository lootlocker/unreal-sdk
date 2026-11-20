// Copyright (c) 2021 LootLocker

#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerSurveysRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"
#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerSurveys, "LootLocker.Surveys",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerTestGame Game;
	FString SurveyId;
END_DEFINE_SPEC(FTestLootLockerSurveys)

void FTestLootLockerSurveys::Define()
{
	LatentBeforeEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		SurveyId.Empty();
		bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("Surveys"));
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.EnableGuestLogin();
		if (!bOk) { Done.Execute(); return; }
		bOk = Game.CreateSurvey(TEXT("CI Survey"), TEXT("ci_survey_answer"), SurveyId);
		if (!bOk) { Done.Execute(); return; }
		Game.InitializeLootLockerSDK();
		test_util::StartSession();
		Done.Execute();
	});

	LatentAfterEach(EAsyncExecution::ThreadPool, [this](const FDoneDelegate& Done)
	{
		Game.DeleteGame();
		Done.Execute();
	});

	Describe("Surveys", [this]()
	{
		LatentIt("ListSurveys_ReturnsStandaloneSurveyWithQuestions", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerListSurveysResponse, FLootLockerListSurveysResponseDelegate>();
			ULootLockerSDKManager::ListSurveys(Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("ListSurveys succeeded", Response.success);
			TestEqual("Exactly one survey is visible", Response.Surveys.Num(), 1);
			if (Response.Surveys.Num() == 1)
			{
				const FLootLockerSurvey& Survey = Response.Surveys[0];
				TestEqual("Survey id matches", Survey.Id, SurveyId);
				TestEqual("Survey name matches", Survey.Name, TEXT("CI Survey"));
				TestFalse("Survey is not completed yet", Survey.Completed);
				TestEqual("completed_at is unset when not completed", Survey.Completed_at, FDateTime(0));
				TestEqual("Exactly one question", Survey.Questions.Num(), 1);
				if (Survey.Questions.Num() == 1)
				{
					TestEqual("Question metadata key matches", Survey.Questions[0].Metadata_key, TEXT("ci_survey_answer"));
					TestTrue("Question is required", Survey.Questions[0].Required);
				}
			}

			TestDone.Execute();
		});

		LatentIt("GetSurvey_ReturnsSurveyWithQuestions", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerGetSurveyResponse, FLootLockerGetSurveyResponseDelegate>();
			ULootLockerSDKManager::GetSurvey(SurveyId, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("GetSurvey succeeded", Response.success);
			TestEqual("Survey id matches", Response.Id, SurveyId);
			TestEqual("Survey name matches", Response.Name, TEXT("CI Survey"));
			TestEqual("Exactly one question", Response.Questions.Num(), 1);
			if (Response.Questions.Num() == 1)
			{
				TestEqual("Question metadata key matches", Response.Questions[0].Metadata_key, TEXT("ci_survey_answer"));
			}

			TestDone.Execute();
		});

		LatentIt("CompleteSurvey_WithoutRequiredAnswer_Fails", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerCompleteSurveyResponse, FLootLockerCompleteSurveyResponseDelegate>();
			ULootLockerSDKManager::CompleteSurvey(SurveyId, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestFalse("Completing with an unanswered required question fails", Response.success);

			TestDone.Execute();
		});

		LatentIt("SubmitSurveyAnswers_ThenCompleteSurvey_SucceedsAndMarksCompleted", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			if (!Game.IsValid()) { AddError(TEXT("Game setup failed")); TestDone.Execute(); return; }

			// Submit the answer through the survey convenience method.
			FLootLockerSurveyAnswer Answer;
			Answer.Metadata_key = TEXT("ci_survey_answer");
			Answer.Value = TEXT("From a friend");
			Answer.Type = ELootLockerMetadataTypes::String;

			TArray<FLootLockerSurveyAnswer> Answers;
			Answers.Add(Answer);

			const auto [SubmitPromise, SubmitDelegate] = test_util::CreateDelegate<FLootLockerSetMetadataResponse, FLootLockerSetMetadataResponseDelegate>();
			ULootLockerSDKManager::SubmitSurveyAnswers(Answers, SubmitDelegate);
			const auto SubmitResponse = test_util::WaitAndGet(SubmitPromise, 30);
			TestTrue("SubmitSurveyAnswers succeeded", SubmitResponse.success);

			const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerCompleteSurveyResponse, FLootLockerCompleteSurveyResponseDelegate>();
			ULootLockerSDKManager::CompleteSurvey(SurveyId, Delegate);
			const auto Response = test_util::WaitAndGet(Promise, 30);
			TestTrue("CompleteSurvey succeeded", Response.success);
			TestTrue("Response reports the survey as complete", Response.Complete);
			TestEqual("Survey id matches", Response.Survey_id, SurveyId);
			TestTrue("completed_at is set", Response.Completed_at != FDateTime(0));

			const auto [ListPromise, ListDelegate] = test_util::CreateDelegate<FLootLockerListSurveysResponse, FLootLockerListSurveysResponseDelegate>();
			ULootLockerSDKManager::ListSurveys(ListDelegate);
			const auto ListResponse = test_util::WaitAndGet(ListPromise, 30);
			TestTrue("ListSurveys succeeded", ListResponse.success);
			TestEqual("Exactly one survey is visible", ListResponse.Surveys.Num(), 1);
			if (ListResponse.Surveys.Num() == 1)
			{
				TestTrue("Survey is marked completed", ListResponse.Surveys[0].Completed);
				TestTrue("completed_at is set on the listed survey", ListResponse.Surveys[0].Completed_at != FDateTime(0));
			}

			TestDone.Execute();
		});
	});
}
#endif
