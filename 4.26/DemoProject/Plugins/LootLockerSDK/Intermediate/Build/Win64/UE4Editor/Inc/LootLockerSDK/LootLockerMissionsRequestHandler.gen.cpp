// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/GameAPI/LootLockerMissionsRequestHandler.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerMissionsRequestHandler() {}
// Cross Module References
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse();
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerStartMissionResponse();
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionResponse();
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionsResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMission();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionData();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCheckpointTime();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionGoal();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerAsset();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerMissionsRequestHandler_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerMissionsRequestHandler();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventFinishMissionResponseDelegateBP_Parms
		{
			FLootLockerFinishMissionResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventFinishMissionResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "FinishMissionResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventFinishMissionResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_FinishMissionResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventStartMissionResponseDelegateBP_Parms
		{
			FLootLockerStartMissionResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventStartMissionResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerStartMissionResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "StartMissionResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventStartMissionResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_StartMissionResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventMissionResponseDelegateBP_Parms
		{
			FLootLockerMissionResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventMissionResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerMissionResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "MissionResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventMissionResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_MissionResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventMissionsResponseDelegateBP_Parms
		{
			FLootLockerMissionsResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventMissionsResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerMissionsResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "MissionsResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventMissionsResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_MissionsResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}

static_assert(std::is_polymorphic<FLootLockerFinishMissionResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerFinishMissionResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerFinishMissionResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerFinishMissionResponse"), sizeof(FLootLockerFinishMissionResponse), Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerFinishMissionResponse>()
{
	return FLootLockerFinishMissionResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerFinishMissionResponse(FLootLockerFinishMissionResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerFinishMissionResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerFinishMissionResponse")),new UScriptStruct::TCppStructOps<FLootLockerFinishMissionResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionResponse;
	struct Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_score_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_score;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_check_grant_notifications_MetaData[];
#endif
		static void NewProp_check_grant_notifications_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_check_grant_notifications;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerFinishMissionResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_score_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_score = { "score", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerFinishMissionResponse, score), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_score_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_score_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications_SetBit(void* Obj)
	{
		((FLootLockerFinishMissionResponse*)Obj)->check_grant_notifications = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications = { "check_grant_notifications", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerFinishMissionResponse), &Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_score,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::NewProp_check_grant_notifications,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerFinishMissionResponse",
		sizeof(FLootLockerFinishMissionResponse),
		alignof(FLootLockerFinishMissionResponse),
		Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerFinishMissionResponse"), sizeof(FLootLockerFinishMissionResponse), Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionResponse_Hash() { return 1979989136U; }

static_assert(std::is_polymorphic<FLootLockerStartMissionResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerStartMissionResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerStartMissionResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerStartMissionResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerStartMissionResponse"), sizeof(FLootLockerStartMissionResponse), Get_Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerStartMissionResponse>()
{
	return FLootLockerStartMissionResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerStartMissionResponse(FLootLockerStartMissionResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerStartMissionResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerStartMissionResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerStartMissionResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerStartMissionResponse")),new UScriptStruct::TCppStructOps<FLootLockerStartMissionResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerStartMissionResponse;
	struct Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_signature_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_signature;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerStartMissionResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::NewProp_signature_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::NewProp_signature = { "signature", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerStartMissionResponse, signature), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::NewProp_signature_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::NewProp_signature_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::NewProp_signature,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerStartMissionResponse",
		sizeof(FLootLockerStartMissionResponse),
		alignof(FLootLockerStartMissionResponse),
		Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerStartMissionResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerStartMissionResponse"), sizeof(FLootLockerStartMissionResponse), Get_Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerStartMissionResponse_Hash() { return 281670687U; }

static_assert(std::is_polymorphic<FLootLockerMissionResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerMissionResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerMissionResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMissionResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMissionResponse"), sizeof(FLootLockerMissionResponse), Get_Z_Construct_UScriptStruct_FLootLockerMissionResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMissionResponse>()
{
	return FLootLockerMissionResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMissionResponse(FLootLockerMissionResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMissionResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMissionResponse")),new UScriptStruct::TCppStructOps<FLootLockerMissionResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionResponse;
	struct Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_mission_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_mission;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMissionResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::NewProp_mission_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::NewProp_mission = { "mission", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionResponse, mission), Z_Construct_UScriptStruct_FLootLockerMission, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::NewProp_mission_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::NewProp_mission_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::NewProp_mission,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerMissionResponse",
		sizeof(FLootLockerMissionResponse),
		alignof(FLootLockerMissionResponse),
		Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMissionResponse"), sizeof(FLootLockerMissionResponse), Get_Z_Construct_UScriptStruct_FLootLockerMissionResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMissionResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionResponse_Hash() { return 3477364721U; }

static_assert(std::is_polymorphic<FLootLockerMissionsResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerMissionsResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerMissionsResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMissionsResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMissionsResponse"), sizeof(FLootLockerMissionsResponse), Get_Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMissionsResponse>()
{
	return FLootLockerMissionsResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMissionsResponse(FLootLockerMissionsResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMissionsResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionsResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionsResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMissionsResponse")),new UScriptStruct::TCppStructOps<FLootLockerMissionsResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionsResponse;
	struct Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_missions_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_missions_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_missions;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMissionsResponse>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions_Inner = { "missions", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMission, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions = { "missions", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionsResponse, missions), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::NewProp_missions,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerMissionsResponse",
		sizeof(FLootLockerMissionsResponse),
		alignof(FLootLockerMissionsResponse),
		Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionsResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMissionsResponse"), sizeof(FLootLockerMissionsResponse), Get_Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionsResponse_Hash() { return 864499322U; }
class UScriptStruct* FLootLockerFinishMissionData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerFinishMissionData, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerFinishMissionData"), sizeof(FLootLockerFinishMissionData), Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerFinishMissionData>()
{
	return FLootLockerFinishMissionData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerFinishMissionData(FLootLockerFinishMissionData::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerFinishMissionData"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionData
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionData()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerFinishMissionData")),new UScriptStruct::TCppStructOps<FLootLockerFinishMissionData>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionData;
	struct Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_signature_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_signature;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_payload_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_payload;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerFinishMissionData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_signature_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_signature = { "signature", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerFinishMissionData, signature), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_signature_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_signature_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_payload_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_payload = { "payload", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerFinishMissionData, payload), Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_payload_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_payload_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_signature,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::NewProp_payload,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerFinishMissionData",
		sizeof(FLootLockerFinishMissionData),
		alignof(FLootLockerFinishMissionData),
		Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerFinishMissionData"), sizeof(FLootLockerFinishMissionData), Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionData_Hash() { return 1398769799U; }
class UScriptStruct* FLootLockerFinishMissionPayload::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerFinishMissionPayload"), sizeof(FLootLockerFinishMissionPayload), Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerFinishMissionPayload>()
{
	return FLootLockerFinishMissionPayload::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerFinishMissionPayload(FLootLockerFinishMissionPayload::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerFinishMissionPayload"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionPayload
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionPayload()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerFinishMissionPayload")),new UScriptStruct::TCppStructOps<FLootLockerFinishMissionPayload>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerFinishMissionPayload;
	struct Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_finish_time_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_finish_time;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_finish_score_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_finish_score;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_checkpoint_times_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_checkpoint_times_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_checkpoint_times;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerFinishMissionPayload>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_time_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_time = { "finish_time", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerFinishMissionPayload, finish_time), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_time_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_time_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_score_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_score = { "finish_score", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerFinishMissionPayload, finish_score), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_score_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_score_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times_Inner = { "checkpoint_times", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCheckpointTime, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times = { "checkpoint_times", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerFinishMissionPayload, checkpoint_times), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_finish_score,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::NewProp_checkpoint_times,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerFinishMissionPayload",
		sizeof(FLootLockerFinishMissionPayload),
		alignof(FLootLockerFinishMissionPayload),
		Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerFinishMissionPayload"), sizeof(FLootLockerFinishMissionPayload), Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerFinishMissionPayload_Hash() { return 2791945408U; }
class UScriptStruct* FLootLockerCheckpointTime::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCheckpointTime, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCheckpointTime"), sizeof(FLootLockerCheckpointTime), Get_Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCheckpointTime>()
{
	return FLootLockerCheckpointTime::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCheckpointTime(FLootLockerCheckpointTime::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCheckpointTime"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCheckpointTime
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCheckpointTime()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCheckpointTime")),new UScriptStruct::TCppStructOps<FLootLockerCheckpointTime>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCheckpointTime;
	struct Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_index_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_time_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_time;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCheckpointTime>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_index_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_index = { "index", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCheckpointTime, index), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_index_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_time_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_time = { "time", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCheckpointTime, time), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_time_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_time_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::NewProp_time,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerCheckpointTime",
		sizeof(FLootLockerCheckpointTime),
		alignof(FLootLockerCheckpointTime),
		Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCheckpointTime()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCheckpointTime"), sizeof(FLootLockerCheckpointTime), Get_Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCheckpointTime_Hash() { return 2533721553U; }
class UScriptStruct* FLootLockerMission::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMission_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMission, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMission"), sizeof(FLootLockerMission), Get_Z_Construct_UScriptStruct_FLootLockerMission_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMission>()
{
	return FLootLockerMission::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMission(FLootLockerMission::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMission"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMission
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMission()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMission")),new UScriptStruct::TCppStructOps<FLootLockerMission>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMission;
	struct Z_Construct_UScriptStruct_FLootLockerMission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_mission_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_mission_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_asset_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_asset_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rounds_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_rounds;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_round_length_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_round_length;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_difficulty_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_difficulty_name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_difficulty_multiplier_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_difficulty_multiplier;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_difficulty_color_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_difficulty_color;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_difficulty_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_difficulty_id;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_goals_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_goals_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_goals;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_checkpoints_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_checkpoints_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_checkpoints;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_player_access_MetaData[];
#endif
		static void NewProp_player_access_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_player_access;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_best_goal_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_best_goal;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMission>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_mission_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_mission_id = { "mission_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, mission_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_mission_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_mission_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_asset_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_asset_id = { "asset_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, asset_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_asset_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_asset_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_rounds_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_rounds = { "rounds", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, rounds), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_rounds_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_rounds_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_round_length_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_round_length = { "round_length", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, round_length), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_round_length_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_round_length_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_name_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_name = { "difficulty_name", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, difficulty_name), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_multiplier_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_multiplier = { "difficulty_multiplier", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, difficulty_multiplier), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_multiplier_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_multiplier_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_color_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_color = { "difficulty_color", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, difficulty_color), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_color_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_color_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_id = { "difficulty_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, difficulty_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_id_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals_Inner = { "goals", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMissionGoal, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals = { "goals", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, goals), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints_Inner = { "checkpoints", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints = { "checkpoints", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, checkpoints), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access_SetBit(void* Obj)
	{
		((FLootLockerMission*)Obj)->player_access = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access = { "player_access", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerMission), &Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_best_goal_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_best_goal = { "best_goal", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMission, best_goal), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_best_goal_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_best_goal_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMission_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_mission_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_asset_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_rounds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_round_length,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_multiplier,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_color,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_difficulty_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_goals,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_checkpoints,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_player_access,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMission_Statics::NewProp_best_goal,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMission_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMission",
		sizeof(FLootLockerMission),
		alignof(FLootLockerMission),
		Z_Construct_UScriptStruct_FLootLockerMission_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMission_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMission_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMission()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMission_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMission"), sizeof(FLootLockerMission), Get_Z_Construct_UScriptStruct_FLootLockerMission_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMission_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMission_Hash() { return 1424320070U; }
class UScriptStruct* FLootLockerMissionCheckpoint::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMissionCheckpoint"), sizeof(FLootLockerMissionCheckpoint), Get_Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMissionCheckpoint>()
{
	return FLootLockerMissionCheckpoint::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMissionCheckpoint(FLootLockerMissionCheckpoint::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMissionCheckpoint"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionCheckpoint
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionCheckpoint()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMissionCheckpoint")),new UScriptStruct::TCppStructOps<FLootLockerMissionCheckpoint>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionCheckpoint;
	struct Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_index_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_time_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_time;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_parameters_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_parameters_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_parameters_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_parameters;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMissionCheckpoint>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_index_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_index = { "index", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionCheckpoint, index), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_index_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_time_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_time = { "time", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionCheckpoint, time), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_time_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_time_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_ValueProp = { "parameters", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_Key_KeyProp = { "parameters_Key", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters = { "parameters", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionCheckpoint, parameters), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::NewProp_parameters,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMissionCheckpoint",
		sizeof(FLootLockerMissionCheckpoint),
		alignof(FLootLockerMissionCheckpoint),
		Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMissionCheckpoint"), sizeof(FLootLockerMissionCheckpoint), Get_Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionCheckpoint_Hash() { return 3837691281U; }
class UScriptStruct* FLootLockerMissionGoal::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionGoal_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMissionGoal, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMissionGoal"), sizeof(FLootLockerMissionGoal), Get_Z_Construct_UScriptStruct_FLootLockerMissionGoal_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMissionGoal>()
{
	return FLootLockerMissionGoal::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMissionGoal(FLootLockerMissionGoal::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMissionGoal"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionGoal
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionGoal()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMissionGoal")),new UScriptStruct::TCppStructOps<FLootLockerMissionGoal>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionGoal;
	struct Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_goal_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_goal;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_points_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_points;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_assets_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_assets_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_assets;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMissionGoal>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_goal_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_goal = { "goal", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionGoal, goal), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_goal_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_goal_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_points_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_points = { "points", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionGoal, points), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_points_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_points_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets_Inner = { "assets", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets = { "assets", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionGoal, assets), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_goal,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_points,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::NewProp_assets,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMissionGoal",
		sizeof(FLootLockerMissionGoal),
		alignof(FLootLockerMissionGoal),
		Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionGoal()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionGoal_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMissionGoal"), sizeof(FLootLockerMissionGoal), Get_Z_Construct_UScriptStruct_FLootLockerMissionGoal_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMissionGoal_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionGoal_Hash() { return 2156269170U; }
class UScriptStruct* FLootLockerMissionGoalAsset::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMissionGoalAsset"), sizeof(FLootLockerMissionGoalAsset), Get_Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMissionGoalAsset>()
{
	return FLootLockerMissionGoalAsset::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMissionGoalAsset(FLootLockerMissionGoalAsset::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMissionGoalAsset"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionGoalAsset
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionGoalAsset()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMissionGoalAsset")),new UScriptStruct::TCppStructOps<FLootLockerMissionGoalAsset>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMissionGoalAsset;
	struct Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_variation_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_variation_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_assets_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_assets;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMissionGoalAsset>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_variation_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_variation_id = { "variation_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionGoalAsset, variation_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_variation_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_variation_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_assets_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_assets = { "assets", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMissionGoalAsset, assets), Z_Construct_UScriptStruct_FLootLockerAsset, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_assets_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_assets_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_variation_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::NewProp_assets,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMissionGoalAsset",
		sizeof(FLootLockerMissionGoalAsset),
		alignof(FLootLockerMissionGoalAsset),
		Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMissionGoalAsset"), sizeof(FLootLockerMissionGoalAsset), Get_Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMissionGoalAsset_Hash() { return 564886671U; }
	void ULootLockerMissionsRequestHandler::StaticRegisterNativesULootLockerMissionsRequestHandler()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerMissionsRequestHandler_NoRegister()
	{
		return ULootLockerMissionsRequestHandler::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameAPI/LootLockerMissionsRequestHandler.h" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMissionsRequestHandler.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerMissionsRequestHandler>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::ClassParams = {
		&ULootLockerMissionsRequestHandler::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerMissionsRequestHandler()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerMissionsRequestHandler_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerMissionsRequestHandler, 2956741086);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerMissionsRequestHandler>()
	{
		return ULootLockerMissionsRequestHandler::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerMissionsRequestHandler(Z_Construct_UClass_ULootLockerMissionsRequestHandler, &ULootLockerMissionsRequestHandler::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerMissionsRequestHandler"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerMissionsRequestHandler);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
