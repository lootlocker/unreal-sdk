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

void ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(const FLootLockerPlayerData& PlayerData, const FLootLockerGetCurrentPlayerInfoResponseBP& OnCompletedRequestBP, const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest)
{
	LLAPI<FLootLockerGetCurrentPlayerInfoResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetInfoFromSession, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::ListPlayerInfo(const FLootLockerPlayerData& PlayerData, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseBP& OnCompletedRequestBP, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest)
{
	if (PlayerIdsToLookUp.Num() == 0 && PlayerLegacyIdsToLookUp.Num() == 0 && PlayerPublicUidsToLookUp.Num() == 0)
	{
		FLootLockerListPlayerInfoResponse emptySuccess;
		emptySuccess.success = true;
		emptySuccess.StatusCode = 200;
		emptySuccess.FullTextFromServer = "{}";
		emptySuccess.Context.PlayerUlid = PlayerData.PlayerUlid;
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

	LLAPI<FLootLockerListPlayerInfoResponse>::CallAPI(HttpClient, request, ULootLockerGameEndpoints::ListPlayerInfo, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetInventory(const FLootLockerPlayerData& PlayerData, const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetFullInventory(const FLootLockerPlayerData& PlayerData, const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest, int32 StartIndex)
{
	TMultiMap<FString, FString> QueryParams;

	if (StartIndex != 0)
	{
		QueryParams.Add("after", FString::FromInt(StartIndex));
	}

	QueryParams.Add("count", "200");

	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetCurrencyBalance(const FLootLockerPlayerData& PlayerData, const FPBalanceResponseBP& OnCompletedRequestBP, const FPBalanceResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerBalanceResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCurrencyBalance, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(const FLootLockerPlayerData& PlayerData, const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerPlayerAssetNotificationResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::InitiateDLCMigration(const FLootLockerPlayerData& PlayerData, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::InitiateDLCMigration, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetDLCsMigration(const FLootLockerPlayerData& PlayerData, const FPDlcResponseBP& OnCompletedRequestBP, const FPDlcResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerDlcResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetDLCsMigrated, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetProfilePrivate(const FLootLockerPlayerData& PlayerData, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePrivate, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetProfilePublic(const FLootLockerPlayerData& PlayerData, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePublic, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetPlayerName(const FLootLockerPlayerData& PlayerData, FString Name, const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{

	if (PlayerData.CurrentPlatform.Platform == ELootLockerPlatform::Guest)
	{
		if (Name.Equals(PlayerData.PlayerIdentifier, ESearchCase::IgnoreCase))
		{
			OnCompletedRequestBP.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to their Identifier", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid));
			return;
		}
		else if (Name.Equals("player", ESearchCase::IgnoreCase)) {
			OnCompletedRequestBP.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to 'Player'", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid));
			return;
		}
	}

	FLootLockerPlayerNameRequest Data;

	Data.name = Name;

	LLAPI<FLootLockerNameResponse>::CallAPI(HttpClient, Data, ULootLockerGameEndpoints::SetPlayerName, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetPlayerName(const FLootLockerPlayerData& PlayerData, const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerNameResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerName, {  }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerMultiplePlayerNamesRequest Request, const FPMultiplePlayerNamesBP& OnCompletedRequestBP, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;

	for (const auto& player : Request.player_ids)
	{
		QueryParams.Add(player.platform, player.player_id);
	}
	LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerLookupMultiplePlayersDataRequest Request, const FPMultiplePlayerNamesBP& OnCompletedRequestBP, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	for (int i = 0; i < Request.player_ids.Num(); ++i) {
		FString Key = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerPlayerDataLookupIdType"), static_cast<int32_t>(Request.player_ids[i].IdType)).ToLower();
		Key.ReplaceCharInline(TEXT(' '), TEXT('_'));
		QueryParams.Add(Key, Request.player_ids[i].Id);
	}
	LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerPlayerData& PlayerData, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequestBP, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;

	for (const auto& player_id : Request.player_ids)
	{
		QueryParams.Add("player_id", player_id);
	}
	for (const auto& player_public_uid : Request.player_public_uids)
	{
		QueryParams.Add("player_public_uid", player_public_uid);
	}
	LLAPI<FLootLockerMultiplePlayersPlatformIdsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayer1stPlatformID, {  }, QueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::DeletePlayer(const FLootLockerPlayerData& PlayerData, const FLootLockerDefaultResponseBP& OnCompletedRequestBP, const FLootLockerDefaultDelegate OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayer, {}, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

