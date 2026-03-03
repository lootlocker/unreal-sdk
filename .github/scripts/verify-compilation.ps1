#Requires -Version 5.0
<#
.SYNOPSIS
    Verifies that the LootLocker Unreal SDK plugin compiles without errors.

.DESCRIPTION
    Reads unreal-dev-settings.json from the repo root, locates the plugin's
    .uplugin file, then runs Unreal's RunUAT BuildPlugin in batch mode to
    check that the plugin compiles cleanly on the local machine.

    See .github/instructions/verification.md for setup instructions.

.NOTES
    Exit codes: 0 = compilation succeeded, 1 = compilation failed or setup error.
#>

$ErrorActionPreference = 'Stop'

$RepoRoot   = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$SettingsFile = Join-Path $RepoRoot "unreal-dev-settings.json"
$BuildOutput  = Join-Path $RepoRoot "Build~\PluginBuild"
$LogFile      = Join-Path $RepoRoot "Build~\UAT.log"

function Write-Step { param([string]$Msg) Write-Host $Msg }
function Write-Ok   { param([string]$Msg) Write-Host $Msg -ForegroundColor Green }
function Write-Fail { param([string]$Msg) Write-Host $Msg -ForegroundColor Red }
function Write-Warn { param([string]$Msg) Write-Host $Msg -ForegroundColor Yellow }

Write-Step "==========================================="
Write-Step "  LootLocker Unreal SDK - Compile Check"
Write-Step "==========================================="
Write-Step ""

# ---------------------------------------------------------------------------
# 1. Load settings
# ---------------------------------------------------------------------------
if (-not (Test-Path $SettingsFile)) {
    Write-Warn "SETUP REQUIRED: 'unreal-dev-settings.json' not found at repo root."
    Write-Step ""
    Write-Step "Create the file with the following content:"
    Write-Step '  { "unreal_engine_path": "C:\\Program Files\\Epic Games\\UE_5.5" }'
    Write-Step ""
    Write-Step "See .github/instructions/verification.md for details."
    exit 1
}

$Settings      = Get-Content $SettingsFile -Raw | ConvertFrom-Json
$UnrealRoot    = $Settings.unreal_engine_path

if ([string]::IsNullOrWhiteSpace($UnrealRoot)) {
    Write-Fail "ERROR: 'unreal_engine_path' is empty in unreal-dev-settings.json."
    exit 1
}
if (-not (Test-Path $UnrealRoot)) {
    Write-Fail "ERROR: Unreal Engine path not found: $UnrealRoot"
    exit 1
}

$RunUAT = Join-Path $UnrealRoot "Engine\Build\BatchFiles\RunUAT.bat"
if (-not (Test-Path $RunUAT)) {
    Write-Fail "ERROR: RunUAT.bat not found at: $RunUAT"
    Write-Step "       Check that 'unreal_engine_path' points to the UE install root."
    exit 1
}

# ---------------------------------------------------------------------------
# 2. Locate the plugin uplugin file
# ---------------------------------------------------------------------------
$PluginFile = Get-ChildItem -Path $RepoRoot -Filter "*.uplugin" -Recurse -Depth 2 |
              Select-Object -First 1

if (-not $PluginFile) {
    Write-Fail "ERROR: No .uplugin file found under $RepoRoot"
    exit 1
}

Write-Step "Plugin  : $($PluginFile.FullName)"
Write-Step "Engine  : $UnrealRoot"
Write-Step "Output  : $BuildOutput"
Write-Step "Log     : $LogFile"
Write-Step ""

# ---------------------------------------------------------------------------
# 3. Prepare output directories and clear stale log
# ---------------------------------------------------------------------------
# Use cmd rmdir rather than Remove-Item: it's more forceful about releasing
# Windows file handles that are still held by antivirus / Explorer after a
# previous crashed build.
if (Test-Path $BuildOutput) {
    Write-Step "Clearing previous build output..."
    & cmd /c "rmdir /S /Q `"$BuildOutput`"" 2>&1 | Out-Null
    # If anything is still locked, warn but continue - UAT will overwrite it.
    if (Test-Path $BuildOutput) {
        Write-Warn "Warning: Could not fully remove previous build output at $BuildOutput - UAT will attempt to overwrite it."
    }
}
$LogDir = Split-Path $LogFile
if (-not (Test-Path $LogDir)) { New-Item -ItemType Directory -Path $LogDir -Force | Out-Null }
# Remove the previous run's log immediately so a stale file is never
# mistaken for the current run's output if UAT is interrupted.
if (Test-Path $LogFile) { Remove-Item $LogFile -Force }

# ---------------------------------------------------------------------------
# 4. Temporarily disable UBA local execution
#
# UbaDetours.dll (Unreal Build Accelerator) crashes on some machines when
# detouring rc.exe (Windows resource compiler), killing the build with
# ExitCode=-1 after only a couple of actions. Disabling UBA local execution
# makes UBT fall back to its standard parallel local executor, which is
# reliable and sufficient for a plugin compile check.
#
# We write a temporary BuildConfiguration.xml override and always remove it.
# ---------------------------------------------------------------------------
$UbtConfigDir = Join-Path $env:APPDATA "Unreal Engine\UnrealBuildTool"
$UbtConfigFile = Join-Path $UbtConfigDir "BuildConfiguration.xml"
$UbtConfigBackup = $UbtConfigFile + ".verify-compilation-backup"
$WroteUbtConfig = $false

if (-not (Test-Path $UbtConfigDir)) { New-Item -ItemType Directory -Path $UbtConfigDir -Force | Out-Null }

if (Test-Path $UbtConfigFile) {
    Copy-Item $UbtConfigFile $UbtConfigBackup -Force
}

$noUbaXml = @'
<?xml version="1.0" encoding="utf-8" ?>
<Configuration xmlns="https://www.unrealengine.com/BuildConfiguration">
  <BuildConfiguration>
    <bAllowUBAExecutor>false</bAllowUBAExecutor>
  </BuildConfiguration>
</Configuration>
'@
[IO.File]::WriteAllText($UbtConfigFile, $noUbaXml)
$WroteUbtConfig = $true
Write-Step "Note: Disabled UBA local executor to avoid UbaDetours/rc.exe crash (restored after build)."
Write-Step ""

# ---------------------------------------------------------------------------
# 5. Run RunUAT BuildPlugin
# ---------------------------------------------------------------------------
Write-Step "Running: RunUAT BuildPlugin (Win64, this may take a few minutes on a cold cache) ..."
Write-Step ""

$uatArgs = @(
    "BuildPlugin"
    "-Plugin=`"$($PluginFile.FullName)`""
    "-Package=`"$BuildOutput`""
    "-Rocket"
    "-TargetPlatforms=Win64"
    "-VS2022"
)

$prevEAP = $ErrorActionPreference
$ErrorActionPreference = 'Continue'

# Run RunUAT, streaming each line to the console and appending to the log
# file immediately so the log is never stale if the process is interrupted.
$uatOutput = [System.Collections.Generic.List[string]]::new()
$logStream = [System.IO.StreamWriter]::new($LogFile, $false, [System.Text.Encoding]::UTF8)
try {
    & $RunUAT @uatArgs 2>&1 | ForEach-Object {
        $line = "$_"
        $uatOutput.Add($line)
        $logStream.WriteLine($line)
        $logStream.Flush()
        Write-Host $line
    }
} finally {
    $logStream.Close()

    # Always restore the UBT config regardless of build outcome.
    if ($WroteUbtConfig) {
        if (Test-Path $UbtConfigBackup) {
            Move-Item $UbtConfigBackup $UbtConfigFile -Force
        } else {
            Remove-Item $UbtConfigFile -Force -ErrorAction SilentlyContinue
        }
    }
}
$script:uat_exit = $LASTEXITCODE

$ErrorActionPreference = $prevEAP

# ---------------------------------------------------------------------------
# 6. Report results
# ---------------------------------------------------------------------------
Write-Step ""
Write-Step "--- Compilation result ---"
Write-Step ""

# Echo any compiler error lines to the console for quick triage
$compilerErrors = $uatOutput | Select-String -Pattern "error C\d+|error LNK\d+|Error:|Deprecation:|Result: Failed" | Select-String -NotMatch "0 error\(s\)|not a preferred version"
if ($compilerErrors) {
    $compilerErrors | ForEach-Object { Write-Host $_.Line }
    Write-Step ""
}

Write-Step "----------------------------------"
Write-Step ""

if ($script:uat_exit -eq 0) {
    Write-Ok "COMPILATION SUCCEEDED"
}
else {
    # Search for a clean failure summary line from RunUAT
    $failureLine = $uatOutput | Select-String -Pattern "BUILD FAILED|Failed to build|ExitCode=\d+" | Select-Object -First 1
    $reason = if ($failureLine) { $failureLine.Line.Trim() } else { "exit code: $script:uat_exit" }
    Write-Fail "COMPILATION FAILED ($reason)"
    Write-Step "Full log: $LogFile"
    exit 1
}
