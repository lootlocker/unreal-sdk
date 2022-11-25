// Copyright (c) 2021 LootLocker


#include "LootLockerPersistentData.h"

FString ULootLockerPersistentData::Token = "";
FString ULootLockerPersistentData::DomainKey = "";
FString ULootLockerPersistentData::SteamToken = "";
FString ULootLockerPersistentData::PlayerIdentifier = FPlatformMisc::GetDeviceId();;
FString ULootLockerPersistentData::WhiteLabelEmail = "";
FString ULootLockerPersistentData::WhiteLabelToken = "";
