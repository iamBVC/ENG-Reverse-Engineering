"""Keep the game's top-level exception filter in the rebuilt startup path."""

import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent


class GameExceptionFilterStartupTests(unittest.TestCase):
    def test_original_filter_is_compiled_and_chains_to_diagnostic_handler(self):
        excluded = {
            line.split("#", 1)[0].strip()
            for line in (ROOT / "harness" / "crt_bodies.txt").read_text(
                encoding="utf-8").splitlines()
        }
        self.assertNotIn("sub_567FCA", excluded)

        main = (ROOT / "harness" / "exe_main.c").read_text(encoding="utf-8")
        diagnostic = main.index("SetUnhandledExceptionFilter(report_unhandled_exception);")
        game_filter = main.index("sub_567FCA();")
        initializers = main.index("groove_crt_initialisers[i]();")
        self.assertLess(diagnostic, game_filter)
        self.assertLess(game_filter, initializers)

        source = (ROOT / "decompiled_ghidra_12_1_4_fixed" /
                  "sub_00567FCA.c").read_text(encoding="utf-8")
        self.assertIn("SetUnhandledExceptionFilter(sub_567F84)", source)


if __name__ == "__main__":
    unittest.main()
