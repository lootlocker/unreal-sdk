# Coding agent guardrails (Unreal SDK)

These guardrails are **non-negotiable** for work in this repo.

## Branching & PR rules

- Default branches:
  - `main`: latest released state. Updated only by **manual PR** from `dev` → `main`.
  - `dev`: working trunk. **Never commit directly** to `dev`.
- Always work on a **work branch** (examples: `docs/...`, `feat/...`, `fix/...`, `chore/...`, `refactor/...`, `meta/...`, `ci/...`, `scout/...`).
- PRs must target **base = `dev`** (never `main`).

## Release/versioning prohibitions

Unless the task explicitly asks for it, do **not**:
- create tags
- create GitHub releases
- publish packages/binaries
- bump versions or change release metadata (for example `.uplugin` `Version`/`VersionName`)

## Change discipline

- Prefer **minimal diffs**; touch only files required for the task.
- **Do not** move/rename files or restructure directories unless explicitly requested.
- **Search-first**: before adding new helpers/types/files, search the repo to avoid duplication.
- Respect module boundaries:
  - Public API lives under `LootLockerSDK/Source/<Module>/Public/`.
  - Internal implementation lives under `LootLockerSDK/Source/<Module>/Private/`.
  - Avoid including `Private/` headers from outside the owning module.

## When unsure

If any requirement is ambiguous (scope, ownership, API surface, versioning, release steps), **stop and ask** 1–3 focused clarifying questions before making changes.
