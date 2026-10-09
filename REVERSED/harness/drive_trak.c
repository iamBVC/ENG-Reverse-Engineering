/* drive_trak.c - run the decompiled TRAK loader on a real chunk.
 *
 * `sub_5563F0` is the first loader function that can be driven with real game
 * data: it takes a chunk buffer that already holds the TRAK payload, relocates
 * every record's three sub-array pointers into a bump heap, rewrites the triangle
 * material references, and reports the header-array base.
 *
 * The driver reproduces the original caller (sub_42AAC0) faithfully:
 *   1. prime the primary bump heap (the driver supplies the arena, because
 *      sub_41EEA0 is not part of the decompiled subset),
 *   2. allocate the chunk from that heap and copy the file into it,
 *   3. call sub_5563F0(&cursor, record_count, &out) with cursor = chunk + 4,
 *   4. dump every offset and every material index it produced.
 *
 * tools/verify_trak.py prepares the input and checks the dump against an
 * independent computation from the same bytes, so this compares the decompiled
 * code against the format spec rather than against itself.
 *
 *   drive_trak.exe <trak_chunk.bin> <dump.txt>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef int  (__cdecl *fn_sub_5563F0)(void *cursor_slot, int record_count, void *out_records);
typedef void *(__cdecl *fn_alloc)(int);
typedef unsigned int *(__cdecl *fn_get_u32)(void);
typedef unsigned char *(__cdecl *fn_get_u8)(void);

static unsigned char arena[8 << 20];      /* the primary bump heap */

int main(int argc, char **argv)
{
    HMODULE mod;
    fn_sub_5563F0 sub_5563F0;
    fn_alloc sub_41EF00;
    fn_get_u32 get_cursor, get_remaining, get_materials;
    FILE *in;
    FILE *out;
    long size;
    unsigned char *chunk;
    unsigned char *file_data;
    unsigned int record_count;
    unsigned int cursor;
    unsigned int out_records = 0;
    unsigned int i;
    unsigned int heap_base;

    if (argc < 3) {
        printf("usage: drive_trak.exe <trak_chunk.bin> <dump.txt>\n");
        return 2;
    }
    mod = LoadLibraryA("build\\groove_ghidra.dll");
    if (!mod) {
        printf("cannot load the DLL (error %lu)\n", GetLastError());
        return 2;
    }
    sub_5563F0 = (fn_sub_5563F0)GetProcAddress(mod, "wh_sub_5563F0");
    sub_41EF00 = (fn_alloc)GetProcAddress(mod, "wh_sub_41EF00");
    get_cursor = (fn_get_u32)GetProcAddress(mod, "wh_get_00586584");
    get_remaining = (fn_get_u32)GetProcAddress(mod, "wh_get_00586588");
    get_materials = (fn_get_u32)GetProcAddress(mod, "wh_get_00581154");
    if (!sub_5563F0 || !sub_41EF00 || !get_cursor || !get_remaining || !get_materials) {
        printf("missing exports in the harness DLL\n");
        return 2;
    }

    in = fopen(argv[1], "rb");
    if (!in) {
        printf("cannot open %s\n", argv[1]);
        return 2;
    }
    fseek(in, 0, SEEK_END);
    size = ftell(in);
    fseek(in, 0, SEEK_SET);
    file_data = (unsigned char *)malloc((size_t)size);
    if (!file_data || fread(file_data, 1, (size_t)size, in) != (size_t)size) {
        printf("cannot read %s\n", argv[1]);
        return 2;
    }
    fclose(in);

    /* 1. prime the heap: the driver owns the arena, the DLL owns the cursor */
    *get_cursor() = (unsigned int)(size_t)arena;
    *get_remaining() = sizeof arena;

    /* 2. the chunk itself comes off the same heap, like sub_42AAC0 does */
    chunk = (unsigned char *)sub_41EF00((int)size);
    if (!chunk) {
        printf("the heap refused the %ld-byte chunk\n", size);
        return 2;
    }
    memcpy(chunk, file_data, (size_t)size);

    record_count = *(unsigned int *)chunk;
    cursor = (unsigned int)(size_t)(chunk + 4);

    /* 3. call it exactly like the loader does */
    sub_5563F0(&cursor, (int)record_count, &out_records);

    heap_base = (unsigned int)(size_t)arena;
    out = fopen(argv[2], "w");
    if (!out) {
        printf("cannot write %s\n", argv[2]);
        return 2;
    }
    fprintf(out, "# chunk=%s size=%ld record_count=%u\n", argv[1], size, record_count);
    fprintf(out, "# arena=%08X heap_base=%08X headers_off=%08X cursor_end=%08X materials=%08X\n",
            (unsigned)sizeof arena, heap_base, out_records - heap_base,
            cursor - heap_base, *get_materials());

    for (i = 0; i < record_count; i++) {
        unsigned char *rec = (unsigned char *)(size_t)out_records + i * 132;
        unsigned int vc  = *(unsigned short *)(rec + 0x6C);
        unsigned int tc  = *(unsigned short *)(rec + 0x6E);
        unsigned int g0  = *(unsigned short *)(rec + 0x78);
        unsigned int g1  = *(unsigned short *)(rec + 0x7A);
        unsigned int g2  = *(unsigned short *)(rec + 0x7C);
        unsigned int vp  = *(unsigned int *)(rec + 0x70);
        unsigned int tp  = *(unsigned int *)(rec + 0x74);
        unsigned int cp  = *(unsigned int *)(rec + 0x80);
        unsigned int j;

        fprintf(out, "REC %u vc=%u tc=%u coll=%u vtx_off=%08X tri_off=%08X col_off=%08X\n",
                i, vc, tc, g0 + g1 + g2,
                vp ? vp - heap_base : 0, tp ? tp - heap_base : 0, cp ? cp - heap_base : 0);

        /* every triangle's material index: the loader stored base + 20*index */
        for (j = 0; j < tc; j++) {
            unsigned int *slot = (unsigned int *)(size_t)(tp + j * 28 + 8);
            fprintf(out, "TRI %u %u idx=%u\n", i, j, (*slot - *get_materials()) / 20);
        }
    }
    fclose(out);
    printf("wrote %s (%u records)\n", argv[2], record_count);
    return 0;
}
