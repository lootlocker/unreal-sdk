// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerResponse.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerResponse
{
	GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    bool success = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int ServerCallStatusCode = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString FullTextFromServer;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString session_token;
};

USTRUCT(BlueprintType)
struct FLootLockerKeyBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int Total;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString NextCursor;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString PreviousCursor;
};

USTRUCT(BlueprintType)
struct FLootLockerIndexBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int32 Total;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int32 NextCursor;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int32 PreviousCursor;
};