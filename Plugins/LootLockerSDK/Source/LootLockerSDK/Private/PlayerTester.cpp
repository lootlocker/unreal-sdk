// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTester.h"

// Sets default values
APlayerTester::APlayerTester()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerTester::BeginPlay()
{
	Super::BeginPlay();
	LootLockerSDKManager = NewObject<ULootLockerSDKManager>();
	LootLockerSDKManager->GetPlayerInfo(FLootLockerPlayerInformationResponse::CreateUObject(this, &APlayerTester::OnGetPlayerInfoRequestCompleted));
}

// Called every frame
void APlayerTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APlayerTester::OnGetPlayerInfoRequestCompleted(FPlayerInfoResponse response)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *response.FullTextFromServer, response.success ? TEXT("true") : TEXT("false"));
}


void APlayerTester::OnInventoryRequestCompleted(FInventoryResponse response)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *response.FullTextFromServer, response.success ? TEXT("true") : TEXT("false"));
}


void APlayerTester::OnSubmitXpRequestCompleted(FSubmitXpResponse response)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *response.FullTextFromServer, response.success ? TEXT("true") : TEXT("false"));
}



void APlayerTester::OnGetOtherPlayerInfoRequestCompleted(FPlayerInfoResponse response)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *response.FullTextFromServer, response.success ? TEXT("true") : TEXT("false"));
}


void APlayerTester::OnCheckPlayerAssetNotificationRequestCompleted(FPlayerAssetNotificationResponse response)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *response.FullTextFromServer, response.success ? TEXT("true") : TEXT("false"));
}


void APlayerTester::OnCheckPlayerAssetDeactivationNotificationRequestCompleted(FPlayerAssetNotificationResponse response)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *response.FullTextFromServer, response.success ? TEXT("true") : TEXT("false"));
}
