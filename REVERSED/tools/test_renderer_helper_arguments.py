import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class RendererHelperArgumentTests(unittest.TestCase):
    def test_renderer_helpers_keep_their_reconstructed_nine_argument_prototypes(self):
        header = (ROOT / "src_generated" / "ghidra_prototypes.h").read_text(encoding="utf-8")
        for helper in ("sub_43CD60", "sub_4C0EC0"):
            with self.subTest(helper=helper):
                match = re.search(rf"\bvoid\s+{helper}\(([^)]*)\);", header)
                self.assertIsNotNone(match, f"{helper} needs a checked prototype")
                self.assertEqual(len(match.group(1).split(",")), 9)

    def test_triangle_rasterizers_receive_original_nine_arguments(self):
        cases = {
            "src_recovered/sub_447770.c": "sub_43CD60",
            "src_recovered/sub_4CB870.c": "sub_4C0EC0",
        }
        expected_tail = ["pfVar2", "pfVar3", "pfVar14", "recovered_sort_flags"]

        for relative_path, helper in cases.items():
            with self.subTest(caller=relative_path):
                source = (ROOT / relative_path).read_text(encoding="utf-8")
                matches = re.findall(rf"\b{helper}\(([^;]*)\);", source)
                self.assertEqual(len(matches), 1, f"expected one {helper} call")
                args = [arg.strip() for arg in matches[0].split(",")]
                self.assertEqual(len(args), 9, f"{helper} must receive all nine arguments")
                self.assertEqual(args[:5], ["param_1", "param_2", "param_3", "param_4", "param_5"])
                self.assertEqual(args[5:], expected_tail)

    def test_software_rasterizers_receive_all_three_vertex_pointers(self):
        header = (ROOT / "src_generated" / "ghidra_prototypes.h").read_text(encoding="utf-8")
        expected_declarations = {
            "sub_558FF0": "void sub_558FF0(int in_EAX,int param_1,int param_2);",
            "sub_559459": "void sub_559459(int in_EAX,int param_1,int param_2);",
        }
        for helper, declaration in expected_declarations.items():
            with self.subTest(helper=helper):
                self.assertIn(declaration, header)

        patches = (ROOT / "src_generated" / "bulk_patches.csv").read_text(encoding="utf-8-sig")
        self.assertIn(
            'sub_560EA0,"sub_558FF0();","sub_558FF0((int)param_1,(int)param_2,(int)param_3);',
            patches,
        )

        callers = (
            "sub_55A6D0", "sub_55B874", "sub_55AF9A",
            "sub_55C13E", "sub_55CA18", "sub_55D316",
        )
        expected_call = "sub_559459((int)param_1,(int)param_2,(int)param_3);"
        for caller in callers:
            with self.subTest(caller=caller):
                source = (ROOT / "src_recovered" / f"{caller}.c").read_text(encoding="utf-8")
                self.assertEqual(source.count(expected_call), 1)

        bulk = (ROOT / "src_generated" / "bulk_all.c").read_text(encoding="utf-8")
        for helper in expected_declarations:
            with self.subTest(generated_helper=helper):
                marker = f"/* ==== {helper} ==== */"
                self.assertIn(marker, bulk, f"missing generated body for {helper}")
                body = bulk.split(marker, 1)[1].split("/* ==== ", 1)[0]
                self.assertIn(expected_declarations[helper][:-1], body)
                self.assertNotRegex(body, r"\bint\s+in_EAX\s*;")

        expected_calls = {
            "sub_558FF0": "sub_558FF0((int)param_1,(int)param_2,(int)param_3);",
            "sub_559459": expected_call,
        }
        for helper, call in expected_calls.items():
            with self.subTest(generated_call=helper):
                self.assertIn(call, bulk)


if __name__ == "__main__":
    unittest.main()
