// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerAuthenticationRequestHandler.h"
#include "LootLockerServerEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerServerAuthenticationRequestHandler::HttpClient = nullptr;
// Sets default values for this component's properties
ULootLockerServerAuthenticationRequestHandler::ULootLockerServerAuthenticationRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerServerAuthenticationRequestHandler::StartSession(const FServerAuthResponseDelegateBP& OnCompletedRequestBP /*= FServerAuthResponseDelegateBP()*/, const FServerAuthResponseDelegate& OnCompletedRequest /*= FServerAuthResponseDelegate()*/)
{
	FLootLockerServerAuthenticationRequest AuthRequest;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	AuthRequest.is_development = config->OnDevelopmentMode;
	AuthRequest.game_version = config->GameVersion;

	LLAPI<FLootLockerServerAuthenticationResponse>::CallServerAPI(HttpClient, AuthRequest, ULootLockerServerEndpoints::StartSessionEndpoint, {}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerServerAuthenticationResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerServerAuthenticationResponse& Response)
	{
		if (Response.success)
		{
			ULootLockerStateData::SetServerToken(Response.token);
		}
	}));
}

void ULootLockerServerAuthenticationRequestHandler::Ping(const FServerPingResponseDelegateBP& OnCompletedRequestBP /*= FServerPingResponseDelegateBP()*/, const FServerPingResponseDelegate& OnCompletedRequest /*= FServerPingResponseDelegate()*/)
{
	LLAPI<FLootLockerServerPingResponse>::CallServerAPI(HttpClient, LootLockerEmptyRequest, ULootLockerServerEndpoints::PingEndpoint, {}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerServerPingResponse>::FResponseInspectorCallback());
}

void ULootLockerServerAuthenticationRequestHandler::EndSession(const FServerEndSessionResponseDelegateBP& OnCompletedRequestBP /*= FServerEndSessionResponseDelegateBP()*/, const FServerEndSessionResponseDelegate& OnCompletedRequest /*= FServerEndSessionResponseDelegate()*/)
{
	ULootLockerStateData::SetServerToken("");

	FLootLockerServerEndSessionResponse Response;
	Response.success = true;

	OnCompletedRequestBP.ExecuteIfBound(Response);
	OnCompletedRequest.ExecuteIfBound(Response);
}
