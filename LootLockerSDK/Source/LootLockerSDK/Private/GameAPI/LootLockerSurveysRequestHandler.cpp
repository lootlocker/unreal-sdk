// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerSurveysRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerSurveysRequestHandler::ListSurveys(const FLootLockerPlayerData& PlayerData, const FLootLockerListSurveysResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerListSurveysResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListSurveysEndpoint, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerSurveysRequestHandler::GetSurvey(const FLootLockerPlayerData& PlayerData, const FString& SurveyId, const FLootLockerGetSurveyResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerGetSurveyResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetSurveyEndpoint, { SurveyId }, {}, PlayerData, OnComplete);
}

FString ULootLockerSurveysRequestHandler::CompleteSurvey(const FLootLockerPlayerData& PlayerData, const FString& SurveyId, const FLootLockerCompleteSurveyResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerCompleteSurveyResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::CompleteSurveyEndpoint, { SurveyId }, {}, PlayerData, OnComplete);
}

FString ULootLockerSurveysRequestHandler::SubmitSurveyAnswers(const FLootLockerPlayerData& PlayerData, const TMap<FString, FString>& AnswersByMetadataKey, const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
    TArray<FLootLockerSetMetadataAction> Actions;
    Actions.Reserve(AnswersByMetadataKey.Num());
    for (const TPair<FString, FString>& Answer : AnswersByMetadataKey)
    {
        FLootLockerSetMetadataAction Action;
        Action.Action = ELootLockerMetadataActions::Create_or_Update;
        Action.Entry = FLootLockerMetadataEntry::MakeStringEntry(Answer.Key, {}, {}, Answer.Value);
        Actions.Add(Action);
    }

    return ULootLockerMetadataRequestHandler::SetMetadata(PlayerData, ELootLockerMetadataSources::self, TEXT("self"), Actions, OnComplete);
}
