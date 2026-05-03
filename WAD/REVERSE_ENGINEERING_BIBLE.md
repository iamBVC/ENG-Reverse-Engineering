# Emperor's New Groove WAD Reverse-Engineering Bible

This document is a handoff-grade reverse-engineering notebook for the PC WAD files used by *Disney's / Argonaut's The Emperor's New Groove*.  It summarizes what has been learned from the decompiled executable, how the current Python tooling interprets the data, and which fields remain uncertain.

The goal is practical: another human or AI should be able to continue from the current point without re-reading all of the decompiled ASM/pseudocode.

## Coordinate and numeric conventions

Unless stated otherwise:

- Integer world positions are usually **12.12 fixed point**: `float = value / 4096.0`.
- Several angles use **4096 units per full turn**: `radians = units * 2*pi / 4096`.
- MAP object disk rotations are stored as 16-bit units and then shifted left by 12 before being placed in `Actor340` transform fields.
- The game often flips/negates Z when converting file data into runtime/rendering coordinates.
- Texture/material colors are often doubled and clamped at load/render time.

## WAD container and chunk dispatch

Top-level WAD loading is performed by `sub_558880(_DWORD *ElementSize)`.

It builds a WAD filename from four fields in `ElementSize`:

```c
switch (ElementSize[3]) {
case 0: sprintf(name, "T%01dL%01dM%03d", ElementSize[0], ElementSize[1], ElementSize[2]); break;
case 1: sprintf(name, "T%01dB%01dM%03d", ElementSize[0], ElementSize[1], ElementSize[2]); break;
case 2: sprintf(name, "T%01dS%01dM%03d", ElementSize[0], ElementSize[1], ElementSize[2]); break;
case 3: sprintf(name, "T%01dI%01dM%03d", ElementSize[0], ElementSize[1], ElementSize[2]); break;
}
```

The loader then reads chunk tag and chunk size pairs and dispatches on the little-endian tag integer.

| Integer | Tag | Current meaning | Loader function |
|---:|---|---|---|
| `1179602516` | `FONT` | font-ish 256 x 8-byte table | `sub_558C90` |
| `1279739988` | `LGHT` | light records | `sub_42C180` |
| `1279742019` | `LGPC` / `CPGL` | variable blob/grid/list | `sub_558DB0` |
| `1280198223` | unknown | small loader path | `sub_42AB10` |
| `1296125984` | `MAP ` | main map/full placement chunk | `sub_42AC50` |
| `1095585859` | `AMPC` / `CPMA` | audio/resource | `sub_558D70` |
| `1162757152` | `END ` | terminator | closes WAD |
| `1397575747` | `SMPC` / `CPMS` | audio/resource | `sub_558D30` |
| `1397903427` | `SRPC` / `CPRS` | resource pack | `sub_545350(..., 2)` |
| `1398034499` | `STPC` / `CPTS` | packed scene/static mesh/animation container | `sub_42AB50` |
| `1413830740` | `TEXT`-material-related | material/texture table | `sub_4067B0` |
| `1414676811` | `TRAK` / `KART` integer | terrain/track geometry records | `sub_42AAC0` |
| `1464225859` | flags/version | WAD capability flags | reads `dword_6DA330` |

`sub_558C30(a1)` resets per-level state, frees light handles through `sub_42C460`, clears material pointers, clears the world container, and resets chunk allocator state.

## Core geometry record formats

Two closely related geometry record formats exist:

- `GeometryRecord84`: 132 bytes, used by `dword_5846EC` for TRAK/world geometry and many render/collision paths.
- `GeometryRecord8C`: 140 bytes, used by packed `CPTS/STPC` container sections and extended/skinned/morphed geometry paths.

### `GeometryRecord84`

Confirmed from `sub_5563F0`, `sub_402840`, `sub_556510`, `sub_41FB30`, collision functions, and MAP render dispatch.

```c
#pragma pack(push, 1)
struct Vec3 {
    float x, y, z;
};

struct Vertex24 {
    float x, y, z;
    float nx, ny, nz;
};

struct GeometryRecord84 {
    uint32_t unknown_00;          // +0x00, still unknown
    float unknown_04;             // +0x04, still unknown
    float unknown_08;             // +0x08, still unknown
    Vec3 cull_points[8];          // +0x0C..+0x6B, frustum-culling points used by sub_402840

    uint16_t vertex_count;        // +0x6C / 108
    uint16_t triangle_count;      // +0x6E / 110
    Vertex24 *vertices;           // +0x70 / 112
    Triangle28Runtime *triangles; // +0x74 / 116

    uint16_t collision_group0_count; // +0x78 / 120
    uint16_t collision_group1_count; // +0x7A / 122
    uint16_t collision_group2_count; // +0x7C / 124
    uint16_t unknown_7E;             // +0x7E / 126
    CollisionEntry32 *collision_entries; // +0x80 / 128
}; // 0x84
#pragma pack(pop)
```

The 8 culling points were proven by `sub_402840`: it starts reading at `record + 0x0C`, processes 8 `Vec3`s, transforms them by the current matrix, computes clip/outcode flags with `sub_401080`, ORs all outcodes, ANDs them for trivial rejection, and returns whether the object is visible.

### `GeometryRecord8C`

Used by `sub_41F770` and consumed by `sub_41FB30` when the extended transform-group path is enabled.

```c
struct GeometryRecord8C {
    GeometryRecord84 base;          // +0x00..+0x83
    uint16_t base_vertex_count;     // +0x84 / 132
    uint16_t transform_group_count; // +0x86 / 134
    uint16_t *group_vertex_counts;  // +0x88 / 136
}; // 0x8C
```

`group_vertex_counts` is not just a generic extra array: `sub_41FB30` uses it to decide how many vertices are affected by each transform matrix supplied through its `a9` parameter.

## Geometry relocation loaders

### `sub_42AAC0(FILE *Stream, int ElementSize)`

Loads the direct TRAK-like geometry chunk into `dword_5846EC`:

```c
buffer = alloc(ElementSize);
read(Stream, buffer, ElementSize);
record_count = *buffer++;
sub_5563F0(&cursor, record_count, &dword_5846EC);
```

### `sub_5563F0(int *cursor, int count, DWORD *out)`

Relocates `GeometryRecord84` records:

```text
records[count]                         // 132 bytes each
for each record:
  vertices = cursor; cursor += 24 * vertex_count; record+112 = vertices
  triangles = cursor; cursor += 28 * triangle_count; record+116 = triangles
  collision = cursor; cursor += 32 * (group0+group1+group2); record+128 = collision
  for each triangle:
    triangle.material_ptr = dword_581154 + 20 * triangle.material_index
```

### `sub_41F770(int *cursor, int count, DWORD *out)`

Relocates `GeometryRecord8C` records.  It has the same vertex/triangle/collision relocation as `sub_5563F0`, plus:

```text
record+134 = transform_group_count
record+136 = pointer to u16 transform-group vertex-count array
```

### `sub_42AB50(world, FILE *Stream, int size)`

Loads the packed CPTS/STPC container into `dword_6D9DBC`. It then cursor-relocates nested `GeometryRecord8C` blocks and animation records.  This is the base used when MAP object records store `script_offset`: runtime script pointer is `dword_6D9DBC + script_offset`.

## Triangle records

```c
#pragma pack(push, 1)
struct Triangle28Disk {
    uint16_t flags;          // +0x00
    uint16_t i0;             // +0x02
    uint16_t i1;             // +0x04
    uint16_t i2;             // +0x06
    uint16_t material_index; // +0x08, rewritten to runtime material pointer
    uint16_t material_pad;   // +0x0A
    float plane_nx;          // +0x0C
    float plane_ny;          // +0x10
    float plane_nz;          // +0x14
    float plane_d;           // +0x18
}; // 28 bytes
#pragma pack(pop)
```

At runtime, the 32 bits at `+0x08` become a pointer to a 20-byte `RuntimeMaterial20` entry.

Known triangle flag uses:

| Bit | Meaning / observed use |
|---:|---|
| `0x0001` | material/special render path bit; also material-mode-sensitive in render paths |
| `0x0002` | render/effect queue bit used with `dword_5F6EE8` |
| `0x0008` | render batch/material-state separator |
| `0x0010` | terrain UV branch bit, used with `0x0800` |
| `0x0020` | UV swap / material filter bit |
| `0x0400` | backface/plane-cull override |
| `0x0800` | terrain UV branch bit |

The terrain UV mapping confirmed by `sub_556510` is implemented in the current Python tools.

## Collision/contact entries

The geometry record's `+0x80` pointer references 32-byte collision/contact plane records. The three counts at `+0x78/+0x7A/+0x7C` are summed by collision routines; semantic group names remain unknown.

```c
#pragma pack(push, 1)
struct CollisionEntry32 {
    uint8_t  flags;          // +0x00, bit0: 0=3 edge tests, 1=4 edge tests
    uint8_t  surface_id;     // +0x01, IDs 17/18 skipped by some actors, 30 invalid/no-contact
    int8_t   normal_x_q32;   // +0x02
    int8_t   normal_y_q32;   // +0x03
    int8_t   normal_z_q32;   // +0x04
    int8_t   unknown_05;     // +0x05
    int16_t  plane_d;        // +0x06
    uint8_t  edge_data[24];  // +0x08, 3 or 4 x 6-byte edge equations
}; // 32 bytes
#pragma pack(pop)
```

Plane coefficients:

```c
nx = 32 * (int8_t)entry[2];
ny = 32 * (int8_t)entry[3];
nz = 32 * (int8_t)entry[4];
d  = *(int16_t *)(entry + 6);
```

Edge half-space test pattern:

```c
((x * 32 * edge.x + y * 32 * edge.y + z * 32 * edge.z) >> 12) - edge.d
```

Important collision functions:

| Function | Role |
|---|---|
| `sub_404240` | broadphase over MAP grid for actor radius |
| `sub_4042F0` | static map swept collision/contact test per grid cell |
| `sub_4036D0` | static current-position ground/contact scan |
| `sub_403AD0` | dynamic actor/object ground/contact scan |
| `sub_4046E0` | dynamic swept actor/object push test |
| `sub_403020` | final ground/contact chooser, writes actor contact state |
| `sub_403EE0` | push/standing/alignment response |

## TEXT textures and runtime material table

### TEXT texture compression

Textures are RGB555 word RLE streams, not 8-bit paletted LZSS. Default channel order is BGR for decoded PNGs.

```python
packet = read_u16()
if packet < 0x8000:
    # literal packet
    read packet RGB555 words
else:
    count = 0x10000 - packet
    word = read_u16()
    repeat word count times
```

RGB555 base decode:

```python
def rgb555_to_rgb(word):
    r = ((word & 0x7C00) >> 10) << 3
    g = ((word & 0x03E0) >> 5) << 3
    b = (word & 0x001F) << 3
```

### Runtime material table

`sub_4067B0` / `sub_407240` populate `dword_581154`, a 20-byte-stride material table.

```c
struct RuntimeMaterial20 {
    uint16_t flags;             // +0x00
    int8_t   texture_page_idx;  // +0x02, -1 = none
    int8_t   texture_ref_idx;   // +0x03, -1 = none
    float    u0;                // +0x04
    float    u1;                // +0x08
    float    v0;                // +0x0C
    float    v1;                // +0x10
}; // 20 bytes
```

Disk material fields are 8 bytes in the TEXT trailing table:

```c
struct MaterialDisk8 {
    uint16_t flags;
    uint8_t  texture_index;
    uint8_t  extra;
    uint8_t  x0, x1, y0, y1;
};
```

`sub_407240` converts material rects to UV floats:

```c
u0 = x0 / texture_width;
u1 = (x1 + 1) / texture_width;
v0 = y0 / texture_height;
v1 = (y1 + 1) / texture_height;
```

Known material flag observations:

| Bit/range | Meaning |
|---:|---|
| `flags & 0x0001` | color-only / special path, not a normal texture page |
| `(flags >> 12) & 7` | blend/render mode |
| `flags & 0x0002` | flip/alpha-related bit |
| `flags & 0x0004` | padded border |
| `flags & 0x0008` | double width |
| `flags & 0x0010` | double height |
| `flags & 0x0020` | generated page |

## TRAK chunk

`TRAK` stores the direct world/terrain geometry table used by `dword_5846EC`.  It is loaded by `sub_42AAC0` and relocated by `sub_5563F0`.

Current exporter output includes:

- `trak/records.csv`
- `trak/table_a_vertices.csv`
- `trak/table_b_triangles.csv`
- `trak/table_cde_entries.csv`
- OBJ diagnostic surfaces and per-record OBJ files
- MAP-placed terrain viewer after MAP_FULL parse

The record format is `GeometryRecord84`.

## STPC / CPTS chunk

`STPC` is loaded by `sub_42AB50` into `dword_6D9DBC`.  It contains packed scene/container data, embedded `GeometryRecord8C` records, animation data, and object/script data consumed by MAP object records.

Current status:

- STPC mesh scanner/exporter can find and export validated static meshes.
- STPC OBJ exports include material/UV output where derivable from runtime materials.
- STPC object definition parsing is still heuristic: MAP object `script_offset` points into `dword_6D9DBC`, and the world exporter scans around that area for exact decoded STPC mesh-record offsets.

## Geometry animation records

`sub_41F8B0` loads 32-byte geometry animation/morph records. `sub_41FA30(geometry, anim, frame)` applies them to vertices.

Observed structure:

```c
struct GeometryAnimRecord32 {
    uint32_t unknown_count_a;      // +0x00
    void    *ptr_a;                // +0x04
    uint32_t frame_count;          // +0x08
    void    *maybe_frame_data;     // +0x0C
    uint32_t vertex_count;         // +0x10, used by sub_41FA30
    void   **frame_delta_ptrs;     // +0x14
    uint32_t block64_count;        // +0x18
    void    *block64_ptrs;         // +0x1C
}; // 32 bytes
```

`sub_41FA30` behavior:

- `frame == 0`: writes absolute base positions from signed 16-bit fixed values scaled by `1/4096`.
- `frame != 0`: applies packed 16-bit deltas with exponent-like high nibble and 4-bit signed components.

Important actor animation calls:

| Function | Role |
|---|---|
| `sub_550160` | pops an animation pointer, sets `actor+20`, resets frame fields, applies frame 0 |
| `sub_54FAD0` | pops fixed-frame value, advances `actor+272`, applies frame deltas |
| `sub_54C4A0` | update path that can call `sub_41FA30` when time advances |

## LGHT chunk

Loaded by `sub_42C180(world, Stream)`.

World light fields:

```c
struct MapWorldLightFields {
    uint32_t light_count;       // world +0x5C / 92
    RuntimeLight112 **lights;   // world +0x60 / 96
};
```

### Disk layout

```c
#pragma pack(push, 1)
struct LGHT_Header {
    uint32_t light_count;
};

struct LGHT_Type1_Directional {
    uint8_t type;     // 1
    uint8_t r, g, b;  // byte intensity, converted to 0..2 range
    float dir_x;
    float dir_y;
    float dir_z;      // runtime negates z
}; // 16 bytes

struct LGHT_Type2_Point {
    uint8_t type;     // 2
    uint8_t r, g, b;
    float x, y, z;    // runtime negates z
    float inner_radius;
    float outer_radius;
    uint8_t falloff_or_mode;
}; // 25 bytes packed

struct LGHT_Type4_NegativePoint {
    uint8_t type;     // 4 on disk; runtime type 2 with negative/special color
    uint8_t r, g, b;
    float x, y, z;    // runtime negates z
    float inner_radius;
    float outer_radius;
    uint8_t falloff_or_mode;
}; // 25 bytes packed
#pragma pack(pop)
```

Color conversion:

```c
base = (2 * byte) / 255.0;
```

Type 4 conversion before constructing a runtime type-2 light:

```c
runtime_component = -(component + 1.0) * 0.5;
```

### `RuntimeLight112`

Allocated by `sub_41B8A0`, 112 bytes.

```c
struct RuntimeLight112 {
    float color_r;             // +0x00 current/effective
    float color_g;             // +0x04
    float color_b;             // +0x08
    float color_a_or_unused;   // +0x0C

    float base_r;              // +0x10 constructor r
    float base_g;              // +0x14
    float base_b;              // +0x18
    float base_a_or_unused;    // +0x1C

    float pos_x_current;       // +0x20 type 2
    float pos_y_current;       // +0x24
    float pos_z_current;       // +0x28

    float dir_x;               // +0x2C type 1 normalized
    float dir_y;               // +0x30
    float dir_z;               // +0x34

    float pos_x_base;          // +0x38 type 2
    float pos_y_base;          // +0x3C
    float pos_z_base;          // +0x40

    float dir_x_base;          // +0x44 type 1 copied normalized direction
    float dir_y_base;          // +0x48
    float dir_z_base;          // +0x4C

    float outer_radius_sq;     // +0x50 type 2
    float inner_radius_sq;     // +0x54
    float outer_radius;        // +0x58
    float inner_radius;        // +0x5C
    float inv_radius_range;    // +0x60 = 1/(outer-inner)
    uint32_t falloff_or_mode;  // +0x64
    uint32_t type;             // +0x68, 1=directional, 2=point/ranged
    uint8_t active_or_flags;   // +0x6C, constructor clears to 0
}; // 112 bytes
```

`sub_41BEE0` copies base color to current color and converts current RGB to grayscale when color rendering is disabled.  `sub_41BD70`, `sub_41BF80`, `sub_41BFA0`, and `sub_41BFC0` maintain a simple linked list of active lights.

## MAP_FULL / MAP chunk

The executable-confirmed MAP parser follows `sub_42AC50`.

### High-level `MapWorld`

```c
struct MapWorld {
    uint32_t tile_count;       // +0x00
    uint32_t object_count;     // +0x04
    uint32_t object_count_b;   // +0x08
    uint16_t final_u16;        // +0x0C read at end

    // ...
    uint32_t grid_width;       // +0x14 / a1[5]
    uint32_t grid_height;      // +0x18 / a1[6]

    MapObjectRuntime72 *objects; // +0x38 / a1[14]
    MapTilePlacement32 *placements; // +0x3C / a1[15]
    GridNode **grid_heads;     // +0x40 / a1[16]
    GridNode *grid_nodes;      // +0x44 / a1[17]
    uint32_t *grid_visibility_mask; // +0x48 / a1[18]
    uint32_t *tile_trak_indices;    // +0x4C / a1[19]

    uint32_t optional_count;   // +0x20 / a1[8], when dword_6DA330 & 0x10000
    Optional20 *optional20;    // +0x50 / a1[20]
    uint8_t **vertex_color_blocks; // +0x58 / a1[22]

    uint32_t light_count;      // +0x5C
    RuntimeLight112 **lights;  // +0x60
};
```

### MAP tile placement / render dispatch

`sub_42BF40(world, dword_5846EC)` loops visible grid cells, reads tile placement records from `world+0x3C`, resolves TRAK geometry through `world+0x4C`, and calls `sub_556510(record, translation, yaw, vertex_color_block)`.

`MapTilePlacement32` access in `sub_42BF40`:

```c
struct MapTilePlacement32 {
    uint32_t unknown_00;
    int32_t  yaw_4096;       // +0x04, radians = yaw * 2*pi/4096
    uint32_t unknown_08;
    uint32_t unknown_0C;
    int32_t  pos_x_fixed12;  // +0x10
    int32_t  pos_y_fixed12;  // +0x14
    int32_t  pos_z_fixed12;  // +0x18, runtime/render negates z
    uint32_t unknown_1C;
};
```

### Object table: disk 58 bytes -> runtime 72 bytes -> Actor340

This is the most recent major discovery.

`sub_42AC50` reads each MAP object as a packed 58-byte disk record and expands it to a 72-byte runtime record at `world+0x38`. `sub_54CFC0` later consumes the runtime table and spawns `Actor340` entries via `sub_54BFC0`.

#### `MapObjectDisk58`

```c
#pragma pack(push, 1)
struct MapObjectDisk58 {
    uint16_t rot_x_units;          // +0x00, expanded to u32; actor receives << 12
    uint16_t rot_y_units;          // +0x02
    uint16_t rot_z_units;          // +0x04

    int32_t pos_x_fixed12;         // +0x06
    int32_t pos_y_fixed12;         // +0x0A
    int32_t pos_z_fixed12;         // +0x0E

    uint32_t script_offset;        // +0x12, runtime = dword_6D9DBC + offset
    uint32_t local_count;          // +0x16
    uint32_t section2_index;       // +0x1A, sentinel => NULL else section2 + 4*index
    uint32_t stack_word_count;     // +0x1E, passed as sub_54BFC0 a4
    uint32_t stack_arg_count;      // +0x22, values popped from parent/root stack
    uint32_t spawn_flags;          // +0x26, Actor340 +0xEC and +0x138
    uint32_t extra_count;          // +0x2A
    uint32_t section4_index;       // +0x2E, sentinel => NULL else section4 + 48*index
    uint32_t spawn_aux_raw;        // +0x32, runtime +0x40; may become Section4 tail pointer
    uint16_t flags;                // +0x36, bit 1 skips initial spawn
    uint16_t extra_u16;            // +0x38
}; // 58 bytes
#pragma pack(pop)
```

#### `MapObjectRuntime72`

```c
struct MapObjectRuntime72 {
    uint32_t rot_x_units;          // +0x00
    uint32_t rot_y_units;          // +0x04
    uint32_t rot_z_units;          // +0x08
    uint32_t unused_0C;            // +0x0C, not written by sub_42AC50

    int32_t pos_x_fixed12;         // +0x10
    int32_t pos_y_fixed12;         // +0x14
    int32_t pos_z_fixed12;         // +0x18
    uint32_t unused_1C;            // +0x1C, not written by sub_42AC50

    uint32_t *script_pc;           // +0x20 = dword_6D9DBC + script_offset
    uint32_t local_count;          // +0x24
    uint32_t *section2_ptr;        // +0x28 or NULL
    uint32_t stack_word_count;     // +0x2C
    uint32_t stack_arg_count;      // +0x30
    uint32_t spawn_flags;          // +0x34
    uint32_t extra_count;          // +0x38
    MapSection4Runtime48 *section4_ptr; // +0x3C or NULL
    uint32_t spawn_aux_or_section4_tail; // +0x40
    uint16_t flags;                // +0x44, bit 1 = skip initial spawn
    uint16_t extra_u16;            // +0x46
}; // 72 bytes
```

`sub_54CFC0` does:

```c
if ((object->flags & 2) == 0) {
    Transform32 t;
    t.rot_x = object->rot_x_units << 12;
    t.rot_y = object->rot_y_units << 12;
    t.rot_z = object->rot_z_units << 12;
    t.pos_x = object->pos_x_fixed12;
    t.pos_y = object->pos_y_fixed12;
    t.pos_z = object->pos_z_fixed12;

    SpawnParams sp;
    sp.initial_stack_count = object->stack_arg_count;
    sp.local_count = object->local_count;
    sp.flags = object->spawn_flags;
    sp.extra_count = object->extra_count;
    sp.attach_to_parent = 0;
    sp.value_18 = object->spawn_aux_or_section4_tail;

    sub_54BFC0(&sp, &t, object->script_pc, object->stack_word_count, 0);
}
```

### Section4 runtime table

`sub_42AC50` reads 34-byte disk section4 entries and expands them to 48 bytes, then builds linked-list pointers. Object records can reference this table through `section4_index`.

```c
struct MapSection4Runtime48 {
    MapSection4Runtime48 *next;  // +0x00
    MapSection4Runtime48 *prev;  // +0x04
    uint32_t small_a;            // +0x08, disk u16 expanded
    uint32_t small_b;            // +0x0C
    uint32_t small_c;            // +0x10
    uint32_t unused_14;          // +0x14
    uint32_t field_18;           // +0x18
    uint32_t field_1C;           // +0x1C
    uint32_t field_20;           // +0x20
    uint32_t unused_24;          // +0x24
    uint32_t field_28;           // +0x28
    uint32_t field_2C;           // +0x2C
}; // 48 bytes
```

## Actor system

### Globals

```c
Actor340 *dword_6D9DC0;  // actor pool base
Actor340 *dword_6D9E38;  // active actor list head
Actor340 *dword_6D9E3C;  // free actor list head
uint32_t dword_6D9DC8;   // active/used actor count
```

`sub_54D0D0(world)` allocates `340 * (world->object_count_b? or object capacity + 30)` bytes, resets each actor with `sub_54CEF0`, pushes actors onto the free list, then calls `sub_54CFC0(world)` to spawn initial objects.

### `SpawnParams`

Inferred from `sub_54BFC0`:

```c
struct SpawnParams {
    Actor340 *parent_or_source;   // +0x00
    uint32_t initial_stack_count; // +0x04
    uint32_t local_count;         // +0x08
    uint32_t flags;               // +0x0C
    uint32_t extra_count;         // +0x10
    uint32_t attach_to_parent;    // +0x14
    uint32_t value_18;            // +0x18, copied to Actor340 +0xF0
};
```

### `Transform32`

```c
struct Transform32 {
    int32_t rot_x;    // +0x00, actor fixed-angle domain
    int32_t rot_y;    // +0x04
    int32_t rot_z;    // +0x08
    int32_t unk_0C;   // +0x0C
    int32_t pos_x;    // +0x10, fixed12
    int32_t pos_y;    // +0x14
    int32_t pos_z;    // +0x18
    int32_t unk_1C;   // +0x1C
};
```

### `Actor340`

```c
#pragma pack(push, 1)
struct Actor340 {
    uint32_t *script_pc;             // +0x000
    Actor340 *next;                  // +0x004
    Actor340 *prev;                  // +0x008
    Actor340 *owner_or_template;     // +0x00C

    GeometryRecord84 *geometry;      // +0x010
    GeometryAnimRecord32 *anim;      // +0x014
    uint32_t unk_018;                // +0x018, initialized to aBlank in spawn path
    uint32_t unk_01C;                // +0x01C

    Transform32 current;             // +0x020
    Transform32 target_or_start;     // +0x040

    int32_t scale_x;                 // +0x060, default 4096
    int32_t scale_y;                 // +0x064, default 4096
    int32_t scale_z;                 // +0x068, default 4096
    int32_t unk_06C;                 // +0x06C

    int32_t matrix_3x3[9];           // +0x070..+0x090, written by sub_54BC30
    int32_t matrix_tx;               // +0x094
    int32_t matrix_ty;               // +0x098
    int32_t matrix_tz;               // +0x09C

    Transform32 saved_transform;     // +0x0A0

    void *contact_state;             // +0x0C0 / 192
    uint16_t contact_0C;             // +0x0CC / 204
    uint16_t contact_0E;             // +0x0CE / 206
    uint16_t contact_10;             // +0x0D0 / 208
    uint16_t collision_radius;       // +0x0D2 / 210, default 1024
    int16_t contact_index;           // +0x0D4 / 212, default -1

    uint8_t unknown_0D6[18];
    uint32_t flags0;                 // +0x0E8 / 232, script stop bits include 0x02 and 0x10
    uint32_t render_or_spawn_flags;  // +0x0EC / 236
    uint32_t spawn_aux;              // +0x0F0 / 240

    void *mem_base;                  // +0x0F4 / 244
    void *locals_ptr;                // +0x0F8 / 248
    uint16_t unk_0FC;                // +0x0FC / 252
    uint16_t unk_0FE;                // +0x0FE / 254
    uint32_t local_count;            // +0x100 / 256
    uint32_t script_stack_ptr;       // +0x104 / 260
    uint32_t script_stack_count;     // +0x108 / 264

    int32_t alpha_or_intensity;      // +0x10C / 268, default 4096
    uint32_t anim_frame;             // +0x110 / 272
    uint16_t anim_scale_or_time;     // +0x114 / 276, default 4096
    uint16_t anim_subframe;          // +0x116 / 278

    uint32_t inherited_280;          // +0x118 / 280
    uint32_t inherited_284;          // +0x11C / 284
    uint32_t inherited_288;          // +0x120 / 288
    uint32_t inherited_292;          // +0x124 / 292

    uint16_t special_material_index; // +0x128 / 296
    uint16_t unk_12A;                // +0x12A
    uint32_t special_size;           // +0x12C / 300

    uint8_t b304;                    // +0x130, default 0
    int8_t b305;                     // +0x131, default -1
    int8_t b306;                     // +0x132, default -1
    uint8_t tint_r_or_state;         // +0x133
    uint8_t tint_g_or_state;         // +0x134
    uint8_t tint_b_or_state;         // +0x135
    uint8_t tint_enabled;            // +0x136

    uint8_t unk_137;
    uint32_t spawn_flags_copy;       // +0x138 / 312
    uint32_t unk_13C;                // +0x13C / 316, default 4096
    uint32_t unk_140;                // +0x140 / 320, default 0
    uint8_t unknown_144[8];
    uint32_t unk_148;                // +0x148 / 328
    int32_t yaw_override;            // +0x14C / 332, default -4096
    int8_t b336, b337, b338, b339;   // +0x150..+0x153, default -1
}; // 0x154 / 340
#pragma pack(pop)
```

### Important actor functions

| Function | Meaning |
|---|---|
| `sub_54CEF0(actor)` | reset actor slot defaults |
| `sub_54D0D0(world)` | allocate actor pool and spawn initial objects |
| `sub_54CFC0(world)` | iterate `MapObjectRuntime72`, build `SpawnParams`/`Transform32`, call `sub_54BFC0` |
| `sub_54BFC0(spawn, transform, script_pc, stack_words, keep_owner)` | main actor spawn/clone/init function |
| `sub_54BC00(actor)` | pop 32-bit value from actor script stack |
| `sub_54BBD0(actor, value)` | push 32-bit value onto actor script stack |
| `sub_54D180(actor)` | script VM loop; stops when `flags0 & 0x12` |
| `sub_54BC30(actor)` | build scaled 3x4 transform matrix from rotations, position, scale |
| `sub_550160(actor)` | set geometry animation pointer from stack and apply frame 0 |
| `sub_54FAD0(actor)` | advance/apply geometry animation frame |
| `sub_546240(actor, id)` | unlink actor from sound/effect emitter pool |

## DEM demo files

DEM file structure:

```c
struct DemFile {
    uint32_t frame_count;
    DemFrame frames[frame_count];
};

struct DemFrame {
    uint16_t buttons;      // PS1-style button bitmask
    uint16_t base_angle;   // copied to word_5FCF00; likely 12-bit direction/angle
    uint16_t aux_u16;      // copied to dword_58471C
    int8_t   analog_x;     // sign-extended and shifted left by 6
    int8_t   analog_y;     // sign-extended and shifted left by 6
}; // 8 bytes
```

Loader/playback path:

- `sub_4255B0` loads `Wads/<name>.DEM`.
- `sub_4256C0` consumes one 8-byte frame per game tick.

Analog conversion:

```c
dword_5FCF1C = (int8_t)analog_x << 6;
dword_5FCF2C = (int8_t)analog_y << 6;
```

Fallback d-pad values:

| Direction | Runtime value |
|---|---:|
| UP | `dword_5FCF2C = 0x1FC0` |
| DOWN | `dword_5FCF2C = -0x2000` |
| LEFT | `dword_5FCF1C = 0x1FC0` |
| RIGHT | `dword_5FCF1C = -0x2000` |

## Current project outputs tied to these discoveries

- `map_full/objects_58_disk.csv`: decoded disk MAP object records with EXE-backed field names.
- `map_full/objects_72_runtime.csv`: how the disk records expand into the runtime 72-byte table.
- `map_full/actors_spawn_preview.csv`: predicted initial `Actor340` spawn fields.
- `map_full/object_spawn_points.obj`: confirmed fixed12 object position markers.
- `lights/lights.csv`: typed directional/point/negative point lights with runtime conversions.
- `trak/table_cde_entries.csv`: decoded `CollisionEntry32` rows.
- `world/map_object_instances.csv`: MAP object placements plus spawn/script metadata used by STPC reference scanning.

## Remaining high-value unknowns

1. Exact semantics of `MapObjectDisk58` script data. `script_offset` points into `dword_6D9DBC`, but the bytecode/data structure there still needs further decoding.
2. Exact meaning of `MapObjectDisk58.flags` bits besides `0x0002` skip-initial-spawn.
3. Exact meaning of `section2` and `section4` records beyond their object references and linked-list structure.
4. The final `LGHT` type 2/4 byte `falloff_or_mode` needs lighting evaluator xrefs for a precise name.
5. `GeometryRecord84` fields `+0x00`, `+0x04`, `+0x08`, and `+0x7E` remain unnamed.
6. STPC object-definition structure and script VM opcodes need more work to replace mesh-reference scanning with exact instance binding.
7. Remaining material tables `dword_581144` and `dword_58114C` are used by render state/texture refs but are not fully named.

## Recommended next reverse-engineering targets

1. Callers of `sub_5531D0`, `sub_553230`, and `sub_5533F0`, because they also call `sub_54BFC0` and probably represent scripted actor spawning/cloning variants.
2. Script VM opcode handlers in `funcs_54D1AB` and `funcs_54D1B8`, especially handlers that read/write actor fields `+16`, `+20`, `+296`, `+300`, `+332`, and transform fields.
3. Consumers of `MapObjectRuntime72 +0x28` and `+0x3C` to name Section2 and Section4.
4. Lighting evaluator functions that iterate the active light list and read `RuntimeLight112 +0x50..+0x68`.
5. Functions reading `GeometryRecord84 +0x00/+0x04/+0x08/+0x7E`.

