# REVERSED - rebuilding `groove.exe` in C

Source-level reconstruction of *The Emperor's New Groove* PC executable, with an
automated harness that compiles each reversed function and compares its machine
code against the original.

The reverse-engineering notes that feed this project live in
[`../WAD/REVERSE_ENGINEERING_BIBLE.md`](../WAD/REVERSE_ENGINEERING_BIBLE.md).

---

## Read this first: what is realistic

The target is **1,642,496 bytes of PE32** built by **Visual C++ 6.0**
(the PE linker version field says `6.0`), containing **1,213 functions** and
1,492,559 bytes of `.text`.

Two things follow, and they shape everything below:

**1. Byte-for-byte equality is only reachable with the original toolchain.**
The exact bytes a compiler emits depend on the compiler version, the flags, and
the link layout. This machine has MSVC 2022 (14.16-14.44) and MinGW GCC, not
MSVC 6. The harness shows what that costs - here is the whole of `sub_415AB0`,
which reads one dword:

```
original (27 B): 8b 44 24 04 85 c0 74 12 50 8b 44 24 0c 6a 01 6a 04 50 e8 ..
rebuilt  (27 B): 8b 44 24 04 85 c0 75 01 c3 50 6a 01 6a 04 50 e8 ..
                                    ^^^^^^^
```

Semantically identical; MSVC 6 falls through to the `retn` at the end, MSVC 2022
inverts the branch and emits its own early `ret`. Two bytes differ. No amount of
tidying the C fixes that - only the original compiler (or a source-permuter
search) does.

**2. Globals are addressed absolutely in this binary.** Any function that touches
data encodes the address inline, so bytes can only match if the rebuild reproduces
the *link layout* too. That is why the harness reports a second verdict,
`RELOC` (identical once absolute-address dwords are masked). `RELOC` is the
practical ceiling for an independently linked build.

So this project has two honest goals, and both are useful:

| Track | Goal | Success criterion |
|---|---|---|
| **A. Matching decomp** | readable C that, compiled with MSVC 6, reproduces the original bytes | `EXACT` verdicts; needs VS 6 in a VM/container |
| **B. Static recompilation** | a working, maintainable C rebuild of the game | behaviour verified against the original / the `eng_wad` reference |

The harness supports both. Nothing here claims the exe is finished: a full
matching decomp of a 2001 game is a multi-year, multi-contributor effort
(SM64/OoT-class projects). What is finished is the *machinery*, plus the first
functions.

---

## Current status

```
functions in the listing : 1,214
  real game functions    : 1,153      <- the actual work surface
  ILT thunks             :    59      <- linker artifacts, do not exist in a rebuild
  library-named          :     1
code bytes (game only)   : 1,491,599  (99.9 % of .text)
leaf game functions      :   381      134 of them are <= 32 bytes

ported                   :    25      16 exact-or-reloc-matching
  EXACT                  :     3      sub_408390, sub_4255A0, sub_426860
  RELOC                  :     9      identical modulo absolute addresses
  DIFF                   :    13      structurally equivalent, different codegen
self-test                : ALL TESTS PASSED (0 failures)
```

Ported so far - the small, fully understood primitives:

| Original | File | What it is |
|---|---|---|
| `sub_415A90`, `sub_415AD0`, `sub_415AB0`, `sub_415AF0` | [`src/gr_io.c`](src/gr_io.c) | the four `fread` wrappers every chunk loader is built from |
| `sub_41ED90` | [`src/gr_alloc.c`](src/gr_alloc.c) | secondary bump allocator (terrain renderer) |
| `sub_41EEA0`, `sub_41EEE0`, `sub_41EF00` | [`src/gr_alloc.c`](src/gr_alloc.c) | primary 16 MB block: create, rewind, bump-allocate |
| `sub_406E30`, `sub_408390`, `sub_40D900`, `sub_40D910`, `sub_40E020`, `sub_40E0A0`, `sub_40E610`, `sub_4136C0`, `sub_413B10`, `sub_4155E0`, `sub_41BCB0`, `sub_41D330`, `sub_41E1B0`, `sub_4255A0`, `sub_426860`, `sub_40FC90` | [`src/gr_small.c`](src/gr_small.c) | batch 1: leaf getters/setters, clearers, a float constant store, two zeroing blocks, a label formatter, `this`-returning initialisers |
| `sub_40DB70` | [`src/gr_pending.c`](src/gr_pending.c) | translated but not linkable yet (calls `sub_40D970`) |
| `groove_tile_cell_index` | [`src/gr_map.c`](src/gr_map.c) | spatial-hash cell index inlined in `sub_42AC50` (helper, not a 1:1 match target) |

---

## Layout

```
REVERSED/
  build.bat              compile + link (finds MSVC via vswhere)
  check.bat              byte-compare build/objects/*.obj against groove.exe
  functions.csv          generated work queue (1,213 rows, with per-function status)
  include/groove.h       confirmed structs + globals; offsets asserted at compile time
  src/                   the reversed translation units
  tools/
    pe_tools.py          PE32 reader; cuts any original function's bytes out of groove.exe
    coff_tools.py        COFF .obj reader; extracts one recompiled function's bytes
    gen_functions.py     builds functions.csv from WAD/groove.exe.asm
    bytecheck.py         the verifier (EXACT / RELOC / DIFF, --dump, --list)
    show_asm.py          print a function's listing verbatim (the workflow tool)
  build/                 generated: objects/ and groove_rebuild.exe   (gitignored)
  decompiled/            Ghidra output: one .c per function + _index/_functions/_data.csv
  src_generated/         generated from decompiled/ by tools/make_bulk.py (gitignored)
```

## Bulk decompilation (Ghidra)

Hand-porting 1,153 functions is not the only way in.  `tools/ghidra_decompile.bat`
runs Ghidra 12 headless over `groove.exe` and writes **one .c file per function**
into `decompiled/`, plus three CSVs (per-function status, signatures, and the data
symbol inventory with sizes).  `tools/make_bulk.py` then turns that into something
a compiler accepts, and measures how far it gets.

```bat
tools\ghidra_decompile.bat        :: ~8 min: analyse groove.exe and dump the C
python tools\make_bulk.py          :: generate globals, prototypes, bulk units
python tools\compile_check.py      :: chunked compile + per-function verdict
python tools\decompiled_report.py  :: audit what the decompiler emitted
```

What it produces today (`decompiled/` is committed, `src_generated/` is derived):

```
decompiled                         1,107 files, 1,109 functions ok, 2 failed
  no decompiler artefacts          1,030   <- the "clean subset"
  needs hand fixing (artefacts)       68   (unaff_EBP, in_stack_, extraout_*, ...)

compiling the clean subset (26 chunks of 40)
  compile cleanly                    901
  have a reported error              129   (700 errors; worst: sub_43CD60 with 31)

top error classes
  C2186  126   illegal operand of type void   (return value used where Ghidra said void)
  C2059  109   syntax                        (hand fixes)
  C2440   99   type conversion               (int/pointer mismatches)
  C2296   74   illegal left operand          (pointer used in arithmetic)
  C2143   64   syntax                        (hand fixes)
  C2065   48   undeclared identifier         (dropped locals, see below)

inventory reconciliation (entry points)
  IDA game functions                 1,153
  Ghidra functions                   1,111
  same entry address                   777
```

**Measure a chunked compile, never a single file.** The first version of this
report claimed 1,016 of 1,039 - it compiled the subset as one translation unit,
and MSVC stops after ~100 errors with C1003, so everything past the cap was never
checked.  `tools/compile_check.py` splits it into chunks of 40 so every function
gets a verdict; that is where the honest 901 comes from.

Two caveats on those numbers.  The two decompiler *failures* are enormous
function-shaped regions (150,625 bytes, with a 42 KB `alloca` in the prologue) -
generated code that needs a different approach.  And IDA and Ghidra disagree about
function boundaries: only 777 entry points line up, so the other 376 IDA
functions are either inside a Ghidra function's body (Ghidra did not split where
IDA did) or absent.  The code is decompiled either way; the *naming and
partitioning* are what need reconciling, which is why names in `decompiled/` are
Ghidra's `sub_<addr>` and may not match `functions.csv` one for one.

The mechanical layer that makes that possible lives in
[`include/ghidra_shim.h`](include/ghidra_shim.h) and in the normalizer inside
[`tools/make_bulk.py`](tools/make_bulk.py):

| Issue | What is done about it |
|---|---|
| pseudo-types (`undefined4`, `uint3`, `float10`, ...) | typedefs in the shim |
| `CONCATxy` / `SUBxy` / `ZEXTxy` intrinsics | bit-exact macros in the shim |
| Win32 types the decompiler emits (`DWORD`, `PVOID`, `RaiseException`, `_STARTUPINFOA`) | lean `windows.h` + aliases |
| `value._<offset>_<size>_` unnamed fields | rewritten to `G_BYTE`/`G_WORD`/`G_DWORD` (3-byte fields to `G_RD3`/`G_WR3`) |
| `DAT_xxxx_4`, `PTR_DAT_xxxx`, `s_Couldn't_open_mode_xxx` | sub-parts rewritten; non-identifier names renamed in the bodies |
| 1,582 referenced data symbols | definitions generated with the sizes from Ghidra's symbol table; string datums get their **real bytes** out of the executable |
| prototypes that disagree with their definitions (C2371) | taken from the definition Ghidra wrote, not from the CSV |
| `__alldiv`, `__frnd`, ... | left to the CRT (declaring them ourselves collides with the CRT headers) |
| call sites with different arities (C2197/C2198) | bulk prototypes are K&R-style `RET name();`; the hand-ported track keeps exact prototypes |
| `__thiscall` on a free function (C3865) | macro-dropped in C mode |
| `Unwind_*` / `Catch_*` SEH blocks | declared as unprototyped functions, never aliased onto data names |
| partial-register / dropped-local functions (68 + 9) | **excluded** and listed in `src_generated/report.txt` rather than papered over |

**Two honest caveats.**

1. *Compiles != verified.* The 1,016 compile; that says nothing yet about whether
they do the same thing.  Verification is the next layer: the harness for the
hand-ported functions, and the Python implementation in `../WAD/eng_wad/` as a
behavioural oracle for the loaders (feed it the shipped WADs and diff the output).
2. *SEH is deliberately not faithful yet.* Ghidra models the exception-chain head
   (`FS:[0]`) as an ordinary global; the shim defines it as one, with a comment.
   The 34 functions that install/restore exception frames (and the `Catch@...`
   handlers) therefore need a real `FS:[0]` accessor before their exception paths
   behave correctly.

## Verification layer (does it do the same thing?)

The byte check answers "is it the same code?" for the hand-ported track.  For the
decompiled bulk the useful question is different: do the two implementations
*behave* the same?  `harness/` builds two DLLs that expose the same wrappers and a
32-bit driver that calls both with identical inputs and compares the results.

```bat
python tools\make_bulk.py            :: generate the bulk units
python tools\compile_check.py        :: chunked compile (writes failed.txt)
python tools\make_getters.py         :: address-keyed accessors for the globals
python tools\make_verify_subset.py   :: curated, linkable subset of the decompiled code
harness\build_dlls.bat               :: build groove_ghidra.dll + groove_hand.dll
harness\run_verify.bat               :: build and run the differential driver
```

```
groove.exe differential verification
  primary bump heap (sub_41EF00)    12 allocations match (incl. the NULL on
                                    overflow and the negative-size rewind)
  secondary bump heap (sub_41ED90)   8 allocations match
  sub_4255A0 / sub_426860 / sub_4136C0   agree
  sub_406E30 / sub_4155E0 / sub_41D330 / sub_41E1B0 / sub_40E0A0   agree
  12 checks, 1 failure
```

### What the harness has already caught

1. **A real bug in this project's own generator.** It declared 4-byte globals as
   `unsigned int`, but the original compares them with *signed* instructions
   (`jle` in `sub_41EF00`).  The decompiled build therefore returned NULL for a
   negative size where the hand port rewound the heap - a genuine divergence.
   Defaulting those globals to `int` fixed it, and the same test now passes:
   harness finds it, fix, harness confirms.
2. **Ghidra lost the return value of the four `fread` wrappers** - it typed them
   as returning `void`, so `sub_415AB0` and friends cannot report how many bytes
   they read.  The hand ports are more faithful here.  This is exactly the kind of
   silent semantic gap a compile-only check would never show.
3. **An open anomaly**: `sub_41EEE0` (reset the primary heap) reports the same
   unchanged value on *both* sides.  Since the two implementations are
   independent, the fault is most likely in the harness wiring for that one case
   (a call not reaching the body), not in either implementation.  It is recorded
   rather than hidden.

### Real-data verification: the TRAK loader

`sub_5563F0` relocates the TRAK chunk's sub-arrays and rewrites the triangle
material references.  It is driven for real by `harness/drive_trak.c`, which
reproduces the original caller (`sub_42AAC0`) step for step - prime the bump heap,
allocate the chunk from it, call with `cursor = chunk + 4` - and dumps every
offset and material index it produced.  `tools/verify_trak.py` then checks that
dump against an independent computation from the same bytes.

```
python tools\verify_trak.py --wad t1l1m002.wad

t0i0m000  PASS  36 records,  1,889 triangle material indices
t1l1m001  PASS  127 records, 9,369
t1l1m002  PASS  131 records, 9,019
t1l1m003  PASS  133 records, 9,758
t1l1m004  PASS  87 records, 5,811
          ---
          514 records and 35,846 material indices, all matching
```

That is the decompiled code agreeing with the format spec on real shipped data:
the 132-byte header table, the 24/28/32-byte sub-array strides in the right order,
the zero-count "store NULL" rule, and the `materials_base + 20 * index` rewrite for
every single triangle in every shipped level.

### The MAP loader: compiles, runs, and is one stage short

`sub_42AC50` (656 decompiled lines) is now built into the harness DLL and driven
against real chunks by `harness/drive_map.c`, which reproduces the game's load
order: prime the heap, load TRAK first (the loader reads vertex counts through the
relocated header table), set the WFPC flags, then call with a zeroed `MapWorld`.

Getting it to *compile* needed three documented artefact fixes, all recorded in
`BODY_PATCHES` in [tools/make_verify_subset.py](tools/make_verify_subset.py):

| Artefact | Fix |
|---|---|
| `switch(local_c)` on a *pointer* (Ghidra reused one stack slot for a pointer and for the u16 it switches on) | cast the switch to `unsigned int`, drop the pointer case labels |
| two `call __ftol` sites with the x87 operand *dropped* | restored as `(int)(*(float *)&local_18 + 0.5f)` / `(int)(*(float *)&local_1c - 0.5f)` - Ghidra's structure matched the listing, only the operand was missing |
| the greyscale colour path's `__ftol` sites (unreachable with the flag set) | routed to a stub so it links |

Running it on `t1l1m001` gets through, in order: tile_count and grid,
Array A, section2, section3, section4, section5, grid_flat, Array B, tile_trak,
the optional20 table, and the colour pointer-array allocation - then faults on the
first per-tile colour block.  The progress markers that located this are the
`CHECKPOINT_ANCHORS` patches, which insert `[map] <stage>` prints into the body;
that is how the fault went from "crashes somewhere" to "crashes between the extra
colour-block allocation and the block store, on tile 0".

Two bugs later it runs to completion, and both were in the *harness*, not the
loader: the driver passed a local for `out_records` where it had to pass the DLL's
own `DAT_005846ec` (so the loader read the TRAK table through a NULL base), and
`tools/verify_map.py` read the driver's decimal fields as hex.

`tools/verify_map.py` now checks the result against `eng_wad/map_full_chunk.py` -
the byte-exact parser for this chunk - and it passes on every shipped level:

```
t0i0m000  PASS   t1l1m001  PASS   t1l1m002  PASS   t1l1m003  PASS   t1l1m004  PASS
```

What that covers, per level: the nine scalars (tile_count, grid, section counts,
both object counts, final_u16) plus the two globals the loader writes at the end,
all ten array offsets - which verify the whole allocation *order* and every stride
(4/8/92/48/32/24 bytes) - and the **vertex-colour byte accounting**, the one part
the Bible had flagged as not byte-exact: the model's 105,712 bytes for `t1l1m001`
and the loader's own consumption put the object table at exactly the same address,
`0xC9BF0`.

So the MAP loader - the most complex and most documented format in the project - is
now functionally verified against an independent implementation, on real data.

#### And on the decoded values, not just the layout

The driver also computes FNV-1a over the arrays whose bytes are address-independent,
and the verifier rebuilds the same runtime images from the oracle.  For `t1l1m001`:

```
section2    1,368 B    grid_flat  36,864 B    placements  43,456 B
tile_trak   5,432 B    section5      256 B
```

All five hash-match on all five levels - about 87 KB of decoded data per chunk
verified byte for byte, which covers the 12.12 fixed-point position fields, the yaw
fields, the tile-to-TRAK mapping and the zone grid.  The arrays that carry
relocated pointers (section3/4, optional20, objects, colour blocks) are covered by
the offset checks instead, since hashing them would compare addresses rather than
data.

### Clearing the compile backlog

The 170 functions the bulk could not compile were analysed by *first error pattern*
rather than one by one, and two systematic causes came out of it:

| Pattern | Functions | Fix |
|---|---|---|
| `C2186`: the result of an indirect call through `code *` is assigned, but `code` returned void | 49 | `typedef int code();` - the looser return type is harmless where the callee really returns void |
| `C2040`/`C2373`/`C2371`: a definition disagreed with its own loosened prototype | ~90 | loosen **only the parameter list** and keep the declared return type verbatim - `char *`, `undefined *` and `void __fastcall` all have to survive; the old whitelist silently rewrote them to `int` |

Result: **798 -> 873 functions compiling cleanly**, a further +3 from a targeted type
override (below) for **876**.

The next cluster is global typing: ~60 symbols account for ~200 of the remaining
errors, because the decompiled code decodes the same slot as an integer, a float or a
pointer depending on the function - and the symbol table does not say which.

[`tools/infer_global_types.py`](tools/infer_global_types.py) exists to answer that
from *evidence*: it compiles, reads the type errors, infers what each erroring use
demands, writes the verdicts to `src_generated/type_overrides.csv` (which make_bulk
applies), and repeats - reporting the clean-function count after every round, and
**deleting its own inferences when a round does not improve the baseline.**

Its first three variants are a *measured negative result*, which is the reason that
discipline is built in:

| Variant | Inferred | Result |
|---|---|---|
| line-local rules (casts, derefs, literals) | 41 | no gain (reverted) |
| compiler-message driven (C2440 names the type) | 61-18 | no gain (reverted) |
| all x87-proven symbols at once | 2,055 | 873 -> 865 (reverted) |
| **one family** (the 8 lighting floats at `0x6D7B9x`) | 8 | **873 -> 876 (kept)** |

The x87 evidence itself is sound: `fld ds:flt_57DB20` *proves* that slot is a float,
and the pass extracts 5,951 such operands covering 2,055 names.  Applying them all
loses eight functions, while applying just the lighting family gains three.  That is
the whole story in one measurement: **the same memory slot really does hold
different types in different functions**, so a *mass* typing pass cannot win and a
*targeted* one can.

Two bugs were found and fixed on the way, both worth remembering: the seed's keys
were spelled the way the *listing* says (`flt_6D7B98`) instead of the way the
generator says (`DAT_006d7b98`), so the first "no change" measurement was vacuous;
and a revert now clears the in-memory table too, otherwise a later stage re-applies
the guesses it just rejected.

The honest conclusion: the remaining ~330 errors are per-site work in the decompiled
code, which is what [`src_generated/bulk_patches.csv`](tools/make_bulk.py) exists
for - a recorded, reviewable (function, find, replace) table that survives
regeneration.  Next session should work that queue and refine the family search to
smaller groups (4-8 adjacent symbols rather than 256-byte pages).

### Coverage, honestly

The differential driver exercises 12 functions, the TRAK loader one more, and the
MAP loader is now verified against real data at both layout and value level.
Everything else in the 819 compiling functions is still only compile-checked.

## Usage

```bat
python tools\gen_functions.py      :: rebuild functions.csv from the listing
build.bat                          :: compile + link
build.bat run                      :: ...and run the behavioural self-test
build.bat check                    :: ...and byte-compare against the original
check.bat --dump sub_41EF00        :: show original vs rebuilt bytes side by side
check.bat --list                   :: show the remaining queue, smallest first
python tools\show_asm.py sub_41EF00  :: read the original listing for one function
```

The two tracks meet in the middle: Ghidra gives scale (1,016 functions already
compiling), the harness gives certainty (byte-verified ports).  A function that
the harness has matched can replace its `decompiled/` counterpart whenever the
bulk translation unit is finally linked.

## The loop for the next function

1. `check.bat --list` - pick the smallest untouched function.
2. Read it in `WAD/groove.exe.asm`; give it a real name when its purpose is clear.
3. Write it in `src/` with **the original name as the C identifier**, so the
   harness maps it 1:1 (glue helpers that do not exist in the original get a
   `groove_` prefix and are excluded from byte comparison).
4. Add behavioural checks to `host_main.c` where they are meaningful.
5. `build.bat check` - iterate until the verdict stops improving.
6. `functions.csv` is updated automatically with `exact` / `reloc` / `diff`.

Two habits worth keeping: assert the *original's* behaviour, not what the source
"should" do (see `sub_41EF00` in the self-test - its size check is a signed
`jle`, so a negative size is accepted and rewinds the heap; the first version of
the test asserted the opposite and was wrong), and prefer the Python
implementation in `../WAD/eng_wad/` as the oracle for anything chunk-shaped,
since it is already validated against the shipped WADs.

## Suggested order

1. **Finish the primitives tier** - the 244 leaf functions <= 48 bytes. Cheap,
   mechanical, and they remove most stubs from the dependency graph.
2. **I/O + container layer** - `sub_415A90` family, `sub_415B10` (skip),
   the WAD chunk dispatcher (`loc_558966` region) and the tag table, so the
   loader skeleton exists end to end.
3. **Chunk loaders, in spec order** - `sub_42AC50` (MAP) first: it is the most
   completely documented function in the project (field order, runtime strides,
   WFPC gates, colour blocks) and `eng_wad/map_full_chunk.py` is a byte-exact
   oracle for it. Then `sub_42AB50` (STPC) and `sub_42AAC0` (TRAK).
4. **Renderer / actor VM** - `sub_42BF40` (terrain), `sub_54D180` (script
   dispatch), then the 293 high-opcode handlers, which are mostly small.
5. **Leave the C++ runtime alone** - `??2@YAPAXI@Z` etc. come from the CRT;
   link the real thing instead of reversing it.

## Lessons that shape the workflow

These came out of the harness itself; they are the difference between a
plausible port and a correct one.

1. **`/arch:IA32` is mandatory.** The original is x87 (`fld`/`fdiv`/`fstp`); MSVC
   2022 defaults to `/arch:SSE2` and silently rewrites every floating-point
   function to `movss`/`divss`. Adding the switch turned `sub_40E020` straight
   into a `RELOC` match.
2. **Intra-module `call` targets are not relocations in the original.** A call to
   another game function is encoded as a plain relative displacement with no
   relocation entry, so it can only match when the two functions sit at the same
   relative distance. Consequence: `RELOC` is reachable for **leaf functions**
   (and functions that only call the CRT); anything that calls a game function is
   capped at `DIFF` until the whole layout matches. `sub_40DB70` is the example:
   its only difference from a match is the `call sub_40D970` displacement.
3. **`__thiscall` cannot be declared on a free function** (MSVC error C3865).
   When the `this` argument is the only one, `__fastcall` is byte-identical
   (`sub_413B10`, `sub_41BCB0`). When there are also stack arguments, emit the
   body verbatim in a `__declspec(naked)` function (`sub_40FC90`) and record that
   it is a C++ member function whose owning class still needs reversing.
4. **MSVC 6 inlined `memset` as `rep stosd`; MSVC 2022 emits a call.** Do not
   contort the source to chase this - keep the readable form and note the
   toolchain difference (`sub_40E0A0`).
5. **Never build the C from a filtered dump.** Three functions in the first
   batch were given the wrong bodies because I misread my own condensed output.
   `tools/show_asm.py` prints the listing verbatim - use it, and re-read the body
   before writing the port.
6. **Assert the original's behaviour, not what the source ought to do.** The
   first version of the allocator test asserted that a negative size is rejected;
   the original's size gate is a signed `jle`, so a negative size is accepted and
   *rewinds* the heap. The test was wrong, the code was right.

## Environment notes

* Build is **x86 only** - the original is PE32, and the codegen question is
  meaningless otherwise.
* `/O2 /MT /GS- /arch:IA32`, and `/TP` (C++ mode) because the game is C++: the
  CRT symbols in the listing are mangled (`??2@YAPAXI@Z`, `??3@YAXPAX@Z`), and
  member-style functions are thiscall.
* Keep the `link` list in `build.bat` **closure-complete**. A port whose callee is
  not reversed yet goes to `gr_pending.c`: compiled, byte-compared, not linked.
* `sub_41EEA0` calls the MSVC C++ `operator new`/`delete`; the port uses
  `malloc`/`free`. Behaviourally identical, and in a rebuild the call operand is a
  relocation, so it is masked by the `RELOC` verdict.
* Function sizes in `functions.csv` come from the gap to the next function and
  include alignment padding; the harness trims trailing `0xCC`/`0x90` before
  comparing.
* For Track A, install Visual C++ 6.0 in a VM, point `build.bat` at its
  `vcvars32.bat`, and add a source-permuter step (randomly permute the C until the
  bytes fall into place) to chase the last few bytes of the remaining `DIFF`s.
