// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDefaultResponseBP, FLootLockerResponse, Var);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultDelegate, FLootLockerResponse);

USTRUCT(BlueprintType)
struct FLootLockerKeyBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int Total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString Next_Cursor = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString Previous_Cursor = "";
};

USTRUCT(BlueprintType)
struct FLootLockerIndexBasedPagination
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int32 Total = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int32 Next_Cursor = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    int32 Previous_Cursor = 0;
};