## Tracking issue

<!-- Link the relevant lootlocker/index issue. Use "Closes lootlocker/index#NNN" to auto-close, or paste a plain URL. -->

Closes lootlocker/index#

---

## Description

<!-- What changed and why? One or two sentences is fine for small changes; more detail for complex ones. -->

---

## Type of change

- [ ] Bug fix
- [ ] New feature
- [ ] Refactor
- [ ] Docs
- [ ] Chore / maintenance

---

## Checklist

**Branch & PR**
- [ ] Targets `dev` branch (not `main`)
- [ ] Branch name follows the convention (`feat/`, `fix/`, `docs/`, `refactor/`, `chore/`, `ci/`, `meta/`, `scout/`)
- [ ] Diff is minimal and scoped — no unrelated changes, no drive-by refactors

**Change discipline**
- [ ] No version bumps or release metadata changes (`.uplugin` `Version`/`VersionName`, tags, releases) unless explicitly requested
- [ ] No new helpers, types, or files added without first searching the repo for existing ones

**Public API surface**
- [ ] Changes to files under `Public/` are intentional public API additions or changes
- [ ] Blueprint facade (`LootLockerManager.h`) updated if the feature is Blueprint-accessible
- [ ] C++ facade (`LootLockerSDKManager.h`) updated if the feature is C++-accessible

**Documentation** *(skip if no public types were added or changed)*
- [ ] Every new `DECLARE_DELEGATE_*` has a `/** … */` doc comment directly above it, inside an `@addtogroup` block
- [ ] Every new `UENUM` / `enum class` has its doc comment **between** `UENUM(…)` and `enum class`, wrapped in its own `@addtogroup/@{…@}` block
- [ ] Every new `USTRUCT` on the public surface has at least a one-sentence `/** … */` description
- [ ] `doxygen .doxygen/Doxyfile` runs without new errors, and the new type appears on its feature group page and is linked in function signatures

**Verification**
- [ ] Compile Check CI workflow passes (or verification has been run locally via `.github/scripts/verify-compilation.ps1` / `.sh`)

**Issue tracking**
- [ ] Tracking issue in `lootlocker/index` is linked (via the "Development" section on the issue)
- [ ] Tracking issue status set to **In Review**
- [ ] PR link posted as a comment on the tracking issue

---

## Testing notes

<!-- How was this change verified? Describe any manual steps, automated tests run, or platforms tested on. -->

---

## Additional notes

<!-- Anything the reviewer should know: trade-offs, follow-up work, open questions, etc. Delete this section if not needed. -->
