import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CALLERS = {
    "sub_54B590": ROOT / "decompiled_fresh" / "sub_54B590.c",
    "sub_54B810": ROOT / "src_recovered" / "sub_54B810.c",
    "sub_54B860": ROOT / "src_recovered" / "sub_54B860.c",
    "sub_54B8A0": ROOT / "src_recovered" / "sub_54B8A0.c",
}


class SetupResourceStackContractTests(unittest.TestCase):
    def test_original_callers_set_the_legacy_update_flag(self):
        for caller, path in CALLERS.items():
            with self.subTest(caller=caller):
                source = path.read_text(encoding="utf-8")
                call = source.index("sub_40E0C0(")
                preceding_code = source[:call].rsplit("\n", 20)[-20:]
                preceding_code = "\n".join(preceding_code)
                self.assertRegex(
                    preceding_code, r"\buStack_[0-9a-fA-F]+\s*=\s*1\s*;"
                )

    def test_recovered_function_models_stack_byte_as_named_value(self):
        source = (ROOT / "src_recovered" / "sub_40E0C0.c").read_text(
            encoding="utf-8"
        )
        self.assertNotRegex(source, r"\bin_stack_[0-9a-fA-F]+\b")
        self.assertRegex(source, r"void\s+sub_40E0C0\(int\s+param_1,\s*int\s+force_update\)")
        self.assertIn("force_update == 0", source)
        self.assertIn("if (force_update != 0)", source)

    def test_recovered_callers_pass_the_recovered_flag_explicitly(self):
        for caller in ("sub_54B810", "sub_54B860", "sub_54B8A0"):
            with self.subTest(caller=caller):
                source = (ROOT / "src_recovered" / f"{caller}.c").read_text(
                    encoding="utf-8"
                )
                self.assertIn("sub_40E0C0(PTR_DAT_005724dc + 0x18,1);", source)

        patches = (ROOT / "src_generated" / "bulk_patches.csv").read_text(
            encoding="utf-8"
        )
        self.assertIn(
            'sub_54B590,sub_40E0C0(PTR_DAT_005724dc + 0x18);,"sub_40E0C0(PTR_DAT_005724dc + 0x18,1);"',
            patches,
        )


if __name__ == "__main__":
    unittest.main()
