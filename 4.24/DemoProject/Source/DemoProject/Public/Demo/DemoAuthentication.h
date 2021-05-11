// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerSDKManager.h"
#include "Online.h"
#include "DemoAuthentication.generated.h"

class IOnlineSubsystem;

UCLASS()
class DEMOPROJECT_API ADemoAuthentication : public AActor
{
public:
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString PlayerId;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString SteamToken;
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoStartSession();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoVerifyPlayer();
    
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    void DemoEndSession();
    
    void OnStartSessionCompleted(FLootLockerAuthenticationResponse Response);
    void OnVerifyPlayerCompleted(FLootLockerAuthenticationDefaultResponse Response);
    void OnEndSessionCompleted(FLootLockerAuthenticationDefaultResponse Response);
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    static FString GetSteamSessionTicket();

    
private:
    ULootLockerSDKManager* LootLockerManager;
};
