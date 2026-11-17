import csv
import unittest
from pathlib import Path
from tempfile import TemporaryDirectory

from audit_data_coverage import (
    DataEntry,
    classify_entries,
    initializer_ranges,
    parse_data_csv,
    table_ranges,
    run_audit,
)

ROOT = Path(__file__).resolve().parents[1]


class DataCoverageAuditTests(unittest.TestCase):
    def test_unreferenced_level_name_pointer_table_is_harvested(self):
        overrides = ROOT / "src_generated" / "type_overrides.csv"
        with overrides.open(encoding="utf-8", newline="") as stream:
            rows = {row["name"]: row["type"] for row in csv.DictReader(stream)}
        self.assertEqual(rows.get("PTR_s_La_giungla_di_notte_0057bc24"), "record:0x20:file")
        self.assertEqual(rows.get("DAT_0057a898"), "string:0x9")
        globals_source = (ROOT / "src_generated" / "ghidra_globals.c").read_text(encoding="utf-8")
        globals_header = (ROOT / "src_generated" / "ghidra_globals.h").read_text(encoding="utf-8")
        table_line = next(line for line in globals_source.splitlines()
                          if line.startswith("int PTR_s_La_giungla_di_notte_0057bc24_storage[8]"))
        for target in (
            "s_La_giungla_di_notte_0057a854",
            "s_Il_fiume_0057a868",
            "s_La_giungla_di_giorno_0057a874",
            "s_La_montagna_0057a88c",
            "DAT_0057a898",
            "s_Le_catacombe_0057a8a4",
            "s_Il_laboratorio_0057a8b4",
            "s_LivelloTest_0057a8c4",
        ):
            self.assertIn(f"(int)&{target}", table_line)
        self.assertNotRegex(table_line, r"0x0057a8(?:54|68|74|8c|98|a4|b4|c4)")
        self.assertIn("PTR_s_La_giungla_di_notte_0057bc24", globals_header)

        classified, _ = run_audit()
        represented = {entry.address for entry in classified["represented"]}
        self.assertTrue(set(range(0x0057BC24, 0x0057BC44, 4)).issubset(represented))

    def test_csv_parser_preserves_comma_in_symbol_names(self):
        entries = parse_data_csv(
            "name,address,size,datatype\n"
            '"s_hello,world_00401000",00401000,12,string\n'
            "s_legacy,00401020,4,pointer\n"
        )

        self.assertEqual(
            entries,
            [
                DataEntry("s_hello,world_00401000", 0x401000, 12, "string"),
                DataEntry("s_legacy", 0x401020, 4, "pointer"),
            ],
        )

    def test_classifies_represented_aliases_and_unresolved_rows_separately(self):
        entries = [
            DataEntry("DAT_00402000", 0x402000, 4, "undefined4"),
            DataEntry("PTR_alias_00402000", 0x402000, 4, "pointer"),
            DataEntry("DAT_00402010", 0x402010, 4, "undefined4"),
            DataEntry("DAT_00403000", 0x403000, 4, "undefined4"),
            DataEntry("DAT_00404000", 0x404000, 4, "undefined4"),
            DataEntry("DAT_00401020", 0x401020, 4, "undefined4"),
        ]

        result = classify_entries(
            entries,
            represented_names={"DAT_00402000"},
            represented_addresses=set(),
            storage_ranges=[(0x402000, 0x402020)],
            referenced_names={"DAT_00402000", "PTR_alias_00402000", "DAT_00403000"},
            code_ranges=[(0x401000, 0x402000)],
            image_ranges=[(0x401000, 0x405000)],
        )

        self.assertEqual(len(result["represented"]), 3)
        self.assertEqual(result["referenced_unrepresented"], [entries[3]])
        self.assertEqual(result["unreferenced_unrepresented"], [entries[4]])
        self.assertEqual(result["code_address"], [entries[5]])

    def test_table_range_parser_accepts_record_file_overrides(self):
        with TemporaryDirectory() as directory:
            path = Path(directory) / "overrides.csv"
            path.write_text(
                "name,type\nDAT_00573410,record:0x470:file\n",
                encoding="utf-8",
            )
            self.assertEqual(
                table_ranges(path, {"DAT_00573410_storage"}),
                [(0x573410, 0x573880)],
            )

    def test_string_initializer_extent_covers_interior_label_addresses(self):
        ranges = initializer_ranges(
            'const char product_name[] = {69,109,112,101,114,111,114,115,0}; '
            '/* 0x0056E31D */'
        )
        self.assertEqual(ranges, [(0x56E31D, 0x56E326)])


if __name__ == "__main__":
    unittest.main()
