"""Verify the independent watchdog stops a non-interactive child in three seconds."""
import subprocess
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
build = ROOT / "build"
candidates = [Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
              Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community")]
vcvars = next(p / "VC/Auxiliary/Build/vcvars32.bat" for p in candidates
              if (p / "VC/Auxiliary/Build/vcvars32.bat").exists())
(build / "watchdog_sleep.c").write_text('#include <windows.h>\nint main(void) { Sleep(60000); return 0; }\n')
batch = build / "build_watchdog.bat"
batch.write_text(f'''@echo off
call "{vcvars}" >nul
cl /nologo /TC /W4 /MT "{ROOT / 'harness/run_bounded.c'}" /Fe:run_bounded.exe /Fo:run_bounded.obj
if errorlevel 1 exit /b 1
cl /nologo /TC /MT watchdog_sleep.c /Fe:watchdog_sleep.exe /Fo:watchdog_sleep.obj
exit /b %errorlevel%
''')
subprocess.run(["cmd", "/c", str(batch)], cwd=build, check=True)
start = time.monotonic()
result = subprocess.run([str(build / "run_bounded.exe"), str(build / "watchdog_sleep.exe")],
                        cwd=build, capture_output=True, text=True, timeout=8, check=True)
elapsed = time.monotonic() - start
assert 2.8 <= elapsed < 7, elapsed
assert "Stopped child at the three-second limit" in result.stdout, result.stdout
print(result.stdout.strip())
print(f"watchdog verified: sleeping child terminated after {elapsed:.2f} seconds")
