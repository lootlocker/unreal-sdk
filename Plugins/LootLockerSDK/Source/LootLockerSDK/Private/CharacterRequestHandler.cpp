// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterRequestHandler.h"

FResponseCallback UCharacterRequestHandler::sessionResponse = nullptr;
UHttpClient* UCharacterRequestHandler::HttpClient = nullptr;

UCharacterRequestHandler::UCharacterRequestHandler()
{
	HttpClient = NewObject<UHttpClient>();
}

void UCharacterRequestHandler::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetCharacterLoadoutEndpoint.requestMethod));
	HttpClient->SendApi(config->GetCharacterLoadoutEndpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void UCharacterRequestHandler::UpdateCharacter(const bool& IsDefault, const FString& Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FUpdateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = Name;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->UpdateCharacterEndpoint.requestMethod));
	HttpClient->SendApi(config->UpdateCharacterEndpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::EquipAssetToDefaultCharacter(const int32& InstanceId,const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	FEquipAssetToCharacterWithInstanceRequest characterRequest;
	characterRequest.instance_id = InstanceId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->EquipAssetToDefaultCharacterEndpoint.requestMethod));
	HttpClient->SendApi(config->EquipAssetToDefaultCharacterEndpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::EquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests,const int32& AssetId, const int32& AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	FEquipUniversalAssetToCharacterRequest characterRequest;
	characterRequest.asset_id = AssetId;
	characterRequest.asset_variation_id = AssetVariationId;

	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FEquipUniversalAssetToCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString newEndpoint = FString::Format(*config->EquipAssetToDefaultCharacterEndpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->EquipAssetToDefaultCharacterEndpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::UnEquipAssetToDefaultCharacter(const int32& InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FString data;
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	FEquipAssetToCharacterWithInstanceRequest characterRequest;
	characterRequest.instance_id = InstanceId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->UnEquipAssetToDefaultCharacterEndpoint.requestMethod));
	HttpClient->SendApi(config->UnEquipAssetToDefaultCharacterEndpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::UnEquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests, const int32& AssetId,const  int32& AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FEquipUniversalAssetToCharacterRequest characterRequest;
	characterRequest.asset_id = AssetId;
	characterRequest.asset_variation_id = AssetVariationId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FEquipUniversalAssetToCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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

	FString newEndpoint = FString::Format(*config->UnEquipAssetToCharacterByIdEndpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->UnEquipAssetToCharacterByIdEndpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();

	FString ContentString;

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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

	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetCurrentLoadoutToDefaultCharacterEndpoint.requestMethod));
	HttpClient->SendApi(config->GetCurrentLoadoutToDefaultCharacterEndpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerGetRequests& GetRequests, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP,  const FLootLockerCharacterLoadoutResponse& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FString ContentString;

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString newEndpoint = FString::Format(*config->GetOtherPlayersLoadoutToDefaultCharacterEndpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetOtherPlayersLoadoutToDefaultCharacterEndpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FString ContentString;
	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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

	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetEquippableContextstoDefaultCharacterEndpoint.requestMethod));
	HttpClient->SendApi(config->GetEquippableContextstoDefaultCharacterEndpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UCharacterRequestHandler::GetEquipableContextsByCharacterId(const FLootLockerGetRequests& GetRequests, const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	ULootLockerConfig* config = GetMutableDefault<ULootLockerConfig>();
	FString ContentString;

	sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
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
	FString newEndpoint = FString::Format(*config->GetEquippableContextsByCharacterIDEndpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(config->GetEquippableContextsByCharacterIDEndpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
