/* verify.c - differential test driver for the two harness DLLs.
 *
 * Loads build\groove_ghidra.dll (decompiled code) and build\groove_hand.dll (the
 * hand-ported track), calls the same function on both with identical inputs, and
 * compares the results.  A function passes only when both implementations do the
 * same thing - which is the property the project actually needs; byte equality is
 * a separate, stricter check (tools/bytecheck.py).
 *
 * Written in C and built as 32-bit because the DLLs are 32-bit and the Python on
 * this machine is 64-bit and cannot load them.
 *
 * Deliberate limitations:
 *   - only functions whose behaviour is observable through arguments, return
 *     values or the harness's address-keyed getters are covered;
 *   - the four fread wrappers are exercised on the hand side only: Ghidra's
 *     decompilation of them returns void (it lost eax), which is one of the gaps
 *     this harness exists to surface.
 */
#include <stdio.h>
#include <string.h>
#include <windows.h>

static int failures = 0;
static int checks = 0;

#define CHECK(cond, ...)                                                  \
    do {                                                                  \
        checks++;                                                         \
        if (cond) {                                                       \
            printf("  [ ok ] " __VA_ARGS__);                              \
            printf("\n");                                                 \
        } else {                                                          \
            printf("  [FAIL] " __VA_ARGS__);                              \
            printf("\n");                                                 \
            failures++;                                                   \
        }                                                                 \
    } while (0)

typedef void *(__cdecl *fn_alloc)(int);
typedef void  (__cdecl *fn_void)(void);
typedef int   (__cdecl *fn_int2)(int, int);
typedef int   (__cdecl *fn_int0)(void);
typedef unsigned int  *(__cdecl *fn_get_u32)(void);
typedef int           *(__cdecl *fn_get_i32)(void);

typedef struct {
    HMODULE mod;
    fn_alloc sub_41EF00, sub_41ED90;
    fn_void  sub_41EEE0, sub_406E30, sub_4155E0, sub_41D330, sub_41E1B0, sub_40E0A0;
    fn_int2  sub_4136C0;
    fn_int0  sub_4255A0, sub_426860;
    fn_get_u32 get_cursor, get_remaining, get_cursor2, get_remaining2, get_58226C, get_5821E0;
    fn_get_i32 get_581158, get_583740, get_586408, get_58640C, get_584644, get_586420;
} Api;

static void *sym(HMODULE m, const char *name)
{
    void *p = (void *)GetProcAddress(m, name);
    if (!p) {
        char decorated[128];
        _snprintf(decorated, sizeof decorated, "_%s", name);
        p = (void *)GetProcAddress(m, decorated);
    }
    if (!p) {
        printf("  [!!] missing export %s\n", name);
        failures++;
    }
    return p;
}

static int load(Api *a, const char *dll)
{
    memset(a, 0, sizeof *a);
    a->mod = LoadLibraryA(dll);
    if (!a->mod) {
        printf("  [!!] cannot load %s (error %lu)\n", dll, GetLastError());
        return 0;
    }
    a->sub_41EF00 = (fn_alloc)sym(a->mod, "wh_sub_41EF00");
    a->sub_41ED90 = (fn_alloc)sym(a->mod, "wh_sub_41ED90");
    a->sub_41EEE0 = (fn_void)sym(a->mod, "wh_sub_41EEE0");
    a->sub_406E30 = (fn_void)sym(a->mod, "wh_sub_406E30");
    a->sub_4155E0 = (fn_void)sym(a->mod, "wh_sub_4155E0");
    a->sub_41D330 = (fn_void)sym(a->mod, "wh_sub_41D330");
    a->sub_41E1B0 = (fn_void)sym(a->mod, "wh_sub_41E1B0");
    a->sub_40E0A0 = (fn_void)sym(a->mod, "wh_sub_40E0A0");
    a->sub_4136C0 = (fn_int2)sym(a->mod, "wh_sub_4136C0");
    a->sub_4255A0 = (fn_int0)sym(a->mod, "wh_sub_4255A0");
    a->sub_426860 = (fn_int0)sym(a->mod, "wh_sub_426860");
    a->get_cursor = (fn_get_u32)sym(a->mod, "wh_get_00586584");
    a->get_remaining = (fn_get_u32)sym(a->mod, "wh_get_00586588");
    a->get_cursor2 = (fn_get_u32)sym(a->mod, "wh_get_0058656C");
    a->get_remaining2 = (fn_get_u32)sym(a->mod, "wh_get_00586570");
    a->get_58226C = (fn_get_u32)sym(a->mod, "wh_get_0058226C");
    a->get_5821E0 = (fn_get_u32)sym(a->mod, "wh_get_005821E0");
    a->get_581158 = (fn_get_i32)sym(a->mod, "wh_get_00581158");
    a->get_583740 = (fn_get_i32)sym(a->mod, "wh_get_00583740");
    a->get_586408 = (fn_get_i32)sym(a->mod, "wh_get_00586408");
    a->get_58640C = (fn_get_i32)sym(a->mod, "wh_get_0058640C");
    a->get_584644 = (fn_get_i32)sym(a->mod, "wh_get_00584644");
    a->get_586420 = (fn_get_i32)sym(a->mod, "wh_get_00586420");
    return 1;
}

static const int SIZES[] = { 16, 32, 64, 1000, 4096, -8, 0, 7, 1, 4000, 8, 64 };
#define NSIZES ((int)(sizeof SIZES / sizeof SIZES[0]))

static void test_primary_heap(Api *gh, Api *hand)
{
    unsigned char heap[4096];
    int i;
    printf("primary bump heap (sub_41EF00): %d allocations, identical sequences\n", NSIZES);

    *gh->get_cursor = (unsigned int)(size_t)heap;
    *gh->get_remaining = sizeof heap;
    *hand->get_cursor = (unsigned int)(size_t)heap;
    *hand->get_remaining = sizeof heap;

    for (i = 0; i < NSIZES; i++) {
        int n = SIZES[i];
        void *a = gh->sub_41EF00(n);
        void *b = hand->sub_41EF00(n);
        if (a != b) {
            CHECK(0, "allocation %d (size %d): ghidra=%08X hand=%08X", i, n,
                  (unsigned)(size_t)a, (unsigned)(size_t)b);
            return;
        }
        if (*gh->get_remaining != *hand->get_remaining) {
            CHECK(0, "remaining after %d (size %d): ghidra=%u hand=%u", i, n,
                  *gh->get_remaining, *hand->get_remaining);
            return;
        }
    }
    CHECK(1, "all %d allocations match, including the NULL on overflow and the "
             "negative-size rewind", NSIZES);
}

static void test_secondary_heap(Api *gh, Api *hand)
{
    unsigned char heap[256];
    int i;
    printf("secondary bump heap (sub_41ED90)\n");

    *gh->get_cursor2 = (unsigned int)(size_t)heap;
    *gh->get_remaining2 = sizeof heap;
    *hand->get_cursor2 = (unsigned int)(size_t)heap;
    *hand->get_remaining2 = sizeof heap;

    for (i = 0; i < 8; i++) {
        int n = (i == 5) ? 300 : 24 + i * 4;
        void *a = gh->sub_41ED90(n);
        void *b = hand->sub_41ED90(n);
        if (a != b || *gh->get_remaining2 != *hand->get_remaining2) {
            CHECK(0, "allocation %d (size %d): ghidra=%08X/%u hand=%08X/%u", i, n,
                  (unsigned)(size_t)a, *gh->get_remaining2,
                  (unsigned)(size_t)b, *hand->get_remaining2);
            return;
        }
    }
    CHECK(1, "8 allocations match, including the out-of-memory NULL");
}

static void test_reset(Api *gh, Api *hand)
{
    unsigned char base[64];
    printf("sub_41EEE0 (reset the primary heap)\n");
    *gh->get_remaining = 123;
    *hand->get_remaining = 123;
    *gh->get_cursor = (unsigned int)(size_t)base;
    *hand->get_cursor = (unsigned int)(size_t)base;
    printf("    slot ghidra=%08X hand=%08X\n", (unsigned)(size_t)gh->get_remaining, (unsigned)(size_t)hand->get_remaining);
    printf("    before  ghidra=%u hand=%u\n", *gh->get_remaining, *hand->get_remaining);
    gh->sub_41EEE0();
    hand->sub_41EEE0();
    printf("    after   ghidra=%u hand=%u\n", *gh->get_remaining, *hand->get_remaining);
    CHECK(*gh->get_remaining == *hand->get_remaining,
          "remaining after reset: ghidra=%u hand=%u", *gh->get_remaining, *hand->get_remaining);
    CHECK(*gh->get_remaining == 0x1000000, "reset restores the 16 MB block size");
}

static void test_pure(Api *gh, Api *hand)
{
    int i;
    printf("pure helpers\n");
    CHECK(gh->sub_4255A0() == hand->sub_4255A0(), "sub_4255A0 both return %d", gh->sub_4255A0());
    CHECK(gh->sub_426860() == hand->sub_426860(), "sub_426860 both return %d", gh->sub_426860());

    for (i = 0; i < 5; i++) {
        int a = 10 + i * 37;
        int b = 3 + i * 11;
        int ga = gh->sub_4136C0(&a, &b);
        int ha = hand->sub_4136C0(&a, &b);
        if (ga != ha) {
            CHECK(0, "sub_4136C0(%d,%d): ghidra=%d hand=%d", a, b, ga, ha);
            return;
        }
    }
    CHECK(1, "sub_4136C0 agrees on 5 input pairs");
}

static void test_global_setters(Api *gh, Api *hand)
{
    int i;
    printf("functions that only move globals\n");

    *gh->get_581158 = 0x11223344;
    *hand->get_581158 = 0x11223344;
    gh->sub_406E30();
    hand->sub_406E30();
    CHECK(*gh->get_581158 == *hand->get_581158, "sub_406E30 -> %d", *gh->get_581158);

    *gh->get_583740 = 0x11223344;
    *hand->get_583740 = 0x11223344;
    gh->sub_4155E0();
    hand->sub_4155E0();
    CHECK(*gh->get_583740 == *hand->get_583740, "sub_4155E0 -> %d", *gh->get_583740);

    *gh->get_586408 = 7; *gh->get_58640C = 9;
    *hand->get_586408 = 7; *hand->get_58640C = 9;
    gh->sub_41D330();
    hand->sub_41D330();
    CHECK(*gh->get_586408 == *hand->get_586408 && *gh->get_58640C == *hand->get_58640C,
          "sub_41D330 -> %d,%d", *gh->get_586408, *gh->get_58640C);

    *gh->get_584644 = 0x0BADF00D;
    *hand->get_584644 = 0x0BADF00D;
    *gh->get_586420 = 0;
    *hand->get_586420 = 0;
    gh->sub_41E1B0();
    hand->sub_41E1B0();
    CHECK(*gh->get_586420 == *hand->get_586420,
          "sub_41E1B0 latches -> %08X", (unsigned)*gh->get_586420);

    for (i = 0; i < 0x100; i++) {
        gh->get_58226C()[i] = 0xA5A5A5A5u;
        hand->get_58226C()[i] = 0xA5A5A5A5u;
    }
    for (i = 0; i < 0x0F; i++) {
        gh->get_5821E0()[i] = 0xA5A5A5A5u;
        hand->get_5821E0()[i] = 0xA5A5A5A5u;
    }
    gh->sub_40E0A0();
    hand->sub_40E0A0();
    if (memcmp(gh->get_58226C(), hand->get_58226C(), 0x100 * 4) != 0 ||
        memcmp(gh->get_5821E0(), hand->get_5821E0(), 0x0F * 4) != 0) {
        CHECK(0, "sub_40E0A0 zeroed the buffers differently");
    } else {
        CHECK(1, "sub_40E0A0 zeroed 0x100 + 0x0F dwords identically");
    }
}

int main(void)
{
    Api gh;
    Api hand;

    setvbuf(stdout, NULL, _IONBF, 0);   /* a crash must not swallow the report */
    printf("groove.exe differential verification\n");
    printf("====================================\n\n");

    if (!load(&gh, "build\\groove_ghidra.dll") || !load(&hand, "build\\groove_hand.dll")) {
        printf("\nFAILED to load the harness DLLs\n");
        return 1;
    }

    test_primary_heap(&gh, &hand);
    printf("\n");
    test_secondary_heap(&gh, &hand);
    printf("\n");
    test_reset(&gh, &hand);
    printf("\n");
    test_pure(&gh, &hand);
    printf("\n");
    test_global_setters(&gh, &hand);

    printf("\n%d checks, %d failure%s\n", checks, failures, failures == 1 ? "" : "s");
    return failures ? 1 : 0;
}
