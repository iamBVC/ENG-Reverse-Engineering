"""Exercise recovered menu-quad code against values derived from the original ASM."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parent.parent


class MenuTextQuadTest(unittest.TestCase):
    def test_vertex_layout_and_three_menu_calls(self):
        compiler = shutil.which("gcc")
        if compiler is None:
            self.skipTest("32-bit MinGW GCC is unavailable")

        source = r'''
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int undefined4;
int DAT_00583378 = 640;
int DAT_00583374 = 480;
int DAT_005f6ef8 = 0;
float DAT_00573d38 = 0.0f;
float DAT_00573d3c = 1.0f;
float DAT_00573d40 = 1.0f;
static unsigned char pool[4096];
static void *blocks[16];
static int sizes[16];
static int count;
static int used;

int sub_41ED90(int size) {
    if (count >= 16 || used + size > (int)sizeof(pool)) abort();
    blocks[count] = pool + used;
    sizes[count++] = size;
    used += size;
    return (int)(uintptr_t)blocks[count - 1];
}

#include "sub_424900.c"
#include "sub_418420.c"

static void expect_float(float actual, float expected, const char *label) {
    if (actual != expected) {
        fprintf(stderr, "%s: got %g, expected %g\n", label, actual, expected);
        exit(1);
    }
}

int main(void) {
    float *v;
    unsigned int *bits;
    int i;
    if (sub_418420() != 0 || count != 9) return 1;
    for (i = 0; i < 9; i += 3) {
        if (sizes[i] != 0x180 || sizes[i + 1] != 0x20 ||
            sizes[i + 2] != 0x20) return 2;
    }
    v = (float *)blocks[0];
    bits = (unsigned int *)blocks[0];
    expect_float(v[0], 218.0f, "first x0");
    expect_float(v[1], 240.0f, "first y0");
    expect_float(v[8], 405.0f, "first x1");
    expect_float(v[9], 200.0f, "first y1");
    expect_float(v[24], 401.0f, "first x3");
    expect_float(v[32], 407.0f, "first x4");
    expect_float(v[40], 404.0f, "first x5");
    if (bits[4] != 0x00B48C00 || bits[12] != 0x00FFD74A ||
        bits[28] != 0x00303080) return 3;
    expect_float(((float *)blocks[3])[40], 217.0f, "second x5");
    expect_float(((float *)blocks[6])[40], 310.0f, "third x5");
    if (DAT_005f6ef8 != (int)(uintptr_t)blocks[8]) return 4;
    return 0;
}
'''
        source = source.replace('"sub_424900.c"', f'"{(ROOT / "src_recovered/sub_424900.c").as_posix()}"')
        source = source.replace('"sub_418420.c"', f'"{(ROOT / "src_recovered/sub_418420.c").as_posix()}"')
        with tempfile.TemporaryDirectory() as temporary:
            source_path = Path(temporary) / "menu_quad.c"
            executable = Path(temporary) / "menu_quad.exe"
            source_path.write_text(source, encoding="utf-8")
            build = subprocess.run(
                [compiler, "-std=c99", "-O0", "-Wall", "-Wextra", "-Werror",
                 str(source_path), "-o", str(executable)],
                capture_output=True, text=True,
            )
            self.assertEqual(build.returncode, 0, build.stderr)
            run = subprocess.run([str(executable)], capture_output=True, text=True)
            self.assertEqual(run.returncode, 0, run.stderr)


if __name__ == "__main__":
    unittest.main()
