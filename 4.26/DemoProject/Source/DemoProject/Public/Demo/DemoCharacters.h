// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"

#include "DemoCharacters.generated.h"

UCLASS()
class DEMOPROJECT_API ADemoCharacters : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int InstanceId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int CharacterId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int AssetVariationId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString OtherPlayerId;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void GetCharacterLoadout();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void EquipAssetToDefaultCharacter();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void EquipAssetToCharacterById();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void UnEquipAssetToDefaultCharacter();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void UnEquipAssetToCharacterById();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void GetCurrentLoadoutToDefaultCharacter();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void GetOtherPlayersCurrentLoadoutToDefaultCharacter();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void GetEquipableContextsToDefaultCharacter();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Characters")
    void GetEquipableContextsByCharacterId();
    
    void OnGetCharacterLoadoutCompleted(FCharacterLoadoutResponse Response);
    void OnEquipAssetToDefaultCharacterCompleted(FLootLockerResponse Response);
    void OnEquipAssetToCharacterByIdCompleted(FLootLockerResponse Response);
    void OnUnEquipAssetToDefaultCharacterCompleted(FLootLockerResponse Response);
    void OnUnEquipAssetToCharacterByIdCompleted(FLootLockerResponse Response);
    void OnGetCurrentLoadoutToDefaultCharacterCompleted(FCharacterLoadoutResponse Response);
    void OnGetOtherPlayersCurrentLoadoutToDefaultCharacterCompleted(FCharacterLoadoutResponse Response);
    void OnGetEquipableContextsToDefaultCharacterCompleted(FGetContextResponse Response);
    void OnGetEquipableContextsByCharacterIdCompleted(FGetContextResponse Response);
    
    
private:
    ULootLockerSDKManager* LootLockerManager;
};
