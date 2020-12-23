// Copyright (c) 2020 LootLocker

#include "Demo/DemoCharacters.h"

ADemoCharacters::ADemoCharacters()
{
    LootLockerManager = NewObject<ULootLockerSDKManager>();
}

void ADemoCharacters::GetCharacterLoadout()
{
    LootLockerManager->GetCharacterLoadout(FLootLockerCharacterLoadoutResponse::CreateUObject(this, &ADemoCharacters::OnGetCharacterLoadoutCompleted));
}

void ADemoCharacters::EquipAssetToDefaultCharacter()
{
    LootLockerManager->EquipAssetToDefaultCharacter(InstanceId, FLootLockerCharacterDefaultResponse::CreateUObject(this, &ADemoCharacters::OnEquipAssetToDefaultCharacterCompleted));
}

void ADemoCharacters::EquipAssetToCharacterById()
{
    LootLockerManager->EquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId, FLootLockerCharacterDefaultResponse::CreateUObject(this, &ADemoCharacters::OnEquipAssetToCharacterByIdCompleted));
}

void ADemoCharacters::UnEquipAssetToDefaultCharacter()
{
    LootLockerManager->UnEquipAssetToDefaultCharacter(InstanceId, FLootLockerCharacterDefaultResponse::CreateUObject(this, &ADemoCharacters::OnUnEquipAssetToDefaultCharacterCompleted));
}

void ADemoCharacters::UnEquipAssetToCharacterById()
{
    LootLockerManager->UnEquipAssetToCharacterById(CharacterId, AssetId, AssetVariationId, FLootLockerCharacterDefaultResponse::CreateUObject(this, &ADemoCharacters::OnUnEquipAssetToCharacterByIdCompleted));
}

void ADemoCharacters::GetCurrentLoadoutToDefaultCharacter()
{
    LootLockerManager->GetCurrentLoadoutToDefaultCharacter(FLootLockerCharacterLoadoutResponse::CreateUObject(this, &ADemoCharacters::OnGetCurrentLoadoutToDefaultCharacterCompleted));
}

void ADemoCharacters::GetOtherPlayersCurrentLoadoutToDefaultCharacter()
{
    LootLockerManager->GetOtherPlayersCurrentLoadoutToDefaultCharacter(OtherPlayerId, FLootLockerCharacterLoadoutResponse::CreateUObject(this, &ADemoCharacters::OnGetOtherPlayersCurrentLoadoutToDefaultCharacterCompleted));
}

void ADemoCharacters::GetEquipableContextsToDefaultCharacter()
{
    LootLockerManager->GetEquipableContextsToDefaultCharacter(FContextDelegate::CreateUObject(this, &ADemoCharacters::OnGetEquipableContextsToDefaultCharacterCompleted));
}

void ADemoCharacters::GetEquipableContextsByCharacterId()
{
    LootLockerManager->GetEquipableContextsByCharacterId(OtherPlayerId, FContextDelegate::CreateUObject(this, &ADemoCharacters::OnGetEquipableContextsByCharacterIdCompleted));
}

void ADemoCharacters::OnGetCharacterLoadoutCompleted(FCharacterLoadoutResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetCharacterLoadoutCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnEquipAssetToDefaultCharacterCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnEquipAssetToDefaultCharacterCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnEquipAssetToCharacterByIdCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnEquipAssetToCharacterByIdCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnUnEquipAssetToDefaultCharacterCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnUnEquipAssetToDefaultCharacterCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnUnEquipAssetToCharacterByIdCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnUnEquipAssetToCharacterByIdCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnGetCurrentLoadoutToDefaultCharacterCompleted(FCharacterLoadoutResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetCurrentLoadoutToDefaultCharacterCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnGetOtherPlayersCurrentLoadoutToDefaultCharacterCompleted(FCharacterLoadoutResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetOtherPlayersCurrentLoadoutToDefaultCharacterCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnGetEquipableContextsToDefaultCharacterCompleted(FGetContextResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetEquipableContextsToDefaultCharacterCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoCharacters::OnGetEquipableContextsByCharacterIdCompleted(FGetContextResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetEquipableContextsByCharacterIdCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
