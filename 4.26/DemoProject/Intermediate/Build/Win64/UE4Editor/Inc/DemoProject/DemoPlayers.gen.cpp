// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoPlayers.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoPlayers() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoPlayers_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoPlayers();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerGetRequests();
// End Cross Module References
	DEFINE_FUNCTION(ADemoPlayers::execSetProfilePublic)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetProfilePublic();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execSetProfilePrivate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetProfilePrivate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execGetDLCsMigration)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetDLCsMigration();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execInitiateDLCMigration)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitiateDLCMigration();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execGetCurrencyBalance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetCurrencyBalance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execDemoCheckPlayerAssetDeactivationNotification)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoCheckPlayerAssetDeactivationNotification();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execDemoCheckPlayerAssetNotification)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoCheckPlayerAssetNotification();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execDemoGetOtherPlayerInfo)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetOtherPlayerInfo();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execDemoSubmitXp)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoSubmitXp();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execDemoGetInventory)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetInventory();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPlayers::execDemoGetPlayerInfo)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetPlayerInfo();
		P_NATIVE_END;
	}
	void ADemoPlayers::StaticRegisterNativesADemoPlayers()
	{
		UClass* Class = ADemoPlayers::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoCheckPlayerAssetDeactivationNotification", &ADemoPlayers::execDemoCheckPlayerAssetDeactivationNotification },
			{ "DemoCheckPlayerAssetNotification", &ADemoPlayers::execDemoCheckPlayerAssetNotification },
			{ "DemoGetInventory", &ADemoPlayers::execDemoGetInventory },
			{ "DemoGetOtherPlayerInfo", &ADemoPlayers::execDemoGetOtherPlayerInfo },
			{ "DemoGetPlayerInfo", &ADemoPlayers::execDemoGetPlayerInfo },
			{ "DemoSubmitXp", &ADemoPlayers::execDemoSubmitXp },
			{ "GetCurrencyBalance", &ADemoPlayers::execGetCurrencyBalance },
			{ "GetDLCsMigration", &ADemoPlayers::execGetDLCsMigration },
			{ "InitiateDLCMigration", &ADemoPlayers::execInitiateDLCMigration },
			{ "SetProfilePrivate", &ADemoPlayers::execSetProfilePrivate },
			{ "SetProfilePublic", &ADemoPlayers::execSetProfilePublic },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "DemoCheckPlayerAssetDeactivationNotification", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "DemoCheckPlayerAssetNotification", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_DemoGetInventory_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_DemoGetInventory_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_DemoGetInventory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "DemoGetInventory", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_DemoGetInventory_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_DemoGetInventory_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_DemoGetInventory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_DemoGetInventory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "DemoGetOtherPlayerInfo", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "DemoGetPlayerInfo", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "DemoSubmitXp", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "GetCurrencyBalance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "GetDLCsMigration", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "InitiateDLCMigration", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "SetProfilePrivate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPlayers_SetProfilePublic_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPlayers_SetProfilePublic_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPlayers_SetProfilePublic_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPlayers, nullptr, "SetProfilePublic", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPlayers_SetProfilePublic_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPlayers_SetProfilePublic_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPlayers_SetProfilePublic()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPlayers_SetProfilePublic_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoPlayers_NoRegister()
	{
		return ADemoPlayers::StaticClass();
	}
	struct Z_Construct_UClass_ADemoPlayers_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_points_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_points;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_getRequests_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_getRequests;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoPlayers_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoPlayers_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetDeactivationNotification, "DemoCheckPlayerAssetDeactivationNotification" }, // 2558597403
		{ &Z_Construct_UFunction_ADemoPlayers_DemoCheckPlayerAssetNotification, "DemoCheckPlayerAssetNotification" }, // 3428029536
		{ &Z_Construct_UFunction_ADemoPlayers_DemoGetInventory, "DemoGetInventory" }, // 1209615805
		{ &Z_Construct_UFunction_ADemoPlayers_DemoGetOtherPlayerInfo, "DemoGetOtherPlayerInfo" }, // 1636041651
		{ &Z_Construct_UFunction_ADemoPlayers_DemoGetPlayerInfo, "DemoGetPlayerInfo" }, // 3219094170
		{ &Z_Construct_UFunction_ADemoPlayers_DemoSubmitXp, "DemoSubmitXp" }, // 4151204784
		{ &Z_Construct_UFunction_ADemoPlayers_GetCurrencyBalance, "GetCurrencyBalance" }, // 1001574909
		{ &Z_Construct_UFunction_ADemoPlayers_GetDLCsMigration, "GetDLCsMigration" }, // 3217610542
		{ &Z_Construct_UFunction_ADemoPlayers_InitiateDLCMigration, "InitiateDLCMigration" }, // 807262842
		{ &Z_Construct_UFunction_ADemoPlayers_SetProfilePrivate, "SetProfilePrivate" }, // 224983541
		{ &Z_Construct_UFunction_ADemoPlayers_SetProfilePublic, "SetProfilePublic" }, // 1572341759
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPlayers_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoPlayers.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPlayers_Statics::NewProp_points_MetaData[] = {
		{ "Category", "DemoPlayers" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoPlayers_Statics::NewProp_points = { "points", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPlayers, points), METADATA_PARAMS(Z_Construct_UClass_ADemoPlayers_Statics::NewProp_points_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPlayers_Statics::NewProp_points_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPlayers_Statics::NewProp_getRequests_MetaData[] = {
		{ "Category", "DemoPlayers" },
		{ "ModuleRelativePath", "Public/Demo/DemoPlayers.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoPlayers_Statics::NewProp_getRequests = { "getRequests", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPlayers, getRequests), Z_Construct_UScriptStruct_FLootLockerGetRequests, METADATA_PARAMS(Z_Construct_UClass_ADemoPlayers_Statics::NewProp_getRequests_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPlayers_Statics::NewProp_getRequests_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoPlayers_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPlayers_Statics::NewProp_points,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPlayers_Statics::NewProp_getRequests,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoPlayers_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoPlayers>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoPlayers_Statics::ClassParams = {
		&ADemoPlayers::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoPlayers_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPlayers_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoPlayers_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPlayers_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoPlayers()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoPlayers_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoPlayers, 1279537242);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoPlayers>()
	{
		return ADemoPlayers::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoPlayers(Z_Construct_UClass_ADemoPlayers, &ADemoPlayers::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoPlayers"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoPlayers);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
