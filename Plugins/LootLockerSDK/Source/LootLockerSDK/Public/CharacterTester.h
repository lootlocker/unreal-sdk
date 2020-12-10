// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterRequestHandler.h"
#include "LootLockerSDKManager.h"
#include "CharacterTester.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ACharacterTester : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterTester();
	void OnGetCharacterLoadoutRequestCompleted(FCharacterLoadoutResponse var);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		ULootLockerSDKManager* LootLockerSDKManager;
};
