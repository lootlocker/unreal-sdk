// Copyright (c) 2021 LootLocker

#include "Demo/DemoAuthentication.h"

FString ADemoAuthentication::GetSteamSessionTicket()
{
    IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
    FString IdentityToken = OnlineSub->GetIdentityInterface()->GetAuthToken(0);
	return IdentityToken;
}

void ADemoAuthentication::DemoStartSession()
{
   ULootLockerSDKManager::StartSession(PlayerId, FLootLockerSessionResponse::CreateUObject(this, &ADemoAuthentication::OnStartSessionCompleted));
}

void ADemoAuthentication::DemoVerifyPlayer()
{
    ULootLockerSDKManager::VerifyPlayer(GetSteamSessionTicket(), FLootLockerDefaultAuthenticationResponse::CreateUObject(this, &ADemoAuthentication::OnVerifyPlayerCompleted));
}

void ADemoAuthentication::DemoEndSession()
{
    ULootLockerSDKManager::EndSession(FLootLockerDefaultAuthenticationResponse::CreateUObject(this, &ADemoAuthentication::OnEndSessionCompleted));
}

void ADemoAuthentication::OnStartSessionCompleted(FLootLockerAuthenticationResponse Response)
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

void ADemoAuthentication::OnVerifyPlayerCompleted(FLootLockerAuthenticationDefaultResponse Response)
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

void ADemoAuthentication::OnEndSessionCompleted(FLootLockerAuthenticationDefaultResponse Response)
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
