// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerActivateRentalAssetResponse;
struct FLootLockerPurchaseStatusResponse;
struct FLootLockerPurchaseResponse;
#ifdef LOOTLOCKERSDK_LootLockerPurchasesRequestHandler_generated_h
#error "LootLockerPurchasesRequestHandler.generated.h already included, missing '#pragma once' in LootLockerPurchasesRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerPurchasesRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_58_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerActivateRentalAssetResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerActivateRentalAssetResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_50_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPurchaseStatusResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPurchaseStatusResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_40_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPurchaseResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPurchaseResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_32_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerVerifyPurchaseIosData_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerVerifyPurchaseIosData>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_25_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAndroidAssetPurchaseData_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerAssetPurchaseData Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAndroidAssetPurchaseData>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetPurchaseData_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetPurchaseData>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_65_DELEGATE \
struct _Script_LootLockerSDK_eventActivateRentalAssetResponseDelegateBP_Parms \
{ \
	FLootLockerActivateRentalAssetResponse Response; \
}; \
static inline void FActivateRentalAssetResponseDelegateBP_DelegateWrapper(const FScriptDelegate& ActivateRentalAssetResponseDelegateBP, FLootLockerActivateRentalAssetResponse Response) \
{ \
	_Script_LootLockerSDK_eventActivateRentalAssetResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	ActivateRentalAssetResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_64_DELEGATE \
struct _Script_LootLockerSDK_eventPurchaseStatusResponseDelegateBP_Parms \
{ \
	FLootLockerPurchaseStatusResponse Response; \
}; \
static inline void FPurchaseStatusResponseDelegateBP_DelegateWrapper(const FScriptDelegate& PurchaseStatusResponseDelegateBP, FLootLockerPurchaseStatusResponse Response) \
{ \
	_Script_LootLockerSDK_eventPurchaseStatusResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	PurchaseStatusResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_63_DELEGATE \
struct _Script_LootLockerSDK_eventPurchaseResponseDelegateBP_Parms \
{ \
	FLootLockerPurchaseResponse Response; \
}; \
static inline void FPurchaseResponseDelegateBP_DelegateWrapper(const FScriptDelegate& PurchaseResponseDelegateBP, FLootLockerPurchaseResponse Response) \
{ \
	_Script_LootLockerSDK_eventPurchaseResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	PurchaseResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerPurchasesRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerPurchasesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerPurchasesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerPurchasesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerPurchasesRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerPurchasesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerPurchasesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerPurchasesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerPurchasesRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerPurchasesRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerPurchasesRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerPurchasesRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerPurchasesRequestHandler(ULootLockerPurchasesRequestHandler&&); \
	NO_API ULootLockerPurchasesRequestHandler(const ULootLockerPurchasesRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerPurchasesRequestHandler(ULootLockerPurchasesRequestHandler&&); \
	NO_API ULootLockerPurchasesRequestHandler(const ULootLockerPurchasesRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerPurchasesRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerPurchasesRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerPurchasesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_70_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h_73_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerPurchasesRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPurchasesRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
