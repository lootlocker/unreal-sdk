// Copyright LootLocker AB

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerReferralRequestHandler.generated.h"

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

    /** The action that turns a claimed referral into a payout: session_started, entitlement_owned, game_asserted or publisher_currency_earned. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString qualifier = "";

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

    /** The state of the referral: claimed (pending the qualifying action), qualified (rewarded) or void (voided). */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString status = "";

    /** When the referral was claimed. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString claimed_at = "";

    /** When the referral qualified. Empty while it is still pending. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString qualified_at = "";
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
