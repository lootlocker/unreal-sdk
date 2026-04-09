// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerFailedRequestReport.generated.h"

/**
 * Data structure for storing information about failed requests for the purpose of error reporting.
 * This is not used for successful requests to avoid unnecessary memory usage.
 */
USTRUCT(BlueprintType)
struct FLootLockerFailedRequestReport
{
    GENERATED_BODY()

    /** Optional developer-provided description of the events leading up to the failure */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString user_description;
    /** The unique client-generated identifier for the request */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString client_request_id;
    /** The unique server-generated identifier for the request (from error data) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString server_request_id;
    /** The unique trace identifier for the request (from error data) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString trace_id;
    /** The HTTP status code returned by the server (or 0 if no response) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 status_code = 0;
    /** The error message from the server or client */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString message;
    /** The endpoint URL the request was sent to */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString endpoint;
    /** The HTTP method used for the request */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString http_method;
    /** The raw JSON body of the response (obfuscated) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString response_json_body;
    /** The response headers returned by the server */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> response_headers;
    /** The raw JSON body of the request (obfuscated) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString request_body;
    /** The request headers that were sent (sensitive headers removed) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> request_headers;
    /** The number of times the request was retried before ultimately failing */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 retry_attempts = 0;
    /** The duration in seconds from when the request was first sent to when it ultimately failed */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    float request_duration_seconds = 0.0f;
    /** The server timestamp from the Date response header (ISO 8601) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString server_timestamp;
    /** The client-side timestamp of when the request was made (ISO 8601) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString client_timestamp;
    /** The ULID of the player for whom the request was made */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString player_ulid;
};
