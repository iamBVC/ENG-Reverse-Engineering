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
| `1179602516` | `FONT` | 256-entry glyph material/metric table | `sub_558C90` |
| `1279739988` | `LGHT` | light records | `sub_42C180` |
| `1279742019` | `LGPC` / `CPGL` | localized dialogue/text table | `sub_558DB0` |
| `1280198223` | unknown | small loader path | `sub_42AB10` |
| `1296125984` | `MAP ` | main map/full placement chunk | `sub_42AC50` |
| `1095585859` | `AMPC` / `CPMA` | ambient-audio resource bank and emitters | `sub_558D70` |
| `1162757152` | `END ` | terminator | closes WAD |
| `1397575747` | `SMPC` / `CPMS` | audio/resource | `sub_558D30` |
| `1397772884` | `SPRT` | sprite material-base metadata | inline branch at `loc_558AD1` |
| `1397903427` | `SRPC` / `CPRS` | streamed speech slice table | `sub_545350(..., 2)` |
| `1398034499` | `STPC` / `CPTS` | packed scene/static mesh/animation container | `sub_42AB50` |
| `1413830740` | `TEXT`-material-related | material/texture table | `sub_4067B0` |
| `1414676811` | `TRAK` / `KART` integer | terrain/track geometry records | `sub_42AAC0` |
| `1464225859` | `WFPC` | WAD feature/capability flags | reads `dword_6DA330` |

`sub_558C30(a1)` resets per-level state, frees light handles through `sub_42C460`, clears material pointers, clears the world container, and resets chunk allocator state.

## FONT chunk

`sub_558C90(context, stream)` loads the whole FONT chunk into the runtime glyph table:

- Allocates `0x800` bytes with `sub_41EF00`.
- Stores the pointer at `context +0x10`.
- Copies the same pointer to global `dword_6DA354`.
- Reads 256 records.  Each record is four little-endian `u16` values, so the disk and runtime stride is 8 bytes.

```c
struct FontGlyph8 {
    uint16_t material_index;    // +0x00, passed as sub_435D10 arg0
    uint16_t y_center_offset;   // +0x02, draw y uses y - (value / 2)
    uint16_t advance_width;     // +0x04, used for text width and x advance
    uint16_t draw_height;       // +0x06, passed as glyph quad height
}; // 8 bytes, 256 entries
```

Confirmed consumers:

- `sub_436510(text)` measures a null-terminated string.  Space (`0x20`) is hardcoded to width `10`; other characters add `dword_6DA354[ch].advance_width`.
- `sub_436A20(ch)` measures one character.  `'#'` returns `3`, space returns `10`, otherwise it returns FONT `+0x04`.
- `sub_436550` and `sub_436A80` draw text by passing `material_index`, adjusted `x/y`, `advance_width`, and `draw_height` to `sub_435D10`.
- `sub_436A80` treats `#` and `=` as inline color/control markers in one text path, so those bytes are not always rendered as glyphs.

The extractor exports this as `font/summary.*`, `font/glyph_metrics.csv`, and `font/text_width_samples.csv`.  When TEXT material data is available, `glyph_metrics.csv` also cross-references each FONT `material_index` to the runtime material table and texture rectangle.

## AMPC chunk

AMPC is loaded only when the audio system is initialized (`dword_5834DC != 0`).  The WAD dispatch reads tag `AMPC`/`CPMA`, then calls `sub_558D70(context, stream)`.

`sub_558D70`:

- Reads one u32 into `context +0x24`.
- If that value is zero, writes `context +0x20 = 0` and stops.
- If nonzero, calls the shared audio/resource loader `sub_545350(context, stream, 4)`.

Case `4` of `sub_545350` confirms the disk format:

```text
u32 resource_count
for each resource:
    u32 resource_id_00
    u32 magic_04              // observed 0x69626D61 = "ambi"
    u32 payload_size_08
    u8  payload[payload_size]

u32 ambient_record_count
AmbientRecord40 ambient_records[ambient_record_count]
```

The first tested levels all carry three resource records.  The first payload starts with `pBAV`, the second with `pQES`, and the third appears to be the associated packed/sample payload.  The loader passes resource 0 and resource 2 to `sub_5472A0`, and resource 1 to `sub_5471F0`.

Confirmed 40-byte ambient record layout:

```c
struct AmbientRecord40 {
    int32_t  pos_x_fixed12;          // +0x00, used by sub_547C00 distance check
    int32_t  pos_y_fixed12;          // +0x04, not used by the confirmed horizontal-distance path
    int32_t  pos_z_fixed12;          // +0x08, used by sub_547C00 distance check
    uint32_t unknown_0C;             // +0x0C, zero in current samples
    uint32_t near_distance;          // +0x10
    uint32_t far_distance;           // +0x14
    uint32_t sound_id_flags;         // +0x18, low word is ambient sound id; bit 0x10000 has special/global-volume handling
    uint32_t target_volume;          // +0x1C
    uint32_t runtime_active_mask;    // +0x20, updated by sub_5458D0
    uint32_t runtime_current_level;  // +0x24, updated by sub_5458D0/sub_549A00
}; // 40 bytes
```

`sub_547C00(record)` computes a horizontal listener distance using `record +0x00` and `record +0x08` against globals `dword_5790B0`/`dword_5790B8`; Y is ignored in that path.  `sub_5458D0` compares that distance with `near_distance`/`far_distance`, scales `target_volume`, and starts/stops/updates the referenced ambient sound through `sub_5499A0`, `sub_549A00`, `sub_549A70`, and `sub_549AC0`.

The extractor exports this as `ampc/summary.*`, `ampc/resources.csv`, `ampc/resource_payloads/*.bin`, and `ampc/ambient_records_40.csv`.

## Core geometry record formats

Two closely related geometry record formats exist:

- `GeometryRecord84`: 132 bytes, used by `dword_5846EC` for TRAK/world geometry and many render/collision paths.
- `GeometryRecord8C`: 140 bytes, used by packed `CPTS/STPC` container sections and extended/skinned/morphed geometry paths.

### BRender source comparison notes

- The public BRender model structs do **not** match the WAD geometry records directly.  In the source tree, 32-bit `br_model` is 92 bytes, `br_vertex` is 40 bytes, and `br_face` is 40 bytes (`BRender/inc/model.h`).  The game chunks use 132-byte/140-byte geometry records, 24-byte vertices, and 28-byte triangles.
- The game triangle record still looks BRender-derived: it keeps three u16 vertex indices, a material pointer slot at runtime, and a face plane equation.  However, the game packs flags/material/equation differently than public `br_face`.
- BRender's internal prepared render format is a better conceptual match than public `br_model`.  `BRender/core/fw/formats.h` defines `v11model`/`v11group` with grouped faces by material, `vertex_numbers`, `edges`, `eqn`, `position`, `map`, `normal`, face colours, and vertex colours.  The game's geometry records appear to be a custom packed/static variant that can feed similar renderer concepts without storing a full public `br_model`.
- `BRender/core/v1db/prepmesh.c` confirms that BRender prepares models by grouping faces by material, copying vertex positions/maps/normals, copying face equations, and optionally building stored renderer geometry.  This explains why the game geometry carries precomputed bounds/cull data and face plane equations.
- `br_actor` (`BRender/inc/actor.h`) is not the same as the game's large `Actor340` runtime object.  The game actor embeds script VM fields, movement/state fields, and game-specific lists; BRender's actor is a smaller scene-graph node with model/material pointers and a `br_transform`.
- BRender scalar/angle conventions are useful but not always identical.  BRender can be built with fixed or float scalars (`BRender/inc/scalar.h`), and its `br_angle` uses 65536 units per full turn in the float macro path.  The game MAP object yaw values observed so far use 4096 units per full turn, so object angles are game-side units, not raw `br_angle`.
- BRender material names/flags are a strong naming source for TEXT/SPRT analysis.  `br_material` has `flags`, `map_transform`, `colour_map`, and mode bits such as two-sided, depth-write inhibition, blend modes, wrap/clamp/mirror, and colour-key toggles (`BRender/inc/material.h`).  The game's compact 20-byte runtime material table is not public `br_material`, but many render-state semantics likely descend from BRender material state.

Practical use: use BRender to name renderer concepts, material modes, actor hierarchy transforms, prepared-model fields, and possible library helper functions.  Do not rewrite WAD parsers to public BRender structs unless an executable loader explicitly proves that a chunk uses a BRender file/chunk format.

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

Relocates `GeometryRecord8C` records.  It has the same vertex/triangle/collision relocation as `sub_5563F0`, plus one important extra array before the vertex block:

```text
for each record:
  matrix_group_counts = cursor; cursor += 2 * transform_group_count; record+136 = matrix_group_counts
  vertices            = cursor; cursor += 24 * vertex_count;          record+112 = vertices
  triangles           = cursor; cursor += 28 * triangle_count;        record+116 = triangles
  block32             = cursor; cursor += 32 * (group0+group1+group2); record+128 = block32

Static records usually have base_vertex_count == vertex_count and transform_group_count == 0.
Skinned/matrix-group records usually have base_vertex_count == 0, transform_group_count > 0, and sum(matrix_group_counts) == vertex_count.
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


## SPRT sprite material-base chunk

`SPRT` does not store sprite pixels.  The pixels and UV rectangles live in the `TEXT` textures and runtime material table.  The confirmed part of `SPRT` is a material-table base index used by the sprite renderer.

### Loader behavior

The chunk dispatcher compares tag integer `0x53505254` (`SPRT`).  At `loc_558AD1`, the loader reads:

```text
0x00  u32 material_base_index  -> dword_5FF728
```

If `dword_6DA330 & 0x100000` is set, the loader then reads an optional table:

```text
+0x04  u32 optional_count
+0x08  u32 optional_values[optional_count] -> unk_5FCFA0
```

Current sample WADs only contain the 4-byte base value, so the optional table is confirmed from executable control flow but not yet observed in the tested files.

### Renderer use

`sub_425D40` consumes `dword_5FF728` while selecting a 20-byte material row from `dword_581154`.  The observed formula is:

```text
material_index = dword_5FF728 + sprite_id * 2 + variant_or_frame
material_ptr   = dword_581154 + material_index * 20
```

`sprite_id` is read from the sprite/runtime object at `+0x0C`.  `variant_or_frame` is usually a two-slot variant/frame value; when the object byte at `+0x2C` is set, the renderer indexes an inline byte table at `+0x2F` using `byte +0x05`.

Observed sample bases against parsed `TEXT` material counts:

| WAD | SPRT base | TEXT materials | Remaining materials | Paired sprite slots |
|---|---:|---:|---:|---:|
| `t1l1m001` | 780 | 986 | 206 | 103 |
| `t1l1m002` | 873 | 1079 | 206 | 103 |
| `t1l1m003` | 605 | 992 | 387 | 193 |
| `t1l1m004` | 577 | 957 | 380 | 190 |
| `t0i0m998` | 181 | 377 | 196 | 98 |
| `t0i0m000` | 366 | 389 | 23 | 11 |

The exporter writes `sprt/summary.txt`, `sprt/summary.json`, and `sprt/sprite_material_slots.csv`, mapping each derived two-material sprite slot to the corresponding parsed `TEXT` material rectangle and texture index.

## WFPC feature flags chunk

`WFPC` is a 4-byte feature/capability mask.  The loader branch at `loc_558B8B` reads the payload directly into `dword_6DA330`:

```text
+0x00  u32 flags -> dword_6DA330
```

Later chunk loaders and runtime paths test individual bits.  Confirmed or observed bits from current disassembly pass:

| Mask | Status | Consumer | Meaning |
|---:|---|---|---|
| `0x00000010` | confirmed | `sub_42AC50`, `loc_42BECC` | MAP has `final_optional_dword` before `final_u16`; otherwise `dword_6DA328` defaults to 200. |
| `0x00000080` | observed only | no confirmed `dword_6DA330` consumer yet | Active in all sampled WADs. |
| `0x00000100` | loader-confirmed, unobserved | `sub_42AB50`, `loc_42ABE8` | STPC has an extra tail count and repeated 16-byte records with variable 8-byte subrecords. |
| `0x00000200` | observed only | no confirmed consumer yet | Active in tested full level WADs. |
| `0x00000400` | observed only | no confirmed consumer yet | Active in several WADs; absent in `t1l1m003/t1l1m004`. |
| `0x00000800` | runtime-confirmed, unobserved | `sub_419676`, nearby init paths | Passed into `sub_424B60/sub_424B90` during render/camera initialization. |
| `0x00010000` | confirmed | `sub_42AC50`, `loc_42B273` | MAP includes optional 20-byte records and extra vertex-color blocks for marked tiles. |
| `0x00080000` | runtime-confirmed, unobserved | `sub_550E60` jump-table case 142 | Passed to `sub_54BBD0`; semantic name still unknown. |
| `0x00100000` | loader-confirmed, unobserved | `SPRT` branch at `loc_558AD1` | SPRT includes `optional_count` and a u32 table after `material_base_index`. |
| `0x00200000` | loader-confirmed, unobserved | `sub_42AC50`, `loc_42BBFB` | MAP includes a global chain/table structure at `dword_6D9C90/dword_6D9CC0`. |
| `0x00400000` | observed only | no confirmed consumer yet | Active only in `t1l1m001` among current samples. |
| `0x04000000` | loader-confirmed, unobserved | `sub_42AC50`, `loc_42BD57` | When the MAP chain table exists, each chain record includes an extra dword at runtime `+0x14`. |
| `0x08000000` | observed only | no confirmed `dword_6DA330` consumer yet | Active in all sampled WADs. |
| `0x10000000` | confirmed | `sub_42AC50`, `loc_42B335`; `sub_42C790` | MAP allocates wider per-tile vertex-list pointers and uses optional20 records in follow-up processing. |

Observed sample values:

| WAD | WFPC flags | Active masks |
|---|---:|---|
| `t0i0m000` | `0x08000490` | `0x10`, `0x80`, `0x400`, `0x08000000` |
| `t0i0m998` | `0x08000080` | `0x80`, `0x08000000` |
| `t0i0m999` | `0x08000080` | `0x80`, `0x08000000` |
| `t1l1m001` | `0x18410690` | `0x10`, `0x80`, `0x200`, `0x400`, `0x10000`, `0x00400000`, `0x08000000`, `0x10000000` |
| `t1l1m002` | `0x18010690` | `0x10`, `0x80`, `0x200`, `0x400`, `0x10000`, `0x08000000`, `0x10000000` |
| `t1l1m003` | `0x18010290` | `0x10`, `0x80`, `0x200`, `0x10000`, `0x08000000`, `0x10000000` |
| `t1l1m004` | `0x180102D0` | `0x10`, `0x40`, `0x80`, `0x200`, `0x10000`, `0x08000000`, `0x10000000` |

The extractor writes `wfpc/summary.txt`, `wfpc/summary.json`, and `wfpc/flags.csv`.  `parse_map_full_exe` now receives `assume_optional20` from `WFPC & 0x10000` and `assume_final_dword` from `WFPC & 0x10`, matching the executable's gated MAP read order.

## LGPC localized dialogue/text chunk

`LGPC` is the localized text/dialogue table.  It is unrelated to `LGHT` lighting despite the similar prefix.  The dispatcher compares tag integer `0x4C475043` and calls `sub_558DB0`.

### Loader behavior

`sub_558DB0` reads:

```text
+0x00  u32 row_count_minus_one -> dword_6DA338, then incremented
+0x04  u32 column_count
+0x08  u32 unknown_header_08   -> read into a stack local; no confirmed consumer yet

u32 blob_sizes[row_count * column_count]
u8  blobs[row_count * column_count][blob_sizes[i]]
```

Runtime allocation:

```text
dword_6DA338 = row_count_minus_one + 1
dword_6DA334 = pointer matrix, row_count * column_count entries
```

The table is stored column-major:

```text
entry_index = column * row_count + row
```

### Runtime lookup

`sub_40D4C0` reads a dialogue index from the script/runtime stream, then:

```text
voice_or_id_entry = dword_6DA334[(dialogue_index + 1) * dword_6DA338 - 1]
text_entry        = dword_6DA334[dialogue_index * dword_6DA338 + dword_584F04]
```

The last row is treated as a `#...` voice/id tag.  If it begins with `'#'`, the code strips the `#`, parses the following number through `sub_40D890`, and calls the audio/speech path through `sub_546620`.  The selected visible string row is controlled by `dword_584F04`; in the current Italian PC WAD samples row `0` is the displayed localized string and row `1` is the `#...` tag.

Observed samples:

| WAD | Size | Rows | Columns | `unknown_header_08` | Payload bytes |
|---|---:|---:|---:|---:|---:|
| `t0i0m000` | 12 | 2 | 0 | 0 | 0 |
| `t0i0m998` | 12 | 2 | 0 | 0 | 0 |
| `t0i0m999` | 12 | 2 | 0 | 0 | 0 |
| `t1l1m001` | 6871 | 2 | 120 | 1474 | 5899 |
| `t1l1m002` | 5411 | 2 | 97 | 1155 | 4623 |
| `t1l1m003` | 2910 | 2 | 61 | 602 | 2410 |
| `t1l1m004` | 5397 | 2 | 96 | 1154 | 4617 |

Exporter outputs:

```text
lgpc/summary.txt
lgpc/summary.json
lgpc/entries.csv          raw row/column matrix
lgpc/dialogue_lines.csv   row 0 text paired with final-row voice/id tag
```

## SRPC / CPRS streamed speech chunk

`SRPC` is the human-readable name used by this project for the WAD chunk whose bytes appear on disk as `CPRS`.  The reversal happens because the original PC executable compares chunk identifiers as little-endian 32-bit integers.  The dispatcher compares the value `0x53525043`, which is the byte sequence `43 50 52 53` (`CPRS`) in the file.

The dispatcher calls:

```c
sub_545350(level_context, stream, 2);
```

This means `sub_545350` case `2` is the `SRPC`/`CPRS` loader.

### What SRPC stores

`SRPC` does **not** store the speech audio bytes directly.  It stores a table of slices into an external CVS stream file, normally:

```text
Music/ENGLISH.CVS
```

A practical way to think about it:

- `SRPC` is the speech index inside the WAD.
- `ENGLISH.CVS` is the large speech data bank.
- Each `SRPC` entry says: "speech N starts at byte offset X in the CVS file and has byte size Y".
- The game loads that slice and sends it to the Argonaut audio layer.

### Loader behavior: `sub_545350(..., case 2)`

Equivalent pseudocode:

```c
uint32_t count;
read_u32(stream, &count);

SRPCEntry16 *entries = alloc(count * 16);
for (uint32_t i = 0; i < count * 4; i++)
    read_u32(stream, ((uint32_t *)entries) + i);

sub_5465D0(entries, count);
```

The loader first reads a 32-bit entry count.  It then reads `count` fixed-size records, each 16 bytes long.  No nested compression or relocation has been observed inside the WAD chunk itself.

### Runtime registration: `sub_5465D0`

```c
SRPCEntry16 *dword_6D91C4; // base pointer to entries
uint32_t     dword_6D91C8; // entry count
uint32_t     dword_6D91D4; // loaded flag

void *sub_5465D0(SRPCEntry16 *entries, uint32_t count) {
    dword_6D91C4 = entries;
    dword_6D91C8 = count;
    dword_6D91D4 = 1;
    return entries + count;
}
```

The important point is that the game registers the whole table globally.  Later playback does not search by filename; it indexes this table by a speech id.

### Disk structure

```c
#pragma pack(push, 1)
struct SRPCChunkDisk {
    uint32_t count;
    SRPCEntry16 entries[count];
};

struct SRPCEntry16 {
    uint32_t unknown_00;       // observed as dialogue/resource-id-like value
    uint16_t rate_or_timing;   // sample-rate scalar; 2048 -> 22050 Hz
    uint16_t unknown_06;       // usually 0 in observed files
    uint32_t cvs_offset;       // byte offset into Music/ENGLISH.CVS
    uint32_t cvs_size;         // byte size before runtime 0x800 alignment
};
#pragma pack(pop)
```

Field explanation for non-specialists:

| Field | Meaning |
|---|---|
| `count` | Number of speech-table entries. |
| `unknown_00` | Looks like a dialogue or resource identifier.  It is useful in exported filenames, but the confirmed playback path indexes by table position. |
| `rate_or_timing` | A scalar converted by the game into an audio sample rate. |
| `unknown_06` | Usually zero in tested files.  No confirmed consumer yet. |
| `cvs_offset` | Start byte of this speech clip inside the external `.CVS` file. |
| `cvs_size` | Number of meaningful bytes in the speech clip before the game aligns the load size. |

### Playback behavior: `sub_546620`

`sub_546620` validates the requested speech id against `dword_6D91C8`, selects `dword_6D91C4[speech_id]`, opens `Music/ENGLISH.CVS`, and sends the referenced slice to AAL:

```c
entry = &dword_6D91C4[speech_id];
stream_ptr  = lpBaseAddress + entry->cvs_offset;
stream_size = (entry->cvs_size + 0x7FF) & ~0x7FF;
AAL_LoadResourceType(stream_ptr, stream_size, 0x15, 0);
```

The runtime aligns the loaded size upward to a `0x800` byte boundary.  The table's `cvs_size` still represents the meaningful clip size; the extra aligned bytes are padding/loading granularity.

The same function copies `rate_or_timing` to `word_6D93E4` and derives a sample-rate-like value:

```text
sample_rate_hz = rate_or_timing * 44100 / 4096
```

Common observed value:

```text
rate_or_timing = 2048 -> 22050 Hz
```

### CVS stream codec

The referenced `.CVS` slices match PlayStation/SPU ADPCM audio:

- Each frame is 16 bytes.
- Each frame decodes to 28 mono PCM samples.
- Byte 0 is the filter/shift header.
- Byte 1 is the frame flags byte.
- Bytes 2..15 store 28 4-bit ADPCM nibbles.

The project decodes these slices to mono 16-bit PCM WAV files.  Optional MP3 conversion is available when `ffmpeg` is installed and `--srpc-mp3` is requested.

### Exporter outputs

When `SRPC` is present, the extractor writes:

```text
srpc/srpc_entries.csv
srpc/summary.txt
srpc/cvs_slices/*.cvs      when a CVS file is found/provided
srpc/wav/*.wav             when a CVS file is found/provided
srpc/mp3/*.mp3             optional, requires ffmpeg and --srpc-mp3
```

The raw WAD chunk is still preserved separately as `raw/srpc.bin` when raw export is enabled.

The extractor searches common CVS locations next to the WAD, such as `Music/ENGLISH.CVS`.  A specific file can be supplied with `--srpc-cvs PATH`.

### Remaining SRPC unknowns

- `SRPCEntry16.unknown_00`: often looks like a dialogue/resource id and is useful in filenames, but the confirmed playback path uses the table index.
- `SRPCEntry16.unknown_06`: observed as zero in tested samples; no confirmed consumer yet.
- Exact AAL resource type `0x15` name is unknown; behavior matches streamed speech/voice.

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

- STPC geometry parsing now follows the executable-confirmed `sub_42AB50`/`sub_41F770` cursor layout instead of relying on blind scanning.
- The exporter now finds static records and matrix-group/skinned records, including records where `base_vertex_count == 0` and `transform_group_count > 0`.
- STPC OBJ exports include material/UV output where derivable from runtime materials.
- The exporter writes `script_geometry_refs.csv` by scanning the script tail for opcode `0x00B2` references to decoded geometry-record offsets.
- World export now binds MAP object placements to STPC meshes through the confirmed VM pattern `0x00B2 <stpc-relative GeometryRecord8C offset>` followed by opcode `0x54` (`sub_553C10`, set actor geometry/model).
- STPC object definition parsing is partial but no longer purely heuristic: mesh binding, child-spawn inheritance, several actor movement opcodes, and Section4 route-transform application are decoded enough for the current world OBJ export.

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

Confirmed export coordinate basis:

- TRAK terrain placement uses tile-definition fixed12 `pos_x`, `pos_y`, and **negated** `pos_z`.
- MAP object actor positions are copied directly into `Actor340 +0x30/+0x34/+0x38` by `sub_54CFC0`.
- Terrain queries convert actor Z into terrain space by shifting and negating it (`mov eax, [actor+0x24]`, `sar eax, 0x0C`, `neg eax` in the relevant query path).  The world exporter therefore uses terrain as the reference orientation and exports STPC actor/object Z as `-actor_z`.
- A centered terrain Z mirror was tested and rejected for the normal world export; the correct default is no centered mirror, no global object Z offset, and one final whole-world OBJ Z flip so terrain and STPC objects are mirrored together without changing their relative alignment.

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

Confirmed Section4 transform use:

- Opcode `0xFE` dispatches to `sub_54DFE0`.
- `sub_54DFE0` reads the actor's `+0x120` Section4 pointer and copies Section4 runtime fields into the active actor transform:
  - `section4 +0x18` -> actor `pos_x` (`+0x30`) after `<< 12`
  - `section4 +0x1C` -> actor `pos_y` (`+0x34`) after `<< 12`
  - `section4 +0x20` -> actor `pos_z` (`+0x38`) after `<< 12`
  - `section4 +0x0C` -> actor `rot_y` (`+0x24`) after `<< 12`
- This explains the object-placement outliers where the MAP object origin is correct for initial spawn, but the visible mesh is offset to a Section4 route/waypoint transform before model binding.

### Section3 runtime table

`sub_42AC50` reads Section3 as 90-byte disk records and expands each entry to a 92-byte runtime record (`0x5C` stride).  The disk record is mostly unaligned: after disk `+0x38` the loader reads several u32 fields from offsets `+0x3A`, `+0x3E`, `+0x42`, and so on.

```text
Disk offset   Size   Runtime offset   Notes
0x00          u32    +0x00            unnamed
0x04          u32    +0x04            unnamed
0x08          u32    +0x08            unnamed
0x0C          u32    +0x0C            unnamed
0x10          u32    +0x10            unnamed
0x14          u32    +0x14            unnamed
0x18          u32    +0x18            unnamed
0x1C          u32    +0x1C            unnamed
0x20          u32    +0x20            flags; low byte bit 0x08 sets dword_584644 to this record
0x24          u32    +0x24            unnamed
0x28          u32    +0x28            STPC-relative pointer; 0 stays NULL, nonzero becomes dword_6D9DBC + value
0x2C          u32    +0x2C            unnamed
0x30          u32    +0x30            unnamed
0x34          u32    +0x34            unnamed
0x38          u16    +0x38            unnamed
0x3A          u32    +0x3C            range/value A minimum
0x3E          u32    +0x40            range/value B minimum
0x42          u32    +0x44            range/value A maximum raw
0x46          u32    +0x48            range/value B maximum raw
0x4A          u32    +0x4C            unnamed
0x4E          u32    +0x50            unnamed
0x52          u16    +0x54            unnamed
0x54          u16    +0x56            unnamed
0x56          u32    +0x58            category/type-like value
```

After loading the four range fields, the loader applies a fallback: if runtime `+0x44 <= +0x3C`, it replaces `+0x44` with `+0x3C + (+0x3C >> 1)` and replaces `+0x48` with `+0x40 + (+0x40 >> 1)`.  The exporter now writes both raw and runtime-adjusted range values in `map_full/section3_records_90.csv`.

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
- `wfpc/summary.txt`: copied `dword_6DA330` feature mask and active/unknown masks.
- `wfpc/flags.csv`: per-bit WFPC diagnostics with confirmed consumers where known.
- `lgpc/entries.csv`: decoded localized text matrix as stored by `sub_558DB0`.
- `lgpc/dialogue_lines.csv`: row-0 visible text paired with final-row `#...` voice/id tags.
- `lights/lights.csv`: typed directional/point/negative point lights with runtime conversions.
- `trak/table_cde_entries.csv`: decoded `CollisionEntry32` rows.
- `stpc/manifest.csv`: table-decoded `GeometryRecord8C` records with exact offsets, counts, Block32 totals, and matrix-group arrays.
- `stpc/script_geometry_refs.csv`: opcode `0x00B2` references from the STPC script tail to decoded geometry-record offsets.
- `sprt/summary.txt`: confirmed `SPRT` material-base value and derived material-slot counts.
- `sprt/sprite_material_slots.csv`: derived sprite slots mapped to `TEXT` material indices, texture pages, rectangles, and flags.
- `world/map_object_instances.csv`: MAP object placements plus spawn/script metadata used by STPC object binding, including decoded Section4 route transforms when present.
- `world/stpc_mesh_reference_hits.csv`: exact per-object STPC mesh binds plus decoded script actor offsets/yaw source used by world OBJ export.
- `world/objects_primary.obj`: one selected placed STPC mesh per MAP object, with materials/textures and decoded script placement offsets.
- `world/terrain_and_objects.obj`: textured terrain plus primary placed STPC objects in one OBJ.

## Remaining high-value unknowns

1. Exact semantics of `MapObjectDisk58` script data. `script_offset` points into `dword_6D9DBC`, but the bytecode/data structure there still needs further decoding.
2. Exact meaning of `MapObjectDisk58.flags` bits besides `0x0002` skip-initial-spawn.
3. Exact meaning of `section2` and the non-transform fields in `section4`; Section4 position/yaw use through opcode `0xFE` is confirmed.
4. The final `LGHT` type 2/4 byte `falloff_or_mode` needs lighting evaluator xrefs for a precise name.
5. `GeometryRecord84` fields `+0x00`, `+0x04`, `+0x08`, and `+0x7E` — now have binary observations (see below), but semantic names not yet confirmed.
6. STPC object-definition structure and script VM opcodes partially decoded (see below); geometry table parsing, mesh binding, child-transform inheritance, and Section4 route transforms are confirmed, but complete actor/object behavior still needs VM semantics.
7. Remaining material tables `dword_581144` and `dword_58114C` are used by render state/texture refs but are not fully named.
8. `SPRT` optional table behind `dword_6DA330 & 0x100000` is loader-confirmed but not observed in current sample WADs; high-level sprite records and animation/frame command semantics remain unnamed.
9. Several observed WFPC bits are still unnamed: `0x40`, `0x80`, `0x200`, `0x400`, `0x00400000`, and `0x08000000`.
10. `LGPC +0x08` is read by the loader but not consumed in the confirmed path yet; `dword_584F04` row-selection semantics need a precise name.

## Recommended next reverse-engineering targets

1. Script VM opcode handlers in `funcs_54D1B8` (opcodes > 0x44) — many schemas still need field-level names.
2. Consumers of `MapObjectRuntime72 +0x28` and `+0x3C` to name Section2 and Section4.
3. Lighting evaluator functions that iterate the active light list and read `RuntimeLight112 +0x50..+0x68`.
4. Finish naming the `sub_550E60` / `sub_5509F0` function-dispatch ids used by STPC opcodes.  The calling convention is decoded, but most switch-case semantic names are still pending.
5. Sprite setup structures that feed `sub_425D40`, especially fields `+0x05`, `+0x0C`, `+0x2C`, and the inline variant table at `+0x2F`.
6. Xrefs or indirect consumers for observed-only WFPC bits, especially always-on `0x80` and `0x08000000`.
7. `dword_584F04` writes/initialization to identify whether LGPC row selection is language, text style, or channel selection.

---

## STPC / CPTS container top-level layout (confirmed from `sub_42AB50`)

`sub_42AB50` loads the packed STPC blob into `dword_6D9DBC`.  The blob is read all at once with `sub_415A90`, then `sub_42AB50` walks a cursor through the buffer.  The key correction is that the executable relocates one `GeometryRecord8C` at a time.  Therefore the disk layout is not "all headers first, all variable data later".  Each geometry header is immediately followed by its own variable-length arrays.

```text
STPC blob layout, tested PC WADs, all little-endian:

  u32 stored_count
      Observed to be geometry_record_count + 1 in tested files.

  repeat stored_count - 1 times:
      GeometryRecord8C header, 0x8C bytes

      u16 matrix_group_vertex_counts[header.transform_group_count]
          Present only when transform_group_count > 0.
          sub_41FB30 uses these counts to split the source vertex array into
          contiguous batches transformed by different matrices.

      Vertex24 vertices[header.vertex_count]

      Triangle28 triangles[header.triangle_count]

      Block32 blocks[
          header.collision_group0_count +
          header.collision_group1_count +
          header.collision_group2_count
      ]

  u32 section2_count
  GeometryAnimRecord32 section2[section2_count]

  raw script / constants / string / object-definition tail
```

Confirmed table-walk results:

| WAD | STPC size | Stored count | Geometry records | Geometry end | Section2 count | First known MAP script offset |
|---|---:|---:|---:|---:|---:|---:|
| `t1l1m001.wad` | `0x43934A` | 33 | 32 | `0x3321E` | 0 | `0x4210E2` |
| `t1l1m002.wad` | `0x381B86` | 57 | 56 | `0x4351E` | 0 | `0x36547E` |

The older assumption was:

```text
u32 count
count * GeometryRecord8C headers
all vertices/triangles/blocks later
```

That model fails because it places section 2 near `0x1210` in `t1l1m001`, but the executable-style cursor walk proves geometry actually continues until `0x3321E`.  It also misses dynamic/skinned records because it treats `+0x84` as a 32-bit duplicate vertex count.  The real fields are two `u16`s:

```c
uint16_t base_vertex_count;       // +0x84
uint16_t transform_group_count;   // +0x86
uint16_t *group_vertex_counts;    // +0x88, relocated runtime pointer
```

### STPC script geometry references

The script/object-definition tail contains opcode `0x00B2` instructions that reference geometry by STPC-relative offset:

```text
u16 opcode = 0x00B2
u16 zero_or_arg
u32 stpc_relative_geometry_offset
```

Scanning this pattern after the geometry table confirms that every table-decoded geometry record in the two tested WADs is referenced by at least one script instruction:

| WAD | `0x00B2` geometry references | Unique records referenced |
|---|---:|---:|
| `t1l1m001.wad` | 41 | 32 / 32 |
| `t1l1m002.wad` | 70 | 56 / 56 |

This is strong independent evidence that the cursor parser is aligned correctly.

When `script_offset` in a MAP object is resolved by `sub_553630`:

```c
// positive offset → absolute runtime pointer into STPC blob
if (script_offset >= 0)
    runtime_ptr = dword_6D9DBC + script_offset;

// negative offset → index into global object pool dword_6DA324
else {
    idx = ~script_offset;               // = -(script_offset + 1)
    if (idx < dword_6DA31C)
        runtime_ptr = dword_6DA324[idx];
    else
        runtime_ptr = NULL;
}
```

A `script_offset` of zero resolves to the very start of the STPC blob (`dword_6D9DBC`), which is the first GeometryRecord8C record header.  Use an existing object's `script_offset` as a template rather than guessing.

### STPC object mesh binding and placement transforms

The current world OBJ exporter uses the following confirmed subset of the STPC VM:

| Opcode | Handler | Confirmed effect for world export |
|---:|---|---|
| `0x44` | `sub_553610` | Push signed 16-bit immediate onto actor stack.  Commonly used for fixed12 movement amounts. |
| `0x54` | `sub_553C10` | Pop a pointer and store it in `actor+0x10`; this binds the actor's current geometry/model. |
| `0x5F` | `sub_550590` | Pop amount; move actor along one local horizontal axis. |
| `0x60` | `sub_5505C0` | Pop amount; move actor along the opposite local horizontal axis. |
| `0x61` | `sub_550720` | Pop amount; move actor along the other local horizontal axis. |
| `0x62` | `sub_550750` | Pop amount; opposite of `0x61`. |
| `0x94` | `sub_5531D0` | Spawn child actor after `sub_553170` reads inline spawn-state words; child inherits current actor transform. |
| `0xB2` | `sub_553630` | Read next dword and push resolved pointer. Positive values are STPC-relative (`dword_6D9DBC + value`). |
| `0xD4` | `sub_553EF0` | Consume two dwords and set an alternate script pointer at actor `+0x18`; no actor placement change by itself. |
| `0xE0` | `sub_553230` | Spawn child actor variant after `sub_553170`; child inherits current actor transform. |
| `0xE3` | `sub_550690` | Pop amount; yaw-relative horizontal move. |
| `0xE4` | `sub_550600` | Pop amount; opposite yaw-relative horizontal move. |
| `0xFE` | `sub_54DFE0` | Copy Section4 route transform into actor position/yaw (see Section4 notes). |
| `0x103` | `sub_5508F0` | Pop amount; add to actor Y (`+0x34`). |
| `0x104` | `sub_550940` | Pop amount; subtract from actor Y (`+0x34`). |
| `0x125` | `sub_550790` | Pop amount; yaw-relative horizontal strafe/move. |
| `0x126` | `sub_550820` | Pop amount; opposite of `0x125`. |

The exporter only treats a `0xB2` operand as a mesh when a later `0x54` binds that pointer as the current actor model.  This avoids the earlier false positives from blind u32 scanning.

Child actors matter for placement: parent scripts can move the actor, spawn a child with `0x94`/`0xE0`, and the mesh bind can occur inside the child script.  In that case the visible mesh should use the inherited child transform, not just the parent MAP object origin.

Section4 route transforms matter too: if `0xFE` executes before the mesh bind, the visible actor position/yaw comes from the referenced Section4 record rather than the initial MAP object position.

---

## GeometryRecord84 unknown fields — binary observations

From `t1l1m001` STPC (`stored_count=33`, `geometry_record_count=32`):

| Field | Offset | Record 0 raw value | Interpreted |
|---:|---:|---|---|
| `unknown_00` | +0x00 | `0x00000000` | u32 = 0 |
| `unknown_04` | +0x04 | `0xBCCCCCBD` | float ≈ −0.025 |
| `unknown_08` | +0x08 | `0x80000000` | float = −0.0 |
| `vertex_count` | +0x6C | `0x0010` | 16 |
| `triangle_count` | +0x6E | `0x001A` | 26 |
| `coll_group0` | +0x78 | `0x0002` | 2 |
| `coll_group1` | +0x7A | `0x0000` | 0 |
| `coll_group2` | +0x7C | `0x0000` | 0 |
| `unknown_7E` | +0x7E | `0x000B` | u16 = 11 |

From `t1l1m001` TRAK (`record_count=127`):

| Field | Record 0 | Record 1 |
|---:|---|---|
| `unknown_00` | 0 | 0x3B0F5C2C (noise) |
| `unknown_04` | float ≈ −2.75 | float ≈ −2.76 |
| `unknown_08` | float = −0.0 | float ≈ +0.51 |
| `vertex_count` | 4 | 10 |
| `triangle_count` | 0 | 8 |

Observations:

- `unknown_00`: Consistently 0 in record 0; appears as noise/uninitialized in later records.  Possibly a sort key or padding not written by `sub_5563F0`.
- `unknown_04` / `unknown_08`: Small floats that differ per record and appear correlated with geometry height range.  Candidate meanings: Y-axis culling bias, LOD distance near/far planes, or bounding-sphere center/radius.  They are read and compared by `sub_401000` in float comparisons adjacent to the frustum culler — but the exact role is not yet confirmed.
- `unknown_7E` (STPC only): Value 11 in the first STPC record; 0 in TRAK records.  Not obviously a count of any known sub-structure.  May be a render-batch hint or a sub-type discriminator used by `sub_41FB30`.

---

## Script VM — opcode table and dispatch

The main VM loop `sub_54D180` fetches 32-bit little-endian instruction words from `[actor+0x00]` (the script PC):

```text
bits  0–15   opcode index (0x00 – 0x44 → funcs_54D1AB; above 0x44 → funcs_54D1B8)
bits 16–31   signed 16-bit immediate argument (sign-extended to 32 bits)
```

Opcodes 0x00–0x44 pass both `(actor, imm16)` to the handler (callee cleans 8 bytes).
Opcodes above 0x44 pass only `actor` (callee cleans 4 bytes).

### Complete `funcs_54D1AB` table (opcodes 0x00–0x44, confirmed from asm line 438973)

```text
opcode  handler         notes (from sub analysis)
──────  ──────────────  ──────────────────────────────────────────────────────
0x00    nullsub_2       no-op
0x01    sub_54FA50      set/clear bit 0x01000000 in actor+0xE8 (imm16≠0 → set)
0x02    sub_553850      stream scanner: reads count, then u16 values; skips +4
                          extra bytes when (u16 + 0x0101) == 0x0146 or 0x01EB
0x03    sub_5537F0      similar scanner; increments dword_6D9DB8 by 0x0C
                          (likely script stack-depth tracker)
0x04    sub_553710      load value from locals array [actor+0xF4][imm16], push
0x05    sub_5537B0      load from [actor+0xF4 + imm16*4], push via sub_54BBD0
0x06    sub_5536B0      load from global object table dword_6D9E8C[imm16*4], push
0x07    sub_552AB0      call sub_550E60(actor, imm16)
0x08    sub_5536F0      push address of [actor+0xF4 + imm16*4] (load-address variant)
0x09    sub_553790      push address via [actor+0x00 + imm16*4] (script-area relative)
0x0A    sub_553690      push address of global slot dword_6D9E8C[imm16]
0x0B    sub_552AD0      call sub_5509F0(actor, actor, imm16); push returned pointer/value
0x0C    sub_54FC40      (unknown)
0x0D    sub_54DBE0      zero the memory cell at actor+0xF8+imm16*16
0x0E    sub_54DC20      set high bit (0x80000000) of cell at actor+0xF8+imm16*16
0x0F    sub_54DC00      clear high bit (AND 0x7FFFFFFF) of same cell
0x10    sub_553D40      advance cursor at [esi] by imm16*4; set actor flag bit 0x02
0x11    sub_553D10      advance cursor at [esi] by imm16*4 (no flag change)
0x12    sub_553E10      conditional advance: if sub_54BC00==0, advance + set 0x02
0x13    sub_553EB0      conditional advance: if sub_54BC00≠0, advance (no flag)
0x14    sub_553E50      advance if sub_54BC00==0, no flag
0x15    sub_553E80      advance if sub_54BC00≠0, no flag
0x16    sub_553D80      add imm16*4 to integer at dereferenced pointer
0x17    sub_550060      array search: walks indexed structure, matches 16-bit keys
0x18    sub_553750      load array element value from [actor+0x0C]→[0xF4][imm16*4]
0x19    sub_553770      push address of same array element (LEA variant of 0x18)
0x1A    sub_552AF0      function call via sub_550E60 with actor+0x0C context
0x1B    sub_553730      function call via sub_5509F0; return value pushed
0x1C    sub_552D20      if dword_6D9E1C exists, call sub_550E60(actor, dword_6D9E1C, imm16), else push 0
0x1D    sub_552D50      if dword_6D9E1C exists, call sub_5509F0(actor, dword_6D9E1C, imm16), push result, else push 0
0x1E    sub_552B60      if dword_6D9E28 exists, call sub_550E60(actor, dword_6D9E28, imm16), else push 0
0x1F    sub_552B90      if dword_6D9E28 exists, call sub_5509F0(actor, dword_6D9E28, imm16), push result, else push 0
0x20    sub_552C40      if dword_6D9E30 exists, call sub_550E60(actor, dword_6D9E30, imm16), else push 0
0x21    sub_552C70      if dword_6D9E30 exists, call sub_5509F0(actor, dword_6D9E30, imm16), push result, else push 0
0x22    sub_54D200      (unknown)
0x23    sub_54D220      (unknown)
0x24    sub_552BD0      if dword_6D9E34 exists, call sub_550E60(actor, dword_6D9E34, imm16), else push 0
0x25    sub_552C00      if dword_6D9E34 exists, call sub_5509F0(actor, dword_6D9E34, imm16), push result, else push 0
0x26    sub_552B10      call sub_550E60(actor, dword_6D9E24, imm16)
0x27    sub_552B30      call sub_5509F0(actor, dword_6D9E24, imm16); push returned pointer/value
0x28    sub_552CB0      if dword_6D9E2C exists, call sub_550E60(actor, dword_6D9E2C, imm16), else push 0
0x29    sub_552CE0      if dword_6D9E2C exists, call sub_5509F0(actor, dword_6D9E2C, imm16), push result, else push 0
0x2A    sub_54E8E0      (unknown)
0x2B    sub_553DA0      (unknown)
0x2C    nullsub_2       no-op
0x2D    nullsub_2       no-op
0x2E    nullsub_2       no-op
0x2F    sub_54F720      (unknown)
0x30    sub_54FA80      (unknown)
0x31    sub_54E090      (unknown)
0x32    sub_54DD90      (unknown)
0x33    sub_54DD30      (unknown)
0x34    sub_54DD60      (unknown)
0x35    nullsub_2       no-op
0x36    nullsub_2       no-op
0x37    sub_553920      pop stack; store into sub_5509F0(actor, dword_6D9E1C, imm16) if dword_6D9E1C exists
0x38    sub_553950      pop stack; store into sub_5509F0(actor, dword_6D9E28, imm16) if dword_6D9E28 exists
0x39    sub_553980      pop stack; store into sub_5509F0(actor, dword_6D9E30, imm16) if dword_6D9E30 exists
0x3A    sub_5539B0      pop stack; store into sub_5509F0(actor, dword_6D9E34, imm16) if dword_6D9E34 exists
0x3B    sub_5539E0      pop stack; store into sub_5509F0(actor, dword_6D9E2C, imm16) if dword_6D9E2C exists
0x3C    sub_54D240      (unknown)
0x3D    sub_553A10      pop stack; store into sub_5509F0(actor, dword_6D9E24, imm16)
0x3E    sub_553A40      pop stack; store into [actor+0x0C]->[0xF4][imm16]
0x3F    sub_553A60      pop stack; store into sub_5509F0(actor, actor+0x0C, imm16)
0x40    sub_553A90      pop stack; store into sub_5509F0(actor, actor, imm16)
0x41    sub_553AC0      pop stack; store into [actor+0xF4][imm16]
0x42    sub_553AE0      pop stack; store into [actor+0x00][imm16]
0x43    sub_553B00      pop stack; store into global slot dword_6D9E8C[imm16]
0x44    sub_553610      push signed imm16 onto actor stack
```

### Script VM actor fields used by known opcodes

| Actor field | Opcode(s) | Role |
|---|---|---|
| `+0x00` (script_pc) | VM loop, 0x09 | instruction pointer; also used as base for 0x09 offset |
| `+0xE8` (flags0) | 0x01, VM loop | bit 0x12 = halt/pause; bit 0x01000000 toggled by 0x01 |
| `+0x104` / `+0x108` | `sub_54BBD0`, `sub_54BC00`, many opcodes | VM value-stack pointer and stack depth/count |
| `+0xF4` (mem_base) | 0x04, 0x05, 0x08, 0x18, 0x19, 0x3E, 0x41 | locals array base pointer |
| `+0xF8` | 0x0D, 0x0E, 0x0F | cell array base (16-byte stride) |

### STPC VM stack and role-pointer model

`sub_54BBD0(actor, value)` pushes a 32-bit value to the VM stack at `actor+0x104` and increments `actor+0x108`.  `sub_54BC00(actor)` is the exact inverse: it decrements `actor+0x108`, backs `actor+0x104` up by 4, and returns the popped dword.

The decoded `0x37..0x43` group is a store family.  These opcodes pop a stack value and write it either through `sub_5509F0` into a role actor's property/function slot, directly into a local array, directly into the script-relative memory area, or into the global 256-entry table `dword_6D9E8C`.

Role pointers used by the store/load/function-call families:

| Global | Setter | Confirmed opcode consumers | Current role name |
|---|---|---|---|
| `dword_6D9E1C` | `sub_550140` | 0x1C, 0x1D, 0x37 | current/primary actor pointer; setter ORs actor flag byte with `0x0800` |
| `dword_6D9E24` | `sub_550130` | 0x26, 0x27, 0x3D | active list/root actor pointer |
| `dword_6D9E28` | `sub_5500F0` | 0x1E, 0x1F, 0x38 | highlighted/target actor pointer; setter also sets actor flag `0x08000000` |
| `dword_6D9E2C` | `sub_550110` | 0x28, 0x29, 0x3B | auxiliary role actor pointer |
| `dword_6D9E30` | `sub_5500E0` | 0x20, 0x21, 0x39 | auxiliary role actor pointer |
| `dword_6D9E34` | `sub_5500D0` | 0x24, 0x25, 0x3A | auxiliary role actor pointer |
| `dword_6D9E8C[256]` | 0x43, cleared by `sub_5536D0` | 0x06, 0x0A, 0x43 | script global variable/object table |

These opcodes are important for full IDE-grade script editing, but they do not directly bind geometry.  The world exporter still only needs the already-confirmed placement subset: stack constants/pointers, `0xB2` STPC-relative pointer load, `0x54` model bind, child-spawn inheritance, movement opcodes, and MAP Section4 route application.

### Actor spawn variants

Three confirmed callers of the main spawn function `sub_54BFC0`:

| Function | Lines | Behavior |
|---|---|---|
| `sub_5531D0` | ~385520 | Simple clone, spawn_keep_owner=0 |
| `sub_553230` | ~385565 | Simple clone, spawn_keep_owner=1 |
| `sub_5533F0` | ~385772 | Complex: decompresses transform matrix from geometry record; uses fixed-point FPU math to convert float positions to actor coordinates before spawning |

`sub_553170` (called from both `sub_5531D0` and `sub_553230`) reads 6 sequential u32 values from the STPC object-definition stream and populates the spawn-state runtime block.

For world placement, both child-spawn variants inherit the current parent actor transform.  If the parent script has already applied movement opcodes or a Section4 route transform, meshes bound inside the child script must use that inherited transform rather than the original MAP object origin.

---

## MAP Section4 disk format (confirmed from `sub_42AC50`)

The 34-byte disk records are read in this order and expanded to 48-byte runtime records:

```text
Disk offset   Size   Runtime offset   Notes
0x00          u32    +0x00            raw next/link flag; nonzero becomes pointer to next record
0x04          u32    +0x04            raw prev/link value; overwritten with previous pointer when chained
0x08          u16    +0x08            small_a (zero-extended to u32)
0x0A          u16    +0x0C            yaw/angle units used by opcode 0xFE
0x0C          u16    +0x10            small_c (zero-extended to u32)
0x0E          u32    +0x18            route/waypoint X
0x12          u32    +0x1C            route/waypoint Y
0x16          u32    +0x20            route/waypoint Z
0x1A          u32    +0x28            unnamed
0x1E          u32    +0x2C            unnamed
```

The loader's linked-list stitcher then walks the runtime array.  If the previous runtime pointer is non-NULL, it writes it to current `+0x04`.  If current `+0x00` is nonzero, the loader overwrites current `+0x00` with `current + 0x30` and carries current as the previous pointer; otherwise the chain resets.

In `t1l1m001`, most MAP objects have `section4_index = 0xFFFFFFFF` (sentinel → NULL).  Only a few objects (e.g., index 4) reference a valid Section4 entry.

---

## Practical notes for WAD editing / object placement

This section consolidates what is needed to add or clone a MAP object.

### Adding a new MAP object (minimal viable approach)

1. **Choose a template** — Pick an existing `MapObjectDisk58` from `map_full/objects_58_disk.csv` whose `script_offset` points to the object type you want to place.
2. **Copy all fields verbatim** from the template except position and rotation.
3. **Set position** (12.12 fixed-point):
   ```python
   pos_x_fixed12 = int(world_x * 4096)
   pos_y_fixed12 = int(world_y * 4096)
   pos_z_fixed12 = int(world_z * 4096)
   ```
4. **Set rotation** (4096 units per full turn, 16-bit, range 0–4095):
   ```python
   rot_y_units = int(yaw_degrees * 4096 / 360) & 0xFFFF
   ```
5. **Increment `object_count`** in the MAP header.
6. **Update `object_count_b`** to the same value (both must agree for the actor pool allocation in `sub_54D0D0`).
7. **Leave `section2_index` = `0xFFFFFFFF`** and **`section4_index` = `0xFFFFFFFF`** unless you need linked-list data (safe to omit for cloned objects).
8. **Leave `flags` = `0x0000`** (all flags 0 in tested level).
9. **Do NOT set `flags & 0x0002`** — that bit skips initial spawn.

### Known `script_offset` values from `t1l1m001`

| `script_offset` hex | Observed objects | Notes |
|---|---|---|
| `0x004210E2` | object 0 | local_count=1, stack_word_count=13 |
| `0x00421F96` | objects 1–3 | local_count=0, stack_word_count=9, spawn_flags=0x8000 |
| `0x004224EE` | object 4 | local_count=5, stack_word_count=12, spawn_flags=0x8000 |

`spawn_flags=0x8000` (bit 15) appears in multiple objects; its render/logic role is not yet named but is safe to copy from a template.

### Rebuilding the WAD chunk

After modifying the MAP object table, the chunk must be re-serialized following the exact confirmed read order from `sub_42AC50`:

```text
u32  tile_count
u32  grid_width
u32  grid_height
MapTile24 tiles[tile_count]

u32  section2_count
u32  section2_data[section2_count]

u32  section3_count
Section3Disk90 section3[section3_count]

u32  section4_count
Section4Disk34 section4[section4_count]

u32  section5_32x8[32][2]      // 256-byte lookup table: 32 records × 32 bytes
u32  grid[grid_width * grid_height]
TileDefDisk24 tile_defs[tile_count]
u32  tile_trak_record_index[tile_count]

// if dword_6DA330 & 0x10000:
u32  optional20_count
OptionalRecord20 optional20[optional20_count]

MapVertexColors colors[tile_count]

u32  object_count
u32  object_count_b            // must equal object_count
MapObjectDisk58 objects[object_count]

// if dword_6DA330 & 0x10:
u32  final_optional_dword
u16  final_u16
```

The WAD container wrapper:
```text
+0x00  u32  total_file_size - 4
+0x04  chunks until EOF:
         char[4]  tag (stored reversed: "MAP " → stored as " PAM")
         u32      chunk_data_size
         bytes    chunk_data
```
