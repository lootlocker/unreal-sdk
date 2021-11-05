// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerOpenLootBoxResponse;
struct FLootLockerLootBoxContentResponse;
struct FLootLockerAssetInstanceStorageItemsResponse;
#ifdef LOOTLOCKERSDK_LootLockerAssetInstancesRequestHandler_generated_h
#error "LootLockerAssetInstancesRequestHandler.generated.h already included, missing '#pragma once' in LootLockerAssetInstancesRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerAssetInstancesRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_67_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerOpenLootBoxResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerOpenLootBoxResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_59_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerLootBoxContentResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerLootBoxContentResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_45_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerLootBoxItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerLootBoxItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageItemsResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetInstanceStorageItemsResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_30_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageItems_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetInstanceStorageItems>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageResponseItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerAssetInstanceStorageItem Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetInstanceStorageResponseItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetInstanceStorageItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_74_DELEGATE \
struct _Script_LootLockerSDK_eventOpenLootBoxResponseDelegateBP_Parms \
{ \
	FLootLockerOpenLootBoxResponse Response; \
}; \
static inline void FOpenLootBoxResponseDelegateBP_DelegateWrapper(const FScriptDelegate& OpenLootBoxResponseDelegateBP, FLootLockerOpenLootBoxResponse Response) \
{ \
	_Script_LootLockerSDK_eventOpenLootBoxResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	OpenLootBoxResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_73_DELEGATE \
struct _Script_LootLockerSDK_eventLootBoxContentResponseDelegateBP_Parms \
{ \
	FLootLockerLootBoxContentResponse Response; \
}; \
static inline void FLootBoxContentResponseDelegateBP_DelegateWrapper(const FScriptDelegate& LootBoxContentResponseDelegateBP, FLootLockerLootBoxContentResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootBoxContentResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	LootBoxContentResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_72_DELEGATE \
struct _Script_LootLockerSDK_eventAssetInstanceStorageItemsResponseDelegateBP_Parms \
{ \
	FLootLockerAssetInstanceStorageItemsResponse Response; \
}; \
static inline void FAssetInstanceStorageItemsResponseDelegateBP_DelegateWrapper(const FScriptDelegate& AssetInstanceStorageItemsResponseDelegateBP, FLootLockerAssetInstanceStorageItemsResponse Response) \
{ \
	_Script_LootLockerSDK_eventAssetInstanceStorageItemsResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	AssetInstanceStorageItemsResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerAssetInstancesRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerAssetInstancesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerAssetInstancesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerAssetInstancesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerAssetInstancesRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerAssetInstancesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerAssetInstancesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerAssetInstancesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerAssetInstancesRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerAssetInstancesRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerAssetInstancesRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerAssetInstancesRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerAssetInstancesRequestHandler(ULootLockerAssetInstancesRequestHandler&&); \
	NO_API ULootLockerAssetInstancesRequestHandler(const ULootLockerAssetInstancesRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerAssetInstancesRequestHandler(ULootLockerAssetInstancesRequestHandler&&); \
	NO_API ULootLockerAssetInstancesRequestHandler(const ULootLockerAssetInstancesRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerAssetInstancesRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerAssetInstancesRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerAssetInstancesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_79_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h_83_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerAssetInstancesRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAssetInstancesRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
