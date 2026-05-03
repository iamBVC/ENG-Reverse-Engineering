# Emperor's New Groove WAD Tools

Reverse-engineering tools for extracting and inspecting level `.WAD` files from *Disney's / Argonaut's The Emperor's New Groove*.

The project is intentionally written in plain Python and split into small modules so each file-format area can be studied independently.  The code assumes the reader may be new to the WAD format, so the comments explain both what is known and what is still uncertain.

## What this tool does

Given a level WAD such as `t1l1m001.wad`, the extractor can:

- scan the WAD container and write a chunk manifest
- extract level metadata such as the level name
- decode the `TEXT` chunk into real RGB555 RLE texture PNGs
- export the remaining `TEXT` palette/metadata table and optional legacy diagnostics
- parse the `MAP ` chunk into world-space tile XYZ data
- generate MAP CSV files, OBJ marker meshes, a PNG grid, and an HTML map viewer
- parse the `LGHT` chunk into `lights.csv`
- decode the `TRAK` chunk into records, vertex/triangle tables, OBJ surfaces, and an HTML viewer
- export `STPC` static geometry as OBJ meshes
- export a `world/` folder that reconstructs the level world from TRAK terrain, MAP tile/object placement, and STPC mesh candidates
- preserve raw binary chunks that are not fully decoded yet

## Installation

Python 3.10+ is recommended.

```bash
pip install -r requirements.txt
```

The only required third-party dependency is Pillow, used for PNG export.

## Basic usage

Extract one WAD:

```bash
python wad_extractor.py t1l1m001.wad
```

Extract to a specific root folder:

```bash
python wad_extractor.py t1l1m001.wad --out-dir extracted
```

Extract every `.wad` / `.WAD` file in a folder:

```bash
python wad_extractor.py wads/ --out-dir extracted
```

## Opt-out flags

Most extraction features are enabled by default.  Use these flags to disable parts you do not need:

```bash
--no-tex              skip TEXT texture/palette extraction
--no-texture-fields   skip diagnostic palette-field images
--no-map              skip MAP parsing and map viewer exports
--no-stpc-obj         skip STPC OBJ mesh export
--no-trak             skip TRAK CSV/OBJ/viewer export
--no-lights           skip LGHT light CSV export
--no-raw              do not export raw undecoded chunks
--no-world            skip reconstructed TRAK + MAP-object + STPC world export
--world-probe          also run the older Section-4 instance-hunting diagnostics, now deprecated
--quiet               reduce per-record progress output
```

STPC-specific options:

```bash
--stpc-alignment 1        exhaustive STPC mesh scan; slower but useful for testing
--stpc-min-score 0.80     lower candidate acceptance threshold
--stpc-scale 0.01         scale OBJ vertices
--stpc-flip-z             flip the Z axis in STPC OBJ export
--stpc-debug-faces        write stpc/faces_debug.csv
```

TRAK-specific options:

```bash
--trak-scale 0.01         scale TRAK OBJ vertices
--trak-flip-z             flip the Z axis in TRAK OBJ export
```

## Output folder layout

The extractor uses a clean output layout.  It does not keep legacy flat output names.

```text
extracted/t1l1m001/
  info.txt
  level_name.txt

  raw/
    stpc.bin
    smpc.bin
    trak.bin
    ambient_audio.bin
    font.bin
    srpc.bin
    lgpc.bin
    wfpc.bin

  textures/
    texture_00.png
    texture_01.png
    texture_decode_stats.csv
    ...

  texture_fields/
    texture_00_legacy_field0_meta0.png
    texture_00_legacy_field1_meta1.png
    ...

  palette/
    palette.bin
    palette.png
    palette_debug.csv

  map/
    map_parse_log.txt
    map_tiles.csv
    map_tile_defs.csv
    map_grid.csv
    map_grid.png
    map_world_tiles.csv
    map_grid_world.csv
    map_world_tiles.obj
    map_grid_world.obj
    map_world_tiles.mtl
    map_world_viewer.html

  lights/
    lights.csv
    summary.txt

  trak/
    summary.txt
    records.csv
    table_a_vertices.csv
    table_b_triangles.csv
    table_cde_entries.csv
    trak.mtl
    table_b_surfaces.obj                 # combined decoded Table A/B surface mesh
    per_record_surfaces/                 # one OBJ per TRAK record/sector
      record_001_surface.obj
      record_002_surface.obj
      ...
    record_aabbs.obj                     # visible diagnostic bounds from decoded vertices
    record_centers.obj                   # visible center markers
    record_header_vectors_diagnostic.obj # old 8-vector header diagnostic; not final geometry
    viewer.html                          # auto-fit HTML preview of decoded triangle surfaces

  stpc/
    manifest.csv
    stpc_materials.mtl
    combined.obj
    mesh_000_off_00000004.obj
    mesh_001_off_00000688.obj
    ...

  world/
    summary.txt
    map_object_instances.csv
    stpc_object_defs.csv
    stpc_mesh_reference_hits.csv
    terrain.obj
    objects_primary.obj
    objects_all_candidates.obj
    objects_by_hit/
    combined.obj
    diagnostics/
    world_viewer.html
```

## How to inspect MAP data

Start with these files:

### `map/map_world_tiles.csv`

This is the raw parsed tile-list section from `MAP `.  Each row contains one tile-like record with:

```text
tile_idx, x, y, z, unknown, flags, flags_hex, type_idx
```

This is currently the most important file for reconstructing a level-map viewer because it contains direct world-space coordinates.

### `map/map_world_tiles.obj`

Each MAP tile-list entry is drawn as a small quad centered at its parsed XYZ position.  This is diagnostic marker geometry, not the final game terrain mesh.

Open it in Blender, MeshLab, Noesis, or another OBJ viewer.

### `map/map_grid_world.obj`

This tries to resolve non-zero `MAP ` grid cells back to tile-list entries.  It auto-detects whether grid values look more like 0-based or 1-based tile indices.

Compare this with `map_world_tiles.obj` to understand how the grid relates to the raw tile list.

### `map/map_world_viewer.html`

A zero-dependency browser viewer.  Open it directly in a browser.  It supports:

- top-down X/Z view
- simple isometric view
- mouse drag to pan
- mouse wheel to zoom
- height coloring
- type-index coloring
- flag coloring
- hover tooltip showing tile index, XYZ, flags, and type index

This is not intended to replace a real 3D engine viewer, but it is useful for quick inspection.


## How to inspect the reconstructed world export

The `world/` folder is the current world-regeneration export. It uses the executable-confirmed relationship:

```text
TRAK = terrain / world-sector triangle geometry
MAP  = object placement records with confirmed 12.12 fixed-point XYZ
STPC = mesh bank plus object-definition/script data referenced by MAP objects
```

For each MAP object record, the game converts the object-definition field to:

```c
dword_6D9DBC + stpc_object_def_offset
```

where `dword_6D9DBC` is the raw STPC chunk base. The exporter scans each referenced STPC object-definition window for exact little-endian `u32` values that match decoded STPC mesh-record offsets. When it finds a match, it exports that STPC mesh translated to the confirmed MAP object XYZ, with the validated Z-basis correction; terrain uses a centered Z mirror and experimental MAP-object yaw.

### `world/terrain.obj`

The reconstructed terrain/world surface. It is generated from TRAK Table A/B geometry placed by MAP tile XYZ, MAP tile yaw, and the tile → TRAK-record index table.

### `world/map_object_instances.csv`

One row per MAP object, with confirmed world position:

```text
world_x = int32(pos_x_fixed) / 4096.0
world_y = int32(pos_y_fixed) / 4096.0
world_z = int32(pos_z_fixed) / 4096.0
```

It also exports unresolved candidate fields such as `field_26_angle_candidate` so rotation/scale can be tested later.

### `world/stpc_object_defs.csv`

Unique STPC object-definition offsets referenced by MAP objects, with the first bytes of each definition.

### `world/stpc_mesh_reference_hits.csv`

Exact hits where an STPC object definition contains a decoded STPC mesh-record offset. These rows are the current bridge from MAP object placement to STPC geometry.

### `world/objects_primary.obj`

One earliest mesh-reference hit per MAP object. This is the cleanest object export for quick inspection and is now the object source used by `world/combined.obj`.

### `world/objects_all_candidates.obj`

All STPC mesh-reference hits translated to MAP object XYZ. This may include multiple candidates for the same MAP object while the full STPC object-definition language is still being decoded.

### `world/objects_by_hit/`

One OBJ per exact STPC mesh-reference hit. Each file contains exactly one STPC mesh candidate. This is the safest folder for checking individual placements.

### `world/combined.obj`

The reconstructed terrain plus `objects_primary.obj` in one OBJ. `objects_all_candidates.obj` is still written as a diagnostic, but it is no longer the default combined-world source.

### `world/world_viewer.html`

A lightweight object-placement viewer. Orange points have at least one STPC mesh-reference hit. Blue points are MAP object records without a current mesh match.

### `world/diagnostics/` and deprecated `world_probe/`

`world/diagnostics/objects_grouped_by_object/` contains grouped candidate meshes per MAP object. These are useful for reverse-engineering but may intentionally contain multiple meshes.

The older Section-4 `world_probe/` diagnostics are now opt-in via `--world-probe`. The executable-confirmed MAP loader showed that Section 4 is not the main STPC placement table, so the official `world/` export should be used instead.

## Known WAD container structure

A level WAD is a linear chunk container.

```text
+0x00  u32  total file size minus 4
+0x04  repeated chunks until EOF:
        char[4]  chunk tag, stored reversed
        u32      chunk data size
        bytes    chunk data
```

Known chunk tags seen in level WADs:

```text
INFO VERS WFPC TEXT FONT SPRT NAME SMPC AMPC SRPC TRAK STPC MAP  LGHT LNFO LGPC
```

The tag `MAP ` includes a trailing space because chunk tags are exactly four bytes.

## Compression notes

The project still includes an LZSS helper because some early reverse-engineering probes used it, but the main `TEXT`/`TXET` texture images are now decoded with the correct RGB555 RLE stream described below.

## `TEXT` chunk structure

Despite the name, `TEXT` is not a text-string chunk.  It contains RGB555 compressed textures plus a palette/metadata table.

Observed layout:

```text
u32 count1                  usually 0
u32 texture_count           18 in t1l1m001

repeated texture_count times:
    u32 flags
    u32 width
    u32 height
    u32 compressed_size
    bytes compressed_data

Then the texture payload itself is decoded as a stream of little-endian 16-bit packets:

```text
packet < 0x8000:
    literal packet
    read packet RGB555 words

packet & 0x8000:
    repeat packet
    count = 0x10000 - packet
    read one RGB555 word and repeat it count times
```

Each RGB555 word is decoded as `xRRRRRGGGGGBBBBB` and expanded to 8-bit RGB by left-shifting each 5-bit channel by 3.

After all texture records:

```text
u32 palette_entry_count
repeated palette_entry_count times, 8 bytes each:
    byte 0  metadata A
    byte 1  metadata B
    byte 2  metadata C
    byte 3  marker, usually 0xFF
    byte 4  red
    byte 5  green
    byte 6  blue
    byte 7  extra / flags
```

Known uncertainty:

- The main exported texture PNGs are now decoded as RGB555 RLE.
- The palette/metadata table is preserved, but its full material/texture binding role is not fully decoded yet.
- Texture flags such as `0x81..0x87` likely encode type/format information, but the exact meanings are not fully confirmed.

## `MAP ` chunk structure

The `MAP ` chunk contains level layout information.  It is partially decoded and parsed in a partial-safe way.

Currently useful layout:

```text
+0x00  u32  tile_count
+0x04  u32  grid_width      usually 96
+0x08  u32  grid_height     usually 96

+0x0C  repeated tile_count times, 24 bytes each:
        f32 x
        f32 y
        f32 z
        f32 unknown
        u32 flags
        u32 type_idx
```

Later observed sections:

```text
Section 2: count + count * u32
Section 3: count + count * 90 bytes
Section 4: count + count * 48 bytes
Section 5: lookup/padding table, observed candidate sizes 256*8 or 32*8 bytes
Section 6: grid_width * grid_height * u32 grid values
Section 7: tile_count * 32-byte tile-definition-like records
```

Known uncertainty:

- The exact meaning of `unknown`, `flags`, and `type_idx` is not fully decoded.
- Grid values may be 0-based tile-list indices, 1-based tile-list indices, type IDs, or another lookup layer depending on the level.
- Tile definitions are exported as raw integer fields, but their semantic meaning is not confirmed.
- MAP does not appear to contain final render geometry by itself; it likely references/organizes geometry from other chunks such as `STPC`.

## `STPC` / `TRAK` geometry structures

The executable has now confirmed the shared render/collision geometry record used by TRAK and by STPC-like static meshes.  The two important loader functions are:

```text
sub_42AAC0 -> sub_5563F0  // TRAK, 0x84-byte runtime geometry records
sub_42AB50 -> sub_41F770  // extended 0x8C-byte records used by packed/scene data
```

### `GeometryRecord84` / runtime record

`sub_5563F0` confirms the normal runtime record is `0x84` bytes.  `sub_402840` confirms that most of the first `0x6C` bytes are culling bounds.

```text
+0x00  u32/f32   unknown metadata
+0x04  f32       unknown header float
+0x08  f32       unknown header float
+0x0C  8 x vec3  culling/bounds points used by sub_402840 frustum tests
+0x6C  u16       vertex_count
+0x6E  u16       triangle_count
+0x70  u32       vertices pointer slot, overwritten by loader
+0x74  u32       triangles pointer slot, overwritten by loader
+0x78  u16       collision/contact group 0 count
+0x7A  u16       collision/contact group 1 count
+0x7C  u16       collision/contact group 2 count
+0x7E  u16       still unknown
+0x80  u32       collision/contact entries pointer slot, overwritten by loader
```

After the fixed record table, `sub_5563F0` lays out the variable data for every record in order:

```text
vertices:          vertex_count * 24 bytes
triangles:         triangle_count * 28 bytes
collision entries: (group0 + group1 + group2) * 32 bytes
```

### Vertex and triangle records

```c
struct Vertex24 {
    float x, y, z;
    float nx, ny, nz;
};

struct Triangle28Disk {
    uint16_t flags;
    uint16_t i0, i1, i2;
    uint16_t material_index; // runtime: dword_581154 + 20 * material_index
    uint16_t material_pad;
    float plane_nx, plane_ny, plane_nz, plane_d;
};
```

Confirmed triangle flag notes from `sub_556510` / `sub_41FB30`:

```text
0x0008 = render batch/material-state break marker
0x0010 = terrain UV branch bit
0x0020 = terrain UV swap/filter bit
0x0400 = backface/plane-cull override
0x0800 = terrain UV branch bit
```

Bits `0x0001` and `0x0002` are render/material/effect related but still conservatively named in CSV output.

### Collision/contact entry records

The C/D/E entries are no longer raw unknown data.  `sub_4036D0`, `sub_403AD0`, `sub_4042F0`, and `sub_4046E0` use them as compact collision/contact polygons.

```c
struct CollisionEntry32 {
    uint8_t  flags;       // bit0: 0 = 3 edges, 1 = 4 edges
    uint8_t  surface_id;  // 17/18 conditionally skipped, 30 invalid/no contact
    int8_t   normal_x_q32;
    int8_t   normal_y_q32;
    int8_t   normal_z_q32;
    int8_t   unknown_05;
    int16_t  plane_d;
    uint8_t  edge_data[24]; // 3 or 4 x 6-byte edge equations
};
```

The runtime usually scans the combined `group0 + group1 + group2` entry array.  The tool now decodes these into `trak/table_cde_entries.csv` with signed plane coefficients, surface IDs, edge counts, and per-edge values.

### Extended `GeometryRecord8C`

`sub_41F770` confirms an extended `0x8C` form used by packed/scene data.  It starts with the same `GeometryRecord84`, then adds transform-group data used by the `sub_41FB30` skinned/multi-transform path:

```text
+0x84  u16  base_vertex_count
+0x86  u16  transform_group_count
+0x88  u32  transform_group_vertex_counts pointer slot
```

### `STPC` chunk status

`STPC` static polygon exports still use a validated scanner because the high-level STPC container is not fully table-decoded yet.  The mesh records it finds match the same 24-byte vertex and 28-byte triangle format, and their first `0x6C` bytes are now understood as the same culling/bounds-style header. STPC OBJ export now writes `vt` coordinates per face using the same material-rectangle selector bits confirmed in `sub_556510` (`0x0800`, `0x0010`, `0x0020`) and writes `map_Kd` texture bindings when the TEXT material table is available.

Known remaining STPC uncertainty:

- the high-level STPC container/table of contents
- exact names for `GeometryRecord84 +0x00/+0x04/+0x08/+0x7E`
- full semantic split of collision group0/group1/group2

## `TRAK` chunk structure

`TRAK` is structurally decoded from the executable loader.  In the WAD file the tag bytes are stored reversed as `KART`, but the chunk name shown by this tool is `TRAK`.  It is not a simple camera spline: it is the level/world geometry record table used for rendering and collision.

Outputs now include:

- `trak/table_b_surfaces.obj` — all decoded render triangles from Table A/B.
- `trak/per_record_surfaces/` — one OBJ per geometry record/sector.
- `trak/table_cde_entries.csv` — decoded collision/contact plane entries.
- `trak/record_header_vectors_diagnostic.obj` — culling/bounds vectors from the record header.
- `trak/viewer.html` — local/MAP-placed interactive preview, depending on whether MAP_FULL was available.

Known remaining TRAK uncertainty:

- exact names for header fields `+0x00`, `+0x04`, `+0x08`, and `+0x7E`
- exact semantic split between the three collision entry count groups
- some triangle flag bits beyond the confirmed render/UV/culling bits

## `LGHT` chunk structure

`LGHT` is now mostly decoded from the PC executable path.  In the WAD dispatcher, the little-endian chunk tag `1279739988` / `0x4C474854` is `LGHT`, and it is loaded by `sub_42C180`.  The loader creates 112-byte runtime light objects with `sub_41B8A0` and stores their pointers in the world container.

World/container fields:

```c
struct MapWorld_LightFields {
    uint32_t light_count;      // world + 0x5C / +92
    RuntimeLight112 **lights;  // world + 0x60 / +96
};
```

### Disk layout

The chunk starts with a 32-bit count, then packed type-dependent records.

```c
#pragma pack(push, 1)

struct LGHT_Header {
    uint32_t light_count;
};

struct LGHT_Type1_Directional {
    uint8_t type;      // 1
    uint8_t r;
    uint8_t g;
    uint8_t b;

    float dir_x;
    float dir_y;
    float dir_z;      // runtime negates z, then normalizes dir_x/dir_y/-dir_z
}; // 16 bytes

struct LGHT_Type2_Point {
    uint8_t type;      // 2
    uint8_t r;
    uint8_t g;
    uint8_t b;

    float x;
    float y;
    float z;          // runtime negates z

    float inner_radius;
    float outer_radius;

    uint8_t falloff_or_mode;
}; // 25 bytes, packed

struct LGHT_Type4_NegativePoint {
    uint8_t type;      // 4 on disk; constructor creates runtime type 2
    uint8_t r;
    uint8_t g;
    uint8_t b;

    float x;
    float y;
    float z;          // runtime negates z

    float inner_radius;
    float outer_radius;

    uint8_t falloff_or_mode;
}; // 25 bytes, packed

#pragma pack(pop)
```

### Color conversion

For type `1` and type `2`, `sub_42C180` converts each RGB byte to runtime intensity with:

```c
float channel = (2.0f * byte_value) / 255.0f;
```

So disk color bytes cover approximately `0.0..2.0` intensity.  For disk type `4`, the loader reads the same point-light payload but converts color to negative/special values before creating a runtime type-2 light:

```c
runtime_channel = -((channel + 1.0f) * 0.5f);
```

Type `4` is therefore best described as a **negative/special point light** until the lighting evaluator is fully named.

### Runtime light object

`sub_41B8A0` allocates 112 bytes for each light.  `sub_41BEE0` copies base color to current/effective color and can convert it to grayscale when color rendering is disabled.

```c
#pragma pack(push, 1)
struct RuntimeLight112 {
    float color_r;             // +0x00 current/effective
    float color_g;             // +0x04 current/effective
    float color_b;             // +0x08 current/effective
    float color_a_or_unused;   // +0x0C copied from +0x1C

    float base_r;              // +0x10 constructor r
    float base_g;              // +0x14 constructor g
    float base_b;              // +0x18 constructor b
    float base_a_or_unused;    // +0x1C

    // runtime type 2 positional light current position
    float pos_x_current;       // +0x20
    float pos_y_current;       // +0x24
    float pos_z_current;       // +0x28

    // runtime type 1 normalized direction
    float dir_x;               // +0x2C
    float dir_y;               // +0x30
    float dir_z;               // +0x34

    // runtime type 2 base/original position
    float pos_x_base;          // +0x38
    float pos_y_base;          // +0x3C
    float pos_z_base;          // +0x40

    // runtime type 1 copied normalized direction
    float dir_x_base;          // +0x44
    float dir_y_base;          // +0x48
    float dir_z_base;          // +0x4C

    // runtime type 2 radius/falloff
    float outer_radius_sq;     // +0x50
    float inner_radius_sq;     // +0x54
    float outer_radius;        // +0x58
    float inner_radius;        // +0x5C
    float inv_radius_range;    // +0x60 = 1.0 / (outer_radius - inner_radius) when non-zero
    uint32_t falloff_or_mode;  // +0x64 final disk byte from type 2/4

    uint32_t type;             // +0x68, 1=directional, 2=point/ranged
    uint8_t active_or_flags;   // +0x6C, constructor clears to 0
    uint8_t unknown_6D[3];
}; // 112 bytes
#pragma pack(pop)
```

`sub_41BD70`, `sub_41BF80`, `sub_41BFA0`, and `sub_41BFC0` are simple active-light linked-list helpers.

### Current LGHT outputs

`lights/lights.csv` now includes both raw disk values and runtime-derived values:

- `kind`: `directional`, `point`, `negative_point`, or `unknown`
- disk RGB bytes and runtime intensities
- type-1 direction and normalized runtime direction
- type-2/type-4 position, runtime-negated Z, inner/outer radii, squared radii, and inverse radius range
- `falloff_or_mode`, the final byte of type-2/type-4 records

`lights/summary.txt` summarizes counts by light kind and repeats the executable-backed interpretation.

Known remaining LGHT uncertainty:

- The final byte in type `2`/`4` is still named `falloff_or_mode`; it should be renamed once the lighting evaluator using runtime offset `+0x64` is reversed.
- `RuntimeLight112 +0x0C/+0x1C` are copied by `sub_41BEE0`, but are not initialized by the constructor pseudocode we have.

## Chunks and files not fully decoded yet

These are preserved in `raw/` for later analysis:

| Chunk | Raw output | Current status |
|---|---|---|
| `STPC` | `raw/stpc.bin` | Static mesh records decoded; culling header and triangle flags documented; full container/material binding still partial |
| `SMPC` | `raw/smpc.bin` | Not decoded; likely sprite/mesh compressed or related geometry data |
| `SRPC` | `raw/srpc.bin` | Not decoded; likely sound/resource config |
| `TRAK` | `raw/trak.bin`, `trak/` | Main record table and A/B/CDE table packing decoded; A/B exported as surfaces; C/D/E semantics still unknown |
| `AMPC` | `raw/ambient_audio.bin` | Exported raw; semantic structure not decoded |
| `LGPC` | `raw/lgpc.bin` | Not decoded; may relate to lighting/geometry/collision |
| `WFPC` | `raw/wfpc.bin` | Not decoded |
| `FONT` | `raw/font.bin` | Exported raw; glyph layout not decoded |
| `MAP ` | `map/` outputs | Tile list/grid partially decoded; flags/type semantics still unknown |
| `TEXT` | `textures/`, `palette/` | RGB555 RLE texture images decoded; palette/material binding semantics still partly unknown |
| `LGHT` | `lights/lights.csv`, `lights/summary.txt` | Directional, point, and negative/special point records decoded from `sub_42C180` / `sub_41B8A0`; final type-2/type-4 byte still named `falloff_or_mode` |

## What is left to do

Useful next reverse-engineering tasks:

1. Validate MAP-object → STPC-definition → STPC-mesh references visually in `world/combined.obj`.
2. Decode MAP object scale and the full STPC object-definition language, then apply it to `world/objects_all_candidates.obj`.
2. Decode `MAP ` `flags` and `type_idx` values.
3. Validate the current EXE-derived STPC triangle UV/material mapping across more levels; texture pages now bind through the decoded TEXT runtime material table.
4. Finish naming TRAK/STPC header fields `+0x00/+0x04/+0x08/+0x7E` and the exact semantic split of collision groups 0/1/2.
5. Reverse the runtime lighting evaluator that reads `RuntimeLight112 +0x64` so `falloff_or_mode` can be named precisely.
6. Identify whether `SMPC`, `LGPC`, or `WFPC` contain collision, visibility, portals, sprites, or runtime placement tables.
7. Replace the STPC mesh scanner with a full container parser once the top-level tables are understood.
8. Build a real 3D viewer that loads `MAP ` marker data, `STPC` render geometry, `TRAK` sector/surface data, and decoded `LGHT` lights together.

## Module overview

```text
wad_extractor.py          main command-line entry point

eng_wad/binary.py         Reader, endian helpers, hexdump helper
eng_wad/lzss.py           legacy/experimental LZSS helper
eng_wad/wad.py            WAD chunk scanner/container utilities
eng_wad/text_chunk.py     TEXT parser and texture/palette exports
eng_wad/map_chunk.py      partial-safe MAP parser
eng_wad/map_export.py     MAP CSV, PNG, OBJ, and HTML viewer exports
eng_wad/world_rebuild.py  TRAK + MAP-object + STPC world reconstruction export
eng_wad/instance_hunter.py deprecated Section-4 world-probe diagnostics
eng_wad/stpc_chunk.py     STPC mesh scanner/exporter library
eng_wad/trak_chunk.py     TRAK parser/exporter library
eng_wad/light_chunk.py    LGHT parser/exporter
eng_wad/raw_export.py     raw binary chunk exporters
```

## Notes on accuracy

This project is based on observed files and reverse-engineering.  It deliberately distinguishes between:

- confirmed structures that have produced valid output
- partially confirmed layouts that are useful but still uncertain
- raw chunks that are preserved but not decoded

When in doubt, the code tries to export partial data and write warnings instead of crashing.

## MAP executable-confirmed diagnostics (`map_full/`)

The project now includes `eng_wad/map_full_chunk.py`, a parser based on the
actual game loader `sub_42AC50`. This parser is more accurate than the older
exploratory MAP parser for sections after the tile list.

Confirmed MAP read order:

```c
uint32 tile_count;
uint32 grid_width;
uint32 grid_height;
MapTile24 tiles[tile_count];

uint32 section2_count;
uint32 section2_u32[section2_count];

uint32 section3_count;
Section3Disk90 section3[section3_count]; // expanded to 92 bytes at runtime

uint32 section4_count;
Section4Disk34 section4[section4_count]; // expanded to 48 bytes at runtime

uint32 section5_32x8[32][2];
uint32 grid[grid_width * grid_height];
TileDefDisk24 tile_defs[tile_count];     // expanded to 32 bytes at runtime
uint32 tile_trak_record_index[tile_count];

// Present in the tested PC WADs when dword_6DA330 & 0x10000 is set:
uint32 optional20_count;
OptionalRecord20 optional20[optional20_count];

// Per tile, color/light bytes sized from the referenced TRAK record's
// Table A vertex count. Extra layers are controlled by the first layer's alpha.
MapVertexColors colors[tile_count];

uint32 object_count;
uint32 object_count_unknown_b;
ObjectDisk58 objects[object_count];       // expanded to 72 bytes at runtime

// Present in the tested PC WADs when dword_6DA330 & 0x10 is set:
uint32 final_optional_dword;
uint16 final_u16;
```

The `map_full/` output folder contains:

- `summary.json` / `summary.txt`
- `tiles_24.csv`
- `section2_u32.csv`
- `section3_records_90.csv`
- `section4_records_34.csv`
- `section5_32x8.csv`
- `grid_u32.csv`
- `tile_defs_24.csv`
- `tile_trak_record_indices.csv`
- `optional20_records.csv`
- `vertex_color_blocks.csv`
- `objects_58.csv`
- `object_record_float_probe.obj`

The `objects_58.csv` table is the next major reverse-engineering target. It is
likely a gameplay/entity/logic table rather than the TRAK terrain itself. Field
names are still conservative until xrefs to these runtime records are decoded.

To skip this export:

```bash
python wad_extractor.py level.wad --no-map-full
```

## World rebuild update: official terrain and object exports

The `world/` exporter now treats TRAK geometry as **local terrain-sector geometry** and uses MAP to place it:

```text
world/terrain.obj
```

is generated by applying:

```text
MAP tile XYZ + MAP tile_trak_record_index + TRAK Table A/B local mesh
```

This is different from the diagnostic TRAK-only exports under `trak/`, where each TRAK record is shown without MAP placement.

The STPC candidate instance exporter now separates ambiguous mesh hits:

```text
world/objects_by_hit/
```

contains exactly one STPC mesh per OBJ file. This is the safest folder to inspect while the STPC object-definition language is still being decoded.

Other STPC world outputs:

```text
world/objects_all_candidates.obj
```

contains all candidate hits together.

```text
world/objects_primary.obj
```

contains only the earliest detected mesh-reference hit per MAP object.

```text
world/diagnostics/objects_grouped_by_object/
```

contains grouped candidate hits per MAP object. These files may intentionally contain multiple meshes and should be treated as diagnostic.

Known limitation: the current visual reference is `terrain.obj`. The exporter therefore mirrors STPC object instances around the same centered world Z axis used by the validated terrain orientation. STPC object yaw is applied experimentally from `small_04`; scale and full STPC object-definition semantics are still unresolved. STPC OBJ faces now include per-face UVs derived from the EXE-confirmed material-rectangle flag path, and `world.mtl` maps `stpc_mat_####` entries to decoded TEXT textures when available.

## World rebuild transform update

The `world/` exporter applies the MAP transforms that are known from the executable-backed MAP parser:

- `terrain.obj` uses `MAP tile_defs_24` fixed-point XYZ plus the tile yaw value.
- MAP tile yaw appears to use 4096 units per full turn. Common values are `0`, `1024`, `2048`, and `3072`.
- Terrain is the visual reference: it uses MAP tile fixed-point XYZ, tile yaw, and the centered Z mirror validated in `terrain.obj`.
- STPC object positions still use `--world-stpc-object-z-sign -1`, then are mirrored around the terrain Z center by default so their placement matches the corrected terrain orientation.
- Local STPC mesh Z is negated by default with `--world-stpc-local-z-sign -1`.
- STPC object yaw is experimental and currently uses the MAP object `small_04` field as a 4096-unit yaw value.

Useful validation files:

```text
world/terrain_tile_transforms.csv
world/stpc_instance_transforms.csv
world/terrain.obj
world/objects_by_hit/
world/combined.obj
```

Useful transform flags:

```bash
--world-terrain-yaw-sign 1
--world-terrain-yaw-sign -1
--world-stpc-object-z-sign -1
--world-stpc-local-z-sign -1
--world-no-object-z-mirror
--world-no-stpc-yaw
--world-stpc-yaw-sign -1
```

If terrain tile rotation appears reversed, try `--world-terrain-yaw-sign -1`. If STPC object placement appears mirrored, compare with `--world-no-object-z-mirror`. If STPC object rotation appears reversed, try `--world-stpc-yaw-sign -1` or `--world-no-stpc-yaw`.

## World alignment calibration notes

The `world/` exporter now treats `terrain.obj` as the validated reference mesh and
writes STPC object candidates relative to that terrain.  Some object-definition
semantics are still unresolved, so a small residual object-vs-terrain offset can
remain on certain levels.

The exporter exposes final world-space offsets that are applied **only to STPC
object instances**, after all MAP/STPC coordinate conversion, mirroring, and yaw
have been applied:

```bash
python wad_extractor.py level.wad --world-object-x-offset 0.25
python wad_extractor.py level.wad --world-object-z-offset -0.50
python wad_extractor.py level.wad --world-object-y-offset 0.10
```

These options are intended for calibration while the remaining STPC object-definition
fields are being reversed.  The exact values used are written to:

```text
world/stpc_instance_transforms.csv
world/summary.json
```

Recommended workflow:

1. Open `world/combined.obj` in Blender or Noesis.
2. Pick a visible prop with an obvious contact point, for example a crate, gate,
   post, bridge support, or platform corner.
3. Measure the delta needed to move the object onto the matching terrain feature.
4. Re-export with `--world-object-x-offset`, `--world-object-y-offset`, and/or
   `--world-object-z-offset`.
5. Send the offset values back with a screenshot if the same residual offset is
   consistent across the level; that lets us decide whether the correction is a
   global coordinate-origin adjustment or a still-undecoded per-object pivot field.

### Validated object/terrain alignment offset

The stable world exporter uses a default object-space Z correction of `+1.5`:

```bash
python wad_extractor.py level.wad --world-object-z-offset 1.5
```

This is now the default, but the flag remains available for experiments. The correction is applied only to STPC object instances after the MAP object position, object yaw, local STPC Z conversion, and centered world mirror. `terrain.obj` is not moved by this offset.

Current best explanation: this is probably an object-anchor/pivot correction from the STPC object-definition scripting layer, not a MAP position error. The MAP object XYZ fields align globally, and the executable contains a STPC definition resolver (`sub_553630`) that converts offsets inside object-definition bytecode to runtime pointers before executing that definition. Our exporter currently scans those definitions for mesh offsets, but it does not yet execute the nearby placement/anchor opcodes. The consistent `+1.5` correction likely represents one of those definition-level local placement constants or a collision/render pivot convention used by the engine.

## Material / UV checkpoint

The trailing table after the `TEXT` texture records is now treated as the executable-confirmed runtime material source table, not as a color palette for the decoded RGB555 texture images.

The game expands each 8-byte disk row into a 20-byte runtime material record at `dword_581154`:

```text
+0x00 u16 flags
+0x02 u8  texture page index
+0x03 u8  extra/source/animation byte, often 0xFF
+0x04 u8  source x0
+0x08 u8  source x1
+0x0C u8  source y0
+0x10 u8  source y1
```

`sub_407240` converts the source rectangle to UV floats as:

```text
u0 = x0 / texture_width
u1 = (x1 + 1) / texture_width
v0 = y0 / texture_height
v1 = (y1 + 1) / texture_height
```

Default material/texture outputs:

```text
materials/
  runtime_material_table_20.csv
  texture_inventory.csv
  texture_material_usage_summary.csv
  trak_terrain_material_usage.csv
  stpc_material_usage.csv
  summary.json

world/
  terrain.obj
  terrain_textured.obj
  world.mtl
  textures/texture_XX.png
```

`terrain_textured.obj` is now the normal textured terrain export. It uses the
visually confirmed terrain UV mapping reconstructed from the game's
`sub_556510` renderer path. The older UV variant folders and texture-index
remap diagnostics have been removed from the default project.

## Validated terrain texture and UV behavior

Texture PNG export defaults to BGR channel order, which matches the original
colors after the observed red/blue channel swap. The older RGB order is still
available only for comparison:

```bash
python wad_extractor.py t1l1m001.wad --texture-channel-order rgb
```

Terrain texture page mapping uses the direct runtime material texture page id.
Earlier texture-index remap probes looked worse than direct mapping, so those
comparison outputs are no longer generated.

Terrain UVs are generated from the validated EXE logic:

```text
material +0x04 = u0
material +0x08 = u1
material +0x0C = v0
material +0x10 = v1

TRAK face flags:
0x0800  selects the main terrain UV branch
0x0010  selects the alternate top-row branch when 0x0800 is set
0x0020  swaps the material U endpoints
```

The exporter applies this mapping directly to `world/terrain_textured.obj`.
There are no UV-variant command-line flags anymore because this mapping is the
validated default.
