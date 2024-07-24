
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
	FLootLockerFeedbackRequest request = FLootLockerFeedbackRequest();
	request.entity_id = Ulid;
	request.description = Description;
	request.category_id = CategoryID;
	request.entity = FeedbackTypeEnumToString(Type);

	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::ListFeedbackCategories, { }, {}, OnCompleteBP, OnComplete);
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
