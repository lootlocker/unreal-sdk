// Copyright (c) 2020 LootLocker

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
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString title;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString published_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString body;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString summary;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString category;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool alert;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool New;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString action;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString image;
};

USTRUCT(BlueprintType)
struct FMessagesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerMessage> messages;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessagesResponseDelegateBP, FMessagesResponse, Response);
DECLARE_DELEGATE_OneParam(FMessagesResponseDelegate, FMessagesResponse);

UCLASS()
class LOOTLOCKERSDK_API UMessagesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void GetMessages(const FMessagesResponseDelegateBP& OnCompletedRequestBP = FMessagesResponseDelegateBP(), const FMessagesResponseDelegate& OnCompletedRequest = FMessagesResponseDelegate());
public:
    UMessagesRequestHandler();
    
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
