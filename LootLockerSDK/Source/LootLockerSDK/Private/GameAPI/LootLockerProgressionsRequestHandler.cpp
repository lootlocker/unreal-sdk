// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerProgressionsRequestHandler::HttpClient = nullptr;

ULootLockerProgressionsRequestHandler::ULootLockerProgressionsRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerProgressionsRequestHandler::GetPlayerProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedPlayerProgressionsResponseBP()*/, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedPlayerProgressionsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionResponseBP()*/, const FLootLockerPlayerProgressionResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionWithRewardsResponseBP()*/, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionWithRewardsResponseBP()*/, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionWithRewardsResponseBP()*/, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP /*= FLootLockerDeleteProgressionBP()*/, const FLootLockerDeleteProgressionDelegate& OnComplete /*= FLootLockerDeleteProgressionDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedCharacterProgressionsResponseBP()*/, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedCharacterProgressionsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionResponseBP()*/, const FLootLockerCharacterProgressionResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionWithRewardsResponseBP()*/, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionWithRewardsResponseBP()*/, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionWithRewardsResponseBP()*/, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP /*= FLootLockerDeleteProgressionBP()*/, const FLootLockerDeleteProgressionDelegate& OnComplete /*= FLootLockerDeleteProgressionDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::GetProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedProgressionsResponseBP()*/, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedProgressionsResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequestBP /*= FLootLockerProgressionResponseBP()*/, const FLootLockerProgressionResponseDelegate& OnComplete /*= FLootLockerProgressionResponseDelegate()*/) 
{

}

void ULootLockerProgressionsRequestHandler::GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const int32& After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedProgressionTiersResponseBP()*/, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete /*= FLootLockerPaginatedProgressionTiersResponseDelegate()*/) 
{

}
