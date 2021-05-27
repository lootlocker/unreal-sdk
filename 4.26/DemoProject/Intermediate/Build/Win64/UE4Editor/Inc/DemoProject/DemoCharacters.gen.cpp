// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoCharacters.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoCharacters() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoCharacters_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoCharacters();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
// End Cross Module References
	DEFINE_FUNCTION(ADemoCharacters::execUpdateCharacter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateCharacter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execGetEquipableContextsByCharacterId)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetEquipableContextsByCharacterId();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execGetEquipableContextsToDefaultCharacter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetEquipableContextsToDefaultCharacter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execGetOtherPlayersCurrentLoadoutToDefaultCharacter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetOtherPlayersCurrentLoadoutToDefaultCharacter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execGetCurrentLoadoutToDefaultCharacter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetCurrentLoadoutToDefaultCharacter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execUnEquipAssetToCharacterById)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UnEquipAssetToCharacterById();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execUnEquipAssetToDefaultCharacter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UnEquipAssetToDefaultCharacter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execEquipAssetToCharacterById)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EquipAssetToCharacterById();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execEquipAssetToDefaultCharacter)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EquipAssetToDefaultCharacter();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCharacters::execGetCharacterLoadout)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetCharacterLoadout();
		P_NATIVE_END;
	}
	void ADemoCharacters::StaticRegisterNativesADemoCharacters()
	{
		UClass* Class = ADemoCharacters::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "EquipAssetToCharacterById", &ADemoCharacters::execEquipAssetToCharacterById },
			{ "EquipAssetToDefaultCharacter", &ADemoCharacters::execEquipAssetToDefaultCharacter },
			{ "GetCharacterLoadout", &ADemoCharacters::execGetCharacterLoadout },
			{ "GetCurrentLoadoutToDefaultCharacter", &ADemoCharacters::execGetCurrentLoadoutToDefaultCharacter },
			{ "GetEquipableContextsByCharacterId", &ADemoCharacters::execGetEquipableContextsByCharacterId },
			{ "GetEquipableContextsToDefaultCharacter", &ADemoCharacters::execGetEquipableContextsToDefaultCharacter },
			{ "GetOtherPlayersCurrentLoadoutToDefaultCharacter", &ADemoCharacters::execGetOtherPlayersCurrentLoadoutToDefaultCharacter },
			{ "UnEquipAssetToCharacterById", &ADemoCharacters::execUnEquipAssetToCharacterById },
			{ "UnEquipAssetToDefaultCharacter", &ADemoCharacters::execUnEquipAssetToDefaultCharacter },
			{ "UpdateCharacter", &ADemoCharacters::execUpdateCharacter },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "EquipAssetToCharacterById", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "EquipAssetToDefaultCharacter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "GetCharacterLoadout", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "GetCurrentLoadoutToDefaultCharacter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "GetEquipableContextsByCharacterId", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "GetEquipableContextsToDefaultCharacter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "GetOtherPlayersCurrentLoadoutToDefaultCharacter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "UnEquipAssetToCharacterById", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "UnEquipAssetToDefaultCharacter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCharacters_UpdateCharacter_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCharacters_UpdateCharacter_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Characters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCharacters_UpdateCharacter_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCharacters, nullptr, "UpdateCharacter", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCharacters_UpdateCharacter_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCharacters_UpdateCharacter_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCharacters_UpdateCharacter()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCharacters_UpdateCharacter_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoCharacters_NoRegister()
	{
		return ADemoCharacters::StaticClass();
	}
	struct Z_Construct_UClass_ADemoCharacters_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InstanceId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_InstanceId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_CharacterId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetVariationId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetVariationId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OtherPlayerId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OtherPlayerId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsDefault_MetaData[];
#endif
		static void NewProp_IsDefault_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsDefault;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CharacterName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CharacterName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoCharacters_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoCharacters_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoCharacters_EquipAssetToCharacterById, "EquipAssetToCharacterById" }, // 2073142489
		{ &Z_Construct_UFunction_ADemoCharacters_EquipAssetToDefaultCharacter, "EquipAssetToDefaultCharacter" }, // 1209543822
		{ &Z_Construct_UFunction_ADemoCharacters_GetCharacterLoadout, "GetCharacterLoadout" }, // 2132814530
		{ &Z_Construct_UFunction_ADemoCharacters_GetCurrentLoadoutToDefaultCharacter, "GetCurrentLoadoutToDefaultCharacter" }, // 422186928
		{ &Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsByCharacterId, "GetEquipableContextsByCharacterId" }, // 1898714258
		{ &Z_Construct_UFunction_ADemoCharacters_GetEquipableContextsToDefaultCharacter, "GetEquipableContextsToDefaultCharacter" }, // 602715364
		{ &Z_Construct_UFunction_ADemoCharacters_GetOtherPlayersCurrentLoadoutToDefaultCharacter, "GetOtherPlayersCurrentLoadoutToDefaultCharacter" }, // 3399124418
		{ &Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToCharacterById, "UnEquipAssetToCharacterById" }, // 1247820870
		{ &Z_Construct_UFunction_ADemoCharacters_UnEquipAssetToDefaultCharacter, "UnEquipAssetToDefaultCharacter" }, // 4111304997
		{ &Z_Construct_UFunction_ADemoCharacters_UpdateCharacter, "UpdateCharacter" }, // 136697398
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoCharacters.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_InstanceId_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_InstanceId = { "InstanceId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCharacters, InstanceId), METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_InstanceId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_InstanceId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterId_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterId = { "CharacterId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCharacters, CharacterId), METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetId_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetId = { "AssetId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCharacters, AssetId), METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetVariationId_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetVariationId = { "AssetVariationId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCharacters, AssetVariationId), METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetVariationId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetVariationId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_OtherPlayerId_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_OtherPlayerId = { "OtherPlayerId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCharacters, OtherPlayerId), METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_OtherPlayerId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_OtherPlayerId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	void Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault_SetBit(void* Obj)
	{
		((ADemoCharacters*)Obj)->IsDefault = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault = { "IsDefault", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ADemoCharacters), &Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault_SetBit, METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterName_MetaData[] = {
		{ "Category", "DemoCharacters" },
		{ "ModuleRelativePath", "Public/Demo/DemoCharacters.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterName = { "CharacterName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCharacters, CharacterName), METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoCharacters_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_InstanceId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_AssetVariationId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_OtherPlayerId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_IsDefault,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCharacters_Statics::NewProp_CharacterName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoCharacters_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoCharacters>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoCharacters_Statics::ClassParams = {
		&ADemoCharacters::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoCharacters_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoCharacters_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCharacters_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoCharacters()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoCharacters_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoCharacters, 2568883340);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoCharacters>()
	{
		return ADemoCharacters::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoCharacters(Z_Construct_UClass_ADemoCharacters, &ADemoCharacters::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoCharacters"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoCharacters);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
