// Copyright (c) 2020 LootLocker

#include "Demo/DemoPlayers.h"


void ADemoPlayers::DemoGetPlayerInfo()
{
   ULootLockerSDKManager::GetPlayerInfo(FLootLockerPlayerInformationResponse::CreateUObject(this, &ADemoPlayers::OnGetPlayerInfoCompleted));
}

void ADemoPlayers::DemoGetInventory()
{
   ULootLockerSDKManager::GetInventory(FLootLockerInventoryResponse::CreateUObject(this, &ADemoPlayers::OnGetInventoryCompleted));
}

void ADemoPlayers::DemoSubmitXp()
{
   ULootLockerSDKManager::SubmitXP(points, FLootLockerSubmitXpResponse::CreateUObject(this, &ADemoPlayers::OnSubmitXpCompleted));
}

void ADemoPlayers::DemoGetOtherPlayerInfo()
{
   ULootLockerSDKManager::GetOtherPlayerInfo(getRequests, FLootLockerPlayerInformationResponse::CreateUObject(this, &ADemoPlayers::OnGetOtherPlayerInfoCompleted));
}

void ADemoPlayers::DemoCheckPlayerAssetNotification()
{
   ULootLockerSDKManager::CheckPlayerAssetActivationNotification(FLootLockerAssetNotificationResponse::CreateUObject(this, &ADemoPlayers::OnCheckPlayerAssetNotificationCompleted));
}

void ADemoPlayers::DemoCheckPlayerAssetDeactivationNotification()
{
   ULootLockerSDKManager::CheckPlayerAssetDeactivationNotification(FLootLockerAssetNotificationResponse::CreateUObject(this, &ADemoPlayers::OnCheckPlayerAssetDeactivationNotificationCompleted));
}

void ADemoPlayers::OnGetPlayerInfoCompleted(FPlayerInfoResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetPlayerInfoCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPlayers::OnGetInventoryCompleted(FInventoryResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetInventoryCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPlayers::OnSubmitXpCompleted(FSubmitXpResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnSubmitXpCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPlayers::OnGetOtherPlayerInfoCompleted(FPlayerInfoResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetOtherPlayerInfoCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPlayers::OnCheckPlayerAssetNotificationCompleted(FPlayerAssetNotificationResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnCheckPlayerAssetNotificationCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoPlayers::OnCheckPlayerAssetDeactivationNotificationCompleted(FPlayerAssetNotificationResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnCheckPlayerAssetDeactivationNotificationCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
