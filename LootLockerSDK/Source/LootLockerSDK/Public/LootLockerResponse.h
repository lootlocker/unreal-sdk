// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerErrorData.h"
#include "LootLockerRequestContext.h"
#include "LootLockerResponse.generated.h"

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
    FString FullTextFromServer = "";
    // If this request was not a success, this structure holds all the information needed to identify the problem
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerErrorData ErrorData;
    // Context for the request
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerRequestContext Context;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultDelegate, FLootLockerResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FResponseCallbackBP, FLootLockerResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerResponseCallback, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FResponseCallback, FLootLockerResponse);

USTRUCT(BlueprintType)
struct FLootLockerKeyBasedPagination
{
    GENERATED_BODY()
    /*
     * How many entries in total exists in the paginated list
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Total = 0;
    /*
     * The cursor to use for fetching the set of entries immediately succeeding this set of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Next_Cursor = "";
    /*
     * The cursor to use for fetching the set of entries immediately preceding this set of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Previous_Cursor = "";
};

USTRUCT(BlueprintType)
struct FLootLockerIndexBasedPagination
{
    GENERATED_BODY()
    /*
     * How many entries in total exists in the paginated list
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Total = 0;
    /*
     * The cursor to use for fetching the set of entries immediately succeeding this set of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Next_Cursor = 0;
    /*
     * The cursor to use for fetching the set of entries immediately preceding this set of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Previous_Cursor = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerExtendedPaginationError
{
    GENERATED_BODY()
    /*
     * Which field in the pagination that this error relates to
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Field = "";
    /*
     * The error message in question
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Message = "";
};

USTRUCT(BlueprintType)
struct FLootLockerExtendedIndexBasedPagination
{
    GENERATED_BODY()
    /*
     * How many entries in total exists in the paginated list
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Total = 0;
    /*
     * How many entries (counting from the beginning of the paginated list) from the first entry that the current page starts at
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Offset = 0;
    /*
     * Number of entries on each page
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Per_page = 0;
    /*
     * The page index to use for fetching the last page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Last_page = 0;
    /*
     * The page index used for fetching this page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Current_page = 0;
    /*
     * The page index to use for fetching the page of entries immediately succeeding this page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Next_page = "";
    /*
     * The page index to use for fetching the page of entries immediately preceding this page of entries
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Prev_page = "";
    /*
     * List of pagination errors (if any). These are errors specifically related to the pagination of the entry set.
     **/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerExtendedPaginationError> Errors;
};

/**
 * Static defines of the different predefined error status codes that can occur in responses
 */
struct LootLockerStaticRequestErrorStatusCodes
{
    static const int LL_ERROR_UNDOCUMENTED = 0;
    static const int LL_ERROR_INVALID_HTTP = -1;
    static const int LL_ERROR_INVALID_INPUT = -2;
    static const int LL_ERROR_PARSE_ERROR = -3;
    static const int LL_UNDEFINED_BEHAVIOUR_ERROR = -4;
};

class LootLockerResponseFactory
{
public:
    // Construct a standardized error response
    template<typename T>
    static T Error(FString ErrorMessage, int StatusCode = 0, const FString& PlayerUlid = "") 
    {
        T ErrorResponse;
        ErrorResponse.success = false;
        ErrorResponse.StatusCode = StatusCode;
        ErrorResponse.FullTextFromServer = "{ \"message\": \"" + ErrorMessage + "\"}";
        ErrorResponse.ErrorData.Message = ErrorMessage;
        ErrorResponse.Context.PlayerUlid = PlayerUlid;
        
        return ErrorResponse;
    }
};
