import csv
import importlib.util
import tempfile
import unittest
from pathlib import Path


TOOL = Path(__file__).with_name("audit_function_coverage.py")
SPEC = importlib.util.spec_from_file_location("audit_function_coverage", TOOL)
AUDIT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(AUDIT)


class FunctionCoverageTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        for folder in ("src", "src_recovered", "src_generated", "harness", "decompiled"):
            (self.root / folder).mkdir()

        rows = [
            ("sub_401000", "00401000", "90", "undefined sub_401000()"),
            ("sub_401100", "00401100", "90", "undefined sub_401100()"),
            ("sub_401200", "00401200", "5", "undefined sub_401200()"),
            ("sub_401300", "00401300", "20", "undefined sub_401300()"),
            ("sub_401400", "00401400", "3", "undefined sub_401400()"),
            ("sub_401500", "00401500", "8", "undefined sub_401500()"),
            ("thunk_sub_401600", "00401600", "5", "undefined thunk_sub_401600()"),
            ("_DirectDrawCreate", "EXTERNAL:00000001", "0", "undefined _DirectDrawCreate()"),
            ("FUN_00401700", "00401700", "12", "undefined FUN_00401700()"),
            ("sub_401800", "00401900", "12", "undefined sub_401800()"),
            ("sub_401900", "00401800", "12", "undefined sub_401900()"),
            ("Catch@00401810", "00401810", "18", "undefined Catch@00401810()"),
            ("sub_401A00", "00401A00", "128", "undefined sub_401A00()"),
            ("caseD_401A20", "00401A20", "12", "undefined caseD_401A20()"),
            ("DirectInputCreateA", "00401A40", "6", "undefined DirectInputCreateA()"),
            ("__nh_malloc", "00562B13", "44", "undefined __nh_malloc()"),
            ("__NLG_Notify1", "005632C9", "9", "undefined __NLG_Notify1()"),
            ("__freebuf", "0056679F", "43", "undefined __freebuf()"),
            ("__CxxThrowException@8", "0056331B", "58", "undefined __CxxThrowException@8()"),
            ("__CallSettingFrame@12", "00567E00", "76", "undefined __CallSettingFrame@12()"),
            ("sub_401B00", "00401B00", "64", "undefined sub_401B00()"),
        ]
        self.manifest = self.root / "_functions.csv"
        with self.manifest.open("w", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(("name", "address", "size", "signature"))
            writer.writerows(rows)

        self._write("src_recovered/sub_401000.c", "void sub_401000(void) { recovered(); }\n")
        self._write("src_generated/clean_subset.c", "/* ==== sub_401100 ==== */\nvoid sub_401100(void) { generated(); }\n")
        self._write(
            "src_generated/bulk_all.c",
            "void sub_401100(void) { generated(); }\n"
            "void sub_401A00(void) { parent(); }\n"
            "void sub_401B00(void) { generated_body(); }\n",
        )
        self._write("src_generated/chunks/chunk_000.c", "void sub_401100(void) { generated(); }\n")
        self._write("harness/wrappers_bulk.c", "void wh_sub_401B00(void) { sub_401B00(); }\n")
        self._write("src_generated/link_stubs.c", "void sub_401200(void) { /* generated unresolved stub */ }\n")
        self._write("src/sub_401300.c", "void sub_401300(void) { first(); }\n")
        self._write("src_recovered/sub_401300.c", "void sub_401300(void) { second(); }\n")
        self._write("decompiled/sub_401500.c", "void sub_401500(void) { decompiled_only(); }\n")
        self._write("decompiled/caseD_401A20.c", "void caseD_401A20(void) { fragment(); }\n")
        self._write("decompiled/thunk_sub_401600.c", "void thunk_sub_401600(void) { jump(); }\n")
        self._write("decompiled/rea/thunk_sub_401600.c", "void FUN_00401600(void) { fallback(); }\n")
        self._write("src_recovered/sub_401700.c", "void sub_401700(void) { address_alias(); }\n")
        self._write("src_recovered/address_mismatch.c", "void sub_401800(void) { address_first(); }\n")
        self._write("src/prototypes.h", "void sub_401400(void);\n")
        with (self.root / "_index.csv").open("w", newline="") as stream:
            writer = csv.writer(stream)
            writer.writerow(("name", "address", "size", "status"))
            writer.writerows((row[0], row[1], row[2], "fail" if row[0] == "thunk_sub_401600" else "ok")
                             for row in rows)

    def tearDown(self):
        self.temp.cleanup()

    def _write(self, relative, content):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(content, encoding="utf-8")

    def test_assigns_each_function_one_explicit_coverage_class(self):
        rows = AUDIT.audit(self.manifest, self.root)
        by_name = {row["name"]: row for row in rows}

        self.assertEqual(len(rows), 21)
        self.assertEqual(by_name["sub_401000"]["source_status"], "implemented")
        self.assertEqual(by_name["sub_401100"]["source_status"], "implemented")
        self.assertEqual(by_name["sub_401200"]["source_status"], "link_stub")
        self.assertEqual(by_name["sub_401300"]["source_status"], "duplicate")
        self.assertEqual(by_name["sub_401400"]["source_status"], "missing")
        self.assertEqual(by_name["sub_401500"]["source_status"], "decompiled_only")
        self.assertEqual(by_name["thunk_sub_401600"]["source_status"], "thunk_decompiled_only")
        self.assertEqual(by_name["_DirectDrawCreate"]["source_status"], "external")
        self.assertEqual(by_name["FUN_00401700"]["source_status"], "implemented")
        self.assertEqual(by_name["sub_401900"]["source_status"], "implemented")
        self.assertEqual(by_name["sub_401800"]["source_status"], "missing")
        self.assertEqual(by_name["Catch@00401810"]["obligation_class"], "compiler_eh_artifact")
        self.assertEqual(by_name["caseD_401A20"]["source_status"], "overlapping_fragment")
        self.assertEqual(by_name["caseD_401A20"]["overlapping_functions"], "sub_401A00")
        self.assertEqual(by_name["DirectInputCreateA"]["source_status"], "import_thunk")
        self.assertEqual(by_name["DirectInputCreateA"]["import_module"], "DINPUT.dll")
        self.assertEqual(by_name["thunk_sub_401600"]["pseudocode_source"], "rea_fallback")
        self.assertEqual(by_name["__nh_malloc"]["source_status"], "runtime_internal")
        self.assertIn("excluded CRT allocation", by_name["__nh_malloc"]["runtime_provider"])
        self.assertEqual(by_name["__NLG_Notify1"]["source_status"], "runtime_replacement")
        self.assertEqual(by_name["__NLG_Notify1"]["runtime_provider"],
                         "harness/recovered_crt_helpers.c: groove_nlg_notify1")
        self.assertEqual(by_name["__freebuf"]["source_status"], "runtime_internal")
        self.assertIn("modern fclose", by_name["__freebuf"]["runtime_provider"])
        self.assertEqual(by_name["__CxxThrowException@8"]["source_status"], "runtime_replacement")
        self.assertEqual(by_name["__CallSettingFrame@12"]["source_status"], "runtime_replacement")
        self.assertEqual(by_name["sub_401B00"]["source_status"], "implemented")

    def test_ignores_prototypes_and_comments_as_source_bodies(self):
        self._write("src/prototypes.h", "void sub_401400(void);\n/* void sub_401400(void) { fake(); } */\n")
        rows = AUDIT.audit(self.manifest, self.root)
        by_name = {row["name"]: row for row in rows}
        self.assertEqual(by_name["sub_401400"]["source_status"], "missing")

    def test_matches_sanitized_c_identifier_for_eh_artifact(self):
        self._write("src_generated/bulk_all.c", "void Catch_00401810(void) { cleanup(); }\n")
        rows = AUDIT.audit(self.manifest, self.root)
        by_name = {row["name"]: row for row in rows}
        self.assertEqual(by_name["Catch@00401810"]["source_status"], "implemented")


if __name__ == "__main__":
    unittest.main()
