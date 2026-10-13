"""Resolve every audio bridge entry against the actual shipped 32-bit DLL."""
import re
from pathlib import Path
from test_hardware_enumeration import main as build_and_run

ROOT = Path(__file__).resolve().parent.parent
bridge = (ROOT / "harness/audio_imports.c").read_text()
exports = re.findall(r'groove_audio_export\("([^"]+)"\)', bridge)
dll_directory = str(ROOT.parent / "Game").replace("\\", "\\\\")
checks = "\n".join(f'    if (!groove_audio_export("{name}")) return 1;' for name in exports)
source = bridge + f'''
int main(void)
{{
    if (!SetDllDirectoryA("{dll_directory}")) return 1;
{checks}
    puts("audio exports: {len(exports)} original DLL entry points resolved");
    return 0;
}}
'''
if __name__ == "__main__":
    raise SystemExit(build_and_run(source, "audio_exports_test", bulk=False))
