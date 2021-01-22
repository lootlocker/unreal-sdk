// Copyright (c) 2021 LootLocker

#include "GameAPI/CharacterRequestHandler.h"
#include "LootLockerGameEndpoints.h"

UHttpClient* UCharacterRequestHandler::HttpClient = nullptr;

UCharacterRequestHandler::UCharacterRequestHandler()
{
	HttpClient = NewObject<UHttpClient>();
}

void UCharacterRequestHandler::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				ResponseStruct.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Get character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(LootLockerGameEndpoints::GetCharacterLoadoutEndpoint.requestMethod));
	HttpClient->SendApi(LootLockerGameEndpoints::GetCharacterLoadoutEndpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UCharacterRequestHandler::UpdateCharacter(bool IsDefault, const FString& Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	FUpdateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = Name;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::UpdateCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::EquipAssetToDefaultCharacter(int InstanceId,const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FString data;

	FEquipAssetToCharacterWithInstanceRequest characterRequest;
	characterRequest.instance_id = InstanceId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				ResponseStruct.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Equip character failed for lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::EquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FEquipUniversalAssetToCharacterRequest characterRequest;
	characterRequest.asset_id = AssetId;
	characterRequest.asset_variation_id = AssetVariationId;

	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FEquipUniversalAssetToCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	TArray<FStringFormatArg> args;
    FEndPoints endpoint = LootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FString data;

	FEquipAssetToCharacterWithInstanceRequest characterRequest;
	characterRequest.instance_id = InstanceId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				ResponseStruct.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Equip character failed for lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::UnEquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests, int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FEquipUniversalAssetToCharacterRequest characterRequest;
	characterRequest.asset_id = AssetId;
	characterRequest.asset_variation_id = AssetVariationId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FEquipUniversalAssetToCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FEndPoints endpoint = LootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FString ContentString;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FEndPoints endpoint = LootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerGetRequests& GetRequests, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP,  const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FString ContentString;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FGetContextResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FGetContextResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FEndPoints endpoint = LootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetEquipableContextsByCharacterId(const FLootLockerGetRequests& GetRequests, const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	FString ContentString;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FGetContextResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FGetContextResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.Broadcast(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FEndPoints endpoint = LootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
