// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminHeroesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAHeroAsset {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
};

USTRUCT(BlueprintType)
struct FAHeroException {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int context_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool can_equip;
};

USTRUCT(BlueprintType)
struct FAHeroData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int character_type_id;
};

USTRUCT(BlueprintType)
struct FAHero : public FAHeroData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int hero_id;
};

USTRUCT(BlueprintType)
struct FAHeroInfo : public FAHero {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAHeroAsset> default_loadout;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAHeroException> exceptions;
};

USTRUCT(BlueprintType)
struct FAHeroAssetData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_variation_id = -1;
};

USTRUCT(BlueprintType)
struct FAHeroExceptionData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool can_equip;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int context_id = -1;
};

USTRUCT(BlueprintType)
struct FAHeroesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAHero> heroes;
};

USTRUCT(BlueprintType)
struct FAHeroInfoResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAHeroInfo hero;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAHeroesResponseDelegate, FAHeroesResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAHeroInfoResponseDelegate, FAHeroInfoResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminHeroesRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void ListHeroes(int GameId, const FAHeroesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetHero(int GameId, int HeroId, const FAHeroInfoResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CreateHero(int GameId, const FAHeroData& HeroData, const FAHeroInfoResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateHero(int GameId, int HeroId, const FAHeroData& HeroData, const FAHeroInfoResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void DeleteHero(int GameId, int HeroId, const FLootLockerResponseCallback& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void AddAssetToDefaultHeroLoadout(int GameId, int HeroId, const FAHeroAssetData& AssetData, const FAHeroInfoResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void RemoveAssetFromDefaultHeroLoadout(int GameId, int HeroId, int AssetId, const FAHeroInfoResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void AddHeroException(int GameId, int HeroId, const FAHeroExceptionData& ExceptionData, const FAHeroInfoResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Heroes", meta = (AutoCreateRefTerm = "OnComplete"))
    static void RemoveHeroException(int GameId, int HeroId, int ExceptionId, const FAHeroInfoResponseDelegate& OnComplete);
    
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
