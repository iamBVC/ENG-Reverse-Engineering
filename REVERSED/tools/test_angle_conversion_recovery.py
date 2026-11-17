"""Guard the recovered x87 angle scaling path in sub_403020."""

import csv
from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parent.parent


class AngleConversionRecoveryTests(unittest.TestCase):
    def test_body_patch_preserves_fpatan_scale_and_truncation(self):
        with (ROOT / "src_generated" / "bulk_patches.csv").open(
            encoding="utf-8", newline=""
        ) as stream:
            patches = list(csv.DictReader(stream))
        row = next(
            patch for patch in patches
            if patch["function"] == "sub_403020"
            and "fpatan((float10)" in patch["find"]
        )
        self.assertIn("groove_angle_to_game_units", row["replace"])
        self.assertIn("DAT_0056e068", row["replace"])
        self.assertNotIn("__ftol()", row["replace"])

    def test_angle_scale_is_recovered_from_original_float(self):
        with (ROOT / "src_generated" / "type_overrides.csv").open(
            encoding="utf-8", newline=""
        ) as stream:
            overrides = {row["name"]: row["type"] for row in csv.DictReader(stream)}
        self.assertEqual(overrides.get("DAT_0056e068"), "floatfile")

    def test_x87_helper_matches_original_operation_order(self):
        helper = (ROOT / "harness" / "x87_math_helpers.c").read_text(
            encoding="utf-8"
        )
        self.assertIn(
            "int groove_angle_to_game_units(int delta_x, int delta_y, float scale)", helper
        )
        for instruction in (
            "fild dword ptr [delta_x]",
            "fild dword ptr [delta_y]",
            "fpatan",
            "fmul dword ptr [scale]",
            "fistp qword ptr",
            "fldcw",
        ):
            self.assertIn(instruction, helper)

    def test_regenerated_sub_403020_uses_scaled_helper(self):
        generated = "\n".join(
            path.read_text(encoding="utf-8")
            for path in sorted((ROOT / "src_generated" / "chunks").glob("chunk_*.c"))
        )
        start = generated.index("/* ==== sub_403020 ====")
        end = generated.find("/* ==== ", start + 1)
        function = generated[start:end]
        self.assertIn("groove_angle_to_game_units", function)
        self.assertIn("DAT_0056e068", function)


if __name__ == "__main__":
    unittest.main()
