import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ASM_PATH = ROOT.parent / "Game" / "groove.exe.asm"
EXPORT_DIR = ROOT / "decompiled_ghidra_12_1_4_fixed"
RECOVERED_DIR = ROOT / "src_recovered"

CASES = {
    "sub_55A6D0": {"format": "555", "transparent": False, "mask": "7E0F81F", "channel": "0FC1F03E0"},
    "sub_55AF9A": {"format": "555", "transparent": True,  "mask": "7E0F81F", "channel": "0FC1F03E0"},
    "sub_55B874": {"format": "565", "transparent": False, "mask": "3E07C1F", "channel": "7C0F83E0"},
    "sub_55C13E": {"format": "565", "transparent": True,  "mask": "3E07C1F", "channel": "7C0F83E0"},
}


def asm_body(asm: str, name: str) -> str:
    match = re.search(rf"(?ms)^{name} proc near\s*(.*?)^{name} endp", asm)
    if not match:
        raise AssertionError(f"missing assembly body: {name}")
    return match.group(1)


def normalized_asm_instructions(body: str) -> list[str]:
    """Drop address-specific labels while retaining branch targets and opcodes."""
    lines = []
    labels = []
    for raw in body.splitlines():
        line = raw.strip().lower()
        if not line or line.startswith(";"):
            continue
        if line.endswith(":"):
            label = line[:-1]
            labels.append(label)
            lines.append(("label", label))
        else:
            lines.append(("instruction", re.sub(r"\s+", " ", line)))
    label_names = {label: f"label_{index}" for index, label in enumerate(labels)}
    result = []
    for kind, line in lines:
        if kind == "label":
            result.append(f"label {label_names[line]}")
        else:
            line = re.sub(r"loc_55[a-f0-9]+", lambda match: label_names[match.group(0)], line)
            line = re.sub(r"(?:7e0f81f|3e07c1f|0fc1f03e0|7c0f83e0)h", "COLOR_MASK", line)
            result.append(line)
    return result


def expected_recovered_export(name: str) -> str:
    text = (EXPORT_DIR / f"sub_00{name[4:]}.c").read_text(encoding="utf-8")
    text = text.replace(
        "/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */",
        f"/* {CASES[name]['format']} software rasterizer recovered from its own Ghidra export.\n"
        " * Original x86 stores 2^52-biased double coordinates and consumes their low dwords. */",
    )
    signature = f"void {name}(undefined4 param_1,undefined4 param_2,undefined4 param_3)\n\n{{"
    if text.count(signature) != 1:
        raise AssertionError(f"unexpected function signature: {name}")
    text = text.replace(signature, signature + "\n  union { double value; uint32_t words[2]; } screen_x, screen_y;", 1)
    for address, local in (("0057c518", "screen_x"), ("0057c520", "screen_y")):
        pattern = rf"  _DAT_{address} =\s*\(double\)(.*?);"
        text, count = re.subn(
            pattern,
            lambda match: f"  {local}.value = (double){match.group(1)};\n  DAT_{address} = (int){local}.words[0];",
            text,
            count=1,
            flags=re.S,
        )
        if count != 1:
            raise AssertionError(f"missing coordinate initialization: {name} {address}")
    text, x_count = re.subn(
        r"_DAT_0057c518 = \(double\)CONCAT44\(DAT_0057c518_4,DAT_0057c518 \+ DAT_0057d864\);",
        "DAT_0057c518 = DAT_0057c518 + DAT_0057d864;", text)
    text, y_count = re.subn(
        r"_DAT_0057c520 = \(double\)CONCAT44\(DAT_0057c520_4,iVar5\);",
        "DAT_0057c520 = iVar5;", text)
    if (x_count, y_count) != (4, 4):
        raise AssertionError(f"expected four scanline updates per axis: {name} {(x_count, y_count)}")
    text = text.replace(
        "  sub_559459();",
        "  sub_559459((int)param_1,(int)param_2,(int)param_3);")
    # Keep the exact Ghidra body branches and state updates while allowing only the
    # documented coordinate-storage correction and the format-specific header comment.
    return text


class RasterRecoveryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.asm = ASM_PATH.read_text(encoding="latin-1")

    def test_each_override_preserves_its_own_export_body(self):
        for name in CASES:
            with self.subTest(function=name):
                expected_recovered_export(name)
                expected = expected_recovered_export(name)
                actual = (RECOVERED_DIR / f"{name}.c").read_text(encoding="utf-8")
                # Ignore the descriptive comment, which is allowed to state the exact
                # transparency mode while all function code must match the transformed export.
                expected_code = re.sub(r"/\*.*?\*/", "", expected, flags=re.S)
                actual_code = re.sub(r"/\*.*?\*/", "", actual, flags=re.S)
                self.assertEqual(actual_code, expected_code)

    def test_abi_coordinate_storage_and_format_masks_match_assembly(self):
        for name, case in CASES.items():
            with self.subTest(function=name):
                body = asm_body(self.asm, name)
                c = (RECOVERED_DIR / f"{name}.c").read_text(encoding="utf-8")
                for arg in ("arg_0= dword ptr  8", "arg_4= dword ptr  0Ch", "arg_8= dword ptr  10h"):
                    self.assertIn(arg, body)
                self.assertRegex(body, r"(?m)^retn\s*$")  # caller cleans the 12-byte cdecl argument area
                self.assertIn("fild    dword_57D8A8", body)
                self.assertIn("fstp    dbl_57C518", body)
                self.assertIn("mov     edi, dword ptr dbl_57C518", body)
                self.assertIn("words[0]", c)
                self.assertIn("DAT_0057c518 = DAT_0057c518 + DAT_0057d864", c)
                self.assertIn("DAT_0057d8a8,int", (ROOT / "src_generated" / "type_overrides.csv").read_text())
                for address, value in (("57C730", "1.0"), ("57C734", "2.0"), ("57C738", "6.7553994e15")):
                    self.assertRegex(self.asm, rf"(?m)^flt_{address} dd {re.escape(value)}$")
                    self.assertIn(f"DAT_00{address.lower()},floatfile", (ROOT / "src_generated" / "type_overrides.csv").read_text())
                self.assertIn(f"and     eax, {case['mask']}h", body)
                self.assertIn(f"and     eax, {case['channel']}h", body)
                self.assertIn(f"0x{case['mask'].lower()}", c.lower())
                if case["transparent"]:
                    self.assertRegex(body, r"(?s)mov\s+ax, \[esi\+edx\*2\]\s+test\s+eax, eax\s+jz\s+short loc_")
                    self.assertIn("sVar1 != 0", c)
                else:
                    self.assertRegex(body, r"(?s)mov\s+ax, \[esi\+edx\*2\]\s+mov\s+\[ebp\+ecx\*2\+var_s0\], bx")
                    self.assertNotIn("sVar1 != 0", c)

    def test_assembly_paths_match_across_555_and_565_counterparts(self):
        # The two opaque variants have 531 instructions each; the two transparent
        # variants have 539. After replacing RGB masks and address labels, each pair
        # must have identical original control flow and state updates.
        for rgb555, rgb565 in (("sub_55A6D0", "sub_55B874"), ("sub_55AF9A", "sub_55C13E")):
            with self.subTest(pair=f"{rgb555}/{rgb565}"):
                self.assertEqual(
                    normalized_asm_instructions(asm_body(self.asm, rgb555)),
                    normalized_asm_instructions(asm_body(self.asm, rgb565)),
                )


if __name__ == "__main__":
    unittest.main()
