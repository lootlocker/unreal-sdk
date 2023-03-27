// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerConfig.h"

#include "LootLockerServerPlayerFileRequestHandler.generated.h"

class ULootLockerHttpClient;

USTRUCT(BlueprintType)
struct FLootLockerServerPlayerFileResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Id = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Name = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Size = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Purpose = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Url = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Url_expires_at = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Created_at = "";

	UPROPERTY(BlueprintReadOnly, Category = "LootLocker")
	FString FileContentAsString = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerListPlayerFilesResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerServerPlayerFileResponse> Items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerListPlayerFilesResponseDelegateBP, FLootLockerServerListPlayerFilesResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerGetPlayerFileResponseDelegateBP, FLootLockerResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerUploadPlayerFileResponseDelegateBP, FLootLockerServerPlayerFileResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServerDeletePlayerFileResponseDelegateBP, FLootLockerResponse, Response);

DECLARE_DELEGATE_OneParam(FLootLockerServerListPlayerFilesResponseDelegate, FLootLockerServerListPlayerFilesResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerGetPlayerFileResponseDelegate, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerUploadPlayerFileResponseDelegate, FLootLockerServerPlayerFileResponse);
DECLARE_DELEGATE_OneParam(FLootLockerServerDeletePlayerFileResponseDelegate, FLootLockerResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerServerPlayerFileRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerServerPlayerFileRequestHandler();
	
	static void ListPlayerFiles(const FString& PlayerId, const FLootLockerServerListPlayerFilesResponseDelegateBP& OnCompletedRequestBP = FLootLockerServerListPlayerFilesResponseDelegateBP(), const FLootLockerServerListPlayerFilesResponseDelegate& OnCompletedRequest = FLootLockerServerListPlayerFilesResponseDelegate());
	static void GetPlayerFile(const FString& PlayerId, int FileId, const FLootLockerServerGetPlayerFileResponseDelegateBP& OnCompletedRequestBP = FLootLockerServerGetPlayerFileResponseDelegateBP(), const FLootLockerServerGetPlayerFileResponseDelegate& OnCompletedRequest = FLootLockerServerGetPlayerFileResponseDelegate());

	static void UploadPlayerFile(const FString& PlayerId, const FString& FileName, const FString& ContentAsString, const FString& Purpose, const FLootLockerServerUploadPlayerFileResponseDelegateBP& OnCompletedRequestBP = FLootLockerServerUploadPlayerFileResponseDelegateBP(), const FLootLockerServerUploadPlayerFileResponseDelegate& OnCompletedRequest = FLootLockerServerUploadPlayerFileResponseDelegate());

	static void DeletePlayerFile(const FString& PlayerId, int FileId, const FLootLockerServerDeletePlayerFileResponseDelegateBP& OnCompletedRequestBP = FLootLockerServerDeletePlayerFileResponseDelegateBP(), const FLootLockerServerDeletePlayerFileResponseDelegate& OnCompletedRequest = FLootLockerServerDeletePlayerFileResponseDelegate());

public:
	static ULootLockerHttpClient* HttpClient;
};
