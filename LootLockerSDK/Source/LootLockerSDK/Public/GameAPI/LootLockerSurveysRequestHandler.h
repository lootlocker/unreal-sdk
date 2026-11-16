// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "JsonObjectWrapper.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
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
    FString Created_at = "";
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
     * The legacy id of the game this survey belongs to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int64 Game_id = 0;
    /**
     * The name of the survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * Whether this survey is standalone (listed and completable through the Game API).
     * Non-standalone surveys are playtest-only and never returned by these endpoints.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Standalone = false;
    /**
     * When the survey was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
     * Whether the current player has already completed this survey.
     * Only populated by ListSurveys.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Completed = false;
    /**
     * When the current player completed this survey, as an RFC 3339 timestamp.
     * Empty when the survey has not been completed. Only populated by ListSurveys.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Completed_at = "";
    /**
     * The questions in this survey, ordered by sort_order
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerSurveyQuestion> Questions;
};
/// @}

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the standalone surveys the current player can see.
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
     * The legacy id of the game this survey belongs to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int64 Game_id = 0;
    /**
     * The name of the survey
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * Whether this survey is standalone (listed and completable through the Game API)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Standalone = false;
    /**
     * When the survey was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
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
     * Whether the survey is now completed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Complete = false;
    /**
     * When the survey was completed, as an RFC 3339 timestamp
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Completed_at = "";
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
};
