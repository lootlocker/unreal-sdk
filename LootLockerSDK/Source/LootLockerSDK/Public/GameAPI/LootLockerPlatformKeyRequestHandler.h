// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerPlatformKeyRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Information about the campaign associated with a platform key
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPlatformKeyCampaign
{
    GENERATED_BODY()
    /**
     * The name of the campaign that issued this key
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
    /**
     * The platform this key is for (e.g. "steam", "discord")
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Platform = "";
};

/**
 * A platform key redeemed by the player
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerPlatformKey
{
    GENERATED_BODY()
    /**
     * Information about the campaign that issued this key
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPlatformKeyCampaign Campaign;
    /**
     * The redeemed key value
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key = "";
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the list of platform keys redeemed by the authenticated player.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListPlatformKeysResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * List of platform keys redeemed by the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPlatformKey> Platform_Keys;
};

//==================================================
// Delegate Definitions
//==================================================

/// @addtogroup PlatformKeys
/// @{
/**
 * C++ response delegate for listing platform keys
 */
DECLARE_DELEGATE_OneParam(FLootLockerListPlatformKeysResponseDelegate, FLootLockerListPlatformKeysResponse);

/// @}

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPlatformKeyRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerPlatformKeyRequestHandler() {};

    static FString ListPlatformKeys(const FLootLockerPlayerData& PlayerData, const FLootLockerListPlatformKeysResponseDelegate& OnResponseCompleted);
};
