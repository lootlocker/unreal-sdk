// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoMissions.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoMissions() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoMissions_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoMissions();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerFinishMissionData();
// End Cross Module References
	DEFINE_FUNCTION(ADemoMissions::execDemoFinishMission)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoFinishMission();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoMissions::execDemoStartMission)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoStartMission();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoMissions::execDemoGetMission)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetMission();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoMissions::execDemoGetAllMissions)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAllMissions();
		P_NATIVE_END;
	}
	void ADemoMissions::StaticRegisterNativesADemoMissions()
	{
		UClass* Class = ADemoMissions::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoFinishMission", &ADemoMissions::execDemoFinishMission },
			{ "DemoGetAllMissions", &ADemoMissions::execDemoGetAllMissions },
			{ "DemoGetMission", &ADemoMissions::execDemoGetMission },
			{ "DemoStartMission", &ADemoMissions::execDemoStartMission },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoMissions_DemoFinishMission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoMissions_DemoFinishMission_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Missions" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoMissions_DemoFinishMission_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoMissions, nullptr, "DemoFinishMission", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoMissions_DemoFinishMission_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoMissions_DemoFinishMission_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoMissions_DemoFinishMission()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoMissions_DemoFinishMission_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Missions" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoMissions, nullptr, "DemoGetAllMissions", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoMissions_DemoGetMission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoMissions_DemoGetMission_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Missions" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoMissions_DemoGetMission_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoMissions, nullptr, "DemoGetMission", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoMissions_DemoGetMission_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoMissions_DemoGetMission_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoMissions_DemoGetMission()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoMissions_DemoGetMission_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoMissions_DemoStartMission_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoMissions_DemoStartMission_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Missions" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoMissions_DemoStartMission_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoMissions, nullptr, "DemoStartMission", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoMissions_DemoStartMission_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoMissions_DemoStartMission_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoMissions_DemoStartMission()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoMissions_DemoStartMission_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoMissions_NoRegister()
	{
		return ADemoMissions::StaticClass();
	}
	struct Z_Construct_UClass_ADemoMissions_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MissionId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_MissionId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MissionData_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MissionData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoMissions_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoMissions_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoMissions_DemoFinishMission, "DemoFinishMission" }, // 2200498312
		{ &Z_Construct_UFunction_ADemoMissions_DemoGetAllMissions, "DemoGetAllMissions" }, // 734366040
		{ &Z_Construct_UFunction_ADemoMissions_DemoGetMission, "DemoGetMission" }, // 2212816908
		{ &Z_Construct_UFunction_ADemoMissions_DemoStartMission, "DemoStartMission" }, // 2690096669
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoMissions_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoMissions.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionId_MetaData[] = {
		{ "Category", "DemoMissions" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionId = { "MissionId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoMissions, MissionId), METADATA_PARAMS(Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionData_MetaData[] = {
		{ "Category", "DemoMissions" },
		{ "ModuleRelativePath", "Public/Demo/DemoMissions.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionData = { "MissionData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoMissions, MissionData), Z_Construct_UScriptStruct_FLootLockerFinishMissionData, METADATA_PARAMS(Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoMissions_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoMissions_Statics::NewProp_MissionData,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoMissions_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoMissions>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoMissions_Statics::ClassParams = {
		&ADemoMissions::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoMissions_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoMissions_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoMissions_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoMissions_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoMissions()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoMissions_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoMissions, 3625421948);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoMissions>()
	{
		return ADemoMissions::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoMissions(Z_Construct_UClass_ADemoMissions, &ADemoMissions::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoMissions"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoMissions);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
