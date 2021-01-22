// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminGamesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAGameData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool sandbox_mode;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString logo_url;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString badge_url;
};

USTRUCT(BlueprintType)
struct FAFullGameData : public FAGameData{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString game_key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool active;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool block_purchases;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool player_progression;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool soft_currency;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString soft_currency_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int max_player_message_title_length;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int max_player_message_summary_length;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int genre;
};

USTRUCT(BlueprintType)
struct FACreateGamePayload {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int organisation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool sandbox_mode;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int steam_app_id = -1;
};

USTRUCT(BlueprintType)
struct FAUpdateGamePayload {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool sandbox_mode;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString game_key;
};

USTRUCT(BlueprintType)
struct FAGamesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAGameData> games;
};

USTRUCT(BlueprintType)
struct FAFullGameResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAFullGameData game;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAGamesResponseDelegate, FAGamesResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAFullGameResponseDelegate, FAFullGameResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminGamesRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Games", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetAllGamesForCurrentUser(const FAGamesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Games", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CreateGame(const FACreateGamePayload& GameData, const FAFullGameResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Games", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetGameInfo(int GameId, const FAFullGameResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Games", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateGame(int GameId, const FAUpdateGamePayload& GameData, const FAFullGameResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Games", meta = (AutoCreateRefTerm = "OnComplete"))
    static void DeleteGame(int GameId, const FLootLockerResponseCallback& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Games")
    static void SaveGameKey(const FString& Key);
    
    UAdminGamesRequestHandler();
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
