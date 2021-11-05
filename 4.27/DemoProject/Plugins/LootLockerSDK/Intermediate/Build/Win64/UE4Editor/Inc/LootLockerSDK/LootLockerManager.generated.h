// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerCollectItemPayload;
struct FLootLockerTriggerEvent;
struct FLootLockerVerifyPurchaseIosData;
struct FLootLockerAndroidAssetPurchaseData;
struct FLootLockerAssetPurchaseData;
struct FLootLockerFinishMissionData;
enum class ELootLockerAssetFilePurpose : uint8;
struct FLootLockerAssetCandidate2;
struct FLootLockerAssetInstanceStorageItem;
enum class ELootLockerAssetFilter : uint8;
struct FLootLockerPersistentStorageItem;
struct FLootLockerGetRequests;
#ifdef LOOTLOCKERSDK_LootLockerManager_generated_h
#error "LootLockerManager.generated.h already included, missing '#pragma once' in LootLockerManager.h"
#endif
#define LOOTLOCKERSDK_LootLockerManager_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execPickDropsFromDropTable); \
	DECLARE_FUNCTION(execComputeAndLockDropTable); \
	DECLARE_FUNCTION(execSubmitScore); \
	DECLARE_FUNCTION(execGetScoreListInitial); \
	DECLARE_FUNCTION(execGetScoreList); \
	DECLARE_FUNCTION(execGetByListOfMembers); \
	DECLARE_FUNCTION(execGetMemberRank); \
	DECLARE_FUNCTION(execGetMessages); \
	DECLARE_FUNCTION(execCollectItem); \
	DECLARE_FUNCTION(execGetAllCollectables); \
	DECLARE_FUNCTION(execGetTriggeredEvents); \
	DECLARE_FUNCTION(execTriggerEvent); \
	DECLARE_FUNCTION(execActivateRentalAsset); \
	DECLARE_FUNCTION(execPollingOrderStatus); \
	DECLARE_FUNCTION(execPurchaseAssetsIOS); \
	DECLARE_FUNCTION(execPurchaseAssetsAndroid); \
	DECLARE_FUNCTION(execPurchaseAssets); \
	DECLARE_FUNCTION(execGetMaps); \
	DECLARE_FUNCTION(execFinishMission); \
	DECLARE_FUNCTION(execStartMission); \
	DECLARE_FUNCTION(execGetMission); \
	DECLARE_FUNCTION(execGetAllMissions); \
	DECLARE_FUNCTION(execDeleteFileFromAssetCandidate); \
	DECLARE_FUNCTION(execAddFileToAssetCandidate); \
	DECLARE_FUNCTION(execGetAssetCandidate); \
	DECLARE_FUNCTION(execGetAllAssetCandidates); \
	DECLARE_FUNCTION(execDeleteAssetCandidate); \
	DECLARE_FUNCTION(execUpdateAssetCandidate); \
	DECLARE_FUNCTION(execCreateAssetCandidate); \
	DECLARE_FUNCTION(execOpenLootBox); \
	DECLARE_FUNCTION(execInspectLootBox); \
	DECLARE_FUNCTION(execDeleteAKeyValuePairByIdForAssetInstance); \
	DECLARE_FUNCTION(execUpdateAKeyValuePairByIdForAssetInstance); \
	DECLARE_FUNCTION(execUpdateOneOrMoreKeyValuePairForAssetInstance); \
	DECLARE_FUNCTION(execCreateAKeyValuePairForAssetInstance); \
	DECLARE_FUNCTION(execGetAKeyValuePairByIdForAssetInstance); \
	DECLARE_FUNCTION(execGetAllKeyValuePairsToAnInstanceForAssetInstance); \
	DECLARE_FUNCTION(execGetAllKeyValuePairsForAssetInstance); \
	DECLARE_FUNCTION(execRemoveAssetFromFavourites); \
	DECLARE_FUNCTION(execAddAssetToFavourites); \
	DECLARE_FUNCTION(execGetFavouriteAssetIndices); \
	DECLARE_FUNCTION(execGetAssetBones); \
	DECLARE_FUNCTION(execGetAssetsByIds); \
	DECLARE_FUNCTION(execGetAssets); \
	DECLARE_FUNCTION(execGetContexts); \
	DECLARE_FUNCTION(execGetPlayerPersistentStorage); \
	DECLARE_FUNCTION(execDeleteItemFromPersistentStorage); \
	DECLARE_FUNCTION(execAddItemsToPersistentStorage); \
	DECLARE_FUNCTION(execGetItemFromPersistentStorage); \
	DECLARE_FUNCTION(execGetEntirePersistentStorage); \
	DECLARE_FUNCTION(execGetEquipableContextsByCharacterId); \
	DECLARE_FUNCTION(execGetEquipableContextsToDefaultCharacter); \
	DECLARE_FUNCTION(execGetOtherPlayersCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execGetCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execUnEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execUnEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execEquipAssetToCharacterByIdAndInstance); \
	DECLARE_FUNCTION(execEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execListCharacterTypes); \
	DECLARE_FUNCTION(execCreateCharacter); \
	DECLARE_FUNCTION(execUpdateCharacter); \
	DECLARE_FUNCTION(execGetCharacterLoadout); \
	DECLARE_FUNCTION(execGetPlayerName); \
	DECLARE_FUNCTION(execSetPlayerName); \
	DECLARE_FUNCTION(execSetProfilePublic); \
	DECLARE_FUNCTION(execSetProfilePrivate); \
	DECLARE_FUNCTION(execGetDLCsMigration); \
	DECLARE_FUNCTION(execInitiateDLCMigration); \
	DECLARE_FUNCTION(execGetCurrencyBalance); \
	DECLARE_FUNCTION(execCheckPlayerAssetDeactivationNotification); \
	DECLARE_FUNCTION(execCheckPlayerAssetActivationNotification); \
	DECLARE_FUNCTION(execGetOtherPlayerInfo); \
	DECLARE_FUNCTION(execSubmitXP); \
	DECLARE_FUNCTION(execGetInventory); \
	DECLARE_FUNCTION(execGetPlayerInfo); \
	DECLARE_FUNCTION(execEndSession); \
	DECLARE_FUNCTION(execVerifyPlayer); \
	DECLARE_FUNCTION(execStartSession);


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execPickDropsFromDropTable); \
	DECLARE_FUNCTION(execComputeAndLockDropTable); \
	DECLARE_FUNCTION(execSubmitScore); \
	DECLARE_FUNCTION(execGetScoreListInitial); \
	DECLARE_FUNCTION(execGetScoreList); \
	DECLARE_FUNCTION(execGetByListOfMembers); \
	DECLARE_FUNCTION(execGetMemberRank); \
	DECLARE_FUNCTION(execGetMessages); \
	DECLARE_FUNCTION(execCollectItem); \
	DECLARE_FUNCTION(execGetAllCollectables); \
	DECLARE_FUNCTION(execGetTriggeredEvents); \
	DECLARE_FUNCTION(execTriggerEvent); \
	DECLARE_FUNCTION(execActivateRentalAsset); \
	DECLARE_FUNCTION(execPollingOrderStatus); \
	DECLARE_FUNCTION(execPurchaseAssetsIOS); \
	DECLARE_FUNCTION(execPurchaseAssetsAndroid); \
	DECLARE_FUNCTION(execPurchaseAssets); \
	DECLARE_FUNCTION(execGetMaps); \
	DECLARE_FUNCTION(execFinishMission); \
	DECLARE_FUNCTION(execStartMission); \
	DECLARE_FUNCTION(execGetMission); \
	DECLARE_FUNCTION(execGetAllMissions); \
	DECLARE_FUNCTION(execDeleteFileFromAssetCandidate); \
	DECLARE_FUNCTION(execAddFileToAssetCandidate); \
	DECLARE_FUNCTION(execGetAssetCandidate); \
	DECLARE_FUNCTION(execGetAllAssetCandidates); \
	DECLARE_FUNCTION(execDeleteAssetCandidate); \
	DECLARE_FUNCTION(execUpdateAssetCandidate); \
	DECLARE_FUNCTION(execCreateAssetCandidate); \
	DECLARE_FUNCTION(execOpenLootBox); \
	DECLARE_FUNCTION(execInspectLootBox); \
	DECLARE_FUNCTION(execDeleteAKeyValuePairByIdForAssetInstance); \
	DECLARE_FUNCTION(execUpdateAKeyValuePairByIdForAssetInstance); \
	DECLARE_FUNCTION(execUpdateOneOrMoreKeyValuePairForAssetInstance); \
	DECLARE_FUNCTION(execCreateAKeyValuePairForAssetInstance); \
	DECLARE_FUNCTION(execGetAKeyValuePairByIdForAssetInstance); \
	DECLARE_FUNCTION(execGetAllKeyValuePairsToAnInstanceForAssetInstance); \
	DECLARE_FUNCTION(execGetAllKeyValuePairsForAssetInstance); \
	DECLARE_FUNCTION(execRemoveAssetFromFavourites); \
	DECLARE_FUNCTION(execAddAssetToFavourites); \
	DECLARE_FUNCTION(execGetFavouriteAssetIndices); \
	DECLARE_FUNCTION(execGetAssetBones); \
	DECLARE_FUNCTION(execGetAssetsByIds); \
	DECLARE_FUNCTION(execGetAssets); \
	DECLARE_FUNCTION(execGetContexts); \
	DECLARE_FUNCTION(execGetPlayerPersistentStorage); \
	DECLARE_FUNCTION(execDeleteItemFromPersistentStorage); \
	DECLARE_FUNCTION(execAddItemsToPersistentStorage); \
	DECLARE_FUNCTION(execGetItemFromPersistentStorage); \
	DECLARE_FUNCTION(execGetEntirePersistentStorage); \
	DECLARE_FUNCTION(execGetEquipableContextsByCharacterId); \
	DECLARE_FUNCTION(execGetEquipableContextsToDefaultCharacter); \
	DECLARE_FUNCTION(execGetOtherPlayersCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execGetCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execUnEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execUnEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execEquipAssetToCharacterByIdAndInstance); \
	DECLARE_FUNCTION(execEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execListCharacterTypes); \
	DECLARE_FUNCTION(execCreateCharacter); \
	DECLARE_FUNCTION(execUpdateCharacter); \
	DECLARE_FUNCTION(execGetCharacterLoadout); \
	DECLARE_FUNCTION(execGetPlayerName); \
	DECLARE_FUNCTION(execSetPlayerName); \
	DECLARE_FUNCTION(execSetProfilePublic); \
	DECLARE_FUNCTION(execSetProfilePrivate); \
	DECLARE_FUNCTION(execGetDLCsMigration); \
	DECLARE_FUNCTION(execInitiateDLCMigration); \
	DECLARE_FUNCTION(execGetCurrencyBalance); \
	DECLARE_FUNCTION(execCheckPlayerAssetDeactivationNotification); \
	DECLARE_FUNCTION(execCheckPlayerAssetActivationNotification); \
	DECLARE_FUNCTION(execGetOtherPlayerInfo); \
	DECLARE_FUNCTION(execSubmitXP); \
	DECLARE_FUNCTION(execGetInventory); \
	DECLARE_FUNCTION(execGetPlayerInfo); \
	DECLARE_FUNCTION(execEndSession); \
	DECLARE_FUNCTION(execVerifyPlayer); \
	DECLARE_FUNCTION(execStartSession);


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerManager(); \
	friend struct Z_Construct_UClass_ULootLockerManager_Statics; \
public: \
	DECLARE_CLASS(ULootLockerManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerManager)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerManager(); \
	friend struct Z_Construct_UClass_ULootLockerManager_Statics; \
public: \
	DECLARE_CLASS(ULootLockerManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerManager)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerManager); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerManager(ULootLockerManager&&); \
	NO_API ULootLockerManager(const ULootLockerManager&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerManager(ULootLockerManager&&); \
	NO_API ULootLockerManager(const ULootLockerManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerManager)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_28_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h_31_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
