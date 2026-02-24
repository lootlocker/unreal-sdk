# Path-specific instructions — Private/GameAPI implementations

Applies to files under: `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/`

- Implement request handlers declared under `Public/GameAPI/`.
- Prefer using existing shared plumbing:
  - `LLAPI<ResponseType>::CallAPI(...)` / `CallAPIUsingRawJSON(...)`
  - `ULootLockerGameEndpoints` for endpoints
  - `ULootLockerHttpClient` for transport
- Params and auth headers:
  - Path params: pass ordered arguments as `TArray<FStringFormatArg>{ ... }` (do not pre-encode).
  - Query params: use `TMultiMap<FString, FString>` and only add values when meaningful.
  - Do not manually add `x-session-token`; `ULootLockerHttpClient` sets it from `PlayerData.Token` when present.
- Keep responses consistent:
  - Ensure `success`, `StatusCode`, `ErrorData`, and `Context` are propagated as in the existing `LLAPI` pattern.
  - Use `FResponseInspectorCallback` (where already used) for side effects before invoking the user delegate (for example caching player state on successful auth).
- Deprecation-aware changes:
  - Avoid silent breaking behavior changes in existing requests unless explicitly requested.
  - If an API needs to change behavior or migrate routes, prefer keeping the old request method working (or forwarding internally) and adding a new method/type for the new behavior.
- Logging & secrets:
  - Do not log tokens/credentials/API keys.
  - If logging JSON for diagnostics, obfuscate using `LootLockerUtilities::ObfuscateJsonStringForLogging(...)`.
- Comments:
  - Keep comments minimal and focused; avoid restating obvious code.
