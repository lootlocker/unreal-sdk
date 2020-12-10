// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterTester.h"

// Sets default values
ACharacterTester::ACharacterTester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterTester::BeginPlay()
{
	Super::BeginPlay();
	LootLockerSDKManager = NewObject<ULootLockerSDKManager>();
	LootLockerSDKManager->GetCharacterLoadout(FLootLockerCharacterLoadoutResponse::CreateUObject(this, &ACharacterTester::OnGetCharacterLoadoutRequestCompleted));
}

// Called every frame
void ACharacterTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACharacterTester::OnGetCharacterLoadoutRequestCompleted(FCharacterLoadoutResponse var)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *var.FullTextFromServer, var.success ? TEXT("true") : TEXT("false"));
}