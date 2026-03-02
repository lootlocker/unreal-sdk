# LootLocker Unreal SDK — conventions & style guide

Docs-only. This is a repo-specific guide for contributors and coding agents.

This guide is intentionally **descriptive**: it only documents conventions that are verifiably present in the current codebase.

## Scope & “source of truth”

- Repo structure / boundaries: see [.github/instructions/architecture.md](architecture.md)
- Guardrails for changes: see [.github/instructions/guardrails.md](guardrails.md)
- File/folder-specific rules: prefer applicable `.github/instructions/**/*.instructions.md` (linked from `.github/copilot-instructions.md`)

## 1) Module boundary discipline (non-negotiable)

This repo is an Unreal Engine **plugin** with modules under `LootLockerSDK/Source/`.

- **Runtime module**: `LootLockerSDK/Source/LootLockerSDK/`
  - Public headers (external include surface): `.../Public/`
  - Internal implementation: `.../Private/`
- **Editor module**: `LootLockerSDK/Source/LootLockerSDKEditor/` (Editor-only tooling; not shipped)

Rules (match existing architecture docs + common usage):

- Do not include `Private/` headers from outside the owning module.
- Prefer keeping helpers/internal types in `Private/`.
- Be cautious when adding new headers to `Public/` (it expands the SDK’s public API surface).

## 2) Public facades & Blueprint exposure

### Where user-facing API lives

- Blueprint-facing facade: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h` (`ULootLockerManager`)
- C++-style facade: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h` (`ULootLockerSDKManager`)

Both facades follow a “static methods on a UObject” pattern.

### Blueprint callable functions

Conventions observed in `ULootLockerManager`:

- Blueprint-facing functions are organized under the `"LootLocker Methods | <Area>"` category hierarchy.
- Many async-style Blueprint functions return a request id (`FString`) so callers can match callbacks when multiple requests are in flight.

More detailed, file-specific rules (documentation rigor, metadata usage, deprecation conventions) are captured in the path-specific instruction files for the public facades.

### Deprecation practices (observed in the Blueprint facade)

Deprecations are present in `ULootLockerManager` and `ULootLockerSDKManager` and should be treated as a compatibility mechanism (prefer deprecating over removing/renaming).

- Mark deprecated Blueprint-callable methods with `meta=(DeprecatedFunction, DeprecationMessage="...")`.
- Mark deprecated Cpp-callable methods with `[[deprecated("This method is deprecated in favor of method <alternative>")]] // Deprecation date <deprecation date>`
- Keep the existing inline comment convention for dating deprecations (for example `// Deprecation date <deprecation date>`).
- Prefer an additive migration path:
  - add a replacement method (new name/signature/behavior)
  - keep the old method working (or forward internally when feasible)
  - update `DeprecationMessage` to point at the replacement

### Delegate patterns (Blueprint vs C++)

The runtime codebase uses both:

- **Blueprint delegates** (dynamic) in `LootLockerManager.h`:
  - `DECLARE_DYNAMIC_DELEGATE_OneParam(<Name>BP, <ResponseStruct>, <ParamName>);`
  - Suffix convention: `...BP` (e.g., `FAuthResponseBP`, `FAppleSessionResponseBP`).

- **C++ delegates** (non-dynamic) in request handlers (example: `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/LootLockerAuthenticationRequestHandler.h`):
  - `DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FLootLockerAuthenticationResponse);`

Guideline:

- Use **dynamic delegates** only for Blueprint-exposed surface APIs.
- Use **standard delegates** for internal plumbing and C++ request handlers.

## 3) Request / response conventions

### Where request handlers live

- Public declarations & DTOs: `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/`
- Implementations: `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/`

Request handler classes are typically `UObject` classes with **static methods** that:

- Return an `FString` request id.
- Accept a response delegate.

More detailed, folder-specific rules (DTO conventions, delegate expectations, and plumbing preferences) are captured in the path-specific instruction files for `Public/GameAPI/` and `Private/GameAPI/`.

### Request/response DTOs (USTRUCT) and field naming

Observed pattern (example: `LootLockerAuthenticationRequestHandler.h`):

- Requests and responses are declared as `USTRUCT(BlueprintType)` (or occasionally plain `USTRUCT()`).
- Fields are `UPROPERTY(EditAnywhere, BlueprintReadWrite, ...)`.
- JSON-facing field names frequently use **snake_case** (e.g., `session_token`, `refresh_token`, `player_identifier`) which matches backend payload keys.

Guideline:

- When a field is serialized to/from backend JSON using `FJsonObjectConverter`, keep the name aligned with the expected JSON key (commonly snake_case in this repo).
- Avoid renaming existing JSON-facing fields (it can break wire compatibility and Blueprint pins). Prefer additive changes.

### Base response & error representation

- Base response struct: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerResponse.h` (`FLootLockerResponse`)
  - `success`, `StatusCode`, `FullTextFromServer`, `ErrorData`, `Context`
- Error payload: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerErrorData.h` (`FLootLockerErrorData`)
- Request context: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerRequestContext.h` (`FLootLockerRequestContext`)

Guideline:

- Response structs commonly **inherit** from `FLootLockerResponse` and add payload fields.
- If you add a new response struct, preserve the base members and mapping (`success`, `StatusCode`, `ErrorData`, `Context`).

### JSON conversion & the LLAPI wrapper

The primary request/response plumbing is implemented in:

- `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.h` (`LLAPI<ResponseType>` and helpers)

Key observed conventions:

- Requests are typically serialized using `LootLockerUtilities::UStructToJsonString(RequestStruct)`.
- Requests are sent via `ULootLockerHttpClient::SendApi(...)`.
- Response parsing uses `FJsonObjectConverter::JsonObjectStringToUStruct<ResponseType>(...)`.
- `LLAPI<ResponseType>` supports an optional `FResponseInspectorCallback` used for side effects before the user callback (e.g., caching player state on successful auth).

Guideline:

- Prefer using `LLAPI<ResponseType>::CallAPI(...)` / `CallAPIUsingRawJSON(...)` instead of duplicating HTTP/JSON code.
- If you must do custom parsing, still return a standard response struct and keep `ErrorData`/`Context` populated.

### Endpoints

Endpoints are declared as static `FLootLockerEndPoints` members in:

- `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerGameEndpoints.h`

They are initialized in the runtime module’s private implementation (`LootLockerGameEndpoints.cpp`).

Guideline:

- Add/declare new endpoints in the endpoints catalog rather than hard-coding URLs in handlers.

## 4) Logging, secrets, and safe diagnostics

### What logging utility is used

- Central logger: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerLogger.h` (`FLootLockerLogger`)
- Implementation: `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerLogger.cpp`

The SDK logs HTTP request/response information (see `ULootLockerHttpClient` and `FLootLockerLogger::LogHttpRequest`).

### Logging defaults & safety intent

Config expresses the intent to avoid accidental logging outside the editor:

- `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerConfig.h`
  - `LogOutsideOfEditor` defaults to `false`
  - Comment warns about “unintentional logging of data” because requests/responses are logged

### Do not log secrets

Treat the following as sensitive (non-exhaustive):

- Session/auth tokens (`x-session-token`, `session_token`, `token`, `refresh_token`)
- Credentials (`email`, `password`)
- API keys / domain keys (`game_key`, `domain_key`, `game_api_key`)

### Existing obfuscation helpers

There is an existing JSON obfuscation utility and a concrete list of obfuscated keys:

- `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.cpp`
  - `UObfuscationSettings::FieldsToObfuscate` includes: `game_key`, `email`, `password`, `domain_key`, `session_token`, `token`
  - `LootLockerUtilities::ObfuscateJsonStringForLogging(...)`

Guideline:

- When adding any new logging that includes JSON request/response bodies, prefer passing the JSON string through `LootLockerUtilities::ObfuscateJsonStringForLogging(...)` (or a repo-consistent equivalent) before writing it.
- Avoid adding new logs that print request headers verbatim when they may include `x-session-token`.

## 5) Documentation expectations by file type

You will encounter different documentation “bar heights” in this repo:

- Public facade APIs in `LootLockerManager.h` and `LootLockerSDKManager.h`:
  - Expect **rigorous, user-facing method documentation** (`/** ... @param ... @return ... */` style is widely used).
- Request/response DTOs (USTRUCTs) in request handler headers:
  - Prefer clear struct/field docs when the meaning is not obvious from backend naming.
- Internal/private implementation (.cpp, `Private/` helpers):
  - Keep comments minimal and focused; avoid restating obvious code.

## 6) Formatting/tooling

- No repository-wide `.clang-format` or `.editorconfig` was found at the repo root.
- The codebase contains mixed formatting (tabs/spaces, brace placement) depending on file age.

Guideline:

- Match the surrounding file style.
- Prefer minimal diffs; do not reformat unrelated lines.

## 7) Diff hygiene & duplication avoidance

- Keep changes focused (no drive-by refactors).
- Search for existing handlers/utilities before creating new ones.
  - Request handlers are already organized under `Public/GameAPI/` + `Private/GameAPI/`.

