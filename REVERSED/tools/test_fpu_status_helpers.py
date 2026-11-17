"""Preserve the original x87 status-word helper side effects."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class FpuStatusHelpersTests(unittest.TestCase):
    def test_status_read_and_clear_helpers_match_original_instruction_order(self):
        cases = {
            "sub_56CF8A.c": (
                "wait",
                "fnstsw word ptr [ebp - 2]",
                "movsx eax, word ptr [ebp - 2]",
                "leave",
                "ret",
            ),
            "sub_56CF98.c": (
                "fnstsw word ptr [ebp - 2]",
                "fnclex",
                "movsx eax, word ptr [ebp - 2]",
                "leave",
                "ret",
            ),
            "sub_56CFA7.c": (
                "int __cdecl sub_56cfa7(unsigned int new_value, unsigned int mask)",
                "fnstcw word ptr [ebp - 4]",
                "mov eax, dword ptr [ebp + 0ch]",
                "and eax, dword ptr [ebp + 8]",
                "not ecx",
                "and ecx, dword ptr [ebp - 4]",
                "or ecx, eax",
                "mov dword ptr [ebp + 0ch], ecx",
                "fldcw word ptr [ebp + 0ch]",
            ),
        }
        for filename, instructions in cases.items():
            with self.subTest(function=filename):
                source = ROOT / "src_recovered" / filename
                self.assertTrue(source.is_file(), "FPU status helper must be recovered")
                text = source.read_text(encoding="utf-8").lower()
                self.assertIn("__declspec(naked)", text)
                for instruction in instructions:
                    with self.subTest(instruction=instruction):
                        self.assertIn(instruction, text)


if __name__ == "__main__":
    unittest.main()
