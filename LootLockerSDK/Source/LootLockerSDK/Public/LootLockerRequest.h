// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerRequest.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerRequest
{
	GENERATED_BODY()
public:
    virtual ~FLootLockerRequest() = default;
    virtual void DoCustomPostSerialization(TSharedPtr<FJsonObject> JsonObject) const {}
};