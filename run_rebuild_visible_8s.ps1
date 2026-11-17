$ErrorActionPreference = 'Stop'

$runDirectory = Join-Path $PSScriptRoot 'REVERSED\build\run'
$sourcePath = Join-Path $runDirectory 'groove_rebuild.exe'
$runToken = [Guid]::NewGuid().ToString('N')
$gamePath = Join-Path $runDirectory ("groove_rebuild_watchdog_{0}.exe" -f $runToken)

if (-not (Test-Path -LiteralPath $sourcePath -PathType Leaf)) {
    throw "Rebuilt game was not found: $sourcePath"
}

if (-not ('GrooveWindowControl' -as [type])) {
    Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class GrooveWindowControl {
    [DllImport("user32.dll")] public static extern bool ShowWindowAsync(IntPtr hWnd, int command);
    [DllImport("user32.dll")] public static extern bool BringWindowToTop(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hWnd);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd);
}
'@
}

# Windows has a path-specific compatibility override on the staged filename.
# Launch a byte-for-byte copy with a unique path so the same rebuilt image runs
# without inheriting that override. Keep the asset working directory unchanged.
Copy-Item -LiteralPath $sourcePath -Destination $gamePath
$game = $null
try {
    Write-Host "Starting rebuilt game from: $sourcePath"
    Write-Host "Isolated launch path: $gamePath"
    $game = Start-Process -FilePath $gamePath -WorkingDirectory $runDirectory -PassThru -WindowStyle Normal
    $watch = [System.Diagnostics.Stopwatch]::StartNew()
    $maximumRunMilliseconds = 8000
    $window = [IntPtr]::Zero

    while ($watch.ElapsedMilliseconds -lt 3000 -and -not $game.HasExited) {
        $game.Refresh()
        $window = [IntPtr]$game.MainWindowHandle
        if ($window -ne [IntPtr]::Zero) { break }
        Start-Sleep -Milliseconds 100
    }

    if ($window -ne [IntPtr]::Zero) {
        [void][GrooveWindowControl]::ShowWindowAsync($window, 9)
        [void][GrooveWindowControl]::BringWindowToTop($window)
        [void][GrooveWindowControl]::SetForegroundWindow($window)
        Start-Sleep -Milliseconds 150
        $game.Refresh()
        Write-Host ("Game window: title='{0}', visible={1}" -f $game.MainWindowTitle, [GrooveWindowControl]::IsWindowVisible($window))
    } else {
        Write-Host 'The process did not create a main window during the first 3 seconds.'
    }

    $remainingMilliseconds = [Math]::Max(0, $maximumRunMilliseconds - [int]$watch.ElapsedMilliseconds)
    if (-not $game.HasExited -and -not $game.WaitForExit($remainingMilliseconds)) {
        Stop-Process -Id $game.Id -Force -ErrorAction SilentlyContinue
        [void]$game.WaitForExit(3000)
        Write-Host 'Stopped the game at the eight-second watchdog limit.'
    } elseif ($game.HasExited) {
        Write-Host ("Game exited on its own with code {0}." -f $game.ExitCode)
    }
} finally {
    if ($game) {
        $game.Refresh()
        if (-not $game.HasExited) {
            Stop-Process -Id $game.Id -Force -ErrorAction SilentlyContinue
            [void]$game.WaitForExit(3000)
            $game.Refresh()
        }
        if (-not $game.HasExited) {
            throw "Could not stop diagnostic process $($game.Id); temporary executable is retained at $gamePath."
        }
    }

    if (Test-Path -LiteralPath $gamePath) {
        Remove-Item -LiteralPath $gamePath -Force
    }
    Write-Host ("Temporary executable removed: {0}" -f (-not (Test-Path -LiteralPath $gamePath)))
}

Write-Host "Trace log: $(Join-Path $runDirectory 'groove_trace.log')"
