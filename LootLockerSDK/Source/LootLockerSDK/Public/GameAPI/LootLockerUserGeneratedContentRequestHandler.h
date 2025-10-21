// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerUserGeneratedContentRequestHandler.generated.h"

UENUM(BlueprintType)
enum class ELootLockerAssetFilePurpose : uint8
{
    PRIMARY_THUMBNAIL = 0,
    THUMBNAIL = 1,
    FILE = 2
};

USTRUCT(BlueprintType)
struct FLootLockerContentKeyValuePair {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAssetDataEntity {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString data = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAssetFile {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString url = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString purpose = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerAssetFilePurpose purpose_enum = ELootLockerAssetFilePurpose::FILE;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString filename = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString content_type = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int size = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidateData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int context_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerContentKeyValuePair> kv_storage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerContentKeyValuePair> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetDataEntity> data_entities;
};

USTRUCT(BlueprintType)
struct FLootLockerCreateAssetCandidateData {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetCandidateData data;
};

USTRUCT(BlueprintType)
struct FLootLockerUpdateAssetCandidateData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool completed = false;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetCandidateData data;
};

USTRUCT(BlueprintType)
struct FLootLockerResponseAssetCandidate {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Status = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Review_feedback = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetCandidateData Data;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetFile> Files; 
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Updated_at = "";
};

USTRUCT(BlueprintType)
struct FLootLockerCreateAssetCandidateResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerResponseAssetCandidate asset_candidate;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidateResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerResponseAssetCandidate asset_candidate;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidatesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerResponseAssetCandidate> asset_candidates;
};

DECLARE_DELEGATE_OneParam(FCreateAssetCandidateResponseDelegate, FLootLockerCreateAssetCandidateResponse);
DECLARE_DELEGATE_OneParam(FAssetCandidateResponseDelegate, FLootLockerAssetCandidateResponse);
DECLARE_DELEGATE_OneParam(FAssetCandidatesResponseDelegate, FLootLockerAssetCandidatesResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerUserGeneratedContentRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerUserGeneratedContentRequestHandler() {};

    static FString CreateAssetCandidate(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest);

    static FString CreateAssetCandidateAndMarkComplete(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest);

    static FString UpdateAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    static FString DeleteAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FResponseCallback& OnCompletedRequest);

    static FString GetAllAssetCandidates(const FLootLockerPlayerData& PlayerData, const FAssetCandidatesResponseDelegate& OnCompletedRequest);

    static FString GetAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    static FString AddFileToAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegate& OnCompletedRequest);

    static FString DeleteFileFromAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest);

    static void ParseFilePurposeEnumsInline(TArray<FLootLockerAssetFile>& Files);
};
