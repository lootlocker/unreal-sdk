
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerFeedbackRequestHandler::ListFeedbackCategories(const FLootLockerPlayerData& PlayerData, const ELootLockerFeedbackType& Type, const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerFeedbackCategoryResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListFeedbackCategories, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerFeedbackType"), static_cast<int32>(Type)).ToLower() }, {}, PlayerData, OnComplete);
}

FString ULootLockerFeedbackRequestHandler::SendFeedback(const FLootLockerPlayerData& PlayerData, const FString& Ulid, const FString& Description, const FString& CategoryID, const ELootLockerFeedbackType& Type, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
	return LLAPI<FLootLockerResponse>::CallAPI(FLootLockerFeedbackRequest{ ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerFeedbackType"), static_cast<int32>(Type)).ToLower(), Ulid, CategoryID, Description }, ULootLockerGameEndpoints::SendFeedback, {}, {}, PlayerData, OnComplete);
}
