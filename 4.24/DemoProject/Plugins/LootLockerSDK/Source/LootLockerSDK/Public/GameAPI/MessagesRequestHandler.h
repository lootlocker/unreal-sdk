// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "MessagesRequestHandler.generated.h"

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
    bool alert;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool New;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString action;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString image;
};

USTRUCT(BlueprintType)
struct FMessagesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMessage> messages;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FMessagesResponseDelegateBP, FMessagesResponse, Response);
DECLARE_DELEGATE_OneParam(FMessagesResponseDelegate, FMessagesResponse);

UCLASS()
class LOOTLOCKERSDK_API UMessagesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void GetMessages(const FMessagesResponseDelegateBP& OnCompletedRequestBP = FMessagesResponseDelegateBP(), const FMessagesResponseDelegate& OnCompletedRequest = FMessagesResponseDelegate());
public:
    UMessagesRequestHandler();
    
    static UHttpClient* HttpClient;
};
