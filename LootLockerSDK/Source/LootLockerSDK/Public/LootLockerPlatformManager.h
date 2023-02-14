// Copyright (c) 2021 LootLocker

#pragma once

#include <stdexcept>

#include "CoreMinimal.h"
#include "LootLockerConfig.h"
#include "LootLockerPlatformManager.generated.h"

UENUM(BlueprintType)
enum class ELootLockerPlatform : uint8
{
	None = 0				UMETA(DisplayName = "None"),
	Guest = 1				UMETA(DisplayName = "Guest"),
	WhiteLabel = 2			UMETA(DisplayName = "White Label"),
	Steam = 3				UMETA(DisplayName = "Steam"),
	PlayStationNetwork = 4	UMETA(DisplayName = "PlayStation Network"),
	Xbox = 5				UMETA(DisplayName = "Xbox"),
	NintendoSwitch = 6		UMETA(DisplayName = "Nintendo Switch Online"),
	AmazonLuna = 7			UMETA(DisplayName = "Amazon Luna"),
	AppleSignIn = 8			UMETA(DisplayName = "Apple Sign In"),
	Android = 9				UMETA(DisplayName = "Android"),
	LastValue = 10			UMETA(DisplayName = "N/A")
};


USTRUCT(BlueprintType)
struct FLootLockerPlatformRepresentation
{
	GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    ELootLockerPlatform Platform;
	UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString PlatformString;
	UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
    FString FriendlyPlatformString;

    FLootLockerPlatformRepresentation(const ELootLockerPlatform& Platform = ELootLockerPlatform::None, const FString& PlatformString = TEXT(""))
	    : Platform(Platform),
	    PlatformString(PlatformString),
	    FriendlyPlatformString(GetFriendlyStringFromEnum(Platform))
	{
	}
private:
	static const FString GetFriendlyStringFromEnum(const ELootLockerPlatform& Platform);
};

UCLASS(BlueprintType)
class LOOTLOCKERSDK_API ULootLockerCurrentPlatform : public UObject
{
	GENERATED_BODY()
public:
    ULootLockerCurrentPlatform()
    {
		EnsureAllPlatformsAreRepresented();
    };
	static const ELootLockerPlatform& Get() { return CurrentPlatform.Platform; }
	static const FString& GetString() { return CurrentPlatform.PlatformString; }
	static const FString& GetFriendlyString() { return CurrentPlatform.FriendlyPlatformString; }
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous")
	static const FLootLockerPlatformRepresentation& GetPlatformRepresentation() { return CurrentPlatform; }
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous")
    static const FLootLockerPlatformRepresentation& GetPlatformRepresentationForPlatform(const ELootLockerPlatform Platform) { return *PlatformRepresentations.Find(Platform); }

	static void Reset() { CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::None); }
	static void Set(const ELootLockerPlatform& Platform) { CurrentPlatform = *PlatformRepresentations.Find(Platform); }
	static void Set(const ELootLockerPlatformType& LegacyPlatform);

	virtual void PostInitProperties() override
	{
		UObject::PostInitProperties();
		EnsureAllPlatformsAreRepresented();
	}
private:
	static TMap<ELootLockerPlatform, FLootLockerPlatformRepresentation> PlatformRepresentations;

	static FLootLockerPlatformRepresentation& CurrentPlatform;

	// Can't static assert, so we try and make it painfully obvious runtime that we've missed something
	static void EnsureAllPlatformsAreRepresented()
	{
		if (PlatformRepresentations.Num() != static_cast<int>(ELootLockerPlatform::LastValue))
		{
			UE_LOG(LogLootLockerGameSDK, Error, TEXT("All platforms in the ELootLockerPlatform must have a representation in PlatformRepresentations"));
			throw std::range_error("All platforms in the ELootLockerPlatform must have a representation in PlatformRepresentations");
		}
	}
};