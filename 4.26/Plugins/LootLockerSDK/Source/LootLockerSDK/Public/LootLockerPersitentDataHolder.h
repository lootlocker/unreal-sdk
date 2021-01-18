// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerPersitentDataHolder.generated.h"


UCLASS()
class LOOTLOCKERSDK_API ULootLockerPersitentDataHolder : public UObject
{
	GENERATED_BODY()
public:	
	static FString Token;
	static FString CachedLastEndpointUsed;
	static FString CachedLastRequestTypeUsed;
	static FString CachedLastDataSentToServer;
	static FString CachedSteamToken;
    static FString CachedPlayerIdentifier;
    static FString AdminToken;

};
