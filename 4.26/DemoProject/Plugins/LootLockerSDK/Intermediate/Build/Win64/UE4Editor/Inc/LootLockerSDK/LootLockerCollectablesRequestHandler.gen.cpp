// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/GameAPI/LootLockerCollectablesRequestHandler.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerCollectablesRequestHandler() {}
// Cross Module References
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectablesResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectable();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectItemPayload();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectableReward();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectableItem();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerAsset();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerCollectablesRequestHandler_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerCollectablesRequestHandler();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventCollectablesResponseDelegateBP_Parms
		{
			FLootLockerCollectablesResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventCollectablesResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerCollectablesResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "CollectablesResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventCollectablesResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_CollectablesResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}

static_assert(std::is_polymorphic<FLootLockerCollectablesResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerCollectablesResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerCollectablesResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCollectablesResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCollectablesResponse"), sizeof(FLootLockerCollectablesResponse), Get_Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCollectablesResponse>()
{
	return FLootLockerCollectablesResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCollectablesResponse(FLootLockerCollectablesResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCollectablesResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectablesResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectablesResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCollectablesResponse")),new UScriptStruct::TCppStructOps<FLootLockerCollectablesResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectablesResponse;
	struct Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_collectables_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_collectables_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_collectables;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCollectablesResponse>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables_Inner = { "collectables", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCollectable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables = { "collectables", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectablesResponse, collectables), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::NewProp_collectables,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerCollectablesResponse",
		sizeof(FLootLockerCollectablesResponse),
		alignof(FLootLockerCollectablesResponse),
		Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectablesResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCollectablesResponse"), sizeof(FLootLockerCollectablesResponse), Get_Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectablesResponse_Hash() { return 1577081446U; }
class UScriptStruct* FLootLockerCollectItemPayload::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCollectItemPayload, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCollectItemPayload"), sizeof(FLootLockerCollectItemPayload), Get_Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCollectItemPayload>()
{
	return FLootLockerCollectItemPayload::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCollectItemPayload(FLootLockerCollectItemPayload::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCollectItemPayload"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectItemPayload
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectItemPayload()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCollectItemPayload")),new UScriptStruct::TCppStructOps<FLootLockerCollectItemPayload>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectItemPayload;
	struct Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_slug_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_slug;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCollectItemPayload>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::NewProp_slug_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::NewProp_slug = { "slug", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectItemPayload, slug), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::NewProp_slug_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::NewProp_slug_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::NewProp_slug,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerCollectItemPayload",
		sizeof(FLootLockerCollectItemPayload),
		alignof(FLootLockerCollectItemPayload),
		Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectItemPayload()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCollectItemPayload"), sizeof(FLootLockerCollectItemPayload), Get_Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectItemPayload_Hash() { return 3904149489U; }
class UScriptStruct* FLootLockerCollectable::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectable_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCollectable, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCollectable"), sizeof(FLootLockerCollectable), Get_Z_Construct_UScriptStruct_FLootLockerCollectable_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCollectable>()
{
	return FLootLockerCollectable::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCollectable(FLootLockerCollectable::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCollectable"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectable
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectable()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCollectable")),new UScriptStruct::TCppStructOps<FLootLockerCollectable>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectable;
	struct Z_Construct_UScriptStruct_FLootLockerCollectable_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_groups_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_groups_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_groups;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_completion_percentage_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_completion_percentage;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_rewards_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rewards_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_rewards;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_grants_all_rewards_MetaData[];
#endif
		static void NewProp_grants_all_rewards_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_grants_all_rewards;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCollectable>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_name_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectable, name), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_name_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups_Inner = { "groups", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups = { "groups", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectable, groups), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_completion_percentage_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_completion_percentage = { "completion_percentage", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectable, completion_percentage), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_completion_percentage_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_completion_percentage_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards_Inner = { "rewards", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCollectableReward, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards = { "rewards", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectable, rewards), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards_SetBit(void* Obj)
	{
		((FLootLockerCollectable*)Obj)->grants_all_rewards = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards = { "grants_all_rewards", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerCollectable), &Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_groups,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_completion_percentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_rewards,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::NewProp_grants_all_rewards,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerCollectable",
		sizeof(FLootLockerCollectable),
		alignof(FLootLockerCollectable),
		Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectable()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectable_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCollectable"), sizeof(FLootLockerCollectable), Get_Z_Construct_UScriptStruct_FLootLockerCollectable_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCollectable_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectable_Hash() { return 381642784U; }
class UScriptStruct* FLootLockerCollectableItemGroup::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCollectableItemGroup"), sizeof(FLootLockerCollectableItemGroup), Get_Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCollectableItemGroup>()
{
	return FLootLockerCollectableItemGroup::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCollectableItemGroup(FLootLockerCollectableItemGroup::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCollectableItemGroup"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableItemGroup
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableItemGroup()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCollectableItemGroup")),new UScriptStruct::TCppStructOps<FLootLockerCollectableItemGroup>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableItemGroup;
	struct Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_completion_percentage_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_completion_percentage;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_items_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_items_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_items;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_rewards_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rewards_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_rewards;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_grants_all_rewards_MetaData[];
#endif
		static void NewProp_grants_all_rewards_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_grants_all_rewards;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCollectableItemGroup>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_name_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableItemGroup, name), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_completion_percentage_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_completion_percentage = { "completion_percentage", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableItemGroup, completion_percentage), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_completion_percentage_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_completion_percentage_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items_Inner = { "items", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCollectableItem, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items = { "items", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableItemGroup, items), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards_Inner = { "rewards", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCollectableReward, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards = { "rewards", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableItemGroup, rewards), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards_SetBit(void* Obj)
	{
		((FLootLockerCollectableItemGroup*)Obj)->grants_all_rewards = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards = { "grants_all_rewards", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerCollectableItemGroup), &Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_completion_percentage,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_items,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_rewards,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::NewProp_grants_all_rewards,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerCollectableItemGroup",
		sizeof(FLootLockerCollectableItemGroup),
		alignof(FLootLockerCollectableItemGroup),
		Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCollectableItemGroup"), sizeof(FLootLockerCollectableItemGroup), Get_Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableItemGroup_Hash() { return 3560719850U; }
class UScriptStruct* FLootLockerCollectableItem::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableItem_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCollectableItem, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCollectableItem"), sizeof(FLootLockerCollectableItem), Get_Z_Construct_UScriptStruct_FLootLockerCollectableItem_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCollectableItem>()
{
	return FLootLockerCollectableItem::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCollectableItem(FLootLockerCollectableItem::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCollectableItem"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableItem
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableItem()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCollectableItem")),new UScriptStruct::TCppStructOps<FLootLockerCollectableItem>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableItem;
	struct Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_collected_MetaData[];
#endif
		static void NewProp_collected_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_collected;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_rewards_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rewards_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_rewards;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_grants_all_rewards_MetaData[];
#endif
		static void NewProp_grants_all_rewards_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_grants_all_rewards;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_just_collected_MetaData[];
#endif
		static void NewProp_just_collected_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_just_collected;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCollectableItem>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_name_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableItem, name), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_name_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected_SetBit(void* Obj)
	{
		((FLootLockerCollectableItem*)Obj)->collected = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected = { "collected", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerCollectableItem), &Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards_Inner = { "rewards", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerCollectableReward, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards = { "rewards", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableItem, rewards), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards_SetBit(void* Obj)
	{
		((FLootLockerCollectableItem*)Obj)->grants_all_rewards = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards = { "grants_all_rewards", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerCollectableItem), &Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected_SetBit(void* Obj)
	{
		((FLootLockerCollectableItem*)Obj)->just_collected = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected = { "just_collected", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerCollectableItem), &Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_collected,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_rewards,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_grants_all_rewards,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::NewProp_just_collected,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerCollectableItem",
		sizeof(FLootLockerCollectableItem),
		alignof(FLootLockerCollectableItem),
		Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectableItem()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableItem_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCollectableItem"), sizeof(FLootLockerCollectableItem), Get_Z_Construct_UScriptStruct_FLootLockerCollectableItem_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCollectableItem_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableItem_Hash() { return 4243342578U; }
class UScriptStruct* FLootLockerCollectableReward::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableReward_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerCollectableReward, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerCollectableReward"), sizeof(FLootLockerCollectableReward), Get_Z_Construct_UScriptStruct_FLootLockerCollectableReward_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerCollectableReward>()
{
	return FLootLockerCollectableReward::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerCollectableReward(FLootLockerCollectableReward::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerCollectableReward"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableReward
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableReward()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerCollectableReward")),new UScriptStruct::TCppStructOps<FLootLockerCollectableReward>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerCollectableReward;
	struct Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_asset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_asset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_asset_variation_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_asset_variation_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_asset_rental_option_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_asset_rental_option_id;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerCollectableReward>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset = { "asset", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableReward, asset), Z_Construct_UScriptStruct_FLootLockerAsset, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_variation_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_variation_id = { "asset_variation_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableReward, asset_variation_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_variation_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_variation_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_rental_option_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_rental_option_id = { "asset_rental_option_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerCollectableReward, asset_rental_option_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_rental_option_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_rental_option_id_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_variation_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::NewProp_asset_rental_option_id,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerCollectableReward",
		sizeof(FLootLockerCollectableReward),
		alignof(FLootLockerCollectableReward),
		Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectableReward()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableReward_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerCollectableReward"), sizeof(FLootLockerCollectableReward), Get_Z_Construct_UScriptStruct_FLootLockerCollectableReward_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerCollectableReward_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerCollectableReward_Hash() { return 1058448218U; }
	void ULootLockerCollectablesRequestHandler::StaticRegisterNativesULootLockerCollectablesRequestHandler()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerCollectablesRequestHandler_NoRegister()
	{
		return ULootLockerCollectablesRequestHandler::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameAPI/LootLockerCollectablesRequestHandler.h" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerCollectablesRequestHandler.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerCollectablesRequestHandler>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::ClassParams = {
		&ULootLockerCollectablesRequestHandler::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerCollectablesRequestHandler()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerCollectablesRequestHandler_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerCollectablesRequestHandler, 799111067);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerCollectablesRequestHandler>()
	{
		return ULootLockerCollectablesRequestHandler::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerCollectablesRequestHandler(Z_Construct_UClass_ULootLockerCollectablesRequestHandler, &ULootLockerCollectablesRequestHandler::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerCollectablesRequestHandler"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerCollectablesRequestHandler);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
