// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoTriggerEvents.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoTriggerEvents() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoTriggerEvents_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoTriggerEvents();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerTriggerEvent();
// End Cross Module References
	DEFINE_FUNCTION(ADemoTriggerEvents::execDemoGetTriggeredEvents)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetTriggeredEvents();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoTriggerEvents::execDemoTriggerEvent)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoTriggerEvent();
		P_NATIVE_END;
	}
	void ADemoTriggerEvents::StaticRegisterNativesADemoTriggerEvents()
	{
		UClass* Class = ADemoTriggerEvents::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoGetTriggeredEvents", &ADemoTriggerEvents::execDemoGetTriggeredEvents },
			{ "DemoTriggerEvent", &ADemoTriggerEvents::execDemoTriggerEvent },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Trigger Events" },
		{ "ModuleRelativePath", "Public/Demo/DemoTriggerEvents.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoTriggerEvents, nullptr, "DemoGetTriggeredEvents", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Trigger Events" },
		{ "ModuleRelativePath", "Public/Demo/DemoTriggerEvents.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoTriggerEvents, nullptr, "DemoTriggerEvent", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoTriggerEvents_NoRegister()
	{
		return ADemoTriggerEvents::StaticClass();
	}
	struct Z_Construct_UClass_ADemoTriggerEvents_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Event;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoTriggerEvents_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoTriggerEvents_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoTriggerEvents_DemoGetTriggeredEvents, "DemoGetTriggeredEvents" }, // 2951119973
		{ &Z_Construct_UFunction_ADemoTriggerEvents_DemoTriggerEvent, "DemoTriggerEvent" }, // 1722220567
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoTriggerEvents_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoTriggerEvents.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoTriggerEvents.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoTriggerEvents_Statics::NewProp_Event_MetaData[] = {
		{ "Category", "DemoTriggerEvents" },
		{ "ModuleRelativePath", "Public/Demo/DemoTriggerEvents.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoTriggerEvents_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoTriggerEvents, Event), Z_Construct_UScriptStruct_FLootLockerTriggerEvent, METADATA_PARAMS(Z_Construct_UClass_ADemoTriggerEvents_Statics::NewProp_Event_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoTriggerEvents_Statics::NewProp_Event_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoTriggerEvents_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoTriggerEvents_Statics::NewProp_Event,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoTriggerEvents_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoTriggerEvents>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoTriggerEvents_Statics::ClassParams = {
		&ADemoTriggerEvents::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoTriggerEvents_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoTriggerEvents_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoTriggerEvents_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoTriggerEvents_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoTriggerEvents()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoTriggerEvents_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoTriggerEvents, 148375478);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoTriggerEvents>()
	{
		return ADemoTriggerEvents::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoTriggerEvents(Z_Construct_UClass_ADemoTriggerEvents, &ADemoTriggerEvents::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoTriggerEvents"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoTriggerEvents);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
