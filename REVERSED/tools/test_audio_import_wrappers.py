"""Check missing AAL wrappers against imports recovered from groove.exe."""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


class MissingAudioWrapperTests(unittest.TestCase):
    def test_allocate_voice_imports_forward_the_exact_stdcall_abi(self):
        source = (ROOT / "harness" / "audio_imports.c").read_text(encoding="utf-8")
        expected = {
            "_AAL_AllocateVoiceForHandle_8": (
                "_AAL_AllocateVoiceForHandle@8", 2),
            "_AAL_AllocateVoice_4": ("_AAL_AllocateVoice@4", 1),
        }
        for c_name, (export_name, argument_count) in expected.items():
            with self.subTest(c_name=c_name):
                match = re.search(
                    rf"int {c_name}\((.*?)\)\s*\{{(.*?)\n\}}",
                    source,
                    re.S,
                )
                self.assertIsNotNone(match, f"missing wrapper {c_name}")
                signature, body = match.groups()
                self.assertEqual(signature.count("UINT_PTR"), argument_count)
                self.assertIn(f'groove_audio_export("{export_name}")', body)
                forwarded = re.search(r"\)\s*\(([^)]*)\);", body)
                self.assertIsNotNone(forwarded)
                self.assertEqual(len(forwarded.group(1).split(",")), argument_count)

    def test_stub_generator_recognizes_audio_wrappers_as_real_definitions(self):
        import sys
        sys.path.insert(0, str(ROOT / "tools"))
        import gen_link_stubs

        for c_name in ("_AAL_AllocateVoiceForHandle_8", "_AAL_AllocateVoice_4"):
            self.assertIn(c_name, gen_link_stubs.REAL_CRT)


if __name__ == "__main__":
    unittest.main()
