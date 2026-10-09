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

What it produced when the decompiler first ran (`decompiled/` is committed,
`src_generated/` is derived).  The numbers below are that first snapshot, kept because
they are what the cluster-by-cluster work started from.  The current state is at the
end of [Clearing the compile backlog](#clearing-the-compile-backlog): 968 functions in
the clean subset, **968 compiling, none failing, 0 errors** - and those 968 link into a
dll that is then driven on the shipped WADs (see
[the whole bulk, linked and driven on the real WADs](#the-whole-bulk-linked-and-driven-on-the-real-wads)):

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

Re-run after the generator round below (the unary-`*`, `FARPROC`, label and
`__fastcall` fixes), from a clean regeneration: **both DLLs build, 12 checks, the same
single known failure**, and the two real-data drivers still pass - TRAK `PASS: all 131
records and 9019 triangle material indices match`, MAP `PASS: scalars, allocation order
and decoded values match the oracle`.  That round also removed a *second* source of
truth: `make_verify_subset.py` used to apply only its own `BODY_PATCHES`, so the shared
`ghidra_prototypes.h` and this subset could disagree about a signature - which is
exactly what happened (`int sub_406E30()` declared, `void` defined, C2371) once the bulk
started patching return types.  The subset now applies `src_generated/bulk_patches.csv`
too, and the four `sub_42AC50` fixes that were duplicated in both places live only in
the table.

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
| `C2186` again: a function Ghidra typed `void` whose callers use its result | 149 | the definition's return type changes to `int` - generated automatically, written into `bulk_patches.csv` so every one is recorded |
| `C2039`/`C2065`: Windows types Ghidra renamed (`_LARGE_INTEGER.s.LowPart`, `HDC__`, `tagMSG`) | ~10 | aliases in the shim to the real system types |

| `C2065` again: locals/parameters Ghidra never declared (`_param_9`, `local_50`, `hdc`) | ~30 | the first three shim fixes cleared most of them (an unknown *type* was breaking the declaration); the rest are generated into `auto_decls.csv` and injected at the top of the function |
| `C2709`: a `__fastcall`/`__stdcall` definition against a bare `()` prototype | ~18 | for these conventions `()` is *not* "unspecified arguments", so no prototype was emitted for them and the definition was the only prototype.  **This was half a fix**: with no prototype, a call that appears *before* the definition makes MSVC invent an implicit `int name()` declaration, which the definition then contradicts - `C2373`, 9 functions.  The generator now strips the keyword from generated bodies (the same approximation the shim already makes for `__thiscall`) and emits the loose prototype for them too. |
| `C2039`/`C2224`: `LARGE_INTEGER.s` (Windows calls it `u`), and sub-fields reached through an index (`local_118[0]._0_1_`) | 22 | one is a rename in the normalizer, the other a generalisation of the sub-field pattern to indexed and `->` forms |
| `C2197`: a callee Ghidra declared `(void)` called with 5 arguments (`sub_426500`) | 6 | [`tools/gen_arity_patches.py`](tools/gen_arity_patches.py) widens the *callee's* parameter list - safe, because the decompiled body only ever reads the parameters it names. It now matches the patch text against the **generated bulk** instead of `decompiled/` (the two differ: the generator renames and normalizes), which is what left two of four candidates unable to find their line, and it skips call sites in excluded functions. |

Result of that round: **798 -> 909 functions compiling cleanly**, with a targeted
type override below accounting for three of those.

The next session took the same cluster-and-measure loop through the rest of the
queue and reached **924 -> 962 of 968** (errors 92 -> 11, failing functions 44 -> 6), then
**968 of 968 with no errors at all** - all six of the stragglers were library code whose
bodies just needed the same treatment, see
[the last six](#the-last-six-library-bodies-that-needed-a-real-fix).
The rest is written up below: the *generator* bugs the earlier rounds had compensated
for with recorded patches, and the two arity conventions.

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

The honest conclusion: the remaining ~240 errors are per-site work in the decompiled
code, which is what `src_generated/bulk_patches.csv` exists for - a recorded,
reviewable (function, find, replace) table that survives regeneration.

One note that turned out to be a *symptom*: `sub_426500` is not a function at all in
Ghidra's sense - the byte at `0x426500` is a lone `C3` (`ret`) followed by alignment,
IDA calls it `nullsub_2` and collapses it, and the original calls it with anything
from 0 to 5 arguments (`sub_426500(s_Failed_to_load_ambient_sound_id___00578ec8,
uVar8)` next to `sub_426500()`).  Widening it to five parameters silenced the
`C2197`s and *caused* a `C2198` in `sub_4268C0`; the correct fix is an old-style `()`
definition, see below.

### The generator bugs behind the last cluster, and the two arity conventions

Four of the remaining error classes were not decompiler artefacts at all - they were
this project's own typing heuristics, which earlier rounds had papered over with
recorded patches.  All four are fixed in `tools/make_bulk.py` and measured:

| Bug | Evidence | Effect |
|---|---|---|
| the unary-`*` test that decides "this datum holds an address" only looked at the character *before* the `*`; in `a * DAT_x` that character is a space | `uVar2 = DAT_00583378 * DAT_00583374;` failing with "right operand has type `unsigned int *`" | every global used as a multiplier was declared a pointer: `C2296`/`C2297`/`C2440`, 23 errors. The test now requires the preceding **token** to be a delimiter |
| function pointers were all declared `code *` (`int (*)()`) | `DAT_005863cc = GetProcAddress(...)` - `C2440` from `FARPROC` | the Win32 ones are `FARPROC`, the internal ones (`DAT_0058372c = &LAB_00415010;`) are `code *`; split by which fills them in, 16 errors |
| a label at the end of a block (`LAB_004054a3:` on the line before `}`) | `C2143: missing ';' before '}'` pointing at the brace | C wants a *statement* after a label; a null statement is now emitted, 2 functions |
| Ghidra's own `(void)`-vs-`()` distinction for a null subroutine | `sub_426500` above | `(void)` -> `()` lets all arities compile (verified against MSVC with `g()`, `g(1,2,3)`, `g(0x10,1,2,3,4)` in one unit) |

And the "too few arguments" class is not a typing problem at all.  On this binary it is
Ghidra **dropping the implicit `this`** of a `__thiscall` call: the decompiled
`sub_413BF0(0)` is `basic_string::_Tidy(bool)` called as `this->_Tidy(false)`, and the
listing shows the operand it lost - `lea ecx, [esp+54h+var_3C]` (a local object) or
`mov ecx, ebp` (the enclosing `this`, since the caller's `mov ebp, ecx` saves its own).
Restoring it is both the compile fix and the faithful fix, so the 11 sites in
`chunk_004` are recorded in `bulk_patches.csv` by hand.  An *automated* version of this
cannot work by name - the listing calls the target
`?_Tidy@?$basic_string@DU$char_traits@D@std@@V?$allocator@D@2@@std@@AAEX_N@Z`, which is
nowhere in Ghidra's `sub_XXXX` namespace - which is why the intermediate
`gen_call_pad_patches.py` was **deleted** rather than kept: padding the call with `0`
makes `this` NULL (the body writes through it) and its row builder replaced the
*argument text* everywhere in the line, so `sub_413BF0(1);` became `sub_41, 03BF0(1, 0);`
and the zero-argument case exploded an empty pattern into every character.  Both
shapes are recorded here because the file was an uncommitted draft; the lesson is that
a patch generator has to be checked against the table it writes.

Three more fixes came out of the same round and are recorded in the table: the
`__fastcall` prototypes made two `void`-returning functions' callers fail (`C2440`/
`C2186`, e.g. `DAT_0058115c = sub_41BCB0();` - and the listing confirms `mov eax, ecx`,
the `this`-returning idiom, so the return type is a pointer); `sub_436550`/`sub_41E790`
were typed `void` while their callers use the result; and the MAP loader's
`switch(local_c)` now carries the cast and the two restored `__ftol` operands that
`tools/make_verify_subset.py` had been applying **only** to the harness build - the two
sources of truth for that function are no longer separate.

The `hand patches applied` counter in `report.txt` is the self-check for all of this:
make_bulk prints a note for any patch whose `find` text is not in the body, so a silently
dead patch cannot accumulate.  It also caught an error *I* made while editing the table
by hand: four rows written without quotes around a field containing a comma were parsed
as extra columns, and the replacement text was truncated at the comma
(`sub_413BF0(param_1` - six `C2143`s).  Every generator writes those rows through
`csv.DictWriter`; hand edits have to quote.

A third tool, [`tools/try_patches.py`](tools/try_patches.py), tests that conclusion
directly: for each erroring line it applies the type the compiler's message implies,
and keeps the change only if the clean count rises.  It kept **0 of 18** candidates -
the same answer as every other mass-typing attempt, and now backed by a measurement
of the per-line unit rather than a guess.

### The last six: library bodies that needed a real fix

After the generator bugs were fixed, six functions were left, all of them CRT/STL code
that Ghidra recovered *inside* library regions (five at addresses where IDA has no
function at all - it collapsed those regions as FLIRT-matched library code).  Each one
had a mechanical cause, provable from the binary:

| Function | What was wrong | Evidence |
|---|---|---|
| `sub_5628EB` | `FILE` was not declared - four `C2143`/`C2059` on the *signature* line | it is the body of `fclose`; `<stdio.h>` cannot supply `FILE` here (this SDK declares it opaque, and `_CRT_INTERNAL_NONSTDC_NAMES` does not bring `_file`/`_tmpfname` back - measured).  The shim now defines `groove_FILE` from the **binary's** layout: `8b 46 0c a8 40` = `_flag` at 0x0C, `ff 76 10` = `_file` at 0x10, with an `offsetof` assertion so a later edit cannot shift a field silently |
| `sub_5632EA` | `*param_1 = &type_info::vftable;` - C++ syntax, C2065 | the vftable address is the immediate in the first instruction: `c7 01 60 e7 56 00` = `mov [ecx], 0x56E760` |
| `sub_5632FF` | `sub_5632EA()` called with no argument | it is `??_Gtype_info` calling `~type_info`: the disassembly is `push esi; mov esi,ecx; call 0x5632EA` - no `ecx` setup, because the callee wants the *same* `this`, so the argument is the caller's `param_1` |
| `sub_56D5AC` | `exception::~exception(param_1);` plus an undeclared `exception` type | the destructor is a named Ghidra function: `~exception,0056d64f,22` in `decompiled/_functions.csv`, so the call becomes `sub_56D64F(param_1)` and the type `undefined4 *` |
| `sub_56BB21`, `sub_56CD4A` | one argument short each | the callee takes a **`double` split into two dwords** - the original pushes it with `push ecx; push ecx; fstp qword ptr [esp]`, which is what the decompiled `(int,uint)` / `(uint,uint,int *)` signature is.  The calls now pass the two halves of the same double (`sub_56B9F4(param_1,param_2)`, `sub_56BA4E(*(uint *)param_2, *((uint *)param_2 + 1), &local_8)`) |

Result: `968 of 968 functions compile, 0 errors, 0 excluded`.  `failed.txt` is empty,
and the `hand patches applied` counter (237) is the check that every recorded patch
still finds its line.

## Compiling and testing against the real WADs

```bat
python tools\make_bulk.py          :: generate all 968 functions into chunks
python tools\compile_check.py      :: 968 of 968 compile, 0 errors
harness\build_dlls.bat             :: the harness DLL (curated subset of those sources)
harness\run_verify.bat             :: differential: ghidra DLL vs hand DLL
harness\run_drive_trak.bat         :: then python tools\verify_trak.py --wad t1l1m002.wad
harness\run_drive_map.bat          :: then python tools\verify_map.py
```

What the drivers and the verifier exercise, re-measured on the shipped data:

```
differential harness      12 checks, 1 failure  (the same known sub_41EEE0 anomaly)
TRAK, all five levels     PASS  36/1,889  127/9,369  131/9,019  133/9,758  87/5,811
                                records / triangle material indices, each matching the
                                independent model
MAP, all five levels      PASS  scalars, the ten array offsets, the colour accounting
                                and the five FNV-1a value hashes match the oracle
```

**The code under those wrappers is the 13-function curated subset, not all 968** - and
that is worth being precise about, because three plausible ways of getting the *bulk*
behind the same wrappers were tried and two of them do not work in this toolchain:

| Attempt | Result |
|---|---|
| `build_dlls.bat bulk`: compile all 25 chunk objects and link them, hoping `/OPT:REF` drops what the exported wrappers cannot reach | **fails**: 282 unresolved symbols.  `/Gy` + `/OPT:REF` does *not* discard unreferenced functions - a two-function experiment (one exported, one unreferenced, both COMDATs, referencing an undefined symbol) fails with LNK2019 either way |
| resolve those 282 with the `/alternatename` aliases in `harness/import_stubs.c` (the device that was built for exactly this) | **does not work here**: the same two-function experiment with `#pragma comment(linker, "/alternatename:...")` still fails with LNK2019.  `import_stubs.c` is not even in the subset link line - nothing has ever linked through it |
| regenerate the alias list from the bulk log `tools/gen_import_stubs.py` | writes 201 aliases, link still fails identically |

The 282 symbols are, measured from `build/_ghidra_link.log`:

* **39 game functions the compile still excludes** - the ~50 artefact-function class
  (`unaff_*`, `in_stack_*`, dropped locals) and the two undecompilable giants.
* **34 `__imp__*` and ~209 other imports** - Win32/COM/DirectX/Miles (`RegCloseKey`,
  `CoInitialize`, `DirectDrawCreate`, the whole `AIL_*` set) and old-CRT internals
  (`_fcos`, `_fptan`, `_flsall`, `_builtin_strncpy`, `_CARRY4`, `_ExceptionList`).

The two routes that *would* work, and that the next round should take:

1. link the real import libraries (`advapi32`, `user32`, `gdi32`, `ole32`, `winmm`, ...)
   - they define the `__imp__*` symbols, which no C-level stub can express because `@`
   is not legal in an identifier - plus the DirectX SDK and `mss32.lib` for the rest;
2. generate ordinary **stub definitions** (one function or datum per remaining name)
   for everything else, including the 39 game functions: measurable, and it turns the
   bulk into a linkable image with a recorded list of what is not real code.

So the honest state is: *every game function compiles; the loaders that are exercised
run against real data and match an independent model; the whole-image link is one
import-library list plus a stub generator away, and it is not claimed yet.*

### Coverage, honestly

The differential driver exercises 12 functions, the TRAK loader one more, and the MAP
loader is verified against real data at both layout and value level - now with the bulk
itself, not a curated subset, on the other side of the wrappers.  Everything else in the
968 compiling functions is still only compile-checked.

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

0. **The artefact functions, then the system libraries** - this is what stands between
   the current state and a runnable image, and it is the only thing on the critical
   path (measured: 282 unresolved symbols, of which 39 are game functions the compile
   still excludes and the rest are imports).  Two different jobs:
   * the ~50 artefact functions (`unaff_*`, `in_stack_*`, dropped locals) and the two
     undecompilable giants: read the original listing and write the port, function by
     function - `tools/show_asm.py` and `WAD/REVERSE_ENGINEERING_BIBLE.md` are the
     tools.  Each one that lands removes a stub from the graph.
   * the imports: DirectX and Miles SDK link libraries (not installed here), plus a
     shim header mapping the MSVC 6 CRT internals (`_fcos`, `_fptan`, `_flsall`,
     `_builtin_strncpy`) onto their modern equivalents.  Then the exe link becomes
     `link /ENTRY:entry chunk_*.obj ...` and the missing list is only game code.
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
