/* groove.h - shared declarations for the groove.exe decompilation project.
 *
 * Everything in here is either (a) needed by the functions already ported, or
 * (b) a structure whose layout was confirmed against the executable in
 * REVERSE_ENGINEERING_BIBLE.md.  The GROOVE_ASSERT_OFFSET() checks make the
 * build fail if a layout drifts, so this header doubles as documentation that
 * the compiler verifies.
 */
#ifndef GROOVE_H
#define GROOVE_H

#include <stddef.h>
#include <stdio.h>

/* Compile-time checks (the negative-array-size trick works on every compiler,
 * including C89/MSVC 6).  `name` must be a unique identifier. */
#define GROOVE_STATIC_ASSERT(expr, name) \
    typedef char groove_static_assert_##name[(expr) ? 1 : -1]
#define GROOVE_ASSERT_SIZE(tag, type, size) \
    GROOVE_STATIC_ASSERT(sizeof(type) == (size), tag)

/* ------------------------------------------------------------------ *
 * Globals confirmed in the Bible
 * ------------------------------------------------------------------ */

/* Primary bump heap (the 16 MB block from sub_41EEA0).
 * dword_586588 is compared with `jle`, so it is signed. */
extern unsigned char *dword_586580;   /* block base, NULL when not allocated */
extern unsigned char *dword_586584;   /* allocation cursor                   */
extern int            dword_586588;   /* bytes remaining in the block        */

/* Secondary bump heap used by the terrain renderer (sub_41ED90). */
extern unsigned char *dword_58656C;   /* allocation cursor                   */
extern int            dword_586570;   /* bytes remaining                     */

/* ------------------------------------------------------------------ *
 * Confirmed structures (offsets verified from sub_42AC50 et al.)
 * ------------------------------------------------------------------ */

struct MapSection3Runtime92;
struct MapSection4Runtime48;
struct MapObjectRuntime72;
struct Optional20Runtime24;
struct GridNode;
struct RuntimeLight112;

/* GridNode is { u32 tile_index; GridNode *next; } (8 bytes). */
struct GridNode {
    unsigned int tile_index;          /* +0x00 */
    struct GridNode *next;            /* +0x04 */
};
GROOVE_ASSERT_SIZE(GridNode_is_8_bytes, struct GridNode, 8);

struct MapWorld {
    unsigned int tile_count;              /* +0x00 */
    unsigned int object_count;            /* +0x04 */
    unsigned int object_count_b;          /* +0x08  actor-pool sizing (sub_54D0D0) */
    unsigned short final_u16;             /* +0x0C  read last via sub_415AF0 */
    unsigned short unk_0E;                /* +0x0E */

    unsigned int grid_cell_count;         /* +0x10  computed: grid_height * grid_width */
    unsigned int grid_width;              /* +0x14 */
    unsigned int grid_height;             /* +0x18 */
    unsigned int section3_count;          /* +0x1C */

    unsigned int optional_count;          /* +0x20  only when WFPC & 0x10000 */
    struct MapSection3Runtime92 *section3;/* +0x24  disk 90 B -> runtime 92 B */
    unsigned int section4_count;          /* +0x28 */
    struct MapSection4Runtime48 *section4;/* +0x2C  disk 34 B -> runtime 48 B */
    unsigned int *section2;               /* +0x30  packed initial-local pool */
    unsigned int unk_34;                  /* +0x34 unknown */
    struct MapObjectRuntime72 *objects;   /* +0x38  disk 58 B -> runtime 72 B */
    unsigned int *placements;             /* +0x3C  tile defs, disk 24 B -> runtime 32 B */

    struct GridNode **grid_heads;         /* +0x40  [grid_cell_count] spatial hash heads */
    struct GridNode *grid_nodes;          /* +0x44  [tile_count] hash nodes */
    unsigned int *grid_flat;              /* +0x48  [grid_height * grid_width] zone ids */

    unsigned int *tile_trak_indices;      /* +0x4C */
    struct Optional20Runtime24 *optional20;/* +0x50  disk 20 B -> runtime 24 B */
    unsigned int unk_54;                  /* +0x54 unknown */
    unsigned char **vertex_color_blocks;  /* +0x58  [tile_count] colour blocks */

    unsigned int light_count;             /* +0x5C */
    struct RuntimeLight112 **lights;      /* +0x60 */
};

GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, object_count_b) == 0x08, MapWorld_object_count_b);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, grid_width) == 0x14, MapWorld_grid_width);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, grid_height) == 0x18, MapWorld_grid_height);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, section2) == 0x30, MapWorld_section2);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, objects) == 0x38, MapWorld_objects);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, placements) == 0x3C, MapWorld_placements);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, grid_heads) == 0x40, MapWorld_grid_heads);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, grid_nodes) == 0x44, MapWorld_grid_nodes);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, grid_flat) == 0x48, MapWorld_grid_flat);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, tile_trak_indices) == 0x4C, MapWorld_tile_trak_indices);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, optional20) == 0x50, MapWorld_optional20);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, vertex_color_blocks) == 0x58, MapWorld_vertex_color_blocks);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, light_count) == 0x5C, MapWorld_light_count);
GROOVE_STATIC_ASSERT(offsetof(struct MapWorld, lights) == 0x60, MapWorld_lights);

struct MapWorld *dword_584648_get(void);   /* the global `world` pointer lives elsewhere */

/* Tile placement record: 24 bytes on disk, 32 bytes at runtime. */
struct MapTilePlacement32 {
    unsigned int always_zero_00;   /* +0x00  runtime +0x00, 0 in every sampled WAD */
    int          yaw_4096;         /* +0x04  radians = yaw * 2*pi/4096; +0x00 unused */
    unsigned int always_zero_08;   /* +0x08  0 in every sampled WAD */
    unsigned int pad_0C;           /* +0x0C  skipped by the loader, never written    */
    int          pos_x_fixed12;    /* +0x10  12.12 fixed point */
    int          pos_y_fixed12;    /* +0x14 */
    int          neg_pos_z_fixed12;/* +0x18  the file stores -Z; render negates again */
    unsigned int pad_1C;           /* +0x1C  skipped by the loader, never written    */
};
GROOVE_STATIC_ASSERT(sizeof(struct MapTilePlacement32) == 32, MapTilePlacement32_is_32_bytes);
GROOVE_STATIC_ASSERT(offsetof(struct MapTilePlacement32, yaw_4096) == 0x04, MapTilePlacement_yaw);
GROOVE_STATIC_ASSERT(offsetof(struct MapTilePlacement32, pos_x_fixed12) == 0x10, MapTilePlacement_pos_x);

/* TRAK header record, 132 bytes, array base is dword_5846EC. */
#define GROOVE_TRAK_RECORD_SIZE 132

/* ------------------------------------------------------------------ *
 * Data symbols used by the ported code (see src/gr_data.c for which of
 * these are confirmed values and which are address-only placeholders)
 * ------------------------------------------------------------------ */
extern const float flt_56E008;   /* 1.0  */
extern const float flt_56E1A0;   /* 0.01 */
extern float flt_581970;

extern int dword_581158;
extern int dword_583740;
extern int dword_584644;
extern int dword_586408;
extern int dword_58640C;
extern int dword_586420;

extern unsigned char byte_6D9858;
extern unsigned char byte_6D94E8;

extern unsigned int dword_58226C[0x100];
extern unsigned int unk_5821E0[0x0F];

extern void *off_56E1C4;        /* PLACEHOLDER: address-only */
extern void *off_56E1C8;        /* PLACEHOLDER: address-only */

/* ------------------------------------------------------------------ *
 * Ported functions (one C function per original, same base name)
 * ------------------------------------------------------------------ */

/* gr_io.c - the fread wrappers used by every chunk loader. */
int sub_415A90(FILE *Stream, void *Buffer, int ElementSize); /* fread(Buffer, ElementSize, 1, Stream) */
int sub_415AD0(FILE *Stream, void *Buffer);                  /* fread(Buffer, 1, 1, Stream) */
int sub_415AB0(FILE *Stream, void *Buffer);                  /* fread(Buffer, 4, 1, Stream) */
int sub_415AF0(FILE *Stream, void *Buffer);                  /* fread(Buffer, 2, 1, Stream) */

/* gr_alloc.c - the two bump allocators and the primary block manager. */
void *sub_41ED90(int size);                                  /* secondary heap */
void  sub_41EEA0(void);                                      /* primary: (re)create 16 MB block */
void  sub_41EEE0(void);                                      /* primary: reset cursor to base */
void *sub_41EF00(int size);                                  /* primary heap */

/* gr_small.c - batch 1 of the small leaf game functions. */
void  sub_406E30(void);
void  sub_408390(int arg_0, int arg_4, int arg_8, unsigned char *arg_C);
void  sub_40D900(void);
void  sub_40D910(void);
void  sub_40E020(void);
void  sub_40E0A0(void);
void  sub_40E610(int index, char *Buffer);
int   sub_4136C0(int *a, int *b);
/* ECX-passed `this` with no stack arguments: __fastcall is byte-identical to
 * __thiscall here (first dword argument in ECX, nothing to clean up).  MSVC
 * rejects __thiscall on free functions with C3865, so this is the faithful form. */
void  __fastcall sub_413B10(void *self);
void  sub_4155E0(void);
void *__fastcall sub_41BCB0(void *self);

/* gr_pending.c - translated but not linkable yet (callee not reversed). */
void  sub_40DB70(void);
void  sub_41D330(void);
void  sub_41E1B0(void);
int   sub_4255A0(void);
int   sub_426860(void);
/* thiscall with a stack argument and `retn 4`: not expressible as a free
 * function in MSVC, so the body is emitted verbatim (see gr_small.c).
 * (`__declspec(naked)` may only appear on the definition, not here.) */
void  sub_40FC90(void *self, const void *src);

/* gr_map.c - pure helpers extracted from sub_42AC50.  These are NOT 1:1
 * counterparts in the original (the original inlines them), so they are
 * checked behaviourally rather than byte-compared. */
int groove_tile_cell_index(float pos_x, float pos_z, int grid_width);

#endif /* GROOVE_H */
