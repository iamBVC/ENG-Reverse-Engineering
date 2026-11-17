"""Keep the visible game launcher within the user's eight-second limit."""

from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT.parent / "run_rebuild_visible_8s.ps1"


class VisibleWatchdogTests(unittest.TestCase):
    def test_launcher_uses_eight_second_total_deadline(self):
        source = SCRIPT.read_text(encoding="utf-8")
        self.assertRegex(source, r"\$maximumRunMilliseconds\s*=\s*8000\b")
        self.assertRegex(
            source,
            r"\$maximumRunMilliseconds\s*-\s*\[int\]\$watch\.ElapsedMilliseconds",
        )
        self.assertNotIn("15000", source)


if __name__ == "__main__":
    unittest.main()
