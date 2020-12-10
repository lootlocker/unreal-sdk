// Fill out your copyright notice in the Description page of Project Settings.

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
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float rotation;
};

USTRUCT(BlueprintType)
struct FMapSpawnPoint {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float position;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float rotation;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FMapCamera> cameras;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool player_access;
};

USTRUCT(BlueprintType)
struct FLootLockerMap {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int map_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FMapSpawnPoint> spawn_points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool player_access;
};

USTRUCT(BlueprintType)
struct FGetMapsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMap> maps;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetMapsResponseDelegateBP, FGetMapsResponse, Response);
DECLARE_DELEGATE_OneParam(FGetMapsResponseDelegate, FGetMapsResponse);

UCLASS()
class LOOTLOCKERSDK_API UMapsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void GetMaps(const FGetMapsResponseDelegateBP& OnCompletedRequestBP = FGetMapsResponseDelegateBP(), const FGetMapsResponseDelegate& OnCompletedRequest = FGetMapsResponseDelegate());
public:
    UMapsRequestHandler();
    
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
