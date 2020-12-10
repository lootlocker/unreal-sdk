// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootLockerSDKManager.h"
#include "LootLockerEndpoint.h"
#include "Online.h"
#include "AuthenticationRequestHandler.h"
#include "SteamAuthTester.generated.h"

class IOnlineSubsystem;

UCLASS(Blueprintable)
class LOOTLOCKERCLIENT_API USteamAuthTester : public UObject
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintAssignable)
		FAuthDefaultResponseBP playerVerifyResponse;
	UFUNCTION(BlueprintCallable, Category = "LootLocker")
		void VerifyPlayer(FString steamSessionTicket);
	UFUNCTION(BlueprintCallable, Category = "LootLocker")
		FString VerifyPlayerBlue();
	UFUNCTION(BlueprintCallable, Category = "LootLocker")
		void OnVerifyPlayerRequestCompleted(FAuthenticationDefaultResponse AuthVar);

	UPROPERTY(BlueprintAssignable)
		FAuthResponseBP  playerAuthResponse;
	UFUNCTION(BlueprintCallable, Category = "LootLocker")
		void AuthPlayer(FString steamId64);
	UFUNCTION(BlueprintCallable, Category = "LootLocker")
		void OnAuthPlayerRequestCompleted(FAuthenticationResponse  AuthVar);
	IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();

	UPROPERTY(EditAnywhere)
		ULootLockerSDKManager* LootLockerSDKManager;

};
