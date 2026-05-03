# Emperor's New Groove `.DEM` Demo Playback Tools

Small reverse-engineering tools for the standalone `.DEM` files found next to some *The Emperor's New Groove* level data.

These files are **not WAD files** and are not WAD chunks. They appear to be sidecar files used by the game for recorded demo playback, attract-mode input, scripted controller input, or a similar replay system.

## Confirmed file structure

The PC executable playback path loads `Wads/<name>.DEM`, reads a 32-bit frame count, and consumes one 8-byte record per playback tick.

```c
struct DEMFile {
    uint32_t frame_count;
    DemoFrame frames[frame_count];
};

#pragma pack(push, 1)
struct DemoFrame {
    uint16_t buttons;      // +0x00 PlayStation-style controller button mask
    uint16_t base_angle;   // +0x02 copied to word_5FCF00
    uint16_t aux_u16;      // +0x04 copied to dword_58471C; no later use confirmed yet
    int8_t   analog_x;     // +0x06 sign-extended by game, then << 6
    int8_t   analog_y;     // +0x07 sign-extended by game, then << 6
};
#pragma pack(pop)
```

The file size should be:

```text
4 + frame_count * 8
```

## Field notes

### `buttons`

The first 16-bit value uses the standard PlayStation-style button bit layout that was tested against the game.

| Bit mask | Name |
|---:|---|
| `0x0001` | SELECT |
| `0x0002` | L3 |
| `0x0004` | R3 |
| `0x0008` | START |
| `0x0010` | UP |
| `0x0020` | RIGHT |
| `0x0040` | DOWN |
| `0x0080` | LEFT |
| `0x0100` | L2 |
| `0x0200` | R2 |
| `0x0400` | L1 |
| `0x0800` | R1 |
| `0x1000` | TRIANGLE |
| `0x2000` | CIRCLE |
| `0x4000` | CROSS |
| `0x8000` | SQUARE |

### `base_angle`

This is copied by the playback code to `word_5FCF00`. It commonly behaves like a 12-bit angle:

```text
angle_degrees = (base_angle & 0x0FFF) * 360 / 4096
```

The high nibble is preserved and exported, but its exact meaning is not fully named yet.

### `aux_u16`

This is the old `field4` + `field5` pair combined as one little-endian 16-bit value.

```text
aux_u16 = byte4 | (byte5 << 8)
```

The playback code copies it to `dword_58471C`. No later use has been confirmed yet, so the tools preserve it exactly and label it `aux_u16` rather than guessing a final meaning.

### `analog_x` and `analog_y`

The old `field6` and `field7` are signed int8 analog axes, not unsigned bytes centered on `0x80`.

```text
0x00 = 0
0x7F = +127
0x80 = -128
0xFF = -1
```

The game sign-extends each byte and shifts it left by 6:

```c
analog_x_scaled = (int8_t)analog_x_raw << 6;
analog_y_scaled = (int8_t)analog_y_raw << 6;
```

Observed sign convention from the fallback digital path:

```text
analog_x > 0 = left
analog_x < 0 = right
analog_y > 0 = up / forward
analog_y < 0 = down / backward
```

## Tools

### `dem_unpacker.py`

CLI decoder/exporter. It writes:

| File | Purpose |
|---|---|
| `summary.json` | Basic file metadata, field ranges, common values, and button usage |
| `frames.csv` | One decoded row per frame |
| `runs.csv` | Run-length encoding of identical 8-byte frame records |
| `viewer.html` | Lightweight generated timeline viewer |

Usage:

```bash
python dem_unpacker.py T1L1M001.DEM -o dem_out/T1L1M001
python dem_unpacker.py T1L1M001.DEM T1L2M001.DEM -o dem_out
```

### `DEM_Editor.html`

Standalone browser editor. It can open, edit, and export `.DEM` files locally without a server.

The editor now displays:

```text
buttons
base_angle
aux_u16
analog_x_s8
analog_y_s8
```

It writes the original 8-byte frame layout back out, preserving endianness and signed analog byte encoding.

## Current limitations

`aux_u16` is not fully named yet. It is known to be copied into the executable global `dword_58471C`, but no later consumer has been confirmed in the currently inspected code.

Playback rate is still best described as input frames/ticks. The tool gives 30 FPS and 60 FPS duration estimates as convenience only.

## Legal / preservation note

This project is for interoperability, research, modding, and preservation of file formats. It does not include original game assets.
