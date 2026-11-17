"""Verify the exception cleanup funclets use the original owner-frame slots."""

from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class ExceptionDestructorFuncletTests(unittest.TestCase):
    def test_destructor_funclets_load_this_from_ebp_and_tail_jump(self):
        expected = {"91c": "14h", "930": "10h", "944": "10h",
                    "958": "10h", "980": "10h"}
        for address, offset in expected.items():
            with self.subTest(address=address):
                source = ROOT / "src_recovered" / f"Unwind_0056d{address}.c"
                self.assertTrue(source.is_file(), f"missing recovered funclet {source.name}")
                text = source.read_text(encoding="utf-8").lower()
                self.assertIn("__declspec(naked)", text)
                self.assertIn(f"[ebp - {offset}]", text)
                self.assertIn("jmp sub_56d64f", text)


if __name__ == "__main__":
    unittest.main()
