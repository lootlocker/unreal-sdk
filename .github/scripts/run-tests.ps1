#Requires -Version 5.0
<#
.SYNOPSIS
    Builds the LootLocker Unreal SDK plugin and runs its automation tests headlessly.

.DESCRIPTION
    1. Builds the plugin via RunUAT BuildPlugin (same as verify-compilation.ps1) so
       compiled binaries are available.
    2. Creates a minimal VerificationProject in Temp~/VerificationProject/ with a
       directory junction pointing to the compiled Build~/PluginBuild/ output.
    3. Invokes UnrealEditor-Cmd.exe with -ExecCmds to run the specified tests.
    4. Parses the output for pass/fail and exits 0 on success, 1 on failure.

    See .github/instructions/verification.md for setup instructions.

.PARAMETER TestFilter
    Substring matched against test names/paths by the UE automation system
    (passed to "automation RunTests <filter>").  Every LootLocker test path
    starts with "LootLocker.", so the default "LootLocker" runs all of them.
    Use a more specific substring to run a subset — e.g. "LootLocker.Balances".

.PARAMETER NoBuild
    Skip the BuildPlugin step and reuse the previously built binaries. Useful
    for iterating on tests without waiting for a full rebuild. Ignored (build
    always runs) when -Clean is also specified.

.PARAMETER Clean
    Delete the previous build output before building. Omit for a faster
    incremental build (UAT reuses cached artifacts). Overrides -NoBuild.

.PARAMETER TimeoutSeconds
    Maximum seconds to wait for UnrealEditor-Cmd.exe to exit after tests finish.
    If exceeded the process is killed and the run is reported as failed.
    Defaults to 600 (10 minutes).

.NOTES
    Exit codes: 0 = all tests passed, 1 = one or more tests failed or setup error.
#>
param(
    [string]$TestFilter = "LootLocker",
    [switch]$NoBuild,
    [switch]$Clean,
    [int]$TimeoutSeconds = 600
)

$ErrorActionPreference = 'Stop'

$RepoRoot      = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$SettingsFile  = Join-Path $RepoRoot "unreal-dev-settings.json"
$BuildOutput   = Join-Path $RepoRoot "Build~\PluginBuild"
$BuildLog      = Join-Path $RepoRoot "Build~\UAT.log"
$ProjectDir    = Join-Path $RepoRoot "Temp~\VerificationProject"
$ProjectName   = "VerificationProject"
$ProjectFile   = Join-Path $ProjectDir "$ProjectName.uproject"
$PluginLinkDir = Join-Path $ProjectDir "Plugins\LootLockerSDK"
$TestLog       = Join-Path $RepoRoot "Temp~\automation-tests.log"

function Write-Step { param([string]$Msg) Write-Host $Msg }
function Write-Ok   { param([string]$Msg) Write-Host $Msg -ForegroundColor Green }
function Write-Fail { param([string]$Msg) Write-Host $Msg -ForegroundColor Red }
function Write-Warn { param([string]$Msg) Write-Host $Msg -ForegroundColor Yellow }

Write-Step "============================================"
Write-Step "  LootLocker Unreal SDK - Automation Tests"
Write-Step "============================================"
Write-Step ""

# ---------------------------------------------------------------------------
# 1. Load settings
# ---------------------------------------------------------------------------
if (-not (Test-Path $SettingsFile)) {
    Write-Warn "SETUP REQUIRED: 'unreal-dev-settings.json' not found at repo root."
    Write-Step '  { "unreal_engine_path": "C:\\Program Files\\Epic Games\\UE_5.5" }'
    exit 1
}

$Settings   = Get-Content $SettingsFile -Raw | ConvertFrom-Json
$UnrealRoot = $Settings.unreal_engine_path

if ([string]::IsNullOrWhiteSpace($UnrealRoot) -or -not (Test-Path $UnrealRoot)) {
    Write-Fail "ERROR: Unreal Engine path not found: $UnrealRoot"
    exit 1
}

$RunUAT    = Join-Path $UnrealRoot "Engine\Build\BatchFiles\RunUAT.bat"
$EditorCmd = Join-Path $UnrealRoot "Engine\Binaries\Win64\UnrealEditor-Cmd.exe"

if (-not (Test-Path $RunUAT)) {
    Write-Fail "ERROR: RunUAT.bat not found at: $RunUAT"
    exit 1
}
if (-not (Test-Path $EditorCmd)) {
    Write-Fail "ERROR: UnrealEditor-Cmd.exe not found at: $EditorCmd"
    exit 1
}

$PluginFile = Get-ChildItem -Path (Join-Path $RepoRoot "LootLockerSDK") -Filter "*.uplugin" |
              Select-Object -First 1
if (-not $PluginFile) {
    Write-Fail "ERROR: No .uplugin file found under $RepoRoot\LootLockerSDK"
    exit 1
}

$ShouldBuild = $Clean -or (-not $NoBuild)

# ---------------------------------------------------------------------------
# 2. Temporarily disable UBA + 3. Build the plugin
# ---------------------------------------------------------------------------
$UbtConfigDir    = Join-Path $env:APPDATA "Unreal Engine\UnrealBuildTool"
$UbtConfigFile   = Join-Path $UbtConfigDir "BuildConfiguration.xml"
$UbtConfigBackup = $UbtConfigFile + ".run-tests-backup"
$WroteUbtConfig  = $false

function Restore-UbtConfig {
    if ($script:WroteUbtConfig) {
        if (Test-Path $script:UbtConfigBackup) {
            Move-Item $script:UbtConfigBackup $script:UbtConfigFile -Force
        } else {
            Remove-Item $script:UbtConfigFile -Force -ErrorAction SilentlyContinue
        }
        $script:WroteUbtConfig = $false
    }
}

if ($ShouldBuild) {
    # Temporarily disable UBA (same reason as in verify-compilation.ps1)
    if (-not (Test-Path $UbtConfigDir)) { New-Item -ItemType Directory -Path $UbtConfigDir -Force | Out-Null }
    if (Test-Path $UbtConfigFile) { Copy-Item $UbtConfigFile $UbtConfigBackup -Force }

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
    Write-Step "Note: Disabled UBA local executor (restored after tests)."
    Write-Step ""

    # Build the plugin (ensures the latest test code is compiled into binaries)
    Write-Step "Step 1/3 - Building plugin via RunUAT BuildPlugin ..."
    Write-Step "Plugin  : $($PluginFile.FullName)"
    Write-Step "Engine  : $UnrealRoot"
    Write-Step "Output  : $BuildOutput"
    Write-Step ""

    $BuildLogDir = Split-Path $BuildLog
    if (-not (Test-Path $BuildLogDir)) { New-Item -ItemType Directory -Path $BuildLogDir -Force | Out-Null }
    if (Test-Path $BuildLog) { Remove-Item $BuildLog -Force }

    if ($Clean) {
        if (Test-Path $BuildOutput) {
            Write-Step "Cleaning previous build output..."
            & cmd /c "rmdir /S /Q `"$BuildOutput`"" 2>&1 | Out-Null
            if (Test-Path $BuildOutput) {
                Write-Warn "Warning: Could not fully remove previous build output - UAT will attempt to overwrite."
            }
        }
    } elseif (Test-Path $BuildOutput) {
        Write-Step "Reusing existing build output (pass -Clean to force a full rebuild)."
    }

    $prevEAP = $ErrorActionPreference
    $ErrorActionPreference = 'Continue'

    $buildLines  = [System.Collections.Generic.List[string]]::new()
    $buildStream = [System.IO.StreamWriter]::new($BuildLog, $false, [System.Text.Encoding]::UTF8)

    $uatArgs = @(
        "BuildPlugin"
        "-Plugin=`"$($PluginFile.FullName)`""
        "-Package=`"$BuildOutput`""
        "-Rocket"
        "-TargetPlatforms=Win64"
        "-VS2022"
    )

    try {
        & $RunUAT @uatArgs 2>&1 | ForEach-Object {
            $line = "$_"
            $buildLines.Add($line)
            $buildStream.WriteLine($line)
            $buildStream.Flush()
            Write-Host $line
        }
    } finally {
        $buildStream.Close()
    }
    $buildExit = $LASTEXITCODE
    $ErrorActionPreference = $prevEAP

    if ($buildExit -ne 0) {
        Restore-UbtConfig
        Write-Fail "BUILD FAILED - cannot run tests without compiled binaries."
        Write-Step "Full build log: $BuildLog"
        exit 1
    }
    Write-Step ""
    Write-Ok "Plugin built successfully."
    Write-Step ""
} else {
    if (-not (Test-Path $BuildOutput)) {
        Write-Fail "ERROR: No previous build found at $BuildOutput - run without -NoBuild first."
        exit 1
    }
    Write-Warn "Skipping build (-NoBuild). Reusing existing binaries in: $BuildOutput"
    Write-Step ""
}

# ---------------------------------------------------------------------------
# 4. Set up VerificationProject pointing at the compiled plugin output
# ---------------------------------------------------------------------------
Write-Step "Step 2/3 - Setting up VerificationProject ..."

if (-not (Test-Path $ProjectDir)) {
    New-Item -ItemType Directory -Path $ProjectDir -Force | Out-Null
}

# Always (re)write the uproject so disabled-plugin list stays current.
$uproject = @{
    FileVersion       = 3
    EngineAssociation = ""
    Category          = ""
    Description       = ""
    Plugins           = @(
        @{ Name = "LootLockerSDK";   Enabled = $true  }
        # Engine plugins that fail to load without a full Marketplace installation
        @{ Name = "Bridge";          Enabled = $false }
        @{ Name = "MegascansPlugin"; Enabled = $false }
        @{ Name = "Fab";             Enabled = $false }
    )
} | ConvertTo-Json -Depth 5
[IO.File]::WriteAllText($ProjectFile, $uproject)

$PluginsDir = Join-Path $ProjectDir "Plugins"
if (-not (Test-Path $PluginsDir)) {
    New-Item -ItemType Directory -Path $PluginsDir -Force | Out-Null
}

# Recreate the junction if it does not exist or points at a stale target.
if (Test-Path $PluginLinkDir) {
    $linkItem      = Get-Item $PluginLinkDir -Force
    $needsRecreate = ($linkItem.LinkType -ne "Junction") -or
                     ($linkItem.Target -and ($linkItem.Target -ne $BuildOutput))
    if ($needsRecreate) {
        & cmd /c "rmdir `"$PluginLinkDir`"" 2>&1 | Out-Null
        if (Test-Path $PluginLinkDir) { Remove-Item $PluginLinkDir -Recurse -Force }
    }
}
if (-not (Test-Path $PluginLinkDir)) {
    Write-Step "Creating plugin junction: Plugins\LootLockerSDK -> $BuildOutput"
    New-Item -ItemType Junction -Path $PluginLinkDir -Target $BuildOutput | Out-Null
}
Write-Step ""

# ---------------------------------------------------------------------------
# 5. Run automation tests via UnrealEditor-Cmd.exe
# ---------------------------------------------------------------------------
Write-Step "Step 3/3 - Running automation tests ..."
Write-Step "Project  : $ProjectFile"
Write-Step "Filter   : $TestFilter"
Write-Step "Log      : $TestLog"
Write-Step ""

$TestLogDir = Split-Path $TestLog
if (-not (Test-Path $TestLogDir)) { New-Item -ItemType Directory -Path $TestLogDir -Force | Out-Null }
if (Test-Path $TestLog) { Remove-Item $TestLog -Force }

# UE's -ExecCmds treats ',' as a command separator, so translate to '+' which
# is the automation system's own OR-filter separator.
$automationFilter = $TestFilter -replace ',', '+'
$execCmd    = "automation RunTests $automationFilter;quit"
$editorArgs = @(
    "`"$ProjectFile`""
    "-unattended"
    "-nullrhi"
    "-nosound"
    "-NoSplash"
    "-NoPause"
    "-NoTargetPlatforms"
    "-stdout"
    "-FullStdOutLogOutput"
    "-SkipBadPlugins"
    "-LogCmds=`"LogTemp Verbose`""
    "-ExecCmds=`"$execCmd`""
)

$prevEAP = $ErrorActionPreference
$ErrorActionPreference = 'Continue'
$outputLines = [System.Collections.Generic.List[string]]::new()
$testStream  = [System.IO.StreamWriter]::new($TestLog, $false, [System.Text.Encoding]::UTF8)
$timedOut    = $false

# Run the editor inside a separate runspace so the main thread can enforce a
# hard timeout. We keep PowerShell's native & call operator (not
# ProcessStartInfo redirection) so UE's -stdout/-FullStdOutLogOutput flags
# work correctly — UE suppresses output when stdout is redirected at the OS level.
$outputQueue = [System.Collections.Concurrent.ConcurrentQueue[string]]::new()
$ueRunspace  = [System.Management.Automation.Runspaces.RunspaceFactory]::CreateRunspace()
$ueRunspace.Open()
$ueRunspace.SessionStateProxy.SetVariable('EditorCmd',   $EditorCmd)
$ueRunspace.SessionStateProxy.SetVariable('editorArgs',  $editorArgs)
$ueRunspace.SessionStateProxy.SetVariable('outputQueue', $outputQueue)

$uePowerShell = [System.Management.Automation.PowerShell]::Create()
$uePowerShell.Runspace = $ueRunspace
[void]$uePowerShell.AddScript({
    & $EditorCmd @editorArgs 2>&1 | ForEach-Object { $outputQueue.Enqueue("$_") }
})

# Snapshot existing UE pids so we can kill only our new instance on timeout.
$priorUEPids = @(Get-Process -Name "UnrealEditor-Cmd" -ErrorAction SilentlyContinue |
                 Select-Object -ExpandProperty Id)
$ueProc   = $null
$ueHandle = $uePowerShell.BeginInvoke()

try {
    # Wait up to 30 s for our editor process to appear so we have its PID for a targeted kill.
    $spawnDeadline = [DateTime]::Now.AddSeconds(30)
    while ($null -eq $ueProc -and [DateTime]::Now -lt $spawnDeadline -and -not $ueHandle.IsCompleted) {
        $ueProc = Get-Process -Name "UnrealEditor-Cmd" -ErrorAction SilentlyContinue |
                  Where-Object { $priorUEPids -notcontains $_.Id } |
                  Select-Object -First 1
        if ($null -eq $ueProc) { Start-Sleep -Milliseconds 500 }
    }

    $deadline = [DateTime]::Now.AddSeconds($TimeoutSeconds)
    while (-not $ueHandle.IsCompleted) {
        $item = $null
        while ($outputQueue.TryDequeue([ref]$item)) {
            $outputLines.Add($item)
            $testStream.WriteLine($item)
            $testStream.Flush()
            Write-Host $item
            $item = $null
        }
        if ([DateTime]::Now -gt $deadline) {
            $timedOut = $true
            Write-Warn ""
            Write-Warn "TIMEOUT: killing UnrealEditor-Cmd.exe (no exit within $TimeoutSeconds s)"
            if ($null -ne $ueProc -and -not $ueProc.HasExited) { $ueProc.Kill() }
            $uePowerShell.Stop()
            break
        }
        Start-Sleep -Milliseconds 100
    }
    if (-not $timedOut) { try { [void]$uePowerShell.EndInvoke($ueHandle) } catch {} }
    # Drain any output still queued after the runspace finished.
    $item = $null
    while ($outputQueue.TryDequeue([ref]$item)) {
        $outputLines.Add($item)
        $testStream.WriteLine($item)
        $testStream.Flush()
        Write-Host $item
        $item = $null
    }
} finally {
    $testStream.Close()
    $uePowerShell.Dispose()
    $ueRunspace.Close()
    $ueRunspace.Dispose()
    Restore-UbtConfig
}
$ErrorActionPreference = $prevEAP

# ---------------------------------------------------------------------------
# 6. Parse results
#    UE automation outputs lines like:
#      LogAutomationController: Test Completed. Result={Passed|Failed} ...
#      LogAutomationController: Automation Test Succeeded
#      LogAutomationController: Automation Test Failed
# ---------------------------------------------------------------------------
Write-Step ""
Write-Step "--- Test results ---"
Write-Step ""

if ($timedOut) {
    Write-Fail "TIMED OUT - UnrealEditor-Cmd.exe did not exit within $TimeoutSeconds seconds"
    Write-Step "Full log: $TestLog"
    exit 1
}

$passedLines = $outputLines | Select-String -Pattern "Test Completed\. Result=\{?(?:Passed|Success)\}?"
$failedLines  = $outputLines | Select-String -Pattern "Test Completed\. Result=\{?(?:Failed|Fail)\}?"
$totalPassed = ($passedLines | Measure-Object).Count
$totalFailed = ($failedLines | Measure-Object).Count

if ($failedLines) {
    $failedLines | ForEach-Object { Write-Host $_.Line -ForegroundColor Red }
    Write-Step ""
}

Write-Step "----------------------------------"
Write-Step "Passed : $totalPassed"
Write-Step "Failed : $totalFailed"
Write-Step ""

if ($totalFailed -eq 0 -and $totalPassed -gt 0) {
    Write-Ok "ALL TESTS PASSED"
    exit 0
} elseif ($totalPassed -eq 0 -and $totalFailed -eq 0) {
    Write-Fail "NO TESTS RAN - check the log for startup errors"
    Write-Step "Full log: $TestLog"
    exit 1
} else {
    Write-Fail "TESTS FAILED"
    Write-Step "Full log: $TestLog"
    exit 1
}
