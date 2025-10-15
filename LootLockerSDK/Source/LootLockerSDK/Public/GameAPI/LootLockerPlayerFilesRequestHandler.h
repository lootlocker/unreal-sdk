// Copyright LootLocker AB

#pragma once
#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerPlayerFilesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerFileUploadRequest
{
    GENERATED_BODY()
	// Path to the file
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString file = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerFileUpdateRequest
{
	GENERATED_BODY()
	// Path to the file
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString file = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerFileResponse : public FLootLockerResponse
{
    GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString message = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString revision_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 size = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString purpose = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url_expires_at = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at = "";
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
	FString revision_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 size = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url_expires_at = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at = "";
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

DECLARE_DELEGATE_OneParam(FLootLockerUploadFileDelegate, FLootLockerPlayerFileResponse);

DECLARE_DELEGATE_OneParam(FLootLockerFileListDelegate, FLootLockerFileListResponse);

DECLARE_DELEGATE_OneParam(FLootLockerFileDeletedDelegate, FLootLockerResponse);

UCLASS()
class LOOTLOCKERSDK_API ULLPlayerFilesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULLPlayerFilesRequestHandler() {};

    static void UploadFile(const FLootLockerPlayerData& PlayerData, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete);
	static void UpdateFile(const FLootLockerPlayerData& PlayerData, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete);
	static void ListFiles(const FLootLockerPlayerData& PlayerData, const FLootLockerFileListDelegate& OnComplete);
	static void ListOtherPlayersPublicFiles(const FLootLockerPlayerData& PlayerData, const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete);
	static void GetSingleFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete);
	static void DeletePlayerFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete);
private:
	static void ParsePublicFlagOnFileList(TArray<FLootLockerPlayerFile>& ParsedFilesList, const TArray<TSharedPtr<FJsonValue>>& JsonFilesList);
};
