"""Preserve the caller-frame ABI of Groove's C++ exception helper."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ExceptionHelper567B34Tests(unittest.TestCase):
    def test_exception_helper_uses_the_inherited_frame_and_original_call_sequence(self):
        source = ROOT / "src_recovered" / "sub_567B34.c"
        self.assertTrue(source.is_file(), "the inherited-frame EH helper needs an exact recovery")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) void sub_567b34(void)",
            "mov eax, dword ptr [ebp - 28h]",
            "mov dword ptr [esi - 4], eax",
            "mov eax, dword ptr [ebp - 1ch]",
            "mov dword ptr [dat_006da420], eax",
            "mov eax, dword ptr [ebp - 20h]",
            "mov dword ptr [dat_006da424], eax",
            "cmp dword ptr [edi], 0e06d7363h",
            "cmp dword ptr [edi + 10h], 3",
            "cmp dword ptr [edi + 14h], 19930520h",
            "cmp dword ptr [ebp - 24h], ebx",
            "cmp dword ptr [ebp - 2ch], ebx",
            "call __abnormal_termination",
            "push eax",
            "push edi",
            "call sub_567d68",
            "pop ecx",
            "ret",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_", text)


if __name__ == "__main__":
    unittest.main()
