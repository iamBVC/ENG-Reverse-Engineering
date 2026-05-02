# Emperor's New Groove `.DEM` Demo Playback Tools

A small reverse-engineering project for the standalone `.DEM` files found next to some *The Emperor's New Groove* level data.

These files are **not WAD files** and are not WAD chunks. They appear to be separate sidecar files used by the game for recorded demo playback, attract-mode input, scripted controller input, or a similar replay system.

This project is intentionally separate from the WAD extractor project.

---

## What is a `.DEM` file?

In the tested files, `.DEM` appears to store a sequence of fixed-size controller/input frames.

A `.DEM` file starts with a 32-bit little-endian frame count, followed by that many 8-byte frame records.

Example files tested:

| File | Size | First `uint32` | Expected size | Notes |
|---|---:|---:|---:|---|
| `T1L1M001.DEM` | 7,204 bytes | 900 frames | `4 + 900 × 8 = 7204` | Valid fixed-record layout |
| `T1L2M001.DEM` | 6,004 bytes | 750 frames | `4 + 750 × 8 = 6004` | Valid fixed-record layout |

This strongly suggests the file layout is:

```c
struct DEMFile {
    uint32_t frame_count;
    DemoFrame frames[frame_count];
};

struct DemoFrame {
    uint16_t buttons_or_flags;
    uint16_t angle_or_heading;
    uint8_t  field4;
    uint8_t  field5;
    uint8_t  field6;
    uint8_t  field7;
};
```

All integer values are currently assumed to be **little-endian**, matching the WAD files and the tested `.DEM` data.

---

## Current interpretation

The current best hypothesis is:

> `.DEM` files are recorded input streams used for demo playback.

That means each 8-byte frame likely represents one game tick, video frame, or input-sampling frame.

The first 2 bytes appear to behave like a button bitfield. The next 2 bytes appear to behave like an angle, heading, or directional value. The final 4 bytes are still under investigation.

---

## File format notes

### Header

Offset | Size | Type | Meaning
---:|---:|---|---
`0x00` | 4 | `uint32` | Number of frame records in the file

The file size should be:

```text
4 + frame_count * 8
```

If the file size does not match this formula, the file may use a different version, contain trailing data, or not be a `.DEM` playback file of this type.

---

### Frame record

Each frame record is 8 bytes:

Offset inside frame | Size | Type | Current name | Current interpretation
---:|---:|---|---|---
`+0x00` | 2 | `uint16` | `buttons_or_flags` | Likely controller button bitfield
`+0x02` | 2 | `uint16` | `angle_or_heading` | Likely 12-bit angle/heading value, often in range `0..4095`
`+0x04` | 1 | `uint8` | `field4` | Unknown; often `0x00` or `0x80` in tested files
`+0x05` | 1 | `uint8` | `field5` | Unknown; often `0x01` in tested files
`+0x06` | 1 | `uint8` | `field6` | Unknown analog-like byte
`+0x07` | 1 | `uint8` | `field7` | Unknown analog-like byte

---

## Tentative button mapping

The `buttons_or_flags` field appears compatible with a PlayStation-style button mask, but this is **not fully confirmed** yet.

Current tentative names:

Bit mask | Tentative meaning
---:|---
`0x0010` | Up
`0x0020` | Right
`0x0040` | Down
`0x0080` | Left
`0x0400` | L1
`0x0800` | R1
`0x2000` | Circle
`0x4000` | Cross
`0x8000` | Square

Important: these may be raw controller bits, game-normalized action bits, or a transformed input state. More files and executable analysis are needed before treating this as final.

---

## Angle / heading field

The second 16-bit field is currently named `angle_or_heading`.

It often looks like an angular value rather than a normal counter or arbitrary flag field. A common game representation is a 12-bit angle where:

```text
0..4095 = one full rotation
```

If this is true, conversion to degrees would be:

```text
degrees = angle_or_heading * 360.0 / 4096.0
```

This is still a hypothesis. It may represent:

- player movement heading
- camera heading
- analog stick angle
- actor facing direction
- a packed direction/state value

---

## What the tool exports

The current script is `dem_unpacker.py`.

It reads one or more `.DEM` files and exports human-readable reverse-engineering outputs.

For each input file, it can write:

File | Purpose
---|---
`summary.json` | Basic file metadata, frame count, value ranges, common values, and button usage
`frames.csv` | One decoded row per frame
`runs.csv` | Run-length encoding of repeated frame records
`viewer.html` | Simple timeline viewer for visual inspection

---

## Installation

This project has no required third-party dependencies.

Use Python 3.10 or newer.

```bash
python --version
```

Recommended:

```text
Python 3.10+
```

---

## Usage

Decode one `.DEM` file:

```bash
python dem_unpacker.py T1L1M001.DEM -o dem_out/T1L1M001
```

Decode multiple `.DEM` files:

```bash
python dem_unpacker.py T1L1M001.DEM T1L2M001.DEM -o dem_out
```

The output directory will contain CSV/JSON files and an HTML viewer.

---

## Recommended workflow

Start by exporting CSV and summary data:

```bash
python dem_unpacker.py T1L1M001.DEM -o dem_out/T1L1M001
```

Then inspect:

```text
dem_out/T1L1M001/summary.json
dem_out/T1L1M001/frames.csv
dem_out/T1L1M001/runs.csv
```

Open the viewer in a browser:

```text
dem_out/T1L1M001/viewer.html
```

Use `runs.csv` to find long stretches where the input state is unchanged. This is useful for understanding repeated movement, waiting, or camera-demo segments.

---

## Why `runs.csv` is useful

A raw frame list can be hard to read because demo files may contain hundreds or thousands of frames.

`runs.csv` compresses repeated records into ranges like:

```text
start_frame,end_frame,length,buttons_or_flags,angle_or_heading,field4,field5,field6,field7
```

This makes it easier to see patterns such as:

- holding one direction for many frames
- pressing a button briefly
- repeated idle frames
- changes in heading or analog values

---

## Current limitations

The following parts are **not fully decoded** yet:

### `buttons_or_flags`

Likely a button bitfield, but the exact mapping needs confirmation against:

- in-game behavior
- more `.DEM` files
- executable code that reads `.DEM` data
- controller input structures

### `angle_or_heading`

Likely an angle or directional value, but it is not yet known whether it controls:

- player facing
- movement direction
- camera direction
- analog stick direction
- scripted actor heading

### `field4`

Unknown. In tested files it is often `0x00` or `0x80`.

Possible meanings:

- analog stick X sign/axis mode
- camera/input mode flag
- playback state flag
- padding or high byte of a larger packed value

### `field5`

Unknown. In tested files it is often `0x01`.

Possible meanings:

- input device index
- active/enabled flag
- constant record marker
- player index

### `field6` and `field7`

Unknown analog-like bytes.

Possible meanings:

- analog stick X/Y
- movement intensity
- camera stick values
- trigger pressure or normalized direction components
- packed signed bytes

### Playback rate

The exact playback rate is not confirmed.

Possibilities:

- 30 frames per second
- 60 frames per second
- one input sample per game logic tick
- variable depending on platform or region

Until confirmed, the tool should describe entries as **frames** or **samples**, not seconds.

---

## Things left to reverse engineer

Useful next steps:

1. Collect more `.DEM` files from other levels.
2. Compare file names to level names and WAD names.
3. Check whether `.DEM` playback appears in attract mode, title-screen demos, or level intros.
4. Search the executable for `.DEM` loading code.
5. Search for code that reads `frame_count` and then advances by 8 bytes per frame.
6. Compare button bit changes against visible gameplay in the demo.
7. Determine whether `angle_or_heading` is a 12-bit angle by plotting it over time.
8. Test whether `field6` and `field7` behave like signed analog axes.

---

## Suggested future project structure

If this grows beyond one script, use this structure:

```text
eng_dem_tools/
  README.md
  dem_unpacker.py
  eng_dem/
    __init__.py
    binary.py
    dem_file.py
    export_csv.py
    export_html.py
```

Suggested module responsibilities:

File | Responsibility
---|---
`binary.py` | Little-endian helpers and safe binary reader
`dem_file.py` | `.DEM` parser and decoded frame dataclasses
`export_csv.py` | `frames.csv`, `runs.csv`, and summary exports
`export_html.py` | Standalone timeline viewer generation
`dem_unpacker.py` | Command-line entry point

---

## Naming note

The `.DEM` extension likely means **demo**, but this is still a reverse-engineering assumption.

This project should avoid claiming the format is fully understood until the unknown fields and playback code are confirmed.

---

## Legal / preservation note

This project is for interoperability, research, modding, and preservation of file formats.

It does not include original game assets.
