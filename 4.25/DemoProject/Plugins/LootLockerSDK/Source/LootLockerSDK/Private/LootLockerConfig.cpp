// Copyright (c) 2020 LootLocker

#include "LootLockerConfig.h"

FString ULootLockerConfig::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
    if (!EnumPtr)
        return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

    return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();

}

FString ULootLockerConfig::LootLockerGameKey = "280eec0a84e48b19de43ae3997597019585f7e1d";
ELootLockerPlatformType ULootLockerConfig::Platform = ELootLockerPlatformType::Android;
FString ULootLockerConfig::GameVersion = "1.0.0.0";
bool ULootLockerConfig::OnDevelopmentMode = true;
bool ULootLockerConfig::AllowTokenRefresh = false;

void ULootLockerConfig::SetLootLockerSettings(FString Key, ELootLockerPlatformType CurrentPlatform, FString Version = "1.0.0.0", bool DevelopmentMode = true, bool AllowTokenToRefresh = false) {

	ULootLockerConfig::LootLockerGameKey = Key;
	ULootLockerConfig::Platform = CurrentPlatform;
	ULootLockerConfig::GameVersion = Version;
	ULootLockerConfig::OnDevelopmentMode = DevelopmentMode;
	ULootLockerConfig::AllowTokenRefresh = AllowTokenToRefresh;
}