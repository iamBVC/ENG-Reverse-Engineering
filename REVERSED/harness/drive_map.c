/* drive_map.c - run the decompiled MAP loader (`sub_42AC50`) on a real chunk.
 *
 * Reproduces what the game does before calling the loader:
 *   1. prime the primary bump heap (the driver owns the arena),
 *   2. load the TRAK chunk first, because the loader reads vertex counts and the
 *      vertex-colour blocks through the relocated TRAK header table,
 *   3. set the WFPC flags (they gate the optional-20 table and the final dword)
 *      and clear the greyscale switch, so the colour path stays on the integer
 *      branch the oracle models,
 *   4. allocate a zeroed MapWorld and call sub_42AC50(world, stream).
 *
 * It then dumps the MapWorld scalars, the two globals the loader writes at the
 * end, and every array pointer it filled (as heap-relative offsets, so the values
 * are independent of where the arena happens to land).
 *
 *   drive_map.exe <map_chunk.bin> <trak_chunk.bin> <wfpc_hex> <dump.txt>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef void  (__cdecl *fn_map)(void *world, void *stream);
typedef int   (__cdecl *fn_trak)(void *cursor_slot, int record_count, void *out_records);
typedef void *(__cdecl *fn_alloc)(int);
typedef unsigned int   *(__cdecl *fn_get_u32)(void);
typedef unsigned int  **(__cdecl *fn_get_pptr)(void);
typedef unsigned char  *(__cdecl *fn_get_u8)(void);

static unsigned char arena[16 << 20];

/* FNV-1a over a byte range: compares the decoded array *values* with the oracle,
 * not just where the arrays landed. */
static unsigned int fnv1a(const unsigned char *p, int len)
{
    unsigned int h = 2166136261u;
    int i;
    for (i = 0; i < len; i++) {
        h ^= p[i];
        h *= 16777619u;
    }
    return h;
}

static unsigned char *read_file(const char *path, long *size)
{
    FILE *f = fopen(path, "rb");
    unsigned char *buf;
    if (!f) {
        printf("cannot open %s\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = (unsigned char *)malloc((size_t)*size);
    if (!buf || fread(buf, 1, (size_t)*size, f) != (size_t)*size) {
        printf("cannot read %s\n", path);
        fclose(f);
        return NULL;
    }
    fclose(f);
    return buf;
}

int main(int argc, char **argv)
{
    HMODULE mod;

    fn_map sub_42AC50;
    fn_trak sub_5563F0;
    fn_alloc sub_41EF00;
    fn_get_u32 get_cursor, get_remaining, get_wfpc, get_320, get_328, get_trak_base;
    fn_get_u8 get_grey;
    unsigned char *map_data;
    unsigned char *trak_data;
    long map_size, trak_size;
    unsigned char *trak_chunk;
    unsigned int trak_cursor;
    unsigned int trak_out = 0;
    unsigned char *world;
    unsigned int world_off;
    unsigned int heap_base;
    FILE *stream;
    FILE *out;
    unsigned int wfpc;
    int i;
    static const struct { int off; const char *name; } FIELDS[] = {
        { 0x00, "tile_count" },   { 0x04, "object_count" }, { 0x08, "object_count_b" },
        { 0x0C, "final_u16" },    { 0x10, "grid_cell_count" }, { 0x14, "grid_width" },
        { 0x18, "grid_height" },  { 0x1C, "section3_count" }, { 0x20, "optional_count" },
        { 0x24, "section3" },     { 0x28, "section4_count" }, { 0x2C, "section4" },
        { 0x30, "section2" },     { 0x34, "unk_34" },       { 0x38, "objects" },
        { 0x3C, "placements" },   { 0x40, "grid_heads" },   { 0x44, "grid_nodes" },
        { 0x48, "grid_flat" },    { 0x4C, "tile_trak" },    { 0x50, "optional20" },
        { 0x54, "unk_54" },       { 0x58, "colour_blocks" }, { 0x5C, "light_count" },
        { 0x60, "lights" },
    };

    setvbuf(stdout, NULL, _IONBF, 0);
    if (argc < 5) {
        printf("usage: drive_map.exe <map_chunk.bin> <trak_chunk.bin> <wfpc_hex> <dump.txt>\n");
        return 2;
    }
    mod = LoadLibraryA("build\\groove_ghidra.dll");
    if (!mod) {
        printf("cannot load the DLL (error %lu)\n", GetLastError());
        return 2;
    }
    sub_42AC50 = (fn_map)GetProcAddress(mod, "wh_sub_42AC50");
    sub_5563F0 = (fn_trak)GetProcAddress(mod, "wh_sub_5563F0");
    sub_41EF00 = (fn_alloc)GetProcAddress(mod, "wh_sub_41EF00");
    get_cursor = (fn_get_u32)GetProcAddress(mod, "wh_get_00586584");
    get_remaining = (fn_get_u32)GetProcAddress(mod, "wh_get_00586588");
    get_wfpc = (fn_get_u32)GetProcAddress(mod, "wh_get_006DA330");
    get_320 = (fn_get_u32)GetProcAddress(mod, "wh_get_006DA320");
    get_328 = (fn_get_u32)GetProcAddress(mod, "wh_get_006DA328");
    get_grey = (fn_get_u8)GetProcAddress(mod, "wh_get_006D7C61");
    get_trak_base = (fn_get_u32)GetProcAddress(mod, "wh_get_005846EC");
    if (!sub_42AC50 || !sub_5563F0 || !sub_41EF00 || !get_cursor || !get_remaining
        || !get_wfpc || !get_320 || !get_328 || !get_grey) {
        printf("missing exports in the harness DLL\n");
        return 2;
    }

    map_data = read_file(argv[1], &map_size);
    trak_data = read_file(argv[2], &trak_size);
    if (!map_data || !trak_data)
        return 2;
    wfpc = (unsigned int)strtoul(argv[3], NULL, 16);

    /* 1. heap */
    *(get_cursor()) = (unsigned int)(size_t)arena;
    *(get_remaining()) = sizeof arena;
    heap_base = (unsigned int)(size_t)arena;

    /* 2. TRAK first: the MAP loader reads through the relocated header table */
    trak_chunk = (unsigned char *)sub_41EF00((int)trak_size);
    if (!trak_chunk) {
        printf("heap refused the TRAK chunk\n");
        return 2;
    }
    memcpy(trak_chunk, trak_data, (size_t)trak_size);
    trak_cursor = (unsigned int)(size_t)(trak_chunk + 4);
    /* out_records must be the DLL's own DAT_005846ec: the MAP loader reads the
       vertex counts through that global, so a driver-local would leave it NULL. */
    sub_5563F0(&trak_cursor, (int)*(unsigned int *)trak_chunk,
               (void *)get_trak_base());   /* the getter returns &DAT_005846ec */
    printf("TRAK: %u records, headers at heap+%08X\n",
           *(unsigned int *)trak_chunk, trak_out - heap_base);

    /* 3. flags: the WFPC value from the WAD, and the greyscale switch off the
     *    integer branch (Ghidra lost the x87 operands of the greyscale path) */
    *(get_wfpc()) = wfpc;
    *(get_grey()) = 1;

    /* 4. zeroed MapWorld, then the loader */
    world = (unsigned char *)sub_41EF00(0x100);
    if (!world) {
        printf("heap refused the MapWorld\n");
        return 2;
    }
    memset(world, 0, 0x100);
    world_off = (unsigned int)(size_t)world - heap_base;

    stream = fopen(argv[1], "rb");
    if (!stream) {
        printf("cannot reopen %s\n", argv[1]);
        return 2;
    }
    printf("calling loader: world=heap+%08X stream=%p\n", world_off, (void *)stream);
    fflush(stdout);
    sub_42AC50(world, stream);
    printf("loader returned: heap_end=heap+%08X\n", *(get_cursor()) - heap_base);
    fflush(stdout);
    fclose(stream);

    out = fopen(argv[4], "w");
    if (!out) {
        printf("cannot write %s\n", argv[4]);
        return 2;
    }
    fprintf(out, "# arena=%08X world=%08X\n", heap_base, (unsigned)(size_t)world);
    for (i = 0; i < 0x64; i += 4) {
        fprintf(out, "#D %02X %08X\n", i, *(unsigned int *)(world + i));
    }
    fprintf(out, "# map=%s (%ld bytes) wfpc=%08X world_off=%08X heap_end=%08X\n",
            argv[1], map_size, wfpc, world_off,
            *(get_cursor()) - heap_base);
    fprintf(out, "# dword_6DA320=%u dword_6DA328=%u\n", *(get_320()), *(get_328()));
    for (i = 0; i < (int)(sizeof FIELDS / sizeof FIELDS[0]); i++) {
        unsigned int *slot = (unsigned int *)(world + FIELDS[i].off);
        unsigned int v = *slot;
        /* pointer fields are reported as heap-relative offsets */
        int is_ptr = (FIELDS[i].off >= 0x24 && FIELDS[i].off <= 0x30)
                  || (FIELDS[i].off >= 0x38 && FIELDS[i].off <= 0x60);
        if (FIELDS[i].off == 0x28 || FIELDS[i].off == 0x1C || FIELDS[i].off == 0x20
            || FIELDS[i].off == 0x5C || FIELDS[i].off == 0x14 || FIELDS[i].off == 0x18
            || FIELDS[i].off == 0x10 || FIELDS[i].off == 0x34 || FIELDS[i].off == 0x54)
            is_ptr = 0;
        fprintf(out, "FIELD %-16s %-10s %u\n", FIELDS[i].name,
                is_ptr ? "offset" : "value",
                is_ptr && v ? v - heap_base : v);
    }
    {
        /* only the address-independent arrays: those carrying relocated pointers
         * (section3/4, optional20, objects, colour blocks) are covered by the offset
         * checks, and hashing them would compare addresses rather than data. */
        unsigned int gfl = *(unsigned int *)(world + 0x48);
        unsigned int ttr = *(unsigned int *)(world + 0x4C);
        unsigned int pla = *(unsigned int *)(world + 0x3C);
        unsigned int sec2 = *(unsigned int *)(world + 0x30);
        unsigned int sec3 = *(unsigned int *)(world + 0x24);
        unsigned int cells = *(unsigned int *)(world + 0x10);
        unsigned int tiles = *(unsigned int *)(world + 0x00);
        fprintf(out, "HASH section2 %08X\n", fnv1a((unsigned char *)sec2, sec3 - sec2));
        fprintf(out, "HASH section5 %08X\n", fnv1a((unsigned char *)(gfl - 0x100), 0x100));
        fprintf(out, "HASH grid_flat %08X\n", fnv1a((unsigned char *)gfl, cells * 4));
        fprintf(out, "HASH placements %08X\n", fnv1a((unsigned char *)pla, tiles * 32));
        fprintf(out, "HASH tile_trak %08X\n", fnv1a((unsigned char *)ttr, tiles * 4));
    }
    fclose(out);
    printf("wrote %s\n", argv[4]);
    return 0;
}
