// Copyright (c) 2021 LootLocker

#include "LootLockerSteamSubsystemHelper.h"

#ifdef LOOTLOCKER_ENABLE_STEAMSUBSYSTEMHELPER
#include "OnlineSubsystem.h"
#include "OnlineError.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlinePurchaseInterface.h"
#endif

DEFINE_LOG_CATEGORY(LogLootLockerSDKSteamSubsystemHelper);

bool ULootLockerSteamSubsystemHelper::IsInitialized = false;
FDelegateHandle ULootLockerSteamSubsystemHelper::LoginDelegateHandle = FDelegateHandle();
FDelegateHandle ULootLockerSteamSubsystemHelper::LogoutDelegateHandle = FDelegateHandle();

#pragma region Logging Functions

void ULootLockerSteamSubsystemHelper::InvokeSteamLoginCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerSteamSubsystemLoginCompletedCallback Callback)
{
	UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *Message);
	Callback.ExecuteIfBound(false, LocalUserNumber, Message, "");
}

void ULootLockerSteamSubsystemHelper::InvokeSteamLogoutCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerSteamSubsystemLogoutCompletedCallback Callback)
{
	UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *Message);
	Callback.ExecuteIfBound(false, LocalUserNumber, Message);
}

#pragma endregion

#ifdef LOOTLOCKER_ENABLE_STEAMSUBSYSTEMHELPER
void ULootLockerSteamSubsystemHelper::Initialize()
{
	if (IsInitialized)
	{
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Verbose, TEXT("ULootLockerSteamSubsystemHelper already initialized"));
		return;
	}

	if (HasSteamOnlineSubsystem())
	{
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("Could not get Steam Subsystem, Steam connected functionality will not work"));
		return;
	}
	IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSubsystemSteam == nullptr || !OnlineSubsystemSteam->Init())
	{
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("Steam Subsystem could not be initialized, Steam connected functionality will not work"));
	}

	IsInitialized = true;
}

bool ULootLockerSteamSubsystemHelper::HasSteamOnlineSubsystem()
{
	const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSubsystemSteam == nullptr)
	{
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("Could not get Steam Subsystem"));
		return false;
	}

	return true;
}

bool ULootLockerSteamSubsystemHelper::IsLoggedIn(int LocalUserNumber)
{
	const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSubsystemSteam == nullptr)
	{
		return false;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemSteam->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		return false;
	}

	return (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn);
}

void ULootLockerSteamSubsystemHelper::SignInWithSteam(int LocalUserNumber, const FLootLockerSteamSubsystemLoginCompletedCallback Callback)
{
	if (!IsInitialized)
	{
		Initialize();
	}

	if (LoginDelegateHandle.IsValid())
	{
		InvokeSteamLoginCallbackWithErrorResponseAndLog("A Login is already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSubsystemSteam == nullptr)
	{
		InvokeSteamLoginCallbackWithErrorResponseAndLog("Could not get Steam Subsystem", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemSteam->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeSteamLoginCallbackWithErrorResponseAndLog("Could not get a valid Identity Interface", LocalUserNumber, Callback);
		return;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) == ELoginStatus::LoggedIn)
	{
		// User already signed in, treat it as a successful login attempt
		Callback.ExecuteIfBound(true, LocalUserNumber, "", GetAuthToken(LocalUserNumber).AuthToken);
		return;
	}

	LoginDelegateHandle = IdentityInterface->AddOnLoginCompleteDelegate_Handle(
		LocalUserNumber, FOnLoginCompleteDelegate::CreateLambda(
			[Callback](int LocalUserNumber, bool wasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				if (!wasSuccessful)
				{
					InvokeSteamLoginCallbackWithErrorResponseAndLog(FString::Format(TEXT("ULootLockerSteamSubsystemHelper Steam Login failed with message: {0}"), { Error }), LocalUserNumber, Callback);
				}
				else
				{
					Callback.ExecuteIfBound(true, LocalUserNumber, "", GetAuthToken(LocalUserNumber).AuthToken);
				}

				// Clear state
				if (LoginDelegateHandle.IsValid())
				{
					if (const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM))
					{
						const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemSteam->GetIdentityInterface();
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

void ULootLockerSteamSubsystemHelper::SignOutWithSteam(int LocalUserNumber, const FLootLockerSteamSubsystemLogoutCompletedCallback Callback)
{
	if (!IsInitialized)
	{
		Initialize();
	}

	if (LoginDelegateHandle.IsValid())
	{
		InvokeSteamLogoutCallbackWithErrorResponseAndLog("Don't log out when logging in", LocalUserNumber, Callback);
		return;
	}

	if (LogoutDelegateHandle.IsValid())
	{
		InvokeSteamLogoutCallbackWithErrorResponseAndLog("Logout process already in progress", LocalUserNumber, Callback);
		return;
	}

	const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSubsystemSteam == nullptr)
	{
		InvokeSteamLogoutCallbackWithErrorResponseAndLog("Could not get Steam Subsystem", LocalUserNumber, Callback);
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemSteam->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		InvokeSteamLogoutCallbackWithErrorResponseAndLog("Could not get a valid Identity Interface", LocalUserNumber, Callback);
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
				InvokeSteamLogoutCallbackWithErrorResponseAndLog(FString::Format(TEXT("ULootLockerSteamSubsystemHelper Steam Logout failed for local user number: {0}"), { LocalUserNumber }), LocalUserNumber, Callback);
				return;
			}

			Callback.ExecuteIfBound(success, LocalUserNumber, "");

			// Clear state
			if (LogoutDelegateHandle.IsValid())
			{
				if (const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM))
				{
					const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemSteam->GetIdentityInterface();
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

FLootLockerSteamSubsystemAuthTokenResult ULootLockerSteamSubsystemHelper::GetAuthToken(int LocalUserNumber)
{
	FLootLockerSteamSubsystemAuthTokenResult Result
		{
			true,
			"",
			"",
			LocalUserNumber,
			""
		};
	const IOnlineSubsystem* OnlineSubsystemSteam = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
	if (OnlineSubsystemSteam == nullptr)
	{
		Result.Success = false;
		Result.Error = "Could not get Steam Subsystem";
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Error, TEXT("%s"), *Result.Error);
		return Result;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystemSteam->GetIdentityInterface();
	if (IdentityInterface == nullptr || !IdentityInterface.IsValid())
	{
		Result.Success = false;
		Result.Error = "Could not get Steam Identity Interface";
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *Result.Error);
		return Result;
	}

	if (IdentityInterface->GetLoginStatus(LocalUserNumber) != ELoginStatus::LoggedIn)
	{
		Result.Success = false;
		Result.Error = FString::Format(TEXT("No Steam user logged in for local user number {0}"), { LocalUserNumber });
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *Result.Error);
		return Result;
	}

	Result.AuthToken = IdentityInterface->GetAuthToken(LocalUserNumber);
	if (Result.AuthToken.IsEmpty())
	{
		Result.Success = false;
		Result.Error = FString::Format(TEXT("Could not get Steam Auth Token for local user number {0}"), { LocalUserNumber });
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *Result.Error);
		return Result;
	}

	const TSharedPtr<const FUniqueNetId> UniqueIdPtr = IdentityInterface->GetUniquePlayerId(LocalUserNumber);
	if (!UniqueIdPtr.IsValid())
	{
		Result.Success = false;
		Result.Error = FString::Format(TEXT("Could not get Steam Player ID for local user number {0}"), { LocalUserNumber });
		UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *Result.Error);
		return Result;
	}

	Result.SteamID = UniqueIdPtr->ToString();
	return Result;
}

#else //LOOTLOCKER_ENABLE_STEAMSUBSYSTEMHELPER

const FString NOT_ENABLED_WARNING = "Steam Subsystem is not enabled in LootLocker. To enable it, add `LootLockerSDK.bEnableSteamSubsystemHelper = true;` to your games Build.cs file";

void ULootLockerSteamSubsystemHelper::Initialize()
{
	UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *NOT_ENABLED_WARNING);
	return;
}

bool ULootLockerSteamSubsystemHelper::HasSteamOnlineSubsystem()
{
	UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *NOT_ENABLED_WARNING);
	return false;
}

bool ULootLockerSteamSubsystemHelper::IsLoggedIn(int LocalUserNumber)
{
	UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *NOT_ENABLED_WARNING);
	return false;
}

void ULootLockerSteamSubsystemHelper::SignInWithSteam(int LocalUserNumber, const FLootLockerSteamSubsystemLoginCompletedCallback Callback)
{
	InvokeSteamLoginCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

void ULootLockerSteamSubsystemHelper::SignOutWithSteam(int LocalUserNumber, const FLootLockerSteamSubsystemLogoutCompletedCallback Callback)
{
	InvokeSteamLogoutCallbackWithErrorResponseAndLog(NOT_ENABLED_WARNING, LocalUserNumber, Callback);
}

FLootLockerSteamSubsystemAuthTokenResult ULootLockerSteamSubsystemHelper::GetAuthToken(int LocalUserNumber)
{
	UE_LOG(LogLootLockerSDKSteamSubsystemHelper, Warning, TEXT("%s"), *NOT_ENABLED_WARNING);
	FLootLockerSteamSubsystemAuthTokenResult Result
	{
		false,
		"",
		"",
		LocalUserNumber,
		NOT_ENABLED_WARNING
	};
	return Result;
}
#endif //LOOTLOCKER_ENABLE_STEAMSUBSYSTEMHELPER