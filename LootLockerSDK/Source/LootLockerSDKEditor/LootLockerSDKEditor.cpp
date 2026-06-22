// Copyright (c) LootLocker. All Rights Reserved.
#include "Modules/ModuleManager.h"
#include "LootLockerLogViewerWidget.h"
#include "LootLockerUpdateChecker.h"
#include "Widgets/Docking/SDockTab.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SBox.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/App.h"
#include "LootLockerConfig.h"

static const FName LootLockerLogViewerTabName("LootLockerLogViewer");

class FLootLockerSDKEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        // Do not register Slate widgets in headless/unattended mode (automated tests,
        // commandlets). The widget binds raw delegates to the logger which fires from
        // background threads; Slate is not safe to call off the game thread.
        if (FApp::IsUnattended() || !FSlateApplication::IsInitialized())
        {
            return;
        }

        FGlobalTabmanager::Get()->RegisterNomadTabSpawner(LootLockerLogViewerTabName,
            FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& Args) {
                return SNew(SDockTab)
                    .TabRole(ETabRole::NomadTab)
                    [
                        SNew(SLootLockerLogViewerWidget)
                    ];
            })
        ).SetDisplayName(FText::FromString(ULootLockerConfig::PackageName + TEXT(" Log Viewer")))
         .SetMenuType(ETabSpawnerMenuType::Enabled);

        // Register menu entry under Tools > LootLocker Tools
        UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateLambda([]
        {
            UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
            if (Menu)
            {
                const FString LLSectionName = ULootLockerConfig::PackageName + TEXT(" Tools");
                FToolMenuSection& Section = Menu->AddSection(*LLSectionName, FText::FromString(LLSectionName));
                Section.AddMenuEntry(
                    "LootLockerLogViewerMenuEntry",
                    FText::FromString(ULootLockerConfig::PackageName + TEXT(" Log Viewer")),
                    FText::FromString(FString::Printf(TEXT("Open the %s Log Viewer window."), *ULootLockerConfig::PackageName)),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateLambda([]
                    {
                        FGlobalTabmanager::Get()->TryInvokeTab(LootLockerLogViewerTabName);
                    }))
                );
                Section.AddMenuEntry(
                    "LootLockerCheckForUpdates",
                    FText::FromString("Check for Updates"),
                    FText::FromString(FString::Printf(TEXT("Check if a newer version of the %s SDK is available."), *ULootLockerConfig::PackageName)),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateStatic(&FLootLockerUpdateChecker::ManualCheck))
                );
            }
        }));

        // Delayed update check (fires after StartupDelaySeconds)
        FLootLockerUpdateChecker::Initialize();
    }

    virtual void ShutdownModule() override
    {
        FLootLockerUpdateChecker::Shutdown();
        FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LootLockerLogViewerTabName);
    }
};

IMPLEMENT_MODULE(FLootLockerSDKEditorModule, LootLockerSDKEditor)
