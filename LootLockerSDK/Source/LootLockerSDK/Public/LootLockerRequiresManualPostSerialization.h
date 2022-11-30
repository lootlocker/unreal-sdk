// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerRequiresManualPostSerialization.generated.h"

#define LOOTLOCKER_GET_VARIABLE_NAME(Variable) (#Variable)

USTRUCT(BlueprintType)
struct FLootLockerRequiresManualPostSerialization
{
	GENERATED_BODY()
    virtual ~FLootLockerRequiresManualPostSerialization() = default;
    virtual void DoManualPostDeserialization(TSharedPtr<FJsonObject> JsonObject) const {}
};