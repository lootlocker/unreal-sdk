// Copyright Epic Games, Inc. All Rights Reserved.

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
    
    static inline FLootLockerSDKModule& Get()
    {
      return FModuleManager::LoadModuleChecked<FLootLockerSDKModule>("LootLockerSDK");
    }
    
    inline ULootLockerConfig* GetSettings()
    {
        return LootLockerSettings;
    }
    
private:
    ULootLockerConfig* LootLockerSettings;
};
