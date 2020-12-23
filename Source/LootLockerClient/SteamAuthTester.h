// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerSDKManager.h"
#include "Online.h"
#include "GameAPI/AuthenticationRequestHandler.h"
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
