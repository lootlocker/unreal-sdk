// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerPickDropsFromDropTableResponse;
struct FLootLockerComputeAndLockDropTableResponse;
#ifdef LOOTLOCKERSDK_LLDropTablesRequestHandler_generated_h
#error "LLDropTablesRequestHandler.generated.h already included, missing '#pragma once' in LLDropTablesRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LLDropTablesRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_52_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPickDropsFromDropTableRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPickDropsFromDropTableRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_41_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPickDropsFromDropTableItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPickDropsFromDropTableItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_33_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPickDropsFromDropTableResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPickDropsFromDropTableResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerComputeAndLockItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerComputeAndLockItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerComputeAndLockDropTableResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerComputeAndLockDropTableResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_58_DELEGATE \
struct _Script_LootLockerSDK_eventFLootLockerPickDropsFromDropTableResponseBP_Parms \
{ \
	FLootLockerPickDropsFromDropTableResponse Response; \
}; \
static inline void FFLootLockerPickDropsFromDropTableResponseBP_DelegateWrapper(const FScriptDelegate& FLootLockerPickDropsFromDropTableResponseBP, FLootLockerPickDropsFromDropTableResponse Response) \
{ \
	_Script_LootLockerSDK_eventFLootLockerPickDropsFromDropTableResponseBP_Parms Parms; \
	Parms.Response=Response; \
	FLootLockerPickDropsFromDropTableResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_56_DELEGATE \
struct _Script_LootLockerSDK_eventLootLockerComputeAndLockDropTableResponseBP_Parms \
{ \
	FLootLockerComputeAndLockDropTableResponse Response; \
}; \
static inline void FLootLockerComputeAndLockDropTableResponseBP_DelegateWrapper(const FScriptDelegate& LootLockerComputeAndLockDropTableResponseBP, FLootLockerComputeAndLockDropTableResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootLockerComputeAndLockDropTableResponseBP_Parms Parms; \
	Parms.Response=Response; \
	LootLockerComputeAndLockDropTableResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULLDropTablesRequestHandler(); \
	friend struct Z_Construct_UClass_ULLDropTablesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULLDropTablesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULLDropTablesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_INCLASS \
private: \
	static void StaticRegisterNativesULLDropTablesRequestHandler(); \
	friend struct Z_Construct_UClass_ULLDropTablesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULLDropTablesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULLDropTablesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULLDropTablesRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULLDropTablesRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULLDropTablesRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULLDropTablesRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULLDropTablesRequestHandler(ULLDropTablesRequestHandler&&); \
	NO_API ULLDropTablesRequestHandler(const ULLDropTablesRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULLDropTablesRequestHandler(ULLDropTablesRequestHandler&&); \
	NO_API ULLDropTablesRequestHandler(const ULLDropTablesRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULLDropTablesRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULLDropTablesRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULLDropTablesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_63_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h_66_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULLDropTablesRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LLDropTablesRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
