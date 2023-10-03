// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerErrorData
{
    GENERATED_BODY()
	// A descriptive code identifying the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code;
    // A link to further documentation on the error.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Doc_url;
    // A unique identifier of the request to use in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Request_id;
    // A unique identifier for tracing the request through LootLocker systems, use this in contact with support.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Trace_id;
    // A free text description of the problem and potential suggestions for fixing it
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Message;
};

USTRUCT(BlueprintType)
struct FLootLockerResponse
{
    GENERATED_BODY()
    // Whether this request was a success
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool success = false;
    // HTTP Status code from the request to LootLockers backend 
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int StatusCode = 0;
    // Raw text/http body from the server response
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString FullTextFromServer;
    // If this request was not a success, this structure holds all the information needed to identify the problem
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerErrorData ErrorData;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultDelegate, FLootLockerResponse);

USTRUCT(BlueprintType)
struct FLootLockerKeyBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Next_Cursor = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Previous_Cursor = "";
};

USTRUCT(BlueprintType)
struct FLootLockerIndexBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Next_Cursor = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Previous_Cursor = 0;
};

class LootLockerResponseFactory
{
public:
    // Construct a standardized error response
    template<typename T>
    static T Error(FString ErrorMessage, int StatusCode = 0)
    {
        T ErrorResponse;
        ErrorResponse.success = false;
        ErrorResponse.StatusCode = StatusCode;
        ErrorResponse.FullTextFromServer = "{ \"message\": \"" + ErrorMessage + "\"}";
        ErrorResponse.ErrorData.Message = ErrorMessage;
        return ErrorResponse;
    }
};