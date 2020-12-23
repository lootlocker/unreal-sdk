// Copyright (c) 2020 LootLocker

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
    void AddEditorShortcut();
    void AddMenuExtension(FMenuBuilder& Builder);
    void AddToolbarExtension(FToolBarBuilder& Builder);
    void OpenAdminDemo();
    ULootLockerConfig* LootLockerSettings;
    TSharedPtr<class FUICommandList> PluginCommands;
    TSubclassOf<UUserWidget> DefaultWidgetClass;
};
