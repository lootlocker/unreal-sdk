// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "JsonObjectConverter.h"
#include "LootLockerMiscellaneousRequestHandler.generated.h"

//==================================================
// Data Definitions
//==================================================

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerGameInfo
{
    GENERATED_BODY()
    /// The title ID of the game (uniquely identifies the game in LootLocker)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Title_id = "";
    /// The environment ID of the game (identifies which environment instance of the title this game refers to in LootLocker)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Environment_id = "";
    /// The id of the game (uniquely identifies the game in LootLocker)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Game_id = 0;
    /// The name of the game as configured in LootLocker
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
};

//==================================================
// Request Definitions
//==================================================
/**
*/
USTRUCT(BlueprintType)
struct FLootLockerGameInfoRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString api_key = "";
};

//==================================================
// Response Definitions
//==================================================
/**
*/
USTRUCT(BlueprintType)
struct FLootLockerTimeResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString date = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerGameInfoResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /// Information about the game
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerGameInfo Info;
};

/// The state of a player's connection and session with the LootLocker backend.
/// Returned by CheckConnectionStatus.
UENUM(BlueprintType)
enum class ELootLockerConnectionState : uint8
{
    /// The SDK has not been configured (game API key is not set).
    NotInitialized      UMETA(DisplayName = "Not Initialized"),
    /// No session token exists in local state for the specified player.
    NotSignedIn         UMETA(DisplayName = "Not Signed In"),
    /// The player has saved credentials on disk but is not currently active in the
    /// multi-player session. Call SetPlayerUlidToActive (or start a new session) to activate
    /// them before calling CheckConnectionStatus again.
    SavedButInactive    UMETA(DisplayName = "Saved But Inactive"),
    /// The session token is valid and the server is reachable (ping returned 200).
    SignedInAndConnected UMETA(DisplayName = "Signed In And Connected"),
    /// A session token exists but the server returned 401 or 403 and the player is not banned.
    SessionExpired      UMETA(DisplayName = "Session Expired"),
    /// A session token exists but the player is currently banned.
    Banned              UMETA(DisplayName = "Banned"),
    /// The server could not be reached (no network, timeout, or status code 0).
    NoConnection        UMETA(DisplayName = "No Connection"),
    /// The server returned a 5xx error or an unexpected non-success status code.
    ServerError         UMETA(DisplayName = "Server Error"),
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerConnectionStateResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /// The determined connection and session state for the player.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerConnectionState State = ELootLockerConnectionState::NotInitialized;
    /// Server timestamp returned by the ping. Populated only when State is SignedInAndConnected.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ServerTime = "";
    /// Details about the active ban. Populated only when State is Banned.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerBanInfo BanDetails;
};

//==================================================
// Delegate Definitions
//==================================================
/// @addtogroup Misc
/// @{
/**
 * C++ response delegate for fetching server time
 */
DECLARE_DELEGATE_OneParam(FTimeResponseDelegate, FLootLockerTimeResponse);
/**
 * C++ response delegate for fetching game info
 */
DECLARE_DELEGATE_OneParam(FGameInfoResponseDelegate, FLootLockerGameInfoResponse);
/**
 * C++ response delegate for CheckConnectionStatus
 */
DECLARE_DELEGATE_OneParam(FLootLockerConnectionStateDelegate, FLootLockerConnectionStateResponse);

//==================================================
// API Class Definition
//==================================================
/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerMiscellaneousRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerMiscellaneousRequestHandler() {};

	static FString GetServerTime(const FLootLockerPlayerData& PlayerData, const FTimeResponseDelegate& OnCompletedRequest);
	static FString GetLastActivePlatform(const FLootLockerPlayerData& PlayerData);
    static FString GetGameInfo(const FGameInfoResponseDelegate& OnCompletedRequest);
    static FString CheckConnectionStatus(const FLootLockerPlayerData& PlayerData, const FLootLockerConnectionStateDelegate& OnCompletedRequest);
};
