// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
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
	Google = 10				UMETA(DisplayName = "Google"),
	Epic = 11				UMETA(DisplayName = "Epic Games / Epic Online Services (EOS)"),
	AppleGameCenter = 12	UMETA(DisplayName = "Apple Game Center"),
	Meta = 13				UMETA(DisplayName = "Apple Game Center"),
	Remote = 14				UMETA(DisplayName = "Remote Session"),
	Server = 15				UMETA(DisplayName = "Server"),
	LastValue = 16			UMETA(DisplayName = "N/A")
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
    FString AuthenticationProviderString;

    FLootLockerPlatformRepresentation(const ELootLockerPlatform& Platform = ELootLockerPlatform::None, const FString& PlatformString = TEXT(""), const FString& AuthenticationProviderString = TEXT(""))
	    : Platform(Platform),
	    PlatformString(PlatformString),
		AuthenticationProviderString(AuthenticationProviderString)
	{
	}
	FString GetFriendlyPlatformString() const;
};

UCLASS(BlueprintType)
class LOOTLOCKERSDK_API ULootLockerPlatforms : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Miscellaneous")
	static const FLootLockerPlatformRepresentation& GetPlatformRepresentationForPlatform(const ELootLockerPlatform Platform) { EnsureAllPlatformsAreRepresented(); return *PlatformRepresentations.Find(Platform); }

	//TODO: Deprecated (or rather temporary) - Remove after 20250901
	static TArray<FLootLockerPlatformRepresentation> GetAllPlatformRepresentations() { TArray<FLootLockerPlatformRepresentation> outArray; PlatformRepresentations.GenerateValueArray(outArray); return outArray; }

	virtual void PostInitProperties() override
	{
		UObject::PostInitProperties();
		EnsureAllPlatformsAreRepresented();
	}
private:
	static TMap<ELootLockerPlatform, FLootLockerPlatformRepresentation> PlatformRepresentations;

	// Can't static assert, so we try and make it painfully obvious runtime that we've missed something
	static void EnsureAllPlatformsAreRepresented()
	{
		checkf(PlatformRepresentations.Num() == static_cast<int>(ELootLockerPlatform::LastValue), TEXT("All platforms in the ELootLockerPlatform must have a representation in PlatformRepresentations"));
	}
};