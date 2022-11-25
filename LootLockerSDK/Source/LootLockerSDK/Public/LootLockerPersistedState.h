// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LootLockerPersistedState.generated.h"


UCLASS()
class LOOTLOCKERSDK_API ULootLockerPersistedState : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString Token = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString SteamToken = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString PlayerIdentifier = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString WhiteLabelEmail = "";
	UPROPERTY(VisibleAnywhere, Category = "LootLocker")
	FString WhiteLabelToken = "";

	ULootLockerPersistedState() {}
};