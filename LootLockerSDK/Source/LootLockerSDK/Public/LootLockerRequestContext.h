// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerRequestContext.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerRequestContext
{
    GENERATED_BODY()
    // What player this request was made on behalf of
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString PlayerUlid = "";
    // The time that this request was made
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestTime = "";
    // The unique identifier for this request
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestId = "";
    // The url that this request was made to
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestURL = "";
    // The url that this request was made to
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestMethod = "";
    // The request parameters as a json string.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestParametersJsonString = "";
};
