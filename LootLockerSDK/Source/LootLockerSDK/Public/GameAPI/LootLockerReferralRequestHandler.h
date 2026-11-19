// Copyright LootLocker AB

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerReferralRequestHandler.generated.h"

//==================================================
// Enum Definitions
//==================================================

/// @addtogroup Referrals
/// @{
/**
 * The action that turns a claimed referral into a payout.
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerReferralQualifier : uint8
{
    session_started = 0,
    entitlement_owned = 1,
    game_asserted = 2,
    publisher_currency_earned = 3,
};
/// @}

/// @addtogroup Referrals
/// @{
/**
 * The state of a referral relation.
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerReferralStatus : uint8
{
    claimed = 0,
    qualified = 1,
    Void = 2,
};
/// @}

//==================================================
// Data Definitions
//==================================================

/**
 * One referral program as it applies to the inviting player: the program's identity, the action that
 * qualifies a referral, and how many rewarded referrals the player has against the program's cap.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerReferralProgram
{
    GENERATED_BODY()

    /** The game-unique machine key of the program. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString program_key = "";

    /** The human-friendly display name of the program. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";

    /** The action that turns a claimed referral into a payout. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerReferralQualifier qualifier = ELootLockerReferralQualifier::session_started;

    /** How many rewarded referrals the player has made under this program. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 referral_count = 0;

    /** The maximum number of rewarded referrals this player may make under this program. Only meaningful when HasReferrerCap is true. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 referrer_cap = 0;

    /** True when the program has a referrer cap, in which case Referrer_cap holds it. False means the program is uncapped. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool HasReferrerCap = false;
};

/**
 * One referral relation as the referring player sees it: the program it was made under, the referee's
 * public UID, and its state.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerReferral
{
    GENERATED_BODY()

    /** The referral ULID. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";

    /** The game-unique machine key of the program the referral was made under. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString program_key = "";

    /** The human-friendly display name of the program. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString program_name = "";

    /** The referred player's public UID. Empty when their game-player row is gone. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString referee_public_uid = "";

    /** The state of the referral. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerReferralStatus status = ELootLockerReferralStatus::claimed;

    /** When the referral was claimed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime claimed_at = FDateTime(0);

    /** When the referral qualified. Only meaningful when HasQualifiedAt is true. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime qualified_at = FDateTime(0);

    /** True when the referral has qualified and Qualified_at holds the time. False while it is still pending. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool HasQualifiedAt = false;

    /** True when the referee's game-player row still exists, in which case Referee_public_uid holds their UID. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool HasRefereePublicUid = false;
};

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the calling player's referral code and their rewarded-referral count against each
 * active program's cap. Use this to render an invite-a-friend screen.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerReferralInviteResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The player's referral code, which is their public UID. Share it so friends can supply it as the referral_code session optional. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString code = "";

    /** The game's active referral programs, each with the player's progress against its cap. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerReferralProgram> programs;

    /**
     Populate the convenience structures that FJsonObjectConverter cannot derive on its own, notably
     HasReferrerCap, which distinguishes an uncapped program from one capped at zero.
     */
    void PopulateConvenienceStructures();
};

/**
 * Response containing one page of the calling player's own referrals, newest first, including ones still
 * pending their qualifying action.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerReferralListResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The player's referrals, newest first. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerReferral> referrals;

    /** Pagination information for the referrals. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination pagination;

    /**
     Populate the convenience structures that FJsonObjectConverter cannot derive on its own, notably the
     status and qualifier enums and the nullable qualified_at and referee_public_uid.
     */
    void PopulateConvenienceStructures();
};

//==================================================
// C++ Delegate Definitions
//==================================================

/// @addtogroup Referrals
/// @{
/** C++ response callback delegate; receives an @ref FLootLockerReferralInviteResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerReferralInviteResponseDelegate, FLootLockerReferralInviteResponse);

/** C++ response callback delegate; receives an @ref FLootLockerReferralListResponse result. */
DECLARE_DELEGATE_OneParam(FLootLockerReferralListResponseDelegate, FLootLockerReferralListResponse);
/// @}

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULLReferralRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULLReferralRequestHandler() {};

    static FString GetInvite(const FLootLockerPlayerData& PlayerData, const FLootLockerReferralInviteResponseDelegate& OnCompletedRequest);
    static FString ListMyReferrals(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerReferralListResponseDelegate& OnCompletedRequest);
};
