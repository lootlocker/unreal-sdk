// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerProgressionsRequestHandler.generated.h"

/* PURE DATA STRUCTS */
USTRUCT(BlueprintType)
struct FLootLockerProgression
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        bool Active = false;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerProgression
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Step = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Points = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Previous_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Next_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Last_Level_Up = "";
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterProgression
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Step = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Points = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Previous_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Next_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Last_Level_Up = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAssetReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int Asset_Id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int Asset_Variation_Id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int Asset_Rental_Option_Id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionPointsReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Amount = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionResetReward
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRewards
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerProgressionPointsReward> Progression_Points_Rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerProgressionResetReward> Progression_Reset_Rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerAssetReward> Asset_Rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerAwardedTier
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Step = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Points_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerRewards Rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionTier
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Step = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Points_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerRewards Rewards;
};

/* RESPONSE STRUCTS */

USTRUCT(BlueprintType)
struct FLootLockerProgressionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        bool Active = false;
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedProgressionsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerKeyBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerProgression> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerGenericProgressionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Id = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Progression_Name = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Step = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Points = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Previous_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        int32 Next_Threshold = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FString Last_Level_Up = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedGenericProgressionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerKeyBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerPlayerProgression> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerGenericProgressionWithRewardsResponse : public FLootLockerGenericProgressionResponse
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerAwardedTier> Awarded_Tiers;
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedProgressionTiersResponse : public FLootLockerResponse
{
    GENERATED_BODY()
        UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        FLootLockerIndexBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
        TArray<FLootLockerProgressionTier> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterProgressionResponse : public FLootLockerGenericProgressionResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterProgressionWithRewardsResponse : public FLootLockerGenericProgressionWithRewardsResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedCharacterProgressionResponse : public FLootLockerPaginatedGenericProgressionResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerProgressionResponse : public FLootLockerGenericProgressionResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerProgressionWithRewardsResponse : public FLootLockerGenericProgressionWithRewardsResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedPlayerProgressionResponse : public FLootLockerPaginatedGenericProgressionResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerInstanceProgressionResponse : public FLootLockerGenericProgressionResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerInstanceProgressionWithRewardsResponse : public FLootLockerGenericProgressionWithRewardsResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedInstanceProgressionResponse : public FLootLockerPaginatedGenericProgressionResponse
{
    GENERATED_BODY()
};

/* REQUEST STRUCTS */
USTRUCT()
struct FLootLockerModifyScoreRequest
{
    GENERATED_BODY()
        UPROPERTY()
        int32 Amount = 0;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerProgressionResponseBP, FLootLockerProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedProgressionsResponseBP, FLootLockerPaginatedProgressionsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerProgressionResponseBP, FLootLockerPlayerProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedPlayerProgressionsResponseBP, FLootLockerPaginatedPlayerProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerProgressionWithRewardsResponseBP, FLootLockerPlayerProgressionWithRewardsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCharacterProgressionResponseBP, FLootLockerCharacterProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedCharacterProgressionsResponseBP, FLootLockerPaginatedCharacterProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCharacterProgressionWithRewardsResponseBP, FLootLockerCharacterProgressionWithRewardsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedProgressionTiersResponseBP, FLootLockerPaginatedProgressionTiersResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDeleteProgressionBP, FLootLockerResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInstanceProgressionResponseBP, FLootLockerInstanceProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedInstanceProgressionsResponseBP, FLootLockerPaginatedInstanceProgressionResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInstanceProgressionWithRewardsResponseBP, FLootLockerInstanceProgressionWithRewardsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerProgressionResponseDelegate, FLootLockerProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedProgressionsResponseDelegate, FLootLockerPaginatedProgressionsResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPlayerProgressionResponseDelegate, FLootLockerPlayerProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedPlayerProgressionsResponseDelegate, FLootLockerPaginatedPlayerProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPlayerProgressionWithRewardsResponseDelegate, FLootLockerPlayerProgressionWithRewardsResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterProgressionResponseDelegate, FLootLockerCharacterProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedCharacterProgressionsResponseDelegate, FLootLockerPaginatedCharacterProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterProgressionWithRewardsResponseDelegate, FLootLockerCharacterProgressionWithRewardsResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedProgressionTiersResponseDelegate, FLootLockerPaginatedProgressionTiersResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDeleteProgressionDelegate, FLootLockerResponse);
DECLARE_DELEGATE_OneParam(FLootLockerInstanceProgressionResponseDelegate, FLootLockerInstanceProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedInstanceProgressionsResponseDelegate, FLootLockerPaginatedInstanceProgressionResponse);
DECLARE_DELEGATE_OneParam(FLootLockerInstanceProgressionWithRewardsResponseDelegate, FLootLockerInstanceProgressionWithRewardsResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerProgressionsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerProgressionsRequestHandler();

    static void GetPlayerProgressions(const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedPlayerProgressionsResponseBP(), const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedPlayerProgressionsResponseDelegate());
    static void GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionResponseBP(), const FLootLockerPlayerProgressionResponseDelegate& OnComplete = FLootLockerPlayerProgressionResponseDelegate());
    static void AddPointsToPlayerProgression(const FString& ProgressionKey, const int32 Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionWithRewardsResponseBP(), const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerPlayerProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32 Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionWithRewardsResponseBP(), const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerPlayerProgressionWithRewardsResponseDelegate());
    static void ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionWithRewardsResponseBP(), const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerPlayerProgressionWithRewardsResponseDelegate());
    static void DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP = FLootLockerDeleteProgressionBP(), const FLootLockerDeleteProgressionDelegate& OnComplete = FLootLockerDeleteProgressionDelegate());

    static void GetCharacterProgressions(const int32 CharacterId, const int32 Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedCharacterProgressionsResponseBP(), const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedCharacterProgressionsResponseDelegate());
    static void GetCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionResponseBP(), const FLootLockerCharacterProgressionResponseDelegate& OnComplete = FLootLockerCharacterProgressionResponseDelegate());
    static void AddPointsToCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const int32 Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionWithRewardsResponseBP(), const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerCharacterProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const int32 Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionWithRewardsResponseBP(), const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerCharacterProgressionWithRewardsResponseDelegate());
    static void ResetCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionWithRewardsResponseBP(), const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerCharacterProgressionWithRewardsResponseDelegate());
    static void DeleteCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP = FLootLockerDeleteProgressionBP(), const FLootLockerDeleteProgressionDelegate& OnComplete = FLootLockerDeleteProgressionDelegate());

    static void GetProgressions(const int32 Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedProgressionsResponseBP(), const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedProgressionsResponseDelegate());
    static void GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequestBP = FLootLockerProgressionResponseBP(), const FLootLockerProgressionResponseDelegate& OnComplete = FLootLockerProgressionResponseDelegate());
    static void GetProgressionTiers(const FString& ProgressionKey, const int32 Count, const int32 After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequestBP = FLootLockerPaginatedProgressionTiersResponseBP(), const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete = FLootLockerPaginatedProgressionTiersResponseDelegate());

    static void GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedInstanceProgressionsResponseBP(), const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedInstanceProgressionsResponseDelegate());
    static void GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequestBP = FLootLockerInstanceProgressionResponseBP(), const FLootLockerInstanceProgressionResponseDelegate& OnComplete = FLootLockerInstanceProgressionResponseDelegate());
    static void AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerInstanceProgressionWithRewardsResponseBP(), const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerInstanceProgressionWithRewardsResponseBP(), const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate());
    static void ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerInstanceProgressionWithRewardsResponseBP(), const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerInstanceProgressionWithRewardsResponseDelegate());
    static void DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP = FLootLockerDeleteProgressionBP(), const FLootLockerDeleteProgressionDelegate& OnComplete = FLootLockerDeleteProgressionDelegate());

    static ULootLockerHttpClient* HttpClient;
};