// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerErrorData.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerErrorData
{
    GENERATED_BODY()
	// A descriptive code identifying the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
    // A link to further documentation on the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Doc_url = "";
    // A unique identifier of the request to use in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Request_id = "";
    // A unique identifier for tracing the request through LootLocker systems, use this in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Trace_id = "";
    /// <summary>
    /// If the request was rate limited (status code 429) or the servers were temporarily unavailable (status code 503) you can use this value to determine how many seconds to wait before retrying
    /// </summary>
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Retry_after_seconds = -1;
    // A free text description of the problem and potential suggestions for fixing it
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Message = "";
};
