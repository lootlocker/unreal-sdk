// Copyright (c) 2021 LootLocker

#include "LootLockerServerEndpoints.h"

FString ULootLockerServerEndpoints::ServerBaseUrl = "https://api.lootlocker.io/server/";

//Session
FLootLockerEndPoints ULootLockerServerEndpoints::StartSessionEndpoint = InitEndpoint("session", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerServerEndpoints::PingEndpoint = InitEndpoint("ping", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerServerEndpoints::EndSessionEndpoint = InitEndpoint("session", ELootLockerHTTPMethod::DELETE);

//PlayerStorage
FLootLockerEndPoints ULootLockerServerEndpoints::UpdateOrCreateKeyValuePairToPersistentStorageEndpoint = InitEndpoint("players/storage", ELootLockerHTTPMethod::PATCH);
FLootLockerEndPoints ULootLockerServerEndpoints::DeleteKeyFromPersistentStorageEndpoint = InitEndpoint("players/storage", ELootLockerHTTPMethod::DELETE);
FLootLockerEndPoints ULootLockerServerEndpoints::GetEntirePersistentStorageEndpoint = InitEndpoint("players/storage", ELootLockerHTTPMethod::GET);

//PlayerFiles
FLootLockerEndPoints ULootLockerServerEndpoints::UploadPlayerFile = InitEndpoint("players/{0}/files", ELootLockerHTTPMethod::POST);
FLootLockerEndPoints ULootLockerServerEndpoints::ListPlayerFiles = InitEndpoint("players/{0}/files", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerServerEndpoints::GetPlayerFile = InitEndpoint("players/{0}/files/{1}", ELootLockerHTTPMethod::GET);
FLootLockerEndPoints ULootLockerServerEndpoints::DeletePlayerFile = InitEndpoint("players/{0}/files/{1}", ELootLockerHTTPMethod::DELETE);

FLootLockerEndPoints ULootLockerServerEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method)
{
	FLootLockerEndPoints Result;
	Result.endpoint = ServerBaseUrl + Endpoint;
	Result.requestMethod = Method;
	return Result;
}
