// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerFinishMissionResponse;
struct FLootLockerStartMissionResponse;
struct FLootLockerMissionResponse;
struct FLootLockerMissionsResponse;
#ifdef LOOTLOCKERSDK_LootLockerMissionsRequestHandler_generated_h
#error "LootLockerMissionsRequestHandler.generated.h already included, missing '#pragma once' in LootLockerMissionsRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerMissionsRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_135_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerFinishMissionResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_127_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerStartMissionResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_119_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMissionResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_111_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMissionsResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_101_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerFinishMissionData>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_89_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerFinishMissionPayload>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_79_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerCheckpointTime>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_49_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMission_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMission>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_37_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMissionCheckpoint>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_25_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMissionGoal>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_15_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMissionGoalAsset>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_145_DELEGATE \
struct _Script_LootLockerSDK_eventFinishMissionResponseDelegateBP_Parms \
{ \
	FLootLockerFinishMissionResponse Response; \
}; \
static inline void FFinishMissionResponseDelegateBP_DelegateWrapper(const FScriptDelegate& FinishMissionResponseDelegateBP, FLootLockerFinishMissionResponse Response) \
{ \
	_Script_LootLockerSDK_eventFinishMissionResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	FinishMissionResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_144_DELEGATE \
struct _Script_LootLockerSDK_eventStartMissionResponseDelegateBP_Parms \
{ \
	FLootLockerStartMissionResponse Response; \
}; \
static inline void FStartMissionResponseDelegateBP_DelegateWrapper(const FScriptDelegate& StartMissionResponseDelegateBP, FLootLockerStartMissionResponse Response) \
{ \
	_Script_LootLockerSDK_eventStartMissionResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	StartMissionResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_143_DELEGATE \
struct _Script_LootLockerSDK_eventMissionResponseDelegateBP_Parms \
{ \
	FLootLockerMissionResponse Response; \
}; \
static inline void FMissionResponseDelegateBP_DelegateWrapper(const FScriptDelegate& MissionResponseDelegateBP, FLootLockerMissionResponse Response) \
{ \
	_Script_LootLockerSDK_eventMissionResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	MissionResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_142_DELEGATE \
struct _Script_LootLockerSDK_eventMissionsResponseDelegateBP_Parms \
{ \
	FLootLockerMissionsResponse Response; \
}; \
static inline void FMissionsResponseDelegateBP_DelegateWrapper(const FScriptDelegate& MissionsResponseDelegateBP, FLootLockerMissionsResponse Response) \
{ \
	_Script_LootLockerSDK_eventMissionsResponseDelegateBP_Parms Parms; \
	Parms.Response=Response; \
	MissionsResponseDelegateBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerMissionsRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerMissionsRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerMissionsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerMissionsRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerMissionsRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerMissionsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerMissionsRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerMissionsRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerMissionsRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerMissionsRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerMissionsRequestHandler(ULootLockerMissionsRequestHandler&&); \
	NO_API ULootLockerMissionsRequestHandler(const ULootLockerMissionsRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerMissionsRequestHandler(ULootLockerMissionsRequestHandler&&); \
	NO_API ULootLockerMissionsRequestHandler(const ULootLockerMissionsRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerMissionsRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerMissionsRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerMissionsRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_151_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h_154_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerMissionsRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerMissionsRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
