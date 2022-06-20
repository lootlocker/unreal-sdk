// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "LootLockerConfig.h"

class FLootLockerSDKModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
