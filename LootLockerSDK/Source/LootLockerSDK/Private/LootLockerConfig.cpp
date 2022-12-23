// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"

DEFINE_LOG_CATEGORY(LogLootLockerGameSDK);

FString ULootLockerConfig::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuterUPackage(), Enum, true);
    if (!EnumPtr)
        return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

    return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();

}
