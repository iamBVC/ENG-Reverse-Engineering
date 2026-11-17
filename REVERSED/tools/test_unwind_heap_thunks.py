"""Check the callback cleanup thunks keep their owner-frame argument offsets."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class UnwindHeapThunkTests(unittest.TestCase):
    def test_operator_delete_thunks_use_original_ebp_offsets(self):
        expected = {
            "8e0": "10h",
            "8eb": "10h",
            "740": "10h",
            "760": "14h",
            "780": "8",
            "78b": "8",
        }
        for address, offset in expected.items():
            with self.subTest(address=address):
                source = ROOT / "src_recovered" / f"Unwind_0056d{address}.c"
                self.assertTrue(source.is_file(), f"missing recovered funclet {source.name}")
                text = source.read_text(encoding="utf-8").lower()
                self.assertIn("__declspec(naked)", text)
                self.assertIn(f"[ebp + {offset}]", text)
                self.assertIn("call sub_562941", text)
                self.assertIn("pop ecx", text)
                self.assertIn("ret", text)


if __name__ == "__main__":
    unittest.main()
