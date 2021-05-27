// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerAuthenticationDefaultResponse;
struct FLootLockerAuthenticationResponse;
#ifdef LOOTLOCKERSDK_LootLockerAuthenticationRequestHandler_generated_h
#error "LootLockerAuthenticationRequestHandler.generated.h already included, missing '#pragma once' in LootLockerAuthenticationRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerAuthenticationRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_84_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAuthenticationDefaultResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAuthenticationDefaultResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_58_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAuthenticationResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAuthenticationResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_43_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerLevelThresholds_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerLevelThresholds>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_31_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerVerificationRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerVerificationRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAuthenticationRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAuthenticationRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_89_DELEGATE \
struct _Script_LootLockerSDK_eventAuthDefaultResponseBP_Parms \
{ \
	FLootLockerAuthenticationDefaultResponse AuthVar; \
}; \
static inline void FAuthDefaultResponseBP_DelegateWrapper(const FScriptDelegate& AuthDefaultResponseBP, FLootLockerAuthenticationDefaultResponse AuthVar) \
{ \
	_Script_LootLockerSDK_eventAuthDefaultResponseBP_Parms Parms; \
	Parms.AuthVar=AuthVar; \
	AuthDefaultResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_88_DELEGATE \
struct _Script_LootLockerSDK_eventAuthResponseBP_Parms \
{ \
	FLootLockerAuthenticationResponse Var; \
}; \
static inline void FAuthResponseBP_DelegateWrapper(const FScriptDelegate& AuthResponseBP, FLootLockerAuthenticationResponse Var) \
{ \
	_Script_LootLockerSDK_eventAuthResponseBP_Parms Parms; \
	Parms.Var=Var; \
	AuthResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerAuthenticationRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerAuthenticationRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerAuthenticationRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerAuthenticationRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerAuthenticationRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerAuthenticationRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerAuthenticationRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerAuthenticationRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerAuthenticationRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerAuthenticationRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerAuthenticationRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerAuthenticationRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerAuthenticationRequestHandler(ULootLockerAuthenticationRequestHandler&&); \
	NO_API ULootLockerAuthenticationRequestHandler(const ULootLockerAuthenticationRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerAuthenticationRequestHandler(ULootLockerAuthenticationRequestHandler&&); \
	NO_API ULootLockerAuthenticationRequestHandler(const ULootLockerAuthenticationRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerAuthenticationRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerAuthenticationRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerAuthenticationRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_93_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h_96_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerAuthenticationRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerAuthenticationRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
