// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerHeroRequestHandler::HttpClient = nullptr;

ULootLockerHeroRequestHandler::ULootLockerHeroRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerHeroRequestHandler::GetGameHeroes(const FPGameHeroesResponseBP& OnCompletedRequestBP, const FGameHeroesResponse& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerGameHeroesResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerGameHeroesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Get game heroes failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::GetGameHeroesEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerHeroRequestHandler::ListPlayerHeroes(const FPHeroesResponseBP& OnCompletedRequestBP, const FHeroesResponse& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerHeroesResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerHeroesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("List player heroes failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::ListPlayerHeroesEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerHeroRequestHandler::CreateHero(FString HeroName, int HeroId, const FPHeroResponseBP& OnCompletedRequestBP, const FHeroResponse& OnCompletedRequest)
{
	FString data;
	FLootLockerCreateHeroRequest createHeroRequest;
	createHeroRequest.name = HeroName;
	createHeroRequest.hero_id = HeroId;

	FString ContentString;
	FJsonObjectConverter::UStructToJsonObjectString(FLootLockerCreateHeroRequest::StaticStruct(), &createHeroRequest, ContentString, 0, 0);

	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerHeroResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerHeroResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Create hero failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints endpoint = ULootLockerGameEndpoints::CreateHeroEndpoint;
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(endpoint.requestMethod));
	HttpClient->SendApi(endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerHeroRequestHandler::GetHero(int HeroId, const FPHeroResponseBP& OnCompletedRequestBP, const FHeroResponse& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerHeroResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerHeroResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Get hero failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetHeroEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { HeroId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerHeroRequestHandler::GetHeroLoadout(int HeroId, const FPHeroLoadoutResponseBP& OnCompletedRequestBP,
	const FHeroLoadoutResponse& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerHeroLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerHeroLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Get hero loadout failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetHeroLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { HeroId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerHeroRequestHandler::EquipAssetToHero(int HeroId, int AssetId, int AssetVariationId,
	const FPHeroLoadoutResponseBP& OnCompletedRequestBP, const FHeroLoadoutResponse& OnCompletedRequest)
{
TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
ItemJson->SetStringField(FString(TEXT("asset_id")), FString::FromInt(AssetId));
if(AssetVariationId > 0)
{
	ItemJson->SetStringField(FString(TEXT("asset_variation_id")), FString::FromInt(AssetVariationId));
}
FString ContentString;
TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
FJsonSerializer::Serialize(ItemJson, Writer);
	
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerHeroLoadoutResponse ResponseStruct;
			if (response.success)
			{
				FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerHeroLoadoutResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Equip asset to hero failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	TArray<FStringFormatArg> args;
	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::AddAssetToHeroLoadoutEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { HeroId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerHeroRequestHandler::DeleteHero(int HeroId, const FPHeroDefaultResponseBP& OnCompletedRequestBP,	const FHeroDefaultResponse& OnCompletedRequest)
{
	FString ContentString;
	FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
		{
			FLootLockerResponse ResponseStruct;
			if (response.success)
			{
				ResponseStruct.success = true;
			}
			else {
				ResponseStruct.success = false;
				UE_LOG(LogLootLocker, Error, TEXT("Delete hero failed from lootlocker"));
			}
			ResponseStruct.FullTextFromServer = response.FullTextFromServer;
			OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
			OnCompletedRequest.ExecuteIfBound(ResponseStruct);
		});
	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::DeleteHeroEndpoint;
	FString endpoint = FString::Format(*(Endpoint.endpoint), { HeroId });
	FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
	HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
