// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminPlayerRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAPlayerData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString steamId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString psn_account_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int banned;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Public;
};

USTRUCT(BlueprintType)
struct FAFullPlayerData : public FAPlayerData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString last_seen;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString creation_date;
};

USTRUCT(BlueprintType)
struct FAPlayerScoreData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int score;
};

USTRUCT(BlueprintType)
struct FASteamPlayerData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString avatar;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString profile_url;
};

USTRUCT(BlueprintType)
struct FAInventoryItem {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString player_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString game_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString reserved;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString source;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString variation_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool refundable;
};

USTRUCT(BlueprintType)
struct FACurrency {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString balance;
};

USTRUCT(BlueprintType)
struct FAOrder {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString player_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString game_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString status;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString deleted_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString status_name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAInventoryItem> items;
};

USTRUCT(BlueprintType)
struct FAPlayerSearchResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int offset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAPlayerData> players;
};

USTRUCT(BlueprintType)
struct FAPlayersResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAFullPlayerData> players;
};

USTRUCT(BlueprintType)
struct FAPlayerScoreResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int score;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString last_level_up;
};

USTRUCT(BlueprintType)
struct FASteamPlayerResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FASteamPlayerData player;
};

USTRUCT(BlueprintType)
struct FAInventoryItemsResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAInventoryItem> inventory;
};

USTRUCT(BlueprintType)
struct FACurrenciesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FACurrency> currencies;
};

USTRUCT(BlueprintType)
struct FAOrdersResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAOrder> orders;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAPlayerSearchResponseDelegate, FAPlayerSearchResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAPlayersResponseDelegate, FAPlayersResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAPlayerScoreResponseDelegate, FAPlayerScoreResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FASteamPlayerResponseDelegate, FASteamPlayerResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAInventoryItemsResponseDelegate, FAInventoryItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FACurrenciesResponseDelegate, FACurrenciesResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAOrdersResponseDelegate, FAOrdersResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminPlayerRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void SearchForPlayer(int GameId, const FString& Query, const FAPlayerSearchResponseDelegate& OnComplete, int Offset = 0);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetPlayer(int GameId, int PlayerId, const FAPlayersResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetPlayerScore(int GameId, int PlayerId, const FAPlayerScoreResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void AddPlayerScore(int Score, int GameId, int PlayerId, const FAPlayerScoreResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void ResetPlayerScore(int GameId, int PlayerId, const FAPlayerScoreResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetPlayerSteamProfile(int GameId, const FString& SteamId, const FASteamPlayerResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetPlayerInventory(int GameId, int PlayerId, const FAInventoryItemsResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void RefundPlayerPurchase(int GameId, int PlayerId, int ItemId, const FAInventoryItemsResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetPlayerCurrencies(int GameId, int PlayerId, const FACurrenciesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetPlayerOrders(int GameId, int PlayerId, const FAOrdersResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void SetPlayerProfilePublic(bool Public, int GameId, int PlayerId, const FLootLockerResponseCallback& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Players", meta = (AutoCreateRefTerm = "OnComplete"))
    static void ResetPlayerProfile(int GameId, int PlayerId, const FLootLockerResponseCallback& OnComplete);
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
