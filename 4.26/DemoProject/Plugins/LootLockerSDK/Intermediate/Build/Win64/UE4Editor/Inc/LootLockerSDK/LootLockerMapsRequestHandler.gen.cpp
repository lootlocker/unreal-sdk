// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/GameAPI/LootLockerMapsRequestHandler.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerMapsRequestHandler() {}
// Cross Module References
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerGetMapsResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMap();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMapCamera();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerMapsRequestHandler_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerMapsRequestHandler();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventGetMapsResponseDelegateBP_Parms
		{
			FLootLockerGetMapsResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventGetMapsResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerGetMapsResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "GetMapsResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventGetMapsResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_GetMapsResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}

static_assert(std::is_polymorphic<FLootLockerGetMapsResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerGetMapsResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerGetMapsResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerGetMapsResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerGetMapsResponse"), sizeof(FLootLockerGetMapsResponse), Get_Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerGetMapsResponse>()
{
	return FLootLockerGetMapsResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerGetMapsResponse(FLootLockerGetMapsResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerGetMapsResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerGetMapsResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerGetMapsResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerGetMapsResponse")),new UScriptStruct::TCppStructOps<FLootLockerGetMapsResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerGetMapsResponse;
	struct Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_maps_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_maps_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_maps;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerGetMapsResponse>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps_Inner = { "maps", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMap, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps = { "maps", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerGetMapsResponse, maps), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::NewProp_maps,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerGetMapsResponse",
		sizeof(FLootLockerGetMapsResponse),
		alignof(FLootLockerGetMapsResponse),
		Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerGetMapsResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerGetMapsResponse"), sizeof(FLootLockerGetMapsResponse), Get_Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerGetMapsResponse_Hash() { return 3724038940U; }
class UScriptStruct* FLootLockerMap::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMap_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMap, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMap"), sizeof(FLootLockerMap), Get_Z_Construct_UScriptStruct_FLootLockerMap_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMap>()
{
	return FLootLockerMap::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMap(FLootLockerMap::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMap"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMap
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMap()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMap")),new UScriptStruct::TCppStructOps<FLootLockerMap>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMap;
	struct Z_Construct_UScriptStruct_FLootLockerMap_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_map_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_map_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_asset_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_asset_id;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_spawn_points_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_spawn_points_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_spawn_points;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_player_access_MetaData[];
#endif
		static void NewProp_player_access_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_player_access;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMap_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMap>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_map_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_map_id = { "map_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMap, map_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_map_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_map_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_asset_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_asset_id = { "asset_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMap, asset_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_asset_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_asset_id_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points_Inner = { "spawn_points", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points = { "spawn_points", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMap, spawn_points), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access_SetBit(void* Obj)
	{
		((FLootLockerMap*)Obj)->player_access = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access = { "player_access", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerMap), &Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMap_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_map_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_asset_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_spawn_points,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMap_Statics::NewProp_player_access,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMap_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMap",
		sizeof(FLootLockerMap),
		alignof(FLootLockerMap),
		Z_Construct_UScriptStruct_FLootLockerMap_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMap_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMap_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMap_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMap()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMap_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMap"), sizeof(FLootLockerMap), Get_Z_Construct_UScriptStruct_FLootLockerMap_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMap_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMap_Hash() { return 1605577846U; }
class UScriptStruct* FLootLockerMapSpawnPoint::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMapSpawnPoint"), sizeof(FLootLockerMapSpawnPoint), Get_Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMapSpawnPoint>()
{
	return FLootLockerMapSpawnPoint::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMapSpawnPoint(FLootLockerMapSpawnPoint::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMapSpawnPoint"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMapSpawnPoint
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMapSpawnPoint()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMapSpawnPoint")),new UScriptStruct::TCppStructOps<FLootLockerMapSpawnPoint>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMapSpawnPoint;
	struct Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_asset_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_asset_id;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_position_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_position;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_rotation;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_cameras_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_cameras_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_cameras;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_player_access_MetaData[];
#endif
		static void NewProp_player_access_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_player_access;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMapSpawnPoint>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_asset_id_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_asset_id = { "asset_id", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMapSpawnPoint, asset_id), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_asset_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_asset_id_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_position_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_position = { "position", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMapSpawnPoint, position), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_position_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_position_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_rotation_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_rotation = { "rotation", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMapSpawnPoint, rotation), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_rotation_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras_Inner = { "cameras", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMapCamera, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras = { "cameras", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMapSpawnPoint, cameras), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access_SetBit(void* Obj)
	{
		((FLootLockerMapSpawnPoint*)Obj)->player_access = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access = { "player_access", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerMapSpawnPoint), &Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_asset_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_position,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_rotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_cameras,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::NewProp_player_access,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMapSpawnPoint",
		sizeof(FLootLockerMapSpawnPoint),
		alignof(FLootLockerMapSpawnPoint),
		Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMapSpawnPoint"), sizeof(FLootLockerMapSpawnPoint), Get_Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMapSpawnPoint_Hash() { return 1355395263U; }
class UScriptStruct* FLootLockerMapCamera::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMapCamera_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMapCamera, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMapCamera"), sizeof(FLootLockerMapCamera), Get_Z_Construct_UScriptStruct_FLootLockerMapCamera_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMapCamera>()
{
	return FLootLockerMapCamera::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMapCamera(FLootLockerMapCamera::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMapCamera"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMapCamera
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMapCamera()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMapCamera")),new UScriptStruct::TCppStructOps<FLootLockerMapCamera>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMapCamera;
	struct Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_position_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_position;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_rotation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMapCamera>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_position_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_position = { "position", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMapCamera, position), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_position_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_position_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_rotation_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_rotation = { "rotation", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMapCamera, rotation), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_rotation_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_position,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::NewProp_rotation,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMapCamera",
		sizeof(FLootLockerMapCamera),
		alignof(FLootLockerMapCamera),
		Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMapCamera()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMapCamera_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMapCamera"), sizeof(FLootLockerMapCamera), Get_Z_Construct_UScriptStruct_FLootLockerMapCamera_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMapCamera_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMapCamera_Hash() { return 1814433819U; }
	void ULootLockerMapsRequestHandler::StaticRegisterNativesULootLockerMapsRequestHandler()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerMapsRequestHandler_NoRegister()
	{
		return ULootLockerMapsRequestHandler::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameAPI/LootLockerMapsRequestHandler.h" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMapsRequestHandler.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerMapsRequestHandler>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::ClassParams = {
		&ULootLockerMapsRequestHandler::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerMapsRequestHandler()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerMapsRequestHandler_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerMapsRequestHandler, 878462872);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerMapsRequestHandler>()
	{
		return ULootLockerMapsRequestHandler::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerMapsRequestHandler(Z_Construct_UClass_ULootLockerMapsRequestHandler, &ULootLockerMapsRequestHandler::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerMapsRequestHandler"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerMapsRequestHandler);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
