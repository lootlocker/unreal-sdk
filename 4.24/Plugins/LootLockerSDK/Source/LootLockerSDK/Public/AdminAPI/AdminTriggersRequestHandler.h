// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminTriggersRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FATriggerReward {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_variation_id = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString asset_image = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString asset_name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int score = -1;
};

USTRUCT(BlueprintType)
struct FATriggerPayload {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int times;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool grant_all;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FATriggerReward> rewards;
};

USTRUCT(BlueprintType)
struct FATrigger : public FATriggerPayload {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
};

USTRUCT(BlueprintType)
struct FATriggersResponse : public FLootLockerResponse {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FATrigger> triggers;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FATriggersResponseDelegate, FATriggersResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminTriggersRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Triggers", meta = (AutoCreateRefTerm = "OnComplete"))
    static void ListTriggers(int GameId, const FATriggersResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Triggers", meta = (AutoCreateRefTerm = "OnComplete"))
    static void CreateTrigger(int GameId, const FATriggerPayload& TriggerData, const FATriggersResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Triggers", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateTrigger(int GameId, int TriggerId, const FATriggerPayload& TriggerData, const FATriggersResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Triggers", meta = (AutoCreateRefTerm = "OnComplete"))
    static void DeleteTrigger(int GameId, int TriggerId, const FATriggersResponseDelegate& OnComplete);
    
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
