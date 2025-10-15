
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerFeedbackRequestHandler::ListFeedbackCategories(const FLootLockerPlayerData& PlayerData, const ELootLockerFeedbackType& Type, const FLootLockerListFeedbackCategoryResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerFeedbackCategoryResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListFeedbackCategories, { ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerFeedbackType"), static_cast<int32>(Type)).ToLower() }, {}, PlayerData, OnComplete);
}

void ULootLockerFeedbackRequestHandler::SendFeedback(const FLootLockerPlayerData& PlayerData, const FString& Ulid, const FString& Description, const FString& CategoryID, const ELootLockerFeedbackType& Type, const FLootLockerSendFeedbackResponseDelegate& OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(FLootLockerFeedbackRequest{ ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerFeedbackType"), static_cast<int32>(Type)).ToLower(), Ulid, CategoryID, Description }, ULootLockerGameEndpoints::SendFeedback, {}, {}, PlayerData, OnComplete);
}
