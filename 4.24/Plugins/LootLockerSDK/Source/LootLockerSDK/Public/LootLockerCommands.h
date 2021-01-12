// Copyright (c) 2020 LootLocker

#pragma once

#include "SlateBasics.h"
#include "Framework/Commands/Commands.h"

class LootLockerCommands : public TCommands<LootLockerCommands>
{
public:

    LootLockerCommands()
        : TCommands<LootLockerCommands>(TEXT("LootLockerSDK"), NSLOCTEXT("Contexts", "LootLockerSDK", "LootLockerSDK Plugin"), NAME_None, FName(TEXT("LootLockerSDKStyle")))
    {
    }

    // TCommands<> interface
    virtual void RegisterCommands() override;

public:
    TSharedPtr<FUICommandInfo> PluginAction;
};
