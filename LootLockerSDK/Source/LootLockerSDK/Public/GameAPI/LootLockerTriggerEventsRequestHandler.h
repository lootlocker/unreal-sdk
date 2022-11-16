// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerTriggerEventsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerTriggerEvent {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerTriggerEventResponse : public FLootLockerSubmitXpResponse {
    GENERATED_BODY()
        FLootLockerAsset granted_assets;
};

USTRUCT(BlueprintType)
struct FLootLockerTriggersResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> triggers;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FTriggerEventResponseDelegateBP, FLootLockerTriggerEventResponse, Value);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTriggersResponseDelegateBP, FLootLockerTriggersResponse, Value);
DECLARE_DELEGATE_OneParam(FTriggerEventResponseDelegate, FLootLockerTriggerEventResponse);
DECLARE_DELEGATE_OneParam(FTriggersResponseDelegate, FLootLockerTriggersResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerTriggerEventsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnCompletedRequestBP = FTriggerEventResponseDelegateBP(), const FTriggerEventResponseDelegate& OnCompletedRequest = FTriggerEventResponseDelegate());
    
    static void GetTriggeredEvents(const FTriggersResponseDelegateBP& OnCompletedRequestBP = FTriggersResponseDelegateBP(), const FTriggersResponseDelegate& OnCompletedRequest = FTriggersResponseDelegate());
public:
    ULootLockerTriggerEventsRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
