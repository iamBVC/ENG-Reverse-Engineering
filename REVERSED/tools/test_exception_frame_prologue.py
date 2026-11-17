"""Keep the MSVC x86 exception-frame prologue in its original register ABI."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ExceptionFramePrologueTests(unittest.TestCase):
    def test_sub_56d674_is_recovered_as_naked_register_thunk(self):
        source = ROOT / "src_recovered" / "sub_56D674.c"
        self.assertTrue(source.is_file(), "the original EH frame helper must override Ghidra C")
        text = source.read_text(encoding="utf-8").lower()
        for instruction in (
            "__declspec(naked)",
            "push -1",
            "push eax",
            "mov eax, dword ptr fs:[0]",
            "mov dword ptr fs:[0], esp",
            "mov dword ptr [esp + 0ch], ebp",
            "lea ebp, dword ptr [esp + 0ch]",
            "push eax",
            "ret",
        ):
            with self.subTest(instruction=instruction):
                self.assertIn(instruction, text)


if __name__ == "__main__":
    unittest.main()
