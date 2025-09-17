// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FCreateAssetCandidateResponseDelegateBP, FLootLockerCreateAssetCandidateResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCandidateResponseDelegateBP, FLootLockerAssetCandidateResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCandidatesResponseDelegateBP, FLootLockerAssetCandidatesResponse, Response);
DECLARE_DELEGATE_OneParam(FCreateAssetCandidateResponseDelegate, FLootLockerCreateAssetCandidateResponse);
DECLARE_DELEGATE_OneParam(FAssetCandidateResponseDelegate, FLootLockerAssetCandidateResponse);
DECLARE_DELEGATE_OneParam(FAssetCandidatesResponseDelegate, FLootLockerAssetCandidatesResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerUserGeneratedContentRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void CreateAssetCandidate(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidate, const FCreateAssetCandidateResponseDelegateBP&
        OnCompletedRequestBP = FCreateAssetCandidateResponseDelegateBP(), const FCreateAssetCandidateResponseDelegate&
        OnCompletedRequest = FCreateAssetCandidateResponseDelegate());

    static void CreateAssetCandidateAndMarkComplete(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidate, const FCreateAssetCandidateResponseDelegateBP&
        OnCompletedRequestBP = FCreateAssetCandidateResponseDelegateBP(), const FCreateAssetCandidateResponseDelegate&
        OnCompletedRequest = FCreateAssetCandidateResponseDelegate());

    static void UpdateAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());

    static void DeleteAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());

    static void GetAllAssetCandidates(const FLootLockerPlayerData& PlayerData, const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP = FAssetCandidatesResponseDelegateBP(), const FAssetCandidatesResponseDelegate& OnCompletedRequest = FAssetCandidatesResponseDelegate());

    static void GetAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());

    static void AddFileToAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());

    static void DeleteFileFromAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());

    static void ParseFilePurposeEnumsInline(TArray<FLootLockerAssetFile>& Files);
public:
    ULootLockerUserGeneratedContentRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
