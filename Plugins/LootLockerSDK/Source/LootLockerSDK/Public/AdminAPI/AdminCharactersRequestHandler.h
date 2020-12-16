// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminCharactersRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FADefaultLoadoutAsset {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString image;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString variation_name;
};

USTRUCT(BlueprintType)
struct FACharacterClassContext {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FADefaultLoadoutAsset default_loadout_asset;
};

USTRUCT(BlueprintType)
struct FACharacterClassPayload {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool Default;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FACharacterClassContext> contexts;
};

USTRUCT(BlueprintType)
struct FACharacterClass : public FACharacterClassPayload {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
};

USTRUCT(BlueprintType)
struct FACharacterClassesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FACharacterClass> character_types;
};

USTRUCT(BlueprintType)
struct FACharacterClassDeleteResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString error;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FACharacterClassesResponseDelegate, FACharacterClassesResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FACharacterClassDeleteResponseDelegate, FACharacterClassDeleteResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminCharactersRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Characters", meta = (AutoCreateRefTerm = "OnComplete"))
    static void ListCharacterClasses(int GameId, const FACharacterClassesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Characters", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CreateCharacterClass(int GameId, const FACharacterClassPayload& Data, const FACharacterClassesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Characters", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateCharacterClass(int GameId, int ClassId, const FACharacterClassPayload& Data, const FACharacterClassesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Characters", meta = (AutoCreateRefTerm = "OnComplete"))
    static void DeleteCharacterClass(int GameId, int ClassId, const FACharacterClassDeleteResponseDelegate& OnComplete);
    
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
