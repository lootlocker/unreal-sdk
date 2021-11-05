// Copyright (c) 2021 LootLocker


#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerPlayerRequestHandler::HttpClient = nullptr;

ULootLockerPlayerRequestHandler::ULootLockerPlayerRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerPlayerRequestHandler::GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	FString data;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP,OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerPlayerInfoResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPlayerInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetPlayerInfoEndPoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::GetInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest)
{
	FString data;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerInventoryResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerInventoryResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetPlayerInventoryEndPoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::GetCurrencyBalance(const FPBalanceResponseBP& onCompletedRequestBP, const FPBalanceResponse& onCompletedRequest )
{

}

void ULootLockerPlayerRequestHandler::SubmitXp(int points,const FPSubmitResponseBP& OnCompletedRequestBP, const FSubmitXpResponse& OnCompletedRequest)
{
	FLootLockerSubmitXpRequest authRequest;
	authRequest.points = points;
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerSubmitXpRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);


	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerSubmitXpResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;	
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerSubmitXpResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::SubmitXpEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, AuthContentString, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::GetOtherPlayerInfo(FLootLockerGetRequests getRequests,const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	FString data;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	getRequests.args.Add(platform);
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerPlayerInfoResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPlayerInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetOtherPlayerInfoEndpoint;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, getRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerPlayerAssetNotificationResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPlayerAssetNotificationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}
void ULootLockerPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerPlayerAssetNotificationResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerPlayerAssetNotificationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}		
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::CheckPlayerAssetDeactivatonEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::InitiateDLCMigration;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP, const FPDlcResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerDlcResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerDlcResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::InitiateDLCMigration;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::SetProfilePrivate;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::SetProfilePublic;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::SetPlayerName(FString name, const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{
	FLootLockerPlayerNameRequest data;
	FString PlayerName;
	data.name = name;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerPlayerNameRequest::StaticStruct(), &data, PlayerName, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerNameResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerNameResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::SetPlayerName;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, PlayerName, sessionResponse, true);
}

void ULootLockerPlayerRequestHandler::GetPlayerName(const FPNameResponseBP& OnCompletedRequestBP, const FPNameResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerNameResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerNameResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetPlayerName;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}