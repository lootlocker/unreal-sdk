// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/GameAPI/LootLockerMessagesRequestHandler.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerMessagesRequestHandler() {}
// Cross Module References
	LOOTLOCKERSDK_API UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMessagesResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerResponse();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMessage();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerMessagesRequestHandler_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerMessagesRequestHandler();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics
	{
		struct _Script_LootLockerSDK_eventMessagesResponseDelegateBP_Parms
		{
			FLootLockerMessagesResponse Response;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LootLockerSDK_eventMessagesResponseDelegateBP_Parms, Response), Z_Construct_UScriptStruct_FLootLockerMessagesResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LootLockerSDK, nullptr, "MessagesResponseDelegateBP__DelegateSignature", nullptr, nullptr, sizeof(_Script_LootLockerSDK_eventMessagesResponseDelegateBP_Parms), Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LootLockerSDK_MessagesResponseDelegateBP__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}

static_assert(std::is_polymorphic<FLootLockerMessagesResponse>() == std::is_polymorphic<FLootLockerResponse>(), "USTRUCT FLootLockerMessagesResponse cannot be polymorphic unless super FLootLockerResponse is polymorphic");

class UScriptStruct* FLootLockerMessagesResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMessagesResponse, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMessagesResponse"), sizeof(FLootLockerMessagesResponse), Get_Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMessagesResponse>()
{
	return FLootLockerMessagesResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMessagesResponse(FLootLockerMessagesResponse::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMessagesResponse"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMessagesResponse
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMessagesResponse()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMessagesResponse")),new UScriptStruct::TCppStructOps<FLootLockerMessagesResponse>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMessagesResponse;
	struct Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_messages_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_messages_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_messages;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMessagesResponse>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages_Inner = { "messages", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerMessage, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages = { "messages", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessagesResponse, messages), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::NewProp_messages,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		Z_Construct_UScriptStruct_FLootLockerResponse,
		&NewStructOps,
		"LootLockerMessagesResponse",
		sizeof(FLootLockerMessagesResponse),
		alignof(FLootLockerMessagesResponse),
		Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMessagesResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMessagesResponse"), sizeof(FLootLockerMessagesResponse), Get_Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMessagesResponse_Hash() { return 115493845U; }
class UScriptStruct* FLootLockerMessage::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOOTLOCKERSDK_API uint32 Get_Z_Construct_UScriptStruct_FLootLockerMessage_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLootLockerMessage, Z_Construct_UPackage__Script_LootLockerSDK(), TEXT("LootLockerMessage"), sizeof(FLootLockerMessage), Get_Z_Construct_UScriptStruct_FLootLockerMessage_Hash());
	}
	return Singleton;
}
template<> LOOTLOCKERSDK_API UScriptStruct* StaticStruct<FLootLockerMessage>()
{
	return FLootLockerMessage::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLootLockerMessage(FLootLockerMessage::StaticStruct, TEXT("/Script/LootLockerSDK"), TEXT("LootLockerMessage"), false, nullptr, nullptr);
static struct FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMessage
{
	FScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMessage()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("LootLockerMessage")),new UScriptStruct::TCppStructOps<FLootLockerMessage>);
	}
} ScriptStruct_LootLockerSDK_StaticRegisterNativesFLootLockerMessage;
	struct Z_Construct_UScriptStruct_FLootLockerMessage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_title_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_title;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_published_at_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_published_at;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_body_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_body;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_summary_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_summary;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_category_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_category;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_alert_MetaData[];
#endif
		static void NewProp_alert_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_alert;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_New_MetaData[];
#endif
		static void NewProp_New_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_New;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_action_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_action;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_image_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_image;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLootLockerMessage>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_title_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_title = { "title", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, title), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_title_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_title_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_published_at_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_published_at = { "published_at", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, published_at), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_published_at_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_published_at_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_body_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_body = { "body", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, body), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_body_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_body_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_summary_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_summary = { "summary", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, summary), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_summary_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_summary_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_category_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_category = { "category", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, category), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_category_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_category_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert_SetBit(void* Obj)
	{
		((FLootLockerMessage*)Obj)->alert = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert = { "alert", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerMessage), &Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New_SetBit(void* Obj)
	{
		((FLootLockerMessage*)Obj)->New = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New = { "New", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLootLockerMessage), &Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_action_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_action = { "action", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, action), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_action_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_action_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_image_MetaData[] = {
		{ "Category", "LootLocker" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_image = { "image", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLootLockerMessage, image), METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_image_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_image_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLootLockerMessage_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_title,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_published_at,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_body,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_summary,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_category,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_alert,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_New,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_action,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLootLockerMessage_Statics::NewProp_image,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLootLockerMessage_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
		nullptr,
		&NewStructOps,
		"LootLockerMessage",
		sizeof(FLootLockerMessage),
		alignof(FLootLockerMessage),
		Z_Construct_UScriptStruct_FLootLockerMessage_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLootLockerMessage_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLootLockerMessage()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLootLockerMessage_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LootLockerSDK();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LootLockerMessage"), sizeof(FLootLockerMessage), Get_Z_Construct_UScriptStruct_FLootLockerMessage_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLootLockerMessage_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLootLockerMessage_Hash() { return 3297464606U; }
	void ULootLockerMessagesRequestHandler::StaticRegisterNativesULootLockerMessagesRequestHandler()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerMessagesRequestHandler_NoRegister()
	{
		return ULootLockerMessagesRequestHandler::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameAPI/LootLockerMessagesRequestHandler.h" },
		{ "ModuleRelativePath", "Public/GameAPI/LootLockerMessagesRequestHandler.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerMessagesRequestHandler>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::ClassParams = {
		&ULootLockerMessagesRequestHandler::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerMessagesRequestHandler()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerMessagesRequestHandler_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerMessagesRequestHandler, 4129768559);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerMessagesRequestHandler>()
	{
		return ULootLockerMessagesRequestHandler::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerMessagesRequestHandler(Z_Construct_UClass_ULootLockerMessagesRequestHandler, &ULootLockerMessagesRequestHandler::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerMessagesRequestHandler"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerMessagesRequestHandler);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
