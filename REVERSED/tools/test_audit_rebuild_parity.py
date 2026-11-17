"""Focused tests for the provenance audit's classification boundaries."""

import unittest
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import audit_rebuild_parity
from audit_rebuild_parity import (LEGACY_CRT_REPLACEMENTS, address_of,
                                  body_mismatches, classify, classify_merged_fragment,
                                  generated_name)


class RebuildParityAuditTests(unittest.TestCase):
    def test_address_and_exception_label_mapping(self):
        self.assertEqual(address_of("0x0040FB87"), 0x40FB87)
        self.assertEqual(address_of("sub_41D2C0"), 0x41D2C0)
        self.assertIsNone(address_of("entry"))
        self.assertEqual(generated_name("Catch@0040fb87"), "Catch_0040fb87")

    def test_export_does_not_imply_exe_inclusion(self):
        self.assertEqual(classify(exported=True, selected=True, generated=True,
                                  compiled_input=False, stub=True, game_code=True),
                         "not_in_exe_compile_input")
        self.assertEqual(classify(exported=True, selected=True, generated=True,
                                  compiled_input=True, stub=True, game_code=True),
                         "compiled_input_with_stub")
        self.assertEqual(classify(exported=False, selected=False, generated=False,
                                  compiled_input=False, stub=False, game_code=True),
                         "no_ghidra_export")

    def test_known_legacy_crt_replacements_are_not_missing_game_code(self):
        self.assertEqual(classify(exported=True, selected=True, generated=True,
                                  compiled_input=False, stub=False, game_code=True,
                                  runtime_replacement=True),
                         "runtime_replacement")

    def test_exact_stack_probe_is_game_code_and_merged_fragment_requires_compiled_parent(self):
        self.assertNotIn("sub_562840", LEGACY_CRT_REPLACEMENTS)
        self.assertEqual(classify_merged_fragment(True), "covered_by_parent_body")
        self.assertEqual(classify_merged_fragment(False), "missing_parent_body")

    def test_exe_bodies_are_compared_with_full_generated_source(self):
        generated = {"game_a": "body A", "game_b": "body B", "omitted": "body C"}
        exe = {"game_a": "body A", "game_b": "body B changed"}
        self.assertEqual(body_mismatches(generated, exe), ["game_b"])

    def test_intentional_crt_replacements_are_not_reported_as_missing_game_bodies(self):
        self.assertTrue(hasattr(audit_rebuild_parity, "body_gap_report"))
        report = audit_rebuild_parity.body_gap_report(
            {"game_a", "sub_562AEE", "sub_562B75"},
            {"game_a"},
            {"sub_562AEE", "sub_562B75"},
        )
        self.assertEqual(report["unresolved_generated_bodies"], [])
        self.assertEqual(
            report["runtime_replacement_bodies"], ["sub_562AEE", "sub_562B75"]
        )
        self.assertEqual(report["missing_runtime_replacement_bodies"], [])
        self.assertEqual(report["unexpectedly_included_replacements"], [])

    def test_a_missing_unreplaced_game_body_remains_an_audit_failure(self):
        report = audit_rebuild_parity.body_gap_report(
            {"game_a", "game_b", "sub_562AEE"},
            {"game_a"},
            {"sub_562AEE"},
        )
        self.assertEqual(report["unresolved_generated_bodies"], ["game_b"])


if __name__ == "__main__":
    unittest.main()
