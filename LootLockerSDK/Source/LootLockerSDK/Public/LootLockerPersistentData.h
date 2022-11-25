// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerPersistentData.generated.h"


UCLASS()
class LOOTLOCKERSDK_API ULootLockerPersistentData : public UObject
{
	GENERATED_BODY()
public:
	static FString Token;
	static FString DomainKey;
	static FString SteamToken;
    static FString PlayerIdentifier;
    static FString WhiteLabelEmail;
    static FString WhiteLabelToken;
    static FString AdminToken;
};