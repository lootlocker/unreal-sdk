// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerGoogleSubsystemHelper.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerSDKGoogleSubsystemHelper, Log, All);

/**
 * Offer entry for display from online store
 */
USTRUCT(BlueprintType)
struct FLootLockerGoogleSubsystemStoreOffer
{
    GENERATED_BODY()
    /** Unique offer identifier */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FString OfferId;
    /** Title for display */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FText Title;
    /** Short description for display */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FText Description;
    /** Full description for display */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FText LongDescription;
    /** Regular non-sale price as text for display */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FText RegularPriceText;
    /** Regular non-sale price in numeric form for comparison/sorting */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    int32 RegularPrice = 0;
    /** Final-Pricing (Post-Sales/Discounts) as text for display */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FText PriceText;
    /** Final-Price (Post-Sales/Discounts) in numeric form for comparison/sorting */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    int32 NumericPrice = 0;
    /** Price currency code */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | GoogleSubsystemHelper")
    FString CurrencyCode;
};


/*
 * Delegate for responses upon login process completion
 */
DECLARE_DYNAMIC_DELEGATE_FourParams(FLootLockerGoogleSubsystemLoginCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg, const FString&, IDToken);
/*
 * Delegate for responses upon logout process completion
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FLootLockerGoogleSubsystemLogoutCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg);
/*
 * Delegate for responses upon purchase completion
 */
DECLARE_DYNAMIC_DELEGATE_FiveParams(FLootLockerGoogleSubsystemPurchaseCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg, const FString&, ReceiptOfferID, const FString&, ReceiptPurchaseToken);
/*
 * Delegate for responses upon purchase information read completion
 */
DECLARE_DYNAMIC_DELEGATE_FourParams(FLootLockerGoogleSubsystemReadOfferCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg, FLootLockerGoogleSubsystemStoreOffer, OfferInformation);

/*
 * Delegate for responses upon login process completion
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FLootLockerGooglePlaySubsystemLoginCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg);
/*
 * Delegate for responses upon logout process completion
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FLootLockerGooglePlaySubsystemLogoutCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg);

UCLASS()
class ULootLockerGoogleSubsystemHelper : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Does the Google Subsystem exist and is initialized
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static bool HasGoogleOnlineSubsystem();

    /**
     * Does the Google Play Subsystem exist and is initialized
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static bool HasGooglePlayOnlineSubsystem();

    /**
     * Initialize Google Subsystem Helper
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void Initialize();

    /**
     * Do sign in using Google asynchronously and call callback on completion
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void SignInWithGoogle(int LocalUserNumber, const FLootLockerGoogleSubsystemLoginCompletedCallback Callback);

    /**
     * Do sign out using Google asynchronously and call callback on completion
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void SignOutWithGoogle(int LocalUserNumber, const FLootLockerGoogleSubsystemLogoutCompletedCallback Callback);

    /**
     * Do sign in using Google Play asynchronously and call callback on completion
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void SignInWithGooglePlay(int LocalUserNumber, const FLootLockerGooglePlaySubsystemLoginCompletedCallback Callback);

    /**
     * Do sign out using Google Play asynchronously and call callback on completion
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void SignOutWithGooglePlay(int LocalUserNumber, const FLootLockerGooglePlaySubsystemLogoutCompletedCallback Callback);

    /**
     * Get the ID Token for the google user signed in for the provided local user number
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static FString GetIDToken(int LocalUserNumber);

    /**
     * Read info about the specified offering from Google Play
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="OfferId">The ID of the offer to purchase</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void ReadOfferInformation(int LocalUserNumber, const FString& OfferId, FLootLockerGoogleSubsystemReadOfferCompletedCallback Callback);

    /**
     * Purchase the specified offering from Google Play
     * 
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="OfferId">The ID of the offer to purchase</param>
     * <param name="IsConsumable">Whether this offer is consumable or not</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker | GoogleSubsystemHelper")
    static void PurchaseOffer(int LocalUserNumber, const FString& OfferId, bool IsConsumable, FLootLockerGoogleSubsystemPurchaseCompletedCallback Callback);
private:
    static void InvokeGoogleLoginCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemLoginCompletedCallback Callback);
    static void InvokeGoogleLogoutCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemLogoutCompletedCallback Callback);
    static void InvokePurchaseCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemPurchaseCompletedCallback Callback);
    static void InvokeReadOfferCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemReadOfferCompletedCallback Callback);
    static void InvokeGooglePlayLoginCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGooglePlaySubsystemLoginCompletedCallback Callback);
    static void InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGooglePlaySubsystemLogoutCompletedCallback Callback);
    static FDelegateHandle LoginDelegateHandle;
    static FDelegateHandle LogoutDelegateHandle;
    static bool IsPurchaseInProgress;
    static bool IsInitialized;
};