// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerMiscellaneousRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerTimeResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString date;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FTimeResponseDelegateBP, FLootLockerTimeResponse, Response);
DECLARE_DELEGATE_OneParam(FTimeResponseDelegate, FLootLockerTimeResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerMiscellaneousRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerMiscellaneousRequestHandler();
    
	static void GetServerTime(const FTimeResponseDelegateBP& OnCompletedRequestBP = FTimeResponseDelegateBP(), const FTimeResponseDelegate& OnCompletedRequest = FTimeResponseDelegate());
public:
	static ULootLockerHttpClient* HttpClient;
};