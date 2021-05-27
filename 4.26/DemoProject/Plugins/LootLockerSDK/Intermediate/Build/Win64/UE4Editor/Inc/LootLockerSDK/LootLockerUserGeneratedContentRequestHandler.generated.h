// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerAssetCandidatesResponse;
struct FLootLockerAssetCandidateResponse;
struct FLootLockerCreateAssetCandidateResponse;
#ifdef LOOTLOCKERSDK_LootLockerUserGeneratedContentRequestHandler_generated_h
#error "LootLockerUserGeneratedContentRequestHandler.generated.h already included, missing '#pragma once' in LootLockerUserGeneratedContentRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerUserGeneratedContentRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_87_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetCandidatesResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetCandidatesResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_79_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetCandidateResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetCandidateResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_69_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCreateAssetCandidateResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCreateAssetCandidateResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_47_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerResponseAssetCandidate_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerResponseAssetCandidate>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_32_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetCandidate2_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetCandidate2>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerAssetDataEntity_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerAssetDataEntity>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerContentKeyValuePair_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerContentKeyValuePair>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_102_DELEGATE \
struct _Script_LootLockerSDK_eventAssetCandidatesResponseDelegateBP_Parms \
{ \
	FLootLockerAssetCandidatesResponse Response; \
}; \
static inline void FAssetCandidatesResponseDelegateBP_DelegateWrapper(const FScriptDelegate& AssetCandidatesResponseDelegateBP, FLootLockerAssetCandidatesResponse Response) \
{ \
	_Script_LootLockerSDK_eventAssetCandidatesResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	AssetCandidatesResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_101_DELEGATE \
struct _Script_LootLockerSDK_eventAssetCandidateResponseDelegateBP_Parms \
{ \
	FLootLockerAssetCandidateResponse Response; \
}; \
static inline void FAssetCandidateResponseDelegateBP_DelegateWrapper(const FScriptDelegate& AssetCandidateResponseDelegateBP, FLootLockerAssetCandidateResponse Response) \
{ \
	_Script_LootLockerSDK_eventAssetCandidateResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	AssetCandidateResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_100_DELEGATE \
struct _Script_LootLockerSDK_eventCreateAssetCandidateResponseDelegateBP_Parms \
{ \
	FLootLockerCreateAssetCandidateResponse Response; \
}; \
static inline void FCreateAssetCandidateResponseDelegateBP_DelegateWrapper(const FScriptDelegate& CreateAssetCandidateResponseDelegateBP, FLootLockerCreateAssetCandidateResponse Response) \
{ \
	_Script_LootLockerSDK_eventCreateAssetCandidateResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	CreateAssetCandidateResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerUserGeneratedContentRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerUserGeneratedContentRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerUserGeneratedContentRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerUserGeneratedContentRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerUserGeneratedContentRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerUserGeneratedContentRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerUserGeneratedContentRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerUserGeneratedContentRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerUserGeneratedContentRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerUserGeneratedContentRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerUserGeneratedContentRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerUserGeneratedContentRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerUserGeneratedContentRequestHandler(ULootLockerUserGeneratedContentRequestHandler&&); \
	NO_API ULootLockerUserGeneratedContentRequestHandler(const ULootLockerUserGeneratedContentRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerUserGeneratedContentRequestHandler(ULootLockerUserGeneratedContentRequestHandler&&); \
	NO_API ULootLockerUserGeneratedContentRequestHandler(const ULootLockerUserGeneratedContentRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerUserGeneratedContentRequestHandler); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerUserGeneratedContentRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerUserGeneratedContentRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_107_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h_110_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerUserGeneratedContentRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerUserGeneratedContentRequestHandler_h


#define FOREACH_ENUM_ELOOTLOCKERASSETFILEPURPOSE(op) \
	op(ELootLockerAssetFilePurpose::PRIMARY_THUMBNAIL) \
	op(ELootLockerAssetFilePurpose::THUMBNAIL) \
	op(ELootLockerAssetFilePurpose::FILE) 

enum class ELootLockerAssetFilePurpose : uint8;
template<> LOOTLOCKERSDK_API UEnum* StaticEnum<ELootLockerAssetFilePurpose>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
