// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerTriggersRequestHandler.generated.h"

//==================================================
// Enum Definitions
//==================================================

/**
 * Possible reasons for a trigger key to fail
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerTriggerFailureReasons : uint8
{
    Trigger_limit_reached = 0,
    Key_not_found = 1,
    Reward_not_found = 2,
};

//==================================================
// Data Type Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerSuccessfulKey
{
    GENERATED_BODY()
    /**
     * The key that was successfully executed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
};

/**
 * 
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerFailedKey
{
    GENERATED_BODY()
    /**
     * The key that failed
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
    /**
     * The reason for the key failing.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerTriggerFailureReasons Reason = ELootLockerTriggerFailureReasons::Key_not_found;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerInvokeTriggersByKeyRequest
{
    GENERATED_BODY()
    /**
     * The keys of the triggers that should be invoked
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Keys;
};


//==================================================
// Response Definitions
//==================================================

/**
 * The result of the invoked triggers
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerInvokeTriggersByKeyResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * A list of keys that failed invocation together with the reason for failure
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFailedKey> Failed_keys;
    /**
     * A list of keys that were successfully invoked
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerSuccessfulKey> Successful_keys;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for invoking a set of triggers by key
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInvokeTriggersByKeyResponseBP, FLootLockerInvokeTriggersByKeyResponse, Response);


//==================================================
// API Class Definition
//==================================================
/**
 * C++ response delegate for invoking a set of triggers by key
 */
DECLARE_DELEGATE_OneParam(FLootLockerInvokeTriggersByKeyResponseDelegate, FLootLockerInvokeTriggersByKeyResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerTriggersRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void InvokeTriggersByKey(const TArray<FString>& KeysToInvoke, const FLootLockerInvokeTriggersByKeyResponseBP& OnCompleteBP = FLootLockerInvokeTriggersByKeyResponseBP(), const FLootLockerInvokeTriggersByKeyResponseDelegate& OnComplete = FLootLockerInvokeTriggersByKeyResponseDelegate());

    ULootLockerTriggersRequestHandler();

    static ULootLockerHttpClient* HttpClient;
};
