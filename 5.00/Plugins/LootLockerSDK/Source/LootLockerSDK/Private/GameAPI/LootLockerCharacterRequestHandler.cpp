// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerCharacterRequestHandler::HttpClient = nullptr;

ULootLockerCharacterRequestHandler::ULootLockerCharacterRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerCharacterRequestHandler::GetCharacterLoadout(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				ResponseStruct.success = true;
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Get character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint.requestMethod));
	HttpClient->SendApi(ULootLockerGameEndpoints::GetCharacterLoadoutEndpoint.endpoint, requestMethod, data, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::UpdateCharacter(int CharacterId, bool IsDefault,  FString Name, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	FLootLockerUpdateCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = Name;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::UpdateCharacterEndpoint;
	TArray<FStringFormatArg> args;
	FString newEndpoint = FString::Format(*endpoint.endpoint, { CharacterId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::CreateCharacter(bool IsDefault,  FString CharacterName,  FString CharacterId, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FString data;
	FLootLockerListCharacterRequest characterRequest;
	characterRequest.is_default = IsDefault;
	characterRequest.name = CharacterName;
	characterRequest.character_type_id = CharacterId;

	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerListCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::CreateCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::ListCharacterTypes(const FPLootLockerListCharacterTypesResponseBP& OnCompletedRequestBP, const FPLootLockerListCharacterTypesResponse& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerListCharacterTypesResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerListCharacterTypesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("Update character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::ListCharacterTypesByIdEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(int InstanceId,const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FString data;

	FLootLockerEquipAssetToCharacterWithInstanceRequest characterRequest;
	characterRequest.instance_id = InstanceId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
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
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::EquipAssetToDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(FString CharacterId,int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FString data;

	FLootLockerEquipAssetToCharacterWithInstanceRequest characterRequest;
	characterRequest.instance_id = InstanceId;
	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
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
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, {CharacterId});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests,int AssetId, int AssetVariationId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerEquipUniversalAssetToCharacterRequest characterRequest;
	characterRequest.asset_id = AssetId;
	characterRequest.asset_variation_id = AssetVariationId;

	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerEquipUniversalAssetToCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
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
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	TArray<FStringFormatArg> args;
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::EquipAssetToCharacterByIdEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(int InstanceId, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	//FString data;

	//FLootLockerEquipAssetToCharacterWithInstanceRequest characterRequest;
//	characterRequest.instance_id = InstanceId;
	FString ContentString;
//	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerUpdateCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
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
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::UnEquipAssetToDefaultCharacterEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, {InstanceId});
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(const FLootLockerGetRequests& GetRequests, const FPCharacterDefaultResponseBP& OnCompletedRequestBP, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	//FLootLockerEquipUniversalAssetToCharacterRequest characterRequest;
	//characterRequest.asset_id = AssetId;
	///characterRequest.asset_variation_id = AssetVariationId;
	FString ContentString;
	//FJsonObjectConverter::UStructToJsonObjectString(FLootLockerEquipUniversalAssetToCharacterRequest::StaticStruct(), &characterRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::UnEquipAssetToCharacterByIdEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(const FPCharacterLoadoutResponseBP& OnCompletedRequestBP, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FString ContentString;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::GetCurrentLoadoutToDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FLootLockerGetRequests& GetRequests, const FPCharacterLoadoutResponseBP& OnCompletedRequestBP,  const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FString ContentString;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerCharacterLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCharacterLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerGetContextResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetContextResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});

    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::GetEquippableContextstoDefaultCharacterEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(const FLootLockerGetRequests& GetRequests, const FContextDelegateBP& OnCompletedRequestBP, const FContextDelegate& OnCompletedRequest)
{
	FString ContentString;

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerGetContextResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGetContextResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogTemp, Error, TEXT("equip asset to default character failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
    FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::GetEquippableContextsByCharacterIDEndpoint;
	FString newEndpoint = FString::Format(*endpoint.endpoint, GetRequests.args);
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(newEndpoint, requestMethod, ContentString, sessionResponse, true);
}
