// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthTester.h"

void AAuthTester::OnAuthCompleted(FAuthenticationResponse AuthVar) 
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s and balance %f"), *AuthVar.FullTextFromServer, AuthVar.success ? TEXT("true") : TEXT("false"), AuthVar.account_balance);
}

// Called when the game starts or when spawned
void AAuthTester::BeginPlay()
{
	Super::BeginPlay();
	LootLockerSDKManager = NewObject<ULootLockerSDKManager>();
	FString playerId = TEXT("dgehrthrty");
	LootLockerSDKManager->StartSession(playerId, FLootLockerSessionResponse::CreateUObject(this, &AAuthTester::OnAuthCompleted));
}

// Called every frame
void AAuthTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
