
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerFeedbackRequestHandler::HttpClient = nullptr;

ULootLockerFeedbackRequestHandler::ULootLockerFeedbackRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerFeedbackRequestHandler::ListFeedbackCategories(const ELootLockerFeedbackType& Type, const FLootLockerListFeedbackCategoryResponseBP& OnCompleteBP, const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerFeedbackCategoryResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListFeedbackCategories, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerFeedbackType"), static_cast<int32>(Type)).ToLower() }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerFeedbackRequestHandler::SendFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const ELootLockerFeedbackType& Type, const FLootLockerSendFeedbackResponseBP& OnCompleteBP, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerFeedbackRequest{ Ulid, Description, CategoryID, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerFeedbackType"), static_cast<int32>(Type)).ToLower() }, ULootLockerGameEndpoints::SendFeedback, {}, {}, OnCompleteBP, OnComplete);
}
