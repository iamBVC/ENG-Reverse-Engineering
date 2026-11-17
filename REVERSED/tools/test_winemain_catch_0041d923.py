"""Preserve WinMain's catch-frame cleanup and relocated epilogue target."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class WinMainCatchTests(unittest.TestCase):
    def test_catch_and_resume_epilogue_keep_original_frame_abi(self):
        source = ROOT / "src_recovered" / "Catch_0041d923.c"
        self.assertTrue(source.is_file(), "WinMain catch must replace unaff_EBP C")
        catch = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked)",
            "[ebp + 10h]",
            "[ebp - 28h]",
            "[ebp - 4]",
            "[ebp - 24h]",
            "call sub_426500",
            "offset groove_resume_winemain_epilogue",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, catch)

        labels = (ROOT / "harness" / "code_labels.c").read_text(encoding="utf-8").lower()
        for instruction in (
            "groove_resume_winemain_epilogue",
            "mov ecx, dword ptr [ebp - 0ch]",
            "mov dword ptr fs:[0], ecx",
            "pop edi",
            "pop esi",
            "pop ebx",
            "ret 10h",
        ):
            with self.subTest(epilogue=instruction):
                self.assertIn(instruction, labels)


if __name__ == "__main__":
    unittest.main()
