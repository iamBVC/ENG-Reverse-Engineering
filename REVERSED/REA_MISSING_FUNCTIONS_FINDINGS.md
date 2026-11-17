# Recovered string and angle functions

## Target and evidence

Target: `Game/groove.exe`, SHA-256 `151102050d79c0cc703d121e7755f7bb75f436d5822d31e72a43c31cc1adb9bc`.

REA 6.4.0 with Ghidra 12.1.4 produced these native dossiers:

| Function | Evidence | Static finding |
| --- | --- | --- |
| `0x404DB0` | `ev_07c655693e59d3d8d8c8b3f6efde69be35973dac66fe84d25d69c4e580f35d60` | The original computes fixed point X/Y/Z deltas, overwrites the Y-square temporary with the Z square, uses x87 `FPATAN`/`FSQRT` and the constants at `0x56e020`, `0x56e070`, and `0x56e078`, then masks each turn to 12 bits. The recovered body follows that instruction sequence. |
| `0x413C40` | `ev_91e4a9024a67e4c394de814318d9acf145dd5d5f5dbaf6b19279e38937fc3c0c` | This is a string-buffer growth helper with its destination object in `ECX`. REA found four callers: `0x413B20`, `0x413F10`, `0x414160`, and `0x414390`. |
| `0x414030` | `ev_5457c55079387e0c36d7e2291d4328bca423126388c8689956122e0be99f3502` | This copies a string, appends a NUL-terminated suffix, and copies the result to its destination. The original assembly sets `ECX` for both `0x414160` calls and for `0x413F10`; the recovered body supplies those receivers. |

Caller dossiers confirm the receiver registers for the four growth paths:

- `0x413B20`: `ECX = EBP` (`param_2`), evidence `ev_97ff601d4cbf4de8693ad99c329442b2e166a3108dcf07d35f9b0028ba6a1b17`.
- `0x413F10`: `ECX = ESI` (the string object, `param_1`), evidence `ev_8183808322c8af11c1ed5e3841415692dfbc31a2f4dcf188215ac55dedb4b0e1`.
- `0x414160`: `ECX = EBP` (the destination object, `param_1`), evidence `ev_037f031aff7b04284f0d94b8ebe9820e6096f4eb241239801b9a726d84d95407`.
- `0x414390`: `ECX = EBP` (the string object, `param_1`), evidence `ev_02d0830027d9ff523a0d7f1e8cc37cad10a7c97866de86a60e8bc690b7c777f9`.

These are shipped-binary static observations, not proof of runtime equivalence. The complete REA records are retained in `build/rea_missing_functions_evidence.json` and `build/rea_string_callers_evidence.json`.

## Build and current runtime result

The latest user-visible run of the prior build showed the logo and then a cyan screen. Its trace selected the Direct3D HAL, completed texture upload, submitted menu quads, and presented frames. The 15 texture sources had varied nonzero hashes, but every uploaded texture surface read back as zero. That run did not crash before the eight-second watchdog stopped it.

## Palette construction and relocated global state

`sub_436E30` is called by `sub_407240` after the texture histogram is built and before the generated palette is attached to the DirectDraw surface. The earlier bulk build satisfied it with a logging stub, so `src_recovered/sub_436E30.c` now restores its median-cut algorithm using the existing split-box, histogram, and palette helpers. This removed one missing function, but did not by itself fix the cyan frame.

The later run showed the more direct defect in `sub_436CC0`: its decompiled loop increments a pointer to the 256-entry RGB square table and stops when that pointer reaches the original executable address `0x61ff34`. In the rebuilt process the table is relocated, so that absolute-address comparison is false at the first iteration. The table stayed zero, and `sub_436D40` then accumulated zero squared-color values, preventing useful palette partitions.

`src_recovered/sub_436CC0.c` now initializes exactly 256 square values with a count-bounded loop. `type_overrides.csv` declares the table's 0x400-byte extent so generated globals reserve all entries. `tools/test_palette_histogram_layout.py` first failed because the generated header exposed only a scalar and then failed at runtime because the decompiled address comparison left entry 1 at zero. It now passes the square-table checks, RGB555 histogram, palette build, and texture-index remap.

## RGB555 palette conversion lost from decompiled C

The original `0x4083A0` disassembly reads each 16-bit source texel, extracts the three 5-bit RGB channels, scales them with the float constants at `0x56e12c`, `0x56e124`, and `0x56e11c`, then converts with the truncating x87 helper at `0x5626f0`. The decompiled C had only three `__ftol()` calls and omitted the loads and multiplies, so the rebuilt routine emitted black palette entries. `src_recovered/sub_4083A0.c` now follows the observed channel masks, truncation (including the original maximum channel value of 254), opaque alpha, and transparent-black marker.

`tools/test_rgb555_palette_conversion.py` exercises all 32 values in each channel and both transparent-black cases. It failed against the old decompile and passes against the recovered function. `tools/test_menu_texture_conversion.py` also passes. After clearing the now-obsolete `sub_4083A0` entry from the compile exclusion list, `make_bulk.py` and `compile_check.py` accepted 1502 functions with no errors, and the full bulk DLL and EXE build linked successfully.

## RGB555 surface conversion omitted from decompiled C

The active non-palettized texture callback is `0x408470`. In the decompiled C, each nonzero texel reaches four `__ftol()` calls without first loading or scaling the source channels. The original assembly at `Game/groove.exe.asm` performs those operations: it scales the low, middle, and high RGB555 fields into the destination red, green, and blue masks using constants at `0x56e11c`, `0x56e124`, and `0x56e12c`, then adds the destination alpha mask. The missing x87 operations explain the zero pixels seen in the uploaded surfaces.

`src_recovered/sub_408470.c` restores the assembly's channel mapping, 8/16/32-bit writes, source and destination pitch handling, and zero-texel transparency. `tools/test_rgb555_surface_conversion.py` failed against the decompiled body at the first RGB channel assertion. It now passes for all three destination depths, verifies alpha and row padding, and the existing palette, menu conversion, and upload tests continue to pass. The game-visible result still requires a desktop run of the rebuilt executable.

After the `sub_436CC0` repair, the full bulk DLL and EXE were rebuilt and copied into `build/run`. The palette-pipeline regression test passes. A bounded launch from the isolated Codex account reached adapter enumeration but did not reach the user's hardware-rendered frame path, so it cannot verify the visible result. The next check must be the user's desktop launcher; menu rendering after this fix remains unverified.
