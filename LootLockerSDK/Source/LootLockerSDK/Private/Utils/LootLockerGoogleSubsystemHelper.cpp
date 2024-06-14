// Copyright (c) 2021 LootLocker

#include "LootLockerGoogleSubsystemHelper.h"

#ifdef LOOTLOCKER_ENABLE_GOOGLESUBSYSTEMHELPER
#include "OnlineSubsystem.h"
#include "OnlineError.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#endif

DEFINE_LOG_CATEGORY(LogLootLockerSDKGoogleSubsystemHelper);

bool ULootLockerGoogleSubsystemHelper::IsPurchaseInProgress = false;
bool ULootLockerGoogleSubsystemHelper::IsInitialized = false;
FDelegateHandle ULootLockerGoogleSubsystemHelper::LoginDelegateHandle = FDelegateHandle();
FDelegateHandle ULootLockerGoogleSubsystemHelper::LogoutDelegateHandle = FDelegateHandle();

#pragma region Logging Functions

void ULootLockerGoogleSubsystemHelper::InvokeGoogleLoginCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemLoginCompletedCallback Callback)
{
	Callback.ExecuteIfBound(false, LocalUserNumber, Message, "");
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *Message);
}

void ULootLockerGoogleSubsystemHelper::InvokeGoogleLogoutCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemLogoutCompletedCallback Callback)
{
	Callback.ExecuteIfBound(false, LocalUserNumber, Message);
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *Message);
}

void ULootLockerGoogleSubsystemHelper::InvokePurchaseCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemPurchaseCompletedCallback Callback)
{
	Callback.ExecuteIfBound(false, LocalUserNumber, Message, "", "");
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *Message);
}

void ULootLockerGoogleSubsystemHelper::InvokeReadOfferCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGoogleSubsystemReadOfferCompletedCallback Callback)
{
	Callback.ExecuteIfBound(false, LocalUserNumber, Message, FLootLockerGoogleSubsystemStoreOffer());
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *Message);
}

void ULootLockerGoogleSubsystemHelper::InvokeGooglePlayLoginCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGooglePlaySubsystemLoginCompletedCallback Callback)
{
	Callback.ExecuteIfBound(false, LocalUserNumber, Message);
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *Message);
}

void ULootLockerGoogleSubsystemHelper::InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerGooglePlaySubsystemLogoutCompletedCallback Callback)
{
	Callback.ExecuteIfBound(false, LocalUserNumber, Message);
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *Message);
}

#pragma endregion

#ifdef LOOTLOCKER_ENABLE_GOOGLESUBSYSTEMHELPER
bool ULootLockerGoogleSubsystemHelper::HasGoogleOnlineSubsystem()
{
	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Could not get Google Subsystem"));
		return false;
	}

	return true;
}

bool ULootLockerGoogleSubsystemHelper::HasGooglePlayOnlineSubsystem()
{
	const IOnlineSubsystem* OnlineSubsystemGPlay = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM);
	if (OnlineSubsystemGPlay == nullptr)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Could not get Google Play Subsystem"));
		return false;
	}

	return true;
}

void ULootLockerGoogleSubsystemHelper::Initialize()
{
	if (IsInitialized)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Verbose, TEXT("ULootLockerGoogleSubsystemHelper already initialized"));
		return;
	}

	if (IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM); OnlineSubsystemGoogle == nullptr)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Could not get Google Subsystem, Google connected functionality will not work"));
	}
	else if (!OnlineSubsystemGoogle->Init())
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Google Subsystem could not be initialized, Google connected functionality will not work"));
	}

	if (const IOnlineSubsystem* OnlineSubsystemGooglePlay = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM); OnlineSubsystemGooglePlay == nullptr)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Could not get Google Play Subsystem, Google Play connected functionality will not work"));
	}

	IsInitialized = true;
}

void ULootLockerGoogleSubsystemHelper::SignInWithGoogle(int LocalUserNumber, const FLootLockerGoogleSubsystemLoginCompletedCallback Callback)
{
	if (!IsInitialized)
	{
		Initialize();
	}

	if (LoginDelegateHandle.IsValid())
	{
		InvokeGoogleLoginCallbackWithErrorResponseAndLog("A Login is already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		InvokeGoogleLoginCallbackWithErrorResponseAndLog("Could not get Google Subsystem", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeGoogleLoginCallbackWithErrorResponseAndLog("Could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) == ELoginStatus::LoggedIn)
	{
		// User already signed in, treat it as a successful login attempt
		Callback.ExecuteIfBound(true, LocalUserNumber, "", GetIDToken(LocalUserNumber));
		return;
	}

	LoginDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(
		LocalUserNumber, FOnLoginCompleteDelegate::CreateLambda(
			[Callback](int LocalUserNumber, bool wasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				if (!wasSuccessful)
				{
					InvokeGoogleLoginCallbackWithErrorResponseAndLog(FString::Format(TEXT("ULootLockerGoogleSubsystemHelper Google Login failed with message: {0}"), { Error }), LocalUserNumber, Callback);
				}
				else
				{
					Callback.ExecuteIfBound(true, LocalUserNumber, "", GetIDToken(LocalUserNumber));
				}

				// Clear state
				if (LoginDelegateHandle.IsValid())
				{
					if (const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM))
					{
						const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
						if (IdentityInterface != nullptr && IdentityInterface.IsValid())
						{
							IdentityInterface->ClearOnLoginCompleteDelegate_Handle(LocalUserNumber, LoginDelegateHandle);
						}
					}
					LoginDelegateHandle.Reset();
				}
			}
		)
	);

	IdentityInterface->Login(LocalUserNumber, FOnlineAccountCredentials{});
}

void ULootLockerGoogleSubsystemHelper::SignOutWithGoogle(int LocalUserNumber, const FLootLockerGoogleSubsystemLogoutCompletedCallback Callback)
{
	if (!IsInitialized)
	{
		Initialize();
	}

	if (LoginDelegateHandle.IsValid())
	{
		InvokeGoogleLogoutCallbackWithErrorResponseAndLog("Don't log out when logging in", LocalUserNumber, Callback);
		return;
	}

	if (LogoutDelegateHandle.IsValid())
	{
		InvokeGoogleLogoutCallbackWithErrorResponseAndLog("Logout process already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		InvokeGoogleLogoutCallbackWithErrorResponseAndLog("Could not get Google Subsystem", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeGoogleLogoutCallbackWithErrorResponseAndLog("Could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn)
	{
		// User already not signed in, treat it as a successful logout attempt
		Callback.ExecuteIfBound(true, LocalUserNumber, "");
		return;
	}

	LogoutDelegateHandle = IdentityInterface->AddOnLogoutCompleteDelegate_Handle(LocalUserNumber, FOnLogoutCompleteDelegate::CreateLambda([Callback](int LocalUserNumber, bool success)
		{
			if (!success)
			{
				InvokeGoogleLogoutCallbackWithErrorResponseAndLog(FString::Format(TEXT("ULootLockerGoogleSubsystemHelper Google Logout failed for local user number: {0}"), { LocalUserNumber }), LocalUserNumber, Callback);
				return;
			}

			Callback.ExecuteIfBound(success, LocalUserNumber, "");

			// Clear state
			if (LogoutDelegateHandle.IsValid())
			{
				if (const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM))
				{
					const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
					if (IdentityInterface != nullptr && IdentityInterface.IsValid())
					{
						IdentityInterface->ClearOnLogoutCompleteDelegate_Handle(LocalUserNumber, LogoutDelegateHandle);
					}
				}
				LogoutDelegateHandle.Reset();
			}
		})
	);
}

void ULootLockerGoogleSubsystemHelper::SignInWithGooglePlay(int LocalUserNumber, const FLootLockerGooglePlaySubsystemLoginCompletedCallback Callback)
{
	if (!IsInitialized)
	{
		Initialize();
	}

	if (LoginDelegateHandle.IsValid())
	{
		InvokeGooglePlayLoginCallbackWithErrorResponseAndLog("A Login is already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		InvokeGooglePlayLoginCallbackWithErrorResponseAndLog("Could not get Google Play Subsystem", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeGooglePlayLoginCallbackWithErrorResponseAndLog("Could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) == ELoginStatus::LoggedIn)
	{
		// User already signed in, treat it as a successful login attempt
		Callback.ExecuteIfBound(true, LocalUserNumber, "");
		return;
	}

	LoginDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(
		LocalUserNumber, FOnLoginCompleteDelegate::CreateLambda(
			[Callback](int LocalUserNumber, bool wasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				if (!wasSuccessful)
				{
					InvokeGooglePlayLoginCallbackWithErrorResponseAndLog(FString::Format(TEXT("ULootLockerGoogleSubsystemHelper Google Play Login failed with message: {0}"), { Error }), LocalUserNumber, Callback);
				}
				else
				{
					Callback.ExecuteIfBound(true, LocalUserNumber, "");
				}

				// Clear state
				if (LoginDelegateHandle.IsValid())
				{
					if (const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM))
					{
						const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
						if (IdentityInterface != nullptr && IdentityInterface.IsValid())
						{
							IdentityInterface->ClearOnLoginCompleteDelegate_Handle(LocalUserNumber, LoginDelegateHandle);
						}
					}
					LoginDelegateHandle.Reset();
				}
			}
		)
	);

	IdentityInterface->Login(LocalUserNumber, FOnlineAccountCredentials{});
}

void ULootLockerGoogleSubsystemHelper::SignOutWithGooglePlay(int LocalUserNumber, const FLootLockerGooglePlaySubsystemLogoutCompletedCallback Callback)
{
	if (!IsInitialized)
	{
		Initialize();
	}

	if (LoginDelegateHandle.IsValid())
	{
		InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog("Don't log out when logging in", LocalUserNumber, Callback);
		return;
	}

	if (LogoutDelegateHandle.IsValid())
	{
		InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog("Logout process already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog("Could not get Google Play Subsystem", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog("Could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn)
	{
		// User already not signed in, treat it as a successful logout attempt
		Callback.ExecuteIfBound(true, LocalUserNumber, "");
		return;
	}

	LogoutDelegateHandle = IdentityInterface->AddOnLogoutCompleteDelegate_Handle(LocalUserNumber, FOnLogoutCompleteDelegate::CreateLambda([Callback](int LocalUserNumber, bool success)
		{
			if (!success)
			{
				InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog(FString::Format(TEXT("ULootLockerGoogleSubsystemHelper Google Play Logout failed for local user number: {0}"), { LocalUserNumber }), LocalUserNumber, Callback);
				return;
			}

			Callback.ExecuteIfBound(success, LocalUserNumber, "");

			// Clear state
			if (LogoutDelegateHandle.IsValid())
			{
				if (const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM))
				{
					const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
					if (IdentityInterface != nullptr && IdentityInterface.IsValid())
					{
						IdentityInterface->ClearOnLogoutCompleteDelegate_Handle(LocalUserNumber, LogoutDelegateHandle);
					}
				}
				LogoutDelegateHandle.Reset();
			}
		})
	);
}

FString ULootLockerGoogleSubsystemHelper::GetIDToken(int LocalUserNumber)
{
	FString IdToken;
	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Error, TEXT("Could not get Google Subsystem"));
		return IdToken;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Could not get Google Identity Interface"));
		return IdToken;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("No google user logged in for local user number %d"), LocalUserNumber);
		return IdToken;
	}

	const FUniqueNetIdPtr UniqueNetIdPtr = IdentityInterface->GetUniquePlayerId(LocalUserNumber);
	if (!UniqueNetIdPtr.IsValid() || UniqueNetIdPtr.Get() == nullptr)
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("No valid user id found for local user number %d"), LocalUserNumber);
		return IdToken;
	}

	const TSharedPtr<FUserOnlineAccount> UserAccount = IdentityInterface->GetUserAccount(*UniqueNetIdPtr.Get());
	if (UserAccount == nullptr || !UserAccount.IsValid())
	{
		UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("No valid Google User Account found for local user number %d"), LocalUserNumber);
		return IdToken;
	}

	UserAccount->GetAuthAttribute(AUTH_ATTR_ID_TOKEN, IdToken);
	return IdToken;
}

void ULootLockerGoogleSubsystemHelper::ReadOfferInformation(int LocalUserNumber, const FString& OfferId, FLootLockerGoogleSubsystemReadOfferCompletedCallback Callback)
{
	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		InvokeReadOfferCallbackWithErrorResponseAndLog("Could not get Google Subsystem for getting user information", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGooglePlay = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM);
	if (OnlineSubsystemGooglePlay == nullptr)
	{
		InvokeReadOfferCallbackWithErrorResponseAndLog("Could not find a valid Google Play Subsystem to use to read purchase information", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeReadOfferCallbackWithErrorResponseAndLog("ULootLockerGoogleSubsystemHelper could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn || LoginDelegateHandle.IsValid() || LogoutDelegateHandle.IsValid())
	{
		InvokeReadOfferCallbackWithErrorResponseAndLog("This user does not have a valid Google user signed in to read purchase information for", LocalUserNumber, Callback);
		return;
	}

	const FUniqueNetIdPtr UniqueNetIdPtr = IdentityInterface->GetUniquePlayerId(LocalUserNumber);
	if (!UniqueNetIdPtr.IsValid() || UniqueNetIdPtr.Get() == nullptr)
	{
		InvokeReadOfferCallbackWithErrorResponseAndLog("This user does not have a valid Google user id", LocalUserNumber, Callback);
		return;
	}

	const FUniqueNetId& UserIdRef = *UniqueNetIdPtr;

	const IOnlineStoreV2Ptr StoreInterface = OnlineSubsystemGooglePlay->GetStoreV2Interface();
	if (!StoreInterface.IsValid())
	{
		InvokeReadOfferCallbackWithErrorResponseAndLog("ULootLockerGoogleSubsystemHelper could not get a valid Store Interface", LocalUserNumber, Callback);
		return;
	}

	StoreInterface->QueryOffersById(UserIdRef, { OfferId }, FOnQueryOnlineStoreOffersComplete::CreateLambda([LocalUserNumber, Callback, OfferId](bool Success, const TArray<FString>& Products, const FString& ErrorMessage)
		{
			if (!Success)
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("Failed offer query request with message: " + ErrorMessage, LocalUserNumber, Callback);
				return;
			}
			const IOnlineSubsystem* OnlineSubsystemGooglePlay = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM);
			if (OnlineSubsystemGooglePlay == nullptr)
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("Could not find a valid Google Play Subsystem to use to read purchase information", LocalUserNumber, Callback);
				return;
			}

			const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
			if (OnlineSubsystemGoogle == nullptr)
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("ULootLockerGoogleSubsystemHelper has no valid Google subsystem", LocalUserNumber, Callback);
				return;
			}

			const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
			if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("ULootLockerGoogleSubsystemHelper could not get a valid Identity Interface", LocalUserNumber, Callback);
				return;
			}

			if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn || LoginDelegateHandle.IsValid() || LogoutDelegateHandle.IsValid())
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("This user does not have a valid Google user signed in to read purchase information for", LocalUserNumber, Callback);
				return;
			}

			const IOnlineStoreV2Ptr StoreInterface = OnlineSubsystemGooglePlay->GetStoreV2Interface();
			if (!StoreInterface.IsValid())
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("ULootLockerGoogleSubsystemHelper could not get a valid Store Interface", LocalUserNumber, Callback);
				return;
			}

			const TSharedPtr<FOnlineStoreOffer> OfferSharedPtr = StoreInterface->GetOffer(OfferId);
			if (!OfferSharedPtr.IsValid())
			{
				InvokeReadOfferCallbackWithErrorResponseAndLog("Could not get cached store offer information", LocalUserNumber, Callback);
				return;
			}

			FLootLockerGoogleSubsystemStoreOffer Offer;
			Offer.OfferId = OfferSharedPtr->OfferId;
			Offer.Title = OfferSharedPtr->Title;
			Offer.Description = OfferSharedPtr->Description;
			Offer.LongDescription = OfferSharedPtr->LongDescription;
			Offer.RegularPriceText = OfferSharedPtr->RegularPriceText;
			Offer.RegularPrice = static_cast<int32>(OfferSharedPtr->RegularPrice);
			Offer.PriceText = OfferSharedPtr->PriceText;
			Offer.NumericPrice = static_cast<int32>(OfferSharedPtr->NumericPrice);
			Offer.CurrencyCode = OfferSharedPtr->CurrencyCode;
			Callback.ExecuteIfBound(true, LocalUserNumber, "", Offer);
		})
	);
}

void ULootLockerGoogleSubsystemHelper::PurchaseOffer(int LocalUserNumber, const FString& OfferId, bool IsConsumable, FLootLockerGoogleSubsystemPurchaseCompletedCallback Callback)
{
	if (IsPurchaseInProgress)
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("A purchase is already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGoogle = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (OnlineSubsystemGoogle == nullptr)
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("Could not get Google Subsystem for getting user information", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemGooglePlay = IOnlineSubsystem::Get(GOOGLEPLAY_SUBSYSTEM);
	if (OnlineSubsystemGooglePlay == nullptr)
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("Could not find a valid Google Play Subsystem to use to read purchase information", LocalUserNumber, Callback);
		return;
	}

	// Try first with GPlay and then with Google
	IOnlineIdentityPtr IdentityInterface = OnlineSubsystemGooglePlay->GetIdentityInterface();
	if ((IdentityInterface == nullptr || !IdentityInterface.IsValid()) || (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn))
	{
		IdentityInterface = OnlineSubsystemGoogle->GetIdentityInterface();
	}

	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("ULootLockerGoogleSubsystemHelper could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn || LoginDelegateHandle.IsValid() || LogoutDelegateHandle.IsValid())
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("This user does not have a valid Google user signed in to make purchase for", LocalUserNumber, Callback);
		return;
	}

	const FUniqueNetIdPtr UniqueNetIdPtr = IdentityInterface->GetUniquePlayerId(LocalUserNumber);
	if (!UniqueNetIdPtr.IsValid() || UniqueNetIdPtr.Get() == nullptr)
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("This user does not have a valid Google user id", LocalUserNumber, Callback);
		return;
	}

	const FUniqueNetId& UserIdRef = *UniqueNetIdPtr;

	const IOnlinePurchasePtr PurchaseInterface = OnlineSubsystemGooglePlay->GetPurchaseInterface();
	if (PurchaseInterface == nullptr || !PurchaseInterface.IsValid())
	{
		InvokePurchaseCallbackWithErrorResponseAndLog("Could not find a valid Google Play purchase interface to use to make purchase", LocalUserNumber, Callback);
		return;
	}

	FPurchaseCheckoutRequest PurchaseCheckoutRequest;
	PurchaseCheckoutRequest.AddPurchaseOffer("", OfferId, 1, IsConsumable);
	IsPurchaseInProgress = true;
	PurchaseInterface->Checkout(UserIdRef, PurchaseCheckoutRequest, FOnPurchaseCheckoutComplete::CreateLambda([&UserIdRef, OfferId, LocalUserNumber, Callback](const FOnlineError& Error, const TSharedRef<FPurchaseReceipt>& ReceiptRef)
		{
			IsPurchaseInProgress = false;

			if (!Error.WasSuccessful())
			{
				InvokePurchaseCallbackWithErrorResponseAndLog("Failed to make purchase, Error Message: \"" + Error.ToLogString() + "\"", LocalUserNumber, Callback);
				return;
			}

			int RequestedOfferIdIndex = -1;
			if (ReceiptRef.Get().ReceiptOffers.IsEmpty())
			{
				InvokePurchaseCallbackWithErrorResponseAndLog("Purchase completed successfully but returned no purchased offers", LocalUserNumber, Callback);
				return;
			}
			else {
				RequestedOfferIdIndex = 0;
			}

			if (ReceiptRef.Get().ReceiptOffers.Num() > 1)
			{
				UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("Receipt from Google Purchase returned more items than requested, count=%d"), ReceiptRef.Get().ReceiptOffers.Num());
				for (int i = 0; i < ReceiptRef.Get().ReceiptOffers.Num(); ++i)
				{
					if (ReceiptRef.Get().ReceiptOffers[i].OfferId.Equals(OfferId))
					{
						RequestedOfferIdIndex = i;
						break;
					}
				}
			}

			if (RequestedOfferIdIndex < 0 || RequestedOfferIdIndex >= ReceiptRef.Get().ReceiptOffers.Num())
			{
				InvokePurchaseCallbackWithErrorResponseAndLog("The receipt from Google Play did not contain the requested offer", LocalUserNumber, Callback);
				return;
			}

			const FPurchaseReceipt& Receipt = ReceiptRef.Get();
			Callback.ExecuteIfBound(true, LocalUserNumber, Error.ErrorMessage.ToString(), ReceiptRef.Get().ReceiptOffers[RequestedOfferIdIndex].OfferId, ReceiptRef.Get().ReceiptOffers[RequestedOfferIdIndex].LineItems[0].UniqueId);
		}));
}

#else //LOOTLOCKER_ENABLE_GOOGLESUBSYSTEMHELPER

const FString NOT_ENABLED_WARNING = "Google Subsystem is not enabled in LootLocker. To enable it, add LootLockerSDK.bEnableGoogleSubsystemHelper = true; to your games Build.cs file";

void ULootLockerGoogleSubsystemHelper::Initialize()
{
	UE_LOG(LogLootLockerSDKGoogleSubsystemHelper, Warning, TEXT("%s"), *NOT_ENABLED_WARNING);
	return;
}

bool ULootLockerGoogleSubsystemHelper::HasGoogleOnlineSubsystem()
{
	return false;
}

bool ULootLockerGoogleSubsystemHelper::HasGooglePlayOnlineSubsystem()
{
	return false;
}

void ULootLockerGoogleSubsystemHelper::SignInWithGoogle(int LocalUserNumber, const FLootLockerGoogleSubsystemLoginCompletedCallback Callback)
{
	InvokeGoogleLoginCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

void ULootLockerGoogleSubsystemHelper::SignOutWithGoogle(int LocalUserNumber, const FLootLockerGoogleSubsystemLogoutCompletedCallback Callback)
{
	InvokeGoogleLogoutCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

void ULootLockerGoogleSubsystemHelper::SignInWithGooglePlay(int LocalUserNumber, const FLootLockerGooglePlaySubsystemLoginCompletedCallback Callback)
{
	InvokeGooglePlayLoginCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

void ULootLockerGoogleSubsystemHelper::SignOutWithGooglePlay(int LocalUserNumber, const FLootLockerGooglePlaySubsystemLogoutCompletedCallback Callback)
{
	InvokeGooglePlayLogoutCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

FString ULootLockerGoogleSubsystemHelper::GetIDToken(int LocalUserNumber)
{
	return "";
}

void ULootLockerGoogleSubsystemHelper::ReadOfferInformation(int LocalUserNumber, const FString& OfferId, FLootLockerGoogleSubsystemReadOfferCompletedCallback Callback)
{
	InvokeReadOfferCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

void ULootLockerGoogleSubsystemHelper::PurchaseOffer(int LocalUserNumber, const FString& OfferId, bool IsConsumable, FLootLockerGoogleSubsystemPurchaseCompletedCallback Callback)
{
	InvokePurchaseCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

#endif //LOOTLOCKER_ENABLE_GOOGLESUBSYSTEMHELPER