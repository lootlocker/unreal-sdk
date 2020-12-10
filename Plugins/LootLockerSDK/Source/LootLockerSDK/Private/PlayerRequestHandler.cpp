// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRequestHandler.h"

FResponseCallback UPlayerRequestHandler::sessionResponse = nullptr;
UHttpClient* UPlayerRequestHandler::HttpClient = nullptr;

UPlayerRequestHandler::UPlayerRequestHandler()
{
	HttpClient = NewObject<UHttpClient>();
}

void UPlayerRequestHandler::GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP,OnCompletedRequest](FLootLockerResponse response)
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
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetPlayerInfoEndPoint.requestMethod));
	HttpClient->SendApi(config->GetPlayerInfoEndPoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::GetInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FLootLockerInventoryResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetPlayerInventoryEndPoint.requestMethod));
	HttpClient->SendApi(config->GetPlayerInventoryEndPoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::SubmitXp(const int32& points,const FPSubmitResponseBP& OnCompletedRequestBP, const FLootLockerSubmitXpResponse& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FSubmitXpRequest authRequest;
	authRequest.points = points;
	FString AuthContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FSubmitXpRequest::StaticStruct(), &authRequest, AuthContentString, 0, 0);


	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->SubmitXpEndpoint.requestMethod));
	HttpClient->SendApi(config->SubmitXpEndpoint.endpoint, requestMethod, AuthContentString, sessionResponse, true);
}

void UPlayerRequestHandler::GetOtherPlayerInfo(FLootLockerGetRequests getRequests,const FPInfoResponseBP& OnCompletedRequestBP, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FString platform = ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(config->Platform));
	getRequests.args.Add(platform);
	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});


	FString newEndpoint = FString::Format(*config->GetOtherPlayerInfoEndpoint.endpoint, getRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetOtherPlayerInfoEndpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, data, sessionResponse, true);
}

void UPlayerRequestHandler::CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->CheckPlayerAssetActivationEndpoint.requestMethod));
	HttpClient->SendApi(config->CheckPlayerAssetActivationEndpoint.endpoint, requestMethod, data, sessionResponse, true);
}
void UPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->CheckPlayerAssetDeactivatonEndpoint.requestMethod));
	HttpClient->SendApi(config->CheckPlayerAssetDeactivatonEndpoint.endpoint, requestMethod, data, sessionResponse, true);
}

