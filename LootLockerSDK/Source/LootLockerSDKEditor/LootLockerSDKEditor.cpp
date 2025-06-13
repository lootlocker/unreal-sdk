// Copyright (c) LootLocker. All Rights Reserved.
#include "Modules/ModuleManager.h"
#include "LootLockerLogViewerWidget.h"
#include "Widgets/Docking/SDockTab.h"
#include "LevelEditor.h"
#include "ToolMenus.h"
#include "Widgets/Layout/SBox.h"

static const FName LootLockerLogViewerTabName("LootLockerLogViewer");

class FLootLockerSDKEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        FGlobalTabmanager::Get()->RegisterNomadTabSpawner(LootLockerLogViewerTabName,
            FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& Args) {
                return SNew(SDockTab)
                    .TabRole(ETabRole::NomadTab)
                    [
                        SNew(SLootLockerLogViewerWidget)
                    ];
            })
        ).SetDisplayName(FText::FromString("LootLocker Log Viewer"))
         .SetMenuType(ETabSpawnerMenuType::Enabled);

        // Register menu entry under Tools > LootLocker Tools
        UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateLambda([]
        {
            UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
            if (Menu)
            {
                FToolMenuSection& Section = Menu->AddSection("LootLocker Tools", FText::FromString("LootLocker Tools"));
                Section.AddMenuEntry(
                    "LootLockerLogViewerMenuEntry",
                    FText::FromString("LootLocker Log Viewer"),
                    FText::FromString("Open the LootLocker Log Viewer window."),
                    FSlateIcon(),
                    FUIAction(FExecuteAction::CreateLambda([]
                    {
                        FGlobalTabmanager::Get()->TryInvokeTab(LootLockerLogViewerTabName);
                    }))
                );
            }
        }));
    }

    virtual void ShutdownModule() override
    {
        FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(LootLockerLogViewerTabName);
    }
};

IMPLEMENT_MODULE(FLootLockerSDKEditorModule, LootLockerSDKEditor)
