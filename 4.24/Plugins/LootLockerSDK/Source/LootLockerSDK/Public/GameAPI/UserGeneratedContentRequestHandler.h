// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "UserGeneratedContentRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FContentKeyValuePair {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
};

USTRUCT(BlueprintType)
struct FAssetDataEntity {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString data;
};

USTRUCT(BlueprintType)
struct FAssetCandidate {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int context_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FContentKeyValuePair> kv_storage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FContentKeyValuePair> filters;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FAssetDataEntity> data_entities;
};

USTRUCT(BlueprintType)
struct FResponseAssetCandidate {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString status;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString review_feedback;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FAssetCandidate data;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> files; 
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString updated_at;
};

USTRUCT(BlueprintType)
struct FCreateAssetCandidateResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_candidate_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FResponseAssetCandidate asset_candidate;
};

USTRUCT(BlueprintType)
struct FAssetCandidateResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FResponseAssetCandidate asset_candidate;
};

USTRUCT(BlueprintType)
struct FAssetCandidatesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FResponseAssetCandidate> asset_candidates;
};

UENUM(BlueprintType)
enum class EAssetFilePurpose : uint8
{
    PRIMARY_THUMBNAIL = 0,
    THUMBNAIL = 1,
    FILE = 2
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FCreateAssetCandidateResponseDelegateBP, FCreateAssetCandidateResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCandidateResponseDelegateBP, FAssetCandidateResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetCandidatesResponseDelegateBP, FAssetCandidatesResponse, Response);
DECLARE_DELEGATE_OneParam(FCreateAssetCandidateResponseDelegate, FCreateAssetCandidateResponse);
DECLARE_DELEGATE_OneParam(FAssetCandidateResponseDelegate, FAssetCandidateResponse);
DECLARE_DELEGATE_OneParam(FAssetCandidatesResponseDelegate, FAssetCandidatesResponse);

UCLASS()
class LOOTLOCKERSDK_API UUserGeneratedContentRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void CreateAssetCandidate(const FAssetCandidate& AsssetCandidate, const FCreateAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FCreateAssetCandidateResponseDelegateBP(), const FCreateAssetCandidateResponseDelegate& OnCompletedRequest = FCreateAssetCandidateResponseDelegate());
    
    static void UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());
    
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
    
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP = FAssetCandidatesResponseDelegateBP(), const FAssetCandidatesResponseDelegate& OnCompletedRequest = FAssetCandidatesResponseDelegate());
    
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());
    
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
    
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
public:
    UUserGeneratedContentRequestHandler();
    
    static UHttpClient* HttpClient;
};
