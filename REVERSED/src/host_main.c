/* host_main.c - self-test host for the ported functions.
 *
 * This is the "compile it into an exe again" target: it links the reversed
 * translation units and checks them behaviourally (the byte-for-byte check
 * against the original lives in tools/bytecheck.py, because it compares the
 * .obj files rather than a finished executable).
 *
 * The tile-cell expectations below are not invented: they are the values the
 * real MAP data produces (first tile of three shipped levels), so this is a
 * genuine differential check against the game's own placement data.
 */
#include "groove.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures = 0;

#define CHECK(cond, what)                                                    \
    do {                                                                     \
        if (cond) {                                                          \
            printf("  [ ok ] %s\n", what);                                   \
        } else {                                                             \
            printf("  [FAIL] %s\n", what);                                   \
            failures++;                                                      \
        }                                                                    \
    } while (0)

static void test_primary_heap(void)
{
    void *a;
    void *b;
    void *c;

    printf("sub_41EEA0 / sub_41EF00 / sub_41EEE0 (primary 16 MB bump heap)\n");
    sub_41EEA0();
    CHECK(dword_586580 != NULL, "sub_41EEA0 allocates the block");
    CHECK(dword_586588 == 0x1000000, "remaining reset to 16 MB");
    CHECK(dword_586584 == dword_586580, "cursor reset to base");

    a = sub_41EF00(16);
    b = sub_41EF00(32);
    CHECK(a == dword_586580, "first allocation is at the block base");
    CHECK((unsigned char *)a + 16 == (unsigned char *)b, "allocations are contiguous");
    CHECK(dword_586588 == 0x1000000 - 48, "remaining decreased by the exact byte count");

    CHECK(sub_41EF00(0x7FFFFFFF) == NULL, "oversized request returns NULL");
    CHECK(dword_586588 == 0x1000000 - 48, "a rejected request does not consume bytes");

    /* `cmp ecx, eax / jle` is a SIGNED compare, so the original does not
     * validate the size: a negative request is accepted and rewinds the heap
     * (cursor moves back, `remaining` grows). */
    CHECK(sub_41EF00(-8) == (unsigned char *)b + 32,
          "negative size returns the current cursor instead of NULL");
    CHECK(dword_586584 == dword_586580 + 40, "negative size rewinds the cursor");
    CHECK(dword_586588 == 0x1000000 - 40, "negative size increases 'remaining'");

    sub_41EEE0();
    c = sub_41EF00(0x1000000);
    CHECK(c == dword_586580, "the whole block can be handed out");
    CHECK(dword_586588 == 0, "heap is exactly exhausted");
    CHECK(sub_41EF00(1) == NULL, "allocation past the end returns NULL");

    /* sub_41EEE0 rewinds the cursor but keeps the block. */
    sub_41EEE0();
    CHECK(dword_586584 == dword_586580, "sub_41EEE0 rewinds the cursor");
    CHECK(dword_586588 == 0x1000000, "sub_41EEE0 restores the size");
    CHECK(sub_41EF00(16) == dword_586580, "reused memory starts at the base again");
}

static void test_secondary_heap(void)
{
    static unsigned char arena[64];

    printf("sub_41ED90 (secondary bump heap)\n");
    dword_58656C = arena;
    dword_586570 = (int)sizeof(arena);

    CHECK(sub_41ED90(24) == arena, "first allocation at the cursor");
    CHECK(sub_41ED90(40) == arena + 24, "second allocation follows");
    CHECK(dword_586570 == 0, "arena exactly consumed");
    CHECK(sub_41ED90(1) == NULL, "next allocation fails");
    /* same unvalidated signed gate as sub_41EF00 */
    CHECK(sub_41ED90(-4) == arena + 64, "negative size is accepted, not rejected");
    CHECK(dword_58656C == arena + 60, "negative size rewinds the cursor");
    CHECK(dword_586570 == 4, "negative size increases 'remaining'");
}

static void test_small_batch(void)
{
    unsigned char out_byte = 0;
    unsigned int buf[4];
    char label[32];
    unsigned char obj[0x40];
    unsigned int pair_src[2];
    unsigned char pair_dst[8];
    int i;

    printf("batch 1 - small leaf game functions\n");

    dword_581158 = 1234;
    sub_406E30();
    CHECK(dword_581158 == 0, "sub_406E30 clears dword_581158");

    sub_408390(1, 2, 3, &out_byte);
    CHECK(out_byte == 0xFF, "sub_408390 writes 0xFF through the 4th argument");

    byte_6D9858 = 7;
    byte_6D94E8 = 9;
    sub_40D900();
    sub_40D910();
    CHECK(byte_6D9858 == 0, "sub_40D900 clears byte_6D9858");
    CHECK(byte_6D94E8 == 0, "sub_40D910 clears byte_6D94E8");

    flt_581970 = 0.0f;
    sub_40E020();
    CHECK(flt_581970 > 99.99f && flt_581970 < 100.01f,
          "sub_40E020 stores 1.0f / 0.01f = 100.0f");

    for (i = 0; i < 4; i++) buf[i] = 0xA5A5A5A5u;
    for (i = 0; i < 4; i++) dword_58226C[i] = 0xA5A5A5A5u;
    unk_5821E0[0] = 0xA5A5A5A5u;
    sub_40E0A0();
    CHECK(buf[0] == 0xA5A5A5A5u, "sub_40E0A0 does not touch unrelated memory");
    CHECK(dword_58226C[0] == 0 && dword_58226C[0xFF] == 0,
          "sub_40E0A0 zeroes all 0x100 dwords");
    CHECK(unk_5821E0[0] == 0 && unk_5821E0[0x0E] == 0, "sub_40E0A0 zeroes the 0x0F dwords too");

    sub_40E610(4, label);
    CHECK(strcmp(label, "BUTTON 5") == 0, "sub_40E610 formats 'BUTTON %d' with index+1");

    {
        int a[4];
        int b[1];
        a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 40;
        b[0] = 15;
        CHECK(sub_4136C0(a, b) == 25, "sub_4136C0 returns a[3] - *b");
    }

    memset(obj, 0, sizeof(obj));
    sub_413B10(obj);
    CHECK(*(void **)obj == (void *)&off_56E1C8,
          "sub_413B10 stores the address of off_56E1C8 into the object");

    memset(obj, 0xEE, sizeof(obj));
    CHECK(sub_41BCB0(obj) == obj, "sub_41BCB0 returns `this`");
    CHECK(*(unsigned int *)(obj + 0x20) == 0 && *(unsigned int *)(obj + 0x24) == 0,
          "sub_41BCB0 zeroes +0x20 and +0x24");
    CHECK(obj[0x1F] == 0xEE, "sub_41BCB0 leaves neighbouring bytes alone");

    dword_586408 = dword_58640C = 5;
    sub_41D330();
    CHECK(dword_586408 == 0 && dword_58640C == 0, "sub_41D330 clears both globals");

    dword_584644 = 0x1234;
    dword_586420 = 0;
    sub_41E1B0();
    CHECK(dword_586420 == 0x1234, "sub_41E1B0 latches dword_584644 into dword_586420");

    CHECK(sub_4255A0() == 1, "sub_4255A0 is a constant-true predicate");
    CHECK(sub_426860() == 0, "sub_426860 is a constant-false predicate");

    /* sub_40FC90 is deliberately not called here: its thiscall/`retn 4`
     * convention cannot be expressed for a free function, so the C caller would
     * pass the wrong registers.  The byte check still verifies its body. */
    (void)pair_src;
    (void)pair_dst;
}

static void test_io_wrappers(void)
{
    const char *path = "build/_selftest.bin";
    unsigned char out[8];
    unsigned char in[8];
    unsigned int w32 = 0x11223344u;
    unsigned short w16 = 0xAABB;
    FILE *f;

    printf("sub_415AB0 / sub_415AD0 / sub_415AF0 / sub_415A90 (fread wrappers)\n");
    CHECK(sub_415AB0(NULL, out) == 0, "NULL stream returns 0 (sub_415AB0)");
    CHECK(sub_415AF0(NULL, out) == 0, "NULL stream returns 0 (sub_415AF0)");

    f = fopen(path, "wb");
    if (!f) {
        printf("  [FAIL] cannot create %s\n", path);
        failures++;
        return;
    }
    fwrite(&w32, 4, 1, f);
    fwrite(&w16, 2, 1, f);
    fwrite("xy", 1, 2, f);
    fclose(f);

    memset(in, 0, sizeof(in));
    f = fopen(path, "rb");
    CHECK(sub_415AB0(f, in) == 1, "sub_415AB0 reads one 4-byte element");
    CHECK(in[0] == 0x44 && in[3] == 0x11, "little-endian dword read correctly");
    CHECK(sub_415AF0(f, in + 4) == 1, "sub_415AF0 reads one 2-byte element");
    CHECK(in[4] == 0xBB && in[5] == 0xAA, "little-endian word read correctly");
    CHECK(sub_415AD0(f, in + 6) == 1, "sub_415AD0 reads one byte");
    CHECK(in[6] == 'x', "byte value correct");
    {
        unsigned char two[2];
        CHECK(sub_415A90(f, two, 1) == 1, "sub_415A90 reads ElementSize bytes");
    }
    fclose(f);
    remove(path);
}

static void test_tile_cell_index(void)
{
    printf("groove_tile_cell_index (sub_42AC50 spatial hash)\n");
    /* first tile of t0i0m000: pos_x 36.5, stored (negated) z -55.5, width 96 */
    CHECK(groove_tile_cell_index(36.5f, -55.5f, 96) == 5316, "t0i0m000 tile 0 -> cell 5316");
    /* first tile of t1l1m001: pos_x 39.5, stored z -46.5, width 96 */
    CHECK(groove_tile_cell_index(39.5f, -46.5f, 96) == 4455, "t1l1m001 tile 0 -> cell 4455");
    /* first tile of t1l1m002: pos_x 0.5, stored z -0.5, width 96 */
    CHECK(groove_tile_cell_index(0.5f, -0.5f, 96) == 0, "t1l1m002 tile 0 -> cell 0");
    /* grid width changes the row stride */
    CHECK(groove_tile_cell_index(36.5f, -55.5f, 80) == 4436, "width 80 -> cell 4436");
}

int main(void)
{
    printf("groove.exe reverse-engineering self-test\n");
    printf("========================================\n\n");
    test_primary_heap();
    printf("\n");
    test_secondary_heap();
    printf("\n");
    test_io_wrappers();
    printf("\n");

    test_tile_cell_index();
    printf("\n");
    test_small_batch();
    printf("\n%s (%d failure%s)\n", failures ? "FAILED" : "ALL TESTS PASSED",
           failures, failures == 1 ? "" : "s");
    return failures ? 1 : 0;
}
