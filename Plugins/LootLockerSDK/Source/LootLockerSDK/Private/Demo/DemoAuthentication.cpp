// Copyright (c) 2020 LootLocker

#include "Demo/DemoAuthentication.h"


void ADemoAuthentication::DemoStartSession()
{
   ULootLockerSDKManager::StartSession(PlayerId, FLootLockerSessionResponse::CreateUObject(this, &ADemoAuthentication::OnStartSessionCompleted));
}

void ADemoAuthentication::DemoVerifyPlayer()
{
   ULootLockerSDKManager::VerifyPlayer(SteamToken, FLootLockerDefaultAuthenticationResponse::CreateUObject(this, &ADemoAuthentication::OnVerifyPlayerCompleted));
}

void ADemoAuthentication::DemoEndSession()
{
   ULootLockerSDKManager::EndSession(PlayerId, FLootLockerDefaultAuthenticationResponse::CreateUObject(this, &ADemoAuthentication::OnEndSessionCompleted));
}

void ADemoAuthentication::OnStartSessionCompleted(FAuthenticationResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnStartSessionCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAuthentication::OnVerifyPlayerCompleted(FAuthenticationDefaultResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayerCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoAuthentication::OnEndSessionCompleted(FAuthenticationDefaultResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnEndSessionCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
