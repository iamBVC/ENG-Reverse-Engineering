"""Behavioral tests for callable code-label bodies recovered from original bytes."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from test_hardware_enumeration import main as build_and_run  # noqa: E402


class MissingCallableRecoveryTests(unittest.TestCase):
    def test_decimal_tail_trimmer_matches_original_delimiter_and_exponent_rules(self):
        source = ROOT / "src_recovered" / "sub_5640F2.c"
        self.assertTrue(source.exists(), "missing recovered body for 0x005640F2")
        fixture = r'''
#include <stdio.h>
#include <string.h>
unsigned char DAT_0057ca14 = '.';
'''
        main = r'''
int main(void)
{
    char a[64] = "score.1200";
    char b[64] = "score.0000";
    char c[64] = "score.1200E+3";
    char d[64] = "score1200";
    char e[64] = "score.1200";
    sub_5640F2(a);
    sub_5640F2(b);
    sub_5640F2(c);
    sub_5640F2(d);
    DAT_0057ca14 = ',';
    sub_5640F2(e);
    if (strcmp(a, "score.12") || strcmp(b, "score") ||
        strcmp(c, "score.12E+3") || strcmp(d, "score1200") ||
        strcmp(e, "score.1200")) return 1;
    return 0;
}
'''
        body = source.read_text(encoding="utf-8")
        self.assertEqual(build_and_run(fixture + body + main,
                                       "decimal_tail_recovery_test", bulk=False), 0)

    def test_nonnegative_double_predicate_matches_x87_ordered_compare(self):
        source = ROOT / "src_recovered" / "sub_564140.c"
        self.assertTrue(source.exists(), "missing recovered body for 0x00564140")
        fixture = r'''
#include <math.h>
'''
        main = r'''
int main(void)
{
    double negative = -0.25;
    double zero = 0.0;
    double positive = 0.25;
    double nan_value = NAN;
    if (sub_564140(&negative) != 0) return 1;
    if (sub_564140(&zero) != 1) return 2;
    if (sub_564140(&positive) != 1) return 3;
    if (sub_564140(&nan_value) != 0) return 4;
    return 0;
}
'''
        body = source.read_text(encoding="utf-8")
        self.assertEqual(build_and_run(fixture + body + main,
                                       "nonnegative_predicate_recovery_test", bulk=False), 0)

    def test_static_list_destructor_thunks_empty_both_original_intrusive_lists(self):
        paths = [ROOT / "src_recovered" / "sub_40E070.c",
                 ROOT / "src_recovered" / "sub_40F4E0.c"]
        for source in paths:
            self.assertTrue(source.exists(), f"missing recovered body: {source.name}")
        fixture = r'''
#include <stdint.h>
#include <string.h>
struct list_storage { int before_root; int head[3]; };
static struct list_storage list_a, list_b;
#define DAT_00582260 (list_a.head)
#define DAT_00583410 (list_b.head)
static void initialize_list(struct list_storage *storage, int *first, int *second)
{
    int *head = storage->head;
    int *root_link = head - 1;
    int *sentinel = head + 1;
    head[0] = (int)(uintptr_t)first;
    first[0] = (int)(uintptr_t)root_link;
    first[1] = (int)(uintptr_t)second;
    second[0] = (int)(uintptr_t)first;
    second[1] = (int)(uintptr_t)sentinel;
}
'''
        main = r'''
int main(void)
{
    int a1[2], a2[2], b1[2], b2[2];
    initialize_list(&list_a, a1, a2);
    initialize_list(&list_b, b1, b2);
    sub_40E070();
    if ((int *)(uintptr_t)list_a.head[0] != list_a.head + 1) return 1;
    if (a1[0] || a1[1] || a2[0] || a2[1]) return 2;
    sub_40F4E0();
    if ((int *)(uintptr_t)list_b.head[0] != list_b.head + 1) return 3;
    if (b1[0] || b1[1] || b2[0] || b2[1]) return 4;
    return 0;
}
'''
        bodies = "\n".join(path.read_text(encoding="utf-8") for path in paths)
        self.assertEqual(build_and_run(fixture + bodies + main,
                                       "list_destructor_recovery_test", bulk=False), 0)


if __name__ == "__main__":
    unittest.main()
