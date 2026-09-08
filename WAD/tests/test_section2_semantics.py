from __future__ import annotations

import unittest

from eng_wad.section2_semantics import section2_schema


class Section2SemanticTests(unittest.TestCase):
    def test_standard_coin_schema_is_exact_variant_only(self) -> None:
        schema = section2_schema("Coin", 3)
        self.assertIsNotNone(schema)
        self.assertEqual(len(schema or ()), 3)
        self.assertEqual((schema or ())[0].name, "Run interaction block")

    def test_different_coin_program_is_not_mislabeled(self) -> None:
        self.assertIsNone(section2_schema("Coin", 7))


if __name__ == "__main__":
    unittest.main()
