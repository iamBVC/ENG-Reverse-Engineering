"""Guard the register and frame contract of Groove's EH3 handler."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class SehHandler563E08Tests(unittest.TestCase):
    def test_eh3_handler_retains_the_original_stack_walk_and_register_contract(self):
        source = ROOT / "src_recovered" / "sub_563E08.c"
        self.assertTrue(source.is_file(), "missing exact recovery of the EH3 handler")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) undefined4 sub_563e08(int param_1, int param_2, undefined4 param_3)",
            "test dword ptr [eax + 4], 6",
            "mov dword ptr [ebx - 4], eax",
            "call dword ptr [edi + ecx*4 + 4]",
            "lea ebp, dword ptr [ebx + 10h]",
            "call __global_unwind2",
            "call __local_unwind2",
            "mov eax, dword ptr [edi + ecx*4 + 8]",
            "call sub_5632d2",
            "mov dword ptr [ebx + 0ch], eax",
            "mov eax, 0",
            "mov eax, 1",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("extraout_", text)


if __name__ == "__main__":
    unittest.main()
