# Emperor's New Groove WAD Tools

Python tools for extracting, inspecting, and partially rebuilding level `.WAD` files from *Disney's / Argonaut's The Emperor's New Groove*.

The repository is split into small modules so every chunk can be studied independently.  The short README gives the workflow and current status; the detailed reverse-engineering notes live in [`REVERSE_ENGINEERING_BIBLE.md`](REVERSE_ENGINEERING_BIBLE.md).

## What it can extract today

Given a level WAD such as `t1l1m001.wad`, the extractor can currently:

- scan the WAD container and write a chunk manifest
- extract simple metadata such as level name, version, light info, and SPRT material-base index
- decode `TEXT` RGB555 RLE textures to PNG
- export `TEXT` palette/material diagnostics
- parse `MAP ` tile placement data, grid data, object records, and executable-confirmed MAP diagnostics
- parse `LGHT` directional, point, and negative/special point lights to CSV
- decode `SMPC` level audio entries to `.cvg`, raw payloads, and WAV files
- decode `SRPC` streamed speech tables and, when `Music/ENGLISH.CVS` is available, export speech `.cvs` slices and WAV files
- decode `TRAK` terrain/world geometry records, vertices, triangles, collision/contact entries, OBJ surfaces, and an HTML viewer
- parse `STPC` with the executable-confirmed table/cursor layout and export all decoded geometry records as OBJ meshes
- generate a `world/` reconstruction using TRAK terrain, MAP object placement, and STPC mesh candidates
- preserve raw chunks for anything still unknown or only partially decoded

## Installation

Python 3.10+ is recommended.

```bash
pip install -r requirements.txt
```

Required dependency:

```text
Pillow
```

Optional dependency:

```text
ffmpeg   # only needed for --srpc-mp3
```

## Basic usage

Extract one WAD:

```bash
python wad_extractor.py t1l1m001.wad
```

Extract to a specific folder:

```bash
python wad_extractor.py t1l1m001.wad --out-dir extracted
```

Extract every `.wad` / `.WAD` file in a folder:

```bash
python wad_extractor.py wads/ --out-dir extracted
```

For SRPC speech extraction, place the matching CVS file next to the WAD as `Music/ENGLISH.CVS`, or pass it explicitly:

```bash
python wad_extractor.py t1l1m001.wad --srpc-cvs Music/ENGLISH.CVS
```

## Common options

```bash
--no-tex                 skip TEXT texture/palette extraction
--no-texture-fields      skip diagnostic palette-field images
--texture-channel-order  bgr or rgb; bgr is the corrected default
--no-map                 skip MAP parsing and map viewer exports
--no-map-full            skip executable-confirmed MAP diagnostics
--no-stpc-obj            skip STPC OBJ mesh export
--no-trak                skip TRAK CSV/OBJ/viewer export
--no-lights              skip LGHT light CSV export
--no-sounds              skip SMPC sound export
--no-srpc                skip SRPC speech-table export
--srpc-cvs PATH          explicit CVS file for SRPC speech extraction
--srpc-mp3               also create MP3 files when ffmpeg is available
--no-raw                 do not export preserved raw chunks
--no-world               skip reconstructed world export
--world-probe            run old deprecated Section-4 instance-hunting diagnostics
--quiet                  reduce per-record progress output
```

STPC options:

```bash
--stpc-alignment 1       legacy fallback scanner alignment; rarely needed
--stpc-min-score 0.80    lower fallback mesh-candidate acceptance threshold
--stpc-scale 0.01        scale STPC OBJ vertices
--stpc-flip-z            flip the Z axis in STPC OBJ export
--stpc-debug-faces       write stpc/faces_debug.csv
--stpc-force-scan        use the old candidate scanner instead of the table parser
```

TRAK options:

```bash
--trak-scale 0.01        scale TRAK OBJ vertices
--trak-flip-z            flip the Z axis in TRAK OBJ export
```

World reconstruction options:

```bash
--world-scale 0.01
--world-flip-z              default final Z-axis flip for world OBJ exports
--world-no-flip-z           disable the default final Z-axis flip
--world-def-scan-bytes 2048
--world-terrain-yaw-sign -1|1
--world-terrain-z-mirror
--world-stpc-object-z-sign -1|1
--world-stpc-local-z-sign -1|1
--world-no-stpc-yaw
--world-stpc-yaw-sign -1|1
--world-object-x-offset 0.0
--world-object-y-offset 0.0
--world-object-z-offset 0.0
```

## Output layout

Typical output:

```text
extracted/t1l1m001/
  info.txt
  level_name.txt

  raw/                  preserved source chunks
  textures/             decoded TEXT PNG textures
  texture_fields/       optional diagnostic field images
  palette/              palette/material diagnostics

  map/                  legacy/partial-safe MAP outputs
  map_full/             executable-confirmed MAP diagnostics
  lights/               LGHT CSV + summary

  sounds/               SMPC .cvg, WAV, raw payloads, manifest
  srpc/                 SRPC entries, CVS slices, WAV, optional MP3
  sprt/                 SPRT material-base summary and sprite material slots

  trak/                 TRAK CSV, OBJ surfaces, HTML viewer
  stpc/                 STPC geometry, script refs, OBJ/MTL files, local texture copies
  world/                reconstructed terrain + object candidates
  world_probe/          deprecated opt-in diagnostics
```

Useful first files to inspect:

| File | Why it matters |
|---|---|
| `info.txt` | Shows chunk order, offsets, sizes, and basic metadata. |
| `textures/*.png` | Decoded level texture pages. |
| `map_full/objects_58_disk.csv` | Executable-confirmed MAP object table. |
| `trak/viewer.html` | Interactive terrain/sector preview. |
| `stpc/manifest.csv` | Table-decoded STPC geometry records, offsets, matrix groups, and counts. |
| `stpc/script_geometry_refs.csv` | STPC script opcode `0xB2` references to decoded geometry records. |
| `sprt/sprite_material_slots.csv` | SPRT-derived sprite slots mapped onto TEXT runtime material rows. |
| `world/terrain_and_objects.obj` | Textured terrain plus placed STPC object instances in one OBJ. |
| `world/combined.obj` | Current best-effort diagnostic combined world reconstruction. |
| `lights/lights.csv` | Runtime-derived light positions, colors, radii, and types. |
| `sounds/smpc_manifest.csv` | Level sound table and decoded WAV metadata. |
| `srpc/srpc_entries.csv` | Speech table pointing into `ENGLISH.CVS`. |

## WAD container basics

A level WAD is a linear chunk container:

```text
+0x00  u32  total file size minus 4
+0x04  repeated chunks until EOF:
        char[4]  chunk tag, stored reversed on disk
        u32      chunk data size
        bytes    chunk data
```

Example: the human tag `TRAK` is stored as `KART` bytes.  The tool reverses tags when showing them to humans.

Known chunk tags seen in level WADs:

```text
INFO VERS WFPC TEXT FONT SPRT NAME SMPC AMPC SRPC TRAK STPC MAP  LGHT LNFO LGPC
```

`MAP ` includes a trailing space because tags are exactly four bytes.

## Current reverse-engineering status by chunk

Percentages are approximate and describe how much of each chunk is understood from executable analysis, successful exports, and field-level validation.  A high percentage does not always mean every runtime use is named; it means the extractor can safely interpret most important fields.

| Chunk | Reverse-engineered | Current tool support | Main remaining unknowns |
|---|---:|---|---|
| `INFO` | ~95% | Reads basic metadata value. | Exact meaning of minor metadata bits/fields. |
| `VERS` | ~95% | Reads version value. | None important for extraction. |
| `NAME` | ~90% | Extracts level name string. | Encoding edge cases. |
| `LNFO` | ~20% | Reads count/version-like values when present. | Full purpose and relation to `LGHT`. |
| `SPRT` | ~45% | Reads the executable-confirmed TEXT material-base index, optional flag-gated table when present, and exports sprite material slot diagnostics. | High-level sprite object records, animation/frame command semantics, and optional table purpose. |
| `TEXT` | ~80% | Decodes RGB555 RLE textures, palette, material diagnostics. | Some material flags, `extra` byte, and full binding semantics. |
| `FONT` | ~10% | Preserves raw bytes. | Glyph layout and font renderer mapping. |
| `SMPC` | ~80% | Exports `.cvg`, raw audio payloads, manifest, WAV. | Some CVG header semantics and uncommon channel/quality modes. |
| `SRPC` | ~85% | Exports speech table; decodes `.CVS` slices to WAV when CVS is available. | `unknown_00`, `unknown_06`, and exact AAL resource type name. |
| `AMPC` | ~10% | Preserves raw ambient/audio chunk. | Full structure and relation to SMPC/AAL. |
| `TRAK` | ~75% | Exports geometry records, vertices, triangles, collision entries, OBJ, viewer. | Header fields `+0x00/+0x04/+0x08/+0x7E`, collision group names, remaining triangle flags. |
| `STPC` | ~65% | Parses the confirmed top-level geometry cursor layout, including matrix-group/skinned records; exports OBJ/MTL, manifest, face diagnostics, and script-to-geometry references. | Object-definition VM semantics, animation record fields, Block32 semantics. |
| `MAP ` | ~60% | Parses tile placement, grid, object58 table, vertex colors, MAP diagnostics. | Section 3/4 semantics, some flags/type ids, complete object runtime behavior. |
| `LGHT` | ~90% | Exports directional, point, and negative/special point lights. | Final type-2/type-4 byte currently named `falloff_or_mode`; two copied runtime color fields. |
| `LGPC` | ~5% | Preserves raw bytes. | Structure and purpose unknown. |
| `WFPC` | ~5% | Preserves raw bytes. | Structure and purpose unknown. |

## Chunk summary

### `TEXT`

Contains texture pages and material/palette information.  Texture pixels are RGB555 RLE words, not normal 8-bit paletted image data.  The extractor writes PNGs and diagnostics.

### `MAP `

Contains level layout data: terrain tile placements, grid data, object records, vertex color blocks, and additional sections that are still partially named.  It does not appear to store final render geometry by itself; it places or references geometry from other chunks.

### `TRAK`

Stores the main world/terrain geometry record table.  Each decoded geometry record contains vertices, triangles, culling/bounds data, and collision/contact entries.  OBJ exports from this chunk are the best starting point for terrain analysis.

### `STPC`

Stores packed scene/static object data.  The tool now follows the executable-confirmed cursor parser: each `GeometryRecord8C` header is immediately followed by its matrix-group counts, vertices, triangles, and Block32 data.  The exporter also scans the script tail for opcode `0xB2` references back to decoded geometry offsets.  The old scanner remains available internally as a fallback.

### `LGHT`

Stores level lights.  Directional lights and point-like lights are mostly decoded.  Runtime conversion doubles color intensity to a `0.0..2.0` range and negates Z in several cases.

### `SMPC`

Stores level sound entries using CVG containers with PlayStation/SPU ADPCM-style payloads.  The extractor exports original `.cvg` files and decoded WAV files.

### `SRPC`

Stores streamed speech table entries into an external `.CVS` speech bank, normally `Music/ENGLISH.CVS`.  The WAD chunk contains offsets, sizes, and sample-rate scalars; the actual speech bytes live in the CVS file.

### `SPRT`

Stores sprite rendering metadata, not pixels.  The first `u32` is copied by the executable to `dword_5FF728` and used as a base index into the runtime `TEXT` material table.  Sprite rendering indexes materials approximately as `base + sprite_id * 2 + variant/frame`.  Current sample WADs only contain this 4-byte base value; the loader can read an optional `u32` table when `WFPC` flags include `0x100000`.

### Raw/low-knowledge chunks

`AMPC`, `FONT`, `LGPC`, `WFPC`, and parts of `LNFO` are preserved for later analysis.  `SPRT` now has confirmed material-base decoding, but the higher-level sprite/animation structures that consume those slots still need more runtime analysis.

## Development notes

The project intentionally separates confirmed structures from guesses:

- confirmed fields are backed by executable analysis, repeated samples, or successful runtime-style exports
- uncertain fields are named `unknown_*` or described as candidates
- raw chunks are preserved even when higher-level parsers exist, so future work can be validated against original bytes

Main modules:

```text
wad_extractor.py          command-line entry point
eng_wad/wad.py            WAD scanner/container utilities
eng_wad/binary.py         binary Reader and endian helpers
eng_wad/text_chunk.py     TEXT parser and PNG/palette exports
eng_wad/map_chunk.py      older partial-safe MAP parser
eng_wad/map_full_chunk.py executable-confirmed MAP parser/diagnostics
eng_wad/map_export.py     MAP CSV, PNG, OBJ, and HTML exports
eng_wad/trak_chunk.py     TRAK parser/exporter
eng_wad/stpc_chunk.py     STPC table parser/exporter plus scanner fallback
eng_wad/world_rebuild.py  TRAK + MAP + STPC reconstruction
eng_wad/light_chunk.py    LGHT parser/exporter
eng_wad/smpc_chunk.py     SMPC sound parser/exporter
eng_wad/srpc_chunk.py     SRPC speech parser/exporter
eng_wad/sprt_chunk.py     SPRT material-base parser/exporter
eng_wad/raw_export.py     raw chunk preservation
```

## What to work on next

1. Decode the STPC object-definition/script VM that points at the geometry records.
2. Finish naming MAP Section 3/4 and object-definition data.
3. Validate MAP object placement against more levels and in-game positions.
4. Name the remaining TRAK/STPC geometry header fields and collision group roles.
5. Finish decoding `AMPC`, `LGPC`, `WFPC`, `FONT`, and the remaining high-level `SPRT` sprite/animation consumers.
6. Build a single viewer that combines decoded textures, TRAK terrain, STPC objects, MAP placement, and LGHT lights.
