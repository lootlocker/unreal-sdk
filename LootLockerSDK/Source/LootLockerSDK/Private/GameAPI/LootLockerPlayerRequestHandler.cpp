// Copyright (c) 2021 LootLocker


#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerPlayerRequestHandler::HttpClient = nullptr;

ULootLockerPlayerRequestHandler::ULootLockerPlayerRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequestBP, const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetCurrentPlayerInfoResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetInfoFromSession, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::ListPlayerInfo(TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequestBP, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest)
{
	if(PlayerIdsToLookUp.Num() == 0 && PlayerLegacyIdsToLookUp.Num() == 0 && PlayerPublicUidsToLookUp.Num() == 0)
	{
		FLootLockerListPlayerInfoResponse emptySuccess;
		emptySuccess.success = true;
		emptySuccess.StatusCode = 200;
		emptySuccess.FullTextFromServer = "{}";
		OnCompletedRequestBP.ExecuteIfBound(emptySuccess);
		OnCompletedRequest.ExecuteIfBound(emptySuccess);
		return;
	}

	FLootLockerListPlayerInfoRequest request 
	{
		PlayerIdsToLookUp,
		PlayerLegacyIdsToLookUp,
		PlayerPublicUidsToLookUp
    };
	
	LLAPI<FLootLockerListPlayerInfoResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::ListPlayerInfo, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetFullInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest, int32 StartIndex)
{
	TMultiMap<FString,FString> QueryParams;
	
	if (StartIndex != 0)
	{
		QueryParams.Add("after" , FString::FromInt(StartIndex));
	}

	QueryParams.Add("count","200");

	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { },QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetCurrencyBalance(const FPBalanceResponseBP& OnCompletedRequestBP, const FPBalanceResponse& OnCompletedRequest )
{
	LLAPI<FLootLockerBalanceResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCurrencyBalance, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerPlayerAssetNotificationResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::InitiateDLCMigration, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP, const FPDlcResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerDlcResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetDLCsMigrated, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePrivate, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePublic, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetPlayerName(FString Name, const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{

	if (ULootLockerCurrentPlatform::Get() == ELootLockerPlatform::Guest)
	{

		if (Name.Equals(ULootLockerStateData::GetPlayerIdentifier(), ESearchCase::IgnoreCase)) 
		{
			OnCompletedRequestBP.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to their Identifier", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT));
			return;
		} else if (Name.Equals("player", ESearchCase::IgnoreCase)) {
			OnCompletedRequestBP.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to 'Player'", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT));
			return;
		}


	}

	FLootLockerPlayerNameRequest Data;

	Data.name = Name;

	LLAPI<FLootLockerNameResponse>::CallAPI(HttpClient, Data, ULootLockerGameEndpoints::SetPlayerName, {  }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetPlayerName(const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerNameResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerName, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(FLootLockerMultiplePlayerNamesRequest Request, const FPMultiplePlayerNamesBP& OnCompletedRequestBP, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString,FString> QueryParams;

	for (const auto& player : Request.player_ids)
	{
		QueryParams.Add(player.platform, player.player_id);
	}
	LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  },QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(FLootLockerLookupMultiplePlayersDataRequest Request, const FPMultiplePlayerNamesBP& OnCompletedRequestBP, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	for (int i = 0; i < Request.player_ids.Num(); ++i) {
		FString Key = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerPlayerDataLookupIdType"), static_cast<int32_t>(Request.player_ids[i].IdType)).ToLower();
		Key.ReplaceCharInline(TEXT(' '), TEXT('_'));
		QueryParams.Add(Key, Request.player_ids[i].Id);
	}
	LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequestBP, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest)
{
	TMultiMap<FString,FString> QueryParams;

	for (const auto& player_id : Request.player_ids)
	{
		QueryParams.Add("player_id", player_id);
	}
    for (const auto& player_public_uid : Request.player_public_uids)
	{
		QueryParams.Add("player_public_uid", player_public_uid);
	}
	LLAPI<FLootLockerMultiplePlayersPlatformIdsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayer1stPlatformID, {  }, QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::DeletePlayer(const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayer, {}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

