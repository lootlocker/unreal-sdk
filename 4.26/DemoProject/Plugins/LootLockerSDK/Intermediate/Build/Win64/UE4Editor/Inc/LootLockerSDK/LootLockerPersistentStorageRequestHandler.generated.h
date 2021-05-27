// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerPersistentStorageItemResponse;
struct FLootLockerPersistentStorageItemsResponse;
#ifdef LOOTLOCKERSDK_LootLockerPersistentStorageRequestHandler_generated_h
#error "LootLockerPersistentStorageRequestHandler.generated.h already included, missing '#pragma once' in LootLockerPersistentStorageRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerPersistentStorageRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_36_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPersistentStorageItemResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPersistentStorageItemResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_28_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPersistentStorageItemsResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPersistentStorageItemsResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPersistentStorageItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPersistentStorageItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_42_DELEGATE \
struct _Script_LootLockerSDK_eventPersistentStorageItemResponseDelegateBP_Parms \
{ \
	FLootLockerPersistentStorageItemResponse Response; \
}; \
static inline void FPersistentStorageItemResponseDelegateBP_DelegateWrapper(const FScriptDelegate& PersistentStorageItemResponseDelegateBP, FLootLockerPersistentStorageItemResponse Response) \
{ \
	_Script_LootLockerSDK_eventPersistentStorageItemResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	PersistentStorageItemResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_41_DELEGATE \
struct _Script_LootLockerSDK_eventPersistentStorageItemsResponseDelegateBP_Parms \
{ \
	FLootLockerPersistentStorageItemsResponse Response; \
}; \
static inline void FPersistentStorageItemsResponseDelegateBP_DelegateWrapper(const FScriptDelegate& PersistentStorageItemsResponseDelegateBP, FLootLockerPersistentStorageItemsResponse Response) \
{ \
	_Script_LootLockerSDK_eventPersistentStorageItemsResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	PersistentStorageItemsResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerPersistentStorageRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerPersistentStorageRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerPersistentStorageRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerPersistentStorageRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerPersistentStorageRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerPersistentStorageRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerPersistentStorageRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerPersistentStorageRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerPersistentStorageRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerPersistentStorageRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerPersistentStorageRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerPersistentStorageRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerPersistentStorageRequestHandler(ULootLockerPersistentStorageRequestHandler&&); \
	NO_API ULootLockerPersistentStorageRequestHandler(const ULootLockerPersistentStorageRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerPersistentStorageRequestHandler(ULootLockerPersistentStorageRequestHandler&&); \
	NO_API ULootLockerPersistentStorageRequestHandler(const ULootLockerPersistentStorageRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerPersistentStorageRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerPersistentStorageRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerPersistentStorageRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_49_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h_53_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerPersistentStorageRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerPersistentStorageRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
