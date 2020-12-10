// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "AuthenticationRequestHandler.h"
#include "LootLockerSDKManager.h"
//#include <Runtime/UMG/Public/Components/TextBlock.h>
#include "AuthTester.generated.h"


/**
 *
 */
UCLASS()
class LOOTLOCKERSDK_API AAuthTester : public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION()
		void OnAuthCompleted(FAuthenticationResponse AuthVar);
	UPROPERTY(EditAnywhere)
		ULootLockerSDKManager* LootLockerSDKManager;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
