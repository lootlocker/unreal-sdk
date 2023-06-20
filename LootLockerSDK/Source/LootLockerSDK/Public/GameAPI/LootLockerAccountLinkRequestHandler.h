// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerAccountLinkRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/*
 * Possible account linking process statuses. Undefined means that the object couldn't be constructed correctly
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerAccountLinkingProcessStatus : uint8
{
        Undefined = 0       UMETA(DisplayName = "Undefined"),
		Started = 1			UMETA(DisplayName = "Started"),
		Cancelled = 2		UMETA(DisplayName = "Cancelled"),
		Completed = 3		UMETA(DisplayName = "Completed")
};

//==================================================
// Response Definitions
//==================================================

/*
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerAccountLinkStartResponse : public FLootLockerResponse
{
	GENERATED_BODY()
    /*
     * ID of the account linking process. Save this as you will need it for checking the linking process status and if you want to cancel it.
     */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Link_id = "";
    /*
     * Used by the user in the online account linking process
     */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Code = "";
    /*
     * Base64 encoded PNG image of a qr code that can be shown to the player for them to scan and open the account linking flow
     */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Qr_code = "";
    /*
     * URL to where the user can continue the online account linking process
     */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Code_page_url = "";
};

/*
 *
 */
USTRUCT(BlueprintType)
struct FLootLockerAccountLinkProcessStatusResponse : public FLootLockerResponse
{
	GENERATED_BODY()
    /*
     * Current status of the specified account linking process
     */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	ELootLockerAccountLinkingProcessStatus Status = ELootLockerAccountLinkingProcessStatus::Undefined;
    /*
     * Time when the specified account linking process was started
     */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Created_at = "";
};

/*
 * This response will be empty unless there's an error
 */
USTRUCT(BlueprintType)
struct FLootLockerCancelAccountLinkingProcessResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};

/*
 * This response will be empty unless there's an error
 */
USTRUCT(BlueprintType)
struct FLootLockerUnlinkProviderFromAccountResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
/*
 * Blueprint response delegate for starting an account linking process
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerAccountLinkStartResponseBP, FLootLockerAccountLinkStartResponse, Response);
/*
 * Blueprint response delegate for checking the status of an ongoing account linking process
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerAccountLinkProcessStatusResponseBP, FLootLockerAccountLinkProcessStatusResponse, Response);
/*
 * Blueprint response delegate for cancelling an account linking process
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCancelAccountLinkingProcessResponseBP, FLootLockerCancelAccountLinkingProcessResponse, Response);
/*
 * Blueprint response delegate for unlinking a provider from an account
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerUnlinkProviderFromAccountResponseBP, FLootLockerUnlinkProviderFromAccountResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/*
 * C++ response delegate for starting an account linking process
 */
DECLARE_DELEGATE_OneParam(FLootLockerAccountLinkStartResponseDelegate, FLootLockerAccountLinkStartResponse);
/*
 * C++ response delegate for checking the status of an ongoing account linking process
 */
DECLARE_DELEGATE_OneParam(FLootLockerAccountLinkProcessStatusResponseDelegate, FLootLockerAccountLinkProcessStatusResponse);
/*
 * C++ response delegate for cancelling an account linking process
 */
DECLARE_DELEGATE_OneParam(FLootLockerCancelAccountLinkingProcessResponseDelegate, FLootLockerCancelAccountLinkingProcessResponse);
/*
 * C++ response delegate for unlinking a provider from an account
 */
DECLARE_DELEGATE_OneParam(FLootLockerUnlinkProviderFromAccountResponseDelegate, FLootLockerUnlinkProviderFromAccountResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerAccountLinkRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerAccountLinkRequestHandler();

    static void StartAccountLinkingProcess(const FLootLockerAccountLinkStartResponseBP& OnResponseCompletedBP = FLootLockerAccountLinkStartResponseBP(), const FLootLockerAccountLinkStartResponseDelegate& OnResponseCompleted = FLootLockerAccountLinkStartResponseDelegate());
    static void CheckAccountLinkingProcessStatus(const FString& LinkID, const FLootLockerAccountLinkProcessStatusResponseBP& OnResponseCompletedBP = FLootLockerAccountLinkProcessStatusResponseBP(), const FLootLockerAccountLinkProcessStatusResponseDelegate& OnResponseCompleted = FLootLockerAccountLinkProcessStatusResponseDelegate());
    static void CancelAccountLinkingProcess(const FString& LinkID, const FLootLockerCancelAccountLinkingProcessResponseBP& OnResponseCompletedBP = FLootLockerCancelAccountLinkingProcessResponseBP(), const FLootLockerCancelAccountLinkingProcessResponseDelegate& OnResponseCompleted = FLootLockerCancelAccountLinkingProcessResponseDelegate());
    static void UnlinkProviderFromAccount(const ELootLockerPlatform Provider, const FLootLockerUnlinkProviderFromAccountResponseBP& OnResponseCompletedBP = FLootLockerUnlinkProviderFromAccountResponseBP(), const FLootLockerUnlinkProviderFromAccountResponseDelegate& OnResponseCompleted = FLootLockerUnlinkProviderFromAccountResponseDelegate());
    
    static ULootLockerHttpClient* HttpClient;
};
