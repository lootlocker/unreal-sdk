// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerFeedbackRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/*
 * An enum with the supported Feedback types that are available for Feedback
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerFeedbackType : uint8
{
    Player = 0,
    Game = 1,
    Ugc = 2,
};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFeedbackCategory
{
    GENERATED_BODY()
    /*
    * The unique identifier of a feedback category
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id;
    /*
    * The type of a feedback category (Player, Game, UGC)
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerFeedbackType entity = ELootLockerFeedbackType::Game;
    /*
    * The name of a feedback category
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    /*
    * The description of a feedback category
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString description;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFeedbackCategoryResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /*
    * A list of categories made for the game
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFeedbackCategory> categories;
};

//==================================================
// Request Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerFeedbackRequest 
{
    GENERATED_BODY()
    /*
    * A string representation of the type of feedback, use ELootLockerFeedbackType
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entity;
    
    /*
    * The Ulid of what you're sending feedback about
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString entity_id;

    /*
    * The category id of what kind of feedback you're sending, use ListFeedbackCategories for all the ids
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString category_id;

    /*
    * The description of feedback you're sending, this will be the reason
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString description;


};

//==================================================
// Blueprint Delegate Definitions
//==================================================

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListFeedbackCategoryResponseBP, FLootLockerFeedbackCategoryResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerSendFeedbackResponseBP, FLootLockerResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

DECLARE_DELEGATE_OneParam(FLootLockerListFeedbackCategoryResponseDelegate, FLootLockerFeedbackCategoryResponse);
DECLARE_DELEGATE_OneParam(FLootLockerSendFeedbackResponseDelegate, FLootLockerResponse)

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerFeedbackRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerFeedbackRequestHandler();
    static void ListFeedbackCategories(const ELootLockerFeedbackType& Type, const FLootLockerListFeedbackCategoryResponseBP& OnCompletedRequestBP = FLootLockerListFeedbackCategoryResponseBP(), const FLootLockerListFeedbackCategoryResponseDelegate& OnCompletedRequest = FLootLockerListFeedbackCategoryResponseDelegate());
    static void SendFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const ELootLockerFeedbackType& Type, const FLootLockerSendFeedbackResponseBP& OnCompletedRequestBP = FLootLockerSendFeedbackResponseBP(), const FLootLockerSendFeedbackResponseDelegate& OnCompletedRequest = FLootLockerSendFeedbackResponseDelegate());
private:
    static ULootLockerHttpClient* HttpClient;
};