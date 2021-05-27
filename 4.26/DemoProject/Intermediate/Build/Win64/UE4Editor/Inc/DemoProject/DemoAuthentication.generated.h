// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DEMOPROJECT_DemoAuthentication_generated_h
#error "DemoAuthentication.generated.h already included, missing '#pragma once' in DemoAuthentication.h"
#endif
#define DEMOPROJECT_DemoAuthentication_generated_h

#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_SPARSE_DATA
#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetSteamSessionTicket); \
	DECLARE_FUNCTION(execDemoEndSession); \
	DECLARE_FUNCTION(execDemoVerifyPlayer); \
	DECLARE_FUNCTION(execDemoStartSession);


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetSteamSessionTicket); \
	DECLARE_FUNCTION(execDemoEndSession); \
	DECLARE_FUNCTION(execDemoVerifyPlayer); \
	DECLARE_FUNCTION(execDemoStartSession);


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADemoAuthentication(); \
	friend struct Z_Construct_UClass_ADemoAuthentication_Statics; \
public: \
	DECLARE_CLASS(ADemoAuthentication, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoAuthentication)


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_INCLASS \
private: \
	static void StaticRegisterNativesADemoAuthentication(); \
	friend struct Z_Construct_UClass_ADemoAuthentication_Statics; \
public: \
	DECLARE_CLASS(ADemoAuthentication, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoAuthentication)


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoAuthentication(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoAuthentication) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoAuthentication); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoAuthentication); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoAuthentication(ADemoAuthentication&&); \
	NO_API ADemoAuthentication(const ADemoAuthentication&); \
public:


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoAuthentication(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoAuthentication(ADemoAuthentication&&); \
	NO_API ADemoAuthentication(const ADemoAuthentication&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoAuthentication); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoAuthentication); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoAuthentication)


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_13_PROLOG
#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_RPC_WRAPPERS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_INCLASS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_INCLASS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h_17_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DEMOPROJECT_API UClass* StaticClass<class ADemoAuthentication>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Source_DemoProject_Public_Demo_DemoAuthentication_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
