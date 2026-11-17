"""Preserve the original x87 stack-to-cdecl bridge in sub_563360."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class X87Bridge563360Tests(unittest.TestCase):
    def test_bridge_preserves_x87_order_and_stack_arguments(self):
        source = ROOT / "src_recovered" / "sub_563360.c"
        self.assertTrue(source.is_file(), "x87 bridge must replace pseudo-register C")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "sub esp, 10h",
            "fxch st(1)",
            "fstp qword ptr [esp]",
            "fst qword ptr [esp + 8]",
            "mov eax, dword ptr [esp + 0ch]",
            "call sub_563382",
            "add esp, 10h",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)


if __name__ == "__main__":
    unittest.main()
