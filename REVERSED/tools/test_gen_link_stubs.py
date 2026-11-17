import tempfile
import unittest
from pathlib import Path

import gen_link_stubs
from code_label_aliases import function_for_code_label


class GeneratedStubFilteringTests(unittest.TestCase):
    def test_address_alias_target_uses_canonical_function_name_case(self):
        self.assertEqual(function_for_code_label("FUN_0043cd60"), "sub_43CD60")

    def test_stale_previous_stubs_without_live_code_references_are_pruned(self):
        stale = gen_link_stubs.unreferenced_previous_stubs(
            {"_DirectDrawCreate", "_fopen", "_printf", "_old_helper"},
            {"_fopen"},
            ['DirectDrawCreate(0, 0, 0); printf("still used"); /* fopen("comment-only") */'],
        )
        self.assertEqual(stale, {"_old_helper"})

    def test_seh_chain_pseudoglobal_is_not_emitted_as_a_process_global(self):
        stale = gen_link_stubs.unreferenced_previous_stubs(
            {"_ExceptionList"}, set(), ["ExceptionList = 0;"])
        self.assertEqual(stale, {"_ExceptionList"})
        shim = (gen_link_stubs.ROOT / "include" / "ghidra_shim.h").read_text(
            encoding="utf-8")
        self.assertIn("((NT_TIB *)NtCurrentTeb())->ExceptionList", shim)
        generated = (gen_link_stubs.ROOT / "src_generated" / "link_stubs.c").read_text(
            encoding="utf-8")
        self.assertNotIn("void *ExceptionList;", generated)

    def test_current_bulk_function_definitions_supersede_previous_stubs(self):
        with tempfile.TemporaryDirectory() as tmp:
            chunk_dir = Path(tmp)
            (chunk_dir / "chunk_000.c").write_text(
                "/* ==== sub_56D64F ==== */\nvoid sub_56D64F(void) {}\n"
                "/* ==== sub_401000 ==== */\nint sub_401000(void) { return 1; }\n",
                encoding="utf-8",
            )

            defined = gen_link_stubs.compiled_game_functions(
                chunk_dir, chunk_dir / "missing-substitutions.txt",
                chunk_dir / "missing-crt-bodies.txt", chunk_dir / "missing-labels.c")

        self.assertEqual(defined, {"sub_56D64F", "sub_401000"})

    def test_shared_stub_filter_models_exe_crt_removal_and_harness_substitution(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            chunk_dir = root / "chunks"
            chunk_dir.mkdir()
            (chunk_dir / "chunk_000.c").write_text(
                "/* ==== sub_5626AD ==== */\nvoid sub_5626AD(void) {}\n"
                "/* ==== sub_415A90 ==== */\nint sub_415A90(void) { return 0; }\n",
                encoding="utf-8",
            )
            substituted = root / "substituted.txt"
            substituted.write_text("sub_415A90 # implemented by harness\n", encoding="utf-8")
            crt_bodies = root / "crt_bodies.txt"
            crt_bodies.write_text("sub_5626AD # intentionally omitted from exe\n", encoding="utf-8")

            defined = gen_link_stubs.compiled_game_functions(
                chunk_dir, substituted, crt_bodies, root / "missing-labels.c")

        self.assertEqual(defined, {"sub_415A90"})

    def test_recovered_code_label_source_is_not_generated_as_a_stub(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            labels = root / "code_labels.c"
            labels.write_text(
                "/* ==== LAB_00427fa0 ==== */\n"
                "__declspec(naked) void LAB_00427fa0(void) {}\n",
                encoding="utf-8",
            )

            defined = gen_link_stubs.compiled_game_functions(
                root / "no-chunks", root / "no-substitutions.txt",
                root / "no-crt-bodies.txt", labels)

        self.assertIn("LAB_00427fa0", defined)

    def test_code_label_at_compiled_function_entry_is_an_alias_not_a_stub(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            chunks = root / "chunks"
            chunks.mkdir()
            (chunks / "chunk_000.c").write_text(
                "/* ==== sub_409290 ==== */\nvoid sub_409290(void) {}\n"
                "void *handler = &LAB_00409290;\n",
                encoding="utf-8",
            )

            defined = gen_link_stubs.compiled_game_functions(
                chunks, root / "no-substitutions.txt", root / "no-crt-bodies.txt",
                root / "no-labels.c")

        self.assertIn("LAB_00409290", defined)

    def test_fun_address_symbol_at_compiled_function_entry_is_an_alias(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            chunks = root / "chunks"
            chunks.mkdir()
            (chunks / "chunk_000.c").write_text(
                "/* ==== sub_43CD60 ==== */\nvoid sub_43CD60(void) {}\n"
                "void *callback = &FUN_0043cd60;\n",
                encoding="utf-8",
            )

            defined = gen_link_stubs.compiled_game_functions(
                chunks, root / "no-substitutions.txt", root / "no-crt-bodies.txt",
                root / "no-labels.c")

        self.assertIn("FUN_0043cd60", defined)


class GeneratedFunctionAliasTests(unittest.TestCase):
    def test_bulk_header_aliases_labels_to_exact_compiled_function_entries(self):
        root = Path(gen_link_stubs.ROOT)
        header = (root / "src_generated" / "ghidra_prototypes.h").read_text(encoding="utf-8")
        self.assertIn("#define LAB_00409290 sub_409290", header)

    def test_link_stub_file_has_no_placeholder_for_function_entry_alias(self):
        root = Path(gen_link_stubs.ROOT)
        stubs = (root / "src_generated" / "link_stubs.c").read_text(encoding="utf-8")
        self.assertNotIn("void LAB_00409290()", stubs)

    def test_hand_label_shim_does_not_redefine_a_recovered_function_alias(self):
        root = Path(gen_link_stubs.ROOT)
        labels = (root / "harness" / "code_labels.c").read_text(encoding="utf-8")
        self.assertNotIn("LAB_004284d0(void)", labels)


if __name__ == "__main__":
    unittest.main()
