# Verifying Changes: Compilation

This repo ships as an Unreal Engine plugin. C++ must be verified through
Unreal's own build infrastructure — `cmake`, `msbuild`, or `dotnet build` will
**not** work here.

---

## Cloud coding agent (GitHub Copilot agent / CI)

When you push commits to a work branch the **`Compile Check`** workflow
(`.github/workflows/compile-check.yml`) runs automatically.  It builds the
plugin against a single fixed Unreal Engine version and verifies that the C++
compiles cleanly on Linux.

### Workflow to follow after each batch of commits

1. Push your work branch (`feat/…`, `fix/…`, `ci/…`, `copilot/…`, etc.).
2. Navigate to the **Actions** tab → **Compile Check** → your branch's run.
3. Wait for it to complete and confirm it is **green** before opening a PR.

If the workflow fails:

1. **Job Summary** (fastest) — the run's Summary page shows a compact
   `Compilation Failed` section with file path, line number, and error
   code/message.  This is the primary place to read errors; no log-digging
   required.
2. **Annotations** — the Summary page also lists inline annotations that link
   directly to the offending line and appear in the PR diff view.
3. **Raw log artifact** (fallback) — download
   `compile-check-<ue-image>-UAT.log` from the run's artifacts and search for
   `error C` / `ERROR:` / `FATAL:` to locate the failure.

Fix the reported errors and push again.

> The full multi-version matrix build (`build-with-image.yml`) runs on PRs to
> `dev` and `main`.  The compile check is a smaller, faster subset for
> in-progress work branches.

---

## Local (human developer or local Copilot instance)

### Prerequisites

1. Unreal Engine is installed locally (the version used in `unreal-dev-settings.json`
   must match a version you have installed, e.g. UE 5.5).
2. You have an `unreal-dev-settings.json` file at the repo root (gitignored).
3. PowerShell 5+ is available (built into Windows 10/11; also available on
   macOS/Linux via `pwsh`).

### One-time setup

Create `unreal-dev-settings.json` at the repo root:

```json
{
  "unreal_engine_path": "C:\\Program Files\\Epic Games\\UE_5.5"
}
```

**`unreal_engine_path`** must point to the **root** of your UE installation
(the folder that contains `Engine\Build\BatchFiles\RunUAT.bat`).

| Platform | Example path |
|---|---|
| Windows | `C:\Program Files\Epic Games\UE_5.5` |
| macOS   | `/Users/Shared/Epic Games/UE_5.5` |

### Running the check

**Windows (PowerShell 5+):**

```powershell
# Incremental build (fast — reuses previous build output)
.github\scripts\verify-compilation.ps1

# Full clean rebuild (use after structural changes or a failed incremental)
.github\scripts\verify-compilation.ps1 -Clean
```

**macOS / Linux (bash):**

```bash
bash .github/scripts/verify-compilation.sh
```

The script will:

1. Read `unreal-dev-settings.json`.
2. Locate the plugin's `.uplugin` file automatically.
3. Detect the host OS and build for the matching platform (`Win64` / `Mac` / `Linux`).
4. Print any compiler errors to the console.
5. Exit `0` on success, `1` on any compiler error.

By default the script reuses the existing `Build~/PluginBuild/` output for a
faster incremental build. Pass `-Clean` to delete it first (equivalent to the
previous behaviour).

Build artefacts land in `Build~/PluginBuild/` (gitignored); the full UAT log
is written to `Build~/UAT.log`.

---

## Running automation tests locally

```powershell
# Run all LootLocker tests (default filter = "LootLocker" matches all test paths)
.github\scripts\run-tests.ps1

# Run only a specific subset by test-path substring
.github\scripts\run-tests.ps1 -TestFilter LootLocker.Balances
.github\scripts\run-tests.ps1 -TestFilter LootLocker.Leaderboards

# Force a clean rebuild before running tests
.github\scripts\run-tests.ps1 -Clean
.github\scripts\run-tests.ps1 -TestFilter LootLocker.Balances -Clean
```

The `-TestFilter` value is a substring matched against **test path names** by UE's
`automation RunTests` command. Every LootLocker test is registered under a path that
starts with `LootLocker.`, so `"LootLocker"` (the default) runs all of them.

The `-Clean` flag deletes `Build~/PluginBuild/` before building. Omitting it
lets UAT reuse cached intermediate files for a significantly faster turnaround
during iterative test work.

---

## What counts as "verified"

A change is verified when **either** of the following is true:

- The `Compile Check` CI workflow is green on your branch, **or**
- The local verification script exits `0`.

**Additionally** ensure:

- No new `error C####` or `error LNK####` compiler errors appear.
- No new compiler warnings inside the LootLockerSDK plugin appear
- No existing public API signatures were changed without following the
  deprecation flow described in `.github/instructions/style-guide.md`.

Running the full multi-version matrix build (`build-with-image.yml`) is a CI-only step and is not required for local verification.
