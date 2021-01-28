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
    
    void OnStartSessionCompleted(FAuthenticationResponse Response);
    void OnVerifyPlayerCompleted(FAuthenticationDefaultResponse Response);
    void OnEndSessionCompleted(FAuthenticationDefaultResponse Response);
    UFUNCTION(BlueprintCallable, CallInEditor, Category = "LootLocker Demo | Authentication")
    static FString GetSteamIdentityToken();

    
private:
    ULootLockerSDKManager* LootLockerManager;
};
