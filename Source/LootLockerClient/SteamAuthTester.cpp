// Copyright (c) 2020 LootLocker


#include "SteamAuthTester.h"



//void USteamAuthTester::VerifyPlayerBlue()
//{
//	FString IdentityToken = OnlineSub->GetIdentityInterface()->GetAuthToken(0);
//
//	return IdentityToken;
////	playerVerifyResponse.AddDynamic(this, &USteamAuthTester::OnVerifyPlayerRequestCompleted);
//	//ULootLockerSDKManager::VerifyPlayer(IdentityToken, &playerVerifyResponse);
//}

void USteamAuthTester::VerifyPlayer(FString steamSessionTicket)
{
//	playerVerifyResponse.AddDynamic(this, &USteamAuthTester::OnVerifyPlayerRequestCompleted);
//	LootLockerSDKManager->VerifyPlayer(steamSessionTicket, playerVerifyResponse);
}

FString USteamAuthTester::VerifyPlayerBlue()
{
	FString IdentityToken = OnlineSub->GetIdentityInterface()->GetAuthToken(0);

	return IdentityToken;
}

void USteamAuthTester::OnVerifyPlayerRequestCompleted(FAuthenticationDefaultResponse AuthVar)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *AuthVar.FullTextFromServer, AuthVar.success ? TEXT("true") : TEXT("false"));
}

void USteamAuthTester::AuthPlayer(FString steamId64)
{
//	playerAuthResponse.AddDynamic(this, &USteamAuthTester::OnAuthPlayerRequestCompleted);
//	LootLockerSDKManager->StartSession(steamId64, playerAuthResponse);
}

void USteamAuthTester::OnAuthPlayerRequestCompleted(FAuthenticationResponse  AuthVar)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s response status %s"), *AuthVar.FullTextFromServer, AuthVar.success ? TEXT("true") : TEXT("false"));
}
//// Called when the game starts or when spawned
//void USteamAuthTester::BeginPlay()
//{
//	Super::BeginPlay();
//	FString IdentityToken = OnlineSub->GetIdentityInterface()->GetAuthToken(0);
//	UE_LOG(LogTemp, Warning, TEXT("Data from server: %s"), *IdentityToken)
//	//VerifyPlayer(IdentityToken);
//
//}
//
//// Called every frame
//void ASteamAuthTester::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

