"""Preserve Groove's x86 stack-probe helper ABI and page-touch sequence."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class StackProbe562840Tests(unittest.TestCase):
    def test_stack_probe_uses_the_original_eax_and_return_address_contract(self):
        source = ROOT / "src_recovered" / "sub_562840.c"
        self.assertTrue(source.is_file(), "stack probe must replace the lost-register pseudo-C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) void sub_562840(void)",
            "push ecx",
            "cmp eax, 1000h",
            "lea ecx, [esp + 8]",
            "sub ecx, 1000h",
            "sub eax, 1000h",
            "test dword ptr [ecx], eax",
            "sub ecx, eax",
            "mov eax, esp",
            "mov esp, ecx",
            "mov ecx, dword ptr [eax]",
            "mov eax, dword ptr [eax + 4]",
            "push eax",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)

    def test_stack_probe_is_not_replaced_by_the_previous_crt_noop(self):
        crt_aliases = (ROOT / "harness" / "crt_aliases.c").read_text(encoding="utf-8")
        crt_bodies = (ROOT / "harness" / "crt_bodies.txt").read_text(encoding="utf-8")
        self.assertNotIn("void sub_562840(void) { }", crt_aliases)
        self.assertNotRegex(crt_bodies, r"(?m)^\s*sub_562840\b")


if __name__ == "__main__":
    unittest.main()
