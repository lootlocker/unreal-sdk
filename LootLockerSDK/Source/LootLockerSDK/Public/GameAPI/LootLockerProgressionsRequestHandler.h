// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerProgressionsRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerProgression
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Active;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerProgression
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionKey;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 PreviousThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 NextThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString LastLevelUp;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterProgression
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionKey;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 PreviousThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 NextThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString LastLevelUp;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int AssetId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int AssetVariationId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int AssetRentalOptionId;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionPointsReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionKey;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Amount;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionResetReward
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionKey;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionName;
};

USTRUCT(BlueprintType)
struct FLootLockerRewards
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionPointsReward> ProgressionPointsRewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProgressionResetReward> ProgressionResetRewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetReward> AssetRewards;
};

USTRUCT(BlueprintType)
struct FLootLockerAwardedTier
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 PointsThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerRewards Rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionTier
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 PointsThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerRewards Rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerProgressionResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool Active;
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
struct FLootLockerPlayerProgressionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionKey;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 PreviousThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 NextThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString LastLevelUp;
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedPlayerProgressionsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerKeyBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPlayerProgression> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerProgressionWithRewardsResponse : public FLootLockerPlayerProgressionResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAwardedTier> AwardedTiers;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterProgressionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionKey;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ProgressionName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Step;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Points;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 PreviousThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 NextThreshold;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString LastLevelUp;
};

USTRUCT(BlueprintType)
struct FLootLockerPaginatedCharacterProgressionsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerKeyBasedPagination Pagination;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCharacterProgression> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerCharacterProgressionWithRewardsResponse : public FLootLockerCharacterProgressionResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAwardedTier> AwardedTiers;
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerProgressionResponseBP, FLootLockerProgressionResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerProgressionResponseDelegate, FLootLockerProgressionResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedProgressionsResponseBP, FLootLockerPaginatedProgressionsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedProgressionsResponseDelegate, FLootLockerPaginatedProgressionsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerProgressionResponseBP, FLootLockerPlayerProgressionResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPlayerProgressionResponseDelegate, FLootLockerPlayerProgressionResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedPlayerProgressionsResponseBP, FLootLockerPaginatedPlayerProgressionsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedPlayerProgressionsResponseDelegate, FLootLockerPaginatedPlayerProgressionsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPlayerProgressionWithRewardsResponseBP, FLootLockerPlayerProgressionWithRewardsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPlayerProgressionWithRewardsResponseDelegate, FLootLockerPlayerProgressionWithRewardsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCharacterProgressionResponseBP, FLootLockerCharacterProgressionResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterProgressionResponseDelegate, FLootLockerCharacterProgressionResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedCharacterProgressionsResponseBP, FLootLockerPaginatedCharacterProgressionsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedCharacterProgressionsResponseDelegate, FLootLockerPaginatedCharacterProgressionsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCharacterProgressionWithRewardsResponseBP, FLootLockerCharacterProgressionWithRewardsResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerCharacterProgressionWithRewardsResponseDelegate, FLootLockerCharacterProgressionWithRewardsResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerPaginatedProgressionTiersResponseBP, FLootLockerPaginatedProgressionTiersResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerPaginatedProgressionTiersResponseDelegate, FLootLockerPaginatedProgressionTiersResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDeleteProgressionBP, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerDeleteProgressionDelegate, FLootLockerResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerProgressionsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerProgressionsRequestHandler();

    static void GetPlayerProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedPlayerProgressionsResponseBP(), const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedPlayerProgressionsResponseDelegate());
    static void GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionResponseBP(), const FLootLockerPlayerProgressionResponseDelegate& OnComplete = FLootLockerPlayerProgressionResponseDelegate());
    static void AddPointsToPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionWithRewardsResponseBP(), const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerPlayerProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32& Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionWithRewardsResponseBP(), const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerPlayerProgressionWithRewardsResponseDelegate());
    static void ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerPlayerProgressionWithRewardsResponseBP(), const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerPlayerProgressionWithRewardsResponseDelegate());
    static void DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP = FLootLockerDeleteProgressionBP(), const FLootLockerDeleteProgressionDelegate& OnComplete = FLootLockerDeleteProgressionDelegate());

    static void GetCharacterProgressions(const int32& CharacterId, const int32& Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedCharacterProgressionsResponseBP(), const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedCharacterProgressionsResponseDelegate());
    static void GetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionResponseBP(), const FLootLockerCharacterProgressionResponseDelegate& OnComplete = FLootLockerCharacterProgressionResponseDelegate());
    static void AddPointsToCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionWithRewardsResponseBP(), const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerCharacterProgressionWithRewardsResponseDelegate());
    static void SubtractPointsFromCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const int32& Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionWithRewardsResponseBP(), const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerCharacterProgressionWithRewardsResponseDelegate());
    static void ResetCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP = FLootLockerCharacterProgressionWithRewardsResponseBP(), const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete = FLootLockerCharacterProgressionWithRewardsResponseDelegate());
    static void DeleteCharacterProgression(const int32& CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP = FLootLockerDeleteProgressionBP(), const FLootLockerDeleteProgressionDelegate& OnComplete = FLootLockerDeleteProgressionDelegate());

    static void GetProgressions(const int32& Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequestBP = FLootLockerPaginatedProgressionsResponseBP(), const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete = FLootLockerPaginatedProgressionsResponseDelegate());
    static void GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequestBP = FLootLockerProgressionResponseBP(), const FLootLockerProgressionResponseDelegate& OnComplete = FLootLockerProgressionResponseDelegate());
    static void GetProgressionTiers(const FString& ProgressionKey, const int32& Count, const int32& After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequestBP = FLootLockerPaginatedProgressionTiersResponseBP(), const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete = FLootLockerPaginatedProgressionTiersResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};