# LootLocker Unreal SDK — implementation patterns (reference)

Docs-only. This document complements the style guide by describing the *existing* patterns used when adding/changing SDK functionality.

This doc intentionally avoids re-stating rules that already live in:

- `.github/instructions/style-guide.md` (repo-wide conventions)
- applicable `.github/instructions/**/*.instructions.md` files (higher-precedence, path-specific rules)

If this doc and the surrounding code disagree, prefer the surrounding code and keep diffs minimal.

## Pattern: add a new API call (end-to-end)

This repo generally uses a layered structure:

1) Endpoint catalog (`ULootLockerGameEndpoints`)
2) Request handler (GameAPI handler class)
3) Public facade(s) (`ULootLockerSDKManager` for C++, `ULootLockerManager` for Blueprint)

### 1) Add/declare the endpoint

- Declare a new `static FLootLockerEndPoints` in:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerGameEndpoints.h`
- Initialize it in:
  - `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerGameEndpoints.cpp`

Conventions:

- Use `FLootLockerEndPoints` with `.endpoint` and `.requestMethod`.
- Prefer using path templates and formatting args rather than concatenating strings in handlers.

### 2) Add request/response DTOs and handler method

- Prefer placing request/response structs in the relevant request handler header:
  - `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/<Something>RequestHandler.h`
- Implement the handler in:
  - `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/<Something>RequestHandler.cpp`

Conventions observed across request handlers:

- Request/response types are `USTRUCT(BlueprintType)` with `UPROPERTY(EditAnywhere, BlueprintReadWrite, ...)`.
- JSON-facing fields commonly use snake_case matching backend keys.
- Handler methods are typically `static FString <Method>(..., const <DelegateType>& OnCompletedRequest)`.

Prefer using the existing `LLAPI<ResponseType>` wrapper:

- Serialization helpers and `LLAPI` live in:
  - `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.h`

Typical call shapes:

- `LLAPI<ResponseType>::CallAPI(RequestStruct, Endpoint, OrderedArgs, QueryParams, PlayerData, OnCompletedRequest, /*optional inspector*/)`
- `LLAPI<ResponseType>::CallAPIUsingRawJSON(JsonString, Endpoint, ...)`

Parameter conventions (as used by `LLAPI` and existing handlers):

- Path params: pass ordered arguments as `TArray<FStringFormatArg>{ ... }`.
  - Do not pre-encode; `LLAPI` URL-encodes path params before formatting the endpoint URL.
- Query params: use `TMultiMap<FString, FString>` and only add params when meaningful (avoid adding empty/default values).
- Auth header: do not manually add `x-session-token` in request handlers; `ULootLockerHttpClient` sets it from `PlayerData.Token` when present.

When appropriate, use `FResponseInspectorCallback` for side effects (e.g., caching auth/session state) before invoking the consumer delegate.

### 3) Expose via public facade(s)

C++ facade:

- Add a forwarding static method to:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h`
- Implement (if needed) in:
  - `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerSDKManager.cpp`

Blueprint facade:

- Add a `UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | <Area>")` to:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h`
- Implement (if needed) in:
  - `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerManager.cpp`

Conventions observed in Blueprint facade:

- Follow the existing Blueprint exposure and documentation conventions in the facade file.

## Pattern: response/error handling

- Prefer using `FLootLockerResponse`-derived response structs.
- Ensure `success`, `StatusCode`, `ErrorData`, and `Context` are set consistently.
- For standardized synthetic errors, use the existing factories:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerResponse.h` (`LootLockerResponseFactory`)

## Pattern: logging, secrets, and boundaries

- Follow the repo-wide guidance in `.github/instructions/style-guide.md` and any applicable path-specific instruction files.

