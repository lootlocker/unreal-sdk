// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef DEMOPROJECT_DemoCharacters_generated_h
#error "DemoCharacters.generated.h already included, missing '#pragma once' in DemoCharacters.h"
#endif
#define DEMOPROJECT_DemoCharacters_generated_h

#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_SPARSE_DATA
#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execUpdateCharacter); \
	DECLARE_FUNCTION(execGetEquipableContextsByCharacterId); \
	DECLARE_FUNCTION(execGetEquipableContextsToDefaultCharacter); \
	DECLARE_FUNCTION(execGetOtherPlayersCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execGetCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execUnEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execUnEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execGetCharacterLoadout);


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateCharacter); \
	DECLARE_FUNCTION(execGetEquipableContextsByCharacterId); \
	DECLARE_FUNCTION(execGetEquipableContextsToDefaultCharacter); \
	DECLARE_FUNCTION(execGetOtherPlayersCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execGetCurrentLoadoutToDefaultCharacter); \
	DECLARE_FUNCTION(execUnEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execUnEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execEquipAssetToCharacterById); \
	DECLARE_FUNCTION(execEquipAssetToDefaultCharacter); \
	DECLARE_FUNCTION(execGetCharacterLoadout);


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesADemoCharacters(); \
	friend struct Z_Construct_UClass_ADemoCharacters_Statics; \
public: \
	DECLARE_CLASS(ADemoCharacters, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoCharacters)


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_INCLASS \
private: \
	static void StaticRegisterNativesADemoCharacters(); \
	friend struct Z_Construct_UClass_ADemoCharacters_Statics; \
public: \
	DECLARE_CLASS(ADemoCharacters, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoProject"), NO_API) \
	DECLARE_SERIALIZER(ADemoCharacters)


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoCharacters(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoCharacters) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoCharacters); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoCharacters); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoCharacters(ADemoCharacters&&); \
	NO_API ADemoCharacters(const ADemoCharacters&); \
public:


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ADemoCharacters(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ADemoCharacters(ADemoCharacters&&); \
	NO_API ADemoCharacters(const ADemoCharacters&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoCharacters); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoCharacters); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ADemoCharacters)


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_11_PROLOG
#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_RPC_WRAPPERS \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_INCLASS \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_SPARSE_DATA \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_INCLASS_NO_PURE_DECLS \
	DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h_15_ENHANCED_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> DEMOPROJECT_API UClass* StaticClass<class ADemoCharacters>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Source_DemoProject_Public_Demo_DemoCharacters_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
