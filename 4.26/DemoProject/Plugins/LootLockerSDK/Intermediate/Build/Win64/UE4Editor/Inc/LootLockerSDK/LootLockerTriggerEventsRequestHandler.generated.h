// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerTriggersResponse;
struct FLootLockerTriggerEventResponse;
#ifdef LOOTLOCKERSDK_LootLockerTriggerEventsRequestHandler_generated_h
#error "LootLockerTriggerEventsRequestHandler.generated.h already included, missing '#pragma once' in LootLockerTriggerEventsRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerTriggerEventsRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_29_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerTriggersResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerTriggersResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerTriggerEventResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerSubmitXpResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerTriggerEventResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_16_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerTriggerEvent_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerTriggerEvent>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_35_DELEGATE \
struct _Script_LootLockerSDK_eventTriggersResponseDelegateBP_Parms \
{ \
	FLootLockerTriggersResponse Value; \
}; \
static inline void FTriggersResponseDelegateBP_DelegateWrapper(const FScriptDelegate& TriggersResponseDelegateBP, FLootLockerTriggersResponse Value) \
{ \
	_Script_LootLockerSDK_eventTriggersResponseDelegateBP_Parms Parms; \
	Parms.Value=Value; \
	TriggersResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_34_DELEGATE \
struct _Script_LootLockerSDK_eventTriggerEventResponseDelegateBP_Parms \
{ \
	FLootLockerTriggerEventResponse Value; \
}; \
static inline void FTriggerEventResponseDelegateBP_DelegateWrapper(const FScriptDelegate& TriggerEventResponseDelegateBP, FLootLockerTriggerEventResponse Value) \
{ \
	_Script_LootLockerSDK_eventTriggerEventResponseDelegateBP_Parms Parms; \
	Parms.Value=Value; \
	TriggerEventResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerTriggerEventsRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerTriggerEventsRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerTriggerEventsRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerTriggerEventsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerTriggerEventsRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerTriggerEventsRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerTriggerEventsRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerTriggerEventsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerTriggerEventsRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerTriggerEventsRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerTriggerEventsRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerTriggerEventsRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerTriggerEventsRequestHandler(ULootLockerTriggerEventsRequestHandler&&); \
	NO_API ULootLockerTriggerEventsRequestHandler(const ULootLockerTriggerEventsRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerTriggerEventsRequestHandler(ULootLockerTriggerEventsRequestHandler&&); \
	NO_API ULootLockerTriggerEventsRequestHandler(const ULootLockerTriggerEventsRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerTriggerEventsRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerTriggerEventsRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerTriggerEventsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_39_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h_42_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerTriggerEventsRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerTriggerEventsRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
