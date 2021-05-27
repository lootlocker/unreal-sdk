// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DEMOPROJECT_DemoAssets_generated_h
#error "DemoAssets.generated.h already included, missing '#pragma once' in DemoAssets.h"
#endif
#define DEMOPROJECT_DemoAssets_generated_h

#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_SPARSE_DATA
#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execDemoRemoveAssetFromFavourites); \
	DECLARE_FUNCTION(execDemoAddAssetToFavourites); \
	DECLARE_FUNCTION(execDemoGetFavouriteAssetIndices); \
	DECLARE_FUNCTION(execDemoGetAssetBones); \
	DECLARE_FUNCTION(execDemoGetAssetsByIds); \
	DECLARE_FUNCTION(execDemoGetAssets); \
	DECLARE_FUNCTION(execDemoGetContexts);


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execDemoRemoveAssetFromFavourites); \
	DECLARE_FUNCTION(execDemoAddAssetToFavourites); \
	DECLARE_FUNCTION(execDemoGetFavouriteAssetIndices); \
	DECLARE_FUNCTION(execDemoGetAssetBones); \
	DECLARE_FUNCTION(execDemoGetAssetsByIds); \
	DECLARE_FUNCTION(execDemoGetAssets); \
	DECLARE_FUNCTION(execDemoGetContexts);


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADemoAssets(); \
	friend struct Z_Construct_UClass_ADemoAssets_Statics; \
public: \
	DECLARE_CLASS(ADemoAssets, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoAssets)


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_INCLASS \
private: \
	static void StaticRegisterNativesADemoAssets(); \
	friend struct Z_Construct_UClass_ADemoAssets_Statics; \
public: \
	DECLARE_CLASS(ADemoAssets, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoAssets)


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoAssets(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoAssets) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoAssets); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoAssets); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoAssets(ADemoAssets&&); \
	NO_API ADemoAssets(const ADemoAssets&); \
public:


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoAssets(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoAssets(ADemoAssets&&); \
	NO_API ADemoAssets(const ADemoAssets&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoAssets); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoAssets); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoAssets)


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_11_PROLOG
#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_RPC_WRAPPERS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_INCLASS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_INCLASS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h_15_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DEMOPROJECT_API UClass* StaticClass<class ADemoAssets>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Source_DemoProject_Public_Demo_DemoAssets_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
