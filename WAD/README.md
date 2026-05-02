# Emperor's New Groove WAD Tools

Reverse-engineering tools for extracting and inspecting level `.WAD` files from *Disney's / Argonaut's The Emperor's New Groove*.

The project is intentionally written in plain Python and split into small modules so each file-format area can be studied independently.  The code assumes the reader may be new to the WAD format, so the comments explain both what is known and what is still uncertain.

## What this tool does

Given a level WAD such as `t1l1m001.wad`, the extractor can:

- scan the WAD container and write a chunk manifest
- extract level metadata such as the level name
- decode the `TEXT` chunk into texture/control-map diagnostic PNGs
- export the `TEXT` palette table and palette-field debug images
- parse the `MAP ` chunk into world-space tile XYZ data
- generate MAP CSV files, OBJ marker meshes, a PNG grid, and an HTML map viewer
- parse the `LGHT` chunk into `lights.csv`
- decode the `TRAK` chunk into records, vertex/triangle tables, OBJ surfaces, and an HTML viewer
- export `STPC` static geometry as OBJ meshes
- export a `world/` folder that combines TRAK terrain with experimental MAP-object → STPC mesh instances
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
--no-world-rebuild    skip experimental TRAK + MAP-object + STPC world rebuild probe
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
    texture_00_grey.png
    texture_00_pal.png
    ...

  texture_fields/
    texture_00_field0_meta0.png
    texture_00_field1_meta1.png
    texture_00_field2_meta2.png
    texture_00_field3_marker.png
    texture_00_field4_rgb_r.png
    texture_00_field5_rgb_g.png
    texture_00_field6_rgb_b.png
    texture_00_field7_extra.png
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
    terrain_trak.obj
    map_object_markers.obj
    stpc_instances_combined.obj
    stpc_instances_by_object/
    world_combined_probe.obj
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


## How to inspect the experimental world rebuild

The `world/` folder is the current best world-regeneration probe. It uses the executable-confirmed relationship:

```text
TRAK = terrain / world-sector triangle geometry
MAP  = object placement records with confirmed 12.12 fixed-point XYZ
STPC = mesh bank plus object-definition/script data referenced by MAP objects
```

For each MAP object record, the game converts the object-definition field to:

```c
dword_6D9DBC + stpc_object_def_offset
```

where `dword_6D9DBC` is the raw STPC chunk base. The exporter scans each referenced STPC object-definition window for exact little-endian `u32` values that match decoded STPC mesh-record offsets. When it finds a match, it exports that STPC mesh translated to the confirmed MAP object XYZ.

### `world/terrain_trak.obj`

The decoded TRAK terrain/world surface.

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

### `world/stpc_instances_combined.obj`

All STPC mesh-reference hits translated to MAP object XYZ. Rotation and scale are not applied yet.

### `world/stpc_instances_by_object/`

One OBJ per MAP object that had at least one STPC mesh-reference hit. This is usually easier to inspect than the combined file.

### `world/world_combined_probe.obj`

A combined diagnostic OBJ containing TRAK terrain plus translated STPC candidate instances.

### `world/world_viewer.html`

A lightweight object-placement viewer. Orange points have at least one STPC mesh-reference hit. Blue points are MAP object records without a current mesh match.

### Deprecated: `world_probe/`

The older Section-4 `world_probe/` diagnostics are now opt-in via `--world-probe`. The executable-confirmed MAP loader showed that Section 4 is not the main STPC placement table, so the new `world/` rebuild probe should be used instead.

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

## LZSS compression

The game uses an LZSS-style compression scheme in texture/control-map data.

```text
Read control byte b.

If (b & 0x80) == 0:
    literal run
    copy next (b & 0x7F) bytes directly

If (b & 0x80) != 0:
    read byte c
    w      = (b << 8) | c
    offset = w & 0x0FFF
    length = ((w >> 12) & 7) + 3
    copy length bytes from dst[dp - offset]
```

Important detail: the currently confirmed decompressor uses a fixed back-reference source for each byte in the run.  It does not use a sliding `dst[dp - offset + i]` source.

## `TEXT` chunk structure

Despite the name, `TEXT` is not a text-string chunk.  It contains texture/control-map byte planes and a palette/metadata table.

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

- The direct `pixel_byte -> first 256 palette entries` mapping is only a diagnostic view.
- Palette counts can exceed 256, while texture byte values are only 0..255.
- The full material/palette remapping logic is not fully decoded yet.
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

## `STPC` chunk structure

`STPC` contains static polygon geometry.  The exporter scans for validated mesh records and writes OBJ files.

Recognized mesh record layout:

```text
+0x00  u32/f32   unknown block field
+0x04  f32       unknown / local bound field
+0x08  f32       unknown / local bound field
+0x0C  8 x vec3  local bounding/corner vectors, 96 bytes
+0x6C  u32       packed counts:
                  low 16 bits  = vertex_count
                  high 16 bits = triangle_count
+0x70  u32       unknown
+0x74  u32       unknown
+0x78  u32       unknown
+0x7C  u32       unknown
+0x80  u32       unknown
+0x84  u32       repeated vertex_count
+0x88  u32       unknown
+0x8C  vertices  vertex_count * 24 bytes:
                  f32 x, y, z
                  f32 nx, ny, nz
...    triangles triangle_count * 28 bytes:
                  u16 face_flags
                  u16 i0, i1, i2
                  u16 material_or_texture_id
                  u16 unknown
                  f32 plane_nx, plane_ny, plane_nz, plane_d
```

Known uncertainty:

- The full STPC container is not decoded yet.
- Mesh records are found with a validated scanner, not a complete table-driven parser.
- Unknown bytes between mesh records may contain collision data, BSP/spatial partitioning, visibility, batching, material lookup tables, or other render metadata.
- OBJ material IDs are diagnostic placeholders; texture/material binding is not fully decoded.

## `TRAK` chunk structure

`TRAK` is now structurally decoded from the game executable loader.  In the WAD file the tag bytes are stored reversed as `KART`, but the chunk name shown by this tool is `TRAK`.

The loader path observed in the executable is:

```text
sub_42AAC0
  reads the whole TRAK chunk
  reads first uint32 as record_count
  calls sub_5563F0(&cursor, record_count, &dword_5846EC)

sub_5563F0
  treats the first table as record_count records of 0x84 bytes
  assigns three runtime pointers inside each record
  rewrites a field in every Table B entry into a pointer to dword_581154 + 20 * index
```

Confirmed packed layout:

```text
u32 record_count

repeated record_count times, 0x84 bytes each:
    +0x00  vec3 center
    +0x0C  vec3 corners[8]
    +0x6C  u16 table_a_count
    +0x6E  u16 table_b_count
    +0x70  u32 runtime_table_a_pointer_slot, overwritten by game loader
    +0x74  u32 runtime_table_b_pointer_slot, overwritten by game loader
    +0x78  u16 table_c_count
    +0x7A  u16 table_d_count
    +0x7C  u16 table_e_count
    +0x7E  u16 padding_or_unused
    +0x80  u32 runtime_table_cde_pointer_slot, overwritten by game loader

then, for every record in order:
    Table A:   table_a_count * 24 bytes
    Table B:   table_b_count * 28 bytes
    Table CDE: (table_c_count + table_d_count + table_e_count) * 32 bytes
```

Table A decodes as point/normal data:

```text
f32 x, y, z
f32 nx, ny, nz
```

Table B decodes as indexed triangle/plane/material-like data:

```text
u16 flags
u16 i0, i1, i2
u16 material_or_global_table_index
u16 unknown
f32 plane_nx, plane_ny, plane_nz, plane_d
```

Table C/D/E entries are located and exported, but their field meanings are still unknown.

Current interpretation:

- TRAK is probably not a free camera spline.
- It looks more like level spatial sectors, navigation/collision surfaces, camera constraints, or track graph data.
- `trak/table_b_surfaces.obj` exports all decoded Table A/B triangle surfaces as one combined OBJ.
- `trak/per_record_surfaces/` exports one OBJ per TRAK record/sector, which is easier to inspect than the combined mesh.
- `trak/record_aabbs.obj` exports visible diagnostic bounding boxes derived from decoded Table A vertices.
- `trak/record_centers.obj` exports visible center markers.
- `trak/record_header_vectors_diagnostic.obj` preserves the raw 8-vector record-header diagnostic, but those vectors are not treated as final geometry.
- `trak/viewer.html` previews the decoded Table A/B triangle surfaces with auto-fit, height coloring, pan/zoom, and hover details.

Known uncertainty:

- The exact gameplay role of TRAK is not confirmed.
- Table C/D/E semantics are not decoded.
- The 20-byte global table at `dword_581154`, referenced by Table B material/global indices, is not decoded yet.
- The Table B `flags`, `unknown`, and material/global table index meanings are not fully decoded.

## `LGHT` chunk structure

`LGHT` contains light entries.

Observed layout:

```text
u32 count
repeated entries:
    u8 type
    u8 red
    u8 green
    u8 blue
    f32 f0
    f32 f1
    f32 f2
    f32 f3
    f32 f4
```

Known uncertainty:

- The meaning of `f0..f4` depends on light type and is not fully decoded.
- They may encode direction, position, radius, falloff, or intensity depending on the light.

## Chunks and files not fully decoded yet

These are preserved in `raw/` for later analysis:

| Chunk | Raw output | Current status |
|---|---|---|
| `STPC` | `raw/stpc.bin` | Static mesh records decoded; full container, material binding, collision/BSP unknown |
| `SMPC` | `raw/smpc.bin` | Not decoded; likely sprite/mesh compressed or related geometry data |
| `SRPC` | `raw/srpc.bin` | Not decoded; likely sound/resource config |
| `TRAK` | `raw/trak.bin`, `trak/` | Main record table and A/B/CDE table packing decoded; A/B exported as surfaces; C/D/E semantics still unknown |
| `AMPC` | `raw/ambient_audio.bin` | Exported raw; semantic structure not decoded |
| `LGPC` | `raw/lgpc.bin` | Not decoded; may relate to lighting/geometry/collision |
| `WFPC` | `raw/wfpc.bin` | Not decoded |
| `FONT` | `raw/font.bin` | Exported raw; glyph layout not decoded |
| `MAP ` | `map/` outputs | Tile list/grid partially decoded; flags/type semantics still unknown |
| `TEXT` | `textures/`, `palette/` | Compression and palette table parsed; material remap/field semantics still unknown |
| `LGHT` | `lights/lights.csv` | Light entries parsed; exact field semantics still unknown |

## What is left to do

Useful next reverse-engineering tasks:

1. Validate MAP-object → STPC-definition → STPC-mesh references visually in `world/world_combined_probe.obj`.
2. Decode MAP object rotation/scale fields and apply them to `world/stpc_instances_combined.obj`.
2. Decode `MAP ` `flags` and `type_idx` values.
3. Decode texture/material binding between `STPC` triangle material IDs and `TEXT` palette/texture data.
4. Decode TRAK Table C/D/E semantics and the 20-byte global table at `dword_581154` used by Table B material/global indices.
5. Identify whether `SMPC`, `LGPC`, or `WFPC` contain collision, visibility, portals, sprites, or runtime placement tables.
6. Replace the STPC mesh scanner with a full container parser once the top-level tables are understood.
7. Build a real 3D viewer that loads `MAP ` marker data, `STPC` render geometry, and `TRAK` sector/surface data together.

## Module overview

```text
wad_extractor.py          main command-line entry point

eng_wad/binary.py         Reader, endian helpers, hexdump helper
eng_wad/lzss.py           LZSS decompressor
eng_wad/wad.py            WAD chunk scanner/container utilities
eng_wad/text_chunk.py     TEXT parser and texture/palette exports
eng_wad/map_chunk.py      partial-safe MAP parser
eng_wad/map_export.py     MAP CSV, PNG, OBJ, and HTML viewer exports
eng_wad/world_rebuild.py  experimental TRAK + MAP-object + STPC world rebuild probe
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
