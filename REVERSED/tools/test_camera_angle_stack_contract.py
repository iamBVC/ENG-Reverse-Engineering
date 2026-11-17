import unittest
from pathlib import Path


SOURCE = Path(__file__).resolve().parents[1] / "src_recovered" / "sub_41A920.c"


class CameraAngleStackContractTests(unittest.TestCase):
    def test_camera_angles_are_computed_without_x87_stack_pseudo_calls(self):
        source = SOURCE.read_text(encoding="utf-8")
        body = source.split("int sub_41A920(", 1)[1]
        body = body.split("/* ====", 1)[0]

        self.assertNotRegex(body, r"\b__ftol\s*\(\s*\)")
        self.assertNotRegex(body, r"(?m)^\s*fpatan\s*\(")
        self.assertIn("sqrt(", body)
        self.assertIn("atan2(", body)
        self.assertIn("-(double)DAT_0056e078", body)
        self.assertIn("(double)DAT_0056e078", body)
        self.assertIn("0x180", body)
        self.assertIn("0x10", body)
        helper = source.split("static int groove_camera_fistp(", 1)[1]
        helper = helper.split("/* sub_41A920", 1)[0]
        self.assertIn("9223372036854775808.0", helper)
        self.assertIn("(uint32_t)(uint64_t)converted", helper)
        self.assertIn("return 0", helper)


if __name__ == "__main__":
    unittest.main()
