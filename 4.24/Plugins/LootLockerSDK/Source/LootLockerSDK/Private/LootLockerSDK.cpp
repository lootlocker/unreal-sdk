// Copyright (c) 2020 LootLocker

#include "LootLockerSDK.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerConfig.h"
#include "LevelEditor.h"
#include "UObject/ConstructorHelpers.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LootLockerCommands.h"
#include "LootLockerStyle.h"

#include "Editor/Blutility/Classes/EditorUtilityWidgetBlueprint.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Editor/Blutility/Public/EditorUtilitySubsystem.h"
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"

#define LOCTEXT_NAMESPACE "FLootLockerSDKModule"

void FLootLockerSDKModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR
    
    LootLockerSettings = NewObject<ULootLockerConfig>(GetTransientPackage(), "LootLockerSettings", RF_Standalone);
    LootLockerSettings->AddToRoot();

	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

	if (SettingsModule != nullptr)
	{
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "LootLockerSDK",
			LOCTEXT("LootLockerSDKSettingsName", "LootLockerSDK"),
			LOCTEXT("LootLockerSDKSettingsDescription", "Configure LootLockerSDK."),
			LootLockerSettings
		);
	}
    
    AddEditorShortcut();

#endif
}

void FLootLockerSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
      SettingsModule->UnregisterSettings("Project", "Plugins", "LootLockerSDK");
    }

    if (!GExitPurge)
    {
      // If we're in exit purge, this object has already been destroyed
      LootLockerSettings->RemoveFromRoot();
    }
    else
    {
      LootLockerSettings = nullptr;
    }
    
    LootLockerStyle::Shutdown();

    LootLockerCommands::Unregister();
}

void FLootLockerSDKModule::AddEditorShortcut()
{
    LootLockerStyle::Initialize();
    LootLockerStyle::ReloadTextures();

    LootLockerCommands::Register();
    
    PluginCommands = MakeShareable(new FUICommandList);
    
    PluginCommands->MapAction(
        LootLockerCommands::Get().PluginAction,
        FExecuteAction::CreateRaw(this, &FLootLockerSDKModule::OpenAdminDemo),
        FCanExecuteAction());
        
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    
    {
        TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
        MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FLootLockerSDKModule::AddMenuExtension));

        LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
    }
    
    {
        TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
        ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FLootLockerSDKModule::AddToolbarExtension));
        
        LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
    }
}

void FLootLockerSDKModule::AddMenuExtension(FMenuBuilder& Builder)
{
    Builder.AddMenuEntry(LootLockerCommands::Get().PluginAction);
}

void FLootLockerSDKModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
    Builder.AddToolBarButton(LootLockerCommands::Get().PluginAction);
}

void FLootLockerSDKModule::OpenAdminDemo()
{
    const FString BlueprintRef = "EditorUtilityWidgetBlueprint'/LootLockerSDK/Demo/AdminUI/AdminAPIControlPanel'";
    FSoftObjectPath BlueprintPath = FSoftObjectPath(BlueprintRef);
    UObject* BlueprintObject = BlueprintPath.TryLoad();
    UWidgetBlueprint* Blueprint = Cast<UWidgetBlueprint>(BlueprintObject);
     
    if (!Blueprint || Blueprint->IsPendingKillOrUnreachable())
    {
        return;
    }
     
    if (!Blueprint->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))
    {
        return;
    }
     
    UEditorUtilityWidgetBlueprint* EditorWidget = (UEditorUtilityWidgetBlueprint*)Blueprint;
    if (EditorWidget)
    {
        UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
        EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
