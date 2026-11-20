// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "JsonObjectWrapper.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "LootLockerSurveysRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================
/// @addtogroup Surveys
/// @{
/**
 * A single question in a survey. Answers are submitted through the player metadata API using the question's metadata_key.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSurveyQuestion
{
    GENERATED_BODY()
    /**
     * The unique identifier of the question
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The unique identifier of the survey this question belongs to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Survey_id = "";
    /**
     * The text shown to the player for this question
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Question_text = "";
    /**
     * The player metadata key that the answer to this question is stored under
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Metadata_key = "";
    /**
     * The type of field to render for this question (for example short_text, long_text, select)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Field_type = "";
    /**
     * Opaque JSON parameters for the field type, for example the available options for a select field.
     * Empty when the question has no parameters.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FJsonObjectWrapper Params;
    /**
     * Whether an answer to this question is required before the survey can be completed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Required = false;
    /**
     * The order in which this question should be presented, ascending
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Sort_order = 0;
    /**
     * When the question was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Created_at = FDateTime(0);
    /**
     * When true, answers for this question's metadata_key are masked in game metadata reads.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Sensitive = false;
};
/// @}

/// @addtogroup Surveys
/// @{
/**
 * A survey that a player can see and complete.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSurvey
{
    GENERATED_BODY()
    /**
     * The unique identifier of the survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The name of the survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * When the survey was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Created_at = FDateTime(0);
    /**
     * Whether the current player has already completed this survey.
     * Only populated by ListSurveys.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Completed = false;
    /**
     * When the current player completed this survey.
     * Default (FDateTime(0)) when the survey has not been completed.
     * Only populated by ListSurveys.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Completed_at = FDateTime(0);
    /**
     * The questions in this survey, ordered by sort_order
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerSurveyQuestion> Questions;
};
/// @}

//==================================================
// Request Definitions
//==================================================

/// @addtogroup Surveys
/// @{
/**
 * A single answer to a survey question, submitted through SubmitSurveyAnswers.
 *
 * The value is passed as a JSON literal string and parsed according to Type, because the
 * metadata API validates the declared type: a checkbox answer must be declared Bool and sent
 * as `true`/`false`, not as the string "true".
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSurveyAnswer
{
    GENERATED_BODY()
    /**
     * The metadata_key of the question this answers
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Metadata_key = "";
    /**
     * The answer value, as a JSON literal matching Type:
     * `"some text"` (with quotes) for String, `42` for Number, `true`/`false` for Bool,
     * and a JSON array such as `["a","b"]` for a multiselect (Json).
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Value = "";
    /**
     * The metadata type of the value. Must match the question's field_type:
     * short_text/long_text/date/select -> String, number -> Number, checkbox -> Bool,
     * multiselect -> Json.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerMetadataTypes Type = ELootLockerMetadataTypes::String;
};
/// @}

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the surveys the current player can see.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListSurveysResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The surveys visible to the current player, filtered by each survey's segments
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerSurvey> Surveys;
};

/**
 * Response containing a single survey and its questions.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGetSurveyResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The unique identifier of the survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The name of the survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * When the survey was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Created_at = FDateTime(0);
    /**
     * The questions in this survey, ordered by sort_order
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerSurveyQuestion> Questions;
};

/**
 * Response returned after recording a survey completion for the current player.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCompleteSurveyResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Whether the survey is now completed. A successful response always reports true;
     * failures (for example an unanswered required question) are returned as an error response instead.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Complete = false;
    /**
     * When the survey was completed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime Completed_at = FDateTime(0);
    /**
     * The unique identifier of the completed survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Survey_id = "";
};

//==================================================
// Delegate Definitions
//==================================================
/// @addtogroup Surveys
/// @{
/**
 * C++ response delegate for listing surveys
 */
DECLARE_DELEGATE_OneParam(FLootLockerListSurveysResponseDelegate, FLootLockerListSurveysResponse);
/**
 * C++ response delegate for getting a single survey
 */
DECLARE_DELEGATE_OneParam(FLootLockerGetSurveyResponseDelegate, FLootLockerGetSurveyResponse);
/**
 * C++ response delegate for completing a survey
 */
DECLARE_DELEGATE_OneParam(FLootLockerCompleteSurveyResponseDelegate, FLootLockerCompleteSurveyResponse);

//==================================================
// API Class Definition
//==================================================

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerSurveysRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerSurveysRequestHandler() {};

    static FString ListSurveys(const FLootLockerPlayerData& PlayerData, const FLootLockerListSurveysResponseDelegate& OnComplete);
    static FString GetSurvey(const FLootLockerPlayerData& PlayerData, const FString& SurveyId, const FLootLockerGetSurveyResponseDelegate& OnComplete);
    static FString CompleteSurvey(const FLootLockerPlayerData& PlayerData, const FString& SurveyId, const FLootLockerCompleteSurveyResponseDelegate& OnComplete);

    /**
     * Submit answers to a survey for the current player.
     *
     * Survey answers are stored as player metadata, so this writes each answer to the player's own metadata
     * under the question's metadata_key. Call CompleteSurvey afterwards to record the completion.
     */
    static FString SubmitSurveyAnswers(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerSurveyAnswer>& Answers, const FLootLockerSetMetadataResponseDelegate& OnComplete);
};
