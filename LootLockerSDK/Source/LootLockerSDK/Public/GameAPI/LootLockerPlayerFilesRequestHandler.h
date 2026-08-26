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
	/// Path to the file
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString file = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerFileUpdateRequest
{
	GENERATED_BODY()
	/// Path to the file
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
	FString key = "";
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
	FString key = "";
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

USTRUCT(BlueprintType)
struct FLootLockerPlayerFileMetadata
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString key = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString purpose = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool IsPublic = false;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerFileContentResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString url = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 size = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString created_at = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerFileRevisionsResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerFileContentResponse> revisions;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerPlayerFileMetadata file;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString current_revision_id = "";
};

/// @addtogroup PlayerFiles
/// @{
/** C++ response callback delegate; receives an @ref FLootLockerPlayerFileResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerUploadFileDelegate, FLootLockerPlayerFileResponse);

/** C++ response callback delegate; receives an @ref FLootLockerFileListResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerFileListDelegate, FLootLockerFileListResponse);

/** C++ response callback delegate; receives an @ref FLootLockerResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerFileDeletedDelegate, FLootLockerResponse);

/** C++ response callback delegate; receives an @ref FLootLockerPlayerFileRevisionsResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerFileRevisionsDelegate, FLootLockerPlayerFileRevisionsResponse);

/** C++ response callback delegate; receives an @ref FLootLockerPlayerFileContentResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerFileContentDelegate, FLootLockerPlayerFileContentResponse);

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULLPlayerFilesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULLPlayerFilesRequestHandler() {};

    static FString UploadFile(const FLootLockerPlayerData& PlayerData, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete);
	static FString UpdateFile(const FLootLockerPlayerData& PlayerData, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete);
	static FString ListFiles(const FLootLockerPlayerData& PlayerData, const FLootLockerFileListDelegate& OnComplete);
	static FString ListOtherPlayersPublicFiles(const FLootLockerPlayerData& PlayerData, const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete);
	static FString GetSingleFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete);
	static FString DeletePlayerFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete);
	static FString ListFileRevisions(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerFileRevisionsDelegate& OnComplete);
	static FString GetFileRevision(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FString& RevisionID, const FLootLockerFileContentDelegate& OnComplete);
	static FString PromoteFileRevision(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FString& RevisionID, const FLootLockerDefaultDelegate& OnComplete);
	static FString GetFileByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FLootLockerUploadFileDelegate& OnComplete);
	static FString ListFileRevisionsByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FLootLockerFileRevisionsDelegate& OnComplete);
	static FString GetFileRevisionByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FString& RevisionID, const FLootLockerFileContentDelegate& OnComplete);
	static FString PromoteFileRevisionByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FString& RevisionID, const FLootLockerDefaultDelegate& OnComplete);
	static FString DeletePlayerFileByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FLootLockerFileDeletedDelegate& OnComplete);
private:
	static void ParsePublicFlagOnFileList(TArray<FLootLockerPlayerFile>& ParsedFilesList, const TArray<TSharedPtr<FJsonValue>>& JsonFilesList);
};
