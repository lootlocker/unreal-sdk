// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "LootLockerPlaytestsRequestHandler.generated.h"

//==================================================
// Request Definitions
//==================================================
/// @addtogroup Playtests
/// @{
/**
 * Request to acknowledge a playtest document. Send every statement id in the document.
 * Leave statement_ids empty for documents that have no statements.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAcknowledgePlaytestDocumentRequest
{
    GENERATED_BODY()
    /**
     * Every statement id in the document. Required when the document has statements.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> statement_ids;
};
/// @}

//==================================================
// Data Type Definitions
//==================================================
/// @addtogroup Playtests
/// @{
/**
 * A document the calling player has acknowledged in a playtest.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPlaytestAcknowledgedDocument
{
    GENERATED_BODY()
    /**
     * The ULID of the document.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString document_id = "";
    /**
     * The content hash of the document at the time it was acknowledged. A document whose
     * content changed must be acknowledged again before onboarding can be completed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString content_hash = "";
    /**
     * The statement ids that were acknowledged. Empty when the document has no statements.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> statement_ids;
    /**
     * When the document was acknowledged.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime acknowledged_at = FDateTime(0);
};

/**
 * An answer the calling player has stored for a playtest question.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPlaytestAnswer
{
    GENERATED_BODY()
    /**
     * The player metadata key the answer is stored under.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key = "";
    /**
     * The serialized metadata entry. A string answer arrives JSON-quoted, for example "\"yes\"".
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value = "";
};
/// @}

//==================================================
// Request Definitions
//==================================================

/**
 * A single answer to a playtest question, submitted through SubmitPlaytestAnswers.
 *
 * The metadata API validates the declared type against the value, so a checkbox answer must be
 * declared Bool, a number Number, and a multiselect Json — sending everything as String is
 * rejected. Use the From* helpers rather than filling the fields by hand: they format the value
 * with the metadata layer so it always matches Type.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPlaytestAnswerSubmission
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
     *
     * Prefer the From* helpers below, which format this for you.
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

    /** Build a String answer, for short_text, long_text, date and select questions. */
    static FLootLockerPlaytestAnswerSubmission FromText(const FString& MetadataKey, const FString& Value);

    /** Build a Number answer, for number questions. */
    static FLootLockerPlaytestAnswerSubmission FromNumber(const FString& MetadataKey, double Value);

    /** Build a Bool answer, for checkbox questions. */
    static FLootLockerPlaytestAnswerSubmission FromBool(const FString& MetadataKey, bool Value);

    /** Build a Json answer, for multiselect questions. */
    static FLootLockerPlaytestAnswerSubmission FromMultiSelect(const FString& MetadataKey, const TArray<FString>& SelectedValues);

    /** Build the metadata entry for this answer, using the metadata layer's typed factories. */
    FLootLockerMetadataEntry MakeEntry() const;
};
/// @}

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the calling player's onboarding progress for a playtest.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPlaytestOnboardingStatusResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Whether the player has completed onboarding for this playtest.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool completed = false;
    /**
     * When the player completed onboarding.
     * Default (FDateTime(0)) until the player completes it.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime completed_at = FDateTime(0);
    /**
     * The documents the player has acknowledged.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPlaytestAcknowledgedDocument> documents;
    /**
     * The answers the player has stored for this playtest's questions.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPlaytestAnswer> answers;
};

/**
 * Response returned after completing playtest onboarding for the calling player.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCompletePlaytestOnboardingResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Whether onboarding is now complete. A successful response always reports true;
     * failures (for example an unacknowledged required document) are returned as an error response instead.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool complete = false;
    /**
     * When onboarding was completed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime completed_at = FDateTime(0);
    /**
     * The ULID of the playtest that was completed.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString playtest_id = "";
};

/**
 * Response returned after acknowledging a playtest document.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAcknowledgePlaytestDocumentResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The ULID of the acknowledged document.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString document_id = "";
    /**
     * The content hash of the document that was acknowledged.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString content_hash = "";
};

//==================================================
// Delegate Definitions
//==================================================
/// @addtogroup Playtests
/// @{
/**
 * C++ response delegate for getting a playtest's onboarding status
 */
DECLARE_DELEGATE_OneParam(FLootLockerPlaytestOnboardingStatusResponseDelegate, FLootLockerPlaytestOnboardingStatusResponse);
/**
 * C++ response delegate for completing playtest onboarding
 */
DECLARE_DELEGATE_OneParam(FLootLockerCompletePlaytestOnboardingResponseDelegate, FLootLockerCompletePlaytestOnboardingResponse);
/**
 * C++ response delegate for acknowledging a playtest document
 */
DECLARE_DELEGATE_OneParam(FLootLockerAcknowledgePlaytestDocumentResponseDelegate, FLootLockerAcknowledgePlaytestDocumentResponse);

//==================================================
// API Class Definition
//==================================================

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerPlaytestsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerPlaytestsRequestHandler() {};

    static FString GetOnboardingStatus(const FLootLockerPlayerData& PlayerData, const FString& Subdomain, const FLootLockerPlaytestOnboardingStatusResponseDelegate& OnComplete);
    static FString CompleteOnboarding(const FLootLockerPlayerData& PlayerData, const FString& Subdomain, const FLootLockerCompletePlaytestOnboardingResponseDelegate& OnComplete);
    static FString AcknowledgeDocument(const FLootLockerPlayerData& PlayerData, const FString& Subdomain, const FString& DocumentId, const FLootLockerAcknowledgePlaytestDocumentRequest& Request, const FLootLockerAcknowledgePlaytestDocumentResponseDelegate& OnComplete);

    /**
     * Submit answers to a playtest for the current player.
     *
     * Playtest answers are stored as player metadata, so this writes each answer to the player's own metadata
     * under the question's metadata_key. Call CompleteOnboarding afterwards to record the completion.
     */
    static FString SubmitAnswers(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerPlaytestAnswerSubmission>& Answers, const FLootLockerSetMetadataResponseDelegate& OnComplete);
};
