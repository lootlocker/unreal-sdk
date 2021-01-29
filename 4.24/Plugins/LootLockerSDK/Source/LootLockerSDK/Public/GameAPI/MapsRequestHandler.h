// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "MapsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FMapCamera {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float rotation;
};

USTRUCT(BlueprintType)
struct FMapSpawnPoint {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float rotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FMapCamera> cameras;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool player_access;
};

USTRUCT(BlueprintType)
struct FLootLockerMap {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int map_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FMapSpawnPoint> spawn_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool player_access;
};

USTRUCT(BlueprintType)
struct FGetMapsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMap> maps;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FGetMapsResponseDelegateBP, FGetMapsResponse, Response);
DECLARE_DELEGATE_OneParam(FGetMapsResponseDelegate, FGetMapsResponse);

UCLASS()
class LOOTLOCKERSDK_API UMapsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void GetMaps(const FGetMapsResponseDelegateBP& OnCompletedRequestBP = FGetMapsResponseDelegateBP(), const FGetMapsResponseDelegate& OnCompletedRequest = FGetMapsResponseDelegate());
public:
    UMapsRequestHandler();
    
    static UHttpClient* HttpClient;
};
