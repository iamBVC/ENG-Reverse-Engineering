import unittest
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from make_dll_source import substituted  # noqa: E402


class BulkBuildRegenerationTests(unittest.TestCase):
    def test_bulk_build_compiles_every_generated_function_before_linking(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        bulk = script.split(":build_bulk", 1)[1].split(":build_subset", 1)[0]

        self.assertIn(
            'python "%ROOT%\\tools\\compile_check.py" --all', bulk,
            "bulk build must compile all generated bodies, including functions flagged for manual review",
        )

    def test_all_function_build_keeps_the_exact_stack_probe_implementation(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        aliases = (ROOT / "harness" / "crt_aliases.c").read_text(encoding="utf-8")
        crt_bodies = (ROOT / "harness" / "crt_bodies.txt").read_text(encoding="utf-8")
        recovered = (ROOT / "src_recovered" / "sub_562840.c").read_text(encoding="utf-8")
        bulk = script.split(":build_bulk", 1)[1].split(":build_subset", 1)[0]
        self.assertIn("/DGROOVE_ALL_BODIES", bulk)
        self.assertNotIn("void sub_562840(void) { }", aliases)
        self.assertNotRegex(crt_bodies, r"(?m)^\s*sub_562840\b")
        self.assertNotIn("sub_562840", substituted())
        self.assertIn("test dword ptr [ecx], eax", recovered.lower())

    def test_bulk_build_regenerates_recovered_c_before_copying_chunks(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        bulk = script.split(":build_bulk", 1)[1].split(":build_subset", 1)[0]
        generation = bulk.find('python "%ROOT%\\tools\\make_bulk.py"')
        compile_check = bulk.find('python "%ROOT%\\tools\\compile_check.py"')
        chunk_copy = bulk.find('python "%ROOT%\\tools\\make_dll_source.py"')

        self.assertGreaterEqual(generation, 0, "bulk build must regenerate generated C from recovered sources")
        self.assertGreater(compile_check, generation, "chunk generation must follow source generation")
        self.assertGreater(chunk_copy, compile_check, "DLL chunks must be copied only after compile_check refreshes them")

    def test_bulk_build_refreshes_link_stubs_after_current_functions_are_compiled(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        bulk = script.split(":build_bulk", 1)[1].split(":build_subset", 1)[0]
        compile_check = bulk.find('python "%ROOT%\\tools\\compile_check.py" --all')
        stub_refresh = bulk.find('python "%ROOT%\\tools\\gen_link_stubs.py"')
        chunk_copy = bulk.find('python "%ROOT%\\tools\\make_dll_source.py"')

        self.assertGreaterEqual(stub_refresh, 0, "the current linked bodies must supersede stale placeholders")
        self.assertGreater(stub_refresh, compile_check, "stub pruning needs the freshly compiled function inventory")
        self.assertGreater(chunk_copy, stub_refresh, "DLL source staging must see the refreshed stub source")

    def test_bulk_build_stages_the_exe_used_by_the_visible_watchdog(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        link = script.find('/OUT:"%ROOT%\\build\\groove_rebuild.exe"')
        staged = script.find('%ROOT%\\build\\run\\groove_rebuild.exe')

        self.assertGreaterEqual(link, 0, "bulk build must link the rebuilt game executable")
        self.assertGreater(staged, link, "linked executable must be copied to the watchdog launch path")

    def test_bulk_exe_preserves_original_version_resource_for_app_compatibility(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        exe = script.split(":build_bulk", 1)[1].split(":skip_exe", 1)[0]
        resource = (ROOT / "harness" / "rebuild_version_info.rc").read_text(encoding="utf-8")

        compile_resource = exe.find('rc /nologo /fo"exe_obj\\rebuild_version_info.res"')
        link = exe.find('/OUT:"%ROOT%\\build\\groove_rebuild.exe"')
        linked_resource = exe.find('"exe_obj\\rebuild_version_info.res"', link)
        self.assertGreaterEqual(compile_resource, 0, "EXE build must compile original VERSIONINFO")
        self.assertGreater(link, compile_resource, "VERSIONINFO must be ready before linking")
        self.assertGreater(linked_resource, link, "EXE link must include the VERSIONINFO resource")
        for value in ("Argonaut", "Argonaut Croc2", "Croc2.exe", "1, 0, 0, 1"):
            with self.subTest(value=value):
                self.assertIn(value, resource)

    def test_bulk_build_removes_stale_chunk_objects_before_compiling(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        bulk = script.split(":build_bulk", 1)[1].split(":build_subset", 1)[0]
        cleanup = bulk.find("del /q chunk_*.obj")
        compile_chunks = bulk.find('"%ROOT%\\build\\dll_chunks\\chunk_*.c"')

        self.assertGreaterEqual(cleanup, 0, "old root-level bulk objects must be deleted")
        self.assertGreater(compile_chunks, cleanup,
                           "cleanup must happen before the new DLL chunk compilation")

    def test_bulk_exe_build_removes_stale_exe_objects_before_compiling(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        exe = script.split(":build_bulk", 1)[1].split(":skip_exe", 1)[0]
        cleanup = exe.find('del /q "exe_obj\\*.obj"')
        compile_chunks = exe.find('"%ROOT%\\build\\exe_chunks\\chunk_*.c"')

        self.assertGreaterEqual(cleanup, 0, "old EXE object files must be deleted")
        self.assertGreater(compile_chunks, cleanup,
                           "EXE cleanup must happen before the current chunk compilation")

    def test_recovered_code_label_is_compiled_into_both_bulk_images(self):
        script = (ROOT / "harness" / "build_dlls.bat").read_text(encoding="utf-8")
        bulk = script.split(":build_bulk", 1)[1].split(":build_subset", 1)[0]
        exe = bulk.split(":skip_exe", 1)[0]

        self.assertGreaterEqual(bulk.find('"%ROOT%\\harness\\code_labels.c"'), 0)
        for helper_object in ("audio_imports.obj", "x87_math_helpers.obj",
                              "recovered_crt_helpers.obj", "code_labels.obj"):
            with self.subTest(helper_object=helper_object):
                self.assertIn(helper_object, bulk)
        self.assertGreaterEqual(exe.find('"%ROOT%\\harness\\code_labels.c"'), 0)


if __name__ == "__main__":
    unittest.main()
