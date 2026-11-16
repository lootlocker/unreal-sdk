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
