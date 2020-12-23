// Copyright (c) 2020 LootLocker

#include "LootLockerSDK.h"
#include "LootLockerCommands.h"
#include "InputCoreTypes.h"

#define LOCTEXT_NAMESPACE "FLootLockerSDKModule"

void LootLockerCommands::RegisterCommands()
{
    UI_COMMAND(PluginAction, "LootLocker Admin", "Open LootLocker Admin Console", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftMouseButton, true, false, false, false));
}

#undef LOCTEXT_NAMESPACE
