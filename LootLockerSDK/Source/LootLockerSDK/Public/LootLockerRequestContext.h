// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerRequestContext.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerRequestContext
{
    GENERATED_BODY()
    // What player this request was made on behalf of
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString PlayerUlid;
    // The time that this request was made
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestTime;
};
