
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
	FString type = FeedbackTypeEnumToString(Type);

	LLAPI<FLootLockerFeedbackCategoryResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListFeedbackCategories, { type }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerFeedbackRequestHandler::SendFeedback(const FString& Ulid, const FString& Description, const FString& CategoryID, const ELootLockerFeedbackType& Type, const FLootLockerSendFeedbackResponseBP& OnCompleteBP, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerFeedbackRequest{ Ulid, Description, CategoryID, FeedbackTypeEnumToString(Type) }, ULootLockerGameEndpoints::SendFeedback, {}, {}, OnCompleteBP, OnComplete);
}


FString ULootLockerFeedbackRequestHandler::FeedbackTypeEnumToString(ELootLockerFeedbackType e)
{
	switch (e)
	{
	case ELootLockerFeedbackType::Player:
		return "player";
		break;
	case ELootLockerFeedbackType::Game:
		return "game";
		break;
	case ELootLockerFeedbackType::Ugc:
		return "ugc";
		break;
	default:
		return "";
		break;
	}
}
