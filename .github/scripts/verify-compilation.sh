#!/usr/bin/env bash
# verify-compilation.sh - LootLocker Unreal SDK local compilation check (macOS / Linux)
# See .github/instructions/verification.md for setup instructions.
#
# Exit codes: 0 = compilation succeeded, 1 = compilation failed or setup error.

set -uo pipefail   # intentionally no -e: we handle non-zero exits ourselves

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SETTINGS_FILE="$REPO_ROOT/unreal-dev-settings.json"
BUILD_OUTPUT="$REPO_ROOT/Build~/PluginBuild"
LOG_FILE="$REPO_ROOT/Build~/UAT.log"

RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'; NC='\033[0m'

echo "==========================================="
echo "  LootLocker Unreal SDK - Compile Check"
echo "==========================================="
echo ""

# ---------------------------------------------------------------------------
# 1. Load settings
# ---------------------------------------------------------------------------
if [[ ! -f "$SETTINGS_FILE" ]]; then
    echo -e "${YELLOW}SETUP REQUIRED:${NC} 'unreal-dev-settings.json' not found at repo root."
    echo ""
    echo "  Create the file with the following content:"
    echo '  { "unreal_engine_path": "/Users/Shared/Epic Games/UE_5.5" }'
    echo ""
    echo "  See .github/instructions/verification.md for details."
    exit 1
fi

read_json_field() {
    python3 -c "import json,sys; d=json.load(open('$1')); print(d.get('$2',''))" 2>/dev/null || true
}

UNREAL_ROOT=$(read_json_field "$SETTINGS_FILE" "unreal_engine_path")

if [[ -z "$UNREAL_ROOT" ]]; then
    echo -e "${RED}ERROR:${NC} 'unreal_engine_path' is empty in unreal-dev-settings.json."
    exit 1
fi
if [[ ! -d "$UNREAL_ROOT" ]]; then
    echo -e "${RED}ERROR:${NC} Unreal Engine path not found: $UNREAL_ROOT"
    exit 1
fi

RUN_UAT="$UNREAL_ROOT/Engine/Build/BatchFiles/RunUAT.sh"
if [[ ! -f "$RUN_UAT" ]]; then
    echo -e "${RED}ERROR:${NC} RunUAT.sh not found at: $RUN_UAT"
    echo "       Check that 'unreal_engine_path' points to the UE install root."
    exit 1
fi

# Detect target platform
if [[ "$(uname)" == "Darwin" ]]; then
    TARGET_PLATFORM="Mac"
else
    TARGET_PLATFORM="Linux"
fi

# ---------------------------------------------------------------------------
# 2. Locate the plugin .uplugin file
# ---------------------------------------------------------------------------
PLUGIN_FILE=$(find "$REPO_ROOT" -maxdepth 3 -name "*.uplugin" | head -1)
if [[ -z "$PLUGIN_FILE" ]]; then
    echo -e "${RED}ERROR:${NC} No .uplugin file found under $REPO_ROOT"
    exit 1
fi

echo "Plugin  : $PLUGIN_FILE"
echo "Engine  : $UNREAL_ROOT"
echo "Platform: $TARGET_PLATFORM"
echo "Output  : $BUILD_OUTPUT"
echo "Log     : $LOG_FILE"
echo ""

# ---------------------------------------------------------------------------
# 3. Prepare output directories and clear stale log
# ---------------------------------------------------------------------------
if [[ -d "$BUILD_OUTPUT" ]]; then
    echo "Clearing previous build output..."
    rm -rf "$BUILD_OUTPUT"
fi

mkdir -p "$(dirname "$LOG_FILE")"
# Remove stale log immediately so a previous run's content is never mistaken
# for the current run's output if UAT is interrupted.
rm -f "$LOG_FILE"

# ---------------------------------------------------------------------------
# 4. Temporarily disable UBA local execution
#
# UBA can crash on certain configurations. Disabling it makes UBT fall back
# to its standard parallel local executor, which is reliable for a plugin
# compile check. We write a temporary BuildConfiguration.xml and restore it.
# ---------------------------------------------------------------------------
if [[ "$(uname)" == "Darwin" ]]; then
    UBT_CONFIG_DIR="$HOME/Library/Application Support/Unreal Engine/UnrealBuildTool"
else
    UBT_CONFIG_DIR="${XDG_CONFIG_HOME:-$HOME/.config}/Unreal Engine/UnrealBuildTool"
fi

UBT_CONFIG_FILE="$UBT_CONFIG_DIR/BuildConfiguration.xml"
UBT_CONFIG_BACKUP="$UBT_CONFIG_FILE.verify-compilation-backup"
WROTE_UBT_CONFIG=0

mkdir -p "$UBT_CONFIG_DIR"
if [[ -f "$UBT_CONFIG_FILE" ]]; then
    cp "$UBT_CONFIG_FILE" "$UBT_CONFIG_BACKUP"
fi

cat > "$UBT_CONFIG_FILE" <<'EOF'
<?xml version="1.0" encoding="utf-8" ?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
  <BuildConfiguration>
    <bAllowUBAExecutor>false</bAllowUBAExecutor>
  </BuildConfiguration>
</Configuration>
EOF
WROTE_UBT_CONFIG=1
echo "Note: Disabled UBA local executor (restored after build)."
echo ""

# Restore UBT config on exit regardless of outcome
restore_ubt_config() {
    if [[ "$WROTE_UBT_CONFIG" -eq 1 ]]; then
        if [[ -f "$UBT_CONFIG_BACKUP" ]]; then
            mv "$UBT_CONFIG_BACKUP" "$UBT_CONFIG_FILE"
        else
            rm -f "$UBT_CONFIG_FILE"
        fi
    fi
}
trap restore_ubt_config EXIT

# ---------------------------------------------------------------------------
# 5. Run RunUAT BuildPlugin
# ---------------------------------------------------------------------------
echo "Running: RunUAT BuildPlugin ($TARGET_PLATFORM, this may take a few minutes on a cold cache) ..."
echo ""

chmod +x "$RUN_UAT"

UAT_EXIT=0
# Stream output to both console and log file simultaneously via tee
"$RUN_UAT" BuildPlugin \
    -Plugin="$PLUGIN_FILE" \
    -Package="$BUILD_OUTPUT" \
    -Rocket \
    -TargetPlatforms="$TARGET_PLATFORM" \
    2>&1 | tee "$LOG_FILE" || UAT_EXIT=${PIPESTATUS[0]}

# ---------------------------------------------------------------------------
# 6. Report results
# ---------------------------------------------------------------------------
echo ""
echo "--- Compilation result ---"
echo ""

# Surface compiler error lines for quick triage (exclude noise)
COMPILER_ERRORS=$(grep -E "error C[0-9]+|error LNK[0-9]+|Deprecation:|Result: Failed" "$LOG_FILE" \
    | grep -v "0 error(s)\|not a preferred version" || true)
if [[ -n "$COMPILER_ERRORS" ]]; then
    echo "$COMPILER_ERRORS"
    echo ""
fi

echo "----------------------------------"
echo ""

if [[ "$UAT_EXIT" -eq 0 ]]; then
    echo -e "${GREEN}COMPILATION SUCCEEDED${NC}"
else
    FAILURE_LINE=$(grep -E "BUILD FAILED|Failed to build|ExitCode=[0-9]+" "$LOG_FILE" | head -1 || true)
    REASON="${FAILURE_LINE:-exit code: $UAT_EXIT}"
    echo -e "${RED}COMPILATION FAILED${NC} ($REASON)"
    echo "Full log: $LOG_FILE"
    exit 1
fi
