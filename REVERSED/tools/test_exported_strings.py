"""Check original string bytes and malformed legacy CSV names after generation."""
import re
from pathlib import Path
from pe_tools import PE

ROOT = Path(__file__).resolve().parent.parent
original = PE(ROOT.parent / "Game/groove.exe")
generated = (ROOT / "src_generated/ghidra_globals.c").read_text()
strings = dict((name, bytes(int(value) for value in values.split(",") if value))
               for name, values in re.findall(r"const char (\w+)\[\] = \{([0-9,]*)\};", generated))
assert strings and all(value.endswith(b"\0") for value in strings.values())
assert strings["DAT_00570348"] == b"Wads\0"
name = "s_Couldnt_load_wad_tribe__d__level_00571f84"
assert strings[name] == original.read(0x571F84, 53)
assert strings[name].count(b"%d") == 4
print(f"exported strings: {len(strings)} terminated strings; comma-containing format and Wads path verified")
