"""Guard the inherited-frame std::length_error construction helpers."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class LengthErrorHelperRecoveryTests(unittest.TestCase):
    def test_length_error_constructor_preserves_original_frame_and_throw_sequence(self):
        source = ROOT / "src_recovered" / "sub_56D0A0.c"
        self.assertTrue(source.is_file(), "missing recovered string-too-long constructor")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) void sub_56d0a0(void)",
            "mov eax, offset sub_56d910",
            "call sub_56d674",
            "sub esp, 30h",
            "mov al, byte ptr [ebp - 0dh]",
            "lea ecx, dword ptr [ebp - 20h]",
            "call sub_56d3b4",
            "call sub_56d0fa",
            "mov dword ptr [ebp - 3ch], offset ptr_lab_0056ed48",
            "call __cxxthrowexception_8",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("unaff_", text)

    def test_logic_error_constructor_preserves_thiscall_stack_and_seh_epilogue(self):
        source = ROOT / "src_recovered" / "sub_56D0FA.c"
        self.assertTrue(source.is_file(), "missing recovered std::logic_error constructor")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) undefined4 * sub_56d0fa(int param_1)",
            "mov eax, offset sub_56d924",
            "call sub_56d674",
            "mov dword ptr [ebp - 14h], esi",
            "mov dword ptr [ebp - 10h], offset dat_0057f834",
            "call sub_56d5c8",
            "mov ebx, dword ptr [ebp + 8]",
            "call sub_414160",
            "mov dword ptr [esi], offset ptr_sub_56d1c5_0056ed68",
            "mov dword ptr fs:[0], ecx",
            "ret 4",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)
        self.assertNotIn("extraout_", text)
        self.assertNotIn("unaff_", text)

    def test_out_of_range_constructor_uses_its_own_throw_metadata(self):
        source = ROOT / "src_recovered" / "sub_56D2CC.c"
        self.assertTrue(source.is_file(), "missing recovered invalid-string-position path")
        text = source.read_text(encoding="utf-8").lower()
        for fragment in (
            "__declspec(naked) void sub_56d2cc(void)",
            "mov eax, offset sub_56d974",
            "mov esi, offset groove_string_invalid_position",
            "call sub_56d0fa",
            "push offset dat_0056f700",
            "mov dword ptr [ebp - 3ch], offset ptr_lab_0056ed78",
            "call __cxxthrowexception_8",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, text)

    def test_unwind_thunks_and_legacy_funcinfo_mappings_are_present(self):
        for filename, immediate in (("sub_56D910.c", "0056f5e8h"),
                                    ("sub_56D924.c", "0056f610h"),
                                    ("sub_56D974.c", "0056f710h")):
            thunk = (ROOT / "src_recovered" / filename).read_text(encoding="utf-8").lower()
            for fragment in ("__declspec(naked)", f"mov eax, {immediate}",
                             "jmp sub_562fa9"):
                with self.subTest(filename=filename, fragment=fragment):
                    self.assertIn(fragment, thunk)

        metadata = (ROOT / "harness" / "legacy_exception_metadata.h").read_text(
            encoding="utf-8"
        ).lower()
        for fragment in (
            "groove_unwind_56d0a0_state1",
            "groove_unwind_56d0fa_state1",
            "groove_unwind_56d2cc_state1",
            "0x0056f5e8",
            "0x0056f610",
            "0x0056f710",
        ):
            with self.subTest(fragment=fragment):
                self.assertIn(fragment, metadata)

        labels = (ROOT / "harness" / "code_labels.c").read_text(encoding="utf-8").lower()
        self.assertIn('groove_string_too_long[] = "string too long"', labels)
        self.assertIn('groove_string_invalid_position[] = "invalid string position"', labels)


if __name__ == "__main__":
    unittest.main()
