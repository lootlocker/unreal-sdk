// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerUserGeneratedContentRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerContentKeyValuePair {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetDataEntity {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString data;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetCandidateData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
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
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString status;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString review_feedback;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetCandidateData data;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> files; 
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString updated_at;
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

UENUM(BlueprintType)
enum class ELootLockerAssetFilePurpose : uint8
{
    PRIMARY_THUMBNAIL = 0,
    THUMBNAIL = 1,
    FILE = 2
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
    static void CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidate, const FCreateAssetCandidateResponseDelegateBP&
                                         OnCompletedRequestBP = FCreateAssetCandidateResponseDelegateBP(), const FCreateAssetCandidateResponseDelegate&
                                         OnCompletedRequest = FCreateAssetCandidateResponseDelegate());
    
    static void UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());
    
    static void DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
    
    static void GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP = FAssetCandidatesResponseDelegateBP(), const FAssetCandidatesResponseDelegate& OnCompletedRequest = FAssetCandidatesResponseDelegate());
    
    static void GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP = FAssetCandidateResponseDelegateBP(), const FAssetCandidateResponseDelegate& OnCompletedRequest = FAssetCandidateResponseDelegate());
    
    static void AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
    
    static void DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
public:
    ULootLockerUserGeneratedContentRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
