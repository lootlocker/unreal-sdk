// Copyright (c) 2020 LootLocker

#include "LootLockerConfig.h"

FString ULootLockerConfig::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, Enum, true);
    if (!EnumPtr)
        return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

#if WITH_EDITOR
    return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
#else
    return EnumPtr->GetEnumName(EnumValue);
#endif
}
