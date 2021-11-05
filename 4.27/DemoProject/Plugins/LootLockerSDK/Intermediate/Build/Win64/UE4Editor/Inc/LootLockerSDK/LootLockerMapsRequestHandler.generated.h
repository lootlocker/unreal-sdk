// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerGetMapsResponse;
#ifdef LOOTLOCKERSDK_LootLockerMapsRequestHandler_generated_h
#error "LootLockerMapsRequestHandler.generated.h already included, missing '#pragma once' in LootLockerMapsRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerMapsRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_52_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetMapsResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMap_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMap>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMapSpawnPoint>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMapCamera>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_57_DELEGATE \
struct _Script_LootLockerSDK_eventGetMapsResponseDelegateBP_Parms \
{ \
	FLootLockerGetMapsResponse Response; \
}; \
static inline void FGetMapsResponseDelegateBP_DelegateWrapper(const FScriptDelegate& GetMapsResponseDelegateBP, FLootLockerGetMapsResponse Response) \
{ \
	_Script_LootLockerSDK_eventGetMapsResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	GetMapsResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerMapsRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerMapsRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerMapsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerMapsRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerMapsRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerMapsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerMapsRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerMapsRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerMapsRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerMapsRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerMapsRequestHandler(ULootLockerMapsRequestHandler&&); \
	NO_API ULootLockerMapsRequestHandler(const ULootLockerMapsRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerMapsRequestHandler(ULootLockerMapsRequestHandler&&); \
	NO_API ULootLockerMapsRequestHandler(const ULootLockerMapsRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerMapsRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerMapsRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerMapsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_60_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h_63_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerMapsRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMapsRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
