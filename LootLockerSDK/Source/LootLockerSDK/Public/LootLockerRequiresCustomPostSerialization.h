// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerRequiresCustomPostSerialization.generated.h"

#define LOOTLOCKER_GET_VARIABLE_NAME(Variable) (#Variable)

USTRUCT(BlueprintType)
struct FLootLockerRequiresCustomPostSerialization
{
	GENERATED_BODY()
    virtual ~FLootLockerRequiresCustomPostSerialization() = default;
    virtual void DoCustomPostSerialization(TSharedPtr<FJsonObject> JsonObject) const {}
};