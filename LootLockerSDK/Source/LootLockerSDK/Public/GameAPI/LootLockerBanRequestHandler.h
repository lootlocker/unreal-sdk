// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerErrorData.h"
#include "LootLockerPlayerData.h"
#include "LootLockerBanRequestHandler.generated.h"

//==================================================
// Request / Response Definitions
//==================================================

/// @addtogroup Authentication
/// @{

USTRUCT(BlueprintType)
struct FLootLockerBanStatusRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString game_api_key = "";
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString player_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerBanStatusResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /// Whether the player is currently banned.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool is_banned = false;
    /// Details about the active ban. Populated when is_banned is true.
    /// Check is_banned before accessing these fields. On failure, ErrorData.Code contains the error code.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerBanInfo ban;
};

/// @}

//==================================================
// Delegate
//==================================================

DECLARE_DELEGATE_OneParam(FLootLockerBanStatusDelegate, FLootLockerBanStatusResponse);

//==================================================
// Handler
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerBanRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerBanRequestHandler() {}

    /**
     * Get the ban status for a player.
     * Use this after receiving a 403 player_banned response from a session start to retrieve
     * the ban reason and duration. Does not require an active player session.
     * @param PlayerUlid The ULID of the player to query
     * @param OnCompletedRequest Delegate called when the request completes
     * @return A unique id for this request used to match callbacks
     */
    static FString GetPlayerBanStatus(const FString& PlayerUlid, const FLootLockerBanStatusDelegate& OnCompletedRequest);
};
