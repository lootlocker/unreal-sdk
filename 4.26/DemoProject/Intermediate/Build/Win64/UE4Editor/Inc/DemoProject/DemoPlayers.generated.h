// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DEMOPROJECT_DemoPlayers_generated_h
#error "DemoPlayers.generated.h already included, missing '#pragma once' in DemoPlayers.h"
#endif
#define DEMOPROJECT_DemoPlayers_generated_h

#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_SPARSE_DATA
#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetProfilePublic); \
	DECLARE_FUNCTION(execSetProfilePrivate); \
	DECLARE_FUNCTION(execGetDLCsMigration); \
	DECLARE_FUNCTION(execInitiateDLCMigration); \
	DECLARE_FUNCTION(execGetCurrencyBalance); \
	DECLARE_FUNCTION(execDemoCheckPlayerAssetDeactivationNotification); \
	DECLARE_FUNCTION(execDemoCheckPlayerAssetNotification); \
	DECLARE_FUNCTION(execDemoGetOtherPlayerInfo); \
	DECLARE_FUNCTION(execDemoSubmitXp); \
	DECLARE_FUNCTION(execDemoGetInventory); \
	DECLARE_FUNCTION(execDemoGetPlayerInfo);


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetProfilePublic); \
	DECLARE_FUNCTION(execSetProfilePrivate); \
	DECLARE_FUNCTION(execGetDLCsMigration); \
	DECLARE_FUNCTION(execInitiateDLCMigration); \
	DECLARE_FUNCTION(execGetCurrencyBalance); \
	DECLARE_FUNCTION(execDemoCheckPlayerAssetDeactivationNotification); \
	DECLARE_FUNCTION(execDemoCheckPlayerAssetNotification); \
	DECLARE_FUNCTION(execDemoGetOtherPlayerInfo); \
	DECLARE_FUNCTION(execDemoSubmitXp); \
	DECLARE_FUNCTION(execDemoGetInventory); \
	DECLARE_FUNCTION(execDemoGetPlayerInfo);


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADemoPlayers(); \
	friend struct Z_Construct_UClass_ADemoPlayers_Statics; \
public: \
	DECLARE_CLASS(ADemoPlayers, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoPlayers)


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_INCLASS \
private: \
	static void StaticRegisterNativesADemoPlayers(); \
	friend struct Z_Construct_UClass_ADemoPlayers_Statics; \
public: \
	DECLARE_CLASS(ADemoPlayers, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoPlayers)


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoPlayers(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoPlayers) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoPlayers); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoPlayers); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoPlayers(ADemoPlayers&&); \
	NO_API ADemoPlayers(const ADemoPlayers&); \
public:


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoPlayers(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoPlayers(ADemoPlayers&&); \
	NO_API ADemoPlayers(const ADemoPlayers&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoPlayers); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoPlayers); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoPlayers)


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_11_PROLOG
#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_RPC_WRAPPERS \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_INCLASS \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_INCLASS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h_15_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DEMOPROJECT_API UClass* StaticClass<class ADemoPlayers>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Source_DemoProject_Public_Demo_DemoPlayers_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
