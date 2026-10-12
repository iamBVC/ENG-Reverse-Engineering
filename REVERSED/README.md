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

### Continuation checkpoint (2026-10-12)

**Second desktop trace:** depth and display enumeration both return success,
both HAL adapters enter the list, and main reports `ddraw=1`. The next trace
names `__strcmpi` and the still-stubbed legacy throw helper. `__strcmpi` now maps
to the real case-insensitive CRT comparison instead of returning zero for every
pair. Device creation/query/release and surface-setup COM calls now retain their
stdcall argument counts. The fourth argument to `sub_410700` is an object address,
not a float; its later palette-index and floating scratch uses are separate locals.

Surface setup now has actual 124-byte surface descriptions, 100-byte capability
outputs, and 72-byte monitor-info storage. `sub_40FF40` passes real width/height
pairs rather than pointers to separate locals. Graphics throw sites log their
message and HRESULT before the existing legacy exception stub, so that future
failures can be distinguished. Faithful MSVC 6 exception handling remains open.

`python tools\test_graphics_surfaces.py` exercises the generated surface setup
against COM mocks in all four combinations of offscreen/depth requirements. It
checks display-mode arguments, descriptor fields and complete output-buffer
writes. The hardware test also passes actual DirectDraw4/Direct3D3 interface
creation/query/release. Hardware enumeration and callback tests still pass;
1,130 included functions compile and the executable links. These are focused
initialization checks, not validation of real fullscreen rendering, viewport
math, texture enumeration or gameplay. The incoming desktop log is preserved
as `build/hardware_user_trace_before_surface_fix.log`.

**Desktop HAL trace follow-up:** the user's normal desktop run does enumerate
Direct3D HAL (`caps=1`, flags `0x1ff`) and stops just afterward. Inspection found
two callback contexts represented as separate C locals: the original passes
addresses of adjacent stack slots, and the callbacks index those slots at fixed
offsets. `groove_ddraw_enum_context` and `groove_d3d_enum_context` now preserve
those layouts explicitly, with x86 size/offset checks. The display-format
constructor in `sub_412320` also now receives its allocated object (`param_1`),
matching the original ECX argument before the call to `sub_413570`.

`python tools\test_hardware_enumeration.py` links against the bulk DLL objects
and drives the real generated hardware callback through deterministic COM
methods. It passes depth-format selection, display-mode creation and reuse,
and insertion into the parent adapter's list. The fixture exercises the branch
the session's software-only renderer cannot reach; it is not a real-GPU gameplay
test. The callback tests still pass, all 1,130 included functions compile, and
the exe links. Depth/display enumeration begin/result probes were added for
the next desktop run. The old desktop log is preserved in
`build/hardware_user_trace_before_context_fix.log`.

**Later checkpoint:** the bulk now includes **1,130 functions**, all compiling
with zero errors. Six assembly-recovered callbacks/comparators live in
`src_recovered/`; `make_bulk.py` prefers those files over same-named Ghidra exports
so another export cannot erase them. The window procedure at 0x41DDA0 is now real
code, and Windows/DirectDraw/Direct3D callbacks keep their verified stdcall
signatures. The relevant COM methods use fixed argument counts and stdcall.

The DirectDraw list loads its stored head pointer, rather than treating the
three-dword storage array as a node. The surface list has the corresponding fix,
including byte-address arithmetic and the sentinel in the second dword. The
module-path buffers passed to `GetModuleFileNameA(..., 260)` now have 260 bytes:
a hardware watchpoint showed the old one-byte buffer corrupting the DirectDraw
diagnostic stream. The DirectDraw4/Direct3D3 IIDs and the CoCreateInstance GUIDs
also retain their full 16 bytes.

DirectDraw creation/enumeration, DirectInput creation, and COM imports now call
the real APIs instead of zero-returning stubs. The generated build script fails
on an unsuccessful exe link, and the compile checker fails on compiler errors
including shared-header errors.

Validation commands (run after generation):

```bat
python tools\test_recovered_callbacks.py
python tools\test_legacy_imports.py
python tools\test_registry_handles.py
```

The recovered callback tests pass dispatch, capture naming, comparator ordering,
and 20,000 calls through stdcall callback pointers. The real API smoke test
creates/releases DirectDraw and DirectInput interfaces and invokes both forms
of enumeration callbacks. The registry and existing MAP/TRAK tests also pass.

**Runtime limit:** the rebuilt image creates its window and reaches device
enumeration without the earlier crashes, but returns `ddraw=0`. In this execution
session the callbacks expose RGB Emulation with an empty HAL descriptor. Running
the original under gdb also supplies an empty HAL descriptor to `sub_412A10`.
This does not establish equivalence of the full enumeration path or explain why
the user's ordinary desktop run works; graphics checks have not been bypassed.
The next runtime evidence needed is `build/run/groove_trace.log` from launching
the rebuilt copy in the user's normal desktop session. Rendering, menus, audio,
and gameplay remain unverified, and 48 artifact bodies plus further referenced
stubs (including Miles audio and legacy exception handling) remain unresolved.

The following paragraphs document the earlier checkpoint.

The current generated output includes **1,124 functions**, all compile-checked
successfully with x86 MSVC, and **48 excluded bodies**. The older counts below
describe earlier snapshots. `harness\build_dlls.bat bulk` successfully links the
rebuild executable and both verification DLLs. This remains a partial rebuild:
linking with missing-function stubs does not establish gameplay equivalence.

The registry helper `sub_405960` now uses two local `HKEY` slots, matching the
assembly's local `hKey` array, rather than indexing beyond its `param_1` argument.
The root argument stays intact while the slots alternate. Its dropped `_sprintf`
call now receives the buffer, original `"[08x%x]"` format, and root value. These
corrections are recorded in `src_generated/bulk_patches.csv`; the Ghidra export
remains unchanged. `python tools\test_registry_handles.py` compiles the generated
body against mocked registry calls and passes six cases: opening existing keys,
creating keys for HKCU/HKLM/another root, creation failure, and an empty path.
The test checks intermediate handle closure without modifying the registry.

The build script's library assignments now occupy single lines: quoted caret
continuations previously tried to execute `WinMM.lib` as a command. A fresh bulk
build completes without those command errors. MAP and TRAK verification on
`t1l1m001.wad` passes against the Python models (including MAP value hashes and
all 127 TRAK records / 9,369 material indices).

A debugger run of the rebuilt executable now passes the registry failure and
reaches `[main] E`. It then attempts to free a static address during
`sub_40FD00 -> sub_413170 -> sub_5628BC`. The trace shows the supposed node is
the address of `DAT_00583410` itself. The next concrete repair is to reconcile
that datum's array override with its pointer-valued uses: generated expressions
such as `piVar1 = DAT_00583410` now decay to the array's address instead of loading
the first stored pointer. Keep sentinel addresses (`&DAT_00583410[1]`) distinct
from head-pointer loads, and verify the initializer and list insertion together.
The window procedure at `LAB_0041dda0` also remains a stub. No successful menu,
rendering, or gameplay run has been established by this checkpoint.

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
    gen_functions.py     builds functions.csv from Game/groove.exe.asm
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
generated code that needs a different approach - REA's provider did produce bodies
for both, see
[the provider cross-check](#provider-cross-check-rea-over-the-same-ghidra-database).
And IDA and Ghidra disagree about
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

### Provider cross-check: REA over the same Ghidra database

[REA](https://github.com/morluto/rea) 6.4.0 (MCP server + CLI) is set up against
the local Ghidra 12.1.4.  Its Ghidra provider is the *same engine*
`tools/ghidra_decompile.bat` already uses, so **the pseudocode is not new** -
`decompiled/sub_404DB0.c` and REA's `FUN_00404db0` are identical character for
character.  What is new is the analysis database's own symbol knowledge and a
per-function call graph:

* library identities Ghidra's function-ID resolved but the bulk export never
  carried (`exception::~exception`, `operator_new`, `__ftol`,
  `__abnormal_termination`, the STL `string too long` / `invalid string position`
  throw sites);
* callers, callees, incoming/outgoing references and referenced strings in one
  call per function;
* bodies for the three functions the bulk export produced no file for.

**One session, many calls.**  An MCP session imports and analyses `groove.exe`
once (~3 min) and then answers per-function calls in milliseconds.  The CLI
starts a fresh session per invocation and re-analyses every time (~13 min,
measured), so drive the MCP server, not `rea <command>`, for anything iterative:

```bat
node tools/rea_make_spec.mjs dossier > spec.json
node tools/rea_mcp_call.mjs spec.json dossier_out.json
```

Ghidra needs `GHIDRA_INSTALL_DIR`, and `JAVA_HOME` must point at a 21+ JDK - the
JDK first on this machine's `PATH` is 8, which Ghidra rejects.

The first run covered the 36 game-function entries of
[`src_generated/link_stubs.csv`](src_generated/link_stubs.csv); the per-symbol
result is
[`src_generated/rea_stub_evidence.csv`](src_generated/rea_stub_evidence.csv).  It
corrects three of those entries:

| Symbols | Was | Evidence | Is |
|---|---|---|---|
| `sub_563360`, `sub_567B34`, `sub_56C2B0`, `sub_56C543`, `sub_56CF8A`, `sub_56CF98`, `sub_56CFA7`, `sub_56D188` | 8 x "game function (body still excluded)" | none of the eight is a function in IDA's listing: each is an interior address of `sub_5625F0`, `sub_56394C`, `sub_569961`, `sub_56CF87`, `sub_56D16B` | a Ghidra/IDA **partition** difference, not eight missing bodies |
| `sub_56D64F` | `kind=game`, 0 bytes | Ghidra function-ID: "Library Function - Single Match", symbol `exception::~exception` | library (C++ EH runtime) |
| `sub_56D0A0`, `sub_56D2CC`, `sub_56C2B0` | game | `__CxxThrowException` around `std::string` throw texts; the `1#QNAN`/`1#INF` float-print family | library (STL / CRT) |

`decompiled/rea/sub_447770.c` and `decompiled/rea/sub_4CB870.c` (~600 KB of
pseudocode each) are the two bodies the bulk run never produced, and
`decompiled/rea/sub_56D64F.c` is the third; all three carry a provenance header
naming REA as the producer.  They sit in a subdirectory deliberately:
`tools/make_bulk.py` globs `decompiled/*.c`, so the bulk pipeline's input stays
exactly what `tools/ghidra_decompile.bat` wrote.  The giants are *not* compilable
as they stand - the 42 KB `alloca` prologue and hundreds of "unreachable block"
warnings are why they failed before - but the bodies now exist to work from.

One measured limit: on those two giants the full `analyze_function` dossier
exceeds REA's 10 MiB MCP stdio response budget, so only `batch_decompile`
(pseudocode) covers them over MCP; the CLI's complete JSON output is the other
way out.  Separately, `sub_41F0C0` turns out to be the DirectShow/DirectDraw
stream setup - its referenced strings are the `pMMStream->SetState(...) failed
with HRESULT` family - which is the path that cannot initialise on a machine with
no real display.

An IDA provider is also possible (REA adapts
[mrexodia/ida-pro-mcp](https://github.com/mrexodia/ida-pro-mcp)), but what is
installed here is IDA Free 8.2 and REA's adapter is verified against IDA 9.3, so
the Ghidra provider is the one wired up.

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

### The artefact queue: one function done, and what it exposed

The 39 stubbed game functions are the queue (see `src_generated/link_stubs.csv`), and the
first one is the worked example of how to take one:

**`sub_408390`** (8 bytes, `0x408390`).  Ghidra's body is
`void sub_408390(void) { *in_stack_00000010 = 0xff; }` - it *wrote* through an argument it
could not name, so the function was excluded as an artefact.  IDA's listing names it:

```
sub_408390 proc near
arg_C= dword ptr  10h          ; the 4th argument
mov     eax, [esp+arg_C]
mov     byte ptr [eax], 0FFh
retn
```

Three recorded patch rows (signature, the undeclared local, the store) turn it into a
normal cdecl function with four arguments - and IDA's `arg_*` offsets line up with
Ghidra's `in_stack_<hex>` offsets, which is what makes this mechanical rather than
speculative.  Measured: clean subset 968 -> **969**, `needs hand fixing` 50 -> 49,
`in_stack_` 26 -> 25, and the stub for it disappeared by itself - the next link reported
LNK2005 ("the real code defines it now") and `gen_link_stubs.py` dropped the row: **157 ->
156 stubs**.  That is the loop for the remaining 38: patch the body, and the stub list
shrinks without anyone editing it.

Doing it also exposed something worth knowing about the *metric*.

### The compile metric depends on chunk size (measured)

`compile_check.py` splits the subset into 40-function units, because MSVC gives up after
~100 errors per translation unit.  The side effect: a function's *definition* is only
visible to the call sites that happen to share its chunk, so arity mismatches between
different chunks stay invisible.  Adding `sub_408390` to the clean set shifted the chunk
boundaries and seven previously-hidden errors appeared at once.

The honest numbers, both measured on the same source tree:

```
--chunk 40  (the normal measure)      969 functions, 0 errors
--chunk 480 (every definition visible) 969 functions, 928 clean, 108 errors:
                                       C2197 x69  (call passes *more* than declared)
                                       C2198 x38  (call passes *fewer* - a real bug)
                                       C2440 x1
                                       in 41 functions, across 15 + 19 distinct callees
```

The 38 `C2198` are the ones that matter: in the chunked build the callee is elsewhere and
silently reads whatever the missing parameters left on the stack, so those are behavioural
bugs in the linked image, not just metric noise.  They are the same class the earlier
rounds fixed by hand (dropped `this`, a `double` passed as two dwords, a `(void)`
definition that should be `()`), so the fixes are one rule each - and the grouping above is
already the plan: 19 callees need their argument restored or their parameter list
reconciled, 15 need `(void)` -> `()` or widening.  Re-run `compile_check.py --chunk 480`
after any change that shifts the clean set: it is the only measurement that sees them.

### The arity queue: 106 -> 34 errors, and three tools

**The arbiter is IDA's argument count.**  For a `cdecl` function every argument is on the
stack, so the listing's `args` list is the complete parameter list - and when it disagrees
with a call site, the call site is what is wrong.  That rule settles the ping-pong between
"passes more" and "passes fewer", and both directions are now generated:

* `[tools/gen_trim_patches.py]` drops the *trailing* arguments a callee never reads
  (verified per callee: `sub_4057C0`'s body mentions only `param_1`/`param_2`, and IDA says
  two) - 47 rows;
* `[tools/gen_arity_patches.py]` widens the definition when IDA says it reads *more* than
  Ghidra declared - 7 more rows in the last pass.

The two generators below read the full-visibility log and write recorded rows:

* [`tools/gen_arity_patches.py`](tools/gen_arity_patches.py) - the "call passes *more* than
declared" side: widen the callee, or emit `()` when its definition is `(void)`.  One run
removed **all 69** `C2197` errors (16 rows).
* [`tools/gen_this_patches.py`](tools/gen_this_patches.py) - the "call passes *fewer*" side,
where the missing argument has to come from the binary: it takes the callee's convention
from the *decompiled* source (a recorded patch can rewrite the chunk's line - the
`sub_41BCB0` return-type fix dropped its `__fastcall`), translates the caller's listing
(`mov ecx, dword_581168` -> `DAT_00581168`), and only prepends the caller's own `param_1`
when the caller is a member function *and* nothing touches `ecx` before the call.  4 rows,
every one the same `DAT_0058115c`/`DAT_00581168` object - the same shape the hand-written
`sub_402910` fix used, which is the consistency check that matters.

Measured on the same tree, over three passes until both generators stopped adding rows:
**106 -> 34 errors** - `C2198` 33 (the genuine dropped-argument sites), `C2440` 1, and
`C2197` 69 -> 0 twice over (widening, then reverting the widenings IDA disagreed with and
trimming their call sites instead).  The normal `--chunk 40` measure stayed at **969 clean
/ 0 errors** throughout, so the linked image was never left broken.

Both generators cost a round by breaking the *normal* build while the full-visibility
number looked good, and both bugs are worth knowing:

* the first version rebuilt the call from `(` to `)` and **dropped the trailing `;`** - four
  `C2146` errors in the normal build, for a patch that looked fine in the full-visibility
  count;
* it patched the *line* the error pointed at, which for a call Ghidra wrapped over two
  lines is half an expression.  It now refuses those sites ("the call spans several lines:
  not patchable as text") and they join the hand queue.

The lesson is in the numbers, not the prose: after any generated batch, run **both**
measures - the full one says whether the error is gone, the chunked one says whether
anything else broke.

### Working the C2198 queue (and what the sites actually are)

[`tools/dropped_arg_report.py`](tools/dropped_arg_report.py) is the queue's working tool:
take the full-visibility log, group the sites by callee, and print for each one the
callee's declaration plus the caller's listing up to the call - `mov ecx, ...` immediately
before the `call` *is* the dropped argument, and its absence means ECX is the caller's own
incoming `this`.  For callers IDA never defined (they sit inside library regions) it falls
back to a byte-scan hint, labelled as a hint because an opcode scan can match bytes inside
another instruction.

Two examples from the current 36 sites, and they are two *different* kinds:

* `sub_402910` (2 sites) - a `__thiscall` callee called with only its two float arguments.
  Both callers show the same three instructions:

  ```
  mov ecx, dword_581168      ; the object, loaded from a global
  call sub_402910
  ```

  so the restore is `sub_402910((int)DAT_00581168, 0x3f800000, 0x3f800000);` - recorded,
  measured: the full-visibility error count 108 -> 106, and the normal measure still
  969 clean / 0 errors.
* `sub_414600` (5 sites) - *not* a register argument at all.  The listing shows
  `push esi` / `push offset aCocreateinstan ; "CoCreateInstance(CLSID_AMMultiMediaStre..."`
  followed by `call sub_414600`: it is a **printf-style logger**, variadic, with the format
  string as its first argument, and Ghidra dropped the pushed arguments *and* modelled the
  callee with a single parameter.  These five need the arguments read off the listing one
  site at a time, the same way the `__ftol` operands do.

So the queue is not one rule but two, and the tool separates them: a dropped register
argument is a one-line restore, a dropped stack argument to a variadic callee is per-site
work with the listing open.  Both kinds are recorded in `bulk_patches.csv` like every other
hand fix.

A second, smaller lesson: the *same* CSV trap as the previous round (a comma inside an
unquoted `find`/`replace` field) cost another round - the field was truncated mid-comment,
which left an unterminated `/*` and made the *next* function fail with a syntax error that
pointed nowhere near the patch.  `make_bulk.py` now counts `/*` against `*/` after patching
every function and says so, because that class of mistake is invisible in the patch table
and misleading in the compiler output.

And the 64-bit helpers (`__alldiv`, `__aulldiv`, `__aullrem`, `__allmul`, `__allshl`, 13
call sites) turned out **not** to be a `__asm` shim away, which was the plan: Ghidra models
them as one explicit low dword plus the high dword *implicitly in EDX* - the same lost-
operand class as `__ftol`, whose sites are patched one by one.  The call shapes are
recorded above; restoring them is per-site work, and until then those 5 stubs are the ones
that would compute a wrong answer if executed.

## The exe: it builds, and it says what it needs next

```bat
harness\build_dlls.bat bulk     :: also links build\groove_rebuild.exe (812 KB, 0 unresolved)
build\groove_rebuild.exe        :: run it: it names the first function it is missing
```

Linking the *exe* used to fail with 14 unresolved symbols, and the reason was the entry
point, not missing C: the original PE entry (`entry`, 0x563EE0) **is the MSVC 6 CRT
startup**, and it is one of the excluded artefact bodies - so `/ENTRY:entry` replaced the
runtime's startup with a stub of it, and the runtime's own entry points (`_memcpy`, `_cos`,
`_malloc`, `_log2`, ...) had nowhere to come from.  The fix is the structure a rebuild
wants anyway: the modern CRT keeps its startup (`WinMainCRTStartup`) and
[`harness/exe_main.c`](harness/exe_main.c) supplies the `WinMain` it asks for, calling the
game's own main.  That main is `sub_41D350` - identified by disassembling the original
startup, whose calls include it.

What a run currently does, with the stubs reporting themselves and two lines of
instrumentation in `WinMain`:

```
[winmain] calling sub_41D350(hInst=00920000, cmd=)
[stub] sub_405960
```

So: CRT startup ✓, the game's own main ✓, and then it reaches the first function whose body
is still excluded - `sub_405960`, a 401-byte registry/settings helper (it sets up `HKEY`,
`_strtok`, `_sprintf` and a 4 KB buffer; excluded because its decompiled body has 12
register-artefact lines, and it uses `__alloca_probe`, which is why Ghidra's frame model
for it is confused).  After that it waits rather than exits, which is the next thing to
chase.

That is the loop for a runnable image: **run it, read the name, reverse that function,
rebuild** - and the name comes from the stubs themselves, so no debugger is needed to know
where it stopped.

### The first two names, and the recipes they establish

**`sub_405960`** (401 bytes) is a registry-settings helper: `registry_root(root, subkey,
access)` walks a `HKEY` tree with the CRT's `strtok`.  Two things made it tractable, and
both generalise:

* Ghidra's `in_stack_<hex>` names *are* its arguments.  The offsets line up exactly with
  IDA's `arg_0`/`arg_4`/`samDesired` once the `__alloca_probe` frame shift (0x1010) is
  subtracted - so `in_stack_00001014` = the root, `in_stack_00001018` = the subkey string,
  `in_stack_0000101c` = `samDesired`, and the same rule maps `&stack0x00000810` to IDA's
  `String` buffer and `&stack0x0000000c` to its `dwDisposition`.  Nine replacements, all
  mechanical, all from the listing;
* its two `strtok` calls had lost **both** arguments (`sub_56279D()` with a definition of
  `(byte *, byte *)`).  The listing shows the pushes: `(String, "\\")` and `(0, "\\")`.
  The delimiter is the single backslash at 0x570334, and it is passed as a local
  `char delim[2] = {0x5c, 0}` rather than a string literal - the address *is* declared in
  the generated globals, but as a plain `unsigned char`, which the generator would
  materialise as zero.

Result: clean subset 969 -> **970**, `in_stack_` 26 -> 22 for that one function, and its
stub removed itself through the LNK2005 rule.  It also fixed two of the 33 `C2198` sites as
a side effect.

**`sub_562840`**, the next name a run printed, is *not* game code at all: IDA's listing
names the call `__alloca_probe`.  It is the MSVC 6 stack probe, and a rebuild does not need
it (the modern compiler emits its own probe for a frame that size), so it is now a no-op in
[`harness/crt_aliases.c`](harness/crt_aliases.c) with that explanation.  That is a rule worth
keeping: **a Ghidra-only `sub_XXXXXX` in the CRT region can often be named from the call
sites in IDA's listing** - which is cheaper than reversing it, and correct.

After both, a run walks past the settings code and prints no stub at all; it now stops
where the game would create its window and wait.

### Localising the first crash (in progress)

With the startup running, the exe faulted inside the game's main.  Eleven probes inserted as
recorded patch rows (`fprintf(stderr, "[main] X\n")` after chosen statements of
`sub_41D350`) narrow it to a three-statement window:

```
[winmain] calling sub_41D350(...)
[main] A                       <- after `cVar3 = sub_41DC10();`
(crash)                        <- ... and before the next probe,
                                  `sub_41C050()`
```

Inside that window sits:

```c
if (cVar3 == '\0') {
    iVar4 = sub_415690(0, "111.cor");                       /* the file loader */
    if (iVar4 == 0) {
        /* 111.cor is missing, so this is the path a bare run takes */
        lpText = (&PTR_s_Inserire_il_CD_del_gioco_per_com_0057ba3c)[DAT_00584f04];
    } else { ... strtok / __strcmpi / sub_41C050(); }
```

Three real bugs were found and fixed on the way, all recorded:

* `DAT_0058115c = sub_41BCB0();` and `DAT_00581160 = sub_41BCB0();` - the object
  initialiser was called with **no object**, so it wrote through an uninitialised `this`
  (`*(param_1 + 0x20/0x24)`).  The listing shows `mov [ebp+0x10], eax` ... `mov ecx, eax`,
  and the C shows `pvVar5 = operator_new(0x28)` NULL-checked immediately above: the
  argument is `pvVar5`.
* `sub_41BCF0(0,0,0,0xff)` was one argument short - `xor eax,eax; ...; mov ecx,eax`, so the
  leading argument is 0.
* **the class that actually crashes here**: pointer slots initialised with *stale numeric
  addresses* from the original's image.  `PTR_s_Inserire_il_CD_..._0057ba3c` held `0x579BD0`,
  a string in the original's `.data`; the rebuild has something else at that address, and the
  value is handed to `MessageBoxA` as the message text.  Three rules now apply, in order:
  a datatype of `pointer` (or anything ending in `*`) in Ghidra's own symbol table types the
  slot as a pointer; a target this unit defines becomes `&name`; anything else is
  **materialised** - the bytes it pointed at are read out of `groove.exe` and emitted as
  `groove_str_<addr>`, and the pointer is initialised with that.  74 pointer slots are now
  symbolic and 13 strings exist only because a pointer needed them.

A fourth fix was incidental: the shim had lost `#include <stdio.h>` when `groove_FILE`
replaced it, so the first probe build failed with 24 `C2065`s on `fprintf`/`stderr`.

The probes are deliberately kept in the patch table: they are how the next round sees where
a run stops, and they are stderr-only.

**Next probe, precisely:** print `iVar4` immediately after the `sub_415690(0, "111.cor")`
call.  If it prints, the loader returned and the fault is in the message-box path; if it does
not, the fault is inside the loader - which the original survives (it checks the result),
so it would be a rebuild-side bug in that function.

### The next three: an IID sized one byte, a dropped COM argument, a missing WndProc

With that cluster fixed the exe ran `A -> B` and stopped: no `[main] C`, no dialog - a fault
between B and C.  `C` is printed right after `cVar3 = sub_556340();`, and `sub_556340` is the
**DirectDraw probe**: `LoadLibraryA("DDRAW.DLL")`, `GetProcAddress(...,"DirectDrawCreateEx")`,
then `CreateEx(0, &ppDD, &DAT_0056e70c, 0)`.  Three separate defects lived in that one function.

**1. `DAT_0056e70c` was one byte wide.**  Ghidra's symbol table records the access it saw, and
it saw one: `unsigned char DAT_0056e70c = 0xC0;`.  The bytes at 0x56E70C are
`c0 5e e6 15 9c 3b d2 11 b9 2f 00 60 97 97 ea 5b` - **IID_IDirectDraw7**
(`{15E65EC0-3B9C-11D2-B92F-00609797EA5B}`), with IID_IDirectDraw4 (`9C59509A-...`) immediately
after it.  A one-byte IID cannot match, so `DirectDrawCreateEx` fails with an
interface-not-supported HRESULT **on every machine, display or not**, the probe returns 0, and
the game takes its "cannot start" branch.  Same recorded-override class as the registry buffer
and the `fopen` mode strings: `DAT_0056e70c,array:0x10` in `type_overrides.csv`, and the
generator reads the real 16 bytes out of `groove.exe`.  The scan is cheap for the rest of the
table - of 882 one-byte data symbols, 270 have their address taken, and the real GUIDs sit in
the contiguous IID block 0x56E5CC-0x56E72C.

**2. Ghidra dropped the COM `this`.**  With the IID right `CreateEx` succeeded, and the next
line faulted:

```c
piVar3 = &local_4;
iVar2 = (*pFVar1)(0,piVar3,&DAT_0056e70c,0);
(**(code **)(*piVar3 + 8))(piVar3);       /* Ghidra: reads 8 bytes into the object */
```

`piVar3` holds the *address of the out-parameter slot*, so Ghidra's own COM idiom read a
function pointer 8 bytes into the object and pushed a stack address as `this`.  The listing is
unambiguous - `mov eax,[esp+8+var_4] / push eax / mov edx,[eax] / call [edx+8]` loads the
interface and pushes *that*.  One recorded row in `bulk_patches.csv` reassigns
`piVar3 = (int *)local_4;` before the call and leaves the idiom correct.

Checked first: 31 sites in the bulk have this `(**(code **)(*V + n))(V)` shape with a *local*
`V`.  Only this one puts a slot address in `V`; the other 30 load a real object pointer
(`piVar2 = *(int **)(...)`), where the idiom is right.  The shape is not the signal - what the
variable holds is.

**3. The window procedure is not in the build.**  With both fixed the trace runs
`A -> B -> C -> D -> E` and the log names the next defect itself: `[stub] LAB_0041dda0`,
printed *during* `sub_41DC40`, because the window class is registered with
`local_28.lpfnWndProc = (WNDPROC)&LAB_0041dda0;`.  A `LAB_<addr>` code label became a no-op
stub, so the rebuild installs an empty WndProc - no `WM_NCCREATE`/`WM_CREATE` handling, no
`DefWindowProc`.

Why there is no body: **IDA has a function at 0x41DDA0 (185 listing lines, a full WndProc with a
message switch), Ghidra does not.**  Ghidra's nearest functions are `sub_41DD80` (17 bytes) and
`sub_41DF60`; the whole 0x41DD91-0x41DF60 range is one gap in its function list, and
`tools/ghidra_decompile.bat` exports *Ghidra's* list, so a merged region is silently absent.
Measured size of the class: **438 of the 1,212 IDA entries have no `decompiled/sub_<addr>.c`**,
and **83 `LAB_<addr>` labels are used as function pointers** in the bulk - every one of them a
callback in the same position as this WndProc.

That fix belongs in the export step: an address the code *passes as a function pointer* is
provably a function entry, so create it in the analysis, decompile it, and let `make_bulk` alias
the label to the function.  Hand-porting 185 asm lines is a fallback for `sub_41DDA0` alone; it
does not generalise to the other 82.

**4. A table walked past its end.**  Next was `sub_568953`, and the log pointed at it: an
8-byte-per-entry key->value table (45 entries: `(1,22) (2,2) (3,2) (4,24) ...`) scanned from
`&DAT_0057cd78` to a *literal* `0x57CEE0`.  Both the value read (`0x57CD7C + i*8`) and the end
of the walk were the **original's** addresses; the rebuild places the table at 0x4C0608, so the
walk ran ~770 KB past its end into unmapped memory - the access violation the trace died on.
Two recorded decisions: `DAT_0057cd78,array:0x168` (45 entries, so the walk reads real keys and
`DAT_0057cee0` lands immediately after them) and a `bulk_patches.csv` row that takes the value
from the pointer the loop already holds and ends at `&DAT_0057cee0`.  The class is bigger than
the one site: **125 hex literals in the bulk are original-image addresses**, ~25 of them loop
bounds of this shape (`} while ((int)X < 0x572100);`), the rest mostly the known SEH scope-table
scaffolding.

**5. The generator read file bytes past a section's raw data.**  `.data` covers
0x570000-0x6DB935 *virtually* but only 0x570000-0x57E000 in the file; the rest is zero-filled by
the loader.  `pe_tools.read()` worked out the file offset without checking the section's raw
size, so a datum in that tail was initialised from whatever section *follows* in the file:
`DAT_00583410` (0x583410, which the listing declares `dd ?`) got `0x37CF37BC` - a pair out of
`.reloc`.  **147 of the 311 data symbols with a recorded initial value are in that tail**, so
all of them were wrong.  `read()` now returns zeros past the raw data, which is what the loader
does.

**A crash is a name now, not an address.**  `harness\build_dlls.bat` links the exe with a MAP
file, and `python tools\crash_report.py` runs it under gdb, subtracts the module handle the
trace logs as `hInst=` and resolves every frame through that map (it also says when a frame's
offset is too large to trust).  The map parser accepted only *uppercase* hex addresses while the
linker writes them lowercase as often as not, which silently dropped ~80% of the symbols and
made every resolution look coarse - fixed; the backtrace now reads:

```
#0  _sub_40FD00+0x2C     #1  _sub_40F4F0+0x2DF    #2  _sub_41D350+0x29A
#3  _WinMain@16         #4  ?__scrt_common_main_seh@@YAHXZ
```

A first reading of an earlier, half-resolved crash blamed the 2001 CRT's C++/SEH unwind bodies
(`sub_567BA4`, called from `sub_5679F3`) and proposed extending `crt_bodies.txt`.  **That was
wrong** - the coarse resolution had hid the real function - and it is worth recording because the
wrong fix looked reasonable.  The faults so far are in *game* code: `sub_556340`, `sub_568953`,
`sub_40FD00`.

**Where it stands.**  The trace reaches `[main] E` and dies inside the DirectDraw init: the
list-teardown `sub_40FD00` dereferences a head that nothing populated.  The original does call
that same teardown at startup - measured under gdb, its head holds a *heap* node (0x2A119E0) -
so the divergence is upstream of the teardown, in whatever fills that list.  Two things remain
open: the WndProc is still a stub (`[stub] LAB_0041dda0`), and **gdb runs of the original are not
a faithful oracle** - with faults passed through it exits normally within ~15 s, after a
*handled* access violation inside Miles (`aal!_AAL_CloseFilterProvider@4` calling
`FreeLibrary(0xbaadf00d)`), so the interactive run is the reference, not a debugged one.

**Run the three steps in order.**  `python tools\make_bulk.py` rewrites
`clean_subset.c`/`bulk_all.c`, but the chunk files the compiler consumes are written by
`python tools\compile_check.py`, and `harness\build_dlls.bat` only splits *those*.  Skipping
`compile_check.py` builds stale code: measured - after the `piVar3` row, `clean_subset.c` had the
patch, `build\exe_chunks\*.c` did not, and the exe crashed exactly as before.

### Editing the patch table: never by hand

This round cost three rounds of confusion to a single field.  A replacement text containing
a comma needs the field quoted; a replacement containing a **quote** needs that quote
*\"doubled\"* - and when I wrote one by hand instead, the row was silently malformed (the
parser kept the extra column, `make_bulk` never saw the replacement, and the function failed
with an error that pointed at the wrong line).  The table is now written through Python's
`csv` module whenever a row contains anything but letters, digits, spaces and `_`.  Every
generator already did that; the hand edits did not.

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

**The code under those wrappers is the whole bulk**: `build\groove_ghidra.dll` is built
from all 25 chunk objects (`harness\build_dlls.bat bulk`), 689 KB instead of the subset's
24 KB, and the numbers above were re-measured against *it*.  What it took, in the order
it was measured:

| Step | Result |
|---|---|
| link the system import libraries (`kernel32`, `user32`, `gdi32`, `advapi32`, `ole32`, `winmm`, `shell32`, `comctl32`, `version`, `ddraw`) | 282 unresolved symbols -> 167.  This is the only route for the `__imp__*` ones: an import-address entry cannot be spelled as a C symbol, `@` is not legal in an identifier |
| generate the rest with [`tools/gen_link_stubs.py`](tools/gen_link_stubs.py) | **links**: 167 stubs, classified in `src_generated/link_stubs.csv` - 55 code labels Ghidra turned into values, 39 game functions whose bodies are still excluded, 28 Miles entry points, 27 MSVC 6 CRT/compiler helpers, 8 Win32/COM/DirectX APIs, 10 other.  The generator reads both link logs, keeps what is already stubbed (otherwise a clean log would erase it) and drops any stub the linker now reports as a duplicate (LNK2005) - so the list shrinks by itself as functions land |
| the handful that must **not** be stubbed, in [`harness/crt_aliases.c`](harness/crt_aliases.c) | 16 names are implemented for real: `_malloc`/`_free`/`operator_new` (a stub returns NULL for every allocation), the `_mem*`/`_str*` family, `fcos`/`fsin`, and `__ftol`/`__frnd`, which MSVC 6 gave an x87 convention - written in `__asm` (`fistp`/`frndint`), because C cannot express `ST(0) -> EAX` |
| the six functions the harness replaces, in [`harness/substituted.txt`](harness/substituted.txt) + [`tools/make_dll_source.py`](tools/make_dll_source.py) | the driver feeds a chunk from a *memory buffer*, so the bulk's real stream wrappers (`sub_415A90`/`AB0`/`AD0`/`AF0`), `sub_562941` and `operator_new` are filtered out of the DLL's chunk set and `io_substitutes.c` supplies them - 962 of the 968 functions are in the tested image.  Linking the real wrappers and handing them a memory pointer is exactly how the MAP driver crashed (exit `0xC0000005`) before this |

Seven stubs are flagged in the summary as ones that would compute a **wrong** answer if
executed - the 64-bit helpers (`__alldiv`, `__aulldiv`, `__aullrem`, `__allmul`,
`__allshl`) and the float-formatting pair (`__cfltcvt`, `__fassign`).  A stub for
`__alldiv` returns 0 for every 64-bit division, so that list is the honest boundary of
what "it links" means here.

The `exe` half of the same build (`link /SUBSYSTEM:WINDOWS /ENTRY:entry`) is **not**
finished: it is 14 symbols short, all of them the runtime's own entry points
(`_memcpy`, `_memset`, `_cos`, `_sin`, `_malloc`, `_free`, `_log2`, `__stricmp`, ...)
which neither the DLL-CRT nor the static-CRT library sets resolve in this toolchain
when the CRT startup is bypassed (`/ENTRY:entry`).  The bulk's `entry` is itself one of
the excluded artefact functions, so a stub stands in for it.  The DLL is the tested
artifact; the exe is a link milestone one library-set away, and `build_dlls.bat bulk`
says so instead of pretending otherwise.

Three plausible shortcuts did **not** work, each measured with a two-function
experiment:

* `build_dlls.bat bulk` with `/Gy` + `/OPT:REF`, hoping the linker would discard the
  functions the wrappers cannot reach: it does not - the unreferenced function stays and
  its undefined symbol fails the link;
* the `/alternatename` aliases in `harness/import_stubs.c`, the device built for exactly
  this (and never part of any link line): the same experiment still fails with LNK2019,
  so the file is now documented as not working rather than relied on;
* stubbing the runtime's own names from the exe log (`memcpy`, `cos`, `malloc`): a stub
  shadows the real implementation for the whole image and collides with its prototype
  (C2371/C2040), so the generator refuses them (`STANDARD_C`) and they are library work.

One naming trap cost two rounds and is worth recording: the linker prints **decorated**
symbols, and x86 C decoration prepends one underscore - so the log's `_fcos` is the C
name `fcos`, and `__malloc` is `_malloc`.  Both sets of definitions here had to be
respelled against that rule, and the generator's skip-lists are what silently did nothing
while they were wrong.

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
2. Read it in `Game/groove.exe.asm`; give it a real name when its purpose is clear.
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
* The REA bridge needs two env vars before any provider starts:
  `GHIDRA_INSTALL_DIR` (here `D:\Programmi\Ghidra\ghidra_12.1.4_PUBLIC`) and
  `JAVA_HOME` pointed at a 21+ JDK.  The `java`/`javac` first on `PATH` are JDK 8,
  and REA correctly refuses that pair - a stale `JAVA_HOME` looks like a broken
  Ghidra install.
* REA is registered with the app in `~/.lmstudio/mcp.json`; on Windows it must be
  launched through `cmd.exe /d /c npx -y rea-agents@<version> mcp`, because
  `npx` is a `.cmd` shim that a shell-less stdio spawn cannot execute.
