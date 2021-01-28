// Copyright (c) 2021 LootLocker


#include "GameAPI/PlayerRequestHandler.h"
#include "LootLockerGameEndpoints.h"

UHttpClient* UPlayerRequestHandler::HttpClient = nullptr;

UPlayerRequestHandler::UPlayerRequestHandler()
{
	HttpClient = NewObject<UHttpClient>();
}

void UPlayerRequestHandler::GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	FString data;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP,OnCompletedRequest](FLootLockerResponse response)
		{
			FPlayerInfoResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FPlayerInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints Endpoint = ULootLockerGameEndpoints::GetPlayerInfoEndPoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::GetInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FLootLockerInventoryResponse& OnCompletedRequest)
{
	FString data;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FInventoryResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FInventoryResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);

			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints Endpoint = ULootLockerGameEndpoints::GetPlayerInventoryEndPoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::GetCurrencyBalance(const FPBalanceResponseBP& onCompletedRequestBP, const FPBalanceResponse& onCompletedRequest )
{

}

void UPlayerRequestHandler::SubmitXp(int points,const FPSubmitResponseBP& OnCompletedRequestBP, const FLootLockerSubmitXpResponse& OnCompletedRequest)
{
	FSubmitXpRequest authRequest;
	authRequest.points = points;
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FSubmitXpRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);


	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FSubmitXpResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;	
				FJsonObjectConverter::JsonObjectStringToUStruct<FSubmitXpResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints Endpoint = ULootLockerGameEndpoints::SubmitXpEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, AuthContentString, sessionResponse, true);
}

void UPlayerRequestHandler::GetOtherPlayerInfo(FLootLockerGetRequests getRequests,const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	FString data;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	getRequests.args.Add(platform);
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FPlayerInfoResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FPlayerInfoResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FEndPoints Endpoint = ULootLockerGameEndpoints::GetOtherPlayerInfoEndpoint;
	FString newEndpoint = FString::Format(*Endpoint.endpoint, getRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FPlayerAssetNotificationResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FPlayerAssetNotificationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	
    FEndPoints Endpoint = ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}
void UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FPlayerAssetNotificationResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FPlayerAssetNotificationResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}		
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FEndPoints Endpoint = ULootLockerGameEndpoints::CheckPlayerAssetDeactivatonEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
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

	FEndPoints Endpoint = ULootLockerGameEndpoints::InitiateDLCMigration;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP, const FPDlcResponse& OnCompletedRequest)
{
	FString data;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FDlcResponse ResponseStruct;
			if (response.success)
			{
				response.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FDlcResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				response.success = false;
				UE_LOG(LogTemp, Error, TEXT("Getting player failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FEndPoints Endpoint = ULootLockerGameEndpoints::InitiateDLCMigration;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
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

	FEndPoints Endpoint = ULootLockerGameEndpoints::SetProfilePrivate;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
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

	FEndPoints Endpoint = ULootLockerGameEndpoints::SetProfilePublic;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(Endpoint.endpoint, requestMethod, data, sessionResponse, true);
}