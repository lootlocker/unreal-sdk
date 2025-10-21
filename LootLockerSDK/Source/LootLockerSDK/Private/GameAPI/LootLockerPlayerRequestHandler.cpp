// Copyright (c) 2021 LootLocker


#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerLogger.h"
#include "LootLockerPlatformManager.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(const FLootLockerPlayerData& PlayerData, const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerGetCurrentPlayerInfoResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetInfoFromSession, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::ListPlayerInfo(const FLootLockerPlayerData& PlayerData, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest)
{
	if (PlayerIdsToLookUp.Num() == 0 && PlayerLegacyIdsToLookUp.Num() == 0 && PlayerPublicUidsToLookUp.Num() == 0)
	{
		FLootLockerListPlayerInfoResponse emptySuccess;
		emptySuccess.success = true;
		emptySuccess.StatusCode = 200;
		emptySuccess.FullTextFromServer = "{}";
		emptySuccess.Context.PlayerUlid = PlayerData.PlayerUlid;
		OnCompletedRequest.ExecuteIfBound(emptySuccess);
		return "";
	}

	FLootLockerListPlayerInfoRequest request
	{
		PlayerIdsToLookUp,
		PlayerLegacyIdsToLookUp,
		PlayerPublicUidsToLookUp
	};

	return LLAPI<FLootLockerListPlayerInfoResponse>::CallAPI(request, ULootLockerGameEndpoints::ListPlayerInfo, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetInventory(const FLootLockerPlayerData& PlayerData, const FInventoryResponse& OnCompletedRequest)
{
	return GetFullInventory(PlayerData, OnCompletedRequest, 0);
}

FString ULootLockerPlayerRequestHandler::GetFullInventory(const FLootLockerPlayerData& PlayerData, const FInventoryResponse& OnCompletedRequest, int32 StartIndex)
{
	TMultiMap<FString, FString> QueryParams;

	if (StartIndex != 0)
	{
		QueryParams.Add("after", FString::FromInt(StartIndex));
	}

	QueryParams.Add("count", "200");

	return LLAPI<FLootLockerInventoryResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetCurrencyBalance(const FLootLockerPlayerData& PlayerData, const FPBalanceResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerBalanceResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCurrencyBalance, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(const FLootLockerPlayerData& PlayerData, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerPlayerAssetNotificationResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::InitiateDLCMigration(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::InitiateDLCMigration, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetDLCsMigration(const FLootLockerPlayerData& PlayerData, const FPDlcResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerDlcResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetDLCsMigrated, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::SetProfilePrivate(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePrivate, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::SetProfilePublic(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePublic, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::SetPlayerName(const FLootLockerPlayerData& PlayerData, FString Name, const FPNameResponse& OnCompletedRequest)
{

	if (PlayerData.CurrentPlatform.Platform == ELootLockerPlatform::Guest)
	{
		if (Name.Equals(PlayerData.PlayerIdentifier, ESearchCase::IgnoreCase))
		{
			FLootLockerNameResponse Error = LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to their Identifier", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        	FLootLockerLogger::LogHttpRequest(Error, "No Headers");
			OnCompletedRequest.ExecuteIfBound(Error);
			return "";
		}
		else if (Name.Equals("player", ESearchCase::IgnoreCase)) {
			FLootLockerNameResponse Error = LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to 'Player'", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        	FLootLockerLogger::LogHttpRequest(Error, "No Headers");
			OnCompletedRequest.ExecuteIfBound(Error);
			return "";
		}
	}

	FLootLockerPlayerNameRequest Data;

	Data.name = Name;

	return LLAPI<FLootLockerNameResponse>::CallAPI(Data, ULootLockerGameEndpoints::SetPlayerName, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetPlayerName(const FLootLockerPlayerData& PlayerData, const FPNameResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerNameResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerName, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerMultiplePlayerNamesRequest Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;

	for (const auto& player : Request.player_ids)
	{
		QueryParams.Add(player.platform, player.player_id);
	}
	return LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerLookupMultiplePlayersDataRequest Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	for (int i = 0; i < Request.player_ids.Num(); ++i) {
		FString Key = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerPlayerDataLookupIdType"), static_cast<int32_t>(Request.player_ids[i].IdType)).ToLower();
		Key.ReplaceCharInline(TEXT(' '), TEXT('_'));
		QueryParams.Add(Key, Request.player_ids[i].Id);
	}
	return LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerPlayerData& PlayerData, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest)
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
	return LLAPI<FLootLockerMultiplePlayersPlatformIdsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayer1stPlatformID, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::DeletePlayer(const FLootLockerPlayerData& PlayerData, const FLootLockerDefaultDelegate OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayer, {}, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

