// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerMapsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerMapCamera {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float position = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float rotation = 0.0f;
};

USTRUCT(BlueprintType)
struct FLootLockerMapSpawnPoint {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float position = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float rotation = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMapCamera> cameras;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool player_access = false;
};

USTRUCT(BlueprintType)
struct FLootLockerMap {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int map_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMapSpawnPoint> spawn_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool player_access = false;
};

USTRUCT(BlueprintType)
struct FLootLockerGetMapsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMap> maps;
};

DECLARE_DELEGATE_OneParam(FGetMapsResponseDelegate, FLootLockerGetMapsResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerMapsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void GetMaps(const FLootLockerPlayerData& PlayerData, const FGetMapsResponseDelegate& OnCompletedRequest = FGetMapsResponseDelegate());
public:
    ULootLockerMapsRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
