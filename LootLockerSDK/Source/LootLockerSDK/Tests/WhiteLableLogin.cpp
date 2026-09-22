#include <future>

#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "TestUtils.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FWhiteLabelLogin, "LootLocker.WhiteLabel", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FWhiteLabelLogin)

void FWhiteLabelLogin::Define()
{
	Describe("WhiteLabelLogin", [this]()
	{

		LatentIt("When Working with WhiteLabel Login (requires manual steps)", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			// TODO: requires a live whitelabel-enabled game and manual credential setup — not suitable for automated CI
			UE_LOG(LogTemp, Warning, TEXT("SKIPPED: When Working with WhiteLabel Login — requires manual credential setup"));
			TestDone.Execute();
			return;

			// Fill this in to be able to test the login with your information.
			FString TestEmail = "";
			FString TestPassword = "";
			bool SkipSignup = false; // change this to true if you don't want to create the account

			if(TestEmail.IsEmpty() && !SkipSignup)
			{
				TestEmail = FString::Format(TEXT("erik+unrealci+{0}@lootlocker.com"), { FGuid::NewGuid().ToString() });
				TestPassword = "12345678";
			}

			
			TestFalse("Test email needs to be specified", TestEmail.IsEmpty());
			TestFalse("Test password needs to be specified", TestPassword.IsEmpty());

			if (!SkipSignup)
			{
				// signup
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerLoginResponse, FLootLockerLoginResponseDelegate>();

				ULootLockerSDKManager::WhiteLabelCreateAccount(TestEmail, TestPassword, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Signup success", Response.success);
				delete(Promise);
			}

			{
				// signin
				const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerWhiteLabelLoginAndSessionResponse, FLootLockerWhiteLabelLoginAndSessionResponseDelegate>();

				ULootLockerSDKManager::WhiteLabelLoginAndStartSession(TestEmail, TestPassword, Delegate);

				const auto Response = Promise->get_future().get();
				TestTrue("Signin success", Response.success);
				TestTrue("Seen Before flag has the expected value", Response.StartSessionResponse.seen_before == SkipSignup);
				TestTrue("Player has a ulid", !Response.StartSessionResponse.player_ulid.IsEmpty());
				delete(Promise);
			}

			TestDone.Execute();
		});
	});

	Describe("PrepareCustomFieldsJson", [this]()
	{
		It("converts boolean value_json from string to raw JSON boolean", [this]()
		{
			// Given
			FLootLockerWhiteLabelCreateAccountRequest SignupRequest;
			SignupRequest.email = "email@email.com";
			SignupRequest.password = "password";
			SignupRequest.custom_fields.Add(FLootLockerWhiteLabelCustomSignUpFieldValue{ "tos_agree", "true" });

			TSharedRef<FJsonObject> JsonObject = LootLockerUtilities::UStructToJsonObject(SignupRequest);

			// When
			ULootLockerAuthenticationRequestHandler::PrepareCustomFieldsJson(JsonObject);

			// Then
			TArray<TSharedPtr<FJsonValue>> ResultFields = JsonObject->GetArrayField(TEXT("custom_fields"));
			TestEqual("custom_fields count", ResultFields.Num(), 1);

			TSharedPtr<FJsonObject> ResultField = ResultFields[0]->AsObject();
			TestTrue("metadata_key preserved", ResultField->GetStringField(TEXT("metadata_key")) == TEXT("tos_agree"));
			TestTrue("value_json is now a bool", ResultField->TryGetField(TEXT("value_json"))->Type == EJson::Boolean);
			TestTrue("value_json is true", ResultField->GetBoolField(TEXT("value_json")) == true);
		});

		It("converts number value_json from string to raw JSON number", [this]()
		{
			// Given
			FLootLockerWhiteLabelCreateAccountRequest SignupRequest;
			SignupRequest.email = "email@email.com";
			SignupRequest.password = "password";
			SignupRequest.custom_fields.Add(FLootLockerWhiteLabelCustomSignUpFieldValue{ "age", "42" });

			TSharedRef<FJsonObject> JsonObject = LootLockerUtilities::UStructToJsonObject(SignupRequest);

			// When
			ULootLockerAuthenticationRequestHandler::PrepareCustomFieldsJson(JsonObject);

			// Then
			TArray<TSharedPtr<FJsonValue>> ResultFields = JsonObject->GetArrayField(TEXT("custom_fields"));
			TSharedPtr<FJsonObject> ResultField = ResultFields[0]->AsObject();
			TestTrue("value_json is now a number", ResultField->TryGetField(TEXT("value_json"))->Type == EJson::Number);
			TestEqual("value_json is 42", (int)ResultField->GetNumberField(TEXT("value_json")), 42);
		});

		It("preserves string value_json as a JSON string", [this]()
		{
			// Given
			FLootLockerWhiteLabelCreateAccountRequest SignupRequest;
			SignupRequest.email = "email@email.com";
			SignupRequest.password = "password";
			SignupRequest.custom_fields.Add(FLootLockerWhiteLabelCustomSignUpFieldValue{ "birth_date", "2000-01-15" });

			TSharedRef<FJsonObject> JsonObject = LootLockerUtilities::UStructToJsonObject(SignupRequest);

			// When
			ULootLockerAuthenticationRequestHandler::PrepareCustomFieldsJson(JsonObject);

			// Then
			TArray<TSharedPtr<FJsonValue>> ResultFields = JsonObject->GetArrayField(TEXT("custom_fields"));
			TestEqual("custom_fields count", ResultFields.Num(), 1);

			TSharedPtr<FJsonObject> ResultField = ResultFields[0]->AsObject();
			TestTrue("value_json is still a string", ResultField->TryGetField(TEXT("value_json"))->Type == EJson::String);
			TestEqual("value_json is 2000-01-15", ResultField->GetStringField(TEXT("value_json")), TEXT("2000-01-15"));
		});

		It("handles empty custom_fields array gracefully", [this]()
		{
			// Given
			TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject());
			TArray<TSharedPtr<FJsonValue>> EmptyArray;
			Root->SetArrayField(TEXT("custom_fields"), EmptyArray);

			// When
			ULootLockerAuthenticationRequestHandler::PrepareCustomFieldsJson(Root.ToSharedRef());

			// Then — no crash, array is still empty
			TestEqual("custom_fields is empty", Root->GetArrayField(TEXT("custom_fields")).Num(), 0);
		});

		It("handles JsonObject with no custom_fields field", [this]()
		{
			// Given
			TSharedPtr<FJsonObject> Root = MakeShareable(new FJsonObject());
			Root->SetStringField(TEXT("some_other_field"), TEXT("hello"));

			// When — should not crash
			ULootLockerAuthenticationRequestHandler::PrepareCustomFieldsJson(Root.ToSharedRef());

			// Then
			TestFalse("custom_fields not added", Root->HasField(TEXT("custom_fields")));
		});
	});
}
#endif

