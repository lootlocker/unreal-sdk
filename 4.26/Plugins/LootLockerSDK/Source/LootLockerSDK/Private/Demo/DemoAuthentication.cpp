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
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnStartSession Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnStartSession Failed"));
    }
}

void ADemoAuthentication::OnVerifyPlayerCompleted(FAuthenticationDefaultResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayer Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayer Failed"));
    }
}

void ADemoAuthentication::OnEndSessionCompleted(FAuthenticationDefaultResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnEndSession Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnEndSession Failed"));
    }
}
