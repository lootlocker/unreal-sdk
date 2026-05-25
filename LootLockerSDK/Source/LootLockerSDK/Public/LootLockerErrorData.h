// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerErrorData.generated.h"

/// Details about a player's active ban.
USTRUCT(BlueprintType)
struct FLootLockerBanInfo
{
    GENERATED_BODY()
    /// The reason for the ban. One of "manual" or "chargeback".
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ban_reason = "";
    /// The time the ban was issued, as an ISO 8601 timestamp.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString banned_on = "";
    /// The time the ban expires, as an ISO 8601 timestamp.
    /// Empty string when the ban is permanent; check the Permanent field to confirm.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString banned_until = "";
    /// True if the ban has no expiry date.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool permanent = false;
};

USTRUCT(BlueprintType)
struct FLootLockerErrorData
{
    GENERATED_BODY()
	/// A descriptive code identifying the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
    /// A link to further documentation on the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Doc_url = "";
    /// A unique identifier of the request to use in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Request_id = "";
    /// A unique identifier for tracing the request through LootLocker systems, use this in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Trace_id = "";
    /// <summary>
    /// If the request was rate limited (status code 429) or the servers were temporarily unavailable (status code 503) you can use this value to determine how many seconds to wait before retrying
    /// </summary>
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Retry_after_seconds = -1;
    /// A free text description of the problem and potential suggestions for fixing it
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Message = "";
    /// When Code is "player_banned", contains sanitized details about the active ban.
    /// Fields will have default (empty/false) values for all other error codes.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerBanInfo ban;
};
