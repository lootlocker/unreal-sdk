// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "LootLockerConfig.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerResponse
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool success;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ServerCallHasError;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ServerCallStatusCode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FullTextFromServer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ServerError;
};

UENUM(BlueprintType)
enum class ELootLockerHTTPMethod : uint8
{
	GET = 0         UMETA(DisplayName = "GET"),
	POST = 1        UMETA(DisplayName = "POST"),
	DELETE = 2      UMETA(DisplayName = "DELETE"),
	PUT = 3         UMETA(DisplayName = "PUT"),
	HEAD = 4        UMETA(DisplayName = "HEAD"),
	CREATE = 5      UMETA(DisplayName = "CREATE"),
	OPTIONS = 6     UMETA(DisplayName = "OPTIONS"),
	PATCH = 7       UMETA(DisplayName = "PATCH"),
	UPLOAD = 8      UMETA(DisplayName = "UPLOAD")
};

UENUM(BlueprintType)
enum class ELootLockerPlatformType : uint8
{
	Android = 0				UMETA(DisplayName = "Android"),
	Ios = 1					UMETA(DisplayName = "Ios"),
	Steam = 2				UMETA(DisplayName = "Steam"),
	NintendoSwitch = 3		UMETA(DisplayName = "NintendoSwitch"),
	EpicStore = 3			UMETA(DisplayName = "EpicStore"),
	PlayStationNetwork = 3  UMETA(DisplayName = "PlayStationNetwork"),
	Xbox = 3				UMETA(DisplayName = "Xbox"),
	GoG = 3					UMETA(DisplayName = "GoG")
};

USTRUCT(BlueprintType)
struct FEndPoints
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString endpoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ELootLockerHTTPMethod requestMethod;
};

USTRUCT(BlueprintType)
struct FLootLockerGetRequests
{
	GENERATED_BODY()
	TArray<FStringFormatArg> args;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponseCallbackBP, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FResponseCallback, FLootLockerResponse);

UCLASS(Config = LootLockerSDK)
class LOOTLOCKERSDK_API ULootLockerConfig : public UObject
{
	GENERATED_BODY()
public:
	static FString GetEnum(const TCHAR* Enum, int32 EnumValue);
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FString ApiBaseUrl;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FString LootLockerGameKey;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	ELootLockerPlatformType Platform;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FString PlayerIdentifier;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FString GameVersion;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	bool OnDevelopmentMode = 1;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	bool AllowTokenRefresh = 0;

	//Auth
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints StartSessionEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints VerifyPlayerIdEndPoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints EndSessionEndpoint;

	//Player
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetPlayerInfoEndPoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetPlayerInventoryEndPoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints SubmitXpEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetOtherPlayerInfoEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints CheckPlayerAssetActivationEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints CheckPlayerAssetDeactivatonEndpoint;

	//Character
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetCharacterLoadoutEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints UpdateCharacterEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints EquipAssetToDefaultCharacterEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints EquipAssetToCharacterByIdEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints UnEquipAssetToDefaultCharacterEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints UnEquipAssetToCharacterByIdEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetCurrentLoadoutToDefaultCharacterEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetOtherPlayersLoadoutToDefaultCharacterEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetEquippableContextstoDefaultCharacterEndpoint;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK")
	FEndPoints GetEquippableContextsByCharacterIDEndpoint;
    
    //Persistent Storage
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Persistent Storage")
    FEndPoints GetEntirePersistentStorageEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Persistent Storage")
    FEndPoints GetItemFromPersistentStorageEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Persistent Storage")
    FEndPoints AddItemsToPersistentStorageEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Persistent Storage")
    FEndPoints DeleteItemFromPersistentStorageEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Persistent Storage")
    FEndPoints GetPlayerPersistentStorageEndpoint;
    
    //Assets
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints GetContextsEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints GetAssetsEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints GetAssetsByIdsEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints GetAssetBonesEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints GetFavouriteAssetIndicesEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints AddAssetToFavouritesEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Assets")
    FEndPoints RemoveAssetFromFavouritesEndpoint;
    
    //Asset Instances
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints GetKeyValuePairsForAssetInstanceEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints GetKeyValuePairForAssetInstanceEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints CreateStorageItemForAssetInstanceEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints UpdateStorageItemsForAssetInstanceEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints UpdateStorageItemForAssetInstanceEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints DeleteStorageItemForAssetInstanceEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints InspectLootBoxEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Asset Instances")
    FEndPoints OpenLootBoxEndpoint;
    
    //User Generated Content
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints CreateAssetCandidateEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints UpdateAssetCandidateEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints DeleteAssetCandidateEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints GetAllAssetCandidatesEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints GetAssetCandidateEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints AddFileToAssetCandidateEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | User Generated Content")
    FEndPoints DeleteFileFromAssetCandidateEndpoint;
    
    //Missions
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Missions")
    FEndPoints GetAllMissionsEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Missions")
    FEndPoints GetMissionEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Missions")
    FEndPoints StartMissionEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Missions")
    FEndPoints FinishMissionEndpoint;
    
    //Maps
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Maps")
    FEndPoints GetAllMapsEndpoint;
    
    //Purchases
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Purchases")
    FEndPoints PurchaseAssetsEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Purchases")
    FEndPoints VerifyPurchaseIosEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Purchases")
    FEndPoints PollPurchaseStatusEndpoint;
    UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "LootLockerSDK | Purchases")
    FEndPoints ActivateRentalAssetEndpoint;
};
