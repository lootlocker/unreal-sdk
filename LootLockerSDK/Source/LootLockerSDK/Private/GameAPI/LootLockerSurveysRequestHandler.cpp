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

FString ULootLockerSurveysRequestHandler::SubmitSurveyAnswers(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerSurveyAnswer>& Answers, const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
    TArray<FLootLockerSetMetadataAction> Actions;
    Actions.Reserve(Answers.Num());
    for (const FLootLockerSurveyAnswer& Answer : Answers)
    {
        FLootLockerMetadataEntry Entry;
        switch (Answer.Type)
        {
        case ELootLockerMetadataTypes::Number:
        {
            // The metadata API validates the declared type, so a number has to be sent as a JSON
            // number rather than a string. Parse the caller's literal; 0 when it is not numeric.
            double Number = 0.0;
            LexTryParseString(Number, *Answer.Value);
            Entry = FLootLockerMetadataEntry::MakeFloatEntry(Answer.Metadata_key, {}, {}, static_cast<float>(Number));
            break;
        }
        case ELootLockerMetadataTypes::Bool:
        {
            const FString Trimmed = Answer.Value.TrimStartAndEnd();
            const bool bBool = Trimmed.Equals(TEXT("true"), ESearchCase::IgnoreCase) || Trimmed == TEXT("1");
            Entry = FLootLockerMetadataEntry::MakeBoolEntry(Answer.Metadata_key, {}, {}, bBool);
            break;
        }
        case ELootLockerMetadataTypes::Json:
            // Raw JSON, for example a multiselect array such as ["a","b"].
            // MakeJsonValueEntry ignores its Type argument and always declares Json.
            Entry = FLootLockerMetadataEntry::MakeJsonValueEntry(Answer.Metadata_key, {}, {},
                ELootLockerMetadataTypes::Json, LootLockerUtilities::JsonValueFromFString(Answer.Value));
            break;
        case ELootLockerMetadataTypes::Base64:
        case ELootLockerMetadataTypes::String:
        default:
            // Survey answers are text/number/bool/json; Base64 is folded into String for
            // completeness since a survey question cannot produce one.
            Entry = FLootLockerMetadataEntry::MakeStringEntry(Answer.Metadata_key, {}, {}, Answer.Value);
            break;
        }

        FLootLockerSetMetadataAction Action;
        Action.Action = ELootLockerMetadataActions::Create_or_Update;
        Action.Entry = Entry;
        Actions.Add(Action);
    }

    return ULootLockerMetadataRequestHandler::SetMetadata(PlayerData, ELootLockerMetadataSources::self, TEXT("self"), Actions, OnComplete);
}
