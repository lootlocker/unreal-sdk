// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerCollectablesResponse;
#ifdef LOOTLOCKERSDK_LootLockerCollectablesRequestHandler_generated_h
#error "LootLockerCollectablesRequestHandler.generated.h already included, missing '#pragma once' in LootLockerCollectablesRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerCollectablesRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_78_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCollectablesResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_71_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCollectItemPayload>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_56_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCollectable_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCollectable>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_41_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCollectableItemGroup>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_26_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCollectableItem>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCollectableReward>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_83_DELEGATE \
struct _Script_LootLockerSDK_eventCollectablesResponseDelegateBP_Parms \
{ \
	FLootLockerCollectablesResponse Response; \
}; \
static inline void FCollectablesResponseDelegateBP_DelegateWrapper(const FScriptDelegate& CollectablesResponseDelegateBP, FLootLockerCollectablesResponse Response) \
{ \
	_Script_LootLockerSDK_eventCollectablesResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	CollectablesResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerCollectablesRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerCollectablesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerCollectablesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerCollectablesRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerCollectablesRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerCollectablesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerCollectablesRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerCollectablesRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerCollectablesRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerCollectablesRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerCollectablesRequestHandler(ULootLockerCollectablesRequestHandler&&); \
	NO_API ULootLockerCollectablesRequestHandler(const ULootLockerCollectablesRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerCollectablesRequestHandler(ULootLockerCollectablesRequestHandler&&); \
	NO_API ULootLockerCollectablesRequestHandler(const ULootLockerCollectablesRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerCollectablesRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerCollectablesRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerCollectablesRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_86_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h_89_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerCollectablesRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerCollectablesRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
