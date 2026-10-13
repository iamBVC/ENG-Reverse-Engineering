"""Verify the real WinMain crash filter in an isolated failing child process."""
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parent.parent

def main():
    build = ROOT / "build/crash_probe"
    build.mkdir(parents=True, exist_ok=True)
    (build / "probe.c").write_text('''
void (*const groove_crt_initialisers[])(void) = {0};
const unsigned int groove_crt_initialiser_count = 0;
int sub_41D350(int instance, int previous, char *command)
{
    volatile int *missing = (volatile int *)0;
    *missing = 1;
    return 0;
}
''', encoding="ascii")
    candidates = [Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community"),
                  Path(r"F:\Programmi\Microsoft Visual Studio\2022\Community")]
    vcvars = next(p / "VC/Auxiliary/Build/vcvars32.bat" for p in candidates
                  if (p / "VC/Auxiliary/Build/vcvars32.bat").exists())
    batch = build / "build.bat"
    batch.write_text(f'@echo off\ncall "{vcvars}" >nul\n'
                     f'cl /nologo /TC /W3 /MT probe.c "{ROOT / "harness/exe_main.c"}" '
                     '/Fe:probe.exe /link /SUBSYSTEM:WINDOWS /MAP:probe.map\nexit /b %errorlevel%\n', encoding="ascii")
    compiled = subprocess.run(["cmd", "/c", str(batch)], cwd=build)
    if compiled.returncode:
        return compiled.returncode
    crashed = subprocess.run([str(build / "probe.exe")], cwd=build, timeout=15)
    log = (build / "groove_trace.log").read_text()
    if crashed.returncode == 0 or not re.search(r"\[crash\] code=c0000005 .*rva=[0-9a-f]+", log):
        print(log)
        raise SystemExit("crash probe did not terminate with the expected diagnostic")
    if "[crash] access=1 target=00000000" not in log or "[crash] eip=" not in log:
        raise SystemExit("crash probe did not record the write target and registers")
    if not re.search(r"\[crash\] fault-module=.*probe\.exe base=.* offset=[0-9a-f]+ thread=\d+", log):
        raise SystemExit("crash probe did not identify the faulting module and thread")
    print("crash logging: failing child recorded code, target, registers, faulting module and thread")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
