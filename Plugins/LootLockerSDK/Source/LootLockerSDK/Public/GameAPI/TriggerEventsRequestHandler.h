// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "GameAPI/PlayerRequestHandler.h"
#include "TriggerEventsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FTriggerEvent {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
};

USTRUCT(BlueprintType)
struct FTriggerEventResponse : public FSubmitXpResponse {
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FTriggersResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> triggers;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggerEventResponseDelegateBP, FTriggerEventResponse, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTriggersResponseDelegateBP, FTriggersResponse, Value);
DECLARE_DELEGATE_OneParam(FTriggerEventResponseDelegate, FTriggerEventResponse);
DECLARE_DELEGATE_OneParam(FTriggersResponseDelegate, FTriggersResponse);

UCLASS()
class LOOTLOCKERSDK_API UTriggerEventsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void TriggerEvent(const FTriggerEvent& Event, const FTriggerEventResponseDelegateBP& OnCompletedRequestBP = FTriggerEventResponseDelegateBP(), const FTriggerEventResponseDelegate& OnCompletedRequest = FTriggerEventResponseDelegate());
    
    static void GetTriggeredEvents(const FTriggersResponseDelegateBP& OnCompletedRequestBP = FTriggersResponseDelegateBP(), const FTriggersResponseDelegate& OnCompletedRequest = FTriggersResponseDelegate());
public:
    UTriggerEventsRequestHandler();
    
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
