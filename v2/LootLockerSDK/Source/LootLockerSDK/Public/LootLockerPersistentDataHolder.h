// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerPersistentDataHolder.generated.h"


UCLASS()
class LOOTLOCKERSDK_API ULootLockerPersistentDataHolder : public UObject
{
	GENERATED_BODY()
public:
	static FString Token;
	static FString DomainKey;
	static FString CachedLastEndpointUsed;
	static FString CachedLastRequestTypeUsed;
	static FString CachedLastDataSentToServer;
	static FString CachedSteamToken;
    static FString CachedPlayerIdentifier;
    static FString AdminToken;

};
