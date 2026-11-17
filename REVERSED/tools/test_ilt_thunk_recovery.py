import pathlib
import re
import struct
import unittest


ROOT = pathlib.Path(__file__).resolve().parents[1]


def read_va(path: pathlib.Path, va: int, size: int) -> bytes:
    image = path.read_bytes()
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    section_count = struct.unpack_from("<H", image, pe_offset + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe_offset + 20)[0]
    optional = pe_offset + 24
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    rva = va - image_base
    section = optional + optional_size
    for index in range(section_count):
        header = section + index * 40
        virtual_size, virtual_address, raw_size, raw_offset = struct.unpack_from(
            "<IIII", image, header + 8
        )
        if virtual_address <= rva < virtual_address + max(virtual_size, raw_size):
            offset = raw_offset + rva - virtual_address
            return image[offset : offset + size]
    raise AssertionError(f"VA 0x{va:08X} is not inside a PE section")


def c_function_body(path: pathlib.Path, name: str) -> str:
    source = path.read_text(encoding="utf-8", errors="replace")
    match = re.search(rf"\b{re.escape(name)}\s*\([^;]*\)\s*\{{", source)
    if not match:
        raise AssertionError(f"missing definition for {name} in {path}")
    start = match.end()
    depth = 1
    for index in range(start, len(source)):
        if source[index] == "{":
            depth += 1
        elif source[index] == "}":
            depth -= 1
            if depth == 0:
                return re.sub(r"\s+", "", source[start:index])
    raise AssertionError(f"unterminated function {name} in {path}")


class ImportAddressThunkTests(unittest.TestCase):
    def test_original_ilt_entries_are_relative_tail_jumps(self):
        original = ROOT / "build" / "run" / "groove_original.exe"
        for thunk_va, target_va in ((0x43CB20, 0x545270), (0x43CB30, 0x545030)):
            instruction = read_va(original, thunk_va, 5)
            self.assertEqual(instruction[0], 0xE9)
            displacement = struct.unpack_from("<i", instruction, 1)[0]
            self.assertEqual(thunk_va + 5 + displacement, target_va)

    def test_recovered_thunks_forward_to_their_real_bodies(self):
        cases = (
            ("sub_43CB20", "sub_545270"),
            ("sub_43CB30", "sub_545030"),
        )
        for thunk, target in cases:
            with self.subTest(thunk=thunk):
                body = c_function_body(ROOT / "src_recovered" / f"{thunk}.c", thunk)
                self.assertRegex(body, rf"^{target}\(\);$")


if __name__ == "__main__":
    unittest.main()
