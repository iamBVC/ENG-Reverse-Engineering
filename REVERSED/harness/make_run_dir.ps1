# make_run_dir.ps1 - build a run directory that looks like a full install.
#
#     powershell -ExecutionPolicy Bypass -File harness\make_run_dir.ps1
#
# The game was shipped in two halves - an HD part (exe, DLLs, saves) and a CD part (movies,
# level WADs) - and it opens its assets by relative name, so a rebuild has to sit next to
# both.  This assembles them in REVERSED\build\run\ using **hardlinks**: the CD half is
# hundreds of megabytes of movies and WADs that are only ever read, and a hardlink is the
# same file under another name.  Save slots are *copied*, because the game writes those.
#
# Two layouts are handled, since both are legitimate:
#   * Game\Hd\ + Game\Cd\   the two halves kept apart
#   * Game\                 already merged into one installation folder
# Paths resolve from this script's location, so it works from any checkout.

$ErrorActionPreference = 'Stop'
$harness = $PSScriptRoot                              # ...\REVERSED\harness
$reversed = Split-Path -Parent $harness               # ...\REVERSED
$root = Split-Path -Parent $reversed                  # the project root, holding Game\
$run = Join-Path $reversed 'build\run'
$game = Join-Path $root 'Game'

function Link-File([string]$source, [string]$dest) {
    $destDir = Split-Path -Parent $dest
    if (-not (Test-Path -LiteralPath $destDir)) { New-Item -ItemType Directory -Force -Path $destDir | Out-Null }
    if (Test-Path -LiteralPath $dest) { Remove-Item -LiteralPath $dest -Force }
    New-Item -ItemType HardLink -Path $dest -Target $source | Out-Null
}

function Copy-Tree([string]$source, [string]$destRoot) {
    $copied = 0
    foreach ($f in Get-ChildItem -LiteralPath $source -Recurse -File) {
        if ($f.Name -eq 'groove.exe' -or $f.Name -eq 'groove.exe.i64') { continue }   # not needed to run
        $rel = $f.FullName.Substring($source.Length + 1)
        $dest = Join-Path $destRoot $rel
        if ($f.Extension -eq '.ksv') {
            $destDir = Split-Path -Parent $dest
            if (-not (Test-Path -LiteralPath $destDir)) { New-Item -ItemType Directory -Force -Path $destDir | Out-Null }
            Copy-Item -LiteralPath $f.FullName -Destination $dest -Force               # the game writes these
        } else {
            Link-File $f.FullName $dest
        }
        $copied++
    }
    return $copied
}

if (-not (Test-Path -LiteralPath $game)) { throw "no Game\ folder at $game" }
New-Item -ItemType Directory -Force -Path $run | Out-Null

$linked = 0
if (Test-Path -LiteralPath (Join-Path $game 'Hd')) {
    $linked += Copy-Tree (Join-Path $game 'Hd') $run
    $linked += Copy-Tree (Join-Path $game 'Cd') $run
} elseif (Test-Path -LiteralPath (Join-Path $game 'wads')) {
    $linked += Copy-Tree $game $run                       # already a merged installation
} else {
    throw "Game\ has neither Hd\ + Cd\ nor wads\ - cannot build a run layout"
}

$exe = Join-Path $reversed 'build\groove_rebuild.exe'
if (Test-Path -LiteralPath $exe) {
    Copy-Item -LiteralPath $exe -Destination (Join-Path $run 'groove_rebuild.exe') -Force
} else {
    Write-Output "NOTE: $exe does not exist yet - run harness\build_dlls.bat bulk first"
}

$wads = if (Test-Path (Join-Path $run 'wads')) { (Get-ChildItem (Join-Path $run 'wads') -File).Count } else { 0 }
Write-Output "run directory : $run"
Write-Output "  $linked file(s) linked, $wads WAD(s), 111.cor $(if (Test-Path (Join-Path $run '111.cor')) {'present'} else {'MISSING'})"
Write-Output "  run groove_rebuild.exe from there: it sets its working directory to its own"
Write-Output "  folder and writes its startup trace to groove_trace.log next to itself."
