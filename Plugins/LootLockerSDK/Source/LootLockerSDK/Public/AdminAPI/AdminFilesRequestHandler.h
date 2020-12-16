// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminFilesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAFileAssociationData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int game_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int item_id = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int player_id = -1;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FAFile {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString url;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int size;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> tags;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString updated_at;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString attachment_type;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int attachment_id;
};

USTRUCT(BlueprintType)
struct FAFileTagsData {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FString> tags;
};

USTRUCT(BlueprintType)
struct FAFileResponse : public FLootLockerResponse {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAFile file;
};

USTRUCT(BlueprintType)
struct FAFilesResponse : public FLootLockerResponse {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAFile> files;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAFileResponseDelegate, FAFileResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAFilesResponseDelegate, FAFilesResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminFilesRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Files", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UploadFile(const FString& FilePath, const FAFileAssociationData& AssociationData, const FAFileResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Files", meta = (AutoCreateRefTerm = "OnComplete"))
    static void GetFiles(int GameId, const FString& Filter, const FAFilesResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Files", meta = (AutoCreateRefTerm = "OnComplete"))
    static void UpdateFileTags(int GameId, int FileId, const FAFileTagsData& TagsData, const FAFileResponseDelegate& OnComplete);
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Files", meta = (AutoCreateRefTerm = "OnComplete"))
    static void DeleteFile(int GameId, int FileId, const FLootLockerResponseCallback& OnComplete);
    
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
