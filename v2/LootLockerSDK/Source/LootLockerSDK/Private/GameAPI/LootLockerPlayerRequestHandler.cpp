// Copyright (c) 2021 LootLocker


#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerPlayerRequestHandler::HttpClient = nullptr;

ULootLockerPlayerRequestHandler::ULootLockerPlayerRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerPlayerRequestHandler::GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerPlayerInfoResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInfoEndPoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetFullInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest, int32 StartIndex)
{
	TMap<FString,FString> QueryParams;
	
	if (StartIndex != 0)
	{
		QueryParams.Add("after" , FString::FromInt(StartIndex));
	}

	QueryParams.Add("count","200");

	LLAPI<FLootLockerInventoryResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { },QueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetCurrencyBalance(const FPBalanceResponseBP& OnCompletedRequestBP, const FPBalanceResponse& OnCompletedRequest )
{
	LLAPI<FLootLockerBalanceResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCurrencyBalance, { },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SubmitXp(int Points,const FPSubmitResponseBP& OnCompletedRequestBP, const FSubmitXpResponse& OnCompletedRequest)
{
	FLootLockerSubmitXpRequest AuthRequest;
	AuthRequest.points = Points;
	
	LLAPI<FLootLockerSubmitXpResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::SubmitXpEndpoint, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetOtherPlayerInfo(FString OtherPlayerId,const FPInfoResponseBP OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	const auto* Config = GetDefault<ULootLockerConfig>();
	const FString Platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(Config->Platform));
	TMap<FString, FString> QueryParams;
	QueryParams.Add("platform", Platform);
	
	LLAPI<FLootLockerPlayerInfoResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayerInfoEndpoint, { OtherPlayerId }, QueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetMultiplePlayersXp(FLootLockerMultiplePlayersXpRequest Request, const FPMultiplePlayersXPBP &OnCompletedRequestBP, const FPMultiplePlayersXP &OnCompletedRequest)
{
	LLAPI<FLootLockerMultiplePlayerXpResponse>::CallAPI(HttpClient, Request, ULootLockerGameEndpoints::GetMultipleOtherPlatersXPAndLevel, {  },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerPlayerAssetNotificationResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerPlayerAssetNotificationResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::CheckPlayerAssetDeactivatonEndpoint, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::InitiateDLCMigration, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP, const FPDlcResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerDlcResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetDLCsMigrated, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePrivate, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePublic, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::SetPlayerName(FString Name, const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{
	FLootLockerPlayerNameRequest Data;
	FString PlayerName;
	Data.name = Name;

	LLAPI<FLootLockerNameResponse>::CallAPI(HttpClient, Data, ULootLockerGameEndpoints::SetPlayerName, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::GetPlayerName(const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{
	LLAPI<FLootLockerNameResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerName, {  },EmptyQueryParams,OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(FLootLockerMultiplePlayerNamesRequest Request,
	const FPMultiplePlayerNamesBP& OnCompletedRequestBP, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMap<FString,FString> QueryParams;

	for (const auto player : Request.player_ids)
	{
		QueryParams.Add(player.platform, player.player_id);
	}
	LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  },QueryParams,OnCompletedRequestBP, OnCompletedRequest);
}
