"""Regression checks for the generated camera projection inputs."""

from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[1]
GENERATED = ROOT / "src_generated"


def extract_function(source: str, name: str) -> str:
    match = re.search(rf"(?m)^\s*(?:void|int|uint|undefined4)\s+{name}\s*\(", source)
    if match is None:
        raise AssertionError(f"{name} was not found in generated C")
    opening = source.find("{", match.start())
    depth = 0
    for offset in range(opening, len(source)):
        if source[offset] == "{":
            depth += 1
        elif source[offset] == "}":
            depth -= 1
            if depth == 0:
                return source[match.start():offset + 1]
    raise AssertionError(f"{name} has an unbalanced body")


class CameraProjectionStorageTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.source = (GENERATED / "clean_subset.c").read_text(encoding="utf-8")
        cls.globals_header = (GENERATED / "ghidra_globals.h").read_text(encoding="utf-8")

    def test_far_clip_is_stored_as_float_bits(self):
        body = extract_function(self.source, "sub_41E1C0")
        self.assertRegex(
            body,
            r"\(\(float\s*\*\)\(void\s*\*\)DAT_00581168\)\[7\]\s*=\s*DAT_0057f90c\s*;",
        )
        self.assertNotRegex(body, r"DAT_00581168\[7\]\s*=\s*DAT_0057f90c\s*;")

    def test_camera_near_range_global_keeps_its_full_width(self):
        self.assertRegex(self.globals_header, r"(?m)^extern\s+int\s+DAT_00586594\s*;")

    def test_camera_x87_slots_are_declared_as_floats(self):
        for name in (
            "DAT_0057f8f8",
            "DAT_0057f8fc",
            "DAT_0057f904",
            "DAT_0057f908",
            "DAT_0057f924",
            "DAT_0057f928",
            "DAT_0057f92c",
        ):
            with self.subTest(name=name):
                pattern = rf"(?m)^extern\s+float\s+{name}\s*;"
                self.assertIsNotNone(re.search(pattern, self.globals_header), f"{name} is not declared float")

    def test_field_of_view_is_stored_as_float_bits_before_camera_setup(self):
        body = extract_function(self.source, "sub_41E1C0")
        pattern = r"\(\(float\s*\*\)\(void\s*\*\)DAT_00581168\)\[8\]\s*=\s*_DAT_0057f908\s*\*"
        self.assertIsNotNone(re.search(pattern, body), "FOV must be written as float bits to camera slot 8")
        self.assertIsNone(re.search(r"DAT_00581168\[8\]\s*=", body), "integer camera slot write remains")

    def test_near_plane_bits_and_camera_vector_byte_offsets_match_x86(self):
        main_camera = extract_function(self.source, "sub_41E1C0")
        updated_camera = extract_function(self.source, "sub_41A480")
        self.assertTrue("*(float *)(void *)&DAT_0057f910" in main_camera, "main camera must reinterpret the near-plane bits")
        self.assertTrue("*(float *)(void *)&DAT_0057f910" in updated_camera, "camera update must reinterpret the near-plane bits")
        self.assertTrue("((unsigned char *)DAT_00581168 + 0x1c)" in updated_camera, "far-plane write must use byte offset 0x1c")
        self.assertTrue("((unsigned char *)DAT_00581168 + 0x18)" in updated_camera, "near-plane write must use byte offset 0x18")

    def test_default_camera_translation_copies_float_bits(self):
        body = extract_function(self.source, "sub_41E1C0")
        self.assertTrue("fVar1 = *(float *)(void *)&DAT_0057f91c;" in body, "camera translation X bits must be preserved")
        self.assertTrue("fVar2 = *(float *)(void *)&DAT_0057f920;" in body, "camera translation Y bits must be preserved")


if __name__ == "__main__":
    unittest.main()
