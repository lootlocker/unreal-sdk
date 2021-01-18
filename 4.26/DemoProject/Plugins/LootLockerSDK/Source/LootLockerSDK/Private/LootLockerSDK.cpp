// Copyright (c) 2020 LootLocker

#include "LootLockerSDK.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "LootLockerConfig.h"
#include "LevelEditor.h"
#endif

#include "UObject/ConstructorHelpers.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"



#define LOCTEXT_NAMESPACE "FLootLockerSDKModule"


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLootLockerSDKModule, LootLockerSDK)
