// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Launch/Resources/Version.h"
#include "LootLockerStateData.generated.h"


UCLASS()
class LOOTLOCKERSDK_API ULootLockerStateData : public UObject
{
	GENERATED_BODY()
    static FString Token;
	static FString SteamToken;
	static FString PlayerIdentifier;
	static FString WhiteLabelEmail;
	static FString WhiteLabelToken;

#if ENGINE_MAJOR_VERSION < 5
	static const FString SaveSlot;
    static constexpr int SaveIndex = 0;
#else
    inline static const FString SaveSlot = "LootLocker";
    inline static constexpr int SaveIndex = 0;
#endif
	static bool StateLoaded;

	static void LoadStateFromDiskIfNeeded();
	static void SaveStateToDisk();
public:
	static FString GetToken();
	static FString GetSteamToken();
	static FString GetPlayerIdentifier();
	static FString GetWhiteLabelEmail();
	static FString GetWhiteLabelToken();
	static void SetToken(FString InToken);
	static void SetSteamToken(FString InSteamToken);
	static void SetPlayerIdentifier(FString InPlayerIdentifier);
	static void SetWhiteLabelEmail(FString InWhiteLabelEmail);
	static void SetWhiteLabelToken(FString InWhiteLabelToken);
    static void ClearState();
};