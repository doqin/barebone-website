# Stop execution if any command fails
$ErrorActionPreference = "Stop"

Write-Host "=== Starting build ===" -ForegroundColor Cyan

# --- Configuration ---
$buildDir = "build"
$outputExe = Join-Path $buildDir "output.exe"
$appName = "output"  # process name without .exe
$sourceFiles = @(
    ".\main.cpp",
    ".\src\httpbuilder.cpp",
    ".\src\utils.cpp",
    ".\src\httpreader.cpp",
    ".\src\handlerequest.cpp",
    ".\src\types.cpp"
)
$includeDir = ".\include"
$libs = "-lws2_32"

# --- Step 1: Stop running instance if exists ---
$running = Get-Process -Name $appName -ErrorAction SilentlyContinue
if ($running) {
    Write-Host "Stopping running process '$appName.exe'..." -ForegroundColor Yellow
    Stop-Process -Name $appName -Force
    # Wait a moment to release file locks
    Start-Sleep -Seconds 1
}

# --- Step 2: Ensure build directory exists ---
if (-not (Test-Path $buildDir)) {
    Write-Host "Creating build directory..." -ForegroundColor DarkGray
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# --- Step 3: Build ---
Write-Host "Building project..." -ForegroundColor Cyan

$compileCmd = "g++ -fdiagnostics-color=always -g $($sourceFiles -join ' ') -o $outputExe $libs -I$includeDir"
Write-Host "Running: $compileCmd" -ForegroundColor DarkGray

Invoke-Expression $compileCmd

# --- Step 4: Check for build errors ---
if ($LASTEXITCODE -ne 0) {
    Write-Host "`n❌ Build failed with exit code $LASTEXITCODE" -ForegroundColor Red
    if (Test-Path $outputExe) {
        Remove-Item $outputExe -Force
    }
    exit $LASTEXITCODE
} else {
    Write-Host "`n✅ Build succeeded!" -ForegroundColor Green
}

# --- Step 5: Run the new build ---
if (Test-Path $outputExe) {
    Write-Host "Launching new build..." -ForegroundColor Yellow
    Start-Process $outputExe
} else {
    Write-Host "⚠️ No executable found at $outputExe, skipping run." -ForegroundColor Red
}

exit 0
