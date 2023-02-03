// Copyright (c) 2021 LootLocker


#include "LootLockerPlatformManager.h"

TMap<ELootLockerPlatform, FLootLockerPlatformRepresentation> ULootLockerCurrentPlatform::PlatformRepresentations = TMap<ELootLockerPlatform, FLootLockerPlatformRepresentation>{
        {ELootLockerPlatform::None, FLootLockerPlatformRepresentation(ELootLockerPlatform::None, "")}
		, {ELootLockerPlatform::Guest, FLootLockerPlatformRepresentation(ELootLockerPlatform::Guest, "guest")}
		, {ELootLockerPlatform::WhiteLabel, FLootLockerPlatformRepresentation(ELootLockerPlatform::WhiteLabel, "white_label_login")}
		, {ELootLockerPlatform::Steam, FLootLockerPlatformRepresentation(ELootLockerPlatform::Steam, "steam")}
		, {ELootLockerPlatform::PlayStationNetwork, FLootLockerPlatformRepresentation(ELootLockerPlatform::PlayStationNetwork, "psn")}
		, {ELootLockerPlatform::Xbox, FLootLockerPlatformRepresentation(ELootLockerPlatform::Xbox, "xbox_one")}
		, {ELootLockerPlatform::NintendoSwitch, FLootLockerPlatformRepresentation(ELootLockerPlatform::NintendoSwitch, "nintendo_switch")}
		, {ELootLockerPlatform::AmazonLuna, FLootLockerPlatformRepresentation(ELootLockerPlatform::AmazonLuna, "amazon_luna")}
		, {ELootLockerPlatform::AppleSignIn, FLootLockerPlatformRepresentation(ELootLockerPlatform::AppleSignIn, "apple_sign_in")}
		, {ELootLockerPlatform::Android, FLootLockerPlatformRepresentation(ELootLockerPlatform::Android, "android")}
};

FLootLockerPlatformRepresentation& ULootLockerCurrentPlatform::CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::None);

const FString FLootLockerPlatformRepresentation::GetFriendlyStringFromEnum(const ELootLockerPlatform& Platform)
{
    return ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatform"), static_cast<int>(Platform));
}

void ULootLockerCurrentPlatform::Set(const ELootLockerPlatformType& LegacyPlatform)
{
    switch (LegacyPlatform) {
    case ELootLockerPlatformType::Android: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::Guest); break;
    case ELootLockerPlatformType::Ios: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::AppleSignIn); break;
    case ELootLockerPlatformType::Steam: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::Steam); break;
    case ELootLockerPlatformType::NintendoSwitch: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::NintendoSwitch); break;
    case ELootLockerPlatformType::PlayStationNetwork: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::PlayStationNetwork); break;
    case ELootLockerPlatformType::Xbox: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::Xbox); break;

    case ELootLockerPlatformType::UNUSED:
    default: CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::None); break;
    }
}
