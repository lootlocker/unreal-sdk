// Copyright (c) 2021 LootLocker

#pragma once

#include "Runtime/Launch/Resources/Version.h"
#if ENGINE_MAJOR_VERSION >= 5
#include <regex>
#endif
#include "CoreMinimal.h"
#include "LootLockerConfig.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "LootLocker SDK Settings"))
class LOOTLOCKERSDK_API ULootLockerConfig : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION()
	static bool IsSemverString(const FString& str)
	{
#if ENGINE_MAJOR_VERSION >= 5
		return std::regex_match(TCHAR_TO_UTF8(*str), SemverPattern);
#else
		return true;
#endif
	}
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		if (PropertyChangedEvent.GetPropertyName() == "GameVersion")
		{
			IsValidGameVersion = IsSemverString(GameVersion);
		}
		if (SDKVersion.IsEmpty())
		{
			SDKVersion = ReadSDKVersionFromPlugin();
		}
		UObject::PostEditChangeProperty(PropertyChangedEvent);
	}
#endif //WITH_EDITOR
	virtual void PostInitProperties() override
	{
		IsValidGameVersion = IsSemverString(GameVersion);
		if (SDKVersion.IsEmpty())
		{
			SDKVersion = ReadSDKVersionFromPlugin();
		}
		UObject::PostInitProperties();
	}

	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker", Meta = (EditCondition = "IsOutdatedSDK", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString OutdatedSDKWarning = "This version of LootLocker is no longer updated through fab because of fab guidelines. Please use GitHub releases to update: https://github.com/lootlocker/unreal-sdk/releases";
	// API Key used to talk to LootLocker. The API key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker", Meta = (DisplayName = "LootLocker API Key"))
	FString LootLockerGameKey;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString GameVersion;
	UPROPERTY(Config, VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker", Meta = (EditCondition = "!IsValidGameVersion", EditConditionHides), Meta = (MultiLine = true), Meta = (DisplayName = "WARNING:"), Transient)
	FString InvalidGameVersionWarning = "Game version needs to follow a numeric Semantic Versioning pattern: X.Y.Z.B with the sections denoting MAJOR.MINOR.PATCH.BUILD and the last two being optional. Read more at https://docs.lootlocker.com/the-basics/core-concepts/glossary#game-version";
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool AllowTokenRefresh = true;
	// Domain Key used to talk to LootLocker. The Domain key can be found in `Settings > API Keys` in the Web Console: https://console.lootlocker.com/settings/api-keys
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString DomainKey;

	static FString GetSDKVersionString();
private:
	static FString ReadSDKVersionFromPlugin();
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool IsValidGameVersion = true;
	UPROPERTY(Config, VisibleInstanceOnly, Meta = (EditCondition = "false", EditConditionHides), Transient, Category = "LootLocker")
	bool IsOutdatedSDK /* Value in ifdef */
#ifdef LOOTLOCKER_SHOW_OUTDATED_SDK_MESSAGE
		= true
#else
		= false
#endif
	;
#if ENGINE_MAJOR_VERSION >= 5
	inline static const std::regex SemverPattern = std::regex("^(0|[1-9]\\d*)\\.(0|[1-9]\\d*)(?:\\.(0|[1-9]\\d*))?(?:\\.(0|[1-9]\\d*))?$");
#endif
	static FString SDKVersion;
};
