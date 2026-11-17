import csv
import re
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class MenuSceneClipperTests(unittest.TestCase):
    def test_frustum_clippers_are_compiled_as_game_code_not_link_stubs(self):
        with (ROOT / "src_generated" / "link_stubs.csv").open(
            encoding="utf-8", newline=""
        ) as stream:
            stub_names = {row["c_name"] for row in csv.DictReader(stream)}
        compiled = "\n".join(
            path.read_text(encoding="utf-8", errors="replace")
            for path in sorted((ROOT / "build" / "dll_chunks").glob("chunk_*.c"))
        )

        for name in ("sub_43A110", "sub_43A810"):
            with self.subTest(clipper=name):
                if name in stub_names:
                    self.fail(f"{name} is still listed as a generated no-op stub")
                self.assertRegex(
                    compiled,
                    rf"(?m)^[^\n]*\b{name}\s*\([^;]*\)\s*\n\s*\{{",
                    f"{name} must have a compiled body in the game DLL",
                )

    def test_near_and_side_plane_clipping_emit_bounded_intersections(self):
        sources = [ROOT / "src_recovered" / f"{name}.c"
                   for name in ("sub_43A110", "sub_43A810")]
        for source in sources:
            self.assertTrue(source.is_file(), f"recovered clipper missing: {source.name}")

        compiler = shutil.which("gcc")
        self.assertIsNotNone(compiler, "GCC is required for the standalone clipping check")
        with tempfile.TemporaryDirectory() as tmp:
            exe = Path(tmp) / "clipper_behavior_test.exe"
            subprocess.run(
                [compiler, "-std=c99", "-O0", "-DGROOVE_HOST_TEST", "-I", str(ROOT / "include"),
                 "-I", str(ROOT / "src_generated"),
                 str(ROOT / "tools" / "clipper_behavior_test.c"),
                 *(str(source) for source in sources), "-lm", "-o", str(exe)],
                check=True, cwd=ROOT, capture_output=True, text=True,
            )
            result = subprocess.run([str(exe)], check=True, capture_output=True, text=True)
        self.assertIn("clipper intersections and bounds verified", result.stdout)


if __name__ == "__main__":
    unittest.main()
