// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerSessionOptionals.h"
#include "LootLockerPlayerData.generated.h"

USTRUCT(BlueprintType, Category = "LootLocker")
struct LOOTLOCKERSDK_API FLootLockerPlayerData
{
	GENERATED_BODY()
public:
	/**
	 The session token stored for this player session
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString Token = "";
	/**
	The Token to use when refreshing the session (only present for authentication methods that support it)
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString RefreshToken = "";
	/**
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString PlayerIdentifier = "";
	/**
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString PlayerUlid = "";
	/**
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString PlayerPublicUid = "";
	/**
	The name of the player if any has been set
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString PlayerName = "";
	/**
	If this player is authorized using White Label, then this stores the email that was used
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString WhiteLabelEmail = "";
	/**
	If this player is authorized using white label, then this stores the token for authorizing the player with the White Label system
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString WhiteLabelToken = "";
	/**
	The platform/authentication method used to authorize this player
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FLootLockerPlatformRepresentation CurrentPlatform;
	/**
	When this player was last authenticated
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString LastSignIn = "";
	/**
	When this player was first created
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FString PlayerCreatedAt = "";
	/**
	The session optionals that were used when starting the current session for this player
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LootLocker")
	FLootLockerSessionOptionals SessionOptionals;
	

	static FLootLockerPlayerData Create(const FString& token = "", const FString& refreshToken = "", const FString& playerIdentifier = "", const FString& playerUlid = "", const FString& playerPublicUid = "", const FString& playerName = "", const FString& whiteLabelEmail = "", const FString& whiteLabelToken = "", const FLootLockerPlatformRepresentation& currentPlatform = FLootLockerPlatformRepresentation(), const FString& lastSignIn = "", const FString& playerCreatedAt = "", const FLootLockerSessionOptionals& sessionOptionals = FLootLockerSessionOptionals())
	{
		FLootLockerPlayerData NewObj;
		NewObj.Token = token;
		NewObj.RefreshToken = refreshToken;
		NewObj.PlayerIdentifier = playerIdentifier;
		NewObj.PlayerUlid = playerUlid;
		NewObj.PlayerPublicUid = playerPublicUid;
		NewObj.PlayerName = playerName;
		NewObj.WhiteLabelEmail = whiteLabelEmail;
		NewObj.WhiteLabelToken = whiteLabelToken;
		NewObj.CurrentPlatform = currentPlatform;
		NewObj.LastSignIn = lastSignIn;
		NewObj.PlayerCreatedAt = playerCreatedAt;
		NewObj.SessionOptionals = sessionOptionals;
		return NewObj;
	}
};
