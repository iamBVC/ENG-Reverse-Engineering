# COR2IMG

A small Python utility for converting *The Emperor's New Groove* `.COR` loading-screen image files to common image formats such as PNG, JPEG, WebP, BMP, and TIFF — and converting standard images back into valid `.COR` files.

The tool includes a reverse-engineered `.COR` reader/writer, an LZSS decompressor, and a safe literal-only encoder for generating game-compatible `.COR` files.

## Features

- Convert `.COR` files to:
  - PNG
  - JPEG / JPG
  - WebP
  - BMP
  - TIFF
- Convert standard image files back to `.COR`
- Batch-convert entire folders
- Convert multiple explicit files in one command
- Automatically resizes imported images to the required `640x480` RGB format
- Validates `.COR` magic values before decoding
- Includes a simple Windows batch launcher for drag-and-drop style usage

## Requirements

- Python 3.10 or newer is recommended
- [Pillow](https://pypi.org/project/Pillow/)

Install the required dependency:

```bash
pip install Pillow
```

## Files

| File | Description |
| --- | --- |
| `cor2img.py` | Main command-line converter for `.COR` files and standard images. |
| `COR2PNG.bat` | Minimal Windows batch wrapper that runs `cor2img.py` on the file passed to it. |

## Quick Start

Convert a single `.COR` file to PNG:

```bash
python cor2img.py mountain.cor
```

This creates:

```text
mountain.png
```

Convert a `.COR` file to another image format:

```bash
python cor2img.py mountain.cor --format jpg
python cor2img.py mountain.cor --format webp
python cor2img.py mountain.cor --format bmp
```

Convert a normal image back to `.COR`:

```bash
python cor2img.py replacement.png
```

This creates:

```text
replacement.cor
```

## Usage

```bash
python cor2img.py <input> [<input> ...] [--format FORMAT] [--out-dir OUTPUT_DIR] [--quality QUALITY]
```

### Arguments

| Argument | Description |
| --- | --- |
| `inputs` | One or more files or folders to convert. |
| `--format`, `-f` | Output image format when converting from `.COR`. Default: `png`. |
| `--out-dir`, `-o` | Optional output directory. If omitted, files are written next to the source file. |
| `--quality`, `-q` | Quality value used for JPEG and WebP output. Default: `90`. |

## Examples

### Convert one `.COR` file to PNG

```bash
python cor2img.py 111.cor
```

Output:

```text
111.png
```

### Convert one `.COR` file to JPEG

```bash
python cor2img.py 111.cor --format jpg --quality 92
```

Output:

```text
111.jpg
```

### Convert multiple `.COR` files

```bash
python cor2img.py 111.cor 112.cor 113.cor --format png
```

### Convert every supported file in a folder

```bash
python cor2img.py levels/
```

When a folder is passed, the tool searches for:

```text
*.cor, *.COR, *.png, *.jpg, *.jpeg, *.webp, *.bmp, *.tiff
```

### Convert a folder and write results elsewhere

```bash
python cor2img.py levels/ --format png --out-dir output/
```

### Convert an edited image back to `.COR`

```bash
python cor2img.py edited_loading_screen.png --out-dir cor_output/
```

Output:

```text
cor_output/edited_loading_screen.cor
```

## Windows Batch Usage

`COR2PNG.bat` is a minimal wrapper:

```bat
python cor2img.py "%~1"
```

You can drag a `.COR` file onto the batch file, or run:

```cmd
COR2PNG.bat 111.cor
```

The default output format is PNG.

## `.COR` Format Notes

The converter expects the `.COR` file to use the following header layout:

| Offset | Size | Field |
| --- | ---: | --- |
| `0x00` | 4 bytes | Magic 1: `0x89AF9817` |
| `0x04` | 4 bytes | Magic 2: `0x12D142FE` |
| `0x08` | 4 bytes | Version, expected to be `1` |
| `0x0C` | 4 bytes | Uncompressed payload size |
| `0x10` | 4 bytes | Compressed payload size |
| `0x14` | variable | LZSS-compressed RGB pixel payload |

Known image properties:

```text
Width:  640 px
Height: 480 px
Format: 24-bit RGB
Layout: row-major, top-to-bottom
```

The usual uncompressed payload size is:

```text
640 × 480 × 3 = 921600 bytes
```

## Compression Notes

### Decoding

`.COR` image data is decoded using an LZSS-style stream:

- Control bytes with the high bit clear describe literal byte runs.
- Control bytes with the high bit set describe back-references into already-decoded output.

### Encoding

The included encoder intentionally uses a simple literal-only strategy. This avoids expensive match searching and keeps the encoder predictable and fast.

Generated `.COR` files are valid, but they may be larger than original game files because they are not aggressively compressed.

## Image-to-COR Behavior

When converting a normal image into `.COR`:

1. The image is opened with Pillow.
2. It is converted to RGB.
3. It is resized to `640x480` if necessary.
4. It is written as a `.COR` file with a valid header and compressed payload.

This makes the tool suitable for replacing or editing loading-screen assets, provided the target game accepts the generated `.COR` file.

## Error Handling

The tool reports errors per file and continues processing the remaining inputs.

Examples of possible errors:

- Invalid `.COR` magic values
- File too small
- Incomplete decompression
- Unsupported input extension
- Pillow failing to read or write a file

If any file fails, the program exits with a non-zero status code.

## Supported Input Extensions

For folder batch conversion, the following extensions are detected:

```text
.cor
.COR
.png
.jpg
.jpeg
.webp
.bmp
.tiff
```

## Supported Output Formats

When converting from `.COR`, output support depends on Pillow, but the tool is intended for:

```text
png, jpg, jpeg, webp, bmp, tiff
```

## Project Status

This is a reverse-engineered utility for a legacy game image format. It is designed for modding, preservation, and asset research workflows.

## Disclaimer

This project is an unofficial tool and is not affiliated with Disney, Argonaut Games, or any original publisher/developer of *The Emperor's New Groove*.

Use it only with files you are legally allowed to inspect or modify.

## License

No license has been provided yet.

Before publishing this repository, consider adding an explicit license such as MIT, GPL-3.0, or another license appropriate for your intended use.
