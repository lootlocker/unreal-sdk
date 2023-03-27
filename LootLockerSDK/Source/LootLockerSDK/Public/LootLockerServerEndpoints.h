// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerConfig.h"
#include "LootLockerServerEndpoints.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ULootLockerServerEndpoints : public UObject
{
    GENERATED_BODY()
public:  
	//Session
	static FLootLockerEndPoints StartSessionEndpoint;
	static FLootLockerEndPoints PingEndpoint;
	static FLootLockerEndPoints EndSessionEndpoint;

	//PlayerStoage
	static FLootLockerEndPoints UpdateOrCreateKeyValuePairToPersistentStorageEndpoint;
	static FLootLockerEndPoints DeleteKeyFromPersistentStorageEndpoint;
	static FLootLockerEndPoints GetEntirePersistentStorageEndpoint;

	//PlayerFiles
	static FLootLockerEndPoints UploadPlayerFile;
	static FLootLockerEndPoints ListPlayerFiles;
	static FLootLockerEndPoints GetPlayerFile;
	static FLootLockerEndPoints DeletePlayerFile;
    
private:
	static FString ServerBaseUrl;

	static FLootLockerEndPoints InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method);
};
