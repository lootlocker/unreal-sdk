// Copyright LootLocker AB

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerIdentityRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================
/// @addtogroup Identity
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * Platforms that can be presented as a credential when linking a provider to an identity.
 *
 * The enumerator names are the wire values the backend accepts, so they are sent as-is. These are the
 * platform catalog slugs used by LootLocker, which are not the same catalogue as ELootLockerAccountProvider.
 */
enum class ELootLockerIdentityProvider : uint8
{
    Steam = 0,
    Psn = 1,
    Apple_app_store = 2,
    Google_play_store = 3,
    Xbox_one = 4,
    Nintendo_switch = 5,
    Amazon_luna = 6,
    White_label_login = 7,
    Guest = 8,
    Apple_sign_in = 9,
    Google_sign_in = 10,
    Epic_games = 11,
    Apple_game_center = 12,
    Meta = 13,
    Twitch = 14,
    Google_play_games = 15,
    Discord = 16,
    Lootlocker_delegation = 17
};
/// @}

//==================================================
// Data Definitions
//==================================================

/**
 * One game in which a player of this identity has been active.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityGameActivity
{
    GENERATED_BODY()

    /** The legacy integer id of the game. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 game_id = 0;

    /** The first time a session was started for this identity in the game. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString first_session_at = "";

    /** The most recent time a session was started for this identity in the game. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString last_session_at = "";

    /** The number of sessions started for this identity in the game. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 session_count = 0;
};

/**
 * One game in which both identities being merged have a live player, and therefore needs a choice of
 * which player to keep.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityPlayerConflict
{
    GENERATED_BODY()

    /** The legacy integer id of the game the conflict is in. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 game_id = 0;

    /** The player id belonging to the identity that is kept. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 keep_player_id = 0;

    /** The player id belonging to the identity that is merged away. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 merge_player_id = 0;
};

/**
 * What merging two identities would resolve, without executing anything.
 *
 * An empty Player_conflicts means the merge needs no further choices.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityMergePreview
{
    GENERATED_BODY()

    /** The ULID of the identity the caller keeps. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString keep_identity_id = "";

    /** The ULID of the identity that would be merged into the kept identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString merge_identity_id = "";

    /** The games in which both identities have a live player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerIdentityPlayerConflict> player_conflicts;
};

//==================================================
// Request Definitions
//==================================================

/**
 * Request to look identities up by id and/or by the games they have been active in.
 *
 * At least one of Identity_ids and Game_ids must be supplied. Results are always scoped to the caller's
 * publisher.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityLookupRequest
{
    GENERATED_BODY()

    /** Optional: The ULIDs of the identities to look up. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> identity_ids;

    /** Optional: The legacy integer ids of games to filter the identities by. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<int32> game_ids;

    /** Optional: Whether to populate game_activity on each result. Defaults to false on the server. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool include_game_activity = false;
};

/**
 * Request to record a provider credential against the player's identity.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityLinkRequest
{
    GENERATED_BODY()

    /** The provider platform the credential belongs to. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerIdentityProvider provider = ELootLockerIdentityProvider::Steam;

    /** The provider's identifier for the player, for example the Steam ID. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString provider_uid = "";
};

/**
 * The choice of which player to keep in one game where both identities have a live player.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityMergeResolution
{
    GENERATED_BODY()

    /** The legacy integer id of the game this resolution is for. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 game_id = 0;

    /** The player to keep in this game. Must equal either the keep or the merge player id of the conflict. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 keep_player_id = 0;
};

/**
 * Request to merge another identity into the current one.
 *
 * This is destructive and never runs automatically. Get the conflicts from a merge preview (or from the
 * conflict of a link), let the player choose, then send one resolution per conflict.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityMergeRequest
{
    GENERATED_BODY()

    /** The ULID of the identity to merge into the authenticated identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString merge_identity_id = "";

    /** One entry per game listed in the merge preview's player_conflicts. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerIdentityMergeResolution> resolutions;

    /** Optional: The provider whose credential conflict led to this merge, recorded in the merge log. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString trigger_provider = "";

    /** Optional: The provider credential that led to this merge, recorded in the merge log. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString trigger_provider_uid = "";
};

//==================================================
// Response Definitions
//==================================================

/**
 * Response containing a single identity.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The ULID of the identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";

    /** The legacy integer id of the publisher that owns the identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 publisher_id = 0;

    /** When the identity was created. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at = "";

    /** The games this identity has been active in. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerIdentityGameActivity> game_activity;
};

/**
 * Response containing zero or more identities.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityLookupResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The identities matching the lookup. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerIdentityResponse> identities;
};

/**
 * The body of the 409 returned when the credential being linked already belongs to another identity.
 *
 * LootLocker never merges on the player's behalf. Read this, show the player the conflicts, then call
 * MergeIdentities with one resolution per conflict.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityLinkConflict
{
    GENERATED_BODY()

    /** The message the server attached to the conflict. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString message = "";

    /** The ULID of the identity that already owns the credential. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString conflicting_identity_id = "";

    /** What a merge of the requesting identity (keep) into the conflicting identity (merge) would resolve. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerIdentityMergePreview merge_preview;
};

/**
 * Response returned after linking a provider credential.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityLinkResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** True when a new credential was recorded, false when the identity already owned it. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool created = false;

    /**
     * Set when the request was answered with 409 because the credential belongs to another identity. The
     * success flag is false in that case; this carries the merge offer the player must act on.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerIdentityLinkConflict conflict;

    /** Whether Conflict was populated, because Conflict itself is a value type that cannot be null. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool has_conflict = false;
};

/**
 * Response containing a merge preview.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityMergePreviewResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The ULID of the identity the caller keeps. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString keep_identity_id = "";

    /** The ULID of the identity that would be merged into the kept identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString merge_identity_id = "";

    /** The games in which both identities have a live player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerIdentityPlayerConflict> player_conflicts;
};

/**
 * Response returned after merging two identities, containing the surviving identity.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerIdentityMergeResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The ULID of the surviving identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";

    /** The legacy integer id of the publisher that owns the identity. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 publisher_id = 0;

    /** When the surviving identity was created. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString created_at = "";

    /** The games the surviving identity has been active in. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerIdentityGameActivity> game_activity;
};

//==================================================
// Delegate Definitions
//==================================================
/// @addtogroup Identity
/// @{
/** C++ response delegate for reading the current identity */
DECLARE_DELEGATE_OneParam(FLootLockerIdentityResponseDelegate, FLootLockerIdentityResponse);
/** C++ response delegate for looking identities up */
DECLARE_DELEGATE_OneParam(FLootLockerIdentityLookupResponseDelegate, FLootLockerIdentityLookupResponse);
/** C++ response delegate for linking a provider credential */
DECLARE_DELEGATE_OneParam(FLootLockerIdentityLinkResponseDelegate, FLootLockerIdentityLinkResponse);
/** C++ response delegate for previewing an identity merge */
DECLARE_DELEGATE_OneParam(FLootLockerIdentityMergePreviewResponseDelegate, FLootLockerIdentityMergePreviewResponse);
/** C++ response delegate for merging identities */
DECLARE_DELEGATE_OneParam(FLootLockerIdentityMergeResponseDelegate, FLootLockerIdentityMergeResponse);

//==================================================
// API Class Definition
//==================================================

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerIdentityRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerIdentityRequestHandler() {};

    static FString GetIdentity(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityResponseDelegate& OnComplete);
    static FString LookupIdentities(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityLookupRequest& Request, const FLootLockerIdentityLookupResponseDelegate& OnComplete);
    static FString LinkProvider(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityLinkRequest& Request, const FLootLockerIdentityLinkResponseDelegate& OnComplete);
    static FString UnlinkProvider(const FLootLockerPlayerData& PlayerData, const FString& CredentialId, const FLootLockerDefaultDelegate& OnComplete);
    static FString PreviewIdentityMerge(const FLootLockerPlayerData& PlayerData, const FString& MergeIdentityId, const FLootLockerIdentityMergePreviewResponseDelegate& OnComplete);
    static FString MergeIdentities(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityMergeRequest& Request, const FLootLockerIdentityMergeResponseDelegate& OnComplete);
};