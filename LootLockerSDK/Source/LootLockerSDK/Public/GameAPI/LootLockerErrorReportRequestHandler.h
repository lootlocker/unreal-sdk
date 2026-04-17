// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerErrorReportRequestHandler.generated.h"

//==================================================
// Request Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerErrorReportRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString user_description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString client_request_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString server_request_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString trace_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 status_code = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString message;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString endpoint;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString http_method;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString response_json_body;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> response_headers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString request_body;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> request_headers;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 retry_attempts = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float request_duration_seconds = 0.0f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString server_timestamp;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString client_timestamp;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString player_ulid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString sdk_version;
};

//==================================================
// Handler
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerErrorReportRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    /**
     * Send a report about a failed LootLocker request to the dedicated error-report endpoint.
     * @param PlayerData Player session data used to authenticate the request
     * @param Report Report data populated from the failed request history
     * @param OnComplete Delegate called when the request completes
     * @return A unique id for this request used to match callbacks
     */
    static FString ReportSDKError(const FLootLockerPlayerData& PlayerData, const FLootLockerErrorReportRequest& Report, const FLootLockerResponseDelegate& OnComplete);
};
