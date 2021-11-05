// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerResponse;
#ifdef LOOTLOCKERSDK_LootLockerConfig_generated_h
#error "LootLockerConfig.generated.h already included, missing '#pragma once' in LootLockerConfig.h"
#endif
#define LOOTLOCKERSDK_LootLockerConfig_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_68_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetRequests_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetRequests>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_57_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerEndPoints_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerEndPoints>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_13_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_73_DELEGATE \
struct _Script_LootLockerSDK_eventLootLockerResponseCallback_Parms \
{ \
	FLootLockerResponse Response; \
}; \
static inline void FLootLockerResponseCallback_DelegateWrapper(const FScriptDelegate& LootLockerResponseCallback, FLootLockerResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootLockerResponseCallback_Parms Parms; \
	Parms.Response=Response; \
	LootLockerResponseCallback.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_72_DELEGATE \
struct _Script_LootLockerSDK_eventResponseCallbackBP_Parms \
{ \
	FLootLockerResponse Response; \
}; \
static inline void FResponseCallbackBP_DelegateWrapper(const FScriptDelegate& ResponseCallbackBP, FLootLockerResponse Response) \
{ \
	_Script_LootLockerSDK_eventResponseCallbackBP_Parms Parms; \
	Parms.Response=Response; \
	ResponseCallbackBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerConfig(); \
	friend struct Z_Construct_UClass_ULootLockerConfig_Statics; \
public: \
	DECLARE_CLASS(ULootLockerConfig, UObject, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerConfig) \
	static const TCHAR* StaticConfigName() {return TEXT("LootLockerSDK");} \



#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerConfig(); \
	friend struct Z_Construct_UClass_ULootLockerConfig_Statics; \
public: \
	DECLARE_CLASS(ULootLockerConfig, UObject, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerConfig) \
	static const TCHAR* StaticConfigName() {return TEXT("LootLockerSDK");} \



#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerConfig) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerConfig); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerConfig); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerConfig(ULootLockerConfig&&); \
	NO_API ULootLockerConfig(const ULootLockerConfig&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerConfig(ULootLockerConfig&&); \
	NO_API ULootLockerConfig(const ULootLockerConfig&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerConfig); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerConfig); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerConfig)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_76_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h_79_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerConfig>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_LootLockerConfig_h


#define FOREACH_ENUM_ELOOTLOCKERPLATFORMTYPE(op) \
	op(ELootLockerPlatformType::Android) \
	op(ELootLockerPlatformType::Ios) \
	op(ELootLockerPlatformType::Steam) \
	op(ELootLockerPlatformType::NintendoSwitch) \
	op(ELootLockerPlatformType::EpicStore) \
	op(ELootLockerPlatformType::PlayStationNetwork) \
	op(ELootLockerPlatformType::Xbox) \
	op(ELootLockerPlatformType::GoG) 

enum class ELootLockerPlatformType : uint8;
template<> LOOTLOCKERSDK_API UEnum* StaticEnum<ELootLockerPlatformType>();

#define FOREACH_ENUM_ELOOTLOCKERHTTPMETHOD(op) \
	op(ELootLockerHTTPMethod::GET) \
	op(ELootLockerHTTPMethod::POST) \
	op(ELootLockerHTTPMethod::DEL) \
	op(ELootLockerHTTPMethod::PUT) \
	op(ELootLockerHTTPMethod::HEAD) \
	op(ELootLockerHTTPMethod::CREATE) \
	op(ELootLockerHTTPMethod::OPTIONS) \
	op(ELootLockerHTTPMethod::PATCH) \
	op(ELootLockerHTTPMethod::UPLOAD) 

enum class ELootLockerHTTPMethod : uint8;
template<> LOOTLOCKERSDK_API UEnum* StaticEnum<ELootLockerHTTPMethod>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
