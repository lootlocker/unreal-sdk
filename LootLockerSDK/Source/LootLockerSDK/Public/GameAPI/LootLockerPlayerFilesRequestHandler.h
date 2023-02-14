// Copyright LootLocker AB

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerPlayerFilesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerFileUploadRequest
{
    GENERATED_BODY()
	// Path to the file
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString file;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerFileUpdateRequest
{
	GENERATED_BODY()
	// Path to the file
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString file;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerFileResponse : public FLootLockerResponse
{
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString message;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString revision_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 size = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString purpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url_expires_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerFile
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString revision_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 size = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url_expires_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerFileListResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerFile> items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerUploadFileBP, FLootLockerPlayerFileResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerUploadFileDelegate, FLootLockerPlayerFileResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFileListBP, FLootLockerFileListResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerFileListDelegate, FLootLockerFileListResponse);

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFileDeletedBP, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerFileDeletedDelegate, FLootLockerResponse);

UCLASS()
class LOOTLOCKERSDK_API ULLPlayerFilesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
    ULLPlayerFilesRequestHandler();
    static ULootLockerHttpClient* HttpClient;
    static void UploadFile(const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileBP& OnCompleteBP = FLootLockerUploadFileBP(), const FLootLockerUploadFileDelegate& OnComplete = FLootLockerUploadFileDelegate());
    static void UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnCompleteBP = FLootLockerUploadFileBP(), const FLootLockerUploadFileDelegate& OnComplete = FLootLockerUploadFileDelegate());
	static void ListFiles(const FLootLockerFileListBP& OnCompleteBP, const FLootLockerFileListDelegate& OnComplete);
	static void ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP = FLootLockerFileListBP(), const FLootLockerFileListDelegate& OnComplete = FLootLockerFileListDelegate());
	static void GetSingleFile(const int32 FileID, const FLootLockerUploadFileBP& OnCompleteBP = FLootLockerUploadFileBP(), const FLootLockerUploadFileDelegate& OnComplete = FLootLockerUploadFileDelegate());
	static void DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP& OnCompleteBP = FLootLockerFileDeletedBP(), const FLootLockerFileDeletedDelegate& OnComplete = FLootLockerFileDeletedDelegate());
private:
	static void ParsePublicFlagOnFileList(TArray<FLootLockerPlayerFile>& ParsedFilesList, const TArray<TSharedPtr<FJsonValue>>& JsonFilesList);
};
