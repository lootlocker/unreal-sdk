# Path-specific instructions — LootLockerSDKManager.h

Applies to: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h`

- Treat this file as a **public C++ facade**. Avoid breaking changes (signature changes, renames, removals) unless explicitly requested.
- Keep diffs minimal: do not reformat unrelated sections of this large header.
- Maintain the existing documentation style:
  - Use `/** ... */` doc blocks.
  - Document all parameters with `@param` and include a meaningful `@return` when a value is returned.
  - If a function returns a request id, document that it is a **unique id used to match callbacks**.
- Preserve the existing semantics around player selection:
  - When a function accepts `ForPlayerWithUlid` (or `PlayerUlid`), it is treated as optional in many APIs (empty often implies “default player”). Keep that consistent with surrounding code.
- Prefer routing work through existing request handlers (`Public/GameAPI/…`) and existing plumbing (`LLAPI`, `ULootLockerHttpClient`) instead of adding bespoke HTTP/JSON logic here.
- Be explicit about error behavior in docs when it is already called out in nearby functions (for example, “HTTP 401 indicates refresh token expired” patterns).
