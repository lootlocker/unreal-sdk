# Path-specific instructions — Public/GameAPI request handlers

Applies to files under: `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/`

- These headers define the SDK’s request/response DTOs and request handler entrypoints.
- Keep module boundaries intact:
  - Do not include runtime `Private/` headers here.
- DTO conventions (verifiable in existing handlers):
  - Prefer `USTRUCT(BlueprintType)` for request/response structs.
  - Use `UPROPERTY(EditAnywhere, BlueprintReadWrite, ...)` on fields.
  - JSON-facing fields commonly use **snake_case** to match backend payload keys; keep names aligned with expected JSON keys.
  - Response structs typically inherit from `FLootLockerResponse` (preserve `success`, `StatusCode`, `ErrorData`, `Context`).
- JSON / Blueprint compatibility (critical):
  - These structs are serialized/deserialized via `FJsonObjectConverter` in the shared request plumbing.
  - Prefer additive changes to request/response DTOs.
  - Avoid removing or renaming existing `UPROPERTY` fields: it can break user code, backend JSON expectations, and Blueprint pins.
  - If you must discourage a field, prefer keeping it and using Unreal's deprecation metadata for properties (`DeprecatedProperty` / `DeprecationMessage`) when appropriate.
- Handler method conventions:
  - Typically `static FString <Method>(..., const <DelegateType>& OnCompletedRequest)` returning a request id.
  - Prefer standard C++ delegates (`DECLARE_DELEGATE_OneParam`) here (Blueprint dynamic delegates belong in the Blueprint facade).
- Request plumbing:
  - Prefer using existing endpoint catalog entries (`ULootLockerGameEndpoints`) and the `LLAPI<ResponseType>` wrapper rather than duplicating HTTP/JSON code.
- Logging & secrets:
  - Treat tokens/credentials/API keys as sensitive; avoid logging them.
  - If logging JSON request bodies, use `LootLockerUtilities::ObfuscateJsonStringForLogging(...)` (or repo-consistent equivalent).
