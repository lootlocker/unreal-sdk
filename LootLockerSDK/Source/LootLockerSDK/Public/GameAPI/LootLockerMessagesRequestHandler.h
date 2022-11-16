// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerMessagesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerMessage {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString title;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString published_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString body;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString summary;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString category;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool alert = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool New = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString action;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString image;
};

USTRUCT(BlueprintType)
struct FLootLockerMessagesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMessage> messages;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FMessagesResponseDelegateBP, FLootLockerMessagesResponse, Response);
DECLARE_DELEGATE_OneParam(FMessagesResponseDelegate, FLootLockerMessagesResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerMessagesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void GetMessages(const FMessagesResponseDelegateBP& OnCompletedRequestBP = FMessagesResponseDelegateBP(), const FMessagesResponseDelegate& OnCompletedRequest = FMessagesResponseDelegate());
public:
    ULootLockerMessagesRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
