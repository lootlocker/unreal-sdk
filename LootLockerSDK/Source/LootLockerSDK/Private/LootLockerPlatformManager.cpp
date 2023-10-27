// Copyright (c) 2021 LootLocker


#include "LootLockerPlatformManager.h"

#include "Utils/LootLockerUtilities.h"

TMap<ELootLockerPlatform, FLootLockerPlatformRepresentation> ULootLockerCurrentPlatform::PlatformRepresentations = TMap<ELootLockerPlatform, FLootLockerPlatformRepresentation>{
        {ELootLockerPlatform::None, FLootLockerPlatformRepresentation(ELootLockerPlatform::None, "", "")}
		, {ELootLockerPlatform::Guest, FLootLockerPlatformRepresentation(ELootLockerPlatform::Guest, "guest", "guest")}
		, {ELootLockerPlatform::WhiteLabel, FLootLockerPlatformRepresentation(ELootLockerPlatform::WhiteLabel, "white_label_login", "white_label_login")}
		, {ELootLockerPlatform::Steam, FLootLockerPlatformRepresentation(ELootLockerPlatform::Steam, "steam", "steam")}
		, {ELootLockerPlatform::PlayStationNetwork, FLootLockerPlatformRepresentation(ELootLockerPlatform::PlayStationNetwork, "psn", "psn")}
		, {ELootLockerPlatform::Xbox, FLootLockerPlatformRepresentation(ELootLockerPlatform::Xbox, "xbox_one", "xbox_one")}
		, {ELootLockerPlatform::NintendoSwitch, FLootLockerPlatformRepresentation(ELootLockerPlatform::NintendoSwitch, "nintendo_switch", "nintendo_switch")}
		, {ELootLockerPlatform::AmazonLuna, FLootLockerPlatformRepresentation(ELootLockerPlatform::AmazonLuna, "amazon_luna", "amazon_luna")}
		, {ELootLockerPlatform::AppleSignIn, FLootLockerPlatformRepresentation(ELootLockerPlatform::AppleSignIn, "apple_sign_in", "apple_sign_in")}
		, {ELootLockerPlatform::Android, FLootLockerPlatformRepresentation(ELootLockerPlatform::Android, "android", "android")}
		, {ELootLockerPlatform::Google, FLootLockerPlatformRepresentation(ELootLockerPlatform::Google, "google_sign_in", "google_sign_in")}
		, {ELootLockerPlatform::Epic, FLootLockerPlatformRepresentation(ELootLockerPlatform::Epic, "epic_games", "epic_games")}
        , {ELootLockerPlatform::AppleGameCenter, FLootLockerPlatformRepresentation(ELootLockerPlatform::AppleGameCenter, "apple_game_center", "apple_game_center")}
        , {ELootLockerPlatform::Meta, FLootLockerPlatformRepresentation(ELootLockerPlatform::Meta, "meta", "meta")}
        , {ELootLockerPlatform::Remote, FLootLockerPlatformRepresentation(ELootLockerPlatform::Remote, "remote", "remote")}
};

FLootLockerPlatformRepresentation& ULootLockerCurrentPlatform::CurrentPlatform = *PlatformRepresentations.Find(ELootLockerPlatform::None);

FString FLootLockerPlatformRepresentation::GetFriendlyPlatformString()
{
    return ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerPlatform"), static_cast<int>(Platform));
}
