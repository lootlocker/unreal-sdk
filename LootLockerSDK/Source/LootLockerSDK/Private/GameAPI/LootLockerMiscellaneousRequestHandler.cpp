// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "GameAPI/LootLockerBanRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

FString ULootLockerMiscellaneousRequestHandler::GetServerTime(const FLootLockerPlayerData& PlayerData, const FTimeResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerTimeResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetServerTimeEndpoint, { },EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerMiscellaneousRequestHandler::GetLastActivePlatform(const FLootLockerPlayerData& PlayerData)
{
	return PlayerData.CurrentPlatform.GetFriendlyPlatformString();
}

FString ULootLockerMiscellaneousRequestHandler::GetGameInfo(const FGameInfoResponseDelegate& OnCompletedRequest)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerGameInfoRequest Request { config->LootLockerGameKey };
    return LLAPI<FLootLockerGameInfoResponse>::CallAPI(
        Request,
        ULootLockerGameEndpoints::GetGameInfoEndpoint,
        {},
        EmptyQueryParams,
        FLootLockerPlayerData(),
        OnCompletedRequest
    );
}

FString ULootLockerMiscellaneousRequestHandler::CheckConnectionStatus(const FLootLockerPlayerData& PlayerData, const FLootLockerConnectionStateDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerTimeResponse>::CallAPI(
        LootLockerEmptyRequest,
        ULootLockerGameEndpoints::GetServerTimeEndpoint,
        {},
        EmptyQueryParams,
        PlayerData,
        FTimeResponseDelegate::CreateLambda([PlayerData, OnCompletedRequest](FLootLockerTimeResponse PingResponse)
        {
            if (PingResponse.StatusCode == 0)
            {
                FLootLockerConnectionStateResponse Response;
                Response.success = false;
                Response.StatusCode = 0;
                Response.State = ELootLockerConnectionState::NoConnection;
                Response.FullTextFromServer = PingResponse.FullTextFromServer;
                Response.ErrorData = PingResponse.ErrorData;
                Response.Context = PingResponse.Context;
                OnCompletedRequest.ExecuteIfBound(Response);
                return;
            }

            if (PingResponse.success)
            {
                FLootLockerConnectionStateResponse Response;
                Response.success = true;
                Response.StatusCode = PingResponse.StatusCode;
                Response.State = ELootLockerConnectionState::SignedInAndConnected;
                Response.ServerTime = PingResponse.date;
                Response.FullTextFromServer = PingResponse.FullTextFromServer;
                Response.Context = PingResponse.Context;
                OnCompletedRequest.ExecuteIfBound(Response);
                return;
            }

            int32 StatusCode = PingResponse.StatusCode;

            if (StatusCode >= 500)
            {
                FLootLockerConnectionStateResponse Response;
                Response.success = false;
                Response.StatusCode = StatusCode;
                Response.State = ELootLockerConnectionState::ServerError;
                Response.FullTextFromServer = PingResponse.FullTextFromServer;
                Response.ErrorData = PingResponse.ErrorData;
                Response.Context = PingResponse.Context;
                OnCompletedRequest.ExecuteIfBound(Response);
                return;
            }

            // 401 = token expired (or a banned player's auto-refresh synthesized a 401).
            // 403 = forbidden — could also be a ban.
            // In both cases, call ban-status to check whether the player is actually banned.
            if (StatusCode == 401 || StatusCode == 403)
            {
                ULootLockerBanRequestHandler::GetPlayerBanStatus(
                    PlayerData.PlayerUlid,
                    FLootLockerBanStatusDelegate::CreateLambda([PingResponse, StatusCode, OnCompletedRequest](FLootLockerBanStatusResponse BanResponse)
                    {
                        FLootLockerConnectionStateResponse Response;
                        Response.success = false;
                        Response.StatusCode = StatusCode;
                        Response.FullTextFromServer = PingResponse.FullTextFromServer;
                        Response.ErrorData = PingResponse.ErrorData;
                        Response.Context = PingResponse.Context;

                        if (BanResponse.success && BanResponse.is_banned)
                        {
                            Response.State = ELootLockerConnectionState::Banned;
                            Response.BanDetails = BanResponse.ban;
                        }
                        else
                        {
                            Response.State = ELootLockerConnectionState::SessionExpired;
                        }
                        OnCompletedRequest.ExecuteIfBound(Response);
                    })
                );
                return;
            }

            // Any other failure (e.g. 400, 429) — map to ServerError so State is consistent with StatusCode.
            FLootLockerConnectionStateResponse Response;
            Response.success = false;
            Response.StatusCode = StatusCode;
            Response.State = ELootLockerConnectionState::ServerError;
            Response.FullTextFromServer = PingResponse.FullTextFromServer;
            Response.ErrorData = PingResponse.ErrorData;
            Response.Context = PingResponse.Context;
            OnCompletedRequest.ExecuteIfBound(Response);
        })
    );
}