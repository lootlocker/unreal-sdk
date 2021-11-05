// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLootLockerSubmitScoreResponse;
struct FLootLockerGetScoreListResponse;
struct FLootLockerGetByListOfMembersResponse;
struct FLootLockerGetMemberRankResponse;
#ifdef LOOTLOCKERSDK_LootLockerLeaderboardRequestHandler_generated_h
#error "LootLockerLeaderboardRequestHandler.generated.h already included, missing '#pragma once' in LootLockerLeaderboardRequestHandler.h"
#endif
#define LOOTLOCKERSDK_LootLockerLeaderboardRequestHandler_generated_h

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_129_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetByListMembersRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetByListMembersRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_117_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetScoreListRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetScoreListRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_107_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetMemberRankRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetMemberRankRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_97_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerSubmitScoreRequest_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerSubmitScoreRequest>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_85_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerSubmitScoreResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerSubmitScoreResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_74_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetScoreListResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetScoreListResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_66_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetByListOfMembersResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetByListOfMembersResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_56_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPagination_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPagination>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_42_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerMember_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerMember>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_28_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerGetMemberRankResponse_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct(); \
	typedef FLootLockerResponse Super;


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerGetMemberRankResponse>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_16_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLootLockerPlayer_Statics; \
	LOOTLOCKERSDK_API static class UScriptStruct* StaticStruct();


template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<struct FLootLockerPlayer>();

#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_137_DELEGATE \
struct _Script_LootLockerSDK_eventLootLockerSubmitScoreResponseBP_Parms \
{ \
	FLootLockerSubmitScoreResponse Response; \
}; \
static inline void FLootLockerSubmitScoreResponseBP_DelegateWrapper(const FScriptDelegate& LootLockerSubmitScoreResponseBP, FLootLockerSubmitScoreResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootLockerSubmitScoreResponseBP_Parms Parms; \
	Parms.Response=Response; \
	LootLockerSubmitScoreResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_136_DELEGATE \
struct _Script_LootLockerSDK_eventLootLockerGetScoreListResponseBP_Parms \
{ \
	FLootLockerGetScoreListResponse Response; \
}; \
static inline void FLootLockerGetScoreListResponseBP_DelegateWrapper(const FScriptDelegate& LootLockerGetScoreListResponseBP, FLootLockerGetScoreListResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootLockerGetScoreListResponseBP_Parms Parms; \
	Parms.Response=Response; \
	LootLockerGetScoreListResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_135_DELEGATE \
struct _Script_LootLockerSDK_eventLootLockerGetByListOfMembersResponseBP_Parms \
{ \
	FLootLockerGetByListOfMembersResponse Response; \
}; \
static inline void FLootLockerGetByListOfMembersResponseBP_DelegateWrapper(const FScriptDelegate& LootLockerGetByListOfMembersResponseBP, FLootLockerGetByListOfMembersResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootLockerGetByListOfMembersResponseBP_Parms Parms; \
	Parms.Response=Response; \
	LootLockerGetByListOfMembersResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_134_DELEGATE \
struct _Script_LootLockerSDK_eventLootLockerGetMemberRankResponseBP_Parms \
{ \
	FLootLockerGetMemberRankResponse Response; \
}; \
static inline void FLootLockerGetMemberRankResponseBP_DelegateWrapper(const FScriptDelegate& LootLockerGetMemberRankResponseBP, FLootLockerGetMemberRankResponse Response) \
{ \
	_Script_LootLockerSDK_eventLootLockerGetMemberRankResponseBP_Parms Parms; \
	Parms.Response=Response; \
	LootLockerGetMemberRankResponseBP.ProcessDelegate<UObject>(&Parms); \
}


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_SPARSE_DATA
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_RPC_WRAPPERS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_RPC_WRAPPERS_NO_PURE_DECLS
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULootLockerLeaderboardRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerLeaderboardRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerLeaderboardRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerLeaderboardRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_INCLASS \
private: \
	static void StaticRegisterNativesULootLockerLeaderboardRequestHandler(); \
	friend struct Z_Construct_UClass_ULootLockerLeaderboardRequestHandler_Statics; \
public: \
	DECLARE_CLASS(ULootLockerLeaderboardRequestHandler, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LootLockerSDK"), NO_API) \
	DECLARE_SERIALIZER(ULootLockerLeaderboardRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULootLockerLeaderboardRequestHandler(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULootLockerLeaderboardRequestHandler) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerLeaderboardRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerLeaderboardRequestHandler); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerLeaderboardRequestHandler(ULootLockerLeaderboardRequestHandler&&); \
	NO_API ULootLockerLeaderboardRequestHandler(const ULootLockerLeaderboardRequestHandler&); \
public:


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULootLockerLeaderboardRequestHandler(ULootLockerLeaderboardRequestHandler&&); \
	NO_API ULootLockerLeaderboardRequestHandler(const ULootLockerLeaderboardRequestHandler&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULootLockerLeaderboardRequestHandler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULootLockerLeaderboardRequestHandler); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULootLockerLeaderboardRequestHandler)


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_PRIVATE_PROPERTY_OFFSET
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_144_PROLOG
#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_RPC_WRAPPERS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_INCLASS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_PRIVATE_PROPERTY_OFFSET \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_SPARSE_DATA \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_RPC_WRAPPERS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_INCLASS_NO_PURE_DECLS \
	DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h_147_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOOTLOCKERSDK_API UClass* StaticClass<class ULootLockerLeaderboardRequestHandler>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID DemoProject_Plugins_LootLockerSDK_Source_LootLockerSDK_Public_GameAPI_LootLockerLeaderboardRequestHandler_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
