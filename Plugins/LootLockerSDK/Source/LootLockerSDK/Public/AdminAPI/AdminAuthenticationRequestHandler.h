// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AdminAuthenticationRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAGame {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool is_demo;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString logo_url;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString badge_url;
};

USTRUCT(BlueprintType)
struct FAOrganization {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAGame> games;
};

USTRUCT(BlueprintType)
struct FAUser {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAOrganization> organisations;
};

USTRUCT(BlueprintType)
struct FAUserData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString email;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString password;
};

USTRUCT(BlueprintType)
struct FAVerifyUserData {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString mfa_key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString secret;
};

USTRUCT(BlueprintType)
struct FAAuthenticationResponse : public FLootLockerResponse {
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString auth_token;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FAUser user;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString mfa_key;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAAuthenticationResponseDelegate, FAAuthenticationResponse, Response);

UCLASS()
class LOOTLOCKERSDK_API UAdminAuthenticationRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Authentication", meta = (AutoCreateRefTerm = "OnComplete"))
    static void AuthenticateUser(const FAUserData& UserData, const FAAuthenticationResponseDelegate& OnComplete);
    UFUNCTION(BlueprintCallable, Category = "LootLocker Admin | Authentication", meta = (AutoCreateRefTerm = "OnComplete"))
    static void VerifyUserCode(const FAVerifyUserData& UserData, const FAAuthenticationResponseDelegate& OnComplete);
    
    UAdminAuthenticationRequestHandler();
private:
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
