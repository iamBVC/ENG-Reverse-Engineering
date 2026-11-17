import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from compile_check import (compile_source_path, compiler_input_groups,
                           updated_failed_functions)  # noqa: E402


class CompileCheckSourceTests(unittest.TestCase):
    def test_default_checks_the_clean_subset_and_all_mode_selects_every_body(self):
        self.assertEqual(compile_source_path(False).name, "clean_subset.c")
        self.assertEqual(compile_source_path(True).name, "bulk_all.c")

    def test_compiler_inputs_are_split_to_stay_under_cmd_file_count_limits(self):
        chunks = [Path(f"chunk_{i:03}.c") for i in range(83)]

        groups = compiler_input_groups(chunks, max_files=30)

        self.assertEqual([len(group) for group in groups], [30, 30, 23])
        self.assertEqual([path for group in groups for path in group], chunks)

    def test_all_mode_clears_stale_failures_for_functions_it_recompiled_cleanly(self):
        previous = {"fixed_since_last_run", "still_fails", "not_in_this_source"}
        compiled = {"fixed_since_last_run", "still_fails"}
        bad = {"still_fails"}

        self.assertEqual(updated_failed_functions(previous, compiled, bad),
                         {"still_fails", "not_in_this_source"})

    def test_failed_worklist_normalizes_legacy_ghidra_exception_names(self):
        previous = {"Catch@0040fb87", "Unwind@0056d91c", "not_in_this_source"}
        compiled = {"Catch_0040fb87", "Unwind_0056d91c"}

        self.assertEqual(updated_failed_functions(previous, compiled, set()),
                         {"not_in_this_source"})


if __name__ == "__main__":
    unittest.main()
